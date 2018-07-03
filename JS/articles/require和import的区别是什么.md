## require和import的区别是什么？看这个你就懂了

来源：[https://segmentfault.com/a/1190000014434944](https://segmentfault.com/a/1190000014434944)


| require | import |
|-|-|
| 动态评估 | 静态评估 |
| 再运行时报错 | 再解析时报错 |
| 不是关键词 | 是关键词 |


## 语法
### CommonJs

dep.js

```js
module.exports = {
    foo: function () {},
    bar: 'a'
}
```

app.js

```js
var dep = require('dep')
console.log(dep.bar)
dep.foo()
```
### ESM

dep.js

```js
export foo function(){}
export const bar = 'a'
```

app.js

```js
import { foo, bar } from 'dep'
console.log(bar)
foo()
```
## 加载方式的不同

使用require的时候，其实会将module的代码进行包装，变成如下样子的代码：

```js
function (exports, require, module, __filename, __dirname) {
  const m = 1;
  module.exports.m = m;
}
```

然后在执行这个方法的时候，我们可以传入：

```js
const module = { exports: {} }
const require = function(){/* ...some module load code here */}
// __filename, __dirname是require的时候提供的路径分析出来的
fun(module.exports, require, module, __filename, __dirname)
```

执行完成之后，就能通过module拿到方法中向外抛出的变量了。

所以我们可以看到，module、require、exports都不是全局变量，而是专门为这个模块使用的局部变量。

require的时候真正做的事情如下：


* Resolution ／ 解析路径
* Loading ／ 加载代码
* Wrapping ／ 包装
* Evaluation ／ 评估执行
* Caching ／ 缓存


简单来说就是根据require调用时传入的路径，首先要拿到真正的绝对路径（是相对目录的，还是node_modules下面的等等），然后读入代码，包装成上面显示的样子，然后传给vm进行评估执行，得到结果，最后进行缓存。

所以，在模块代码执行完之前，node根本不知道这个模块到底export出了什么东西，这也是和ESM最大的区别，因为ESM是基于关键字的模块化，是可以在解析的过程中就知道导出了什么。

在解析ESM模块的时候，在把代码传给VM执行之前，就可以得到一个叫做`Module Record`的内部结构，他保存了模块倒出的内容的列表，在你`import {f} from f`的时候，他其实在你引用的地方和倒出的地方的`f`之间建立了连接，即它们是指向同一内存的，即便是原始数据类型，你修改模块中的指也会导致引用处的变化。啥意思呢？

```js
// dep.js
export let a = 1
setTimeout(() => a += 1, 500)

// app.js
import { a } from 'dep'
setTimeout(function () {
  console.log(a)
}, 1000)
```

输出的会是2，但是你用require，CommonJs模块来做，就会是1，因为CommonJs是普通的值传递或者引用传递

这就是require和import最大的区别
