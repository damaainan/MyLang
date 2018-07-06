## ES6精华：函数扩展

来源：[https://segmentfault.com/a/1190000015352725](https://segmentfault.com/a/1190000015352725)

`ES6`在函数方面的扩展比较丰富也很实用，本篇概括了这中的精华知识。
## 1 箭头函数

箭头函数是`ES6`中定义函数的新形式。  
新形式不仅简化了定义方式，更为函数本身减重（其`this`,`argumnets`等与之前不同）。

```js
let fn = () => {
  console.log('fn');
};
fn(); // 'fn'

如果只有一个参数，可以省略括号。
(n => {
  console.log(n);
})(1); // 1

如果不带 {} ，意味着直接返回 => 指向的目标。
console.log( (n => 2)(1) ); // 2
注意，指向的目标只能是单体，如果为表达式需要用 () 包裹形成单体。
console.log( (n => (n + 1))(1) ); // 2
```
### 1.1 this

箭头函数没有自己的`this`，其使用的`this`是引用外层的（类似闭包）。  
因此其里面的`this`是固定的，在定义的那一刻起就已经确定，不会再变。

```js
非严格模式下。

--- 之前的函数是执行时确定 this 。
window.id = 0;

let obj = { id: 1 };
let fn = function () {
  console.log(this.id);
};

fn(); // 0，引用的是 window 。
obj.fn = fn;
obj.fn(); // 1，引用的是 obj 。


--- 箭头函数是定义时确定 this 。
window.id = 0;

let obj = { id: 1 };
let fn = () => {
  console.log(this.id);
};

fn();  // 0，引用的是 window 。
obj.fn = fn;
obj.fn(); // 0，引用的是 window 。
```

再利用多层箭头函数来说明。  
多层箭头函数，`this`的寻找途径是一层层向上查找的，类似作用域链查找。  
所以多层箭头函数在初次获取到`this`时，全部函数的`this`便都确定了。

```js
foo.call({id: 1})()(); // id: 1

function foo() {
  return () => {
    return () => {
      console.log('id:', this.id);
    };
  };
}

--- 等价于

function foo() {
  let _this = this;
  return function() {
    return function() {
      console.log('id:', _this.id);
    }
  }
}
```

因为没有自身的`this`。  
所以无法成为构造函数，不能使用`new`操作符。  
所以不能用`call`,`apply`和`bind`这些方法改变`this`的指向。

```js
let Person = () => {};
let p = new Person(); // 报错，Person is not a constructor。

window.id = '000';
let fn = () => { console.log(this.id) };
let fn1 = fn.bind({ id: '111' });
fn1(); // '000'
```
### 1.2 其它的不同

函数体内没有`arguments`对象，可以使用`rest`参数代替。  
不能使用`yield`命令，因此箭头函数不能用作`Generator`函数（可以使用`async`函数）。

```js
let fn = (...args) => {
  console.log(args); // [1, 2]
  console.log(arguments); // 报错，arguments is not defined。
};
fn(1, 2);
```
## 2 函数参数
### 2.1 默认值

可以为参数设定默认值。  
当没有传递该参数或值为`undefined`时，默认值将被使用。  
借用此方式，可以简化函数体，并使参数的性质、类型等更加清晰。

```js
--- ES6 之前
function fn(id, conf) {
  id || requiredParam();
  conf = conf || {};
  
  conf.name = conf.name || '';
  conf.ago = conf.ago || 0;
  
  console.log(id, conf);
}

--- ES6 之后
function fn(
  id = requiredParam(),
  conf = {
    name: '',
    ago: 0
  }
) {
  console.log(id, conf);
}

function requiredParam() {
  throw Error('Missing parameter.');
}
```
### 2.2 解构赋值

结合解构赋值，默认值设定的功能会更为强大。  
关于解构赋值，可参考此[链接][0]。  
为了直观的显示它的优势，我们将最终的结果分成三步。

```js
1.使用解构赋值，快速声明变量，并赋予相应的属性值。

fn({
  id: '0003'
}); // 两者都打印出：'0003' undefined

--- ES6 之前
function fn(conf) {
  let id = conf.id;
  let name = conf.name;
  console.log(id, name);
}

--- ES6 之后
function fn({id, name}) {
  console.log(id, name);
}


2.紧接着，为解构中的变量设定默认值。

fn({
  id: '0003'
}); // 两者都打印出：'0003' 'Unnamed'

--- ES6 之前
function fn(conf) {
  let id = conf.id || '0000';
  let name = conf.name || 'Unnamed';
  console.log(id, name);
}

--- ES6 之后
function fn({
  id = '0000',
  name = 'Unnamed'
}) {
  console.log(id, name);
}


3.最后，再为此参数设定默认值。

fn(); // 两者都打印出：'0000' 'Unnamed'

--- ES6 之前
function fn(conf) {
  conf = conf || {
    id: '0000',
    name: 'Unnamed'
  };
  
  let id = conf.id;
  let name = conf.name;
  
  console.log(id, name);
}

--- ES6 之后
function fn({
  id = '0000',
  name = 'Unnamed'
} = {}) {
  console.log(id, name);
}
```

再思考一个问题：是在解构中还是在参数默认值中设定属性的值？

```js
function fn1(x = {}, {a = 1, b = 2} = x) { console.log(a, b, x) }
function fn2(x = {a: 1, b: 2}, {a, b} = x) { console.log(a, b, x) }

这两方法的区别在于：变量a, b的默认值的设置地点。
如果要优先确保解析后的变量有默认值，第一种方式更为有效。

fn1(); // 1 2 {}
fn2(); // 1 2 {a:1, b:2}

fn1({}); // 1 2 {}
fn2({}); // undefined undefined {}

fn1({ a: 0 }); // 0 2 {a:0}
fn2({ a: 0 }); // 0 undefined {a:0}
```
### 2.3 rest 参数

将扩展运算符作用于参数，即为`rest`参数。  
它会将所有相应的传入参数合并成一个数组，赋值给`rest`参数。  
`rest`参数只能是最后一个参数，没有正则中所谓的贪婪性，否则会报错。

```js
打印出：'0001' ['m1','m2']。

fn('0001', 'm1', 'm2');

function fn(groupId, ...members) {
  console.log(groupId, members);
}
```
### 2.4 作用域

如果函数参数使用了默认值、解构赋值或扩展运算符，就产生了参数作用域。

执行函数体时，会先默认声明参数变量。  
如果存在参数作用域，会先执行它，再到函数体作用域中。  
初始化结束后，参数作用域消失，之后函数体会默认声明同名变量指向相应的参数变量。

因为作用域的存在，参数是惰性（调用时）求值的。

```js
let n = 0;

fn(); // 1

n = 1;
fn(); // 2

function fn(num = (n + 1)) {
  console.log(num);  
}
```

因为默认声明原则，在函数体中声明同名参数相当二次声明。  
使用`let`,`const`相当重复声明，会报错。  
使用`var`会解绑函数体与参数作用域的关联，变量便成了纯粹的函数体变量。

```js
--- 普通
let x = 0;
fn(1); // 2
function fn(x, y = () => { console.log(x) }) {
  x = 2;
  y();
}

--- 解绑
let x = 0;
fn(1); // 1
function fn(x, y = () => { console.log(x) }) {
  var x = 2;
  y();
}
```

如果存在参数作用域，就不能在函数体中显式的设定严格模式，否则报错。  
因为函数内部的严格模式，应该同时作用于函数体和参数作用域。  
但是只有进入函数体，才能知道是否有显式地声明，而参数体却先于函数体执行。  
不过可以变通的，将此函数置于一个处在严格模式的环境中。

```js
报错：Illegal 'use strict' directive ...
function fn(n = 0) {
  "use strict";
}
```
## 3 函数属性
### 3.1 name

不同形式的函数，其`name`属性值构建的方式也不相同，下面是个人总结的八种方式。

```js
1.声明式，直接为函数名。
console.log(fn.name); // 'fn'
function fn() {}

2.命名函数表达式，直接为函数名。
let fn1 = function fn() {};
console.log(fn1.name); // 'fn'

3.表达式，为第一次赋值的变量/属性。
let fn = function() {};
console.log(fn.name); // 'fn'
let fn1 = fn();
console.log(fn.name); // 'fn'
let obj = { fn: function() {} };
console.log(fn.name); // 'fn'

4.没有赋值的匿名表达式，为空。
console.log( (function() {}).name ); // ''

5.通过构造函数生成的，为 anonymous 。
console.log( (new Function()).name ); // 'anonymous'

6.通过 bind() 生成的，name 属性值会加上 bound 前缀。
console.log( (function() {}).bind({}).name ); // 'bound '
console.log( (function fn() {}).bind({}).name ); // 'bound fn'

7.如果对象的方法名为 Symbol 值，name 属性返回的是此 Symbol 的描述。
let s1 = Symbol();
let s2 = Symbol('s2');
console.log( ({ [s1]() {} })[s1].name ); // ''
console.log( ({ [s2]() {} })[s2].name ); // [s2]

8.getter/setter 函数的 name 属性，在其描述对象的 get/set 属性上，为 get/set 函数名。
let obj = {
   get name() {}
};
Object.getOwnPropertyDescriptor(obj, 'name').get.name; // 'get name'
```
### 3.2 length

其本质含义是该函数预期传入的参数个数。  
如果参数有默认值或为`rest`参数，则它以及它之后的参数都不会被计算在内。  
基于这点，在参数设计上，一般把可以省略或有默认值的参数设置为尾参数。

```js
console.log( (function(...args) {}).length ); // 0
console.log( (function(a, {b}, c = 5, d) {}).length ); // 2
```
### 3.3 arguments

类数组对象`arguments`保存的仅仅存储调用方法时传进来的参数。  
这意味着，使用默认值的参数、解构参数或`rest`参数等都不在其中。

```js
(function (name = 'Wmaker') {
  console.log(name, arguments.length);
})(); // 'Wmaker' 0

(function ({a, b}) {
  console.log(a, b, arguments.length);
})({ a: 1, b: 2 }); // 1 2 1

(function (...arr) {
  console.log(arr, arguments.length);
})(1, 2, 3); // [1, 2, 3] 3
```

[0]: https://segmentfault.com/a/1190000015072149