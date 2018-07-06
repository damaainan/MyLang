## javascript中!=、!==、==、===操作符总结

来源：[http://www.cnblogs.com/weiqinl/p/9049745.html](http://www.cnblogs.com/weiqinl/p/9049745.html)

时间 2018-05-17 10:48:00

 
JavaScript 有两种比较方式：严格比较运算符和转换类型比较运算符。
 
在相等运算符中对应`===`、`!==`和`==`、`!=`。
 
## 先举个栗子
 
```js
var str = '1'
var num0 = 0
var num1 = 1
var blT = true
var blF = false
var nul = null
var und = undefined
console.log(str == num1) // true
console.log(str == blT) // true
console.log(blT == num1) // true
console.log(blF == num0) // true
console.log(nul == und) // true

console.log(str === num1) // false
console.log(str === blT) // false
console.log(blT === num1) // false
console.log(blF === num0) // false
console.log(nul === und) // false
```
 
相等操作符(`==`)会为两个不同类型的操作数进行类型转换，然后进行严格比较。
 
严格相等操作符(`===`),一般也叫做全等操作符。会先判断类型，再比较值是否相等。
 
## 类型转换
 
类型转换的途径:
 
| 类型(x) | 类型(y) | 结果 | 
| undefined | null | true | 
| 字符串 | 数字 | toNumber(x) == y | 
| 布尔值 | 数字 | toNumber(x) == y | 
| 对象 | 字符串/数字 | toPrimary(x) == y | 
 
 
对于两个类型不同的操作数比较。
 
 
* 字符串、布尔值都会先转换成数字类型，再做比较。`toNumber(x)` 
* 对于复杂数据类型，会先将其转换为原始值，之后，再根据上一个规则比较。 
`x = toPrimary(obj) ==> toNumber(x)`
 而，如何转成原始类型值呢，一般都会自动通过 [ 自带的 valueOf() 方法 ][1] 或者`toString()`方法实现。如果转换之后非原始值，比较操作会报类型错误。  
 
 
```js
具体过程：
先执行`valueOf`方法，如果该方法返回一个原始值，则将这个原始值转换为数字，并返回这个数字，转换过程结束。如果返回非原始值，继续下一步。
否则，执行`toString`方法，如果该方法返回一个原始值，则将这个原始值转换为数字，并返回这个数字，转换过程结束。如果返回非原始值 ，继续下一步。
以上都没有成功转换为原始值，则抛出一个类型转换错误的异常。
tips： 每个方法只执行一次。不会将方法返回的非原始类型值继续转换。
```
 
举个例子说明下，参考于 [知乎][2] :
 
![][0]
 
原始数据类型(string,number,boolean,null, undefined,symbol)。
 
复杂数据类型(Object, Function, Array, Date, ...)
 
基础数据类型的比较，是值的比较，Object对象的比较，则是引用的比较
 
相等操作符(`==`)，经过类型转换之后，才比较他们的值或者对象值。
 
对于全等操作符(`===`)，等号两边的值和类型，必须完全相等。
 
## 为什么建议使用`===`### 1. review代码时候，增加理解时间
 
在使用了`==`的表达式中，我们需要先理解作者的意图。
 
 
* 想当然的以为都可以。 
* 确实需要通过类型转换来判断。 
* 不应该类型转换，但是写错了。 
 
 
### 2. 会判断错误
 
```js
let num = 2
let obj = {
  valueOf: function() {
    return 2
  }
}
console.log(obj == 2)
```
 
输出`true`，
 
我们本意是这两者`!=`，而这里得到的结果是`==`，这不是我们想要的结果。
 
### 3. 会产生异常
 
```js
let num = 2
let obj = {
  valueOf: function() {
    return {}
 },
 toString: function() {
  return {}
 }
}
console.log(obj === 2)
console.log(obj == 2)
```
 
第一行输出：`false`
 第二行输出错误提示：`Uncaught TypeError: Cannot convert object to primitive value`通过前面类型转换，可以得知，一般情况下，对象会先转换为原始值。
 
而其过程是通过自带的`valueOf()/toString()`先转换为primitive value，再和其他值做比较。
 
而在这里，我们手动将obj对象的`valueOf()/toString()`覆盖了，导致无法实现转换为原始值。
 
一般情况下，建议使用`===`，除非你了解，确实需要类型转换，才使用`==`## 条件表达式语句（if、三目运算等）
 
```js
if (condition) {
    statement1 
} else {
    statement2
}
```
 
以上是if语句的基础用法。通过判断`condition`的布尔值，来决定执行`statement1`代码块1，还是执行`statement2`代码块2。
 
先看下面的例子：
 
```js
var s = 'str'
var blT = true
var blF = false
if (s) {
    console.log('正确')
} else {
    console.log('错误')
}
console.log(s == blT)
```
 
以上语句，得到的结果是
 
```js
正确
false
```
 
为什么if语句，会执行第一个代码块。而`s == blT`却是false呢？
 
其实，这个就涉及到类型转换的问题了。
 
输出`“正确”`：
 
 
* if语句的条件表达式，会自动调用`Boolean()`转换函数，将这个表达式的结果转换为一个布尔值。  
* Boolean('str') = true 
 
 
输出`false`：
 
 
* 根据在上面类型转换那部分所讲，会先调用`Number()`转换函数转换为数值，之后再比较。  
* Number('str') = NaN 
* Number(true) = 1 
 
 
## 图表举例列出常见对象相等情况
 
  
[普通相等][3]
 
  [完全相等][4] 
 
 
【完】
 


[1]: http://weiqinl.com/2018/03/31/JavaScript%E5%AF%B9%E8%B1%A1%E7%9A%84valueOf-%E6%96%B9%E6%B3%95/
[2]: https://www.zhihu.com/question/277243339/answer/392788506
[3]: https://codepen.io/weiqinl/pen/YaovMp
[4]: https://codepen.io/weiqinl/details/KojBPb
[0]: https://img0.tuicool.com/U7fuEfz.png 