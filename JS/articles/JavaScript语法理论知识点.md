## JavaScript语法理论知识点

来源：[./a/1190000013844569](https://segmentfault.com/a/1190000013844569)


## 前言

这个笔记不知道什么时候记下的反正很有意思，很基础，很理论。
## JavaScript学习笔记1
## 第一章 JavaScript概述
### 1.1 什么是JavaScript

JavaScript是一种轻量级的脚本语言，也是一种嵌入式(embedded)语言，是一种对象模型语言。

脚本语言又被称为扩建的语言，或者动态语言，是一种编程语言，用来控制软件应用程序，脚本通常以文本（如ASCII)保存，只在被调用时进行解释或编译，在依靠特定的宿主环境提供API来实现操作和效果。常见的宿主环境有浏览器，服务器环境（操作系统）。
嵌入式语言一句话就是不能独立做事，插入到其他语言才能用的语言。
### 1.2 使用方法
#### 1.2.1 内部引用（标签引入）

理论上·标签可以放HTML代码的任意位置，实际开发中对于函数的调用，代码的执行通常放入body标签下面；函数的定义，类的定义以及外部文件的引入通常放入head标签中。
#### 1.2.2 外部引入

在head标签中写引入文件的代码即可。
#### 1.2.3 那个用法最好？



* 第三方框架或者库文件的引入都使用外部引入

* 自己写的少量代码用标签引入

* 大量代码最好外部引入，对于前端代码的优化维护有利


## 第二章 JavaScript基本语法
### 2.1 变量

变量是用来临时存储数据内容的容器，在使用过程中可以随时改变存储的值。

是否编程语言的前提是是否有变量，有变量才算得上真正的编程语言。
#### 2.1.1 变量及变量类型

变量命名规则：使用var关键字声明变量；数字，字母，下划线，$，且不能数字开头；可以用各种命名法。var不写则是全局变量；

JavaScript中中文可以作为变量名是可以的，因为JavaScript语言本身就是使用ut8编码,一般不使用中文作为变量名，因为占的空间大，显得low
数据类型：数字，字符串，布尔，对象，null，undefined

在JavaScript中数据类型粉三大类：简单类型（数字，字符串，布尔），复合类型(数组，对象，函数)，特殊类型(null,undefined),注意JavaScript中没有数组类型这一说法，用typeof判断就说其是object。
对比一下PHP的数据类型：1.整形2.字符串3.浮点型4.null5.布尔类型6.资源型7.数组类型8.对象
#### 2.1.2 检测值类型

用typeof来判断数据类型，返回类型有:Number,String,boolean,undefined,function,object;

注意没有null这一类型,
#### 2.1.3 null 和defined的区别

为什么null的类型是object？

这是由于历史原因造成的。 1995年JavaScript语言的第一版， 当时， 只设计了五种数据类型（对象、 整数、 浮点数、字符串和布尔值） ， 完全没考虑null， 只把它当作object的一种特殊值， 为了兼容以前的代码， 后来就没法修改了。
这并不是说null就属于对象， 本质上就是一个特殊值， 表示“没有”。
而在ES6草案时， 也曾将 null 的数据类型修改为了 null ,但是因为兼容性问题， 后来又改回了object。
null和undefined的区别？

null与undefined都可以表示“没有”， 含义非常相似;宽松比较时，两者值相等，都表示空，无，没有;
但是， JavaScript的值分成原始类型和合成类型两大类， Brendan Eich(JS作者)觉得表示”无”的值最好不是对象；其次， JavaScript的最初版本没有包括错误处理机制， 发生数据类型不匹配时， 往往是自动转换类型或者默默地失败。我觉得， 如果null自动转为0， 很不容易发现错误。于是又设计了一个undefined。
具体的说有以下区别：


* 宽松比较时(双等号)，两者值相等，都表示空，无，没有。严格比较时(全等号)不相等；

```js
var n=null;
var d=undefined;

var s=(n==d)
alert(s);
var f=(n===d);
alert(f);
```


* 获取一个不存在的对象时，值是Null

```js
var d=document.getElementById('div');
alert(typeof(d));//object
alert(d);//null
```



* null检测数据类型时是object,undefined就是类型本身undefined

* null表示一个“无”对象，数据类型转换为数值时是0;undefined 表示一个"无"的原始数据，数据类型转换为数值时是NaN


```js
var n=Number(null);
var d=Number(undefined);
alert(n);//0
alert(d);//NaN
```

5.出现undefined的几种情况:

A.变量声明但没有赋值时

```js
 var i;
 alert(typeof(i));//undefined
```

B.函数需要传参但并没有传值时

```js
function f(x){
    return x;//undefined
}
var p=f();
alert(p);
```

C.访问不存在的属性时，出现undefined

```js
var o={};
alert(typeof(o.p));
```

D.函数没有返回值时，函数的返回值是undefined

```js
function h(){};
alert(h());//undefined
```
### 2.2 运算符
#### 2.2.1 算数运算符

加，减，乘，除，取余，自增，自减，举个有趣点的案例：

```js
var i=10;
var j=++i;
var h=i++;
var k=++i;
//没有赋值操作前自增和后自增是没有区别的。
console.log(j);//11
console.log(k);//13
console.log(h);//11
console.log(i);//13
```

复合运算：

```js
//复合赋值运算符 +=，-=，*=，/=
//三目运算符 条件？代码1：代码2; 条件?true：false；
```
#### 2.2.2 比较运算符

```js
//比较运算符 < > == === <= >= != !==
```
#### 2.2.3 逻辑运算符

逻辑运算符 ！ || && 三目运算符等

逻辑与解析图：


![][0]

逻辑或解析图


![][1]
### 2.3 流程控制



* 顺序结构：从上而下

* 分支结构（选择结构）：if else if else 和switch。


if else 和 switch的区别？

if结构不仅可以判断固定值， 还可以判断范围区间。switch结构只能判断固定值情况。


3.循环结构：while,for,do while等

4.continue和break的区别；

continue:跳出当前循环，继续下次循环。break:跳出整个循环结构，也就相当于结束循环。


### 2.4 数组
#### 2.4.1 数组的简单使用

数组是一组有序数据的集合，在内存中表现为一段连续的内存地址。

数组的声明也很简单：

var arr=[1,2,3,4];var arr=new Array(1,2,3,4);

var arr=new Array(2); arr[0]=1;arr[1]=2;arr[2]=3;


多维数组：数组的元素也是一个数组，则父数组是多为数组。

var arr=[1,2,[3,4,5,[6,7]]];是个三维数组
获取数组元素：通过下标获取（数组[下标]），多为数组的话所有下标都写上，不然只的到所在行的全部元素。

数组的遍历：

最常用的通过for循环，根据循环语法，在循环之前先获取数组长度
```js
var arr=['Apple','Huawei','SumSung'];
var len=arr.length;
for(var i=0;i<len;i++){
    console.log(arr[i]);
}
```

for...in循环遍历数组：for..in可以遍历对象，也可以遍历数组，毕竟数组也是个特殊的对象。
```js
var arr=['Apple','Huawei','SumSung'];
for(var i in arr){
    //每次遍历是，系统自动将元素的索引下标放入变量i中
    console.log(arr[i]);
}
```
#### 2.4.2 数组对象的属性及方法（很重要，背下来）

length属性：返回数组的成员数量即数组的长度。
数组对象的常用方法：


* push方法：用于在数组的末端添加一个或多个元素，并返回新元素的数组长度。注意push方法会改变原数组。

```js
var a=[];
a.push(1);
alert(a);//1
a.push('a');
console.log(a);//Array[1,'a']
a.push(true,{});
console.log(a);//Array [ 1, "a", true, {} ]
```


* pop方法：用于删除数组的最好一个元素，并返回该元素。注意，pop方法会改变原数组

```js
var a=['a','b','c'];
var b=a.pop();//c
console.log(a);//Array['a','b']
console.log(b);//c
```


* join方法：用于参数分隔符，将所有数组成员一个字符串返回，如果不提供参数，默认用逗号分隔。不改变原数组。

```js
var a=[1,2,3,4];
var b=a.join('|');
console.log(b);//1|2|3|4
var c=a.join();
console.log(c);
```


* concat方法：用于多个数组的合并，它将新数组的成员添加到原数组的尾部，然后返回一个新的数组，原数组不变。

```js
var a=['hello'];
var b=['world'];
var d=a.concat(b);
console.log(d);//Array [ "hello", "world" ]
console.log(d.concat(['!'],['A']));//Array [ "hello", "world", "!", "A" ]
```


* shift方法：用于删除数组的第一元素，并返回给该元素。注意改变原数组。

```js
var a=[1,2,3];
var b=a.shift();
console.log(a);//Array [ 2, 3 ]
console.log(b);//1
```


* unshift方法：用于在数组的第一个位置添加一个元素，并返回新加元素后的数组长度。注意该方法会改变原数组。

```js
var a=[1,2,3];
var b=a.unshift(5);
console.log(a);//Array [ 5, 1, 2, 3 ]
console.log(b);//4
```


* reverse方法：用于颠倒数组中的元素，返回改变后的数组。注意，该方法将改变原数组。

```js
var a=[1,2,3];
var b=a.reverse();
console.log(a);//Array [ 3,2,1 ]
console.log(b);//Array [ 3,2,1 ]
```


* slice方法：用于提取原数组中的一部分元素（相当于截取）,返回一个新数组，原数组不变。它的第一个参数为起始位置（从0开始） ， 第二个参数为终止位置（但该位置的元素本身不包括在内） 。如果省略第二个参数， 则一直返回到原数组的最后一个成员。

```js
var a = ['a','b','c','d','e'];
console.log(a.slice(0)) // ["a", "b", "c", "d", "e"]
console.log(a.slice(1)) // ["b", "c", "d", "e"]
console.log(a.slice(1,3)); // ["b", "c"]
```


* splice方法：用于删除原数组中的一部分元素，并可以在被删除的位置添加新数组成员，返回值是被删除的元素。注意，该方法会改变原数组。splice的第一个参数是删除的起始位置， 第二个参数是被删除的元素个数

```js
var a = ['a', 'b', 'c', 'd', 'e', 'f'];
var a1 =  a.splice(4, 2);
console.log(a1); //Array["e", "f"]
console.log(a); // Array["a", "b", "c", "d"]

var b = ['a', 'b', 'c', 'd', 'e', 'f'];
var a2 = b.splice(1, 2, 1, 2);
console.log(a2); //["b", "c"]
// console.log(b);//["a", 1, 2, "d", "e", "f"]
```


* forEach方法：用于遍历数组的所有成员，执行某种操作；forEach方法的参数是一个函数，数组的所有成员会依次执行该函数，它接受三个参数，分别是当前位置的值，当前位置的编号和整个数组

```js
var a = ['a', 'b', 'c', 'd', 'e', 'f'];
a.forEach(function(v,k,h){
    console.log(v);
    console.log(k);
    console.log(h);
});
//第三个参数可以写可以不写，它带便遍历次数
```
## 第三章 函数
### 3.1 函数概述

函数就是制作工具的工具，比如计算器就是一个工具，而制作计算器的工具就是函数，也就是制作工具的工具。一次定义多次使用。

用函数的好处：节省代码的数量，减少代码量，使代码可以重复使用，节省空间，节省时间，使程序代码具有结构化，模块化，后期维护更友好等等很多好处
### 3.2 函数基本使用
#### 3.2.1 函数的声明及调用

多次声明同一个函数的话，最后一次声明的函数会覆盖前面的函数，前面的声明在任何时候都是无效的。

递归函数：函数内部调用函数自身，称之为递归。只要是递归必须的有判断，不然它是个死循环，用别的函数解决的问题最好别用递归解决，递归占内存大，不友好。

```js
function Recursion(x){
    if(x>1){
        return x+Recursion(x-1);
    }else{
        return 1;
    }
}
console.log(Recursion(100));
```
#### 3.2.2 函数的参数及返回值

函数的参数有形参和实参：

形参就是函数声明时需要接受的参数，可以理解成暂时的占位符，并无实际意义实参就是调用函数是传递进函数的具体的实际数据，也就是给占替代位符的的值


函数体内部的return语句：表示将数据返回给调用者。return后面即使有语句，也不会执行，也就是return后面不执行.return语句可有可无，没有则不反悔任何值或者说返回undefined。

函数中的arguments对象：arguement是函数调用时的实参列表；只是实参列表

```js
function Argu(a){
    console.log(arguments);
}
Argu(1,2,3);
```

aruguments对象带有一个callee属性，返回他所对应的原函数。callee代表当前运行的函数

```js
function Argu(a){
    console.log(arguments.callee);
}
Argu(1,2,3);
```
#### 3.2.3 自调用匿名函数

函数可以没有名字吗？当然可以:(function(){})();

为什么要有自调用匿名函数？

　因为有名函数有缺点，可能运行时会出现命名冲突，如果在编写程序时，直接采取自调用匿名函数，则不会产生命名冲突问题。市场上很多框架，如JQuery.js，ext.js等都是采用匿名函数进行封装。
使用自调用匿名函数结合aruguments对象实现递归：

```js
var a = (function (n) {
            if (n > 1) {
                return n + arguments.callee(n - 1);
            } else {
                return 1;
            }
        })(100);
console.log(a);
```
### 3.3 函数作用域
#### 3.3.1 定义

作用域指的是变量存在的范围。JavaScript中作用域有两种局部作用域和全局作用域。

局部作用域：变量只在函数的内部存在。在函数内使用var声明的变量是局部变量，是人为的声明。全局作用域：变量在整个程序中存在，所有地方都可以读取。全局变量一个是函数外声明的变量；还有一个是函数内不使用var的变量（仅仅带便变量被赋值),也就是如果不是人为定义，系统会定义，系统定义的变量在整个程序中存在，不加var会污染全局。


```js
function a(){
    b=1
}
a();
console.log(b);
```

局部变量会替代全局变量：函数内部声明的变量会在函数内部区域覆盖同名的全局变量。

　这说明javascript的函数在查找自身函数定义开始，从“内”向“外”查找。
```js
var a=3;
function fun(){
    var a=2;
    console.log(a);
}
fun();//2
console.log(a);//3
```

如果函数内部不使用var关键字，那么函数内部的赋值将会影响全局变量。实际上，JavaScript默认哟偶一个全局的对象窗口，全局作用域的变量实际上是被绑定到窗口对象上的一个属性，因此，直接访问全局对象a和访问window.a是完全一样的


```js
var a=3;
function fun(){
    a=2;
    console.log(a);
}
fun();//2
console.log(a);//2
```

作用域解释图：

![][2]
#### 3.3.2 变量提升

JavaScript的函数定义有个特点，他会先扫描整个函数体呃逆的语句，把所有声明的变量提升到函数的顶部，注意只是把声明提升了，并不会提升变量的赋值。

```js
function fun(){
    console.log(a);//undefined
    var a=2;
    //JavaScript解析引擎来说相当于
    /**
    *var a;
    *var b=1+a;
    *alert(b);
    *a=2;
    **/
}
fun();
```
#### 3.3.3 函数本身的作用域

函数本身也是一个值，也有自己的作用域；函数的作用域与变量一样，就是它声明时所作的作用域，与其运行时所在的作用域无关

函数执行时的作用域是定义时的作用域，而不是调用时的作用域。

```js
var a=3;
var x=function(){
    console.log(a);
}
function f(){
    var a=4;
    x();
}
f();//3
```

再看这个：

```js
var x=function(){
    console.log(a);
}
function y(f){
    var a=2;
    f();
}
y(x);//ReferenceError: a is not defined
//函数执行时的作用域是定义时的作用域，而不是调用是的，所以，这代码运行结果是这样。
```

继续看代码

```js
function fun(){
    var a=2;
    function bar(){
        console.log(a);
    }
    return bar;
}
var a=4;
var f=fun();
f();//2
```
## 第四章 语法分析
### 4.1 JavaScript代码的编译以及执行

JavaScript代码运行，分为编译阶段和执行阶段：

编译阶段:声明变量，声明函数(display)，语法检查等操作，一旦出错不会执行下一阶段，除了错误提示不输出别的内容执行阶段：变量的赋值，函数的调用，代码的执行等操作，这一阶段出错的话出错之前的内容执行；


```html
<script>
    console.log(1);
    console.log(s);
    console.log(3);
    //执行结果是：1  错误提示：找不到变量s
    //原因代码编译阶段没有问题，执行阶段由于发生了错误，错误后面不会执行
</script>
<script>
    console.log(3);
    console.log(4)
    console.log(4);
    //执行结果是：错误提示：有语法错误请检查
    //原因：代码编译阶段就出错不再执行执行阶段
</script>

```
### 4.2 script代码段

在html中<script></script>是一段独立的代码，这一段代码出错不会影响下一个<script></script>代码段的执行；不管前面的代码段错误出现在编译阶段还是执行阶段都不会影响下一段代码的执行。

为什么呢？

虽然script代码段在一个页面，但是script代码并不是一起执行，而是分开解析与执行。JavaScript解析引擎从上而下读取第一个代码段-->放入内存-->编译阶段-->执行阶段-->下一个JavaScript代码段-->放入内存...等操作；

总之一句话，JavaScript解析引擎执行完一段代码再执行下一段代码，每一段代码都是独立的存在。因此，前一个代码无论发生什么错误都不会影响下一个代码段的执行


看图：

![][3]
## 参考资料

[W3school][4]
[菜鸟教程][5]
[JavaScript权威指南（第6版）][6]

[4]: http://www.w3school.com.cn/b.asp
[5]: http://www.runoob.com/js/js-tutorial.html
[6]: http://item.jd.com/10974436.html
[0]: ./img/bV6fJK.pbg
[1]: ./img/bV6fJL.pbg
[2]: ./img/bV6fJz.pbg
[3]: ./img/bV6fJo.pbg