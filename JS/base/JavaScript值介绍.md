## JavaScript值介绍

来源：[https://segmentfault.com/a/1190000008817207](https://segmentfault.com/a/1190000008817207)


## 数组

和其他语言不同，在JavaScript中，数组可以拥有`不同值类型`,可以使`字符串`，`数字`，`对象`，还可以是`数组`(多维数组就是这样形成的).

声明数组后，可以直接通过索引的方式进行赋值:

```js
  var arr = [];
  arr.length;  //0

  arr [0]  =  12;
  arr [1]  = "ok";
  arr.length  //2
```

我们还可以使用`delete`运算符将`单元`从数组中移除：
避免冗余代码，继上写

```js
  délete arr [0]
  arr.length  //2  这是为什么呢？

  arr[0]   // undefined
```

我们来看一下使用`delete`运算符删除后的数组到底是什么样子的呢？

愿数组为 arr = [1,3,4,5]，我们delete arr [1] 


![][0]

我们发现使用`delete`删除数组单元，`length`属性并没有改变，对应的数组单元中，也确实删除了，我们对出现这种情况的数组，称之为`稀疏数组`.

在JavaScript类型介绍中，我们讲过，数组属于对象的子类型，那么我们可不可以通过对象查找属性的方式去访问数组呢？

```js
  var arr = [];

  arr["node"] = "ok";  
  arr["node"]  // "ok"
```

我们可以通过对象的键值去方位和操作它(`但这些并不计算在数组的长度内`)！
 代码继上⬆️

```js
   arr.length  // 0
   arr    //lenght:0 node:"ok";
```

这里有个问题需要特别注意，如果字符串键值能够被`强制类型转换`为十进制`数字`的话，就会被完全当作`数字索引`来处理。

```js
  var arr = [];
  arr["13"] = 42;
  arr.length   //14 
```

我们为arr[”13“]赋值，0-12单元默认为空(undefined)，这说明数组在使用字符串键值时会对它进行强制类型转换，如果不能转换为`number`类型,就只是单纯的字符串键值。
再来看最后一个例子:

```js
 var obj = {name:"mark"}
 var arr = []
 arr[obj] = "12";

 arr[obj]    //??????
 arr["[object Object]"]  //?????
```

好了不卖关子了，它们两个的结果都是"12",我们只需要记住一句话:数组键值如不是number，那么就遵循:`其他类型->字符串键值->数字键值`这一规律。这个例子当中，我们在赋值“12”时，就已经把obj转换成了`字符串"[object Object]"`，由于这段字符不能转换为`number类型`所以JavaScript会以`字符串键值`的形式储存。读取亦是如此。
### 类数组

说到它，我们先来看一张图:

![][1]

我们发现，类数组和纯数组的区别在于纯数组当中的原型链多了一层Array(我们称之为数组对象)，而类数组直接使用了内置的Object对象。

数组对象中包含了我们经常使用的数组方法及属性大家在控制台中输出看一下:

那是不是类数组就不可以使用纯数组当中的方法了呢？类数组当中没有其数组方法，正常不可以使用，但是不要忘记，我们还可以使用call方法。

```js
  function foo (){
     Array.prototype.push.call(arguments,2017);
     //为了方便查看，我们输出一下参数
     console.dir(arguments);
  }

 foo(1,2);   //[1,2,2017]
```

以上直接操作的argumens,也可以用slice工具函数`拷贝`新数组:

```js
 function foo(){
    var arr = Array.prototype.slice.call(arguments);
    arr.push(2017);
    console.dir(arr);
 }
 foo(1,2); //[1,2,2017]
```

使用ES6中内置的工具函数`from`也可以转换为纯数组:

```js
   var arr = Array.from(arguments);
```

我们之后再详细介绍ES6中的特性。这里暂且先不说.

数组和字符串很相似，我们可以把它们都看成`类数组`，都有`.length`和`indexof`属性。我们可以把它看成`人妖`,不男不女。好了，以后如果有人问你类数组是什么，你就可以大声的告诉他了...

可能有些童鞋对类数组的定义还是有些模糊，小编从犀牛书上找到了一句话，比较不错，看⬇️

JavaScript有一些特性是其他对象所没有的：


* 当有新的元素添加时，数组length属性更新

* 设置length为一个较小值，将截断数组

* 从Array.prototype继承一些方法

* 类属性为 Array



这些属性让JavaScript数组和常规对象哟明显的区别，但是他们并不是定制数组的本质特性。`一种常常完全合理的看法把拥有一个数值length属性和对应非负整数属性的对象看做一种类型的数组。`## 字符串

上面我们说过，字符串和数组都属于类数组，字符串内部的实现有没有使用数组并不好说，但JavaScript中的字符串和字符数组并不是一回事，最多只是看上去相似而已。

```js
例如:
```

```js
   var a = "foo";
   var b = ["f","o","o"];
```

它们都有length属性以及indexof和concat方法。

许多数组函数用来处理字符串很方便，虽然字符串没有这些函数，但可以通过`借用`数组的非变更方法来处理字符串:

```js
  var a = "foo";
  a.join;  //undefined
  a.map;   //undefined
  
  var c = Array.prototype.join.call(a,"-");
  var d = Array.prototype.map.call(a,function(v){
       return v.toUpperCase()
  }).join(".");
  
  c;       // "f-o-o";
  d;       // "F.O.O";
```

```js
还有一个不同点在于字符串反转(JavaScirpt面试常见问题)，数组有一个字符串字符串没有的可变更成员函数 reverse();
```

```js
  "".reverse;  //undefined
  [].reverse();   //Function
```

注意：这里不可以用call`借用`数组的可变更成员函数，因为字符串是不可变的。我们可以把字符串做一个转换，再进行操作:

```js
var a = "string",
    c = "string"
        .split("")
        .reverse()
        .join("");
        
    c;  //gnirts
```

如果经常要以字符数组的方式的话，还不如直接使用数组，避免来回折腾，有需要时再使用join转换为字符.
## 数字

JavaScript只有一种数值类型`number`,它没有真正意义上的整数，这也是他一直为人诟病的地方.所谓的整数就是没有小数点的十进制数，所以`42.0`等同于`42`。JavaScript的数字类型是基于`IEEE754标准`实现的，该标准也被称为`浮点数`,使用的是`双精度(即64位2进制)`;

由于数字值可以使用Number对象进行封装，因此数字值可以调用Number.prototype中的方法。例如toFixed方法可指定小数的部分的显示位数:

```js
  var a = 42.59;
  a.toFixed(0);  //42
  a.toFixed(1);  //42.6
  a.toFixed(2);  //42.59
  a.toFixed(3)   //42.590
```

注意，上例中的参数数值如果大于当前数位，其余部分则用0补充，另外大家也应该看到，toFixed的参数数值如果小于其数字数位就会进行四舍五入。

toPrecision()方法用来指定有效数位的现实位数：

```js
  var a = 42.59;
  a.toPrecision(1) //4e+1
  a.toPrecision(2) //43
  a.toPrecision(3) //42.6
  a.toPrecision(4) //42.59
```

在这里介绍一种情况：

```js
    42.toFixed();  //SyntaxError
```

我们要注意，不可使用数字常量直接访问其方法，因为JavaScript会认为.是`常量的一部分`,我们可以赋给变量进行操作，或者可以这样.

```js
  var a = 42;
  42.toFixed(1);

  42..toFixed(1);
```

我们使用变量和..解决，不过不推荐使用第二种方式，在写程序时我们也不会直接拿常量直接使用，在这我们稍作了解即可.
### 较小的数值

二进制浮点数最大的问题就在于(所有使用IEEE754规范的语言都是如此)，是会出现如下情况:

```js
  0.1 +  0.2  ===0.3   //false
```

从数学角度来讲上面的例子应该返回true,可是会什么会返回false呢？
是因为二进制浮点数中的0.2和0.3都不是非常精确，它们相加的结果并非刚好等于0.3，而是一个比较接近的数字:0.000000000004，所以条件判断为false。

那么应该怎样判断0.1+0.2是否相等呢？
最常见的方法是设置一个误差范围，通常称为“机器精度”。
从ES6开始，该值定义在number.EPSILON中，我们可以直接拿来用，也可以为ES6之间的版本写一个polyfill:

```js
   if(!Number.EPSILON){
       Number.EPSILON = Math.pow(2,-52)
   }
```

可以使用Number.EPSILON来比较两个数字是否相等(在指定的误差内);

```js
   function numberCloseEnoughToEqual(n1,n2){
       return Math.abs(n1 - n2) < Number.EPSILON;
   var a = 0.1 + 0.2;
   var b = 0.3;
   numberCloseEnoughToEqual(a,b);     //true
   numberCloseEnoughToEqual(0.0000001,0.0000002); //false
 }
```

能够呈现的最大浮点数大约是1.798e+308（这是一个相当大的数字），它定义在Number.MAX_VALUE中，最小浮点数定义在Number.MIN_VALUE中，大约是5e-334，它不是负数，但无限接近于0！
### 整数类型检测

ES6当中新增`Number.isInteger`方法

```js
   Number.isInteger(32)          //true
   Number.isInteger(32.3)       //false
```

为该方法添加polyfill:
if(!Number.isInteger){

```js
 Number.isInteger = funcion(n){
           return typeof n === "number" && n  % 1 === 0;
}
```

}
### 不是值的值

对于null和undefined，undefined只有一个值为undefined,  null类型也只有一个类型，即null，它们的名称即是类型也是值。
null (空值)
undefined (未被赋值)
`null为关键字，undefined为标识符`.
在我们非严格模式下，是可以对标识符赋值的:

```js
  function foo (){
      undefined = 12;   //为undefined赋值
   }
   
  foo();
  
  function foo (){
       'use strict'
       undefined  = 12  //Type Error
   }
   
   foo();  
```

我们只需要了解这一点就可以，实际使用当中，是绝对不可以这样做的.

void运算符
undefined 是一个内置的标识符，我们可以用void运算符来定义一个表达式的返回值;

void并不改变表达式的返回值，它只是让表达式不返回值; 
假如我们现在要写一个setTimeout计时器，由于这个方法每次都返回唯一的标识符，那么我们就可以使用void 掉它;

```js
  void  setTimout(function(){})
```
### 不是数字的数字

我们都知道在javaScript数字运算中有一种情况为NaN，如:

```js
   1/"a"   //NaN
   []/{}    //NaN
   ""/{}    //NaN
```

我们发现有两种情况为NaN：数字运算中(出现数字运算符)值非Number类型时，或者无法正常解析为10进制或者16进制的有效数字.
可以使用全局方法isNaN来判断是否为NaN

```js
   var s = 1/"a"  
   isNaN(s)        //true        
```

可怕的是NaN连它自己都不想等，这也是JavaScript中唯一一个`非自反`的值

```js
   NaN == NaN      // false
   NaN === NaN   //false
   
   NaN !=  NaN      //true
```

NaN的寓意是`不是一个数字`(Not a Number) ，"不是一个数字" 说到我们不得这个不看一段代码:

```js
   var str = "abc";
   var no = 1/"a";
   
   isNaN(no)    //true
   isNaN(str)     // true --晕
```

这个bug已经存留很久，我们在程序中尽量不要直接使用isNaN方法，可以polyfill或使用ES6的Number.isNaN

```js
   var str = "abc";
   var no = 1/"a";
   
   Number.isNaN(no)     //true;
   Number.isNaN(str)       //false
```

polyfill有两种写法，这里一起贴代码给大家：

```js
 // v1 
 if(!Number.isNaN){
           Number.isNaN = function(n){
             typeof n === "number"  &&  window.isNaN(n)
         }
 }
 
 //v2
 if(!Number.isNaN){
           Number.isNaN = function(n){
             return n !== n
         }
 }
```

第二种方法很简洁，正是利用了我们上面讲过的`NaN是js中唯一一个不和自己全等的特性`大家在程序中如果使用isNaN方法，一定要进行二次改造，否则程序有可能会出问题。可以直接在页面script里加入我们js需要添加的polyfill;
### 无穷数

javaScript中使用有限数字表示法，也就是我们之前介绍过的IEEE754浮点数，所以它和纯数字的数学运算不同，JavaScript的运算结果可能会溢出，此时结果为Infinity或者-Infinity。

```js
  var a = Number.MAX_VALUE;  //1.7976931348623157e+308
 
  1/0   //Infinity
  a + Math.pow(2,970) //Infinity
  a + Math.pow(2,969)  //1.7976931348623157e+308
  a  + a   //Infinity
```

规范规定，如果数学运算的结果超出处理范围，则由`IEEE754规范中的"就近取整"`来决定最后的结果，这里的Math.pow(2,969)更为接近Number.MAX_VALUE，
所以被向下取整， Math.pow(2,970) ＋  Number.MAX_VALUE与Infinity更为接近，所以被向上取整。

那如果对Infinity进行数字运算呢？会出现什么情况？

```js
  Infinity + Infinity // Infinity
  Infinity / Infinity //NaN
  Infinity * Infinity  //Infinity
Infinity - Infinity  //NaN
```

我们可以这样理解由于＋ 和 ＊ 都无需知道Infinity它是多少值，他们肯定比现在的值大，所以一定是Infinity；
如果是- 或者 /运算符，在这样的条件下他们的值一定小于现在的值，无穷大本身就不是一个有效数字，那么小于它的值我们没法判断，所以JavaScript给出的解释是NaN;
### 零值

在js中 0 也有两种表达方式:`－0 和 0`
我们先来看看代码:

```js
   0 *  -3  //-0
    0 / -3  //-0
```

加法和减法不会产生－0，0全等于－0

```js
  ""+-0   //"0"
  JSON.stringify(-0) //"0"
  
  +"-0"  // -0
```

在把－0字符串化后，会转化为0；把“-0”转换为number时还会恢复过来，是不是很奇怪？

那么我门在程序中到底如何区分 0 与 －0呢？我们可以拿 1/－0 等于 - Infinity 来进行条件判断;

```js
 function isNegZero (n){
         Number(n);
        return ( n === 0 && (1 / n === -Infinity) )
 }
     isNegZero(-0) //true
    isNegZero(0)  //false
```

抛开学术，我们为什么需要负零呢？
下面是来自《你不知道的JavaScript 中卷》的一句话;
有些应用程序中的数据需要以级数形式来表示(比如动画贞的移动速度)，数字的符号位用来代表其他位置信息，
此时如果一个值为0的变量失去了它的符号位，它的方向就会丢失，所以保留0值就可以防止类似的事情发生。
以上说的只是一种情况，在实际开发当中，我们面对复杂的业务需求，也有可能要使用它，所以这里我们要记牢它，以备日后之用。
### 特殊等式

以上我们写了很多的检验函数，在ES6中，只有一个很好玩的方法，叫做Object.is，说到这个函数肯定会有很多人喷我，
如果早说这个方法就没必要写那些了，其实不然，我们了解的不仅是js的特性，也是解决问题的方法.

```js
  var a = 1/"asd";   //NaN
  var o = 1 * -0;   //-0
  
  Object.is(a,NaN)   //true
  Object.is("a",a)        //false
  
  Object.is(o,0)  //false
  Object.is(o,-0)  //true
```

当然少不了polyfill

```js
    if(Object.is){
        Object.is = function(v1,v2){
              if(v1 === 0 && v2 === 0){
                 return 1/ v1 === 1/v2
            }
            //为NaN比较时；
            if(v1 !== v1){
                return v2 !== v2  //以上条件判断，参数1一定为NaN,然后再判断第二个参数，是否为NaN,
            }
            //如果都不是那么就做全等比较
            return v1 === v2  
            //
        }
    }
```

[0]: https://segmentfault.com/img/bVKRqx
[1]: https://segmentfault.com/img/bVKSBo