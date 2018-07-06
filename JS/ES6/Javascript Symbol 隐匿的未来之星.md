## Javascript Symbol 隐匿的未来之星

来源：[https://segmentfault.com/a/1190000014538151](https://segmentfault.com/a/1190000014538151)

ES6中基础类型增加到了7种，比上一个版本多了一个`Symbol`，貌似出现了很长时间，但却因没有使用场景，一直当作一个概念层来理解它，我想，用它的最好的方式，还是要主动的去深入了解它吧，所以我从基础部分和总结的实用场景来分析这个特性。已经了解使用方法或者时间紧迫者可以从实用场景一节开始阅读
## base

首先，它给我的第一感觉就是`ES6做出了很多释放语言特性方面的改变`，它能让我们更加了解语言内部机制，Symbol以对象的键值定义，比如

```js
 let key = Symbol('test');  
 let obj = {};
 obj[key] = 'alone';
 obj[key];  // "alone"
```

Symbol正如其名，表示一个唯一的标示，以属性的方式存在于对象当中，它接收一个参数，没有实质的作用，只是为了做一个描述。以上我们通过直接量的方式来定义它，并且取值时，也需要使用key进行读取，如果出现跨作用域的情况，是不是就不能获取了？

```js
function sent(key){
    accept({[key]:"2018"})
}
function accept(obj) {
   obj[???] //我怎么拌？
}
```

以上两个作用域中，如果不把key传递过来，是无法读取的，一个属性还好，但是如果多了，那么靠参数传递key是不现实的. 在这种情况下，我们可以使用`Symbol.for`来为它再添加一个`标示`，它接受一个参数String{key}。通常，它做为一个偏功能性的标记来表示，在全剧中它是 **`唯一`** 的。

```js
function sent(key){
    return accept({[key]:"2018"},key)
}
function accept(obj,key) {
   console.log(Symbol.keyFor(key))  //CURRENT_YEAR
   return obj[Symbol.for(Symbol.keyFor(key))] //CURRENT_YEAR
}
sent(Symbol.for('CURRENT_YEAR'))
```

并且使用`Symbol.for`来生成，会在存入当前全局上下文中一个`<List>`结构中，我们称它为`GlobalSymbolRegistry `, 顾名思义，它是全局的，所以使用key时我们需要谨慎，尤其是在大型项目中。

需要还注意以下几点:


* 读取它需要使用`getOwnPropertySymbols`方法，具体请参看[MDN][0]

* Symbol() !== Symbol()`but`Symbol.for('t') === Symbol.for('t')
* GlobalSymbolRegistry对象存在于当前窗口进程中，直到关闭窗口,才清除掉


目前的浏览器版本中把Symbol打印出来是字符串的格式，并没有显示具体的对象结构，我们可以直接打印 Symbol，来查看对应的prototype属性以及内部方法，所以`Symbol().__proto__ === Symbol.prototype`
在使用 Symbol 做key值时，它经历了以下步骤


* 如果指向对象是没有定义的则抛出类型错误
* 如果描述符为undefined则为''
* 把描述符转换为String格式
* 生成唯一的key，并返回
* 最后一步，把这个key赋给对象，并以Symbol(des)的方式显示，其内部还是以key为准，所以 Symbol() !== Symbol() ，即便他们看起来都是 字符串的"Symbol()"


所以这样写也是可以的，但是貌似没有什么意义

```js
var n = 1;
var key = Symbol('numer')
n[key] = ‘Symbol Number’
```

n[key]的时候把n隐式转换成[封装对象][1]，并为他添加Symbol，但并没有办法去通过封装对象回访这个Symbol

除了单纯的用key以外，在Symbol类下还有一些有意思的方法，following :
## iterator

为指向对象添加 iterator 接口，比如使用`数组解构`或者使用`for of`，它接受一个`generator函数`

```js
class IteratorExec {
    constructor(){ this.count = 1 }
    *[Symbol.iterator] = function* (){
        yield this.count++;
        yield this.count++;
        yield this.count++;
    }
 }
let obj = new IteratorExec()
[...obj] //[1,2,3]
```

通过添加`iterator`使用数据解构，还可以使用`for of`

```js
 let values = [];
 for (let value of obj) { values.push(value) }
 values;  //[1,2,3]
```

注：ES6中Map,Set,数组和添加了`Iterator`接口的对象，拥有Iterator接口.
## asyncIterator

这不是ES6中的特性，貌似放到了ES7中，可以提前意淫一下如下代码:

```js
for await (const line of readLines(filePath)) {
  console.log(line);
}
```
## toPrimitive

在对对象类型进行转换时，会进行一次`toPrimitive`,利用这个Symbol可以改变目标对象的转换规则，改变了以前的 "[object Object]"的固定形式

```js
let obj = {
    [Symbol.toPrimitive](hint){
      switch(hint){
          case 'number': return 5;
          case 'string': return 'string';
          case 'default': return 'default'    
      }
    }
}
obj+11 // 'default11'
obj*2 // 10
```

这里需要注意+ Number操作是不属于 'number' 的，其他正常，这样就可以定义转对象类型的转换规则了。
## toStringTag

在javascript一切皆为对象，而在每个对象中，都会有一个内部属性[[Class]]表示其对象类型，这在`Symbol.toStringTag`，中是可以修改的，也就是说 '[object Object]' 后边的字符串是可自定义的

```js
 let obj = {
    [Symbol.toStringTag]:'custom'
}
Object.prototype.toString(obj); // [object Object]
obj.toString();  //[object custom]
```

通常我们使用Object.prototype.toString读取对象属性，正是因为向后兼容，规范在对象自身的toString上实现了这种特性，而老式方法依旧使用。但是我们可以使用以下方式:

```js
obj = {
    [Symbol.toStringTag]:'custom'
    get [Symbol.toStringTag](){
        return 'custom'
    }
}
Object.prototype.toString.call(obj)
```

我们把obj传入执行toString,可以达到这种效果，可以预想es6中，Object.toString是受到上下文的影响的. 显然，我们上面的两个例子都是获取的Object.prototype.toString 两者有很大区别，只有它才能`准确转换`，如果你的toString不全等于它，那是无法转换的，比如

```js
 var n = new Number();
 n[Symbol.toStringTag] = 123;
 n.toString();  // “0” 
```

太幼稚了，太无聊了😊，Number私有的toString是直接把`[[PrimitiveValue]]`转换成了字符串，这里大家要千万留心，不要误认为所有的对象添加了`Symbol.toStringTag`都可以改变，如果当前对象不是纯对象，那么你可以为此对象添加一个`getter`返回对应的类型，这样外部在使用Object...call的时，会获取自定的类型。所以，这需要外部配合使用，你添加getter，人家不call你也是没办法的。

另外Symbol暴露了几种为原生对象定义了一些类型，比如

```js
Math.toString();  //[object Math]
```

其他类型有 JSON, Promise, Map, TypedArray, DataView, ArrayBuffer, Genterator等等
## unscopeables

```js
const object1 = {
  property1: 42
};

object1[Symbol.unscopables] = {
  property1: true
};

with (object1) {
  console.log(property1);
}

```

这个功能我感觉可用性为0，基本不用，with就是据对禁止的.
## hasInstance

对于`instance`运算符，为此操作添加一个钩子，第一参数是instance的左值，我们可以返回true|false来定义运算符的返回值

```js
var obj1 = {
    [Symbol.hasInstance](instance){
        return Array.isArray(Array)
    }
}
class Array1 {
  static [Symbol.hasInstance](instance) {
    return Array.isArray(instance);
  }
}
[] instance obj1  //true
console.log([] instanceof Array1);  //true
```
## isConcatSpreadable

表示[].concat是否可以展开，默认是true.

```js
let arr = [1,2];
arr.concat([3,4],5)  //[1,2,3,4,5]

arr[Symbol.isConcatSpreadable] = false;
arr.concat([3,4],5)  //[[1,2],3,4,5]

// 也可以把[3,4]提出来处理
let arr2 = [3,4]
arr2[Symbol.isConcatSpreadable] = false;
arr.concat(arr2,5); //[[1,2],[3,4],5]
```

只有在数组中这个symbol属性为false，concat操作时，就不会去解构。那么是不是意味着属性设置为ture，没有意义了？对于数组来说是的，因为它默认就是true，可是对于类数组对象，它还有一个小功能:

```js
// (续)
arr.concat({length:2,0:3,1:4,[Symbol.isConcatSpreadable]:true}) //[1,2,3,4]
```
## match & replace & split & search

一些字符串的操作方法，一起都说了，大概都一个意思，就是接受一个对象，然后实现一个钩子处理的函数，并返回其处理结果，它们都是可以接收正则的方法，在ES6之前，如果我们需要对字符串有比较复杂的操作基本上都是在方法外部的，必

```js
class MyMatch {
    [Symbol.match](string){return string.indexOf('world') }
}

'hello world'.match(new MyMatch()); //6

class MyReplace{
  [Symbol.replace](string) {
     return 'def'
  }
}

'abcdef'.replace(new MyReplace(),'xxx'); //'abcxxx'

class mySplit {
    [Symbol.split](val){
        return val.split('-');
    }
}

"123-123-123".split(new mySplit());  //['123','123','123']

class MySearch {
    constructor(value) {
        this.value = value;
    }
    [Symbol.search](string) {
        return string.indexOf(this.value);
    }
}
var fooSearch = 'foobar'.search(new MySearch('foo'));  //0
var barSearch = 'foobar'.search(new MySearch('bar'));  //3
var bazSearch = 'foobar'.search(new MySearch('baz'));  //-1
```
## practice


* 可以通过Symbol实现以上的功能性方法，比如添加 Iterator 接口，让对象队友接口特性，实际开发中，我估计很少会用到，倒是觉得`sanycIterator`是未来的前景，目前还在[草案阶段][2]

* 对于Symbol做为键值的作用，很尴尬，实际开发中，这个我也没使用过，目前为止，只需要记住它有`unique`性，比如我们想要在一个对象中添加两个一样的key名，这种需求很不常见，


```js
var firstPerson = Symbol("peter");
var secondPerson = Symbol("peter");
var persons = {[firstPerson]:"first", [secondPerson]:"pan"};
```
## 总结
`Symbol`更多的是在使用和语言本身层面暴露更多的使用方式和特性(on Object type)，是的，它只以key的方式存在Object当中，在一切皆为对象中，它为 Next ECMScript Standard 提供了更多的可能性扩展性，这也是ES6中做的最大改变方面之一，虽不常用但我们还是要总结学习一下，以便在极端情况下应变自如，如果有什么文章中没有涉及到的点，欢迎补充! 注:`尤其是使用场景方面`[0]: 


[1]: https://segmentfault.com/a/1190000009083414
[2]: https://link.segmentfault.com/?r=https%3A%2F%2Fgithub.com%2Ftc39%2Fproposal-async-iteration