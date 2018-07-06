## 深入学习this、call、apply、bind

来源：[http://www.jianshu.com/p/b01507377e31](http://www.jianshu.com/p/b01507377e31)

时间 2018-05-18 17:45:17


标签： js

this的指向问题一直是面试里的常客。也是es5的众坑之一。对于es6而讲，它极大地避免了this带来的错误。但是为了为了维护一些老代码，还是有必要了解this的。

  
### this的指向原则：    

  

* this 永远指向最后调用它的那个对象（es5）。
* 匿名函数的this总指向Window对象(全局对象)（es5）。
* 箭头函数中的 this 只和定义它时候的作用域的 this 有关，而与在哪里以及如何调用它无关，同时它的 this 指向是不可改变的。       
    

  
### 全局环境中的 this 是什么    

浏览器：

```js
console.log(this); //Window
```

node：

```js
console.log(this); //global
```

  
### 函数里执行    

  
#### 全局函数执行    


一个函数被直接调用的时候，属于全局调用，这时候它的 this 指向 全局对象

例如：

```js
function test(){
    console.log(this);
}
test();//Window
```

  
#### 作为对象的方法调用    

例如：

```js
var obj={
    name:"JoeWright",
    foo:function(){
        console.log(this);
    }
};
obj.foo();//Object {name: "JoeWright", foo: ƒ}
```


如果把对象的方法赋值给一个变量，然后直接调用这个变量,这时候,this 指向全局对象。

例如：

```js
var obj={
    name:"Joe",
    foo:function(){
        console.log(this);
    }
};
var test=obj.foo;
test();//Window
```

  
#### 作为一个构造函数使用    


this 指向了这个构造函数调用时候实例化出来的对象

例如：

```js
function Person(name){
    this.name=name;
    console.log(this);
}
//this 指向了这个构造函数调用时候实例化出来的对象
var p1=new Person("JoeWright"); //Person
//构造函数其实也是一个函数，如果我们把它当作一个普通函数执行，这个 this 仍然执行全局
var p2=Person("Wright");//Window
```

  
#### 匿名函数使用（this的一些坑）    


匿名函数的this总指向Window对象

例如：

```js
var obj={
    name:"JoeWright",
    f1:function(){
        console.log(this);//Window
    },
    f2:function(){
        console.log(this);//Object
        setTimeout(this.f1,1000);//此时this.f1相当于setTimeout             函数的形参fun，即做了fun=this.f1这个操作
    }
};
obj.f2();
```

解决方法（改变this的指向）：

1.使用箭头函数

```js
var obj={
    name:"JoeWright",
    f1:function(){
        console.log(this);
    },
    f2:function(){
        console.log(this);//Object
        setTimeout(()=>{
            console.log(this);//Object
        },1000);
    }
};
obj.f2();
```

2.在函数内部使用that=this（或者_this=this）

```js
var obj={
    name:"JoeWright",
    f1:function(){
        console.log(this);
    },
    f2:function(){
        console.log(this);//Object
        var that=this;//上面的this指向的是obj4,这里我们用that变量存储下来
        setTimeout(function(){
            console.log(that);//Object
        },1000);
    }
};
obj.f2();
```

  
### 改变this的指向    

改变`this`的指向有以下几种方法：

  

* 使用 ES6 的箭头函数
* 在函数内部使用`that = this`（或`_this = this`）      
* 使用`apply`、`call`、`bind`
* `new`实例化一个对象      
    


1,2两点上面已经讲过，下面介绍下`apply`、`call`、`bind`的用法

例如：

```js
function Cat(name){
    this.name=name;
}
function Dog(name){
    this.name=name;
}
Cat.prototype.eat=function(food){
    console.log(this.name+" eat "+food);
}
Dog.prototype.eat=function(food){
    console.log(this.name+" eat "+food);
}
var c=new Cat("kitty"); 
var d=new Dog("Bubby"); 
c.eat("fish");  //kitty eat fish
d.eat("meat");  //Bubby eat meat
c.eat.apply(d,["fish"]);  //Bubby eat fish
c.eat.call(d,"fish");    //Bubby eat fish
d.eat.call(c,"apple");   //kitty eat apple
d.eat.bind(c,"apple")(); //kitty eat apple
```

从上述的例子可知：

  

* `apply`接收的是一个由若干参数组成的数组，而call接收的是若干个参数列表。      
* `bind`与`call`的用法类似，但是bind **`创建了一个新的函数`** ，我们必须 **`手动去调用它`** 。      
    

  
#### new关键字改变this的指向    

如果函数调用前使用了 new 关键字, 则是调用了构造函数。

例如：

```js
function Cat(name){
    this.name=name;
}
var c=new Cat("kitty"); 
console.log(c.name);  //kitty
```


new的过程：

伪代码：

```js
var c=new Cat("kitty"); 
new Cat{
    var obj={};
    obj.__proto__=Cat.prototype;
    var res=Cat.call(obj,"kitty");
    return typeof res==="obj"?res:obj;
}
```

  

* 先创建一个空对象obj
* 将新创建的空对象的 **`隐式原型`** 指向其构造函数的 **`显式原型`**       
* 使用`call`改变`this`的指向      
* 如果没有返回值或者返回的是一个非对象值，则将obj返回为一个新对象；如果返回值是一个对象的话，就直接返回该对象。
    

  
### apply，call，bind的应用场景    

嗯，既然call，apply，bind可以改变this的指向，那我们在哪里可以用到呢


（1） **`处理伪数组`** 

什么是伪数组？

先看一个例子吧：

```js

  

* 1
* 2
* 3
* 4
    



```

```js
const oLi=document.getElementsByTagName("li");
console.log(oLi.length);//4
console.log(oLi);  //HTMLCollection(4) [li, li, li, li]
console.log(oLi.slice(1,3)); //Uncaught TypeError: oLi.slice is not a function
```

看到没，上面的`oLi`就是一个伪数组。它有数组的`length`属性，但是不可用数组的`slice`方法。

伪数组的定义：

  

* 存在length属性
* 可以通过数组下标的方式对元素进行访问
* 能像遍历数组一样遍历
* 不能使用数组的`slice()`、`push()`等方法。      
    

常见的伪数组

  

* 函数的argument对象
* document.getElementsByTagName()、document.getElementsByClassName()、childNodes/children等方法的返回值（返回的是一个节点列表）
    

解决办法： **`伪数组没有这些方法那就借用Array的方法`** 。

```js
[].slice.call(oLi,1,3)  //[li, li]（推荐）
```

或者：

```js
oLi.slice=[].slice;  //为oLi添加一个slice方法（会污染数组对象）
console.log(oLi.slice(1,3));//[li, li]
```

如果可以随意改变原对象，可以 **`直接将其转成真正的数组对象`** 。

```js
Array.prototype.slice.call(oLi);
console.log(oLi.slice(1,3)); //[li, li]
```

  
#### （2）继承

  

* 单继承
    

```js
function Person(name){
    this.name=name;
}
function Man(sex,name){
    this.sex=sex;
    Person.call(this,name); //继承Person的name
}
var p=new Man("male","JoeWright");
console.log(p.sex,p.name); //male JoeWright
```

  

* 多继承
    

```js
function Person(name){
    this.name=name;
}
function Man(sex){
    this.sex=sex;
}
function Coder(name,sex,learn){
    this.learn=learn;
    Person.call(this,name);
    Man.call(this,sex);
}
var p2=new Coder("JoeWright","male","FE");
console.log(p2.name,p2.sex,p2.learn);//JoeWright male FE
```

（3）获取数组的最值

    
Math.max()方法，支持传递多个参数，比如：`Math.max(1,4,2,3,7,5,6)`

但是它不支持直接传递一个数组作为参数，比如：`Math.max(new Array(1,4,2,3,7,5,6))`。

这里，只要我们有方法把数组，一个一个拆分开来，传递到`Math.max()`方法中，就实现了传递数组的方法。而`apply`接收一个数组，并且是将数组中的每个值，分开来，传递给`Math.max()`方法

    

例如：

```js
var arr=[1,3,6,10,9];
console.log(Math.max.apply(null,arr)); //10
console.log(Math.min.apply(null,arr)); //1
//等价于
console.log(Math.max.apply(Math,arr)); //10
console.log(Math.min.apply(Math,arr)); //1
console.log(Math.max.apply("a",arr)); //10 
console.log(Math.min.apply(a,arr)); //Uncaught ReferenceError: a is not defined(a未定义报错)
```

但为什么上面的例子中apply传的第一个参数为null和Math都会得到相同的结果呢？在网上看了很多解答后，我得出一个结论：按apply的语法上来讲，apply的第一个参数此时是Math.max()方法运行时指定的 this 值。需要注意的是，指定的 this 值并不一定是该函数执行时真正的 this 值，如果这个函数处于非严格模式下，则指定为 null 或 undefined 时会自动指向全局对象（浏览器中就是window对象），同时值为原始值（数字，字符串，布尔值）的 this 会指向该原始值的自动包装对象。 换句话说：当我们传Math就相当于Math对象调用max方法，我们传window相当于window调用这个方法，传Number就相当于Number函数对象调用max方法... **`但是传入的参数必须是一个对象`** （或者参数的原始值的自动包装对象），所以我们传123，"aaa",undefined都可以，但是传入一个未定义的变量是不行的，当然传入null也是可以的。


（4）合并数组

例如：

```js
var arr=[1,3,6,10,9];
var arr2=[2,4,8];
[].push.apply(arr,arr2);
console.log(arr); //[1, 3, 6, 10, 9, 2, 4, 8]
```

  
#### 最后：大家觉得有帮助的话，请点个赞哈哈，如果文章中有写的不恰当的地方，欢迎大家指出~    

  
