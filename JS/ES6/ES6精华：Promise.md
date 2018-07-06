## ES6精华：Promise

来源：[https://segmentfault.com/a/1190000015423360](https://segmentfault.com/a/1190000015423360)

`Promise`是异步编程的解决方案之一，相比传统的回调和事件机制更为合理和强大。
## 1 场景举例

某天，突发奇想，发了封邮件给木匠师傅，定制一个如此这般的家具。  
木匠有求必应，即是说，邮件一旦发出就得到了他的承诺(`Promise`)：在下一定尽力。

邮件中规定好了结果的通知方式：  
成功了，直接将家具(`res`)邮递(`resolve`)过来。  
失败了，直接将失败的信息(`err`)发邮件(`reject`)过来。

```js
let P = new Promise((resolve, reject) => {
  if (/*最终的结果*/) {
    resolve('家具'); // 成功，直接邮递家具。
  } else {
    reject('失败的原因'); // 失败，发邮件告知失败原因。
  }
});
```

邮件发出等价于得到木匠的承诺`P`，之后，能做的只有等待(`then`)。

```js
P.then(res => {
  console.log('成功，收到家具。此刻心情：开心。');
}, err => {
  console.log('失败，收到原因。此刻心情：失落。');
});
```
## 2 行为特征
### 2.1 状态

每个`Promise`有三种状态：进行中(`pending`)、已成功(`resolved`)和已失败(`rejected`)。  
创建即进入`pending`状态，在传入方法中一旦调用了`resolve/reject`方法，最终状态便变成`resolved/rejected`。  
一旦变成结果状态，即更改成`resolved/rejected`，状态便被冷冻，不能再被更改。
 **`状态容器`**   
`Promise`实质是个状态容器。  
得到结果状态后，任何时候都可以访问到此状态。  
这与事件订阅通知不同，如果订阅发生在通知之后，订阅是不起作用的。
 **`状态不可控`**   
一旦创建`Promise`，便会立刻执行，无法取消。  
处于`pending`状态时，无法得知进程具体的信息，比如完成百分比（虽然可以自行设置回调进行通知）。
 **`失败的状态`**   
成功的状态只能由`resolve`方法转成。  
失败的状态可以由`reject`方法转成，也可以由抛出错误间接转成。

```js
三者都会正常的打印出失败的信息。

new Promise((resolve, reject) => {
  reject('error');
}).catch(console.log); // error

new Promise((resolve, reject) => {
  a;
}).catch(console.log); // ReferenceError: a is not defined

new Promise((resolve, reject) => {
  throw 'error';
}).catch(console.log); // Error: error
```
 **`错误的报告机制`**   
如果失败状态没有接收失败的回调函数接收，`Promise`会抛出错误。  
这里的抛出错误，仅仅是在控制台显示之类的提示，不会终止程序的进程。

```js
先打印出 'err' ，再报错。

new Promise((resolve, reject) => {
  reject();
});

new Promise((resolve, reject) => {
  reject('err');
}).then(() => {}, console.log);
```

一旦`Promise`设置了失败回调函数，即便是代码执行错误，也会自行消化，不外报。

```js
虽然 a 未被定义，但全程安静，无槽点。

new Promise((resolve, reject) => {
  a;
}).then(() => {}, () => {});
```
### 2.2 执行顺序
 **`传入方法`**   
创建`Promise`的同时也会执行传入方法。  
传入方法不会因为调用了`resolve/reject`便终止执行，所以更优的方式是`retrun resolve/reject`。

```js
打印出 1 2 。

new Promise((resolve, reject) => {
  console.log(1);
  resolve();
  console.log(2);
});
```
 **`回调方法`**   
立即得到结果的`Promise`，其回调函数依然会晚于本轮事件执行。  
这种后执行不同于`setTimeout`的将执行函数`push`到执行栈，而是将执行函数放到本轮的末尾。

```js
得到的结果是：1 2 3 4 5 6 。

console.log(1);

let p = new Promise((resolve, reject) => {
  console.log(2);
  resolve();
});

setTimeout(() => {
  console.log(5);
});

p.then(function() {
  console.log(4);
});

setTimeout(() => {
  console.log(6);
});

console.log(3);
```
### 2.3 结果参数

传入`reject`的参数，一般是字符串或`Error`实例，表示抛出的错误。  
传入`resolve`的参数，一般是相应的`JSON`数据等，表示得到的数据。

传入`resolve`的参数，还可以是另一个`Promise`实例。  
这时，只有当内层的`Promise`结束后，外层的`Promise`才会结束。

```js
过两秒后，打印出 2000 。

new Promise((resolve, reject) => {
  resolve(createPromise());
}).then(console.log);

function createPromise() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve(2000);
    }, 2000);
  });
}
```

在这种情况下，如果内层失败，并不等于传递`Error`实例给`resolve`不同。  
前者是内层`Promise`抛出了错误将被外层捕获，后者仅仅是参数为一个`Error`实例。

```js
内层失败的信息，被外层捕获。过两秒，打印出 '2' 2000 。

new Promise((resolve, reject) => {
  resolve(createPromise());
}).then(res => {
  console.log('1', res);
}, err => {
  console.log('2', err);
});

function createPromise() {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      reject(2000);
    }, 2000);
  });
}
```
## 3 实例方法
### 3.1 then()

该方法可传入两个，分别对应成功/失败时的回调函数。  
该方法返回的是一个新的`Promise`对象，这也是可以使用链式（`.then.then...`）的原因。

```js
let p1 = new Promise(resolve => resolve(2000));
let p2 = p1.then(() => {}, () => {});
console.log(p1 === p2); // false
```
 **`return`**   
链式中，后者的状态取决于前者（成功/失败）的回调函数中返回（`return`）的结果。  
如果没有返回，相当返回一个成功的状态，值为`undefined`。  
如果返回为`Promise`对象，后者的状态由该对象的最终状态决定。  
如果返回为非`Promise`对象的数据，相当返回一个成功的状态，值为此数据。  
如果前者执行时抛出了错误，相当是返回一个失败的状态，值为此错误。

```js
依次打印出：
1 res 2000
2 res undefined
3 res 3000
4 err 4000

new Promise(resolve => resolve(2000))
.then(res => {
  console.log('1 res', res);
})
.then(res => {
  console.log('2 res', res);
  return 3000;
})
.then(res => {
  console.log('3 res', res);
  return new Promise((resolve, reject) => {
    reject(4000);
  });
})
.then(console.log, err => {
  console.log('4 err', err);
});
```
 **`状态的传递`**   
在链式中，如果前者的状态没有被后者捕获，会一直（像）冒泡到被捕获为止。  
状态被捕获后便消失，这之后的的状态由当前`then`返回的状态决定，之后重复。

```js
依次打印出：
2 res 2000
3 res 3000

new Promise(resolve => resolve(2000))
.then(null, err => {
    console.log('1 err', err);
})
.then(res => {
  console.log('2 res', res);
  return 3000;
})
.then(res => {
  console.log('3 res', res);
});
```
### 3.2 catch()

用于指定发生错误时的回调函数，等价于：`.then(null, callback)`。  
其表现与`then`一致，比如返回新的`Promise`，状态的继承和传递等等。

一般推荐使用`catch`而不是`then`的第二个方法接收错误。  
因为`catch`可以捕获`then`自身的错误，也更接近同步的写法（`try/catch`）。

```js
new Promise(() => {})
.then(() => {
  ...
})
.catch(() => {
  ...
});
```
### 3.3 finally()

用于`Promise`处理结束后的收尾工作。  
传入其的回调函数不会接受任何参数，意味着没有办法知道`Promise`的结果。  
这也正表明，`finally`里面的操作与状态无关，不依赖`Promise`的处理结果。

其本质和`catch`一样，也是`then`方法的变种。  
不过其仅仅是状态的传递者，只会返回原状态，不会接收状态和创建新的状态。

```js
p.finally(() => {
  // codes...
});

--- 等价于

p.then(res => {
  // codes...
  return res; // 将原成功状态返回
}, err => {
  // codes...
  throw err; // 将原失败状态返回
});
```
 **`示例`**   
在请求数据时，我们会显示加载图案，请求完成后无论结果都要隐藏此图案。

```js
一般，一个完整的 Promise 的结构会如下。

showLoading = true;

new Promise((resolve, reject) => {
  // 请求...
})
.then(res => {
  // 成功处理...
})
.catch(err => {
  // 失败处理...
})
.finally(() => {
  // 重置一些状态...
  showLoading = false;
});
```
## 4 静态方法
### 4.1 resolve()

此方法直接返回一个状态为`resolved`，值为其参数的`Promise`。

```js
Promise.resolve(res);
--- 等价于
new Promise(resolve => resolve(res));
```
### 4.2 reject()

此方法直接返回一个状态为`rejected`，值为其参数的`Promise`。

```js
Promise.reject(res);
--- 等价于
new Promise((resolve, reject) => reject(res));
```
### 4.3 all()

此方法用于将多个`Promise`实例，包装成一个新的`Promise`实例。  
其参数为一个数组，每一项应为`Promise`实例（不是则会使用`Promise.resolve`进行转化）。

新`Promise`的状态取决于传入数组中的每一项的最终状态。  
如果有一项状态变成`rejected`，新实例则为`rejected`，值为该项的返回值。  
如果全部项都变成了`resolved`，新实例则为`resolved`，值为包含每一项返回值的数组。

```js
三秒后，打印出：[1, 2, 3]。

let pArr = [1, 2, 3].map(createPromise);

Promise.all(pArr).then(console.log);

function createPromise(num) {
  return new Promise((resolve, reject) => {
    setTimeout(() => { resolve(num) }, num * 1000);
  });
}
```
### 4.4 race()

此方法与`all()`基本相同，传入的参数也是一个`Promise`数组。  
不同的是，新`Promise`的最终状态是由数组中第一个状态改变的项（成功或失败）决定的。

```js
一秒后，打印出 1 。

let pArr = [1, 2, 3].map(createPromise);

Promise.race(pArr).then(console.log);

function createPromise(num) {
  return new Promise((resolve, reject) => {
    setTimeout(() => { resolve(num) }, num * 1000);
  });
}
```
## 5 混合实战

在实际项目中，有时需要处理多个相互关联的异步脚本（多为数据请求）。  
`ES6`之后`async`函数应该是最灵活方便的途径，`Promise`在其中扮演基石的角色。  
不过在这一小节，依旧会以`Promise`作为主要的解决办法进行分析。

这里是下面需要用到的共同方法。

```js
// 创建异步。
function createPromise(name) {
  return new Promise(resolve => {
    setTimeout(() => resolve({
      [name]: `Data form ${name}`
    }), 1000);
  });
}

// 异步 A, B, C。
function A(param) {
  return createPromise('A');
}
function B(param) {
  return createPromise('B');
}
function C(param) {
  return createPromise('C');
}

// 并发处理多个独立的异步请求。
function dealIndependentRequests(qArr, callback) {
  return new Promise((resolve, reject) => {
    let done = false;
    let resData = [];
    let leftNum = qArr.length;

    qArr.forEach((q, i) => {
      Promise.resolve(q).then(res => {
        !done && dealRequest(res, i, true);
      }).catch(err => {
        !done && dealRequest(err, i, false);
      });
    });

    function dealRequest(res, index, isSuccess) {
      if (callback) {
        done = callback(resData, res, index, isSuccess);
      } else {
        resData[index] = {
          res: res,
          isSuccess: isSuccess
        };
      }

      if ( done || !(--leftNum) ) resolve(resData);
    }
  }); 
}
```
### 5.1
 **`5.1.1`**   
有三个请求数据的异步：A, B, C。  
最终的数据必须同时结合三者的数据计算得出。

基于要求，直接使用`Promise.all`进行并发请求，等到所有信息到齐后结束。

```js
大概一秒后，打印出：Get all data: [{...}, {...}, {...}]。

Promise.all([A(), B(), C()])
.then(res => {
  console.log(`Get all data:`, res);
})
.catch(err => {
  console.error(err);
});
```
 **`5.1.2`**   
有三个请求数据的异步：A, B, C。  
最终的数据必须同时结合A, B的数据计算得出，C只是修饰数据。

基于要求，使用`Promise.all`并发A, B请求，成功后再发C。  
如果前者成功，再看C是否成功，之后使用不同方式处理得到最终数据。

```js
大概两秒后，打印出：[{…}, {…}] {C: "Data form C"}。

Promise.all([A(), B()])
.then(res => {
  C().then(c => {
    console.log(res, c);
  })
  .catch(err => {
    console.log(res);
  });
})
.catch(err => {
  console.error(err);
});
```
 **`5.1.3`**   
有三个请求数据的异步：A, B, C。  
最终的数据必须基于结合A的数据计算得出，B, C起独立的修饰作用。

基于要求，与上面的处理基本相同。  
不过要在A的回调里同时请求B, C，并使用状态控制变量控制程序的进程。

```js
大概两秒后，打印出：End {A: "Data form A"} [{…}, {…}]。

A()
.then(res => {
  dealIndependentRequests([B(), C()])
  .then(subs => {
    console.log('End', res, subs);
  })
  .catch(err => {
    console.log('End', res);
  });
})
.catch(err => {
  console.error(err);
});
```
### 5.2
 **`5.2.1`**   
有三个请求异步：A, B, C。  
B的请求需要发送A中的a信息。  
C的请求需要发送B中的b信息。

基于要求，必须逐步请求A, B, C，而且前两者任一出错则停止。

```js
大概三秒后，打印出：End {C: "Data form C"}。

A()
.then(res => {
  return B(res.a);
})
.then(res => {
  return C(res.b);  
})
.then(res => {
  console.log('End', res);
})
.catch(err => {
  console.log(err);
});
```
 **`5.2.2`**   
有三个请求异步：A, B, C。  
B的请求需要发送A中的a信息，即便A失败也需要发送。  
C的请求需要发送B中的b信息。

基于要求，与前者基本相同，只是即便A失败了也会继续请求。

```js
大概三秒后，打印出：End {C: "Data form C"}。

A()
.then(res => {
  return B(res.a);
})
.catch(err => {
  return B();
})
.then(res => {
  return C(res.b);  
})
.then(res => {
  console.log('End', res);
})
.catch(err => {
  console.log(err);
});
```
### 5.3
 **`5.3.1`**   
有三个请求异步：A, B, C。  
需要找出所有异步结果中，包含某值的结果的集合。

基于要求，并发请求所有数据，一一验证返回符合的结果集。

```js
大概一秒后，打印出：[{B: "Data form B"}]

dealIndependentRequests([A(), B(), C()], (data, res) => {
  if (res.B) data.push(res);
  return false;
})
.then(console.log)
.catch(console.log);
```
 **`5.3.2`**   
有三个请求异步：A, B, C。  
只需要找到一个包含某值的结果。

基于要求，还是使用并发请求。  
有任一请求符合预期时，结束并返回（暂不涉及取消请求操作）。

```js
大概一秒后，打印出：[{B: "Data form B"}]

dealIndependentRequests([A(), B(), C()], (data, res) => {
  if (res.B) return data.push(res);
  return false;
})
.then(console.log)
.catch(console.log);
```
