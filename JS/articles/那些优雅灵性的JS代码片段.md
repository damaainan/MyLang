## 那些优雅灵性的JS代码片段

来源：[https://juejin.im/post/5acc2cbef265da239612b508](https://juejin.im/post/5acc2cbef265da239612b508)

时间 2018-04-11 10:41:07

 
我的个人网站：拓跋的前端客栈~了解一哈。这里是原文地址，如果您发现我文章中存在错误，请尽情向我吐槽，大家一起学习一起进步φ(>ω<*)
 
## 引子
 
如果您甘于平凡，写代码对您来说可以就是Ctrl+C和Ctrl+V；如果您充满创造力，写代码也可以成为一门艺术。我们在平时总会遇到一些堪称优雅灵性的代码片段，在这里，仅以我之见，列举出我所见到的那一部分。
 
下面为了阅读方便，我会把代码的题目和莽夫解法放在一起，优雅灵性的解法放在最下面  ，希望能对您造成一定的冲击，看官们可以自己尝试一下，题目并不难。
 
当然，通往罗马的大路有千千万，可能您的解法更为优秀。如果这样，希望您能在评论区展示出来，让更多人看见~
 
注：以下所有题目均来自codewars
 
 ![][0]

## 题目&莽夫解
 

* Create Phone Number
题目：编写一个函数，它接受一个由10个整数组成的数组（0到9之间的数组），该函数以形似(123) 456-7890的电话号码的形式返回这些数字的字符串。
Example:

```js
createPhoneNumber([1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) // => returns "(123) 456-7890"1111
```
莽夫解法：

```js
const createPhoneNumber = n => "(" + n[0] + n[1] + n[2] + ") " + n[3] + n[4] + n[5] + "-" + n[6] + n[7] + n[8] + n[9]
```
  
* Find the odd int
题目：给定一个数组，找到出现奇数次的数字。
PS:将始终只有一个整数出现奇数次。
Example:

```js
findOdd([1,1,2,-2,5,2,4,4,-1,-2,5]); // => returns -1
```
莽夫解法：

```js
function findOdd(A) {
    let count = 0;
    do {
        let i = A.splice(count,1,'p')[0];
        if (i !== 'p'){
            let result = [i];
            A.forEach(function (e, index) {
                if (e === i){
                    i === result[0] ? result.pop(): result.push(i);
                    A.splice(index, 1, 'p');
                }
            });
            if (result.length > 0){
                return result[0]
            }
        }
        count ++;
    } while (A.length > count);
}
```
  
* Who likes it?
题目：您可能知道Facebook或者其他网站的“喜欢”系统。人们可以“喜欢”博客文章，图片或其他项目。我们想要创建一份显示在这样项目旁边的文本。
实现一个函数，它的输入是数组，其中包含喜欢该项目的人的姓名。返回值是如下格式的文本：

```js
likes [] // must be "no one likes this"
likes ["Peter"] // must be "Peter likes this"
likes ["Jacob", "Alex"] // must be "Jacob and Alex like this"
likes ["Max", "John", "Mark"] // must be "Max, John and Mark like this"
likes ["Alex", "Jacob", "Mark", "Max"] // must be "Alex, Jacob and 2 others like this"
```
莽夫解法：

```js
const likes = names => {
    switch (names.length) {
        case 0: return 'no one likes this'
        case 1: return names[0] + ' likes this'
        case 2: return names[0] + ' and ' + names[1] + ' like this'
        case 3: return names[0] + ', ' + names[1] + ' and ' + names[2] + ' like this'
        default: return names[0] + ', ' + names[1] + ' and ' + (names.length - 2) + ' others like this'
    }
}
```
  
* Shortest Word
题目：给定一串单词，返回最短单词的长度。
字符串永远不会为空，您不需要考虑不同的数据类型。
Example:

```js
findShort("bitcoin take over the world maybe who knows perhaps") // returns 3，因为最短单词是the和who，长度为3
```
莽夫解法：

```js
// 其实也不是特别莽
const findShort = s => s.split(' ').map(w => w.length).sort((a,b) => a-b)[0];
```
  
* Sum of Digits / Digital Root
题目：创建一个计算digital root的函数。
digital root是数字中各位数字的递归总和。给定n，取n各位数字之和。如果该值是两位数或者更多，则继续以这种方式递归，直到产生一位数字，这个数字就是digital root。这只适用于自然数。
Example:

```js
digital_root(16)
=> 1 + 6
=> 7

digital_root(942)
=> 9 + 4 + 2
=> 15 ...
=> 1 + 5
=> 6

digital_root(132189)
=> 1 + 3 + 2 + 1 + 8 + 9
=> 24 ...
=> 2 + 4
=> 6

digital_root(493193)
=> 4 + 9 + 3 + 1 + 9 + 3
=> 29 ...
=> 2 + 9
=> 11 ...
=> 1 + 1
=> 2
```
莽夫解法：

```js
function digital_root(n) {
    let num = n;
    if (num < 10){
        return num
    }else {
        return arguments.callee((num+'').split('').reduce(function (a,b) {
            return parseInt(a) + parseInt(b)
        }))
    }
}
```
  
 

## 优雅&灵性解
 

* Create Phone Number

```js
function createPhoneNumber(numbers){
    var format = "(xxx) xxx-xxxx";
    for(var i = 0; i < numbers.length; i++){
        format = format.replace('x', numbers[i]);
    }
    return format;
}
```
使用一个format的模版，通过循环replace所有format里的x位，优雅且可读性强，让人眼前一亮。
  
* Find the odd int

```js
const findOdd = (xs) => xs.reduce((a, b) => a ^ b);
```
我猜起码70%的人看到这个解法会一愣。回想一下，自己多久没有用过位运算了？本题使用reduce()和按位异或操作，相当于所有出现偶数次的数按位异或后均为0，然后出现基数次的数字与0按位异或得到自己本身，从而得解。
  
* Who likes it?

```js
function likes (names) {
    var templates = [
        'no one likes this',
        '{name} likes this',
        '{name} and {name} like this',
        '{name}, {name} and {name} like this',
        '{name}, {name} and {n} others like this'
    ];
    var idx = Math.min(names.length, 4);
    
    return templates[idx].replace(/{name}|{n}/g, function (val) {
        return val === '{name}' ? names.shift() : names.length;
    });
}
```
这个不用解释了，使用模版字符串，可别傻傻的手动拼写了。
  
* Shortest Word

```js
function findShort(s){
    return Math.min.apply(null, s.split(' ').map(w => w.length));
}
```
面试中经常可能会遇到问apply和call的区别之类的题目，但是实际上在工作中有多少人用它们写过代码呢？
  
* Sum of Digits / Digital Root

```js
function digital_root(n) {
    return (n - 1) % 9 + 1;
}
```
这个解法堪称神来之笔。有些人可能看不懂，它利用了我们小学时期学的一条定理，“所有位相加之和是9的倍数的数字能被9整除”。这个您可能没印象了，但是“所有位相加之和是3的倍数的数字能被3整除”这个您一定知道吧，这是同样的道理。至于为什么(n-1)整除9以后再加1，是为了防止9的倍数本身求出0的解来。
  
 

## 小结
 
以上五段代码，分别通过replace、位运算、模版字符串、apply甚至是“所有位相加之和是9的倍数的数字能被9整除”这种定理都能拿来解题，实在是令人叹为观止。
 
有些操作是神来之笔，有些操作是可以学习的。我们要做的就是把能学习到的学习到，下次自己能用上，这就够了。
 


[0]: https://img2.tuicool.com/FJVbiiy.png