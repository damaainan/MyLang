## js正则字符串

来源：[http://varnull.cn/jszheng-ze-zi-fu-chuan/](http://varnull.cn/jszheng-ze-zi-fu-chuan/)

时间 2018-02-12 18:02:43

 

![][0] 
 
正则字符串是什么？
 
这个词是我自己这么叫的，就是可以用字符串来表示的正则。。。一般我们写正则，直接写在两个斜线中间：/这里是正则表达式/
 
可是你要想写个动态正则，你就得借助字符串来完成了，因为字符串可以动态生成，并且当做参数去构造出正则的对象。但是这个参数直接加双引号变成："/这里是正则表达式/" 这样就可以了吗？
 
如果去尝试一下，就知道咿~不对。。。为什么不对呢？先来看看escape这个东西吧。
 
一直对escape这个词有陌生感，因为他的英文是逃避躲开的意思，而程序中它有另一个名字叫做转义。
 
其实顾名思义，转义就是转换意义的意思，也算式一种避开本身意义的行为吧。那么什么是转义呢？为什么需要转义呢？
 
因为在特定环境中，字符串中的【某些字符或者字符组合】有某个意义，而希望它表示其他意义的时候，就需要转义了
 
感觉说了废话，所以上例子：

```js
"Hello "World.""
```
 
由于字符串中的两个双引号，和字符串开头和结尾的双引号引起了歧义，所以程序解释器不知道这个字符串合适结束，而你又想表示确确实实看到的这个由这些字符和四个双引号组成的字符时，就需要转义，让解释器明白我只是想表示双引号这个字符而不是它本来的字符串识别符。所以变成下面就可以了：

```js
"Hello \"World.\""
```
 
那么对于普通js字符串，可以进行转义的有哪些呢？ 

![][1] 
 
所以你想在字符串里使用' " \ 来表示这些字符本来的意义就需要转义成：\' \" \\ 来让程序解析器正确理解你的意图，原来你只是想表示这些字符本来的意义，而不是表示字符的开始和结束以及转义符。。。。
 
好了，再说回来我们的正则字符串, 举个例子： 如下匹配任意一个单字符（除了换行符）

```js
/./
/./.exec('abcd')
```
 
如果传字符串呢？你会想怎么传？这样？"."

```js
var reg = new RegExp(".")  
reg.exec('abcd')
```
 
没错，正如你所想没问题，两种写法都是一样的。
 
可是如果你只想匹配一个.这个本身字符呢？

```js
/\./.exec('abd.ff.')
```
 
没错，是这样写，注意这里的.其实是正则表达的转义，在正则里.表示任意单个字符，当你想表示.字符串本身的时候就需要转义成.了，可是这和上面提到的字符串转义什么关系呢？
 
没有关系。。。
 
他们是相互独立的转义体系，没有关系，但是当你想用字符串来表示正则表达式的时候它们就产生了联系而已，这也就是为什么在刚开始写正则字符串的时候会懵逼一下的原因吧。。。。那产生了联系怎么写呢？这样吗？

```js
var reg = new RegExp("\.")
```
 
你会发现它和下面的是一样的

```js
var reg = new RegExp(".")
```
 
并没有只匹配.字符，这是为什么呢？看图 

![][2] 
 
所以这里进行了两次转义才到达你最终的目的的，所以就应该这么写：

```js
var reg = new RegExp("\\.")
```
 
字符串"\\."先转义成字符串"\."，然后再作为参数传给正则引擎，自然理解你想要匹配的是.这个字符，而不是任意一个字符了。
 
感受一个长一点的, 我想匹配这个正则/\.\w\\a/ 它的正则字符串是什么呢？如下：

```js
'\\.\\w\\\\a'
```
 
现在在看这堆东西是否清晰了一些呢
 


[0]: ./img/3eYv2yi.png
[1]: ./img/fmMJfma.png
[2]: ./img/Mva6bym.png