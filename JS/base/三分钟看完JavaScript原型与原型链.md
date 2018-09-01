## 三分钟看完JavaScript原型与原型链

来源：[http://www.jianshu.com/p/9e7d54bd0717](http://www.jianshu.com/p/9e7d54bd0717)

时间 2018-02-21 14:48:42

 
## 前戏
 

![][0] 
 
* 写的比较短了，三分钟看完应该是没问题（嗯。。）。 
* 当然最好再花半小时思考理解一下。 
 
 
## 正文
 
### 构造函数与原型
 
与大部分面向对象语言不同，JavaScript中并没有引入类（class）的概念，但JavaScript仍然大量地使用了对象，为了保证对象之间的联系，JavaScript引入了原型与原型链的概念。
 
在Java中，声明一个实例的写法是这样的：

```js
ClassName obj = new ClassName()
```
 
为了保证JavaScript“看起来像Java”，JavaScript中也加入了new操作符：

```js
var obj = new FunctionName()
```
 
可以看到，与Java不同的是，JavaScript中的new操作符后面跟的并非类名而是函数名，JavaScript并非通过类而是直接通过构造函数来创建实例。

```js
function Dog(name, color) {
    this.name = name
    this.color = color
    this.bark = () => {
        console.log('wangwang~')
    }
}

const dog1 = new Dog('dog1', 'black')
const dog2 = new Dog('dog2', 'white')
```
 
上述代码就是声明一个构造函数并通过构造函数创建实例的过程，这样看起来似乎有点面向对象的样子了，但实际上这种方法还存在一个很大的问题。
 
在上面的代码中，有两个实例被创建，它们有自己的名字、颜色，但它们的bark方法是一样的，而通过构造函数创建实例的时候，每创建一个实例，都需要重新创建这个方法，再把它添加到新的实例中。这无疑造成了很大的浪费，既然实例的方法都是一样的，为什么不把这个方法单独放到一个地方，并让所有的实例都可以访问到呢。
 
这里就需要用到 **`原型（prototype）`**  ： 
 
 
* 每一个构造函数都拥有一个prototype属性，这个属性指向一个对象，也就是原型对象。当使用这个构造函数创建实例的时候，prototype属性指向的原型对象就成为实例的原型对象。 
* 原型对象默认拥有一个constructor属性，指向指向它的那个构造函数（也就是说构造函数和原型对象是互相指向的关系）。 
*  每个对象都拥有一个隐藏的属性[[prototype]]，指向它的原型对象，这个属性可以通过 
`Object.getPrototypeOf(obj)` 或`obj.__proto__` 来访问。  
*  实际上，构造函数的prototype属性与它创建的实例对象的[[prototype]]属性指向的是同一个对象，即`对象.__proto__ === 函数.prototype` 。  
* 如上文所述，原型对象就是用来存放实例中共有的那部分属性。 
* 在JavaScript中，所有的对象都是由它的原型对象继承而来，反之，所有的对象都可以作为原型对象存在。 
* 访问对象的属性时，JavaScript会首先在对象自身的属性内查找，若没有找到，则会跳转到该对象的原型对象中查找。 
 
 
那么可以将上述代码稍微做些修改，这里把bark方法放入Dog构造函数的原型中：

```js
function Dog(name, color) {
    this.name = name
    this.color = color
}

Dog.prototype.bark = () => {
    console.log('wangwang~')
}
```
 
接着再次通过这个构造函数创建实例并调用它的bark方法：

```js
const dog1 = new Dog('dog1', 'black')
dog1.bark()  //'wangwang~'
```
 
可以看到bark方法能够正常被调用。这时再创建另一个实例并重写它的bark方法，然后再次分别调用两个实例的bark方法并观察结果：

```js
const dog2 = new Dog('dog2', 'white')
dog2.bark() = () => {
    console.log('miaomiaomiao???')
}
dog1.bark()  //'wangwang~'
dog2.bark()  //'miaomiaomiao???'
```
 
这里dog2重写bark方法并没有对dog1造成影响，因为它重写bark方法的操作实际上是为自己添加了一个新的方法使原型中的bark方法被覆盖了，而并非直接修改了原型中的方法。若想要修改原型中的方法，需要通过构造函数的prototype属性：

```js
Dog.prototype.bark = () => {
    console.log('haha~')
}
dog1.bark()  //'haha~'
dog2.bark()  //'haha~'
```
 
这样看起来就没什么问题了，将实例中共有的属性放到原型对象中，让所有实例共享这部分属性。如果想要统一修改所有实例继承的属性，只需要直接修改原型对象中的属性即可。而且每个实例仍然可以重写原型中已经存在的属性来覆盖这个属性，并且不会影响到其他的实例。
 
### 原型链与继承
 
上文提到，JavaScript中所有的对象都是由它的原型对象继承而来。而原型对象自身也是一个对象，它也有自己的原型对象，这样层层上溯，就形成了一个类似链表的结构，这就是 **`原型链（prototype chain）`**  。 
 
所有原型链的终点都是Object函数的prototype属性，因为在JavaScript中的对象都默认由Object()构造。Objec.prototype指向的原型对象同样拥有原型，不过它的原型是null，而null则没有原型。
 
通过原型链就可以在JavaScript中实现继承，JavaScript中的继承相当灵活，有多种继承的实现方法，这里只介绍一种最常用的继承方法也就是 **`组合继承`**  。 

```js
function Dog(name, color) {
    this.name = name
    this.color = color
}

Dog.prototype.bark = () => {
    console.log('wangwang~')
}

function Husky(name, color, weight) {
    Dog.call(this, name, color)
    this.weight = weight
}

Husky.prototype = new Dog()
```
 
这里声明了一个新的构造函数Husky，通过call方法继承Dog中的属性（call方法的作用可以简单理解为将Dog中的属性添加到Husky中，因为还涉及到其他的知识点所以不多赘述），并添加了一个weight属性。然后用Dog函数创建了一个实例作为Husky的原型对象赋值给Husky.prototype以继承方法。这样，通过Husky函数创建的实例就拥有了Dog中的属性和方法。
 
## 结语
 
如果想要深入了解关于JavaScript中的对象和原型链的话，无脑推荐红宝书（《JavaScript高级程序设计（第3版）》）吧，第六章关于原型链有相当详细的讲解。
 


[0]: ./img/YfuyYbF.png