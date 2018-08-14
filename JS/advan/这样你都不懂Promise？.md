## 这样你都不懂Promise,算我输！

来源：[https://juejin.im/post/5b5491856fb9a04fa8672cad](https://juejin.im/post/5b5491856fb9a04fa8672cad)

时间 2018-07-26 15:04:17



#### 1、Promise历史

Promise 是异步编程的一种解决方案，比我们传统的 **`回调函数`** 、 **`事件`** 更加合理，最早由社区提出并实现，ES6觉得很ok，就写进了语言标准中，统一了语法，并且提供了原生的Promise对象。

所谓的Promise，其实就是一个容器，里面保存着未来才会结束的事件（通常是一个异步操作）的结果，从javascript的语法上讲就是一个对象，从里面能获取异步操作的信息，Promise提供统一的api,各种异步操作都可以使用同样的方法来进行处理。


#### 2、Promise的特点

特点一：Promise对象的状态不受外界影响。代表着一个异步操作，有三种状态:Pending(进行中)、Fulfilled(已成功)和Reject(已失败)。只有异步操作的结果才可以决定当前是哪一种状态，任何其他操作都无法改变这个状态，这也就是Promise的由来。“承诺”，就是其他手段无法更改。

特点二：一旦状态改变了，就不会再改变。任何时候都可以得到这个结果。Promise对象的状态的改变只会是两种可能：从Pending变成Fulfilled和Pending变为Rejected。这要这两种情况发生，状态就凝固了，不会再改变了，而是一直保持这样一个结果这时候就成Resolved(已定型)。就算改变已经发生，再对Promise对象添加回调函数，也会立即得到这个结果。这与事件（event）完全不同，事件的特点我们都知道，如果错过它，就监听不到结果的。


## 二、基本用法

ES6规定，Promise对象是一个构造给函数，是用来生成Promise实例的。

```js
let Promise=new Promise(function(resolve,reject){
/*逻辑代码*/
    if(/*异步操作成功*/){
        resolve(value)
    }else{
        reject(error)
    }
})
复制代码
```

Promise构造函数式会接受两个参数的，该函数的两个参数是resolve和reject，是javascript引擎提供的，不用自己部署。

resolve函数的作用是，将Promise对象的状态从“未完成”到“成功”（就是从Pending变为Resolved）,在异步操作成功的时候，并将异步操作的结果作为参数传递进去；reject函数的作用是将Promise对象的状态从“未完成”变成为“失败”（即从Pending变为Rejected），在异步操作失败的时候调用，将异步草字哦报出的错误传递出去。

Promise实例生成以后，可以用then方法分别指定Resolve状态和Reject状态的回调函数。

```js
let Promise=new Promise(function(resolve,reject){})
Promise.then(function(value){
    //success
},function(error){
    //failuer
})
复制代码
```

then方法可以接受两个回调函数作为参数，第一个是Promise对象变成Resolved时调用，第二个是Promise对象的状态变为Rejectd的时候调用，第二个函数式可选的，也可以不写，这两个函数都接受Promise对象传出值作为参数。举一个栗子吧：

```js
function timeout(ms){
    return new Promise((resolve,reject)=>{
        setTimeout(resolve,ms,'done')
    })
}
timeout(100).then((value)=>{
    console.log(value)
})
复制代码
```

上面的代码,timeout方法会返回一个Promise的实例，一段时间以后才会发生的结果，过了指定时间（ms）以后，Promise实例就会变成Resolve，就会触发then的方法绑定的回调函数。

Promise初始化实例与以后就会立即执行，不妨看一下下面的打印验证：

```js
let promise=new Promise(function(resolve,reject){
    console.log("我是Promise")
    resolve()
})
promise.then(function(){
    comsole.log("我时候then的回调")
})
console.log('hello,promise!')

//我是Promise
//hello,promise!
//我时候then的回调
复制代码
```

上面的代码中，Promise实例化之后会立即执行，所以首先输出的是Promise，然后，then方法指定的回调函数将在当前脚本所有同步脚本执行完才会执行，所以上述代码中“我时候then的回调”最后输出。


#### 举一个页面图片异步加载的栗子：

```js
function loadImageAsync(url){
    retutn new Promise(function(resolve,reject){
        var image=new Image();
        image.onload=function(){
            resolve(image)
        }
        image.onerror=function(){
            reject(new Error('could not load image at'+url))
        }
        image.src=url
    })
    
}
复制代码
```

上面举出了常用防止页面阻塞异步加载图片的栗子，如果加载成功，就调用resolve方法，否则就调用reject方法。

如果不过瘾的话，就简单来实现一下当前单页面比较火的Vue、React框架，开发所用的Http请求axios和fetch的基于Promise实现Ajax的过程：

```js
let getJSON=function(url){
    let promise=new Promise(function(){
        let client=new XMLHttpRequest()
        client.open('GET',url)
        client.onreadystatechange=hander
        cilent.responseType='json'
        client.setRequestHeader('Accept',"application/json")
        client.send()
        function hander(){
            if(this.readystate!=4){
                return
            }
            if(this.statues===200){
                resolve(this.response)
            }else{
                reject(new Error(this.stautsText))
            }
        }
    })
    return promise
}

//使用
getJSON('/xxx/xx.json').then((json)=>{
    console.log('contents'+json)
},(error)=>{
    console.log("请求出错"+error)
})
复制代码
```

上面的代码中，getJSON是对XMLHttpRequest对象基于promise的封装，可以发出一个针对json数据的HTTP请求，并返回一个promise对象，可以看见getJSON内部resolve和reject函数都带有参数，那么这些参数会被传递给回调函数，reject幻术的参数通常是Error对象的实例，表示抛出错误，resolve函数的参数除了正常的值外，还可以是另外一个promise实例，比方说：

```js
let pro1=new Promise(function(resolve,reject){
    //....
})
let pro2=new Promise(function(resolve,reject){
    //...
    resolve(pro1)
})
复制代码
```

上面的代码中，pro1和pro2都是promise的实例，但是pro2的resolve方法将pro1作为参数，即一个异步操作的结果返回另一个异步操作结果。此时pro1的状态就会传递给pro2,也就是说pro1决定了pro2的状态，如果pro1状态是pending,那么pro2的回调函数就会等待pro1的状态已经resolve或者rejected,那么pro2的回调函数才立即执行。


## 三、Promise.prototype.then()

Promise实例具有then方法，即then方法是定义在原型对象Promise.prototype上的，作用是给Promise实例添加状态改变时的回调函数。then方法的第一个参数是Resolve状态的回调函数，第二个是Rejected（可选）状态的回调函数。

then方法返回的是一个新的Promise实例，不是原来那个Promise实例，因此可以采用链式写法，即then方法后面再调用另一个then方法。

```js
getJSON('xxx/xx.json').then(function(json){
    return json.post
}).tnen(function(post){
    
})
复制代码
```

采用链式的then可以指定一组按照次序调用的回调函数，这时，前一个回调函数有可能返回的还是一个异步操作，即Promise实例，而后一个回调函数会等待该Promise对象状态改变才调用。


## 四、Promise.prototype.catch()

Promise.prototype.catch的方法是.then(null,rejection)的别名，用于指定发生错误的回调函数。

举个栗子：

```js
getJSON('xxx/xx.json').then(function(json){
   //...
}).catch(function(err){
    console.log('错误'+error)
})
复制代码
```

上面的代码，只要then中某一步异步操作抛出错误，状态变成Rejected，都会被catch()所捕获到，然后指定其回调函数执行，处理这个错误。Promise对象的错误具有冒泡机制，会一直向后传递，一直到被catch()处理函数所捕获，也就是说错误会被下一个catch语句捕获。

```js
getJSON('xxx/xx.json').then(function(json){
   //...some code1
}).then(function(json){
   //...some code2
}).catch(function(err){
    console.log('错误'+error)
})
复制代码
```

上面的代码中一共有三个Promise对象，getJSON产生，两个then产生两个，其中任何一个报错，都会被最后一个catch所捕获，一般使用的时候，注意不要在then()中定义Rejected回调函数，官方建议总是使用catch方法处理错误异常回调。

小伙伴们，以上的基础介绍，希望对你们在vue、react开发中的Promise实现的一些东西有一个更好的认识。


