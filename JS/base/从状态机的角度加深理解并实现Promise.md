## 从状态机的角度加深理解并实现Promise

来源：[https://segmentfault.com/a/1190000013170460](https://segmentfault.com/a/1190000013170460)

 **`这篇文章内容主要来自一篇[stack Overflow][0]高票答案`** 

声明：此Promise的实现仅仅是为了加深本人对其的理解，和A+规范有些出入，但是的确是目前看过所有promise代码中最漂亮，思路比较清晰的一个。
  文章不会特意帮助读者复习Promise基本操作。
## 状态机

Promise其实本质上就是一个状态机，所以首先我们描述一个静态的状态机，就像下边这样

```js
var PENDING = 0;
var FULFILLED = 1;
var REJECTED = 2;

function Promise() {
  // 存储的状态是上边的三个:执行中，已完成，已拒绝
  var state = PENDING;

  // 存储异步结果或者异步错误消息
  var value = null;

  // 负责处理中途加入的处理函数
  var handlers = [];
}
```
## 状态改变

完成了基本的状态机定义，接下来的问题就是完成“ **`状态改变`** ”这个动作的实现：

```js
var PENDING = 0;
var FULFILLED = 1;
var REJECTED = 2;

function Promise() {
  // 存储三个状态
  var state = PENDING;

  // 一旦出现状态的改变，异步结果就会被存到这个地方
  var value = null;

  // 存储成功或者失败的handler
  var handlers = [];

//状态转移到成功
  function fulfill(result) {
    state = FULFILLED;
    value = result;
  }
//状态转移到失败
  function reject(error) {
    state = REJECTED;
    value = error;
  }
}
```

到目前为止，我们给出了两个很纯粹的变化动作，在开发的过程中这两个动作会很不好用，所以我们在这两个动作的基础上构建一个高层次的动作（其实就是加点判断然后封装一层），就像下边这儿，名字就叫做resolve，但是注意和我们正常使用promise调用的那个resolve并不一样，不要搞混：

```js
var PENDING = 0;
var FULFILLED = 1;
var REJECTED = 2;

function Promise() {

  var state = PENDING;
  var value = null;
  var handlers = [];

  function fulfill(result) {
    state = FULFILLED;
    value = result;
  }

  function reject(error) {
    state = REJECTED;
    value = error;
  }
//这里暂时缺少两个重要函数getThen和doResolve这两个函数，稍后会说道
  function resolve(result) {
    try {
      var then = getThen(result);
      //判断then是不是一个Promise对象
      if (then) {
        doResolve(then.bind(result), resolve, reject)
        return
      }
      fulfill(result);
    } catch (e) {
      reject(e);
    }
  }
}
```

是的，我们的用到了两个辅助函数getThen和doResolve，现在给出实现：

```js
/**
 * 这里会判断value的类型，我们只要promise.then这个函数，其他的统统返回null
 *
 * @param {Promise|Any} value
 * @return {Function|Null}
 */
function getThen(value) {
  var t = typeof value;
  if (value && (t === 'object' || t === 'function')) {
    var then = value.then;
    if (typeof then === 'function') {
      return then;
    }
  }
  return null;
}

/**
 * 这个函数的主要作用就是串主逻辑，完成“变化状态”这个动作
 *
 * @param {Function} fn A resolver function that may not be trusted
 * @param {Function} onFulfilled
 * @param {Function} onRejected
 */
function doResolve(fn, onFulfilled, onRejected) {
//done的作用是让onFulfilled或者onRejected仅仅被调用一次，状态机状态一旦改变没法回头
  var done = false;
  try {
//在我们正常使用Promise的时候调的resolve，其实用的就是这里fn注入函数然后调用
    fn(function (value) {
      if (done) return
      done = true
      **onFulfilled(value)**
    }, function (reason) {
      if (done) return
      done = true
      onRejected(reason)
    })
  } catch (ex) {
    if (done) return
    done = true
    onRejected(ex)
  }
}
```
## 构建

好了，一个完整的状态机已经完成，我们完成了一个基本的状态变化逻辑，接下来要做的就是一步一步的朝promise标准进发，这个promise缺少什么呢，暂时缺的就是初始的动作啦（new promise（func）对象一旦被初始化内部代码立即执行），所以我们加上初始动作的开启

```js
var PENDING = 0;
var FULFILLED = 1;
var REJECTED = 2;

function Promise(fn) {

  var state = PENDING;
  var value = null;
  var handlers = [];

  function fulfill(result) {
    state = FULFILLED;
    value = result;
  }

  function reject(error) {
    state = REJECTED;
    value = error;
  }

  function resolve(result) {
    try {
      var then = getThen(result);
      if (then) {
        doResolve(then.bind(result), resolve, reject)
        return
      }
      fulfill(result);
    } catch (e) {
      reject(e);
    }
  }
//开启任务的执行，所以我说doResolve其实才是“主线任务”的引子，而fn其实就是你写的代码
  doResolve(fn, resolve, reject);
}
```
## 联动

我们实现了状态机，但是目前的问题是我们只能眼睁睁的看着代码的流动直到一个Promise结束为止，即没法添加也没法获取结果，这就有很大的局限性了，所以我们要使用then方法来串联Promise，用done方法来完成结果的收集，首先实现done方法，因为then其实说白了就是收集上边的结果--完成自己的逻辑--把结果传递给下一个Promise，做的事情是done的超集。

```js
var PENDING = 0;
var FULFILLED = 1;
var REJECTED = 2;

function Promise(fn) {

  var state = PENDING;
  var value = null;
  var handlers = [];

  function fulfill(result) {
    state = FULFILLED;
    value = result;
    //专门封装一个handle函数处理后续逻辑，在下面有this.handle(handler)方法
    handlers.forEach(handle);
    //在状态变成已处理并且之前加入的handler都被处理完毕的情况下再加入handler就会报错并且没有卵用
    handlers = null;
  }

  function reject(error) {
    state = REJECTED;
    value = error;
    handlers.forEach(handle);
    handlers = null;
  }

  function resolve(result) {
    try {
      var then = getThen(result);
      if (then) {
        doResolve(then.bind(result), resolve, reject)
        return
      }
      fulfill(result);
    } catch (e) {
      reject(e);
    }
  }

  function handle(handler) {
    if (state === PENDING) {
      handlers.push(handler);
    } else {
      if (state === FULFILLED &&
        typeof handler.onFulfilled === 'function') {
        handler.onFulfilled(value);
      }
      if (state === REJECTED &&
        typeof handler.onRejected === 'function') {
        handler.onRejected(value);
      }
    }
  }

//注意看下面done方法的实现，里边只有一个异步方法，换句话说就是会立即返回不会产生阻塞，我们之后会在then当中调用done方法，这里的onFulfilled, onRejected就是用户写的处理函数，promise异步的特性就是这样来的。
  this.done = function (onFulfilled, onRejected) {
    // ensure we are always asynchronous
    setTimeout(function () {
      handle({
        onFulfilled: onFulfilled,
        onRejected: onRejected
      });
    }, 0);
  }

  doResolve(fn, resolve, reject);
}
```

最后，我们来实现Promise.then,完成状态机的串联：

```js
//这段代码有点绕，主要需要完成的工作其实就是，判断上一个Promise是否完成，然后执行用户的then里边的回调代码，并最终返回一个新的Promise，然后依次循环。。。
this.then = function (onFulfilled, onRejected) {
//开启then之后就会返回一个新的promise，但是这个时候我们还可能有上一个Promise的任务没有完成,所以先把上边一个promise对象的this指向保存下来
  var self = this;
//返回一个新包装Promise,这和我们普通的在外边写new Promise是一个道理
  return new Promise(function (resolve, reject) {
//done的代码同样是立即返回，然后异步执行的
    return self.done(function (result) {
      if (typeof onFulfilled === 'function') {
        try {
          return resolve(onFulfilled(result));
        } catch (ex) {
          return reject(ex);
        }
      } else {
        return resolve(result);
      }
    }, function (error) {
      if (typeof onRejected === 'function') {
        try {
          return resolve(onRejected(error));
        } catch (ex) {
          return reject(ex);
        }
      } else {
        return reject(error);
      }
    });
  });
}
```

Over
更多参考请看下面：
[简单的实现Promsie][1]
[高性能实现Promise][2]，以及专门的[wiki][3]

[0]: https://stackoverflow.com/questions/23772801/basic-javascript-promise-implementation-attempt/23785244#23785244
[1]: https://github.com/then/promise/blob/master/src/core.js
[2]: https://github.com/petkaantonov/bluebird
[3]: https://github.com/petkaantonov/bluebird/wiki/Optimization-killers