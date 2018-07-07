## ESLint规范选讲

来源：[http://feclub.cn/post/content/eslint](http://feclub.cn/post/content/eslint)

时间 2018-06-22 16:28:52



### 1. ESLint 规范选讲


#### 1.1 References

1.1.1 优先使用 const 来声明变量; 避免使用 var.



* eslint: prefer-const, no-const-assign
  

1.1.2 如果申明的变量必须要改变, 使用 let.



* eslint: no-var
  

针对不需要改变的变量，优先使用 const，这样可以保证不会在其它地方意外地改变这个值或者引用。

```js
// bad
var a = 1
var b = {}

// :+1:
const a = 1
const b = {}
```

```js
// bad
var count = 1
if (true) {
  count += 1
}

// good, use the let.
let count = 1
if (true) {
  count += 1
}
```


#### 1.2 Objects

1.2.1 Use property value shorthand.



* eslint: object-shorthand
  

```js
const lukeSkywalker = 'Luke Skywalker'

// bad
const obj = {
  lukeSkywalker: lukeSkywalker
}

// good
const obj = {
  lukeSkywalker
}
```

1.2.2 浅拷贝时使用拓展运算符，而不是 Object.assign

```js
// bad
const original = { a: 1, b: 2 }
const copy = Object.assign({}, original, { c: 3 }) // copy => { a: 1, b: 2, c: 3 }

// good
const original = { a: 1, b: 2 }
const copy = { ...original, c: 3 } // copy => { a: 1, b: 2, c: 3 }
```

拓展运算符在类数组转换和数组去重中的运用


#### 1.3 Arrays

1.3.1 使用拓展运算符复制数组。

```js
// bad
const len = items.length
const itemsCopy = []
let i

for (i = 0; i < len; i += 1) {
  itemsCopy[i] = items[i]
}

// good
const itemsCopy = [...items]
[...new Set(arr)]
```

1.3.2 使用...代替 Array.from 来进行类数组至数组的转换。

```js
const foo = document.querySelectorAll('.foo')

arguments
// good
const nodes = Array.from(foo)

// best
const nodes = [...foo]
```


#### 1.4 Destructuring

1.4.1 对象的解构赋值



* eslint: prefer-destructuring
  

```js
// bad
function getFullName(user) {
  const firstName = user.firstName
  const lastName = user.lastName

  return `${firstName} ${lastName}`
}

// good
function getFullName(user) {
  const { firstName, lastName } = user
  return `${firstName} ${lastName}`
}

// best
function getFullName({ firstName, lastName }) {
  return `${firstName} ${lastName}`
}
```

1.4.2 数组的解构赋值



* eslint: prefer-destructuring
  

```js
const arr = [1, 2, 3, 4]

// bad
const first = arr[0]
const second = arr[1]

// good
const [first, second, ...rest] = arr
```

1.4.3 优先使用模版字符串

```js
// bad
function sayHi(name) {
  return 'How are you, ' + name + '?'
}

// bad
function sayHi(name) {
  return ['How are you, ', name, '?'].join()
}

// bad
function sayHi(name) {
  return `How are you, ${name}?`
}

// good
function sayHi(name) {
  return `How are you, ${name}?`
}
```


#### 1.5 Functions

1.5.1 合理使用函数参数默认值

```js
// really bad
function handleThings(opts) {
  opts = opts || {}
  // ...
}

// still bad
function handleThings(opts) {
  if (opts === void 0) {
    opts = {}
  }
  // ...
}

// good
function handleThings(opts = {}) {
  // ...
}
```

1.5.2 不要直接改变函数参数. eslint: no-param-reassign

```js
// bad
function f1(obj) {
  obj.key = 1
}

// good
function f2(obj) {
  const key = Object.prototype.hasOwnProperty.call(obj, 'key') ? obj.key : 1
}
```

```js
// bad
function f1(a) {
  a = 1
  // ...
}

function f2(a) {
  if (!a) {
    a = 1
  }
  // ...
}

// good
function f3(a) {
  const b = a || 1
  // ...
}

function f4(a = 1) {
  // ...
}
```


#### 1.5 Classes

1.5.1 使用 Class 和 extends



* 简洁易于理解，语义性强
  

```js
// bad
function Queue(contents = []) {
  this.queue = [...contents]
}
Queue.prototype.pop = function() {
  const value = this.queue[0]
  this.queue.splice(0, 1)
  return value
}

// good
class Queue {
  constructor(contents = []) {
    this.queue = [...contents]
  }
  static pop() {
    const value = this.queue[0]
    this.queue.splice(0, 1)
    return value
  }
}
```

```js
// bad
const inherits = require('inherits')
function PeekableQueue(contents) {
  Queue.apply(this, contents)
}
inherits(PeekableQueue, Queue)
PeekableQueue.prototype.peek = function() {
  return this.queue[0]
}

// good
class PeekableQueue extends Queue {
  peek() {
    return this.queue[0]
  }
}
```

1.6.2 使用方法执行链

```js
// bad
Jedi.prototype.jump = function() {
  this.jumping = true
  return true
}

Jedi.prototype.setHeight = function(height) {
  this.height = height
}

const luke = new Jedi()
luke.jump() // => true
luke.setHeight(20) // => undefined

// good
class Jedi {
  jump() {
    this.jumping = true
    return this
  }

  setHeight(height) {
    this.height = height
    return this
  }
}

const luke = new Jedi()

luke.jump().setHeight(20)
```


#### 1.final



* 合理使用编辑器的 eslint fix 功能
* 格式化不要使用自己的个性化配置，按照项目内的 eslint 配置  进行格式化
  


### 2. 代码重构

2.1 提炼函数



* 避免超大函数
* 利于代码复用
* 利于单元测试
  

```js
const getInfo = function(params) {
  ajax('http://baidu.com/api', data => {
    global.name = data.name
    global.age = data.age
    global.sex = data.sex
  })
}

// 抽离
const getInfo = function(params) {
  ajax('http://baidu.com/api', data => {
    setInfo(data)
  })
}

const setInfo = function(data) {
  global.name = data.name
  global.age = data.age
  global.sex = data.sex
}
```

2.2 合并重复条件



* 例如函数体内有一些分支条件，每个分支条件内散步了一些重复的代码
  

```js
const paging = function(curPage) {
  if (curPage <= 0) {
    curPage = 0
  } else if (curPage >= totalPage) {
    curPage = totalPage
  }
  jump(curPage)
}
```

2.3 条件抽离



* 复杂的判断条件应该抽离成单独的函数
  

```js
const getPrice = function(goods) {
  if (goods.price > 10000 && goods.price < 20000 && goods.isCheap) {
    return goods.price * 0.8
  }
  return goods.price
}
```

```js
const isNeedDiscount = function(goods) {
  return goods.price > 10000 && goods.price < 20000 && goods.isCheap
}

const getPrice = function(goods) {
  if (isNeedDiscount(goods)) {
    return goods.price * 0.8
  }
  return goods.price
}
```

2.4 熟悉并运用各种数组和对象的方法

避免：



* 遍历数组只会 forEach 或者 for(){}
* 给数组添加元素只会用 push。

push()

push()

应该：

          
* 考虑 every、some、filter、map、reduce 等等

    
* 考虑 concat、unshift、splice 等等
  

2.5 事不过三原则



* 重复或者类似的条件和功能出现达到三次，这段代码就是很垃圾的代码。
* 经常出现在诸如判断接口 code，判断用户各种状态的场景中
  

```js
const cal = function(lev, money) {
  if (lev === 'A') {
    return money * 10
  }
  if (lev === 'B') {
    return money * 8
  }
  if (lev === 'C') {
    return money * 6
  }
  if (lev === 'D') {
    return money * 0
  }
}
```

```js
const calFuncMap = {
  A: money => money * 10,
  B: money => money * 8,
  C: money => money * 6,
  D: money => money * 0
}

calFuncMap['A'](5000)
```

```js
const calMap = {
  A: 10,
  B: 8,
  C: 6,
  D: 0
}

const cal = function(lev, money) {
  return money * calMap[lev]
}
```

2.5 提前退出,代替 if 嵌套

```js
if (a) {
  foo()
  if (b) {
    bar()
    if (c) {
      boo()
    }
  }
}
// good
if (!a) return
foo()
if (!b) return
bar()
if (!c) return
boo()
```

2.6 主动应用上述 ESLint 建议的内容



* 链式调用
* 解构复制
* 默认参数
* Class
* ...
  


### 2.7 态度端正，对自己写的代码负责


