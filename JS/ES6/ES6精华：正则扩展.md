## ES6精华：正则扩展

来源：[https://segmentfault.com/a/1190000015328138](https://segmentfault.com/a/1190000015328138)

本篇概括了`ES6`中正则表达式新增部分的精华要点（最好有`ES5`的基础）。
## 1 u 标志

使正则处于`Unicode`模式。  
关于`ES6`的字符扩展知识，可查看[这里][0]。
### 1.1 四字节字符

处于`Unicode`模式下的正则，可以正确识别32位（四字节）字符。

```js
let c = '\uD83D\uDC2A'; // 32位字符：𠮷。
console.log( /^\S$/.test(c) ); // false，视为两字符。
console.log( /^\S$/u.test(c) ); // true，正确识别，视为一字符。

console.log( /\uD83D/.test(c) ); // true
console.log( /\uD83D/u.test(c) ); // false

console.log( /𠮷{2}/.test('𠮷𠮷') ); // false，其等价于下者。
console.log( /\uD83D\uDC2A{2}/.test('\uD83D\uDC2A\uDC2A') ); // true
console.log( /𠮷{2}/u.test('𠮷𠮷') ); // true
```

处于`Unicode`模式下的正则，支持带`{}`的`Unicode`表示法。

```js
console.log( /\u{20BB7}/.test('𠮷') ); // false
console.log( /\u{20BB7}/u.test('𠮷') ); // true
```

处于`Unicode`模式下的正则，可以用来获取字符串的正确长度。

```js
console.log( stringLength('𠮷𠮷') ); // 2

function stringLength(str) {
  let res = str.match(/[\s\S]/gu);
  return res ? res.length : 0;
}
```
### 1.2 非规范字符

处于`Unicode`模式下的正则，可以识别一些非规范字符。

```js
let k1 = '\u004B'; // 规范的 K 。
let k2 = '\u212A'; // 非规范的 K 。
console.log( /[a-z]/i.test(k2) ); // false
console.log( /[a-z]/ui.test(k2) ); // true
```
### 1.3 属性类
`Unicode`字符都有某些属性（类别），比如3、Ⅲ 都属于`Number`。  
结合`u`标志，`\p{属性名=属性值}`可以用来匹配属于某一类某一种值的字符。  
对于一般的属性，可以直接使用`\p{属性名}`或`\p{属性值}`（另外，大写`P`表否定）。

```js
let reg = /\p{Number}/u; // 匹配属于 Number 属性的字符。
console.log( reg.test('3') ); // true
console.log( reg.test('㉛') ); // true
console.log( reg.test('Ⅲ') ); // true
```
## 2 y 标志

使正则处于`Sticky`（粘连）模式。  
它确保了每次查找的开始，都是紧接上次查找的末尾，不会跳过中间不匹配的字符。  
其本质是在每次查找中加了`^`匹配开头的模式，使整个字符进行严格的一个接一个的检查。

```js
console.log( 'a1a'.match(/a/g).length ); // 2
console.log( 'a1a'.match(/a/gy).length ); // 1

console.log( '1a1a'.match(/a/g).length ); // 2
console.log( '1a1a'.match(/a/gy) ); // null

模拟 Sticky 模式大概是这样。
let str = 'a1a';
let res = /^a/.exec(str);
while (res) {
  str = str.slice(res.index + res[0].length)
  res = /^a/.exec(str);
}
```

对于正则对象，`y`会像`g`标志一样设置其`lastIndex`（类似全局性）。

```js
let reg = null;

reg = /a/y;
reg.exec('aaa');
console.log( reg.lastIndex ); // 1
reg.exec('aaa');
console.log( reg.lastIndex ); // 2

reg = /a/y;
'aaa'.match(reg);
console.log( reg.lastIndex ); // 1
'aaa'.match(reg);
console.log( reg.lastIndex ); // 2

reg = /a/y;
'aaa'.replace(reg);
console.log( reg.lastIndex ); // 1
'aaa'.replace(reg);
console.log( reg.lastIndex ); // 2
```
## 3 s 标志

使正则处于`dotAll`模式，即`.`代表全部字符（之前不包括行终止符`\r`,`\n`等）。  
也有其它可以表示全部字符的方式，比如：`[^]`,`[\s\S]`。

```js
console.log( /./.test('\n') ); // false
console.log( /./s.test('\n') ); // true
```

表示全部字符与表示行的首尾并不冲突，但在`mg`双重模式下要明确是否使用非贪婪模式。

```js
let str = `Hello!`;
console.log( str.match(/^.*$/g) ); // ["Hello!"]
console.log( str.match(/^.*$/gs) ); // ["Hello!"]

let str1 = `
  a.
  b.
`;
console.log( str1.match(/^.*$/mg) ); // ["", "  a.", "  b.", ""]
console.log( str1.match(/^.*$/msg) ); // ["↵  a.↵  b.↵", ""]
console.log( str1.match(/^.*?$/msg) ); // . 的匹配非贪婪模式，["", "  a.", "  b.", ""]。
```

补充：贪婪与非贪婪性。  
对于量词，比如`+, {1, 3}`，其前者的匹配会尽可能达到此区间的最大值，为贪婪性。  
如果在量词后面加上`?`，意味着其前者的匹配为此区间的最小值，可为0，为非贪婪性。

```js
console.log( '1234'.match(/(\d*)(\d*)/) ); // ["1234", "1234", ""]
console.log( '1234'.match(/(\d*?)(\d*)/) ); // ["1234", "", "1234"]
```
## 4 后行断言

结合已有的先行断言一起看。  
先行肯定/否定断言：`x(?=y) / x(?!y)`。  
后行肯定/否定断言：`(?<=y)x / (?<!y)x`。  
先找`x`部分，再看是否满足其前/后条件。匹配的结果仅仅是`x`部分，不包括条件部分。

```js
--- 先行断言
let str = 'The price is $12.';
let reg = /\$(?=(\d+))/;
console.log( str.match(reg) ); // ["$", "12"]，$是整个正则匹配的，122是子组的。

--- 后行断言
let str = 'The percentage is 57%';
let reg = /(?<=(\d+))%/;
console.log( str.match(reg) ); // ["%", "57"]
```

后行断言的条件语句（()里的）的查找顺序是从右向左（逆序）匹配。  
但是其中的子模式的默认命名序号，依旧是从左到右算的（可参考下面内容）。

```js
两个子组都是贪婪的，`(\d+a)`获得的数字多，说明其先被匹配的。
let str = '123a%';
let reg = /(?<=(\d+)(\d+a))%/;
str.match(reg); // ["%", "1", "23a"]，23a 为第二个匹配组 (\d+a) 的结果。
```
## 5 具名组

之前的组（子模式）都没有具体名字，它们是从左到右从1开始被命名。  
现在允许为每一个组匹配指定一个名字，既便于阅读代码，又便于引用。  
一旦使用了具名组，匹配的结果中`groups`属性便指向一个包含相应结果的对象。

```js
let str = '1234';
let reg = /(?<one>\d+)(?<two>\d+)/;
console.log( reg.exec(str).groups ); // {one: "123", two: "4"}
console.log( str.match(reg).groups ); // {one: "123", two: "4"}
```

正则中引用匹配结果的三种方式。  
第一种是上面示例所示的，搭配具名组在结果中引用。  
第二种是在`replace`时用到的，使用`$n`或`$<name>`在替换字符中替代匹配。  
第三种是直接在正则中替代之前组的匹配，使用`\n`或`\<name>`。

```js
--- 第二种
let str = 'a,b-c';
let reg = /([,-])/g;
console.log( str.replace(reg, ' $1 ') ); // a , b - c

--- 第三种
let reg = /(?<one>\d{3})\d+\k<one>/;
console.log( reg.test('111211') ); // false
console.log( reg.test('1112111') ); // true
```

[0]: https://segmentfault.com/a/1190000015271030