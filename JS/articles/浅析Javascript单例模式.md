## 浅析Javascript单例模式

来源：[http://www.cnblogs.com/mianbaodaxia/p/9118660.html](http://www.cnblogs.com/mianbaodaxia/p/9118660.html)

时间 2018-06-01 11:26:00



## 定义

保证一个类仅有一个实例，并提供一个访问它的全局访问点 。就想我们在开发中有些对象只需要一个，例如window对象。


## 1. 实现单例模式

```js


var Singleton = function( name ) { 
    this.name = name;
};
Singleton.prototype.getName = function() { 
    alert ( this.name );
};
Singleton.getInstance = function( name ) { 
    if ( !this.instance ) {   //这里的this指的是Singleton，所以两次调用的都是同一个this
        this.instance = new Singleton( name ); 
    }
    return this.instance;
};
var a = Singleton.getInstance( 'sven1' ); 
var b = Singleton.getInstance( 'sven2' );
alert ( a === b ); // true      
      

```

  
我们通过 Singleton.getInstance 来获取 Singleton 类的唯一对象，这种方式相对简单，这种方式非常类似于Java的单例模式实现，但有 一个问题，就是增加了这个类的“不透明性”，Singleton 类的使用者必须知道这是一个单例类， 跟以往通过 new的方式来获取对象不同，这里偏要使用 Singleton.getInstance 来获取对象。 那么有没有办法直接New出来的就是一个单例的对象呢？

  
## 2.透明的单例模式

```js


var Singleton = (function() {
  var instance;
  var Singleton = function(name) {
    if ( instance ) {
      return instance;
    }
    this.name = name;
    return instance = this;
  };
  Singleton.prototype.getName = function() {   //就近原则，用的是上面的Singleton
    alert ( this.name );
  };
  return Singleton;
})();
var a = new Singleton( 'sven1' );
var b = new Singleton( 'sven2' );
console.log(a == b)


```

    

虽然现在完成了一个透明的单例类的编写，但它同样有一些缺点。

为了把 instance 封装起来，我们使用了自执行的匿名函数和闭包，并且让这个匿名函数返回，真正的 Singleton 构造方法，这增加了一些程序的复杂度，阅读起来也不是很舒服。 所以说有利有弊吧

          
## 3.Javascript中的单例模式


前面提到的几种单例模式的实现，更多的是接近传统面向对象语言中的实现，单例对象从 “类”中创建而来。在以类为中心的语言中，这是很自然的做法。比如在 Java 中，如果需要某个对象，就必须先定义一个类，对象总是从类中创建而来的。

但 JavaScript 其实是一门无类(class-free)语言（虽然ES6中有了类的概念），也正因为如此，生搬单例模式的概念并无 意义。在 JavaScript 中创建对象的方法非常简单，既然我们只需要一个“唯一”的对象，为什 么要为它先创建一个“类”呢?

          

    
    
#### 单例模式的核心是确保只有一个实例，并提供全局访问。

问题：现在有一个需求是点击页面上的登录按钮，显示一个登录弹窗，很显然这个弹窗是唯一的，也就是单例的

（1）

```html


<html> 
  <body>
    <button id="loginBtn">登录</button> 
  </body>
  <script>
  var loginLayer = (function() {
    var div = document.createElement( 'div' ); 
    div.innerHTML = '我是登录浮窗'; 
    div.style.display = 'none'; 
    document.body.appendChild( div );
    return div; 
  })();
  document.getElementById( 'loginBtn' ).onclick = function(){
  loginLayer.style.display = 'block'; };
  </script>
 </html>


```

      
上面解决方案是在页面加载完成的时候便创建好这个 div 浮窗，这个浮窗一开始肯定是隐藏状态的，当用户点击登录按钮的时候，它才开始显示，但是有时候我们根本不需要进行登录操作，如果一开始就被创建好其实是一种浪费资源的行为，DOM资源可是很珍贵的

（2）

```html


<html> 
  <body>
    <button id="loginBtn">登录</button> 
  </body>
  <script>
  var createLoginLayer = function() {
    var div = document.createElement( 'div' ); 
    div.innerHTML = '我是登录浮窗'; 
    div.style.display = 'none'; 
    document.body.appendChild( div );
    return div; 
  };
  document.getElementById( 'loginBtn' ).onclick = function(){
    var loginLayer = createLoginLayer();
    loginLayer.style.display = 'block';
  }; 
  </script>
</html>


```

上面的方法，虽然做到了点击时才创建，但失去了单例的效果。当我们每次点击登录按钮的时候，都会 创建一个新的登录浮窗 div。虽然我们可以在点击浮窗上的关闭按钮时(此处未实现)把这个浮 窗从页面中删除掉，但这样频繁地创建和删除节点明显是不合理的，也是不必要的。

      

    

  

（3）

```html


<html> 
  <body>
    <button id="loginBtn">登录</button> 
  </body>
  <script>
  var createLoginLayer = (function(){ 
    var div;
    return function() { 
      if ( !div ) {
        div = document.createElement( 'div' ); 
        div.innerHTML = '我是登录浮窗'; 
        div.style.display = 'none'; 
        document.body.appendChild( div );
      }
      return div; 
    }
  })();
  document.getElementById( 'loginBtn' ).onclick = function(){ 
    var loginLayer = createLoginLayer(); 
    loginLayer.style.display = 'block';
  };
  </script>
</html>


```

上述方法，用一个变量来判断是否已经创建过登录浮窗，和上面上面实现单例的类的原理是一样的


## 4.通用的单例模式

如果在项目中用到了很多单例的情况，如果每个都做判断，其实是相当复杂的事情，但能不能写一个通用的方法，经过这个方法处理的就是单例的

```html


<html>
  <body>
    <button id="loginBtn">登录</button>
  </body>
  <script>
  var getSingle = function(fn){
    var result;
    return function() {
      return result || ( result = fn .apply(this, arguments ) );
    }
  };
  var createLoginLayer = function() {
    var div = document.createElement( 'div' );
    div.innerHTML = '我是登录浮窗';
    div.style.display = 'none';
    document.body.appendChild( div );
    return div;
  };
  var createMask = function() {
    var div = document.createElement( 'div' );
    div.innerHTML = 'mask';
    div.style.display = 'none';
    document.body.appendChild( div );
    return div;
  };
  var createSingleLoginLayer = getSingle( createLoginLayer );
  var createMask = getSingle( createMask );
  document.getElementById( 'loginBtn' ).onclick = function(){
    var loginLayer = createSingleLoginLayer();
    var mask = createMask();
    loginLayer.style.display = 'block';
    mask.style.display = 'block';
  };
  </script>
</html>


```

我们发现在开发中并不会单独使用弹出窗，遮罩层和弹出窗是经常结合在一起使用，上面的方法就能使弹出窗和遮罩层都是单例的，其中核心的方法就是getSingle

在getSingle函数中，创建对象的方法 fn 被当成参数动态传入 getSingle 函数 ，result 变量因为身在闭包中，它永远不会被销毁。在将来的请求中，如果 result 已经被赋值，那么它将返回这个值 。


## 5. ES6中的单例模式

```js



class SingletonApple {
  constructor(name, creator, products) {
      this.name = name;
      this.creator = creator;
      this.products = products;
  }
  //静态方法
  static getInstance(name, creator, products) {
    if(!this.instance) {
      this.instance = new SingletonApple(name, creator, products);
    }
    return this.instance;
  }
}


let appleCompany = SingletonApple.getInstance('苹果公司', '乔布斯', ['iPhone', 'iMac', 'iPad', 'iPod']);


```

ES6有类，也有静态方法，实现单例模式也显得非常的简单，学过Java的同学能看出几乎和Java的实现一模一样，直接调用`SingletonApple的静态方法 ``getInstance就能获得一个单例对象。ES6能不能直接new一个单例的对象出来呢，答案当然是可以的 `

```js


class SingletonApple {
  constructor(name, creator, products) {
      this.name = name;
      this.creator = creator;
      this.products = products;
  }
  //静态方法
  static getInstance(name, creator, products) {
    if(!this.instance) {
      this.instance = new SingletonApple(name, creator, products);
    }
    return this.instance;
  }
}


```

Javascript单例模式介绍到此结束，有不对的地方请及时指出


