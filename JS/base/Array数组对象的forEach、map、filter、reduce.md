## Array数组对象的forEach、map、filter、reduce

来源：[https://segmentfault.com/a/1190000015849866](https://segmentfault.com/a/1190000015849866)

刚才某人问了我一个问题。`map`怎么遍历，我刷刷刷就是一顿写。遍历么，`forEach`么，妥妥的。

```js
var map = new Map();
map.set('item1', 'value1')
map.set('item2', 'value2')
map.forEach(function(value, key, map) {
  console.log("Key: %s, Value: %s", key, value);
});
```

好吧，我写完了之后，他发给我了一句话。`[].forEach()`改成`[].map()`怎么用？
 **`what?我这个暴脾气`** 。。。。我当然是详细的说一下`Array`的常规遍历方法以及场景了。
## Array.filter
### 语法

```js
var new_arr = arr.filter(callback(element, index, array){

}, this)
```
#### 参数

```
callback 回调
    element 当前的value
    index   当前的索引值
    array   arr这个数组对象
this 回调的this指向
```
#### 返回值

```
Array 类型
//符合条件的值组成的数组
```
### 用法

```js
//如果返回值是true的话，就是符合条件。
//filter 不会改变原数组，它返回过滤后的新数组。
//这个里返回数组里面的偶数
[10,11,12,13].filter((v)=>v % 2 == 0)
//只要审核通过的。当然正常情况下，对象比这个复杂一些。
[{state:1},{state:0},{state:0},{state:0}].filter((v)=>v.state == 1)
//只要成年人，记录是有效的
[{age:18,state:1},{age:16,state:0},{age:21,state:0}].filter((v)=>v.state == 1 && v.age > 17)
```
### 场景

场景就是过滤，把符合条件的整理到一起，常见的就是展示审核通过的数据，只显示关注我的人，只显示妹子，对吧糙汉子就过滤不看了。
## Array.forEach
### 语法

```js
arr.forEach(callback(element, index, array){

}, this)
```
#### 参数

```
callback 回调
    element 当前的value
    index   当前的索引值
    array   arr这个数组对象
this 回调的this指向
```
#### 返回值

```
undefined
// 这个东西没有返回值
```
### 用法

```js
//遍历数组。打印到控制台
[10,11,12,13].forEach((v)=>{
    console.log(v)
})
// 成功的收集到success里面,错误的收集到error里面。
var success = [],error = [];
[{state:1},{state:0},{state:0},{state:0}].forEach((v)=>{
    if(v.state == 1){
        success.push(v)
    }else{
        error.push(v)
    }
})
// 给20岁的小姐姐打招呼
[{state:1,age: 1},{state:0,age: 20},{state:0,age: 19},{state:0,age: 31}].forEach((v)=>{
    if(v.age == 20){
        console.log('你好啊，我今年正好80')
    }
})
```
### 场景

比如说绑定事件，比如判断值然后`push`到不同的地方
## Array.map
### 语法

```
arr.map(callback(element, index, array){

}, this)
```
#### 参数

```
callback 回调
    element 当前的value
    index   当前的索引值
    array   arr这个数组对象
this 回调的this指向
```
#### 返回值

```
array 数组
// 每个回调的返回值组成的新数组
```
### 用法

```js
//把数值格式化，保留两位小数
[10.055,11.054,12.056,13.789].map((v)=>+v.toFixed(2))
```
### 场景

这个一般就用在，我需要一组值，但是这个值不对，需要计算原数组来生成。
## Array.reduce
### 语法

```
arr.reduce(callback(accumulator, element, index, array){

}, initialValue)
```
#### 参数

```
callback 回调
    sum     累加器的返回值，也就是上一次回调的返回值
    element 当前的value
    index   当前的索引值
    array   arr这个数组对象
initialValue 初始传入的值，如果不传回调从下标1开始，下标0作为初始值
```
#### 返回值

```
//返回最后一次回调的值
```
### 用法

```js
//累加
[10,11,12,13].reduce((s,v)=>s+v,0)
```
### 场景

这个计算整个数组得出一个值的
## 对比

forEach没有返回值，重点是function里面处理逻辑
map有返回值，重点是function返回值，组成新数组
filter有返回值，重点是function返回值，过滤之后组成新数组
reduce有返回值，重点是计算数组，返回一个值


-----

昨天晚上下班着急跑路，还差一些例子没往上整理，今天补上
## 例子

大家可以尝试写写，有好的例子能更好的说明函数的作用也可以在评论区提出来，有好的解决方案也可以写出来。
### 有一组用户信息按手机号降序排序，输出用户名称，用逗号分隔

```js
[{name: 'l1', phone: '1507539'},{name: 'l2', phone: '1507540'},{name: 'l3', phone: '1507541'},{name: 'l4', phone: '1507538'}]
 .sort((n,m)=>n.phone<m.phone)
 .map(m=>m.name)
 .join(',')
```
### 给元素绑事件

```js
 [].slice.call(document.querySelectorAll('div'))
  .forEach(v=>v.addEventListener('click',e=>console.log(e.target.className)))
```
### 获取所有元素的class,过滤空串

```js
[].slice.call(document.querySelectorAll('*'))
 .map(v=>v.className)
 .filter(v=>v)
```
