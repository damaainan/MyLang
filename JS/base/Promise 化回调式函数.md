## Promise 化回调式函数

来源：[https://csspod.com/promisify-function/](https://csspod.com/promisify-function/)

时间 2018-06-28 19:55:44


Node.js 8 提供了新的工具函数：[util.promisify][0]，用于把形如`(err, value) => ...`的回调式函数转换为 Promise 版本。


## 基本使用

```js
const util = require('util');
const fs = require('fs');

const stat = util.promisify(fs.stat);

stat('.').then((stats) => {
  // Do something with `stats`
}).catch((error) => {
  // Handle the error.
});
```

当然，也可以使用 Node 8 另一个新功能`async function`调用：

```js
const util = require('util');
const fs = require('fs');

const stat = util.promisify(fs.stat);

async function callStat() {
  const stats = await stat('.');
  console.log(`This directory is owned by ${stats.uid}`);
}
```


## 自定义函数的 Promise 版本

通过设置`util.promisify.custom`symbol，可以自定义`util.promisify()`的返回值：

```js
const util = require('util');

function doSomething(foo, callback) {
  // ...
}

doSomething[util.promisify.custom] = (foo) => {
  return getPromiseSomehow();
};

const promisified = util.promisify(doSomething);

console.log(promisified === doSomething[util.promisify.custom]);
// prints 'true'
```

自定义 Promise symbol 一般用于源函数不遵循`(err, value) => ...`回调的场景，比如`(foo, onSuccessCallback, onErrorCallback)`式回调的函数：

```js
doSomething[util.promisify.custom] = (foo) => {
  return new Promise((resolve, reject) => {
    doSomething(foo, resolve, reject);
  });
};
```


## 回调函数中包含超过两个参数的函数

诸如以下函数，回调中除了`err`参数，还包含多个参数：



* child_process.exec
* child_process.execFile
* dns.lookup
* dns.lookupService
* fs.read
* fs.write
  

经过`util.promisify`处理的 Promise 版本会将多个参数组装成对象返回。

例如，`dns.lookup()`的回调有三个参数：



* err: Error
* address: 字符串
* family: 整数
  

Promise 化后，返回`{address: '', family: 3}`这样的对象：

```js
const util = require('util');
const dns = require('dns');
const lookupAsync = util.promisify(dns.lookup);

lookupAsync('nodejs.org')
  .then(obj => console.log(obj));
   // { address: '104.20.23.46', family: 4 }
```


## 老版本 Node


### Polyfill: util.promisify 模块

```js
npm install util.promisify
```

```js
const util = require('util');
require('util.promisify').shim();

const fs = require('fs');
const readFileAsync = util.promisify(fs.readFile);
```


### pify

[pify][1]
是一个小而美的 Promise 化工具，处理了一些有用的细节，如自动`this`绑定，这是内置的`util.promisify`中没有的。

```js
const fs = require('fs');
const pify = require('pify');

// Promisify a single function
pify(fs.readFile)('package.json', 'utf8').then(data => {
  console.log(JSON.parse(data).name);
  //=> 'pify'
});

// Promisify all methods in a module
pify(fs).readFile('package.json', 'utf8').then(data => {
  console.log(JSON.parse(data).name);
  //=> 'pify'
});
```


## 参考链接



* [Node.js 8: util.promisify()][2]
    
* [util.promisify(original)][3]
Node.js 官方文档    
  



[0]: https://nodejs.org/dist/latest-v8.x/docs/api/util.html#util_util_promisify_original
[1]: https://github.com/sindresorhus/pify
[2]: http://2ality.com/2017/05/util-promisify.html
[3]: https://nodejs.org/dist/latest-v8.x/docs/api/util.html#util_util_promisify_original