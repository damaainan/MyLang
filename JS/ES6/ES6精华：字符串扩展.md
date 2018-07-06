## ES6精华：字符串扩展

来源：[https://segmentfault.com/a/1190000015271030](https://segmentfault.com/a/1190000015271030)


## 1 四字节字符
`ES6`大幅增强了对4字节（32位）字符的支持。

`JS`内部使用`UTF-16`编码规则（网页通常为`UTF-8`）。  
1字符固定为2字节，1字节为8位（二进制），其码点小于`0xFFFF`。  
有些符号的码点大于`0xFFFF`，需4字节表示，即常说的32位`UTF-16`字符。
### 1.1 表示方法

新增一种表示字符的方法：`\u{20BB7}`。  
用`{}`将码点括起，使其可直接表示超过`0xFFFF`的值。

```js
let str1 = '𠮷'; // 非吉，虽也读作 jí 。
let str2 = '\u{20BB7}';
let str3 = '\uD842\uDFB7';

console.log(str1 === str2); // true
console.log(str2 === str3); // true
```

4字节字符的两种表示有固定的转化规则，不是简单的相加。

```js
let c = 0x20BB7;
let ch = 0xD842;
let cl = 0xDFB7;

console.log( H(Number(c)) === ch ); // true
console.log( L(Number(c)) === cl ); // true

function H(c) {
  return Math.floor((c - 0x10000) / 0x400) + 0xD800;
}
function L(c) {
  return (c - 0x10000) % 0x400 + 0xDC00;
}
```
### 1.2 codePoint 系列
 **`codePointAt & charCodeAt`**   
使用`.codePointAt(0)`正确读取到完整的4字节字符。

```js
let str = '𠮷';

console.log( str.charCodeAt(0) ); // 55362，即 \uD842 。
console.log( str.charCodeAt(1) ); // 57271，即 \uDFB7 。
console.log( str.codePointAt(0) ); // 134071，即 \u{20BB7} ，即 𠮷。
console.log( str.codePointAt(1) ); // 57271，即 \uDFB7 。
```
 **`fromCodePoint & fromCharCode`**   
使用`String.fromCodePoint()`正确读取大于`0xFFFF`的32位字符的码点。

```js
console.log( String.fromCharCode(0x20BB7) ); // 解析不成功，已超过 0xFFFF 。
console.log( String.fromCodePoint(0x20BB7) ); // '𠮷'，即'\u{20BB7}'。

console.log( String.fromCharCode(0xD842) + String.fromCharCode(0xDFB7) ); // '𠮷'，即 '\uD842\uDFB7' 。
console.log( String.fromCodePoint(0xD842) + String.fromCodePoint(0xDFB7) ); // '𠮷'，即 '\uD842\uDFB7' 。
```
### 1.3 常用方法集
 **`判断是否为32位字符`** 

```js
console.log(is32Bit('a')); // false
console.log(is32Bit('𠮷')); // true

function is32Bit(s) {
  return s.codePointAt(0) > 0xFFFF;
}
```
 **`获取正确的字符长度`** 

```js
let str = 'a𠮷b';

console.log( getStringLength1(str) ); // 3
console.log( getStringLength2(str) ); // 3

function getStringLength1(str) {
  let res = str.match(/[\s\S]/gu);
  return res ? res.length : 0;
}
function getStringLength2(str) {
  let res = 0;
  for (let c of str) { res++; } // 此遍历方法可以正确的识别32位字符。
  return res;
}
```
 **`遍历方法`**   
`ES5`由于不能正确的识别32位字符，遍历存在隐患。  
`ES6`可以配合`for of`和`codePointAt`更为正确的遍历字符串。

```js
依次打印出：a 𠮷 b。

let str = 'a𠮷b';
for (let c of str) {
  console.log( String.fromCodePoint( c.codePointAt(0) ) );
}
```
## 2 模板字符串

在现行项目中，一般推荐使用模板字符串代替单双引号作为定义字符串的统一规范。
模板字符串是`ES6`新增的定义字符串的方式，使用` ```替代`''`或`""`。  
其字符串中的空格、缩进和换行等空白字符都会被保留在输出之中。  
其字符串中可以使用`${}`包裹有待执行的任意`JS`代码，包括另一个模板字符串。

```js
let name = 'Wmaker';
let str = `

My name is ${ name }.



`;

console.log(str);
// 输出：
// 
// 
//My name is Wmaker.

// 

```
### 2.1 标签模板

标签模板是函数调用的一种特殊形式：` fn`string` `。

实际传入`fn`的参数有三类。  
一是模板字符串会以`/${([\s\S]+?)}/g`为分隔符，拆分形成第一个参数。  
二是将各个`${}`（输出变量）作为依次的参数。  
三是第一个参数中的`raw`属性，这个稍后分析。

```js
let words = 'hi';
let name = 'Wmaker';

say`Say ${words} to ${name}`;
// --- 等价于
say.apply(null, [
  ['Say ', ' to ', ''],
  'hi',
  'Wmaker'
]);

function say() {
  console.log(arguments);
}
```
 **`raw属性`**   
其是为了方便取得转义之前的原始模板而设计的。  
其是与第一个参数基本相同，只不过里面的项都是转义之前的（相当再次转义）。

```js
fn`1\n2`;
// --- 等价
fn.apply(null, ['1↵2', raw:['1\n2']]);
```
 **`实际应用`**   
标签模板的优势在于，不同场景不同参数都可使用同一编译模式。

```js
let words = 'hi';
let name = 'Wmaker';

compileTemplate`Say ${words} to ${name}.
`; // <p>Say hi to Wmaker.</p>
compileTemplate`Hi ${name}!
`; // <p>Hi Wmaker!</p>

function compileTemplate() {
  let strs = arguments[0];
  let vars = Array.prototype.slice.call(arguments, 1);
  let res = transformHTML(strs[0]);

  vars.forEach((item, i) => {
    res += item + transformHTML(strs[i+1]);
  });
  
  console.log(res);

  function transformHTML(s) {
    return s.replace(/&/g, "&")
      .replace(/</g, "<")
      .replace(/>/g, ">");
  }
}
```
## 3 新增函数

这里只列举一些常用的方法和方式，具体可看：[String API][0]。
### 3.1 normalize()

方法会按照一种指定的`Unicode`正规形式将当前字符串正规化。  
有些字符有两种不同的表示方法，而且其表示不等价，虽然在结果上等价。  
比如有些语言有语调符号和重音符号Ǒ，可以使用带重音符号的字符和原字符与重音符两种表示方法。

```js
let s1 = '\u01D1'; // 'Ǒ'
let s2 = '\u004F\u030C'; // 'Ǒ'

console.log(s1 === s2); // false
console.log(s1.normalize() === s2.normalize()); // true
```
### 3.2 padStart() & padEnd()

从头/尾部补全字符的长度，对填充物的态度是多则重复少则裁剪。

```js
为数值补全指定位数。
'1'.padStart(5, '0'); // "00001"

提示字符串格式。
'12'.padStart(10, 'YYYY-MM-DD'); // "YYYY-MM-12"
```
### 3.3 String.raw()

用来充当模板字符串的处理函数，返回一个斜杠都被转义且变量已被替换的字符串。

```js
let name = 'Wmaker';
let str = String.raw`
<div class=\"header\">

## ${name}



`;

console.log(str);
// 输出：
// 
// <div class=\"header\">
// 
## Wmaker

// 

```

[0]: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/String