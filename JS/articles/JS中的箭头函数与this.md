## JS中的箭头函数与this

来源：[https://juejin.im/post/5aa1eb056fb9a028b77a66fd](https://juejin.im/post/5aa1eb056fb9a028b77a66fd)

时间 2018-03-13 11:04:32


在ES6语法之前，JS中的函数由function关键字、params参数和被花括号包裹的函数体组成。为了与后面说到的箭头函数相区别，我们先把这样的函数叫做常规函数，常规函数既可以用声明式写法也可以用赋值式写法。例子：

```js
function test(name) {  //声明式写法
    console.log(name)
}
test('Jerry')

let test2 = function(name) {  //赋值式写法
    console.log(name)
}
test2('Tom')
```


#### 2. 箭头函数的写法

ES6箭头函数的引入，使函数的写法变的更加简洁，但在书写上要遵循一定的规则。


#### 规则一：箭头函数只能用赋值式写法，不能用声明式写法

例子：

```js
const test = (name) => {
    console.log(name)
}
test('Jerry')
```


#### 规则二：如果参数只有一个，可以不加括号，如果没有参数或者参数多于一个就需要加括号

例子：

```js
const test = name => {
    console.log(name)
}
test('Jerry')

const test2 = (name1, name2) => {
    console.log(name1 + ' and ' + name2)
}
test2('Tom', 'Jerry')
```


#### 规则三：如果函数体只有一句话，可以不加花括号

例子：

```js
const test = name => console.log(name)
```


#### 规则四：如果函数体没有括号，可以不写return，箭头函数会帮你return

例子：

```js
const add = (p1, p2) => p1 + p2
add(10, 25)
```

记住：函数体的花括号与return关键字同在。

从以上的例子我们可以看出，箭头函数对常规函数的圆括号和花括号都进行了简化。除了这些简化，箭头函数对于常规函数最大的优化之处在于this。


### 二、理解常规函数中this

在探讨箭头函数对于this的优化之前，我们先得明白this究竟是什么，以及它是如何使用的。this是使用call方法调用函数时传递的第一个参数，它可以在函数调用时修改，在函数没有调用的时候，this的值是无法确定。   

如果没有使用过call方法来调用函数的话，上面的对于this的定义可能不太明白。那么我们需要先理解函数调用的两种方法。


#### 1. 纯粹的函数调用

第一种方法最常见，例子如下：

```js
function test(name) {
    console.log(name)
    console.log(this)
}
test('Jerry')  //调用函数
```

这种方法我们使用最多，但是这种函数调用方法只是一种简写，它完整的写法是下面这样的：

```js
function test(name) {
    console.log(name)
    console.log(this)
}
test.call(undefined, 'Tom')
```

注意到上面调用函数的call方法了吗？call方法接收的第一个参数就是this，这里我们传了一个undefined 。那么，依据定义，函数执行了之后打出来的this会是undefined吗？也不是。  

如果你传的 context 就 null 或者 undefined，那么 window 对象就是默认的 context（严格模式下默认 context 是 undefined）。

所以这里我们打出来的this是Window对象。


#### 2. 对象中函数的调用

直接看例子：

```js
const obj = {
    name: 'Jerry',
    greet: function() {
        console.log(this.name)
    }
}
obj.greet()  //第一种调用方法
obj.greet.call(obj) //第二种调用方法
```

例子里第一种调用方法只是第二种调用方法的语法糖，第二种才是完整的调用方法， **`而且第二种方法厉害的地方在于它可以手动指定this`** 。  

手动指定this的例子：

```js
const obj = {
    name: 'Jerry',
    greet: function() {
        console.log(this.name)
    }
}
obj.greet.call({name: 'Spike'})  //打出来的是 Spike
```

从上面的例子我们看到greet函数执行时this，已经被我们改过了。


#### 3. 构造函数中this

构造函数里的this稍微有点特殊，每个构造函数在new之后都会返回一个对象，这个对象就是this，也就是context上下文。

例子：

```js
function Test() {
    this.name = 'Tom'
}
let p = new Test()
console.log(typeof p)  //object
console.log(p.name)    // Tom
```


#### 4. window.setTimeout()和window.setInterval()中函数的调用

window.setTimeout()和window.setInterval()的函数中的this有些特殊，里面的this默认是window对象。


#### 简单总结一下：函数完整的调用方法是使用call方法，包括`test.call(context, name)`和`obj.greet.call(context,name)`，这里的context就是函数调用时的上下文，也就是this，只不过这个this是可以通过call方法来修改的；构造函数稍微特殊一点，它的this直接指向new之后返回的对象；`window.setTimeout()`和`window.setInterval()`默认的是this是window对象。  


#### 三、理解箭头函数中的this

上面关于this讲了很多，this是函数用call方法调用时传递的第一个参数，而且它还可以手动更改，这样要确定this的值就太麻烦了。不过，箭头函数的出现给我们确定this帮了一些忙。


#### 1. 箭头函数的特性一：默认绑定外层this

上面提到：this的值是可以用call方法修改的，而且只有在调用的时候我们才能确定this的值 。而当我们使用箭头函数的时候，箭头函数会默认帮我们绑定外层this的值，所以在箭头函数中this的值和外层的this是一样的。   

不使用箭头函数例子：

```js
const obj = {
	a: function() { console.log(this) }    
}
obj.a()  //打出的是obj对象
```

使用箭头函数的例子：

```js
const obj = {
    a: () => {
        console.log(this)
    }
}
obj.a()  //打出来的是window
```

在使用箭头函数的例子里，因为箭头函数默认不会使用自己的this，而是会和外层的this保持一致，最外层的this就是window对象。   


#### 2. 箭头函数的特性二：不能用call方法修改里面的this

这个也很好理解，我们之前一直在说，函数的this可以用call方法来手动指定，而为了减少this的复杂性，箭头函数无法用call方法来指定this。

例子：

```js
const obj = {
    a: () => {
        console.log(this)
    }
}
obj.a.call('123')  //打出来的结果依然是window对象
```

因为上文我们说到window.setTimeout()中函数里的this默认是window，我们也可以通过箭头函数使它的this和外层的this保持一致：

window.setTimeout()的例子：

```js
const obj = {
    a: function() {
        console.log(this)
        window.setTimeout(() => { 
            console.log(this) 
        }, 1000)
    }
}
obj.a.call(obj)  //第一个this是obj对象，第二个this还是obj对象
```

想必大家明白了，函数obj.a没有使用箭头函数，因为它的this还是obj，而setTimeout里的函数使用了箭头函数，所以它会和外层的this保持一致，也是obj；如果setTimeout里的函数没有使用箭头函数，那么它打出来的应该是window对象。


### 四、多层对象嵌套里函数的this

这里是笔者在学习时遇到的一点疑惑。箭头函数里的this是和外层保持一致的，但是如果这个外层有好多层，那它是和哪层保持一致呢？

直接上例子：

```js
const obj = {
    a: function() { console.log(this) },
    b: {
    	c: function() {console.log(this)}
	}
}
obj.a()  // 打出的是obj对象, 相当于obj.a.call(obj)
obj.b.c() //打出的是obj.b对象, 相当于obj.b.c.call(obj.b)
```

上面的代码都符合直觉，接下来把obj.b.c对应的函数换成箭头函数，结果如下：

```js
const obj = {
    a: function() { console.log(this) },
    b: {
    	c: () => {console.log(this)}
	}
}
obj.a()   //没有使用箭头函数打出的是obj
obj.b.c()  //打出的是window对象！！
```

obj.a调用后打出来的是obj对象，而obj.b.c调用后打出的是window对象而非obj，这表示多层对象嵌套里箭头函数里this是和最最外层保持一致的。   

上面的内容就是笔者学习箭头函数中梳理出来的知识点，如有错误，请批评指正！这是我在掘金上写的第三篇文章，感谢阅读！

本文参考：    [this 的值到底是什么？一次说清楚][0]
  



[0]: https://link.juejin.im?target=https%3A%2F%2Fuser-gold-cdn.xitu.io%2F2018%2F3%2F9%2F1620a0f210b48408