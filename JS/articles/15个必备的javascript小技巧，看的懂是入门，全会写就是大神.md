## 15个必备的javascript小技巧，看的懂是入门，全会写就是大神

来源：[http://www.jianshu.com/p/a2bd6c9b144b](http://www.jianshu.com/p/a2bd6c9b144b)

时间 2018-06-06 19:39:20

 
![][0]
 
## 1、变量转换
 
看起来很简单，但据我所看到的，使用构造函数，像Array()或者Number()来进行变量转换是常用的做法。始终使用原始数据类型（有时也称为字面量）来转换变量，这种没有任何额外的影响的做法反而效率更高。
 
![][1]
 
转换日期(new Date(myVar))和正则表达式(new RegExp(myVar))必须使用构造函数，而且创建正则表达式的时候要使用/pattern/flags的形式。
 
## 2、玩转数字
 
![][2]
 
## 3、判断属性是否存在
 
这个问题包含两个方面，既有检查属性时候存在，还要获取属性的类型。但我们总是忽略了这些小事情:
 
![][3]
 
但是，有的情况下，我们有更深的结构和需要更合适的检查的时候，可以这样：
 
![][4]
 
## 4、对数组排序进行“洗牌”随机排序
 
这段代码在这里使用Fisher Yates洗牌算法给一个指定的数组进行洗牌(随机排序)。
 
我的web前端学习交流群：575308719，每天会有精美的实战项目特效案例分享，小白或者进阶都有精品学习资料分享的哦！
 
![][5]
 
## 5、返回对象的函数能够用于链式操作
 
当创建面向对象的JavaScript对象的function时，函数返回一个对象将能够让函数可链式的写在一起来执行。
 
![][6]
 
## 6、为replace()方法传递一个函数
 
有的时候你想替换字符串的某个部分为其它的值，最好的方法就是给String.replace()传递一个独立的函数。下面是一个简单例子：
 
![][7]
 
## 7、十进制转换为十六进制或者八进制，或者反过来
 
你是不是写个单独的函数来转换十六进制（或者八进制）呢？马上停下吧！有更容易的现成的函数可以用：
 
![][8]
 
## 8、更快的四舍五入
 
今天的技巧是关于性能。见到过双波浪线"~ ~"操作符吗？它有时也被称为double NOT运算符。你可以更快的使用它来作为Math.floor()替代品。为什么呢？
 
单位移~将32位转换输入-(输入+1)，因此双位移将输入转换为-(-(输入+1))，这是个趋于0的伟大的工具。对于输入的数字，它将模仿Math.ceil()取负值和Math.floor()取正值。如果执行失败，则返回0，这可能在用来代替Math.floor()失败时返回一个NaN的时候发挥作用。
 
![][9]
 
虽然~~可能有更好的表现，为了可读性，请使用Math.floor()。
 
前端有什么不懂的，或者不知道怎么学习的可以来我的前端群：589651705，不管你是小白还是大牛，小编都欢迎，不定期分享干货，欢迎初学和进阶中的小伙伴。
 
## 9、模板字符串
 
截至ES6，JS已经有模板字符串作为替代经典的结束引用的字符串。
 
![][10]
 
## 10、处理一个数组或单个元素作为参数的方法
 
相比于写个单独的方法去分别操作一个数组和一个元素作为参数的函数，更好的是写一个通用的函数，这样就都可以操作。这类似于一些jQuery的方法(css匹配将修改所有的选择器)。
 
你仅需要先将一切放进数组，Array.concat会接收数组或单一的对象：
 
![][11]
 
printUpperCase现在可以接收无论单一的元素作为参数还是一个数组：
 
![][12]
 
## 11、Javascript版本检测
 
你知道你的浏览器支持哪一个版本的Javascript吗？如果不知道的话，去维基百科查一下Javascript版本表吧。出于某种原因，Javascript 1.7版本的某些特性是没有得到广泛的支持。不过大部分浏览器都支持了1.8版和1.8.1版的特性。（注：所有的IE浏览器（IE8或者更老的版本）只支持1.5版的Javascript）这里有一个脚本，既能通过检测特征来检测JavaScript版本，它还能检查特定的Javascript版本所支持的特性。
 
![][13]
 
## 12、循环中标签的使用
 
有的时候，循环中又嵌套了循环，你可能想在循环中退出，则可以用标签：
 
![][14]
 
## 13、提升
 
理解提升将帮助你组织你的function。只需要记住，变量声明和定义函数会被提升到顶部。变量的定义是不会的，即使你在同一行中声明和定义一个变量。此外，变量声明让系统知道变量存在，而定义是将其赋值给它。
 
![][15]
 
为了使事情更容易阅读，在函数作用域内提升变量的声明将会让你明确该变量的声明是来自哪个作用域。在你需要使用变量之前定义它们。在作用域底部定义函数，确保代码清晰规范。
 
## 14、为replace()方法传递一个函数
 
有的时候你想替换字符串的某个部分为其它的值，最好的方法就是给String.replace()传递一个独立的函数。下面是一个简单例子：
 
![][16]
 
## 15、使用document.createDocumentFragment()
 
您可能需要动态地追加多个元素到文档中。然而，直接将它们插入到文档中会导致这个文档每次都需要重新布局一个，相反的，你应该使用文档碎片，建成后只追加一次：
 
![][17]
 
![][18]
 


[0]: https://img2.tuicool.com/bINbmuY.jpg 
[1]: https://img2.tuicool.com/UbI36jm.jpg 
[2]: https://img2.tuicool.com/QnMjyuy.jpg 
[3]: https://img1.tuicool.com/maY7nmf.jpg 
[4]: https://img2.tuicool.com/j6RJBvz.jpg 
[5]: https://img2.tuicool.com/NvYrMvJ.jpg 
[6]: https://img0.tuicool.com/RVvaQzN.jpg 
[7]: https://img0.tuicool.com/i6nUNvq.jpg 
[8]: https://img1.tuicool.com/UNjQBb3.jpg 
[9]: https://img0.tuicool.com/eI3ABjY.jpg 
[10]: https://img2.tuicool.com/V7jiyiU.jpg 
[11]: https://img2.tuicool.com/VZzua2i.jpg 
[12]: https://img0.tuicool.com/bqArIru.jpg 
[13]: https://img2.tuicool.com/NfiqYrQ.jpg 
[14]: https://img1.tuicool.com/JBnIzyn.jpg 
[15]: https://img1.tuicool.com/N32MVzR.jpg 
[16]: https://img2.tuicool.com/yUjaqqZ.jpg 
[17]: https://img2.tuicool.com/MZ3AZbY.jpg 
[18]: https://img0.tuicool.com/R7Z36n3.jpg 