## 'abc' 转换成[a, b, c]一道面试题的思考

来源：[http://www.cnblogs.com/chenjinxinlove/p/8467556.html](http://www.cnblogs.com/chenjinxinlove/p/8467556.html)

时间 2018-02-24 20:24:00


最近面试遇到那样一个问题把'abc' 转换成[a, b, c]，就是字符串转成数组。


看着简单，我就是说split，然后面试官问还有吗。我有思考了一下。循环用charAt()取，然后还有Array.from()和扩展运算符[...'abc']。

然后就是答不出了。然后面试官问还有其他实现方式吗。我实在想出来，那道题就过了。面试完，自己思考还有什么方法，又翻看了

[阮一峰老师的ECMAScript 6 入门][0]
。对Iterator遍历器又有了新的认识。    

1、split

```js
'abc'.split('');
["a", "b", "c"]
```

2、Array.from()

```js
Array.from('abc')
["a", "b", "c"]
```

3、...

```js
[...'abc']
["a", "b", "c"]
```

4、charAt()

```js
function strToArr(str) {
  let result = [];
  for (let i = 0; i < str.length; i++) {
    result.push(str.charAt(i));
  }
  return result;
}
console.log(strToArr('abc'))
["a", "b", "c"]
```

from和扩展运算符都是用了迭代器，当然可以使用for of 来循环

注意：for...in循环读取键名，for...of循环读取键值

5、利用for of

```js
var str = 'abc';

for (let a in str) {
  console.log(a); // 0 1 2
}

for (let a of str) {
  console.log(a); // a b c
}
```

遍历器（Iterator）就是这样一种机制。它是一种接口，为各种不同的数据结构提供统一的访问机制。任何数据结构只要部署 Iterator 接口，就可以完成遍历操作（即依次处理该数据结构的所有成员）。

Iterator 的作用有三个：一是为各种数据结构，提供一个统一的、简便的访问接口；二是使得数据结构的成员能够按某种次序排列；三是 ES6 创造了一种新的遍历命令for...of循环，Iterator 接口主要供for...of消费。

Iterator 的遍历过程是这样的。

（1）创建一个指针对象，指向当前数据结构的起始位置。也就是说，遍历器对象本质上，就是一个指针对象。

（2）第一次调用指针对象的next方法，可以将指针指向数据结构的第一个成员。

（3）第二次调用指针对象的next方法，指针就指向数据结构的第二个成员。

（4）不断调用指针对象的next方法，直到它指向数据结构的结束位置。

每一次调用next方法，都会返回数据结构的当前成员的信息。具体来说，就是返回一个包含value和done两个属性的对象。其中，value属性是当前成员的值，done属性是一个布尔值，表示遍历是否结束。

6、Iterator

```js
let str = 'abc'
let iter = str[Symbol.iterator]();

iter.next() // { value: 'a', done: false }
iter.next() // { value: 'b', done: false }
iter.next() // { value: 'c', done: false }
iter.next() // { value: undefined, done: true }
```

原生具备 Iterator 接口的数据结构如下



* Array
* Map
* Set
* String
* TypedArray
* 函数的 arguments 对象
* NodeList 对象
  

所以数组可以用的字符串也是可以做。



[0]: http://es6.ruanyifeng.com/