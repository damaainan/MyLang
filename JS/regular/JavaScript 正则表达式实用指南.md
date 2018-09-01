## JavaScript 正则表达式实用指南

来源：[https://zhuanlan.zhihu.com/p/41944003](https://zhuanlan.zhihu.com/p/41944003)

时间：发布于昨天 21:01



![][0]

简评：字符串操作中正则表达式是一个非常强大的工具，本文梳理了正则表达式中几个实用语法。
## 什么时候正则表达式

正则表达式使用单个字符串来描述、匹配一系列匹配某个句法规则的字符串。他有一套自己的语法规则，许多语言都提供这个功能如 JavaScript，Perl，Python，Php 和 Java 等等。

正则表达式通常被用来检索、替换那些匹配某个模式的文本。例如模式判断一个字符串是否是一个正确的 IP 地址，检测 E-mail 是否正确。

## 创建正则表达式

JavaScript 有两种方式创建正则表达式。

* 使用 RegExp 构造函数

语法：`new RegExp(pattern[, flags])`例如：

```js

var regexConst = new RegExp('abc');

```

* 使用 Literal快速创建（ / ）

语法：`/pattern/flags`例如：

```js

var regexLiteral = /abc/;

```

注意：flags 是 optional 参数。

## 正则表达式方法

测试正则表达式主要有两个方法：

 **RegExp.prototype.test()** 

这个方法用于检测是否成功匹配，匹配成功返回 true 否则返回 false。

```js

var regex = /hello/;
var str = 'hello world';
var result = regex.test(str);
console.log(result);

```

 **RegExp.prototype.exec()** 

这个方法接收一个用于匹配的字符串，返回一个 array，array 存放返回的结果。

例如：

```js

var regex = /hello/;
var str = 'hello world';
var result = regex.exec(str);
console.log(result);
// returns [ 'hello', index: 0, input: 'hello world', groups: undefined ]
// 'hello' -> is the matched pattern.
// index: -> Is where the regular expression starts.
// input: -> Is the actual string passed.

```

本文主要使用 test() 来进行测试。

## 简单的正则表达式

这是最基本的模式，用于简单地将文本和测试字符串进行匹配，例如：

```js

var regex = /hello/;
console.log(regex.test('hello world'));
// true

```

## 特殊字符

 **Flags：** 

正则表达式有五个可选的标志（flags）或修饰符（modifiers）。首先是

g: 全局搜索，当成功匹配后不会直接返回。

i: 不区分大小写搜索。

一个正则表达式可以有多个 Flags 修饰，并且 Flags 的顺序不会影响最终的结果。

例如：

```js

var regexGlobal = /abc/g;
console.log(regexGlobal.test('abc abc'));
// it will match all the occurence of 'abc', so it won't return 
// after first match.
var regexInsensitive = /abc/i;
console.log(regexInsensitive.test('Abc'));
// returns true, because the case of string characters don't matter 
// in case-insensitive search.

```

 **字符组（Character groups）：** 

character groups [xyz] 允许在同一个位置匹配多个字符，只需要满足其中的一个就算匹配成功。例如：

```js

var regex = /[bt]ear/;
console.log(regex.test('tear'));
// returns true
console.log(regex.test('bear'));
// return true
console.log(regex.test('fear'));
// return false

```

与之相反我们还可以在 character groups 中添加 (^) 表示不匹配字符组中的字符，例如：

```js

var regex = /[^bt]ear/;
console.log(regex.test('tear'));
// 包含 t， returns false
console.log(regex.test('bear'));
// 包含 b，return false
console.log(regex.test('fear'));
// b 和 t 都不包含，return true

```

 **Ranges[a-z] ** 

假设我们想要匹配所有的字母，我们可以在 [] 中添加所有的字母，这显然不是好的做法， 可以使用 [a-z] 表示所有的字母，例如：

```js

var regex = /[a-z]ear/;
console.log(regex.test('fear'));
// returns true
console.log(regex.test('tear'));
// returns true

```

 **元字符 Meta-characters ：** 

元字符是用来表示有特殊含义的字符，可以大大的简化表达式。

* \t   用于匹配 tab
* .    匹配除换行符之外的任何字符
* \d  等价于 [0-9]
* \D 等价于`[^0–9]`
* \w 等价于 [a-zA-Z0–9_] 
* \W 等价于`[^a-zA-Z0–9_]`
* \b  用于匹配单词的边界, 即 \w 和 \W 之间的位置
* \s  用于匹配空白字符（空格 或 tab）
* \S 匹配非空白的字符

 **量词 Quantifiers：** 

* + ：匹配一个或多个字符，例如：

```js

var regex = /\d+/;
console.log(regex.test('8'));
// true
console.log(regex.test('88899'));
// true
console.log(regex.test('8888845'));
// true

```

* * 匹配 0 个或多个字符，例如：

```js

var regex = /go*d/;
console.log(regex.test('gd'));
// true
console.log(regex.test('god'));
// true
console.log(regex.test('good'));
// true
console.log(regex.test('goood'));
// true

```

* ? 匹配 0 个或者 1 个字符，例如：

```js

var regex = /goo?d/;
console.log(regex.test('god'));
// true
console.log(regex.test('good'));
// true
console.log(regex.test('goood'));
// false

```

* ^ 匹配字符串的开头。例如：

```js

var regex = /^g/; // 字符串的开头必须是 g
console.log(regex.test('good'));
// true
console.log(regex.test('bad'));
// false
console.log(regex.test('tag'));
// false

```

* $ 匹配字符串的结尾。例如：

```js

var regex = /.com$/; // 必须以 .com 结尾
console.log(regex.test('test@testmail.com'));
// true
console.log(regex.test('test@testmail'));
// false

```

* {N} 匹配某字符出现 N 次数，例如：

```js

var regex = /go{2}d/; // o 必须连着出现两次
console.log(regex.test('good'));
// true
console.log(regex.test('god'));
// false

```

* {N,} 匹配字符连续出现次数大于 N 次的字符串，例如：

```js

var regex = /go{2,}d/;
console.log(regex.test('good'));
// true
console.log(regex.test('goood'));
// true
console.log(regex.test('gooood'));
// true

```

* {N, M} 匹配字符连续出现次数必须大于 N 次但不能多于 M 的字符串，例如：

```js

var regex = /go{2,}d/;
console.log(regex.test('good'));
// true
console.log(regex.test('goood'));
// true
console.log(regex.test('gooood'));
// true

```

 **可选择的 Alternation X|Y：** 

匹配 X 或者 Y 例如：

```js

var regex = /green|red apple/;
console.log(regex.test('green apple'));
// true
console.log(regex.test('red apple'));
// true
console.log(regex.test('blue apple'));
// false

```

## 进阶

* （x）匹配 x 并记住匹配（捕获组），可以用来在正则表达式中创建子表达式：

```js

var regex = /(foo)bar\1/;   // \1 表示括号内的表达式 foo
console.log(regex.test('foobarfoo'));
// true
console.log(regex.test('foobar'));
// false

```

* （?:x） 匹配并且不记得表达式（非捕获组），这是 \1 就不起作用：

```js

var regex = /(?:foo)bar\1/;
console.log(regex.test('foobarfoo'));
// false
console.log(regex.test('foobar'));
// false
console.log(regex.test('foobar\1'));
// true

```

* **x(?=y) ** 仅当 x 后面紧跟 y 才满足匹配，例如：

```js

var regex = /Red(?=Apple)/;
console.log(regex.test('RedApple'));
// true

```

## 正在表达式实战

* 匹配任何 10 个数字的字符串，并且字符串开头和结尾都是数字：

```js

var regex = /^\d{10}$/;
console.log(regex.test('9995484545'));
// true

```

* 匹配数据格式`DD-MM-YYYY`或`DD-MM-YY`

```js

var regex = /^(\d{1,2}-){2}\d{2}(\d{2})?$/;
console.log(regex.test('01-01-1990'));
// true
console.log(regex.test('01-01-90'));
// true
console.log(regex.test('01-01-190'));
// false

```

* 匹配`abc.def.ghi.jkl`格式的字符串（abcdefghijkl 不包含换行符） 

```js

var regex = /^(.{3}\.){3}.{3}$/;
console.log(regex.test('123.456.abc.def'));
// true
console.log(regex.test('1243.446.abc.def'));
// false
console.log(regex.test('abc.def.ghi.jkl'));
// true

```

原文：[A Practical Guide to Regular Expressions (RegEx) In JavaScript][1]

 **极光日报，[极光开发者][2]旗下媒体。** 

 **每天导读三篇英文技术文章。** 

[1]: https://link.zhihu.com/?target=https%3A//blog.bitsrc.io/a-beginners-guide-to-regular-expressions-regex-in-javascript-9c58feb27eb4
[2]: https://link.zhihu.com/?target=http%3A//y0.cn/6AAFc

[0]: https://pic1.zhimg.com/v2-88f21cc377cb215d2d26e8200b0ab850_1200x500.jpg