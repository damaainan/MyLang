## ES6精华：Let &amp; Const

来源：[https://segmentfault.com/a/1190000015054707](https://segmentfault.com/a/1190000015054707)

`let`和`const`都是声明变量的新方式。  
一般的，由于这两种声明方式的特性，现在项目组的开发规范中都会要求：不使用`var`而是`let`或`const`。
### Const
`const`用于定义不可更改的常量。  
不可更改，意思是标识符存储的值不可更改。  
这意味着，如果存储的是对象的地址，改动地址指向的内存是可以的。

```js
"use strict";

const OBJ = {};
OBJ.name = "OBJ"; // 成功
OBJ = {}; // 失败，改变了存储的地址。
```

由此可联想到`ES5`的冻结对象。  
如果对象的属性是个指针，依然是可以修改的。  
所以，最终极的办法是一层一层冻结所有对象。
### 块级作用域
`let`使`{}`呈现出块级作用域的特征。  
声明的变量仅存在于当前块级作用域中。  
不可在同一块级作用域中重复声明变量。  
一旦在块级作用域中声明了变量，此变量便绑定在这个区域，不再受外部的影响。

```js
"use strict";

if (true) {
  var a = 1;
  let b = 2;
}
console.log(a); // 1
console.log(b); // error, b is not defined.
```
### 定义函数

在块级作用域中，优先使用表达式声明函数（`let`,`const`,`var`）。  
不要使用声明式声明函数，因为不同浏览器在这方面的实现有所差异。  
在`Chrome`中，严格模式下等价于使用`let`声明，非严格下等价于使用`var`。

```js
// 在 Chrome 66 浏览器。

// --- 严格模式
"use strict";

console.log(fn); // error, fn is not defined.
if (true) {
  function fn() {
    console.log('hi');
  }
}
console.log(fn); // error, fn is not defined.

// --- 非严格模式。
console.log(fn); // undefined
if (true) {
  function fn() {
    console.log('hi');
  }
}
console.log(fn); // function
```
### 暂时性死区

块级作用域的顶部到声明此变量之前的区域，称为此变量的暂时性死区。  
在暂时性死区内，不能使用该变量。

```js
"use strict";

let a = 1;
{
  // 在这里使用 a 会报错。
  let a = 2;
}

// 对比 var
var b = 2;
fn();
console.log(b); // 2

function fn() {
  b = 1;
  var b;
  console.log(b); // 1
}
```
 **``let`也存在变量提升，只不过对待方式和之前不同。`**   
变量提升，简单的说就是在执行代码前先会看到底声明了哪些变量和方法。  
在`ES5`中使用`var`声明的变量，在声明之前可以访问，其值为`undefined`。  
在`ES6`中使用`let`声明的变量，为了保持程序的严谨性，不允许被访问。
### 解绑全局变量

在之前的版本中，全局变量等价于顶层对象的相应属性。  
而`ES6`中新的变量声明方式（`let`,`const`,`class`）定义的全局变量与顶层对象的属性脱钩。

```js
const MY = {};
console.log(window.MY); // undefined
```
### 替代自执行函数
#### 定义临时变量

```js
// --- ES5
(function() {
  var a = 1;
})();

// --- ES6
{
  let a = 1;
}
```
#### 简化`for`循化

```js
// --- ES5
// 使用自执行函数获取并切断变量，再用闭包存储变量
var fns = [];
for (var i = 0; i < 7; i++) {
  fns[i] = (function(n) {
    return function() {
      console.log(n);
    };
  })(i);
}
fns[3](); // 3

// --- ES6
var fns = [];
for (let i = 0; i < 7; i++) {
  fns[i] = function() {
    console.log(i);
  };
}
fns[3](); // 3
```
####`for`+`let`组合的理解
`for`后面的`()`是一个独立的作用域。  
`for`后面的`{}`是一个独立的作用域。  
`for`后面的`{}`中的作用域链为：本身 >`()`> 外部。  
每次循环，都会重新在`()`里定义`i`，并将其值设置为其上次循环结束的值。

```js
// 证明 () 是一个独立的作用域。
let i = 3;
for (let i = 0; i< 7; i++) {}
console.log(i); // 3

// 证明 {} 的作用域链为：本身 -> ()作用域 -> 外部作用域。
for (let i = 0; i< 7; i++) {
  i = 7;
  console.log(i); // 纸打印一次，值为 7 。
}
for (let i = 0; i< 7; i++) {
  let i = 'hi';
  console.log(i); // 打印 7 次 'hi' 。
}
```
