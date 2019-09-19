## JavaScript 进阶知识 - 高级篇

来源：[https://segmentfault.com/a/1190000017534335](https://segmentfault.com/a/1190000017534335)

![][0]
## JS高级
## 前言

经过前面几篇文章的学习，相信大家已经对`js`有了大部分的理解了，但是要想真正的掌握好`js`，本篇才是关键。由于`js`高级阶段的知识点比较难理解，所以本篇文章花了大量的时间去理思路，有可能有一些知识点遗漏了，也有可能有部分知识点写的不对，欢迎大家留言纠正。## 1.异常处理
 **`常见的异常分类`** 


* 运行环境的多样性导致的异常（浏览器）
* 语法错误，代码错误

 异常最大的特征，就是一旦代码出现异常，后面的代码就不会执行。 
### 1.1异常捕获

捕获异常，使用`try-catch`语句：
```js
try{
    // 这里写可能出现异常的代码
}catch(e){
    // e-捕获的异常对象
    // 可以在此处书写出现异常后的处理代码
}
```

异常捕获语句执行的过程为：

* 代码正常运行, 如果在`try`中出现了错误,`try`里面出现错误的语句后面的代码都不再执行, 直接跳转到`catch`中
* `catch`中处理错误信息
* 然后继续执行后面的代码
* 如果`try`中没有出现错误, 那么不走`catch`直接执行后面的代码

 通过`try-catch`语句进行异常捕获之后，代码将会继续执行，而不会中断。 
 **`示例代码：`** 

```js
console.log('代码开始执行');
try{
    console.log(num); // num 在外部是没有定义的
}catch(e){
    console.log(e);
    console.log('我已经把错误处理了');
}
console.log('代码结束执行');
```
 **`效果图：`** 

![][1]
 从效果图中我们可以看到，`num`是一个没有定义的变量，如果没有放在`try-catch`代码块中，后面的‘代码结束执行’就不会被打印。通过把`try-catch`放在代码块中，出现错误后，就不会影响后面代码的运行了，他会把错误信息打印出来。 
 **`注意：`** 


* 语法错误异常用`try-catch`语句无法捕获，因为在预解析阶段，语法错误会直接检测出来，而不会等到运行的时候才报错。
* `try-catch`在一般日常开发中基本用不到，但是如果要写框架什么的，用的会非常多。因为这个会让框架变得健壮

 **`异常捕获语句的完整模式`** 

异常捕获语句的完整模式为`try-catch-finally`
```js
try {
    //可能出现错误的代码
} catch ( e ) {
    //如果出现错误就执行
} finally {
    //结束 try 这个代码块之前执行, 即最后执行
}
```
 `finally`中的代码，不管有没有发生异常，都会执行。一般用在后端语言中，用来释放资源，`JavaScript`中很少会用到 
### 1.2抛出异常

如何手动的抛出异常呢？

案例：自己写的一个函数，需要一个参数，如果用户不传参数，此时想直接给用户抛出异常，就需要了解如何抛出异常。抛出异常使用`throw`关键字，语法如下：

```js
throw 异常对象;
```

异常对象一般是用`new Error("异常消息")`, 也可以使用任意对象
 **`示例代码：`** 

```js
function test(para){
    if(para == undefined){
        throw new Error("请传递参数");
        //这里也可以使用自定义的对象
        throw {"id":1, msg:"参数未传递"};
    }
}

try{
    test();
}catch(e){
    console.log(e);
}
```
 **`效果图：`** 

![][2]

![][3]
### 1.3异常的传递机制

```js
function f1 () {
    f2(); 
}

function f2 () {
    f3();
}

function f3() {
    throw new Error( 'error' );
}
f1();  // f1 称为调用者, 或主调函数, f2 称为被调用者, 或被调函数
```
 当在被调函数内发生异常的时候，异常会一级一级往上抛出。 
## 2.面向对象编程

在了解面向对象编程之前，我们先来了解下什么是面向过程，什么是面向对象，他们之间的区别是什么。### 2.1 面向过程和面向对象的的对比
 **`举个例子：`** 

日常洗衣服 **`1.面向过程的思维方式：`** 

面向过程编程：将解决问题的关注点放在解决问题的具体细节上，关注如何一步一步实现代码细节；
```js
step 1:收拾脏衣服
step 2:打开洗衣机盖
step 3:将脏衣服放进去
step 4:设定洗衣程序
step 5:开始洗衣服
step 6:打开洗衣机盖子
step 7:晒衣服
```
 **`2.面向对象的思维方式：`** 

面向对象编程：将解决问题的关注点放在解决问题所需的对象上，我们重点找对象；
```js
人（对象）
洗衣机（对象）
```
 在面向对象的思维方式中：我们只关心要完成事情需要的对象，面向对象其实就是对面向过程的封装； 
 **`示例代码：`** 

在页面上动态创建一个元素
```js
//面向过程
//1-创建一个div
var  div=document.createElement('div');
//2-div设置内容
div.innerHTML='我是div';
//3-添加到页面中
document.body.appendChild(div);

//面向对象
$('body').append('我也是div
');
```
 我们可以看出，`jQ`封装的其实就是对面向过程的封装。 
 **`总结：`**  面向对象是一种解决问题的思路，一种编程思想。
### 2.2 面向对象编程举例

设置页面中的`div`和`p`的边框为`'1px solid red'` **`1、传统的处理办法`** 

```js
// 1> 获取div标签
var divs = document.getElementsByTagName( 'div' );
// 2> 遍历获取到的div标签
for(var i = 0; i < divs.length; i++) {
    //3> 获取到每一个div元素,设置div的样式
    divs[i].style.border = "1px dotted black";
}

// 4> 获取p标签
var ps = document.getElementsByTagName("p");
// 5> 遍历获取到的p标签
for(var j = 0; j < ps.length; j++) { 
    // 获取到每一个p元素 设置p标签的样式
    ps[j].style.border = "1px dotted black"; 
}
```
 **`2、使用函数进行封装优化`** 

```js
// 通过标签名字来获取页面中的元素 
function tag(tagName) { 
    return document.getElementsByTagName(tagName); 
}

// 封装一个设置样式的函数 
function setStyle(arr) { 
    for(var i = 0; i < arr.length; i++) { 
        // 获取到每一个div或者p元素 
        arr[i].style.border = "1px solid #abc"; 
    } 
}
var dvs = tag("div");
var ps = tag("p");
setStyle(dvs); 
setStyle(ps);
```
 **`3、使用面向对象的方式`** 

```js
// 更好的做法：是将功能相近的代码放到一起 
var obj = {     // 命名空间
    getEle: { 
        tag: function (tagName) { 
            return document.getElementsByTagName(tagName); 
        }, 
        id: function (idName) { 
            return document.getElementById(idName); 
        } 
        // ...
    },    
    setCss: { 
        setStyle: function (arr) { 
            for(var i = 0; i < arr.length; i++) { 
                arr[i].style.border = "1px solid #abc"; 
            } 
        }, 
        css: function() {}, 
        addClass: function() {}, 
        removeClass: function() {} 
        // ... 
    } 
    // 属性操作模块 
    // 动画模块 
    // 事件模块 
    // ... 
};

var divs = obj.getEle.tag('div');
obj.setCss.setStyle(divs);
```
### 2.3 面向对象的三大特性

面向对象的三大特性分别是：`'封装'`，`'继承'`，`'多态'`。 **`1、封装性`** 

对象就是对属性和方法的封装，要实现一个功能，对外暴露一些接口，调用者只需通过接口调用即可，不需要关注接口内部实现原理。

* `js`对象就是“键值对”的集合


* 键值如果是数据( 基本数据, 复合数据, 空数据 ), 就称为属性
* 如果键值是函数, 那么就称为方法



* 对象就是将属性与方法封装起来
* 方法是将过程封装起来

 **`2、继承性`** 

所谓继承就是自己没有, 别人有,拿过来为自己所用, 并成为自己的东西 **` 2.1、传统继承基于模板 `** 

子类可以使用从父类继承的属性和方法。

```js
class Person {
 string name;
 int age;
}

class Student : Person {
}
var stu = new Student();
stu.name
```
 即：让某个类型的对象获得另一个类型的对象的属性的方法 
 **` 2.2、js 继承基于对象 `** 

在`JavaScript`中，继承就是当前对象可以使用其他对象的方法和属性。
`js`继承实现举例：混入（`mix`）

```js
// 参数o1和o2是两个对象，其中o1对象继承了所有o2对象的“k”属性或者方法
var o1 = {};
var o2 = {
    name: 'Levi',
    age: 18,
    gender: 'male'
};
function mix ( o1, o2 ) {
    for ( var k in o2 ) {
        o1[ k ] = o2[ k ];
    }
}
mix(o1, o2);
console.log(o1.name); // "Levi"
```
 **`3、多态性（基于强类型，js中没有多态）只做了解`** 

同一个类型的变量可以表现出不同形态，用父类的变量指向子类的对象。
```js
动物 animal = new 子类(); // 子类：麻雀、狗、猫、猪、狐狸...
动物 animal = new 狗();
animal.叫();
```
### 2.4 创建对象的方式
 **`1、字面量 {}`** 

```js
var student1 = {
    name:'诸葛亮',
    score:100,
    code:1,
}

var student2 = {
    name:'蔡文姬',
    score:98,
    code:2,
}

var student3 = {
    name:'张飞',
    score:68,
    code:3,
}
```
 字面量创建方式，代码复用性太低，每一次都需要重新创建一个对象。 
 **`2、Object()构造函数`** 

```js
var student1 = new Object();
    student1.name = '诸葛亮';
    student1.score = 100;
    student1.code = 1;

var student2 = new Object();
    student2.name = '蔡文姬';
    student2.score = 98;
    student2.code = 2;
    
var student3 = new Object();
    student3.name = '张飞';
    student3.score = 68;
    student3.code = 3;
```
 代码复用性太低，字面量创建的方式其实就是代替`Object()`构造函数创建方式的。 
 **`3、自定义构造函数`** 

自定义构造函数，可以快速创建多个对象，并且代码复用性高。
```js
// 一般为了区分构造函数与普通函数，构造函数名首字母大写
function Student(name,score,code){  
    this.name = name;
    this.score = score;
    this.code = code;
}

var stu1 = new Student('诸葛亮',100,1);
var stu2 = new Student('蔡文姬',98,2);
var stu3 = new Student('张飞',68,3);
```
 **`构造函数语法：`** 


* 构造函数名首字母大写；
* 构造函数一般与关键字：`new`一起使用；
* 构造函数一般不需要设置`return`语句，默认返回的是新创建的对象；
* `this`指向的是新创建的对象。

 **`构造函数的执行过程：`** 


* `new`关键字，创建一个新的对象，会在内存中开辟一个新的储存空间；
* 让构造函数中的`this`指向新创建的对象；
* 执行构造函数，给新创建的对象进行初始化（赋值）；
* 构造函数执行（初始化）完成，会将新创建的对象返回。

 **`构造函数的注意点：`** 


* 构造函数本身也是函数；
* 构造函数有返回值，默认返回的是新创建的对象；
* 但是如果手动添加返回值，添加的是值类型数据的时候，构造函数没有影响。如果添加的是引用类型（数组、对象等）值的时候，会替换掉新创建的对象。


```js
function Dog(){
    this.name="哈士奇";
    this.age=0.5;
    this.watch=function(){
        console.log('汪汪汪，禁止入内');
    }
    // return false;          返回值不会改变，还是新创建的对象
    // return 123;            返回值不会改变，还是新创建的对象
    // return [1,2,3,4,5];    返回值发生改变，返回的是这个数组
    return  {aaa:'bbbb'};  // 返回值发生改变，返回的是这个对象
}

var d1=new Dog();  // 新创建一个对象
console.log(d1);
```

* 构造函数可以当做普通函数执行，里面的`this`指向的是全局对象`window`。

```js
 function Dog(){
    this.name="husky";
    this.age=0.5;
    this.watch=function(){
        console.log('汪汪汪，禁止入内');
    }
    console.log(this);  // window对象
    return 1;
}
console.log(Dog());  // 打印 1
```
### 2.5 面向对象案例

通过一个案例，我们来了解下面向对象编程（案例中有一个`prototype`概念，可以学完原型那一章后再来看这个案例）。 **`需求：`** 


* 实现一个`MP3`音乐管理案例；
* 同种类型的`MP3`，厂家会生产出成百上千个，但是每个`MP3`都有各自的样式、使用者、歌曲；
* 每个`MP3`都有一样的播放、暂停、增删歌曲的功能（方法）；

 **`图解：`** 

![][4]
 **`示例代码：`** 

```js
    // 每个MP3都有自己的 主人：owner 样式：color 歌曲：list
    function MP3(name,color,list){
        this.owner = name || 'Levi';  // 不传值时默认使用者是‘Levi’
        this.color = color || 'pink';
        this.musicList = list || [
            {songName:'男人哭吧不是罪',singer:'刘德华'},
            {songName:'吻别',singer:'张学友'},
            {songName:'对你爱不完',singer:'郭富城'},
            {songName:'今夜你会不会来',singer:'黎明'}
        ];
    }
    // 所有的MP3都有 播放 暂停 音乐 增删改查的功能
    MP3.prototype = {
        // 新增
        add:function(songName,singer){
            this.musicList.push({songName:songName,singer:singer});
        },
        // 查找
        select:function(songName){
            for(var i=0;i<this.musicList.length;i++){
                if(this.musicList[i].songName == songName){
                    return this.musicList[i];
                }
            }
            return null;  // 如果没有搜索到返回null
        },
        // 修改
        update:function(songName,singer){
            // 先找到这首歌 在修改
            var result = this.select(songName); // 查找
            if(result){
                result.singer = singer; // 修改
            }
        },
        // 删除
        delete:function(songName){
            // 先找到音乐  splice(index,1)
            var result = this.select(songName);
            // 知道该音乐的索引值
            // 删除
            if(result){
               var index = this.musicList.indexOf(result);
               this.musicList.splice(index,1); // 从指定索引值来删除数据
            }
        },
        // 显示
        show:function(){
            console.log(this.owner+'的MP3');
            for(var i=0;i<this.musicList.length;i++){
                console.log(this.musicList[i].songName +'---'+this.musicList[i].singer);
            }
        }
    }
    
    var XiaoHong = new MP3('小红');  // 实例小红MP3
    var XiaoMing = new MP3('小明');  // 实例小明MP3
    var XiaoDong = new MP3('小东');  // 实例小东MP3
    
    XiaoHong.add('十年','陈奕迅');          // 小红的歌单里添加歌曲
    XiaoDong.add('月亮之上','凤凰传奇');    // 小东的歌单里添加歌曲
    
    XiaoMing.musicList = [                  // 小明的歌单替换
        {
            songName:'精忠报国',
            singer:'屠洪刚'
        },
        {
            songName:'窗外',
            singer:'未知'
        }
    ];
    // 展示各自的歌单
    XiaoHong.show();        
    XiaoMing.show();
    XiaoDong.show();
```
 **`打印结果：`** 

![][5]
## 3.原型
### 3.1 传统构造函数存在问题
 **`通过自定义构造函数的方式，创建小狗对象：`** 

两个实例化出来的“小狗”，它们都用的同一个`say`方法，为什么最后是`false`呢？
```js
function Dog(name, age) {
    this.name = name;
    this.age = age;
    this.say = function() {
        console.log('汪汪汪');
    }
}
var dog1 = new Dog('哈士奇', 1.5);
var dog2 = new Dog('大黄狗', 0.5);

console.log(dog1);
console.log(dog2);

console.log(dog1.say == dog2.say); //输出结果为false
```
 **`画个图理解下：`** 

![][6]
 每次创建一个对象的时候，都会开辟一个新的空间，我们从上图可以看出，每只创建的小狗有一个`say`方法，这个方法都是独立的，但是功能完全相同。随着创建小狗的数量增多，造成内存的浪费就更多，这就是我们需要解决的问题。 
 **`为了避免内存的浪费，我们想要的其实是下图的效果：`** 

![][7]
 **`解决方法：`** 

这里最好的办法就是将函数体放在构造函数之外，在构造函数中只需要引用该函数即可。
```js
function sayFn() {
    console.log('汪汪汪');
}

function Dog(name, age) {
    this.name = name;
    this.age = age;
    this.say = sayFn();
}
var dog1 = new Dog('哈士奇', 1.5);
var dog2 = new Dog('大黄狗', 0.5);

console.log(dog1);
console.log(dog2);

console.log(dog1.say == dog2.say); //输出结果为 true
```
 **`这样写依然存在问题：`** 


* 全局变量增多，会增加引入框架命名冲突的风险
* 代码结构混乱，会变得难以维护

 想要解决上面的问题就需要用到`构造函数的原型`概念。 
### 3.2 原型的概念

`prototype`：原型。每个构造函数在创建出来的时候系统会自动给这个构造函数创建并且关联一个空的对象。这个空的对象，就叫做原型。 **`关键点：`** 


* 每一个由构造函数创建出来的对象，都会默认的和构造函数的原型关联；
* 当使用一个方法进行属性或者方法访问的时候，会先在当前对象内查找该属性和方法，如果当前对象内未找到，就会去跟它关联的原型对象内进行查找；
* 也就是说，在原型中定义的方法跟属性，会被这个构造函数创建出来的对象所共享；
* 访问原型的方式：`构造函数名.prototype`。

 **`示例图：`** 

![][8]
 **`示例代码：`**  给构造函数的原型添加方法

```js
function Dog(name,age){
    this.name = name;
    this.age = age;
}

// 给构造函数的原型 添加say方法
Dog.prototype.say = function(){
    console.log('汪汪汪');
}

var dog1 = new Dog('哈士奇', 1.5);
var dog2 = new Dog('大黄狗', 0.5);

dog1.say();  // 汪汪汪
dog2.say();  // 汪汪汪
```
 我们可以看到，本身`Dog`这个构造函数中是没有`say`这个方法的，我们通过`Dog.prototype.say`的方式，在构造函数`Dog`的原型中创建了一个方法，实例化出来的`dog1`、`dog2`会先在自己的对象先找`say`方法，找不到的时候，会去他们的原型对象中查找。 
 **`如图所示：`** 

![][9]
 在构造函数的原型中可以存放所有对象共享的数据，这样可以避免多次创建对象浪费内存空间的问题。 
### 3.3 原型的使用
 **`1、使用对象的动态特性`** 

使用对象的动态属性，其实就是直接使用`prototype`为原型添加属性或者方法。
```js
function Person () {}

Person.prototype.say = function () {
    console.log( '讲了一句话' );
};

Person.prototype.age = 18;

var p = new Person();
p.say();  // 讲了一句话
console.log(p.age);  // 18
```
 **`2、直接替换原型对象`** 

每次构造函数创建出来的时候，都会关联一个空对象，我们可以用一个对象替换掉这个空对象。
```js
function Person () {}

Person.prototype = {
    say : function () {
        console.log( '讲了一句话' );
    },
};

var p = new Person();
p.say();  // 讲了一句话
```
 **`注意：`** 

使用原型的时候，有几个注意点需要注意一下，我们通过几个案例来了解一下。
* 使用`对象.属性名`去获取对象属性的时候，会先在自身中进行查找，如果没有，就去原型中查找；

```js
// 创建一个英雄的构造函数 它有自己的 name 和 age 属性
function Hero(){
    this.name="德玛西亚之力";
    this.age=18;
}
// 给这个构造函数的原型对象添加方法和属性
Hero.prototype.age= 30;
Hero.prototype.say=function(){
    console.log('人在塔在！！！');
}

var h1 = new Hero();
h1.say();   // 先去自身中找 say 方法，没有再去原型中查找  打印：'人在塔在！！！'
console.log(p1.name);  // "德玛西亚之力"
console.log(p1.age);   // 18 先去自身中找 age 属性，有的话就不去原型中找了
```

* 使用`对象.属性名`去设置对象属性的时候，只会在自身进行查找，如果有，就修改，如果没有，就添加；

```js
// 创建一个英雄的构造函数
function Hero(){
    this.name="德玛西亚之力";
}
// 给这个构造函数的原型对象添加方法和属性
Hero.prototype.age = 18;

var h1 = new Hero();
console.log(h1);       // {name:"德玛西亚之力"}
console.log(h1.age);   // 18

h1.age = 30;           // 设置的时候只会在自身中操作，如果有，就修改，如果没有，就添加 不会去原型中操作
console.log(h1);       // {name:"德玛西亚之力",age:30}
console.log(h1.age);   // 30
```


* 一般情况下，不会将属性放在原型中，只会将方法放在原型中；
* 在替换原型的时候，替换之前创建的对象，和替换之后创建的对象的原型不一致！！！


```js
// 创建一个英雄的构造函数 它有自己的 name 属性
function Hero(){
    this.name="德玛西亚之力";
}
// 给这个构造函数的默认原型对象添加 say 方法
Hero.prototype.say = function(){
    console.log('人在塔在！！！');
}

var h1 = new Hero();
console.log(h1);    // {name:"德玛西亚之力"}
h1.say();           // '人在塔在！！！'

// 开辟一个命名空间 obj，里面有个 kill 方法
var obj = {
    kill : function(){
        console.log('大宝剑');
    }
}

// 将创建的 obj 对象替换原本的原型对象
Hero.prototype = obj;

var h2 = new Hero();

h1.say();           // '人在塔在！！！'
h2.say();           // 报错

h1.kill();          // 报错
h2.kill();          // '大宝剑'
```

画个图理解下：

![][10]
 图中可以看出，实例出来的`h1`对象指向的原型中，只有`say()`方法，并没有`kill()`方法，所以`h1.kill()`会报错。同理，`h2.say()`也会报错。 
### 3.4 __proto__属性

在`js`中以`_`开头的属性名为`js`的私有属性，以`__`开头的属性名为非标准属性。`__proto__`是一个非标准属性，最早由`firefox`提出来。 **`1、构造函数的 prototype 属性`** 

之前我们访问构造函数原型对象的时候，使用的是`prototype`属性：
```js
function Person(){}

//通过构造函数的原型属性prototype可以直接访问原型
Person.prototype;
```

在之前我们是无法通过构造函数`new`出来的对象访问原型的：
```js
function Person(){}

var p = new Person();

//以前不能直接通过p来访问原型对象
```
 **`2、实例对象的 __proto__ 属性`** 

`__proto__`属性最早是火狐浏览器引入的，用以通过实例对象来访问原型，这个属性在早期是非标准的属性，有了`__proto__`属性，就可以通过构造函数创建出来的对象直接访问原型。
```js
function Person(){}

var p = new Person();

//实例对象的__proto__属性可以方便的访问到原型对象
p.__proto__;

//既然使用构造函数的`prototype`和实例对象的`__proto__`属性都可以访问原型对象
//就有如下结论
p.__proto__ === Person.prototype;
```
 **`如图所示：`** 

![][11]
 **`3、__proto__属性的用途`** 


* 可以用来访问原型；
* 在实际开发中除非有特殊的需求，不要轻易的使用实例对象的`__proto__`属性去修改原型的属性或方法；
* 在调试过程中，可以轻易的查看原型的成员；
* 由于兼容性问题，不推荐使用。


### 3.5 constuctor属性

`constructor`：构造函数，原型的`constructor`属性指向的是和原型关联的构造函数。 **`示例代码：`** 

```js
function Dog(){
    this.name="husky";
}

var d=new Dog();

// 获取构造函数
console.log(Dog.prototype.constructor);  // 打印构造函数 Dog
console.log(d.__proto__.constructor);    // 打印构造函数 Dog
```
 **`如图所示：`** 

![][12]
 **`获取复杂类型的数据类型：`** 

通过`obj.constructor.name`的方式，获取当前对象`obj`的数据类型。 在一个的函数中，有个返回值`name`，它表示的是当前函数的函数名； 

```js
function Teacher(name,age){
    this.name = name;
    this.age = age;
}

var teacher = new Teacher();

// 假使我们只知道一个对象teacher，如何获取它的类型呢？
console.log(teacher.__proto__.constructor.name);  // Teacher

console.log(teacher.constructor.name);  // Teacher
```
 实例化出来的`teacher`对象，它的数据类型是啥呢？我们可以通过实例对象`teacher.__proto__`，访问到它的原型对象，再通过`.constructor`访问它的构造函数，通过`.name`获取当前函数的函数名，所以就能得到当前对象的数据类型。又因为`.__proto__`是一个非标准的属性，而且实例出的对象继承原型对象的方法，所以直接可以写成：`obj.constructor.name`。 
### 3.6 原型继承

`原型继承`：每一个构造函数都有`prototype`原型属性，通过构造函数创建出来的对象都继承自该原型属性。所以可以通过更改构造函数的原型属性来实现继承。 继承的方式有多种，可以一个对象继承另一个对象，也可以通过原型继承的方式进行继承。 
 **`1、简单混入继承`** 

直接遍历一个对象，将所有的属性和方法加到另一对象上。
```js
var animal = {
    name:"Animal",
    sex:"male",
    age:5,
    bark:function(){
        console.log("Animal bark");
    }
};

var dog = {};

for (var k in animal){
    dog[k]= animal[k];
}

console.log(dog);  // 打印的对象与animal一模一样
```
 缺点：只能一个对象继承自另一个对象，代码复用太低了。 
 **`2、混入式原型继承`** 

混入式原型继承其实与上面的方法类似，只不过是将遍历的对象添加到构造函数的原型上。
```js
var obj={
     name:'zs',
     age:19,
     sex:'male'
 }

function Person(){
    this.weight=50;
}

for(var k in obj){
    // 将obj里面的所有属性添加到 构造函数 Person 的原型中
    Person.prototype[k] = obj[k];
}

var p1=new Person();
var p2=new Person();
var p3=new Person();

console.log(p1.name);  // 'zs'
console.log(p2.age);   // 19
console.log(p3.sex);   // 'male'

```
 **` 面向对象思想封装一个原型继承 `** 

我们可以利用面向对象的思想，将面向过程进行封装。
```js
function Dog(){
    this.type = 'yellow Dog';
}

// 给构造函数 Dog 添加一个方法 extend
Dog.prototype.extend = function(obj){
    // 使用混入式原型继承，给 Dog 构造函数的原型继承 obj 的属性和方法
     for (var k in obj){
        this[k]=obj[k];
    }
}

// 调用 extend 方法
Dog.prototype.extend({
    name:"二哈",
    age:"1.5",
    sex:"公",
    bark:function(){
        console.log('汪汪汪');
    }
});
```
 **`3、替换式原型继承`** 

替换式原型继承，在上面已经举过例子了，其实就是将一个构造函数的原型对象替换成另一个对象。
```js
function Person(){
    this.weight=50;
}

var obj={
    name:'zs',
    age:19,
    sex:'male'
}
// 将一个构造函数的原型对象替换成另一个对象
Person.prototype = obj;

var p1=new Person();
var p2=new Person();
var p3=new Person();

console.log(p1.name);  // 'zs'
console.log(p2.age);   // 19
console.log(p3.sex);   // 'male'
```
 之前我们就说过，这样做会产生一个问题，就是替换的对象会重新开辟一个新的空间。 
 **` 替换式原型继承时的bug `** 

替换原型对象的方式会导致原型的`constructor`的丢失，`constructor`属性是默认原型对象指向构造函数的，就算是替换了默认原型对象，这个属性依旧是默认原型对象指向构造函数的，所以新的原型对象是没有这个属性的。![][13]

解决方法：手动关联一个`constructor`属性

```js
function Person() {
    this.weight = 50;
}

var obj = {
    name: 'zs',
    age: 19,
    sex: 'male'
}
// 在替换原型对象函数之前 给需要替换的对象添加一个 constructor 属性 指向原本的构造函数
obj.constructor = Person;

// 将一个构造函数的原型对象替换成另一个对象
Person.prototype = obj;

var p1 = new Person();

console.log(p1.__proto__.constructor === Person);  // true
```
 **`4、Object.create()方法实现原型继承`** 

当我们想把`对象1`作为`对象2`的原型的时候，就可以实现`对象2`继承`对象1`。前面我们了解了一个属性：`__proto__`，实例出来的对象可以通过这个属性访问到它的原型，但是这个属性只适合开发调试时使用，并不能直接去替换原型对象。所以这里介绍一个新的方法：`Object.create()`。 **`语法：`** `var obj1 = Object.create(原型对象);` **`示例代码：`**  让空对象`obj1`继承对象`obj`的属性和方法

```js
var obj = {
    name : '盖伦',
    age : 25,
    skill : function(){
        console.log('大宝剑');
    }
}

// 这个方法会帮我们创建一个原型是 obj 的对象
var obj1 = Object.create(obj);

console.log(obj1.name);     // "盖伦"
obj1.skill();               // "大宝剑"
```
 **`兼容性：`** 

由于这个属性是`ECMAScript5`的时候提出来的，所以存在兼容性问题。利用浏览器的`能力检测`，如果存在`Object.create`则使用，如果不存在的话，就创建构造函数来实现原型继承。

```js
// 封装一个能力检测函数
function create(obj){
    // 判断，如果浏览器有 Object.create 方法的时候
    if(Object.create){
        return Object.create(obj);
    }else{
        // 创建构造函数 Fun
        function Fun(){};
        Fun.prototype = obj; 
        return new Fun();
    }
}

var hero = {
    name: '盖伦',
    age: 25,
    skill: function () {
        console.log('大宝剑');
    }
}

var hero1 = create(hero);
console.log(hero1.name);    // "盖伦"
console.log(hero1.__proto__ == hero);   // true
```
## 4.原型链

对象有原型，原型本身又是一个对象，所以原型也有原型，这样就会形成一个链式结构的原型链。### 4.1 什么是原型链
 **`示例代码：`**  原型继承练习

```js
// 创建一个 Animal 构造函数
function Animal() {
    this.weight = 50;
    this.eat = function() {
        console.log('蜂蜜蜂蜜');
    }
}

// 实例化一个 animal 对象
var animal = new Animal();

// 创建一个 Preson 构造函数
function Person() {
    this.name = 'zs';
    this.tool = function() {
        console.log('菜刀');
    }
}

// 让 Person 继承 animal （替换原型对象）
Person.prototype = animal;

// 实例化一个 p 对象 
var p = new Person();

// 创建一个 Student 构造函数
function Student() {
    this.score = 100;
    this.clickCode = function() {
        console.log('啪啪啪');
    }
}

// 让 Student 继承 p （替换原型对象）
Student.prototype = p;

//实例化一个 student 对象
var student = new Student();


console.log(student);           // 打印 {score:100,clickCode:fn}

// 因为是一级级继承下来的 所以最上层的 Animate 里的属性也是被继承的
console.log(student.weight);    // 50
student.eat();         // 蜂蜜蜂蜜
student.tool();        // 菜刀
```
 **`如图所示：`** 

我们将上面的案例通过画图的方式展现出来后就一目了然了，实例对象`animal`直接替换了构造函数`Person`的原型，以此类推，这样就会形成一个链式结构的原型链。![][14]
 **`完整的原型链`** 

结合上图，我们发现，最初的构造函数`Animal`创建的同时，会创建出一个原型，此时的原型是一个空的对象。结合原型链的概念：“原型本身又是一个对象，所以原型也有原型”，那么这个空对象往上还能找出它的原型或者构造函数吗？ 我们如何创建一个空对象？ 1、字面量：`{}`；2、构造函数：`new Object()`。我们可以简单的理解为，这个空的对象就是，构造函数`Object`的实例对象。所以，这个空对象往上面找是能找到它的原型和构造函数的。 

```js
// 创建一个 Animal 构造函数
function Animal() {
    this.weight = 50;
    this.eat = function() {
        console.log('蜂蜜蜂蜜');
    }
}

// 实例化一个 animal 对象
var animal = new Animal();

console.log(animal.__proto__);      // {}
console.log(animal.__proto__.__proto__);  // {}
console.log(animal.__proto__.__proto__.constructor);  // function Object(){}
console.log(animal.__proto__.__proto__.__proto__);  // null
```
 **`如图所示：`** 

![][15]
### 4.2 原型链的拓展
 **`1、描述出数组“[]”的原型链结构`** 

```js
// 创建一个数组
var arr = new Array();

// 我们可以看到这个数组是构造函数 Array 的实例对象，所以他的原型应该是：
console.log(Array.prototype);   // 打印出来还是一个空数组

// 我们可以继续往上找 
console.log(Array.prototype.__proto__);  // 空对象

// 继续
console.log(Array.prototype.__proto__.__proto__)  // null

```
 **`如图所示：`** 

![][16]
 **`2、扩展内置对象`** 

给`js`原有的内置对象，添加新的功能。 注意：这里不能直接给内置对象的原型添加方法，因为在开发的时候，大家都会使用到这些内置对象，假如大家都是给内置对象的原型添加方法，就会出现问题。 

错误的做法：

```js
// 第一个开发人员给 Array 原型添加了一个 say 方法
Array.prototype.say = function(){
    console.log('哈哈哈');
}

// 第二个开发人员也给 Array 原型添加了一个 say 方法
Array.prototype.say = function(){
    console.log('啪啪啪');
}

var arr = new Array();

arr.say();  // 打印 “啪啪啪”  前面写的会被覆盖
```

为了避免出现这样的问题，只需自己定义一个构造函数，并且让这个构造函数继承数组的方法即可，再去添加新的方法。

```js
// 创建一个数组对象 这个数组对象继承了所有数组中的方法
var arr = new Array();

// 创建一个属于自己的构造函数
function MyArray(){}

// 只需要将自己创建的构造函数的原型替换成 数组对象，就能继承数组的所有方法
MyArray.prototype = arr;

// 现在可以单独的给自己创建的构造函数的原型添加自己的方法
MyArray.prototype.say = function(){
    console.log('这是我自己添加的say方法');
}

var arr1 = new MyArray();

arr1.push(1);   // 创建的 arr1 对象可以使用数组的方法
arr1.say();     // 也可以使用自己添加的方法  打印“这是我自己添加的say方法”
console.log(arr1);  // [1]
```
### 4.3 属性的搜索原则

当通过`对象名.属性名`获取属性时，会遵循以下属性搜索的原则：

* 1-首先去对象自身属性中找，如果找到直接使用，
* 2-如果没找到，去自己的原型中找，如果找到直接使用，
* 3-如果没找到，去原型的原型中继续找，找到直接使用，
* 4-如果没有会沿着原型不断向上查找，直到找到`null`为止。


## 5.Object.prototype成员介绍

我们可以看到所有的原型最终都会继承`Object`的原型：`Object.prototype`。打印看看`Object`的原型里面有什么：

```js
// Object的原型
console.log(Object.prototype)
```

如图所示：

![][17]
 我们可以看到`Object`的原型里有很多方法，下面就来介绍下这些方法的作用。 
### 5.1 constructor 属性

指向了和原型相关的构造函数### 5.2 hasOwnProperty 方法

判断对象自身是否拥有某个属性，返回值：`布尔类型`。 **`示例代码：`** 

```js
function Hero() {
    this.name = '盖伦';
    this.age = '25';
    this.skill = function () {
        console.log('盖伦使用了大宝剑');
    }
}

var hero = new Hero();
console.log(hero.name); // '盖伦'
hero.skill();           // '盖伦使用了大宝剑'

console.log(hero.hasOwnProperty("name"));       // true
console.log(hero.hasOwnProperty("age"));        // true
console.log(hero.hasOwnProperty("skill"));      // true
console.log(hero.hasOwnProperty("toString"));   // false toString是在原型链当中的方法，并不是这里对象的方法

console.log('toString' in hero); // true in方法 判断对象自身或者原型链中是否有某个属性
```
### 5.3 isPrototypeOf 方法

`对象1.isPrototypeOf(对象2)`，判断`对象1`是否是`对象2`的原型，或者`对象1`是否是`对象2`原型链上的原型。 **`示例代码：`** 

```js
var obj = {
    age: 18
}
var obj1 = {};

// 创建一个构造函数
function Hero() {
    this.name = '盖伦';
}

// 将这个构造函数的原型替换成 obj
Hero.prototype = obj;

// 实例化一个 hero 对象
var hero = new Hero();

console.log(obj.isPrototypeOf(hero));   // true  判断 obj 是否是 hero 的原型
console.log(obj1.isPrototypeOf(hero));  // false  判断 obj1 是否是 hero 的原型
console.log(Object.prototype.isPrototypeOf(hero));  // true  判断 Object.prototype 是否是 hero 的原型
// 注意 这里的 Object.prototype 是原型链上最上层的原型对象
```
### 5.4 propertyIsEnumerable 方法

`对象.propertyIsEnumerable('属性或方法名')`，判断一个对象是否有该属性，并且这个属性可以被`for-in`遍历，返回值：`布尔类型`。 **`示例代码：`** 

```js
// 创建一个构造函数
function Hero (){
    this.name = '盖伦';
    this.age = 25;
    this.skill = function(){
        console.log('盖伦使用了大宝剑');
    }
}

// 创建一个对象
var hero = new Hero();

// for-in 遍历这个对象 我们可以看到分别打印了哪些属性和方法
for(var k in hero){
    console.log(k + '—' + hero[k]); // "name-盖伦" "age-25" "skill-fn()"
}

// 判断一个对象是否有该属性，并且这个属性可以被 for-in 遍历
console.log(hero.propertyIsEnumerable('name'));     // true
console.log(hero.propertyIsEnumerable('age'));      // true
console.log(hero.propertyIsEnumerable('test'));     // false
```
### 5.5 toString 和 toLocalString 方法

两种方法都是将对象转成字符串的，只不过`toLocalString`是按照本地格式进行转换。 **`示例代码：`** 

```js
// 举个例子，时间的格式可以分为世界时间的格式和电脑本地的时间格式
var date = new Date();

// 直接将创建的时间对象转换成字符串
console.log(date.toString());

// 将创建的时间对象按照本地格式进行转换
console.log(date.toLocaleString());
```
 **`效果图：`** 

![][18]
### 5.6 valueOf 方法

返回指定对象的原始值。[MDN官方文档][31]
## 6.静态方法和实例方法

静态方法和实例方法这两个概念其实也是从面相对象的编程语言中引入的，对应到`JavaScript`中的理解为： **`静态方法：`**  由构造函数调用的

在`js`中，我们知道有个`Math`构造函数，他有一个`Math.abs()`的方法，这个方法由构造函数调用，所以就是静态方法。
```js
Math.abs();
```
 **`实例方法：`**  由构造函数创建出来的对象调用的

```js
var arr = new Array();

// 由构造函数 Array 实例化出来的对象 arr 调用的 push 方法，叫做实例方法
arr.push(1);
```
 **`示例代码：`** 

```js
function Hero(){
    this.name='亚索';
    this.say=function(){
        console.log('哈撒ki');
    }
}
Hero.prototype.skill=function(){
    console.log('吹风');
}

// 直接给构造函数添加一个 run 方法（函数也是对象，可以直接给它加个方法）
Hero.run=function(){
    console.log('死亡如风,常伴吾身');
}

var hero = new Hero();

hero.say();
hero.skill();   //实例方法

Hero.run();     //静态方法
```
 如果这个方法是对象所有的，用实例方法。一般的工具函数，用静态方法，直接给构造函数添加方法，不需要实例化，通过构造函数名直接使用即可； 
## 7.作用域

“域”，表示的是一个范围，“作用域”就是作用范围。作用域说明的是一个变量可以在什么地方被使用，什么地方不能被使用。### 7.1 块级作用域

在`ES5`及`ES5`之前，`js`中是没有块级作用域的。
```js
{
    var num = 123;
    {
        console.log( num ); // 123
    }
}
console.log( num ); // 123
```

上面这段代码在`JavaScript`中是不会报错的，但是在其他的编程语言中`（C#、C、JAVA）`会报错。这是因为，在`JavaScript`中没有块级作用域，使用`{}`标记出来的代码块中声明的变量`num`，是可以被`{}`外面访问到的。但是在其他的编程语言中，有块级作用域，那么`{}`中声明的变量`num`，是不能在代码块外部访问的，所以报错。
 注意：块级作用域只在在`ES5`及`ES5`之前不起作用，但是在`ES6`开始，`js`中是存在块级作用域的。 
### 7.2 词法作用域

词法( 代码 )作用域，就是代码在编写过程中体现出来的作用范围。代码一旦写好，不用执行，作用范围就已经确定好了，这个就是所谓词法作用域。 **`在`js`中词法作用域规则:`** 


* 函数允许访问函数外的数据；
* 整个代码结构中只有函数可以限定作用域；
* 作用域规则首先使用提升规则分析；
* 如果当前作用规则中有名字了，就不考虑外面的名字。

 **`作用域练习：`** 

第一题

```js
var num=250;

function test(){
    // 会现在函数内部查找有没有这个num变量，有的话调用，没有的话会去全局中查找，有就返回，没有就返回undefined
    console.log(num);  // 打印 250
}

function test1(){
   var num=222;
   test();
}

test1();  
```

第二题

```js
if(false){
    var num = 123;
}

console.log(num); // undefined 
// {}是没有作用域的 但是有判断条件，var num会提升到判断语句外部 所以不会报错 打印的是undefined
```

第三题

```js
var num = 123;
function foo() {
    var num = 456;
    function func() {
        console.log( num );
    }
    func();
}
foo();  // 456
// 调用foo时，在函数内部调用了func，打印num的时候，会先在func中查找num  没有的时候会去外层作用域找，找到即返回，找不到即再往上找。
```

第四题

```js
var num1 = 123;
function foo1() {
   var num1 = 456;
   function foo2() {
       num1 = 789;
       function foo3 () {
           console.log( num1 );  // 789  自己的函数作用域中没有就一层层往上找
       }
       foo3();
   }
   foo2();
}
foo1();
console.log( num1 ); // 123 
```
### 7.3 变量提升（预解析）

`JavaScript`是解释型的语言，但是它并不是真的在运行的时候逐句的往下解析执行。我们来看下面这个例子：

```js
func();

function func(){
    alert("函数被调用了");
}
```

在上面这段代码中，函数`func`的调用是在其声明之前，如果说`JavaScript`代码真的是逐句的解析执行，那么在第一句调用的时候就会出错，然而事实并非如此，上面的代码可以正常执行，并且`alert`出来"函数被调用了"。
 所以，可以得出结论，`JavaScript`并非仅在运行时简简单单的逐句解析执行！ 
 **`JavaScript预解析`** 

`JavaScript`引擎在对`JavaScript`代码进行解释执行之前，会对`JavaScript`代码进行预解析，在预解析阶段，会将以关键字`var`和`function`开头的语句块提前进行处理。 关键问题是怎么处理呢？ 

* 当变量和函数的声明处在作用域比较靠后的位置的时候，变量和函数的声明会被提升到当前作用域的开头。
 **`示例代码：函数名提升`** 

* 正常函数书写方式

```js
function func(){
    alert("函数被调用了");
}
func();
```

* 预解析之后，函数名提升

```js
func();
function func(){
    alert("函数被调用了");
}
```
 **`示例代码：变量名提升`** 

* 正常变量书写方式

```js
alert(a);  // undefined  
var a = 123;
// 由于JavaScript的预解析机制，上面这段代码，alert出来的值是undefined，
// 如果没有预解析，代码应该会直接报错a is not defined，而不是输出值。
```

* 不是说要提前的吗？那不是应该`alert`出来`123`，为什么是`undefined`?

```js
// 变量的时候 提升的只是变量声明的提升，并不包括赋值
var a;      // 这里是声明
alert(a);   // 变量声明之后并未有初始化和赋值操作，所以这里是 undefined
a = 123;    // 这里是赋值
```
 **`注意：特殊情况`** 

1、函数不能被提升的情况

* 函数表达式创建的函数不会提升

```js
test();   // 报错 "test is not a function"
var test = function(){
    console.log(123);
}
```

* `new Function`创建的函数也不会被提升

```js
test();   // 报错 "test is not a function"
var test = new Function(){
    console.log(123);
}
```

2、出现同名函数

```js
test();  // 打印 '好走的都是下坡路'

// 两个函数重名，这两个函数都会被提升，但是后面的函数会覆盖掉前面的函数
function test(){
   console.log('众里寻她千百度，他正在自助烤肉....');
}

function test(){
   console.log('好走的都是下坡路');
}
```

3、函数名与变量名同名

```js
// 如果函数和变量重名，只会提升函数，变量不会被提升
console.log(test);  // 打印这个test函数

function test(){
   console.log('我是test');
}
var test=200;
```

再看一种情况：

```js
var num = 1;
function num () {
    console.log(num); // 报错 “num is not a function”
}
num();
```

直接上预解析后的代码：

```js
function num(){
    console.log(num);
}

num = 1;
num();
```

4、条件式的函数声明

```js
// 如果是条件式的函数申明， 这个函数不会被预解析
test();  // test is not a function
if(true){
    function test(){
        console.log('只是在人群中多看了我一眼，再也忘不掉我容颜...');
    }
}
```
 **`预解析是分作用域的`** 

声明提升并不是将所有的声明都提升到`window`对象下面，提升原则是提升到变量运行的当前作用域中去。示例代码：

```js
function showMsg(){
    var msg = 'This is message';
}
alert(msg); // 报错“Uncaught ReferenceError: msg is not defined”
```

预解析之后：

```js
function showMsg(){
    var msg;    // 因为函数本身就会产生一个作用域，所以变量声明在提升的时候，只会提升在当前作用域下最前面
    msg = 'This is message';
}
alert(msg); // 报错“Uncaught ReferenceError: msg is not defined”
```
 **`预解析是分段的`** 

分段，其实就分`script`标签的
```js
<script>
func(); // 输出 AA2;
function func(){
    console.log('AA1');
}

function func(){
    console.log('AA2');
}
</script>

<script>
function func(){
    console.log('AA3');
}
</script>
```

在上面代码中，第一个`script`标签中的两个`func`进行了提升，第二个`func`覆盖了第一个`func`，但是第二个`script`标签中的`func`并没有覆盖上面的第二个`func`。所以说预解析是分段的。
 **`tip:`**  但是要注意，分段只是单纯的针对函数，变量并不会分段预解析。

函数预解析的时候是分段的，但是执行的时候不分段

```js
<script>
    //变量预解析是分段的 ，但是函数的执行是不分段
    var num1=100;

    // test3();  报错，函数预解析的时候分段，执行的时候才不分段
    function test1(){
        console.log('我是test1');
    }

    function test2(){
        console.log('我是test2');
    }
</script>

<script>
    var num2=200;
    function test3(){
        console.log('test3');
    }

    test1();   // 打印 '我是test1' 函数执行的时候不分段
    console.log(num1); // 100
</script>
```
### 7.4 作用域链
 **`什么是作用域链？`** 

只有函数可以制造作用域结构，那么只要是代码，就至少有一个作用域, 即全局作用域。 凡是代码中有函数，那么这个函数就构成另一个作用域。如果函数中还有函数，那么在这个作用域中就又可以诞生一个作用域。将这样的所有的作用域列出来，可以有一个结构: 函数内指向函数外的链式结构。就称作作用域链。 
 **`例如：`** 

```js
function f1() {
    function f2() {
    }
}

var num = 456;
function f3() {
    function f4() {    
    }
}
```
 **`示例代码：`** 

```js
var num=200;
function test(){
    var num=100;
    function test1(){
        var num=50;
        function test2(){
            console.log(num);
        }
        test2();
    }
    test1();
}

test();   // 打印 “50”
```
 **`如图所示：`** 

![][19]
 **`绘制作用域链的步骤：`** 


* 看整个全局是一条链, 即顶级链, 记为`0`级链
* 看全局作用域中, 有什么变量和函数声明, 就以方格的形式绘制到`0`级练上
* 再找函数, 只有函数可以限制作用域, 因此从函数中引入新链, 标记为`1`级链
* 然后在每一个`1`级链中再次往复刚才的行为

 **`变量的访问规则：`** 


* 首先看变量在第几条链上, 在该链上看是否有变量的定义与赋值, 如果有直接使用
* 如果没有到上一级链上找`( n - 1 级链 )`, 如果有直接用, 停止继续查找.
* 如果还没有再次往上刚找... 直到全局链(`0`级 ), 还没有就是`is not defined`
* 注意,同级的链不可混合查找

 **`来点案例练练手`** 

第一题:

```js
function foo() {
    var num = 123;
    console.log(num); //123
}
foo();
console.log(num); // 报错
```

第二题:

```js
var scope = "global";
function foo() {
    console.log(scope); //  undefined
    var scope = "local";
    console.log(scope); // 'local'
}
foo();

// 预解析之后
// var scope = "global";
// function foo() {
//   var scope;
//   console.log(scope); // undefined
//   scope = "local";
//   console.log(scope); // local
// }
```

第三题:

```js
if("a" in window){
   var a = 10;
}
console.log(a); // 10

// 预解析之后
// var a;
// if("a" in window){
//    a = 10;        // 判断语句不产生作用域
// }
// console.log(a); // 10
```

第四题:

```js
if(!"a" in window){
   var a = 10;
}
console.log(a); // undefined

// 预解析之后
// var a;
// if(!"a" in window){
//    a = 10;        // 判断语句不产生作用域
// }
// console.log(a); // undefined
```

第五题

```js
// console.log(num); 报错 虽然num是全局变量 但是不会提升
function test(){
   num = 100;  
}

test();

console.log(num);   // 100
```

第六题

```js
var foo = 1;
function bar() {
   if(!foo) {
       var foo = 10;
   }
   console.log(foo); // 10
}
bar();

// 预解析之后
// var foo=1;
// function bar(){
//    var foo;
//    if(!foo){
//        foo=10;
//    }
//    console.log(foo); // 10
// }
// bar();
```
## 8.Function

`Function`是函数的构造函数，你可能会有点蒙圈，没错，在`js`中函数与普通的对象一样，也是一个对象类型，只不过函数是`js`中的“一等公民”。 这里的`Function`类似于`Array`、`Object`等 
### 8.1 创建函数的几种方式
 **`1、函数字面量（直接声明函数）创建方式`** 

```js
function test(){   
    // 函数体
}   // 类似于对象字面量创建方式：{}
```
 **`2、函数表达式`** 

```js
var test = function(){
    // 函数体
}
```
 **`3、Function构造函数创建`** 

```js
// 构造函数创建一个空的函数
var fn = new Function();
fn1();  // 调用函数
```
 **` 函数扩展名 `** 

有没有一种可能，函数表达式声明函数时，`function`也跟着一个函数名，如：`var fn = function fn1(){}`？ 答案是可以的，不过`fn1`只能在函数内部使用，并不能在外部调用。
```js
var fn = function fn1(a,b,c,d){
    console.log('当前函数被调用了');
    // 但是，fn1可以在函数的内部使用
    console.log(fn1.name);
    console.log(fn1.length);
    // fn1();  注意，这样调用会引起递归！！！  下面我们会讲到什么是递归。
}
// fn1();   // 报错，fn1是不能在函数外部调用的
fn();   // "当前函数被调用了"

// 函数内部使用时打印：
// "当前函数被调用了"
// console.log(fn1.name); => "fn1"
// console.log(fn1.length); => 4
```
### 8.2 Function 构造函数创建函数

上面我们知道了如何通过`Function`构造函数创建一个空的函数，这里我们对它的传参详细的说明下。 **`1、不传参数时`** 

```js
// 不传参数时，创建的是一个空的函数
var fn1 = new Function();
fn1();  // 调用函数
```
 **`2、只传一个参数`** 

```js
// 只传一个参数的时候，这个参数就是函数体
// 语法：var fn = new Function(函数体);
var fn2 = new Function('console.log(2+5)');
f2();   // 7
```
 **`3、传多个参数`** 

```js
// 传多个参数的时候，最后一个参数为函数体，前面的参数都是函数的形参名
// 语法：var fn = new Function(arg1,arg2,arg3.....argn,metthodBody);
var fn3 = new Function('num1','num2','console.log(num1+num2)');
f3(5,2);   // 7
```
### 8.3 Function 的使用
 **`1、用`Function`创建函数的方式封装一个计算`m - n`之间所有数字的和的函数`** 

```js
//求 m-n之间所有数字的和
//var sum=0;
//for (var i = m; i <=n; i++) {
//  sum+=i;
//}
var fn = new Function('m','n','var sum=0;for (var i = m; i <=n; i++) {sum+=i;} console.log(sum);');
fn(1,100);  // 5050
```
 **`函数体参数过长问题：`** 

函数体过长时，可读性很差，所以介绍解决方法：1）字符串拼接符“`+`”

```js
var fn = new Function(
    'm',
    'n',
    'var sum=0;'+
    'for (var i = m; i <=n; i++) {'+
        'sum += i;'+
    '}'+
    'console.log(sum);'
    );
fn(1,100);  // 5050
```

2）`ES6`中新语法“ ` ”，(在`esc`键下面)

表示可换行字符串的界定符，之前我们用的是单引号或者双引号来表示一个字符串字面量，在`ES6`中可以用反引号来表示该字符串可换行。
```js
new Function(
    'm',
    'n',
    `var sum=0;
    for (var i = m; i <=n; i++) {
        sum+=i;
    }
    console.log(sum);`
);
```

3）模板方式

```html
<!-- 新建一个模板 -->
<script type="text/template" id="tmp">
    var sum=0;
    for (var i = m; i <=n; i++) {
        sum += i;
    }
    console.log(sum);
</script>

<script>
    // 获取模板内的内容
    var methodBody = document.querySelector('#tmp').innerHTML;
    console.log(methodBody);
    var fn = new Function('m','n',methodBody);
    
    fn(2,6);  // 20
</script>
```
 **`2、eval 函数`** 

`eval`函数可以直接将把字符串的内容，作为`js`代码执行，前提是字符串代码符合`js`代码规范。这里主要是用作跟`Function`传参比较。 **``eval`和`Function`的区别：`** 


* `Function();`中，方法体是字符串，必须调用这个函数才能执行
* `eval();`可以直接执行字符串中的`js`代码

 **`存在的问题：`** 

* 性能问题

因为`eval`里面的代码是直接执行的，所以当在里面定义一个变量的时候，这个变量是不会预解析的，所以会影响性能。
```js
// eval 里面的代码可以直接执行，所以下面的打印的 num 可以访问到它
// 但是这里定义的 num 是没有预解析的，所以变量名不会提升，从而性能可能会变慢
eval('var num = 123;');
console.log(num);   // 123
```

* 安全问题

主要的安全问题是可能会被利用做`XSS`攻击（跨站脚本攻击(`Cross Site Scripting`)），`eval`也存在一个安全问题，因为它可以执行传给它的任何字符串，所以永远不要传入字符串或者来历不明和不受信任源的参数。 **`示例代码：`**  实现一个简单的计算器

```html
<!-- html 部分 -->
<input type="text" class="num1">
<select class="operator">
    <option value="+">+</option>
    <option value="-">-</option>
    <option value="*">*</option>
    <option value="/">/</option>
</select>
<input type="text" class="num2">
<button>=</button>
<input type="text" class="result">

<!-- js 部分 -->
<script>
    document.querySelector('button').onclick=function(){
        var num1 = document.querySelector('.num1').value;
        var num2 = document.querySelector('.num2').value;
        var operator = document.querySelector('.operator').value;
        
        // result其实最终获得的就是 num1 + operator + num2的字符串  但是他能够直接执行并计算
        var result = eval(num1 + operator + num2);          //计算
        document.querySelector('.result').value = result;   //显示
    }
</script>
```
 **`效果图：`** 

![][20]
### 8.4 Function 的原型链结构

在`7.2`章节中我们知道函数也还可以通过构造函数的方式创建出来，既然可以通过构造函数的方式创建，那么函数本身也是有原型对象的。 **`示例代码：`** 

```js
// 通过Function构造函数创建一个函数test
var test = new Function();
// 既然是通过构造函数创建的，那么这个函数就有指向的原型
console.log(test.__proto__);  // 打印出来的原型是一个空的函数
console.log(test.__proto__.__proto__);  // 空的函数再往上找原型是一个空的对象
console.log(test.__proto__.__proto__.__proto__);    // 再往上找就是null了

// 函数原型链： test() ---> Function.prototype ---> Object.prototype ---> null
```
 **`如图所示：`** 

![][21]
 通过上图，可以直观的看出，函数也是有原型的。那一个完整的原型链究竟是什么样子的呢？下面我们一起做个总结。 
### 8.5 完整的原型链
 **`绘制完整原型链的步骤：`** 


* 1、先将一个对象的原型画出来
* 2、再把对象的原型的原型链画出来 ，到`null`结束
* 3、把对象的构造函数的原型链画出来
* 4、把`Function`和`Object`的原型关系给画出来

 **`示例代码：`** 

```js
// 创建一个构造函数
function Person(){
    this.name = 'Levi';
    this.age = 18;
}

// 实例化一个对象
var p = new Person();
```
 **`如图所示：`** 

![][22]
 **`总结：`** 


* `Function`构造函数的原型，在`Object`的原型链上；
* `Object`构造函数的原型，在`Function`的原型链上；


## 9.arguments对象

在每一个函数调用的过程中, 函数代码体内有一个默认的对象`arguments`, 它存储着实际传入的所有参数。 **`示例代码：`** 

```js
// 封装一个加法函数
function add(num1,num2){
    console.log(num1+num2);
}

add(1);     // NaN
add(1,2);   // 3
add(1,2,3); // 3
```
 在调用函数时，实参和形参的个数可以不一样，但是没有意义。 

在函数内部有个`arguments`对象(注意：是在函数内部)，`arguments`是一个伪数组对象。它表示在函数调用的过程中传入的所有参数（实参）的集合。在函数调用过程中不规定参数的个数与类型，可以使得函数调用变得非常灵活性。
```js
function add(num1,num2){
    console.log(arguments); // 打印的是一个伪数组
}
add(1,2,3,4); 
```

![][23]


* `length`：表示的是实参的个数；
* `callee`：指向的就是`arguments`对象所在的函数；

 **`示例代码：`** 

封装一个求最大值的函数，因为不知道需要传进多少实参，所以直接用伪数组`arguments`获取调用的实参
```js
function max(){
    // 假使实参的第一个数字最大
    var maxNum = arguments[0];
    // 循环这个伪数组
    for(var i = 0; i < arguments.length; i++){
        if(maxNUm < arguments[i]){
            maxNUm = arguments[i];
        }
        return maxNum;
    }
    
}

// 调用
console.log(max(1,9,12,8,22,5));   // 22

```
## 10. 函数的四种调用模式

四种调用模式分别是：“函数调用模式”、“方法调用模式”、“构造器调用模式”、“上下文调用模式”。其实就是分析`this`是谁的问题。只看函数是怎么被调用的，而不管函数是怎么来的。


* 分析`this`属于哪个函数；
* 分析这个函数是以什么方式调用的；

 **`什么是函数？ 什么是方法？`** 

如果一个函数是挂载到一个对象中，那么就把这个函数称为方法如果一个函数直接放在全局中，由`Window`对象调用，那么他就是一个函数。

```js
// 函数
function fn() {}
var f = function() {};
fn();
f();

// 方法
var obj = {
  say: function() {}
};
obj.say();
```
 `fn`和`f`都是函数，`say`是一个方法 
### 10.1 函数模式

函数模式其实就是函数调用模式，`this`是指向全局对象`window`的。
```js
this -> window
```
 **`示例代码：`** 

```js
// 函数调用模式：
// 创建的全局变量相当于window的属性
var num = 999;
var fn = function () {
  console.log(this);  // this 指向的是 window 对象
  console.log(this.num); // 999
};
fn();
```
### 10.2 方法模式

方法模式其实就是方法调用模式，`this`是指向调用方法的对象。
```js
this -> 调用方法的对象
```
 **`示例代码：`** 

```js
// this指向的是obj 
var age = 38;
var obj = {
  age: 18,
  getAge: function () {
    console.log(this);  // this指向的是对象obj  {age:18,getAge:f()}
    console.log(this.age);  // 18
  } 
};
obj.getAge(); // getAge() 是对象 obj 的一个方法
```
### 10.3 构造器模式

构造器模式其实就是构造函数调用模式，`this`指向新创建出来的实例对象。
```js
this -> 新创建出来的实例对象
```
 **`示例代码：`** 

```js
// this指向的是实例化出来的对象
function Person(name){
    this.name = name;
    console.log(this);
}
var p1 = new Person('Levi'); // Person {name: "Levi"}
var p2 = new Person('Ryan'); // Person {name: "Ryan"}
```
 **`构造函数的返回值：`** 

如果返回的是基本类型
```js
function Person() {
    return 1;
}
var p1 = new Person();
console.log(p1);  // 打印Person {}
```
 构造函数内有返回值，且是基本类型的时候，返回值会被忽略掉，返回的是实例出来的对象。 

如果返回的是引用类型
```js
function Person() {
  return {
    name: 'levi',
    age: 18
  };
}
var p1 = new Person();
console.log(p1); // 此时打印 Object {name: 'levi', age: 18}
```
 构造函数内的返回值是一个引用类型的时候，返回的就是这个指定的引用类型。 
### 10.4 上下文（借用方法）模式

上下文，即环境，用于指定方法内部的`this`，上下文调用模式中，`this`可以被随意指定为任意对象。上下文模式有两种方法，是由函数调用的：


* `函数名.apply( ... )`;
* `函数名.call( ... )`;

 **`1、apply 方法`** 

语法：

```js
fn.apply(thisArg, array);
```

参数：

```js
第一个参数：表示函数内部this的指向（或者：让哪个对象来借用这个方法）
第二个参数：是一个数组（或者伪数组），数组中的每一项都将作为被调用方法的参数
```

示例代码：

```js
// 没有参数
function fn (){
    console.log(this.name);
}

var obj = {
    name : 'Levi丶'
}

// this 指向 obj，fn 借用obj方法里面的 name 属性
fn.apply(obj);  // 打印 'Levi丶'
```

```js
// 有参数
function fn (num1, num2){
    console.log(num1 + num2);
}

var obj = {}

// this 指向 obj，数组中的数据是方法 fn 的参数
fn.apply(obj, [1 , 2]);  // 打印 3
```
 注意：`apply`方法的第一个参数，必须是一个对象！如果传入的参数不是一个对象，那么这个方法内部会将其转化为一个包装对象。 

```js
function fn() {
  console.log(this);
}

fn.apply(1); // 包装对象
fn.apply('abc'); // 包装对象
fn.apply(true); // 包装对象
```

![][24]

指向`window`的几种方式：

```js
function fn(){
    
}

fn.apply(window);
fn.apply();
fn.apply(null);
fn.apply(undefined);
```

具体应用：

* 求数组中的最大数

```js
// 以前的方法，假设第一项最大，然后与后面每一项比较，得到最大的项
var arr = [1, 3, 6, 10, 210, 23, 33, 777, 456];

var maxNum = arr[0];
for(var i = 1; i < arr.length; i++) {
  if(maxNum < arr[i]) {
    maxNum = arr[i];
  }
}
console.log(maxNum); // 777
```

```js
// 利用 内置对象的 apply 的方法
var arr = [1, 3, 6, 10, 210, 23, 33, 777, 456];

// max 是内置对象 Math 求最大值的一个方法
var maxNum = Math.max.apply(null, arr);
console.log(maxNum); // 777
```

* 将传进的参数每一项之间用“`-`”连接

```js
// 思考：参数个数是用户随机传的，没有具体的一个值，这时候就需要用到 arguments 的概念了
function fn (){
    // 数组原型中有一个join方法，他的接收的参数是一个字符串
    // join.apply的第一个参数指向 arguments 对象，第二个参数是jion方法需要的参数
    return Array.prototype.join.apply(arguments, ['-']);
}

var ret = fn('a', 'b', 'c', 'd', 'e');
console.log(ret); // 'a-b-c-d-e'
```
 **`2、call 方法`** 

`call`方法的作用于`apply`方法的作用相同，唯一不同的地方就是第二个参数不同。语法：

```js
fn.apply(thisArg, parm1,parm2,parm3,...);
```

参数：

```js
第一个参数：表示函数内部this的指向（或者：让哪个对象来借用这个方法）
第二个及后面的参数：不是之前数组的形式了，对应方法调用的每一个参数
```

示例代码：

```js
function fn(num1, num2, num3) {
  console.log(num1, num2, num3);
}

var obj = {};
fn.call(obj, [1, 3, 9], 0, 1); // [1, 3, 9] 0 1
fn.call(obj, [1, 3, 9]); // [1, 3, 9] undefined undefined
```
 **`3、apply 和 call 的区别`** 

两者在功能上一模一样，唯一的区别就是第二个参数传递的类型不一样。什么时候用`apply`？什么时候用`call`呢？

其实用哪个都可以，在参数少的情况下，我们可以使用`call`方法，但是如果参数是伪数组或者是数组的时候，`call`方法就不适用了，还需要将伪数组中的每一项取出来作为方法的参数，此时`apply`更加实用。
### 10.5 面试题分析
 **`面试题1：`** 

```js
var age = 38;
var obj = {
    age: 18,
    getAge: function() {
        function foo() {
            console.log(this.age); // 这里的this属于函数 foo；   打印 38
        }
        foo(); // foo函是Window对象调用的
    }
};
obj.getAge();
```
 **`面试题2：`** 

```js
// 只看函数是怎么被调用的，而不管函数是怎么来的
var age = 38;
var obj = {
    age: 18,
    getAge: function() {
        alert(this.age); 
    }
};

var f = obj.getAge;
f(); // 函数是Window对象调用的，所以this指向Window对象。打印：38
```
 **`面试题3：`** 

```js
var length = 10;
function fn(){
    console.log(this.length);
}
var obj = {
    length: 5,
    method: function (fn) {
        fn();   // window对象调用 打印 10
        arguments[0](); // 方法调用模式，是arguments对象调用的  
        // this指向arguments，所以arguments.length = 2; （arguments.length：实参的个数）所以打印 2
    }
};
obj.method(fn, 123);
```
 **`面试题4：`** 

怎么使用`call`或者`apply`方法实现构造函数的复用呢？
```js
function Person(name, age, gender) {
  this.name = name;
  this.age = age;
  this.gender = gender;
}
function Teacher(name, age, gender, workYear, subject) {
  this.name = name;
  this.age = age;
  this.gender = gender;
  this.workYear = workYear;
  this.subject = subject;
}
function Student(name, age, gender, stuNo, score) {
  this.name = name;
  this.age = age;
  this.gender = gender;
  this.stuNo = stuNo;
  this.score = score;
}

var tec = new Teacher('张老师', 32, 'male', '7年', '语文');
var stu = new Student('xiaowang', 18, 'male', 10001, 99);
console.log(tec); // Teacher {name: "张老师", age: 32, gender: "male", workYear: "7年", subject: "语文"}
console.log(stu); // Student {name: "xiaowang", age: 18, gender: "male", stuNo: 10001, score: 99}
```
 上面的代码中一个`Teacher`构造函数，一个`Student`构造函数，他们都有一些公共的属性，跟`Perso`n构造函数里面的属性重复，我们能否使用`call`或者`apply`方法，简化上面的代码呢？ 

```js
function Person(name, age, gender) {
  this.name = name;
  this.age = age;
  this.gender = gender;
}
function Teacher(name, age, gender, workYear, subject) {
  // 借用 Person 函数来给当前对象添加属性
  Person.call(this, name, age, gender);  // 这里的this指向的就是当前的Teacher构造函数
  this.workYear = workYear;
  this.subject = subject;
}
function Student(name, age, gender, stuNo, score) {
  Person.call(this, name, age, gender);  // 这里的this指向的就是当前的Student构造函数
  this.stuNo = stuNo;
  this.score = score;
}

var tec = new Teacher('张老师', 32, 'male', '7年', '语文');
var stu = new Student('xiaowang', 18, 'male', 10001, 99);
console.log(tec); // Teacher {name: "张老师", age: 32, gender: "male", workYear: "7年", subject: "语文"}
console.log(stu); // Student {name: "xiaowang", age: 18, gender: "male", stuNo: 10001, score: 99}
```
## 11.递归
### 11.1 什么是递归

什么是递归？递归就是函数直接自己调用自己或者间接的调用自己。 **`举个例子：`** 

* 函数直接调用自己

```js
function fn(){
    fn();
}
fn();
```

* 函数间接调用自己

```js
function fn1(){
    fn2();
}


function fn2(){
    fn1();
}
```
 **`递归示例代码：`** 

```js
function fn (){
    console.log('从前有座山，');
    console.log('山里有座庙，');
    console.log('庙里有个老和尚，');
    console.log('老和尚给小和尚讲，');
    fn();
}
fn();  // 产生递归，无限打印上面的内容
```
 这样做会进入到无限的死循环当中。 
### 11.2 化归思想

化归思想是将一个问题由难化易，由繁化简，由复杂化简单的过程称为化归，它是转化和归结的简称。 **`合理使用递归的注意点：`** 


* 函数调用了自身
* 必须有结束递归的条件，这样程序就不会一直运行下去了

 **`示例代码：`**  求前`n`项的和


* 求前`n`项的和其实就是：`1 + 2 + 3 +...+ n`；
* 寻找递推关系，就是`n`与`n-1`, 或`n-2`之间的关系:`sum(n) == n + sum(n - 1)`；
* 加上结束的递归条件，不然会一直运行下去。


```js
function sum(n){
    if(n == 1) return 1;  // 递归结束条件 
    return n + sum(n - 1);
}

sum(100); // 打印 5050
```
 **`递推关系：`** 

![][25]
### 11.3 递归练习
 **`1、求n的阶乘：`** 

思路：


* `f(n) = n * f(n - 1);`
* `f(n - 1) = (n - 1) * f(n - 2);`


示例代码：

```js
function product(n){
    if(n == 1) {
        return 1;
    }
    return n * product(n-1);
}
console.log(product(5));  // 打印 120
```
 **`2、求m的n次幂：`** 

思路：

* `f(m,n) = m * f(m,n-1);`

示例代码：

```js
function pow(m,n){
    if(n==1){
        return m;
    }
    return m * pow(m,n-1);
}

console.log(pow(2, 10));  // 打印 1024
```
 **`3、斐波那契数列`** 

思路：什么是斐波那契数列？
`1 , 1 , 2 , 3 , 5 , 8 , 13 , 21 , 34 , 55,... `数字从第三项开始，每一项都等于前两项的和。可得出公式：`fn = f(n-1) + f(n-2)`，结束递归的条件：当`n <= 2`时，`fn = 1`。示例代码：

```js
function fib(n){
    if(n<=2) return 1;  // 结束递归的条件
    return fib(n-1) + fib(n-2);
}
console.log(fib(5)); // 5
console.log(fib(10)); // 55
console.log(fib(25)); // 75025   // 数值太大会影响性能问题
```

存在问题：

数值太大时会影响性能，怎么影响的呢？
```js
function fib(n){
    if(n<=2) return 1;
    return fib(n-1) + fib(n-2);
    // 当我们在计算一个值的时候，都是通过计算他的fib(n-1) 跟 fib(n-2)项之后再去进行相加，得到最终的值
    // 这时候就需要调用两次这个函数，在计算fib(n-1)的时候，其实也是调用了两次这个函数，得出fib(n-1)的值
}
```

```js
// 记录执行的次数
var count=0;
function  fib(n){
    count++;
    if(n<=2) return 1;
    return fib(n-1)+fib(n-2);
}

console.log(fib(5));  // 5
console.log(count);   // 9  求第五项的时候就计算了9次

//console.log(fib(20));  // 6765
//console.log(count);   // 13529  求第20项的时候就计算了13529次
```

![][26]
 这个问题在下面讲闭包的时候解决。 
 **`4.获取页面所有的元素，并加上边框`** 

页面结构：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    
我是span标签 我是span标签 我是span标签

我是span标签 我是span标签 我是span标签

    
    
我是span标签 我是span标签 我是span标签

我是span标签 我是span标签 我是span标签


</body>
</html>
```

结构图：

![][27]

js代码:

```js
// 封装一个方法，获取到所有的标签，并且给这些标签加上边框
function childrenTag(ele){
    var eleArr = []; // 用于存放所有的获取到的标签
    var elements = ele.children; // 获取传入元素下的直接子元素 （伪数组）
    for(var i = 0; i < elements.length; i++){
        eleArr.push(elements[i]);
        // 获取子元素下的直接子元素
        var temp = childrenTag(elements[i]);  // 一层层的递推下去
        eleArr = eleArr.concat(temp); // 将获取的子元素的拼接到一起
    }
    return eleArr;
}
console.log(childrenTag(document.body)); // 打印的就是页面body下所有的标签
// 获取所有标签
var tags=childrenTag(document.body);
// 给所有标签添加边框
for(var i=0;i<tags.length;i++){
    tags[i].style.border='1px solid cyan';
}
```

效果图：

![][28]
## 12. JS 内存管理

本章引用自：[《MDN-内存管理》][32]
### 12.1 内存生命周期

不管是什么程序语言，内存生命周期基本是一致的：

* 分配你所需要的内存；
* 使用分配到的内存（读、写）；
* 不需要时将其释放、归还。

 **`JavaScript 的内存分配：`** 

为了不让程序员费心分配内存，`JavaScript`在定义变量时就完成了内存分配。
```js
var n = 123;        // 给数值变量分配内存
var s = "Levi";     // 给字符串分配内存

var o = {
  a: 1,
  b: null
};      // 给对象及其包含的值分配内存

// 给数组及其包含的值分配内存（就像对象一样）
var a = [1, null, "abra"]; 

function f(a){
  return a + 2;
}   // 给函数（可调用的对象）分配内存

// 函数表达式也能分配一个对象
someElement.addEventListener('click', function(){
  someElement.style.backgroundColor = 'blue';
}, false);
```
 **`使用值：`** 

使用值的过程实际上是对分配内存进行读取与写入的操作。读取与写入可能是写入一个变量或者一个对象的属性值，甚至传递函数的参数。 **`当内存不再需要使用时释放：`** 

大多数内存管理的问题都在这个阶段。在这里最艰难的任务是找到“所分配的内存确实已经不再需要了”。它往往要求开发人员来确定在程序中哪一块内存不再需要并且释放它。 高级语言解释器嵌入了“垃圾回收器”，它的主要工作是跟踪内存的分配和使用，以便当分配的内存不再使用时，自动释放它。这只能是一个近似的过程，因为要知道是否仍然需要某块内存是无法判定的（无法通过某种算法解决）。 
### 12.2 垃圾回收

如上所述，自动寻找是否一些内存“不再需要”的问题是无法判定的。因此，垃圾回收实现只能有限制的解决一般问题。本节将解释必要的概念，了解主要的垃圾回收算法和它们的局限性。 **`1、引用：`** 

垃圾回收算法主要依赖于引用的概念。在内存管理的环境中，一个对象如果有访问另一个对象的权限（隐式或者显式），叫做一个对象引用另一个对象。例如，一个`Javascript`对象具有对它原型的引用（隐式引用）和对它属性的引用（显式引用）。 在这里，“对象”的概念不仅特指`JavaScript`对象，还包括函数作用域（或者全局词法作用域）。 
 **`2、引用计数垃圾收集：`** 

这是最天真的垃圾收集算法。此算法把“对象是否不再需要”简化定义为“对象有没有其他对象引用到它”。如果没有引用指向该对象（零引用），对象将被垃圾回收机制回收。
* **`示例代码`** 

```js
var o = { 
  a: {
    b:2
  }
}; 
// 两个对象被创建，一个作为另一个的属性被引用，另一个被分配给变量o
// 很显然，没有一个可以被垃圾收集


var o2 = o; // o2变量是第二个对“这个对象”的引用

o = 1;      // 现在，“这个对象”的原始引用o被o2替换了

var oa = o2.a; // 引用“这个对象”的a属性
// 现在，“这个对象”有两个引用了，一个是o2，一个是oa

o2 = "yo"; // 最初的对象现在已经是零引用了
           // 他可以被垃圾回收了
           // 然而它的属性a的对象还在被oa引用，所以还不能回收

oa = null; // a属性的那个对象现在也是零引用了
           // 它可以被垃圾回收了
```

* **`限制：循环引用`** 

该算法有个限制：无法处理循环引用。在下面的例子中，两个对象被创建，并互相引用，形成了一个循环。它们被调用之后会离开函数作用域，所以它们已经没有用了，可以被回收了。然而，引用计数算法考虑到它们互相都有至少一次引用，所以它们不会被回收。
```js
function f(){
  var o = {};
  var o2 = {};
  o.a = o2; // o 引用 o2
  o2.a = o; // o2 引用 o

  return "azerty";
}

f();
```

* **`实际例子：`** 

`IE 6, 7 `使用引用计数方式对`DOM`对象进行垃圾回收。该方式常常造成对象被循环引用时`内存发生泄漏`：
```js
var div;
window.onload = function(){
  div = document.getElementById("myDivElement");
  div.circularReference = div;
  div.lotsOfData = new Array(10000).join("*");
};
```
 在上面的例子里，`myDivElement`这个`DOM`元素里的`circularReference`属性引用了`myDivElement`，造成了循环引用。如果该属性没有显示移除或者设为`null`，引用计数式垃圾收集器将总是且至少有一个引用，并将一直保持在内存里的`DOM`元素，即使其从`DOM`树中删去了。如果这个`DOM`元素拥有大量的数据(如上的`lotsOfData`属性)，而这个数据占用的内存将永远不会被释放。 
 **`3、标记-清除算法`** 

这个算法把“对象是否不再需要”简化定义为“对象是否可以获得”。这个算法假定设置一个叫做根（`root`）的对象（在`Javascript`里，根是全局对象）。垃圾回收器将定期从根开始，找所有从根开始引用的对象，然后找这些对象引用的对象……从根开始，垃圾回收器将找到所有可以获得的对象和收集所有不能获得的对象。

这个算法比前一个要好，因为“有零引用的对象”总是不可获得的，但是相反却不一定，参考“循环引用”。

从`2012`年起，所有现代浏览器都使用了`标记-清除垃圾`回收算法。所有对`JavaScript`垃圾回收算法的改进都是基于标记-清除算法的改进，并没有改进标记-清除算法本身和它对“对象是否不再需要”的简化定义。

* **`循环引用不再是问题了`** 

在上面的示例中，函数调用返回之后，两个对象从全局对象出发无法获取。因此，他们将会被垃圾回收器回收。第二个示例同样，一旦`div`和其事件处理无法从根获取到，他们将会被垃圾回收器回收。
* **`限制: 那些无法从根对象查询到的对象都将被清除`** 

尽管这是一个限制，但实践中我们很少会碰到类似的情况，所以开发者不太会去关心垃圾回收机制。 一般情况下, 如果需要手动释放变量占用的内存, 就将这个变量赋值为:`null` 
## 13. 闭包

了解闭包之前，先了解下另外两个知识点： **`1、函数基础知识`** 


* 1、函数内部的代码在调用的时候执行
* 2、函数返回值类型可以是任意类型
* 3、怎么理解函数的返回值


* 将函数内部声明的变量暴露到函数外部
* 函数内用来返回数据，相当于没有函数的时候直接使用该数据
* 不同之处在于：函数形成作用域，变量为局部变量


```js
function foo() {
    var o = {age: 12};
    return o;
}
var o1 = foo();

// 相当于： var o1 = {age: 18};
```
 **`2、作用域的结论`** 


* 1、`JavaScript`的作用域是词法作用域
* 2、函数才会形成作用域(函数作用域)
* 3、词法作用域：变量(变量和函数)的作用范围在代码写出来的就已经决定, 与运行时无关
* 4、函数内部可以访问函数外部的变量（函数外部不能访问函数内部的变量）
* 5、变量搜索原则：从当前链开始查找直到`0`级链
* 6、当定义了一个函数，当前的作用域链就保存起来，并且成为函数的内部状态的一部分。


### 13.1 闭包的概念

闭包从字面意思理解就是闭合，包起来。简单的来说闭包就是，一个具有封闭的对外不公开的包裹结构或空间。在`JavaScript`中函数可以构成闭包。一般函数是一个代码结构的封闭结构，即包裹的特性。同时根据作用域规则， 只允许函数访问外部的数据，外部无法访问函数内部的数据，即封闭的对外不公开的特性。因此说函数可以构成闭包。
 **`闭包的其他解释`** 

在计算机科学中，闭包（英语：`Closure`），又称词法闭包（`Lexical Closure`）或函数闭包（`function closures`），是引用了自由变量的函数。

* 这个被引用的自由变量将和这个函数一同存在，即使已经离开了创造它的环境也不例外。所以，有另一种说法认为闭包是由函数和与其相关的引用环境组合而成的实体。
* 闭包在运行时可以有多个`实例`，不同的引用环境和相同的函数组合可以产生不同的`实例`。

`实例：`

```js
function fn() {
    var num = 123;
    return function foo() {
        console.log(num);
    };
}

// bar1就是闭包的一个实例
var bar1 = fn();
// bar2就是闭包的另外一个实例
var bar2 = fn();

bar1(); // 123
bar2(); // 123
```
 **`闭包的构成`** 

闭包包括两部分：

* 1、函数体（函数自身的代码）；
* 2、环境（函数的作用域）。

 **`闭包的说明`** 


* 1、`JS`中函数形成了闭包
* 2、闭包是函数作用域的应用
* 3、对于闭包来说，只关注`创建函数的作用域`，不关注调用函数的位置

 **`闭包的作用`** 


* 对函数内部的变量起到保护作用
* 除了返回的函数以外，没有任何手段能够获取或者修改这个变量的值


### 13.2 闭包模型

```js
function foo() {
    var num = 0;
    // 函数会产生一个作用域，所以外部的程序想要访问函数内部的变量，一般情况下是不行的
    // 通过闭包的方式可以使外部访问到函数内部的变量
    // 具体做法就是在函数内部返回一个函数，并且这个函数使用了这个变量
    // 当用户调用最外层的函数的时候，使用的这个变量就会随着返回的函数返回给用户
    return function() {
        return ++num;
    };
}
// 函数foo的返回值就是一个函数，所以，就可以调用getNum这个函数了！
var getNum = foo();
console.log(getNum());   // 1
```
### 13.3 闭包的使用

目标：想办法（在外部）访问到函数内部的数据 **`利用函数返回值`** 

```js
function foo() {
    var num = Math.random();
    return num;
}

var num1 = foo();
var num2 = foo();
console.log(num1 === num2);  // 随机数 相同的情况很小很小
```
 **`普通的函数返回值说明`** 


* 两次调用函数，返回的数据并不是同一个数据。
* 原因：函数在每次调用的时候，内部的数据会被新创建一次

 **`游戏充值案例`** 

* **`示例图片：`** 

![][29]

* **`示例代码：`** 

```html
<button id="pay">充值</button>
<button id="play">玩游戏</button>
<script>
    // 需求：
    // 1-需要对充值的金额起到保护作用，这个存放数值的变量不能暴露在全局，否则谁都会去修改这个金额
    //   var money = 0;
    // 2-点击充值按钮的时候，每次充值10元
    // 3-点击玩游戏按钮的时候，每玩一次金额减少一元
    function fn (){
        var money = 0; // money用来存储充值的钱，放在函数内部，不会暴露在全局
        // 一般的闭包返回值是一个函数，但是这里有两个功能，一个是玩游戏，一个是充值；
        // 两个功能分开，但是金额之间还是关联的，所以这里返回一个对象，里面存放两个方法
        return {
            // 充值的函数
            recharge:function(value){
                money += value;
                console.log('尊敬的黄金会员，您本次充值：' + value, '，您的总余额为：' + money);
            },
            // 玩游戏的函数
            play:function(){
                if(money <= 0){
                    console.log('余额不足无法继续游戏，请充值！');
                    return;
                }
                money--;
                console.log('您还剩余 ' + money + ' 条命！');
            }
        };
    }
    var obj = fn();
    // 点击“充值”按钮
    var pay = document.getElementById('pay');
    pay.addEventListener('click', function () {
        obj.recharge(10);
    });
    // 点击“玩游戏”按钮
    var play = document.getElementById('play')
    play.addEventListener('click', function () {
        obj.play();
    })
</script>

```

* **`优化，多个角色进行充值玩游戏`** 

```html

    <button id="pay">小明：充值</button>
    <button id="play">小明：玩游戏</button>




    <button id="pay1">小华：充值</button>
    <button id="play1">小华：玩游戏</button>



<script>
    // 1 需要对充值的钱起到保护作用
    // var money = 0;
    // 2 充值：    每次充值20
    // 3 玩游戏：  每玩一次，金额少1
    
    // 整个fn()形成一个函数作用域，对里面的变量起到保护作用
    function fn() {
      // money 用来存储充值的钱
      var money = 0;
    
      // 充值的函数：
      function recharge(value) {
        // money += 20;
        money += value;
        console.log('尊敬的黄金会员，您本次充值：' + value, '，您的总余额为：' + money);
      }
    
      // 玩游戏的函数
      function play() {
        money--;
        if (money < 0) {
          console.log('余额不足，请充值！');
        } else {
          console.log('您还剩余 ' + money + ' 条命！');
        }
      }
    
      return {
        recharge: recharge,
        play: play
      };
    }
    
    // 小明充值玩游戏的函数
    var obj;
    obj = fn();
    
    // 小明玩游戏：
    var pay = document.getElementById('pay');
    pay.addEventListener('click', function () {
      obj.recharge(20);
    });
    
    var play = document.getElementById('play')
    play.addEventListener('click', function () {
      obj.play();
    });
    
    // 小华（新的闭包实例）：
    var obj1 = fn();
    // 小华玩游戏：
    var pay1 = document.getElementById('pay1');
    pay1.addEventListener('click', function () {
      obj1.recharge(20);
    });
    
    var play1 = document.getElementById('play1')
    play1.addEventListener('click', function () {
      obj1.play();
    });
</script>
```
 优化的案例我们可以看到，只要重新定义一个变量，接收函数`  fn()`，就能重新开辟一个新的空间，且多个用户之间不受任何影响。 
### 13.4 闭包里的缓存
 **`从内存看闭包`** 

函数调用也是需要内存的！因为函数中声明了一些变量，这些变量在函数调用过程中是可以使用的，所以, 这个变量是存储到了函数调用时候分配的内存中了！因为没有任何变量来引用这块内存，所以，函数调用结束。 函数调用占用的内存就会被回收掉。虽然，此时的函数有返回值(返回了一个普通的变量)，并且这个函数调用结束以后这个函数占用的内存还是被回收了！但是, 存储函数的内存还在。
 **`闭包的内存占用:`** 

作用域的引用是对函数整个作用域来说的，而不是针对作用域中的某个变量！！！即便没有任何的变量，也是有作用域( 作用域的引用 )。
```js
function fn() {
    var num = 123;
    return function() {
        console.log(num);
    };
}
// 此时, 函数fn调用时候占用的内存, 是不会被释放掉的!!!
var foo = fn();
// 调用 foo() 此时, 因为返回函数的作用域对外层函数fn的作用域有引用
// 所以, 即使是 fn() 调用结束了, 因为 返回函数作用域引用的关系, 所以
// 函数fn()调用时候, 产生的内存是不会被释放掉的!
foo();

// 手动释放闭包占用的内存!
foo = null;
```
 **`缓存介绍`** 


* 缓存：暂存数据方便后续计算中使用。
* 缓存中存储的数据简单来说就是：键值对
* 工作中，缓存是经常被使用的手段。
* 目的：提高程序运行的效率
* 我们只要是使用缓存，就完全信赖缓存中的数据。所以， 我们可以通过闭包来保护缓存。

 对于缓存来说，我们既要存储值，又要取值！存储的目的是为了将来取出来，在`js`中可以使用对象或者数组来充当缓存。 

如果是需要保持顺序的，那么就用数组，否则就用对象！

```js
// 创建一个缓存：
var cache = {};

// 往缓存中存数据：
cache.name = 'xiaoming';
cache['name1'] = 'xiaohua';

// 取值
console.log(cache.name);
console.log(cache['name1']);
```
 计算机中的缓存就是数据交换的缓冲区（称作`Cache`），当某一硬件要读取数据时，会首先从缓存中查找需要的数据，如果找到了则直接执行，找不到的话则从内存中找。由于缓存的运行速度比内存快得多，故缓存的作用就是帮助硬件更快地运行。 
 **`缓存使用步骤`** 


* 首先查看缓存中有没有该数据，
* 如果有，直接从缓存中取出来；
* 如果没有就递归计算，并将结果放到缓存中

 **`递归计算斐波那契数列存在的问题`** 

前面在学习递归的时候，我们举了一个斐波那契数列的例子，但是当时说存在性能问题，我们重新看下这个问题。
```js
// 使用递归计算 菲波那契数列
// 数列：1 1 2 3 5 8 13 21 34 55 89 。。。
// 索引：0 1 2 3 4 5 6  7  8  9  10 。。。

var count = 0;
var fib = function (num) {
  count++;
  if (num === 0 || num == 1) {
    return 1;
  }

  return fib(num - 1) + fib(num - 2);
};

// 计算索引号为10的值, 一共计算了:  177 次
// 计算索引号为11的值, 一共计算了:  287 次
// 计算索引号为12的值, 一共计算了:  465 次
// ....
// 计算索引号为20的值, 一共计算了:  21891 次
// 计算索引号为21的值, 一共计算了:  35421 次
// ...
// 计算索引号为30的值, 一共计算了:  2692537 次
// 计算索引号为31的值, 一共计算了:  4356617 次

fib(31);
console.log(count); // 4356617
```
 注意上面代码，`count`是用来记录程序运行时执行的次数，不明白的小伙伴可以返回递归那一章节，我专门画了一张图，可以理解下这个次数是怎么计算的。我们看下上面的代码的注释，求第`20`项跟`21`项的时候，虽然只相差一项，但是却多运算了一万多次，试想一下这里面存在的效率问题是多么的可怕。 
 **`闭包和缓存解决计算斐波那契数列存在的问题`** 

其实主要的问题就是，数据重复运算。比如计算第五项的时候，他计算的是第三项跟第四项的和，这时的第三项跟第四项都是从一开始重新计算的，假如吧计算过得值保存下来，就不需要再重复的运算。

* 运用缓存：将计算的值存储下来，减少运算次数，提高效率；
* 使用闭包：从来保护缓存。


```js
// 记录计算的次数
var count = 0;

function fn() {
  // 缓存对象
  var cache = {};

  // 这个返回函数才是 递归函数!
  return function( num ) {
    count++;

    // 1 首先查看缓存中有没有 num 对应的数据
    if(cache[num]) {
      // 说明缓存中有我们需要的数据
      return cache[num];
    }

    // 2 如果缓存中没有, 就先计算, 并且将计算的结果存储到缓存中
    if(num === 0 || num === 1) {
      // 存储到缓存中
      cache[num] = 1;
      return 1;
    }

    var temp = arguments.callee(num - 1) + arguments.callee(num - 2);
    cache[num] = temp;
    return temp;
  };
}

var fib = fn();
var ret = fib(20);
console.log(ret);   // 10946
console.log('计算了:' , count, '次');  // 计算了: 39 次
```
 我们可以跟上面没有使用缓存，求斐波那契数列的比较一下，此时求第`20`项的时候，仅仅运算了`39`次，但是在之前却运行了`21891`次。 

上面的方法存在着一些的问题，每次在执行的时候，函数`fn`都要先被调用一次（`var fib = fn();`），下面进行优化：


* 将`fn`转换成自执行函数（沙箱模式，下一章会讲），自执行函数的返回函数就是递归函数；
* 判断缓存是否存在的条件进行优化，之前是通过判断缓存的值是否存在，来进行存、取值的，但是假如一个缓存的值是`false`的时候呢？岂不是`if(false){}`了，明明有值的时候，却不能取值了，所以玩我们只需要判断缓存里是否存在某个键就行。


```js
var fib = (function () {
  // 缓存对象
  var cache = {};

  // 这个返回函数才是 递归函数!
  return function (num) {
    // 1 首先查看缓存中有没有 num 对应的数据

    /**
        if(cache[num]) {
          return cache[num];
        }
    */
    // 只要缓存对象中存在 num 这个key, 那么结果就应该是 true
    if (num in cache) {
      // 说明缓存中有我们需要的数据
      return cache[num];
    }

    // 2 如果缓存中没有, 就先计算, 并且将计算的结果存储到缓存中
    if (num === 0 || num === 1) {
      // 存储到缓存中
      // cache[num] = 1 是一个赋值表达式, 赋值表达式的结果为: 等号右边的值!
      return (cache[num] = 1);
    }

    // arguments.callee 表示当前函数的引用
    return (cache[num] = arguments.callee(num - 1) + arguments.callee(num - 2));
  };
})();

var ret = fib(10)
console.log(ret);
```
 **`什么是 arguments.callee？`** 

返回正被执行的`function`对象，也就是所指定的`function`对象的正文。`callee`属性是`arguments`对象的一个成员，它表示对函数对象本身的引用，这有利于匿名函数的递归或者保证函数的封装性。
```js
function fn(a, b) {
    console.log(arguments);
}
fn(1, 2);
```

我们可以看到，打印的`arguments`属性里面有哪些参数：

![][30]


* 前面几项是函数调用后传进来的实参；
* `callee:f`，它其实就是函数`fn`的引用，你可以理解为：`arguments.callee()`相当于`fn()`；
* `length`就是实参的长度。

 再去看上面斐波那契的案例，它的递归函数是一个匿名函数，所以在这个函数里面自己调用自己的时候，就是使用的`arguments.callee`去引用的。 
## 14. 沙箱模式

沙箱模式又称：沙盒模式、隔离模式。沙箱（`sandbox`）介绍：用于为一些来源不可信、具备破坏力或无法判定程序意图的程序提供试验环境。然而，沙盒中的所有改动对操作系统不会造成任何损失。### 14.1 沙箱模式的作用


* 作用：对变量进行隔离
* 问题：在`js`中如何实现隔离？


```js
ES6之前， JavaScritp中只有函数能限定作用域，所以，只有使用函数才能实现隔离。
```
 本质上还是对函数作用域的应用。 
### 14.2 沙箱模式模型

* 使用自调用函数实现沙箱模式


* 函数形成独立的作用域；
* 函数只有被调用，内部代码才会执行；
* 将全局污染降到最低。


```js
(function() {
    // ...
    // 代码
    // ...
})(); 
```
### 14.3 沙箱模式应用

最佳实践：在函数内定义变量的时候，将 变量定义 提到最前面。
```js
// 1 减少了window变量作用域的查找
// 2 有利于代码压缩
(function( window ) {

  var fn = function( selector ) {
    this.selector = selector;
  };

  fn.prototype = {
    constructor: fn,
    addClass: function() {},
    removeClass: function() {}
  };

  // 给window添加了一个 $属性，值为： fn
  // 暴露数据的方式:
  window.$ = fn;

})( window );
```
### 14.4 沙箱模式的说明


* 将代码放到一个立即执行的函数表达式(`IIFE`)中，这样就能实现代码的隔离；
* 使用`IIFE`：减少一个函数名称的污染，将全局变量污染降到最低；
* 代码在函数内部执行，函数内部声明的变量不会影响到函数外部；
* 如果外部需要，则可以返回数据或把要返回的数据交给`window`。

 `IIFE: Immediately Invoke Function Expression`立即执行的函数表达式 
## 15. 工厂模式

工厂模式是一种设计模式，作用是：隐藏创建对象的细节，省略了使用`new`创建对象。 **`构造函数：`** 

构造函数创建之后，我们实例化一个对象的时候都是直接通过`new`创建出来的。
```js
function Person(name, age) {
  this.name = name;
  this.age = age;
}
var p1 = new Person('Levi', 18);  
```
 **`工厂函数：`** 

工厂函数的核心就是隐藏这个`new`创建对象的细节。
```js
function Person(name, age) {
  this.name = name;
  this.age = age;
}

function createPerson(name, age) {
    return new Person(name, age);
}

var p2 = createPerson('Ryan', 19);
```
 两段代码比较下来，我们可以看到，实例出来的`p2`对象没有直接使用`new`创建，而是通过一个函数的返回值创建出来的，这就是工厂模式。 
 **`使用场合：`** 

`jQuery`中，我们用的`“$”`或者`jQuery`函数，就是一个工厂函数。
```js
/* Jquery 中的部分源码 */
// jQuery 实际上是一个 工厂函数，省略了 new 创建对象的操作
jQuery = function( selector, context ) {
    // jQuery.fn.init 才是jQuery中真正的构造函数
    return new jQuery.fn.init( selector, context );
}
```

（本篇完）

[31]: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Object/valueOf
[32]: https://note.youdao.com/
[0]: ./img/007kscFEgy1fyl4yha8ylj31400p0ac4.jpg 
[1]: ./img/9c47d583gy1fs3j10vw5xj20a004it8m.jpg 
[2]: ./img/9c47d583gy1fs3jgx3t6lj209r01j0sj.jpg 
[3]: ./img/9c47d583gy1fs3jegw83fj206k00m0si.jpg 
[4]: ./img/9c47d583gy1ftpzainrzcj20lp0bcaao.jpg 
[5]: ./img/9c47d583gy1fubq3m5898j20c9086aa5.jpg 
[6]: ./img/9c47d583gy1fs434nbijij20lg0ekt9b.jpg 
[7]: ./img/9c47d583gy1fs5a5q7y6gj20nj0e53z3.jpg 
[8]: ./img/9c47d583gy1fs7akmd4jgj20h60bbweo.jpg 
[9]: ./img/9c47d583gy1fs86or8wkij20m40gtwf5.jpg 
[10]: ./img/9c47d583gy1fs8hq4jgt1j20rv0hjjs5.jpg 
[11]: ./img/9c47d583gy1fs8l1aq567j20i60d53ym.jpg 
[12]: ./img/9c47d583gy1fs8m891kohj20ky0bejrq.jpg 
[13]: ./img/9c47d583gy1fs8o69va2rj20rd0gut9r.jpg 
[14]: ./img/9c47d583gy1fs9k7z43o6j20ob0kojs3.jpg 
[15]: ./img/9c47d583gy1fs9lq5dpasj20uk0jn3zu.jpg 
[16]: ./img/9c47d583gy1fs9n5cdbapj20nr0k1jsc.jpg 
[17]: ./img/9c47d583gy1fsaigizhd8j20at070t8x.jpg 
[18]: ./img/9c47d583gy1fsanzoq584j20b901d743.jpg 
[19]: ./img/9c47d583gy1fukvin4gi7j20vo0c2750.jpg 
[20]: ./img/9c47d583gy1fstap8w0rhg20hm040glp.gif 
[21]: ./img/9c47d583gy1ft1brlihecj20jz0ilq3d.jpg 
[22]: ./img/9c47d583gy1ftpj11xvzbj20zh0m1abu.jpg 
[23]: ./img/9c47d583gy1ftplepbfu5j209404ewec.jpg 
[24]: ./img/007kscFEgy1fyhverd0bsj308906ojrb.jpg 
[25]: ./img/9c47d583gy1fudubcaosgj20pc0iyk6t.jpg 
[26]: ./img/9c47d583gy1fujdj20wq1j20qu0kzdyo.jpg 
[27]: ./img/9c47d583gy1fujef7wiy9j20vi0gg4b0.jpg 
[28]: ./img/9c47d583gy1fujh6gh7acj20j00870ss.jpg 
[29]: ./img/9c47d583gy1fuoiq03p4lg20ed0dmaeb.gif 
[30]: ./img/007kscFEgy1fyl1o62ff1j30ad03p0sm.jpg 