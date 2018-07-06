## ES6精华：解构赋值

来源：[https://segmentfault.com/a/1190000015072149](https://segmentfault.com/a/1190000015072149)

按一定的匹配模式，从数组或对象中解构出相应值，并赋值给变量。

```js
let [a] = [3]; // a = 3
let [, a] = [3, [7]]; // a = [7]
let {a} = {a: 3}; // a = 3，{a} 相当 {a: a}
let {a: {b}} = {a: {b: 3}}; // b = 3
```
### 应用举例
 **`快速的声明并赋予相应的属性值`** 

```js
// --- 以前
let id = obj.id;
let name = obj.name;
let ago = obj.ago;

// --- 现在
let { id, name, ago } = obj;
```
 **`函数配置参数的解构和赋默认值`** 

```js
// --- 以前
function dealUser(id, conf) {
  let name = conf.name || '';
  let ago = conf.ago || 0;
}

// --- 现在
// 可以直接使用 name 等，以及设置默认值（类型也易见）。
function dealUser(id, {
  name = '',
  ago = 0
}) {
  // 函数体
}
```
### 解构非对象

当解构的目标为非对象时，会将目标转化成相应类型的对象。  
`NaN`可以使用`Number`构造函数生成，可以被解构。  
`null`和`undefined`是单值，没有相应的构造函数，不能被解构。

```js
let {length: a} = 'ab'; // a = 2
// 等价于
let {length: a} = new String('ab'); // a = 2

let {toString: a} = NaN; // a = function
let {toString: a} = null; // 报错
```
### 解构方式

左侧的解构符决定如何看待右侧的解构值。  
解构符`{}`意味着视右侧的值为对象，采用对象解构。  
解构符`[]`意味着视右侧的值为数组，采用数组解构。  
以此可以推断：数组即支持数组解构也支持对象解构。

原生类数组对象有迭代接口，也支持两种解构。（`arguments`,`NodeList`,`new String()`）

```js
let [a] = 'ab'; // a = 'a'，a 为第一个元素。
let {length: a} = 'ab'; // a = 2
let {length: a} = ['a', 'b']; // a = 2
let [a] = {0: a, length: 1}; // 报错，自定义对象没有迭代接口。
```
### 解构失败
#### 解构不成功

右侧没有相对应的值，解构不报错，变量值为`undefined`。

```js
let [a, b] = [1]; // a = 1, b = undefined
```
#### 解构出错

当右侧值（包括转换后）不满足左侧要求的类型时，解构失败。

```js
let [[a]] = [1]; // 报错，目标 1 不是数组。
let [a] = {a: 3}; // 报错，目标 {a: 3} 不是数组。
```
### 指定默认值

可以为待赋值的变量指定默认值。  
默认值可以使用解构中其他变量，但该变量的解构必须在此之前。

```js
let [a, b = 2] = [1]; // a = 1, b = 2
let [a, b = a] = [1]; // a = 1, b = 1
```
