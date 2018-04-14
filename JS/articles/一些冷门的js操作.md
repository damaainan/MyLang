## 一些冷门的js操作

来源：[https://juejin.im/post/5acc4c69f265da238440e7d1](https://juejin.im/post/5acc4c69f265da238440e7d1)

时间 2018-04-11 10:49:29

 
大家学习的时候，一开始小白，然后接触到进阶的东西的时候，发现一切得心应手，有的人可能开始说精通了。突然有一天，发现了一些基于很基础的东西的骚操作，就开始怀疑人生：wtf JavaScript？ 如果没有遇到被某些东西打击到或者见识到新的世界，可能永远的，就感叹：jQuery真好用，我精通jQuery，精通js。要不就是，vue？angular？react？我都会，我精通。
 
然而，我现在只能说我只是熟悉，越学发现越多坑。 对于数据类型转换和正则的坑，前面有讲过： [数据类型][2] [正则表达式][3]
 
## 1.数组
 
类似一些遍历类型的api：forEach、map，可能有人就说了：不就是`arr.map(x=>x+1)`，要是涉及到索引，那就再来个index，`arr.map((x,index)=>x+index)`，多简单是不是 然后，先抛出一个问到烂的面试题：`['1','2','3'].map(parseInt)`找工作的人，看过面试题的，都知道结果是[1,NaN,NaN]，那么为什么会这样呢？ 首先，map里面可以传两个参数：map（对每一个元素都调用的函数，该函数的this值） 而那个每一个元素都调用的函数，他传入的参数是（current，index，arr）当前元素（必须）、索引、数组。
 
## 1.1对parseInt精通了吗
 
在这个例子，对parseInt传入的就是这三个参数。 而parseInt这个原生的函数，他传入的参数是（num，radix）: radix表示要解析的数字的基数。该值介于 2 ~ 36 之间。 如果省略该参数或其值为 0，则数字将以 10 为基础来解析。如果它以 “0x” 或 “0X” 开头，将以 16 为基数。如果该参数小于 2 或者大于 36，则 parseInt() 将返回 NaN
 
```js
parseInt(10,10)//对10进制数字10取整，10
parseInt(10,2)//对2进制数字10取整，2
parseInt(111,2)//对2进制数字111取整，7
parseInt(111,4)//对4进制数字111取整，21
parseInt('1',2,[1])//1，传入第三个数组是没有意义的
parseInt('1',2,['1','2','3','4'])//1
parseInt('2',2,['1','2','3','4'])//NaN，2进制没有2
parseInt('2',3,['1','2','3','4'])//3
```
 
那就很明显了，对于为什么是[1,NaN,NaN]，其实就是：
 
```js
parseInt('1',0,['1','2','3'])//1，radix为 0，则数字将以 10 为基础来解析
parseInt('2',1,['1','2','3'])//1进制是啥？反正就是NaN
parseInt('3',2,['1','2','3'])//2进制没有3
```
 
另外，parseInt，遇到字符串的数字他会尽量解释，直到不能解释就停止。
 
```js
parseInt('123sfd')//123
parseInt('123sfd123')//123
parseInt('sfd213')//NaN
```
 
## 1.2数组遍历的api第二个参数
 
第二个参数，表示前面那个函数内部的this，一般不填这个参数，this就是undefined。而在非严格模式下，undefined就是window：`[1,2,3].forEach(function(x){console.log(this)})//window`我们可以强行把他改成其他的看看：`[1,2,3].forEach(function(x){console.log(this)},Math)//Math`## 1.3让Array成精
 
我们知道，Array可以直接生成某一个长度元素全是空的数组： Array(5)//注意了，5空和5个undefined是不同的 不妨apply一下：
 
```js
Array.apply(null, { length:5 })// [undefined, undefined, undefined, undefined, undefined]
Array.apply(null, { '0':1,length:5 })// [1, undefined, undefined, undefined, undefined]
Array.apply(null, { '2':1,length:5 })// [undefined, undefined, 1, undefined, undefined]
```
 
相当于给新创建的array的属性直接进行改变
 
## 1.4你是不是用循环生成一个序列？
 
生成一个序号数组：
 
```js
var arr = [];
for(var i = 0;i<10;i++){
    arr.push(i)
}
```
 
常规操作，没什么问题，但是精通jQuery的你会不会用到其他方法呢？ 比如：
 
```js
Array.apply(null, {length:5 }).map(f.call,Number)//[0, 1, 2, 3, 4]，f可以是任何函数
Array.apply(null, { '0':1,length:5 }).map(f.call,Number)//[0, 1, 2, 3, 4]，不管元素是什么都一样
Array.apply(null, {length:5 }).map(f.call,Boolean)//[false, true, true, true, true]
Array.apply(null, {length:5 }).map(f.call,String)//["0", "1", "2", "3", "4"]
Array.apply(null, {length:5 }).map(eval.call,Object)//[Number, Number, Number, Number, Number]
```
 
对于最后一个结果，点开第二个看看
 
 ![][0]
map的那个函数，传入了三个参数，第一个参数是当前元素。可是对于加了call的，第一个参数就是call的this指向了。而map后面的那个参数，就是this，也就是后面那个this已经把current覆盖，起到主导作用的也是后面那个参数。而map的第一个参数fn，fn里面的第二个参数是index，也就是当前索引。而对于f.call，第一个参数是this指向，第二个参数以后全是f.call的函数f所使用的参数。最后，就相当于对每一个元素进行，Number（index），Boolean（index），String（index），Object（index）
 
## 2.位操作符
 
基本用法和概念就不说了，自行看文档。
 
## 2.1字符串转数字
 
有全世界都知道的parseInt，但是我们又可以用简单一点的方法：
 
```js
//就是让他进行不改变本身的值的数学运算
+"1"
"1"*1
"1"|0
"1" >> 0
"1" << 0
```
 
## 2.2更多的操作
 
要是我们要随意得到一个很大的数，一般就是9999*9999这样子吧，而位移操作可以相当于乘上2的n次方：`1<<30//1073741824`好像没什么用，先抛出一个需求：随机生成字符串（数字+字母） 我知道，很多人完全不需要思考，直接拿起键盘撸：比如生成一个6位随机字符串
 
```js
var n = 6
var str = 'abcdefghijklmnopqrstuvwxyz0123456789'
var result = ''
for (var i = 0 ;i<n;i++){
   result += str[parseInt(Math.random()*(str.length+1))]
}
```
 
对于位操作，就是短短的代码解决:
 
```js
(~~(Math.random()*(1<<24))).toString(16)
(~~(Math.random()*(1<<30))).toString(36)
```
 
首先生成一个大数，再转进制。16进制就是0-9加上前面几个字母，36进制就是0-9加上26个字母，那么我们可以得到一个稳定的生成n位随机字符串版本：
 
```js
function f(n){
	if(n==1) return (~~(Math.random()*36)).toString(36)
	return (~~(Math.random()*36)).toString(36) + f(n-1)
}
//尾递归优化
function k(n){
	return function f(n,s){
		if(n==1) return s
		return  f(n-1,(~~(Math.random()*36)).toString(36)+s)
	}(n,(~~(Math.random()*36)).toString(36))
}
```
 
另一种方法：（也是基于高进制） 我们可以从`Math.random().toString(36)`得到一个0.xxx后面有11位小数的字符串，所以我们只要取第2位以后的就可以了`Math.random().toString(36).slice(2)`### 来一段小插曲
 
对于追求代码极其简短的强迫症，看见上面的if -else，突然想起来平时写了一大堆if-else实在是不顺眼，好的，除了无脑if和简短的三元表达式，我们还有短路表达式： || && a&&b：a为true，跑到b a||b：a为false，跑b，a为true就取a
 
```js
//来一个有点智障的例子
function f(a){
if(a==1) console.log(1)
if(a==2) console.log(2)
if(a==3) console.log(3)
}

//一定要记得写分号
function f(a){
(a==1)&& console.log(1);
(a==2) &&console.log(2);
(a==3) &&console.log(3);
}
```
 
如果在实际应用上面，代码将会大大简洁，但是可能第一次让别人看难以理解
 
### 位操作交换俩整数
 
不用中间变量，加减法实现交换 a = a+b;b = a-b;a = a-b 用位操作： a ^= b; b ^= a; a ^= b;
 
具体过程可以这样子证明：
 
```
我们先令a0 = a， b0 = b。a = a ^ b 可以转化为a = a0 ^ b
第二句：b = b ^ a =  b0 ^ a = b0 ^ (a0 ^ b0) = a0 ^ (b0 ^ b0) = a0 ^ 0 = a0//达到了原始值a0和实际值b交换
第三句一样：a = a ^ b = a ^ (b0 ^ a） = b0 ^ (a ^ a)= b0 ^ 0 = b0，和原始的b0交换成功
```
 
## 3. 构造类
 
继续回到前面的例子：
 
```js
Array.apply(null, {length:5 }).map(f.call,Number)//[0, 1, 2, 3, 4]，f可以是任何函数
Array.apply(null, { '0':1,length:5 }).map(f.call,Number)//[0, 1, 2, 3, 4]，不管元素是什么都一样
Array.apply(null, {length:5 }).map(f.call,Boolean)//[false, true, true, true, true]
Array.apply(null, {length:5 }).map(f.call,String)//["0", "1", "2", "3", "4"]
Array.apply(null, {length:5 }).map(eval.call,Object)//[Number, Number, Number, Number, Number]
```
 
map第二个参数ctx是this指向，而第一个参数是一个函数f（任何函数），f的第一个参数已经报废，因为第一个参数是call的上下文this，但是这个this又被后面的ctx替代了，因此f有效的参数是从第二个开始，最后就相当于ctx（index），即是 ：构造类（index）
 
于是我们又可以看看构造类另一个有意思的地方
 
```js
var toFixed = 1;
var obj = {
     toFixed:"我只是客串的",
    show:function(){
        return this. toFixed;
    }
}
obj.show.call( toFixed);   //ƒ toFixed() { [native code] }
```
 
也许一眼看上去是1，然而call的第一个参数居然不是null、undefined，效果不一样了。 我们call的上下文就是toFixed。可以这样理解，对于js内部，1其实是构造类Number（1）构造出来的，相当于this指向了Number，而我们可以打印一下Number.prototype，结果有
 
 ![][1]
我们把toFixed方法打印出来了
 
对于String也是可以的
 
```js
var big = '1sdasdsadsdasd';//不是字符串的话，其他构造类没有big方法，返回undefined
var obj = {
    big:"我是客串的",
    show:function(){
        return this.big;
    }
}
obj.show.call(big);  //ƒ big() { [native code] }

//或者说，打印一个length看看
var l = '1sdasdsadsdasd';//变量换成l
var obj = {
    length:"我是客串的",
    show:function(){
        return this.length;//主要是这个，变量是什么不重要
    }
}
obj.show.call(l); //14
```
 
属性太多了，可以去控制台看看String.prototype有什么。
 
再或者说，看看函数执行起来会发生什么事情：
 
```js
var l = true;//这次试一下boolean类型
var obj = {
    length:"我是客串的",
    show:function(){
        return this.valueOf();//这次我们不打印这个函数了，让他执行
    }
}
obj.show.call(l,this); //true，直接调用类型转换过程中的那个valueOf
```
 
道理都是一样，大家自己可以回去玩一下
 


[2]: https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2Flhyt%2Fissue%2Fissues%2F5
[3]: https://link.juejin.im?target=https%3A%2F%2Fgithub.com%2Flhyt%2Fissue%2Fissues%2F4
[0]: https://img2.tuicool.com/bM7Jjqe.png 
[1]: https://img1.tuicool.com/i6N3yiU.png 