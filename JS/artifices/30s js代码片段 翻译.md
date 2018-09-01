## 30s js代码片段 翻译

来源：[https://segmentfault.com/a/1190000012800677](https://segmentfault.com/a/1190000012800677)

这是对 github 上[30s代码片段][0]的翻译整理，由于作者的文档是通过脚本生成的，也就懒得去提pull了，整理了放到博客上供大家学习参考，后续会持续跟进翻译。
## Array

### Array concatenation (合并参数)
使用 `Array.concat()` 来连接参数中的任何数组或值。

```js
const arrayConcat = (arr, ...args) => arr.concat(...args);
// arrayConcat([1], 2, [3], [[4]]) -> [1,2,3,[4]]
```

### Array difference (取数组不同项)
以 `b` 创建 `Set`，然后使用 `Array.filter()` 过滤，只保留 `b` 中不包含的值。

```js
const difference = (a, b) => { const s = new Set(b); return a.filter(x => !s.has(x)); };
// difference([1,2,3], [1,2]) -> [3]
```

### Array intersection (取数组相同项)
以 `b` 创建 `Set`，然后使用 `Array.filter()` 过滤，只保留 `b` 中包含的值。

```js
const intersection = (a, b) => { const s = new Set(b); return a.filter(x => s.has(x)); };
// intersection([1,2,3], [4,3,2]) -> [2,3]
```

### Array union (合并数组去重)
用 `a` 和 `b` 的所有值创建一个 `Set` 并转换成一个数组。

```js
const union = (a, b) => Array.from(new Set([...a, ...b]));
// union([1,2,3], [4,3,2]) -> [1,2,3,4]
```

### Average of array of numbers (通过数组取平均值)
使用 `Array.reduce()` 将每个值添加到一个累加器，用值 `0` 初始化，除以数组的长度。

```js
const average = arr => arr.reduce((acc, val) => acc + val, 0) / arr.length;
// average([1,2,3]) -> 2
```

### Chunk array (数组切块)
使用 `Array.from()` 创建一个满足块的数量的新的数组。
使用 `Array.slice()` 将新数组的每个元素映射到 `size` 长度的块。
如果原始数组不能均匀分割，最后的块将包含剩余的元素。

```js
const chunk = (arr, size) =>
  Array.from({length: Math.ceil(arr.length / size)}, (v, i) => arr.slice(i * size, i * size + size));
// chunk([1,2,3,4,5], 2) -> [[1,2],[3,4],5]
```

### Compact (压缩)
使用 `Array.filter()` 去过滤掉假值（`false`, `null`, `0`, `""`, `undefined` 和 `NaN`）。

```js
const compact = (arr) => arr.filter(v => v);
// compact([0, 1, false, 2, '', 3, 'a', 'e'*23, NaN, 's', 34]) -> [ 1, 2, 3, 'a', 's', 34 ]
```

### Count occurrences of a value in array (计算数组中指定值出现的次数)
使用 `Array.reduce()` 去迭代数组，当值相同时，递增计数器。

```js
const countOccurrences = (arr, value) => arr.reduce((a, v) => v === value ? a + 1 : a + 0, 0);
// countOccurrences([1,1,2,1,2,3], 1) -> 3
```

### Deep flatten array (深度展开数组)
使用递归。
使用 `Array.reduce()` 获取所有不是数组的值，并将数组展开。

```js
const deepFlatten = arr =>
  arr.reduce((a, v) => a.concat(Array.isArray(v) ? deepFlatten(v) : v), []);
// deepFlatten([1,[2],[[3],4],5]) -> [1,2,3,4,5]
```

### Drop elements in array (删除数组中的元素)
循环访问数组，使用 `Array.shift()` 删除数组的第一个元素，直到函数的返回值为 `true`，返回其余的元素。

```js
const dropElements = (arr, func) => {
  while (arr.length > 0 && !func(arr[0])) arr.shift();
  return arr;
};
// dropElements([1, 2, 3, 4], n => n >= 3) -> [3,4]
```

### Fill array (填充数组)
使用 `Array.map()` 将 `start`（包含）和 `end`（不包含）之间的值映射为 `value`。
省略 `start` 将从第一个元素开始／省略 `end` 将在数组最后结束。

```js
const fillArray = (arr, value, start = 0, end = arr.length) =>
  arr.map((v, i) => i >= start && i < end ? value : v);
// fillArray([1,2,3,4],'8',1,3) -> [1,'8','8',4]
```

### Filter out non-unique values in an array (过滤掉数组中重复的值)
使用 `Array.filter()` 保证数组仅包含唯一值。

```js
const filterNonUnique = arr => arr.filter(i => arr.indexOf(i) === arr.lastIndexOf(i));
// filterNonUnique([1,2,2,3,4,4,5]) -> [1,3,5]
```

### Flatten array up to depth (展开指定深度的数组)
使用递归去递减深度。
使用 `Array.reduce()` 和 `Array.concat()` 来合并元素或数组。
基本情况下，当深度为 `1` 时停止递归。
省略第二个参数，展开深度为 `1`。

```js
const flattenDepth = (arr, depth = 1) =>
  depth != 1 ? arr.reduce((a, v) => a.concat(Array.isArray(v) ? flattenDepth(v, depth - 1) : v), [])
  : arr.reduce((a, v) => a.concat(v), []);
// flattenDepth([1,[2],[[[3],4],5]], 2) -> [1,2,[3],4,5]
```

### Flatten array (拼合数组)
使用 `Array.reduce()` 来获取内部所有元素并用 `concat()` 合并它们。

```js
const flatten = arr => arr.reduce((a, v) => a.concat(v), []);
// flatten([1,[2],3,4]) -> [1,2,3,4]
```

### Get max value from array (获取数组中的最大值)
使用 `Math.max()` 配合 `...` 扩展运算符去获取数组中的最大值。

```js
const arrayMax = arr => Math.max(...arr);
// arrayMax([10, 1, 5]) -> 10
```

### Get min value from array (获取数组中的最小值)
使用 `Math.max()` 配合 `...` 扩展运算符去获取数组中的最小值。

```js
const arrayMin = arr => Math.min(...arr);
// arrayMin([10, 1, 5]) -> 1
```

### Group by (条件分组)
使用 `Array.map()` 将数组的值映射到函数或属性名称。
使用 `Array.reduce()` 创建一个对象，其中的键是从映射的结果中产生的。

```js
const groupBy = (arr, func) =>
  arr.map(typeof func === 'function' ? func : val => val[func])
    .reduce((acc, val, i) => { acc[val] = (acc[val] || []).concat(arr[i]); return acc; }, {});
// groupBy([6.1, 4.2, 6.3], Math.floor) -> {4: [4.2], 6: [6.1, 6.3]}
// groupBy(['one', 'two', 'three'], 'length') -> {3: ['one', 'two'], 5: ['three']}
```

### Head of list (获取数组的首个元素)
使用 `arr[0]` 返回传递数组的第一个元素。

```js
const head = arr => arr[0];
// head([1,2,3]) -> 1
```

### Initial of list
使用 `arr,slice(0, -1)` 去返回去除最后一个元素的数组。

```js
const initial = arr => arr.slice(0, -1);
// initial([1,2,3]) -> [1,2]
```

### Initialize array with range (使用指定范围来定义数组)
使用 `Array(end-start)` 创建一个所需长度的数组，使用 `Array.map()` 来填充范围中的所需值。
你可以省略`start`，默认值为 `0`。

```js
const initializeArrayRange = (end, start = 0) =>
  Array.apply(null, Array(end - start)).map((v, i) => i + start);
// initializeArrayRange(5) -> [0,1,2,3,4]
```

### Initialize array with values (使用指定值来定义数组)
使用 `Array(n)` 创建一个所需长度的数组，使用 `fill(v)` 去填充所需要的值。
亦可以省略 `value`，默认值为 `0`。

```js
const initializeArray = (n, value = 0) => Array(n).fill(value);
// initializeArray(5, 2) -> [2,2,2,2,2]
```

### Last of list (获取数组的结尾)
使用 `arr.slice(-1)[0]` 获得给定数组的最后一个元素。

```js
const last = arr => arr.slice(-1)[0];
// last([1,2,3]) -> 3
```

### Median of array of numbers (获取数组的中间值)
找到数组的中间，使用 `Array.sort()` 对值进行排序。
如果长度是奇数，则返回中点处的数字，否则返回两个中间数字的平均值。

```js
const median = arr => {
  const mid = Math.floor(arr.length / 2), nums = arr.sort((a, b) => a - b);
  return arr.length % 2 !== 0 ? nums[mid] : (nums[mid - 1] + nums[mid]) / 2;
};
// median([5,6,50,1,-5]) -> 5
// median([0,10,-2,7]) -> 3.5
```

### Nth element of array (获取数组的第 N 个元素)
使用 `Array.slice()` 得到一个包含第一个元素的数组。
如果索引超出范围，则返回 `[]`。（译者注：超过索引返回 `undefind`）
省略第二个参数 `n` 来获取数组的第一个元素。

```js
const nth = (arr, n=0) => (n>0? arr.slice(n,n+1) : arr.slice(n))[0];
// nth(['a','b','c'],1) -> 'b'
// nth(['a','b','b']-2) -> 'a'
```

### Pick (挑选)
使用 `Array.reduce()` 去过滤／挑选存在于 obj 中的 key 值，并转换回相应的键值对的对象。

```js
const pick = (obj, arr) =>
  arr.reduce((acc, curr) => (curr in obj && (acc[curr] = obj[curr]), acc), {});
// pick({ 'a': 1, 'b': '2', 'c': 3 }, ['a', 'c']) -> { 'a': 1, 'c': 3 }
// pick(object, ['a', 'c'])['a'] -> 1
```

### Shuffle array (随机数组)
使用 `Array.sort()` 在比较器中使用 `Math.random()` 重新排序元素。

```js
const shuffle = arr => arr.sort(() => Math.random() - 0.5);
// shuffle([1,2,3]) -> [2,3,1]
```

### Similarity between arrays (获取数组的交集)
使用 `filter()` 移除不是 `values` 的一部分的值，使用 `includes()` 确定。

```js
const similarity = (arr, values) => arr.filter(v => values.includes(v));
// similarity([1,2,3], [1,2,4]) -> [1,2]
```

### Sum of array of numbers (数组的总和)
使用 `Array.reduce()` 去迭代值并计算累计器，初始值为 `0`。

```js
const sum = arr => arr.reduce((acc, val) => acc + val, 0);
// sum([1,2,3,4]) -> 10
```

### Tail of list (列表的尾巴)
如果数组的长度大于1，则返回 `arr.slice(1)`，否则返回整个数组。

```js
const tail = arr => arr.length > 1 ? arr.slice(1) : arr;
// tail([1,2,3]) -> [2,3]
// tail([1]) -> [1]
```

### Take (抽取)
使用 `Array.slice()` 从头开始创建 `n` 个元素的数组。

```js
const take = (arr, n = 1) => arr.slice(0, n);
// take([1, 2, 3], 5) -> [1, 2, 3]
// take([1, 2, 3], 0) -> []
```

### Unique values of array (数组去重)
使用ES6 `Set` 和 `...rest` 运算符去除所有重复的值。

```js
const unique = arr => [...new Set(arr)];
// unique([1,2,2,3,4,4,5]) -> [1,2,3,4,5]
```
## Browser

### Bottom visible (底部可见即滚动至底部)
使用 `scrollY`，`scrollHeight` 和 `clientHeight` 来确定页面的底部是否可见。

```js
const bottomVisible = _ =>
  document.documentElement.clientHeight + window.scrollY >= (document.documentElement.scrollHeight || document.documentElement.clientHeight);
// bottomVisible() -> true
```

### Current URL (当前链接地址)
使用 `window.location.href` 来获取当前链接地址。

```js
const currentUrl = _ => window.location.href;
// currentUrl() -> 'https://google.com'
```

### Element is visible in viewport (元素在视窗中可见)
使用 `Element.getBoundingClientRect()` 和 `window.inner(Width|Height)` 值来确定给定的元素在视口中是否可见。
第二个参数用来指定元素是否要求完全可见，指定 `true` 即部分可见，默认为全部可见。

```js
const elementIsVisibleInViewport = (el, partiallyVisible = false) => {
  const { top, left, bottom, right } = el.getBoundingClientRect();
  return partiallyVisible
    ? ((top > 0 && top < innerHeight) || (bottom > 0 && bottom < innerHeight)) &&
      ((left > 0 && left < innerWidth) || (right > 0 && right < innerWidth))
    : top >= 0 && left >= 0 && bottom <= innerHeight && right <= innerWidth;
};
// e.g. 100x100 viewport and a 10x10px element at position {top: -1, left: 0, bottom: 9, right: 10}
// elementIsVisibleInViewport(el) -> false (not fully visible)
// elementIsVisibleInViewport(el, true) -> true (partially visible)
```

### Get scroll position (获取滚动位置)
如果存在，使用 `pageXOffset` 和 `pageYOffset`，否则使用 `scrollLeft` 和 `scrollTop`。
你可以省略 `el`，默认使用 `window`。

```js
const getScrollPos = (el = window) =>
  ({x: (el.pageXOffset !== undefined) ? el.pageXOffset : el.scrollLeft,
    y: (el.pageYOffset !== undefined) ? el.pageYOffset : el.scrollTop});
// getScrollPos() -> {x: 0, y: 200}
```

### Redirect to URL (URL 重定向)
使用 `window.location.href` 或者 `window.location.replace()` 去重定向到 `url`。
第二个参数用来控制模拟链接点击（`true` - 默认）还是 HTTP 重定向（`false`）。

```js
const redirect = (url, asLink = true) =>
  asLink ? window.location.href = url : window.location.replace(url);
// redirect('https://google.com')
```

### Scroll to top (滚动至顶部)
使用 `document.documentElement.scrollTop` 或 `document.body.scrollTop` 获取到顶端的距离。
从顶部滚动一小部分距离。 使用 `window.requestAnimationFrame（）` 实现滚动动画。

```js
const scrollToTop = _ => {
  const c = document.documentElement.scrollTop || document.body.scrollTop;
  if (c > 0) {
    window.requestAnimationFrame(scrollToTop);
    window.scrollTo(0, c - c / 8);
  }
};
// scrollToTop()
```
## Date

### Get days difference between dates (获取两个日期间的差距)
计算两个 `Date` 对象之间的差距（以天为单位）。

```js
const getDaysDiffBetweenDates = (dateInitial, dateFinal) => (dateFinal - dateInitial) / (1000 * 3600 * 24);
// getDaysDiffBetweenDates(new Date("2017-12-13"), new Date("2017-12-22")) -> 9
```
## Function

### Chain asynchronous functions (链式异步函数)
循环遍历包含异步事件的函数数组，当每个异步事件完成时调用 `next`。

```js
const chainAsync = fns => { let curr = 0; const next = () => fns[curr++](next); next(); };
/*
chainAsync([
  next => { console.log('0 seconds'); setTimeout(next, 1000); },
  next => { console.log('1 second');  setTimeout(next, 1000); },
  next => { console.log('2 seconds'); }
])
*/
```

### Curry (函数柯里化)
使用递归。
如果提供的参数（`args`）的数量足够，则调用传递的函数 `fn`，否则返回一个柯里化函数 `fn`，等待传入剩下的参数。
如果你想要一个接受参数数量可变的函数（一个可变参数函数，例如`Math.min()`），你可以选择将参数个数传递给第二个参数 `arity`。

```js
const curry = (fn, arity = fn.length, ...args) =>
  arity <= args.length
    ? fn(...args)
    : curry.bind(null, fn, arity, ...args);
// curry(Math.pow)(2)(10) -> 1024
// curry(Math.min, 3)(10)(50)(2) -> 2
```

### Pipe (管道)
使用 `Array.reduce()` 让值在函数间流通。

```js
const pipe = (...funcs) => arg => funcs.reduce((acc, func) => func(acc), arg);
// pipe(btoa, x => x.toUpperCase())("Test") -> "VGVZDA=="
```

### Promisify (promise转化)
使用 currying 返回一个函数，返回一个调用原始函数的 `Promise`。
使用 `...rest` 运算符传入所有参数。
**In Node 8+, you can use [util.promisify][1]** 
**Node 8 版本以上，你可以使用 [util.promisify][1]** 

```js
const promisify = func =>
  (...args) =>
    new Promise((resolve, reject) =>
      func(...args, (err, result) =>
        err ? reject(err) : resolve(result))
    );
// const delay = promisify((d, cb) => setTimeout(cb, d))
// delay(2000).then(() => console.log('Hi!')) -> Promise resolves after 2s
```

### Run promises in series (队列运行promise)
使用 `Array.reduce()` 通过创建一个 promise 链来运行一系列 promise，每个 promise 在解析时返回下一个 promise。

```js
const series = ps => ps.reduce((p, next) => p.then(next), Promise.resolve());
// const delay = (d) => new Promise(r => setTimeout(r, d))
// series([() => delay(1000), () => delay(2000)]) -> executes each promise sequentially, taking a total of 3 seconds to complete
```

### Sleep (睡眠)
通过返回一个 `Promise` 延迟执行 `async` 函数，把它放到睡眠状态。

```js
const sleep = ms => new Promise(resolve => setTimeout(resolve, ms));
/*
async function sleepyWork() {
  console.log('I\'m going to sleep for 1 second.');
  await sleep(1000);
  console.log('I woke up after 1 second.');
}
*/
```
## Math

### Collatz algorithm (考拉兹算法)
如果 `n` 是偶数，返回 `n/2`，否则返回 `3n+1`。

```js
const collatz = n => (n % 2 == 0) ? (n / 2) : (3 * n + 1);
// collatz(8) --> 4
// collatz(5) --> 16
```

### Distance between two points (两点间的距离)
使用 `Matg.hypot()` 来计算两点间的欧式距离。

```js
const distance = (x0, y0, x1, y1) => Math.hypot(x1 - x0, y1 - y0);
// distance(1,1, 2,3) -> 2.23606797749979
```

### Divisible by number (可否被整除)
使用模运算符（`％`）来检查余数是否等于 `0`。

```js
const isDivisible = (dividend, divisor) => dividend % divisor === 0;
// isDivisible(6,3) -> true
```

### Even or odd number (偶数或奇数)
使用模运算符（`%`）来计算一个数为偶数还是奇数。
返回 `true` 为偶数，返回 `false` 则为奇数。

```js
const isEven = num => num % 2 === 0;
// isEven(3) -> false
```

### Factorial (阶乘)
使用递归。
如果 `n` 小于或等于 `1`，返回 `1`。
其它情况，则返回 `n` 和 `n-1` 的阶乘的积。

```js
const factorial = n => n <= 1 ? 1 : n * factorial(n - 1);
// factorial(6) -> 720
```

### Fibonacci array generator (斐波纳契数组生成器)
创建一个指定长度的空数组，初始化前两个值（`0`和`1`）。
使用 `Array.reduce()` 将最后两个值的总和添加到数组中（前两个除外）。

```js
const fibonacci = n =>
  Array(n).fill(0).reduce((acc, val, i) => acc.concat(i > 1 ? acc[i - 1] + acc[i - 2] : i), []);
// fibonacci(5) -> [0,1,1,2,3]
```

### Greatest common divisor (GCD) (最大公约数)(译者注：使用辗转相乘法)
使用递归。
基本情况是如果 `y` 等于 `0`，则返回 `x`。
其它情况下，返回 `y` 与 `x/y` 的最大公约数。

```js
const gcd = (x, y) => !y ? x : gcd(y, x % y);
// gcd (8, 36) -> 4
```

### Hamming distance (汉明距离)
使用 异或 运算符（`^`）去查找两个数值间的位差，使用 `toString(2)` 转换为二进制值，使用 `match(/1/g)` 计算并返回字符串中 `1` 的数量。

```js
const hammingDistance = (num1, num2) =>
  ((num1 ^ num2).toString(2).match(/1/g) || '').length;
// hammingDistance(2,3) -> 1
```

### Percentile (百分位数)
使用百分比公式计算给定数组中有多少个数小于或等于给定值。
使用Array.reduce()计算值的下面有多少个数是相同的值, 并应用百分比公式。

```js
const percentile = (arr, val) => 
  100 * arr.reduce((acc,v) => acc + (v < val ? 1 : 0) + (v === val ? 0.5 : 0), 0) / arr.length;
// percentile([1,2,3,4,5,6,7,8,9,10], 6) -> 55
```

### Powerset (幂集)
使用 `Array.reduce()` 与 `Array.map()` 结合来迭代元素并将其组合成一个包含所有组合的数组。

```js
const powerset = arr =>
  arr.reduce((a, v) => a.concat(a.map(r => [v].concat(r))), [[]]);
// powerset([1,2]) -> [[], [1], [2], [2,1]]
```

### Round number to n digits (取小数点后 n 位)
使用 `Math.round()` 和字符串模板将数字四舍五入到指定的位数。
省略第二个参数，`decimals` 将四舍五入到一个整数。

```js
const round = (n, decimals=0) => Number(`${Math.round(`${n}e${decimals}`)}e-${decimals}`);
// round(1.005, 2) -> 1.01
```

### Standard deviation (标准差)
Use `Array.reduce()` to calculate the mean, variance and the sum of the variance of the values, the variance of the values, then
determine the standard deviation.
You can omit the second argument to get the sample standard deviation or set it to `true` to get the population standard deviation.
使用 `Array.reduce()` 来计算平均值，方差以及方差之和，然后确定标准偏差。
您可以省略第二个参数来获取样本标准差或将其设置为 `true` 以获得总体标准差。

```js
const standardDeviation = (arr, usePopulation = false) => {
  const mean = arr.reduce((acc, val) => acc + val, 0) / arr.length;
  return Math.sqrt(
    arr.reduce((acc, val) => acc.concat(Math.pow(val - mean, 2)), [])
       .reduce((acc, val) => acc + val, 0) / (arr.length - (usePopulation ? 0 : 1))
  );
};
// standardDeviation([10,2,38,23,38,23,21]) -> 13.284434142114991 (sample)
// standardDeviation([10,2,38,23,38,23,21], true) -> 12.29899614287479 (population)
```
## Media (媒体)

### Speech synthesis (experimental) 语音合成(试验功能)
使用 `SpeechSynthesisUtterance.voice` 和 `indow.speechSynthesis.getVoices()` 将消息转换为语音。
使用 `window.speechSynthesis.speak()` 来播放消息。
了解更多关于 [SpeechSynthesisUtterance interface of the Web Speech API][3].

```js
const speak = message => {
  const msg = new SpeechSynthesisUtterance(message);
  msg.voice = window.speechSynthesis.getVoices()[0];
  window.speechSynthesis.speak(msg);
};
// speak('Hello, World') -> plays the message
```
## Object (对象)

### Object from key-value pairs (键值对创建对象)
使用 `Array.reduce()` 创建和组合键值对。

```js
const objectFromPairs = arr => arr.reduce((a, v) => (a[v[0]] = v[1], a), {});
// objectFromPairs([['a',1],['b',2]]) -> {a: 1, b: 2}
```

### Object to key-value pairs (对象生成键值对)
使用 `Object.keys()` 和 `Array.map()` 去遍历对象的键并生成一个包含键值对的数组。

```js
const objectToPairs = obj => Object.keys(obj).map(k => [k, obj[k]]);
// objectToPairs({a: 1, b: 2}) -> [['a',1],['b',2]])
```

### Shallow clone object (浅拷贝对象)
使用 `...spread` 扩展运算符将目标对象的属性添加到拷贝对象中。

```js
const shallowClone = obj => ({ ...obj });
/*
const a = { x: true, y: 1 };
const b = shallowClone(a);
a === b -> false
*/
```
## String (字符串)

### Anagrams of string (with duplicates) (字符串异位(和重复))
使用递归。
遍历给定字符串中的每个字母，用其余字母创建所有部分字母。
使用 `Array.map()` 将字母与每个部分字母组合，然后使用 `Array.reduce()` 将所有字母组合到一个数组中。
当给定字符串数量等与 `2` 或 `1` 时做简单处理。＝

```js
const anagrams = str => {
  if (str.length <= 2) return str.length === 2 ? [str, str[1] + str[0]] : [str];
  return str.split('').reduce((acc, letter, i) =>
    acc.concat(anagrams(str.slice(0, i) + str.slice(i + 1)).map(val => letter + val)), []);
};
// anagrams('abc') -> ['abc','acb','bac','bca','cab','cba']
```

### Capitalize first letter of every word (所有单词的第一个字母大写)
使用 `replace()` 去查找单词的第一个字母并使用 `toUpperCase()` 改为大写。

```js
const capitalizeEveryWord = str => str.replace(/\b[a-z]/g, char => char.toUpperCase());
// capitalizeEveryWord('hello world!') -> 'Hello World!'
```

### Capitalize first letter (单词的第一个字母大写)
使用 `slice(0,1)` 和 `toUpperCase()` 将首字母大写，使用 `slice(1)` 得到字符串的其余部分。
忽略 `lowerRest` 参数以保持字符串的其余部分不变，或者将其设置为 `true` 以转换为小写字母。

```js
const capitalize = (str, lowerRest = false) =>
  str.slice(0, 1).toUpperCase() + (lowerRest ? str.slice(1).toLowerCase() : str.slice(1));
// capitalize('myName', true) -> 'Myname'
```

### Check for palindrome (检查回文)
使用 `toLowerCase()` 转换字符串并用 `replace()` 删除其中的非字母数字字符。
然后，使用 `split('')` 分散为单个字符，再使用 `reverse()` 和 `join('')` 倒序合并后与原字符进行比较。

```js
const palindrome = str => {
  const s = str.toLowerCase().replace(/[\W_]/g,'');
  return s === s.split('').reverse().join('');
}
// palindrome('taco cat') -> true
```

### Reverse a string (反转一个字符串)
使用数组解构和 `Array.reverse()` 来反转字符串中字符的顺序。
使用 `join('')` 组合字符获得一个字符串。

```js
const reverseString = str => [...str].reverse().join('');
// reverseString('foobar') -> 'raboof'
```

### Sort characters in string (alphabetical) 字符串排序（按字母顺序排列）
使用 `split('')` 切割字符串，使用 `Array.sort` 通过 `localeCompare()` 去排序，再使用 `join('')` 组合。

```js
const sortCharactersInString = str =>
  str.split('').sort((a, b) => a.localeCompare(b)).join('');
// sortCharactersInString('cabbage') -> 'aabbceg'
```

### Truncate a String (字符串截断)
确定字符串的长度是否大于 `num`。
将字符串截断为所需的长度，在末尾或原始字符串后附加 `...`。

```js
const truncate = (str, num) =>
  str.length > num ? str.slice(0, num > 3 ? num - 3 : num) + '...' : str;
// truncate('boomerang', 7) -> 'boom...'
```
## Utility (效率工具)

### Escape regular expression (转义正则表达式)
使用 `replace()` 去转义特殊字符。

```js
const escapeRegExp = str => str.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
// escapeRegExp('(test)') -> \\(test\\)
```

### Get native type of value (获取值的原始类型)
返回值的构造函数名称的小写字符，值为 `undefined` 或 `null` 时则返回 `undefined` 或 `null`。

```js
const getType = v =>
  v === undefined ? 'undefined' : v === null ? 'null' : v.constructor.name.toLowerCase();
// getType(new Set([1,2,3])) -> "set"
```

### Is array (是否是数组)
使用 `Array.isArray()` 去检查值是否为数组。

```js
const isArray = val => !!val && Array.isArray(val);
// isArray(null) -> false
// isArray([1]) -> true
```

### Is boolean (是否为布尔值)
使用 `typeof` 去检查值是否为原始布尔值类型。

```js
const isBoolean = val => typeof val === 'boolean';
// isBoolean(null) -> false
// isBoolean(false) -> true
```

### Is function (是否为函数)
使用 `typeof` 去检查值是否为函数原始类型。

```js
const isFunction = val => val && typeof val === 'function';
// isFunction('x') -> false
// isFunction(x => x) -> true
```

### Is number (是否为数值)
使用 `typeof` 去检查值是否为数值原始类型。

```js
const isNumber = val => typeof val === 'number';
// isNumber('1') -> false
// isNumber(1) -> true
```

### Is string (是否为字符串)
使用 `typeof` 去检查值是否为字符串原始类型。

```js
const isString = val => typeof val === 'string';
// isString(10) -> false
// isString('10') -> true
```

### Is symbol (是否为 symbol 类型)
使用 `typeof` 去检查值是否为 symbol 原始类型。

```js
const isSymbol = val => typeof val === 'symbol';
// isSymbol('x') -> false
// isSymbol(Symbol('x')) -> true
```

### Measure time taken by function (测量函数的耗时)
使用 `console.time()` 和 `console.timeEnd()` 来测量开始和结束时间之间的差异，以确定回调执行的时间。

```js
const timeTaken = callback => {
  console.time('timeTaken');
  const r = callback();
  console.timeEnd('timeTaken');
  return r;
};
// timeTaken(() => Math.pow(2, 10)) -> 1024
// (logged): timeTaken: 0.02099609375ms
```

### Number to array of digits (数值转换为数组)
将数值转换为字符串，使用 `split()` 分割为数组。
再使用 `Array.map()` 和 `parseInt()` 将每个值转换为整数。

```js
const digitize = n => (''+n).split('').map(i => parseInt(i));
// digitize(2334) -> [2, 3, 3, 4]
```

### Ordinal suffix of number （数值增加序号后缀）
Use the modulo operator (`%`) to find values of single and tens digits.
Find which ordinal pattern digits match.
If digit is found in teens pattern, use teens ordinal.
使用模运算符（`％`）来查找单位数和十位数的值。
查找数字匹配哪些序号模式。
如果数字在十几的模式中找到，请使用的十几的序数。

```js
const toOrdinalSuffix = num => {
  const int = parseInt(num), digits = [(int % 10), (int % 100)],
    ordinals = ['st', 'nd', 'rd', 'th'], oPattern = [1, 2, 3, 4],
    tPattern = [11, 12, 13, 14, 15, 16, 17, 18, 19];
  return oPattern.includes(digits[0]) && !tPattern.includes(digits[1]) ? int + ordinals[digits[0] - 1] : int + ordinals[3];
};
// toOrdinalSuffix("123") -> "123rd"
```

### Random integer in range (指定范围内的随机整数)
使用 `Math.random()` 去生成一个在指定范围内的随机数，使用 `Math.floor()` 将其转换为整数。

```js
const randomIntegerInRange = (min, max) => Math.floor(Math.random() * (max - min + 1)) + min;
// randomIntegerInRange(0, 5) -> 2
```

### Random number in range (指定范围内的随机数)
使用 `Math.random()` 去生成一个在指定范围内的随机数。

```js
const randomInRange = (min, max) => Math.random() * (max - min) + min;
// randomInRange(2,10) -> 6.0211363285087005
```

### RGB to hexadecimal (RGB转十六进制)
使用按位左移运算符（`<<`）和 `toString(16)` 将 RGB 参数转换为十六进制，然后使用 `padStart(6, '0')` 去获取6位数的十六进制。

```js
const rgbToHex = (r, g, b) => ((r << 16) + (g << 8) + b).toString(16).padStart(6, '0');
// rgbToHex(255, 165, 1) -> 'ffa501'
```

### Swap values of two variables (交换两个变量的值)
使用数组解构来交换两个变量之间的值。

```js
[varA, varB] = [varB, varA];
// [x, y] = [y, x]
```

### URL parameters （URL参数）
使用 `match()` 和一个合适的正则去获取所有键值对，使用 `Array.reduce()` 合并到一个对象中。
允许将 `location.search` 作为参数传递。

```js
const getUrlParameters = url =>
  url.match(/([^?=&]+)(=([^&]*))/g).reduce(
    (a, v) => (a[v.slice(0, v.indexOf('='))] = v.slice(v.indexOf('=') + 1), a), {}
  );
// getUrlParameters('http://url.com/page?name=Adam&surname=Smith') -> {name: 'Adam', surname: 'Smith'}
```

### UUID generator （UUID生成器）
使用 `crypto` API 生成符合 [RFC4122][4] 版本4的UUID。

```js
const uuid = _ =>
  ([1e7] + -1e3 + -4e3 + -8e3 + -1e11).replace(/[018]/g, c =>
    (c ^ crypto.getRandomValues(new Uint8Array(1))[0] & 15 >> c / 4).toString(16)
  );
// uuid() -> '7982fcfe-5721-4632-bede-6000885be57d'
```

### Validate email （校验邮箱）
Use a regular experssion to check if the email is valid.
Returns `true` if email is valid, `false` if not.
使用正则表达式去检验邮箱格式。
返回 `true` 表示邮箱格式正确，`false` 则不正确。

```js
const validateEmail = str =>
  /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/.test(str);
// validateEmail(mymail@gmail.com) -> true
```

### Validate number （校验数值）
使用 `!isNaN` 和 `parseFloat()` 来检查参数是否是一个数字（或允许转换为数值）。
使用 `isFinite()` 来检查数字是否是有限的。
使用 Number() 来检查数值转换是否成立。

```js
const validateNumber = n => !isNaN(parseFloat(n)) && isFinite(n) && Number(n) == n;
// validateNumber('10') -> true
```

### Value or default （值或默认值）
默认返回 `value` 如果 `value` 为假，则返回默认值。

```js
const valueOrDefault = (value, d) => value || d;
// valueOrDefault(NaN, 30) -> 30
```

[0]: https://github.com/Chalarangelo/30-seconds-of-code
[1]: https://nodejs.org/api/util.html#util_util_promisify_original
[2]: https://nodejs.org/api/util.html#util_util_promisify_original
[3]: https://developer.mozilla.org/en-US/docs/Web/API/SpeechSynthesisUtterance
[4]: https://www.ietf.org/rfc/rfc4122.txt