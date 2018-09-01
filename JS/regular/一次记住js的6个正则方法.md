## 一次记住js的6个正则方法

来源：[http://varnull.cn/yi-ci-ji-zhu-jsde-6ge-zheng-ze-fang-fa/](http://varnull.cn/yi-ci-ji-zhu-jsde-6ge-zheng-ze-fang-fa/)

时间 2018-02-12 13:03:18


![][0] 
 
我时常感到困惑，为什么有些知识我总是觉得模糊，其实就是想的少，总结的少，大多数人也如此，有疑惑不清楚就找出来，想明白或者想不明白都记录下来自己的收获，比扭头忘记还是要好很多吧。。好我觉得js中的正则我不是很清楚，那么来看一下吧。
 
首先6这个具象的数字可以帮助我们整体记忆了，666哈哈
 
#### 范围
 
  
js中有两个类可以让正则发挥作用
  

![][1] 
 
 
#### 创建

```js
var re = /ab+c/
```
 
方式一：正则表达字面量，这种直接是常量的表示用法可以让js解析器提高性能

```js
var re = new RegExp('ab+c')
```
 
方式二：构造函数，这种方式可以在runtime的时候动态确定正则是什么，更加灵活
 
#### 常用特殊字符
 
来记忆一些常用特殊字符，这个是正则本身的范畴了，是不是总觉得记不住？其实我也记不住，每次都是去搜索和online验证来完成一些任务。我也困恼过，其实最后还是因为自己写的少吧，唯手熟尔。。。下面的总结不写具体内容，只列出具体特殊字符和分类，可以尝试一下说出他们的意义，我觉得比看表格更有利于记忆。。。
 
 
* 匹配量的：`* + ? {n} {n,} {n,m} .` 
* 匹配位置的：`^ $` 
* 匹配并且需要支持分组的时候需要括号来包裹：`(匹配的模式) `
* 匹配条件的：`|` 
* 匹配集合的：`[]` 
* 匹配非集合的：`[^] `
 
 
还有大量的由`\`和字母组成的特殊含义的匹配模式，这些用到的时候查询就可以了，没有必要记住，其实我是记不住。。。
 
#### 例子
 
例子是最好的老师。。。。 例子来源于MDN
 
 
* 我想得到匹配后的数组 
 

```js
var myRe = /d(b+)d/g;  
myRe.exec('cdbbdbsdbdbz') // ["dbbd", "bb", index: 1, input: "cdbbdbsdbdbz"]  
myRe.exec('cdbbdbsdbdbz') // ["dbd", "b", index: 7, input: "cdbbdbsdbdbz"]  
myRe.exec('cdbbdbsdbdbz') // null
```
 
注意对于每个正则对象的exec每次调用都只返回一个匹配，如果需要拿到全部匹配就需要while循环获取，循环结束标志是返回值为null

```js
'cdbbdbsdbdbz'.match(/d(b+)d/g) // ["dbbd", "dbd"]  
'cdbbdbsdbdbz'.match(/d(b+)d/) // ["dbbd", "bb", index: 1, input: "cdbbdbsdbdbz"]
```
 
string的match挺奇怪的，如果是global匹配则出所有匹配的数组，如果不是，则出第一个匹配的字符串，以及相应的捕获内容
 
 
* 我想得到是否匹配 
 

```js
var str = 'hello world!';  
var result = /^hello/.test(str); // true
```
 
 
* 我只想得到第一次匹配的位置 
 

```js
'cdbbdbsdbdbz'.search(/d(b+)d/) // 1  
'xxx'.search(/d(b+)d/) // -1 没有匹配
```
 
 
* 我想按照匹配拆分字符串 
 

```js
var names = 'Harry Trump ;Fred Barney; Helen Rigby ; Bill Abel ;Chris Hand ';  
var re = /\s*;\s*/;  
var nameList = names.split(re);  
// [ "Harry Trump", "Fred Barney", "Helen Rigby", "Bill Abel", "Chris Hand " ]
```
 
 
* 我想按照匹配覆盖字符串 
 

```js
var re = /apples/gi;  
var str = 'Apples are round, and apples are juicy.';  
var newstr = str.replace(re, 'oranges');  
// // oranges are round, and oranges are juicy.
```
 
这个replace方法的用法着实比较多，只放了最基础用法，当有需求的时候再查就好了，整体有概念了再实践比强行记忆要好吧~
 

[0]: ./img/rIbAjy.png 
[1]: ./img/UnMJfuz.png 