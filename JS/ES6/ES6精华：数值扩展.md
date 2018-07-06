## ES6精华：数值扩展

来源：[https://segmentfault.com/a/1190000015386211](https://segmentfault.com/a/1190000015386211)

`ES6`为数值增加了些常量和方法，使计算更为简便安全。本篇概括了这中的精华知识。
## 1 基础
### 1.1 极值

JS采用`IEEE 754`标准的64位双精度格式存储数值。  
数值的精度最多可达到`53`个二进制位（1个隐藏位和52个有效位）。  
如果数值的精度超过此限度，第`54`位及后面的会被丢弃。

数值的极值分为两种：可表示的极值和可精确计算的极值（浮点型不算）。  
可表示的极值：`[5e-324, 1.7976931348623157e+308]`。  
可精确计算的极值：`[1 - Math.pow(2, 53), Math.pow(2, 53) - 1]`。

```js
超过精度的数值可正确显示，但由其计算得出的结果可能不准确。

let num = 9007199254741002;
console.log( num ); // 9007199254741002
console.log( num + 1 ); // 9007199254741004
console.log( num + 3 ); // 9007199254741004

let n1 = Math.pow(2, 53) - 1 + 1 + 1;
let n2 = Math.pow(2, 53) - 1 + 1 + 2;
console.log(n1 === n2); // true
```

对于整数，最多能精确显示`16`个十进制位，超过会被截断。  
对于小数，最多能精确显示小数点后`16`个十进制位，超过会被截断。

```js
超过的位数会被截断。

console.log( 3.000000000000001 === 3 ); // false
console.log( 3.0000000000000001 === 3 ); // true
console.log( 0.123456789123456891 ); // 0.1234567891234569
```
### 1.2 进制

二进制：`0b100`或`0B`。  
八进制：`0o100`或`0O`或`0100`。  
十六进制：`0x100`或`0X100`。  
注意，可忽略`0100`格式表八进制，因为严格模式下不允许使用。
 **`进制间的转化`**   
使用进制的完整格式，通过`toString`在不同进制间转化。

```js
console.log( (10).toString(2) ); // 1010
console.log( (0b100).toString(8) ); // 4
console.log( ('0o100').toString(16) ); // 40
```

使用进制的值，通过`parseInt`将其它进制转换成十进制。

```js
console.log( parseInt(100, 2) ); // 4
console.log( parseInt(100, 8) ); // 64
console.log( parseInt('100', 16) ); // 256
```

使用进制的完整格式，通过`Number`将其它进制转化成十进制。

```js
console.log( Number(0b100) ); // 4
console.log( Number('0o100') ); // 64
console.log( Number('0x100') ); // 256
```
## 2 Number

完整的API列表：[地址][0]。  
此模块的方法，不会默认转化期待为数值类型而实际不是的参数。
### 2.1 模块化

将全局方法`isFinite() & isNaN()`，放到了`Number`模块下。  
两者唯一的差别是，全局中的方法会默认转化非数值参数，`Number`模块下的不会。

```js
console.log( isNaN('NaN') ); // true
- 等价于
console.log( isNaN(Number('NaN')) );

只要不是 NaN ，则为 false 。更为严格严谨。
console.log( Number.isNaN('NaN') ); // false
```
### 2.2 整数

增加了一些常量和方法为安全计算服务。
 **`isInteger()`**   
判断一个数值是否为整数。非数直接为`false`。  
在JS中，整数和浮点数的储存方式是相同的，所以`25`和`25.0`被视为同一个值。

```js
console.log( Number.isInteger('25') ); // false
console.log( Number.isInteger(25.0) ); // true
console.log( Number.isInteger(3.0000000000000002) ); // true
```
 **`isSafeInteger()`**   
判断整型数值是否处于安全区间内。非整型即为`false`。  
整型数值安全区间：`[Number.MIN_SAFE_INTEGER, Number.MAX_SAFE_INTEGER]`。  
判断一个算式及其结果是否安全，需要验证它的各个项以及结果。

```js
isTrusty(9007199254740993, 990, 9007199254740993 - 990); // 报错

function isTrusty(left, right, result) {
  if (Number.isSafeInteger(left)
    && Number.isSafeInteger(right)
    && Number.isSafeInteger(result)) {
    return result;
  }
  throw new RangeError('Operation cannot be trusted!');
}
```
### 2.3 误差

JS能识别的最小精度为`Number.EPSILON`，即`Math.pow(2, -52)`。  
如果误差小于此精度，就可以认为这点误差已经没有意义，即不存在误差了。  
在实际项目中，可以设置计算的容错误差，以对比两个浮点数应不应该相同等等。

```js
console.log( 0.1 + 0.2 ); // 0.30000000000000004
console.log( (0.1 + 0.2) === 0.3 ); // false
console.log( isEqualInErrorRange(0.1 + 0.2, 0.3) ); // true

function isEqualInErrorRange(left, right) {
  return Math.abs(left - right) < Number.EPSILON;
}
```

设定需要精确的位数，将浮点型转化成整型，来较为安全的计算浮点数。

```js
console.log( countFloat(0.1, 0.2, '+', 14) ); // 0.3

function countFloat(a, b, sign, num) {
  let res;
  let times = Math.pow(10, num);
  let _a = Math.floor(a * times);
  let _b = Math.floor(b * times);
  
  switch (sign) {
    case '-':
      res = isTrusty(_a, _b, _a - _b);
      break;
    case '+':
      res = isTrusty(_a, _b, _a + _b);
      break;
    case '/':
      res = isTrusty(_a, _b, _a / _b);
      break;
    case '*':
      res = isTrusty(_a, _b, _a * _b);
      break;
  }
  
  return res / times;
}
```
## 3 Math

完整的API列表：[地址][1]。  
此模块的方法，会默认调用`Number()`转化，期待为数值类型而实际不是的参数。  
此模块新增了些，可以自行实现的简易方法，直接查手册会更有效，就不列举了。

[0]: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Number
[1]: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Math