## 【译】理解JavaScript中的柯里化

来源：[http://www.cnblogs.com/GeniusLyzh/p/9937829.html](http://www.cnblogs.com/GeniusLyzh/p/9937829.html)

时间 2018-11-10 00:35:00



## 译文开始


函数式编程是一种编程风格，这种编程风格就是试图将传递函数作为参数（即将作为回调函数）和返回一个函数，但没有函数副作用（函数副作用即会改变程序的状态）。

有很多语言采用这种编程风格，其中包括JavaScript、Haskell、Clojure、Erlang和Scala等一些很流行的编程语言。

函数式编程凭借其传递和返回函数的能力，带来了许多概念：


* 纯函数
* 柯里化
* 高阶函数      

其中一个我们将要看到的概念就是柯里化。      

在这篇文章，我们将看到柯里化是如何工作以及它如何在我们作为软件开发者的工作中发挥作用。    
  


## 什么是柯里化

柯里化是函数式编程中的一种过程，可以将接受具有多个参数的函数转化为一个的嵌套函数队列，然后返回一个新的函数以及期望下一个的内联参数。它不断返回一个新函数（期望当前参数，就像我们之前说的那样）直到所有参数都用完为止。这些参数会一直保持“存活”不会被销毁（利用闭包的特性）以及当柯里化链中最后的函数返回并执行时，所有参数都用于执行。


柯里化就是将具有多个arity的函数转化为具有较少的arity的函数。——[kbrainwave][0]

备注：术语arity（元数）：指的是函数的参数个数，例如：

```js
function fn(a, b) {
    //...
}
function _fn(a, b, c) {
    //...
}
```


函数fn有两个参数（即 2-arity函数）以及_fn有三个参数（即3-arity函数）。

因此，柯里化将一个具有多个参数的函数转化为一系列只需一个参数的函数。

下面，我们看一个简单的例子：

```js
function multiply(a, b, c) {
    return a * b * c;
}
```

这个函数接收三个数字并且相乘，然后返回计算结果。

```js
multiply(1,2,3); // 6
```

接下来看看，我们如何用完整参数调用乘法函数。我们来创建一个柯里化版本的函数，然后看看如何在一系列调用中调用相同的函数（并且得到同样的结果）。

```js
function multiply(a) {
    return (b) => {
        return (c) => {
            return a * b * c
        }
    }
}
log(multiply(1)(2)(3)) // 6
```


我们已经将multiply(1,2,3)函数调用形式转化为multiply(1)(2)(3)多个函数调用的形式。

一个单独的函数已经转化为一系列的函数。为了得到三个数字1、2、3的乘法结果，这些数字一个接一个传递，每个数字会预先填充用作下一个函数内联调用。

我们可以分开这个multiply(1)(2)(3)函数调用步骤，更好理解一点。

```js
const mul1 = multiply(1);
const mul2 = mul1(2);
const result = mul2(3);
log(result); // 6
```

我们来一个接一个地传递参数。首先传参数1到multiply函数：

```js
let mul1 = multiply(1);
```

以上代码执行会返回一个函数：

```js
return (b) => {
        return (c) => {
            return a * b * c
        }
    }
```


现在，变量mul1会保持以上的函数定义，这个函数接收参数b。

我们调用函数mul1，传入参数2：

```js
let mul2 = mul1(2);
```

函数mul1执行后会返回第三个函数

```js
return (c) => {
            return a * b * c
        }
```


这个返回的函数现在保存在变量mul2中。

本质上，变量mul2可以这么理解：

```js
mul2 = (c) => {
            return a * b * c
        }
```

当传入参数3调用函数mul2时，

```js
const result = mul2(3);
```

会使用之前传入的参数进行计算：a=1，b=2，然后结果为6。

```js
log(result); // 6
```


作为一个嵌套函数，mul2函数可以访问外部函数的变量作用域，即multiply函数和mul1函数。

这就是为什么mul2函数能使用已经执行完函数中定义的变量中进行乘法计算。虽然函数早已返回而且已经在内存中执行垃圾回收。但是它的变量还是以某种方式保持“存活”。

  
备注：以上变量保持存活是闭包特性，不明白可以查看闭包相关文章了解更多

你可以看到三个数字每次只传递一个参数应用于函数，并且每次都返回一个新的函数，值得所有的参数用完为止。

下面来看一个其他的例子：

```js
function volume(l,w,h) {
    return l * w * h;
}
const aCylinder = volume(100,20,90) // 180000
```


上面是一个计算任何实心形状体积的函数。

这个柯里化版本将接受一个参数以及返回一个函数，该函数同样也接受一个参数和返回一个新的函数。然后一直这样循环/继续，直到到达最后一个参数并返回最后一个函数。然后执行之前的参数和最后一个参数的乘法运算。

```js
function volume(l) {
    return (w) => {
        return (h) => {
            return l * w * h
        }
    }
}
const aCylinder = volume(100)(20)(90) // 180000
```

就像之前的multiply函数那样，最后的函数只接受一个参数h，但是仍然会对那些早已执行完返回的函数作用域中里的其他变量执行操作。能这样操作是因为有闭包的特性。


译者注：以上写的很啰嗦，感觉另外的例子完全就是重复说明。

柯里化背后的想法其实是获取一个函数并派生出一个返回特殊函数的函数。

  
## 柯里化在数学方面的应用


我有点喜欢数学说明:point_right:[维基百科][1]进一步展示了柯里化的概念。下面用我们的例子来进一步看下柯里化。

假设有一个方程

```js
f(x,y) = x^2 + y = z
```


有两个变量x和y，如果这两个变量分别赋值x=3和y=4，可以得到z的值。

下面我们在函数f(x,y)中替换变量的值为y=4和x=3：

```js
f(x,y) = f(3,4) = x^2 + y = 3^2 + 4 = 13 = z
```


得到z的结果为13

我们也可以将f(x,y)柯里化，在一系列的函数里提供这些变量。

```js
h = x^2 + y = f(x,y)
hy(x) = x^2 + y = hx(y) = x^2 + y
[hx => w.r.t x] and [hy => w.r.t y]
```

注：hx表示h下标为x的标识符，同理hy表示h下标为y的标识符。w.r.t(with respect to)，数学符号，表示关于，常用于求导，或者满足一定条件之类的情况

我们使方程f(x,y)=x^2+y的变量x=3，它将返回一个以y为变量的新方程。

```js
h3(y) = 3^2 + y = 9 + y
注：h3 表示h下标为3的标识符
```

也等同于：

```js
h3(y) = h(3)(y) = f(3,y) = 3^2 + y = 9 + y
```


函数的结果还是没有确定的，而是返回一个期望其他变量y的一个新方程 9+y。

下一步，我们传入y=4

```js
h3(4) = h(3)(4) = f(3,4) = 9 + 4 = 13
```


变量y是变量链中的最后一个，然后与前一个保留的变量x=3执行加法运算，值最后被解析，结果是12。

所以基本上，我们将这个方程f(x,y)=3^2+y柯里化为一系列的方程式，在最终结果得到之前。

```js
3^2 + y -> 9 + y
f(3,y) = h3(y) = 3^2 + y = 9 + y
f(3,y) = 9 + y
f(3,4) = h3(4) = 9 + 4 = 13
```

好了，这就是柯里化在数学方面的一些应用，如果你觉得这些说明得还不够清楚。可以在[维基百科][1]阅读更详细的内容。


## 柯里化和部分应用函数


现在，有些人可能开始认为柯里化函数的嵌套函数的数量取决于它接受的参数。是的，这就是柯里化。

我可以设计一个这样的柯里化函数volume：

```js
function volume(l) {
    return (w, h) => {
        return l * w * h
    }
}
```

所以，可以像这样去调用：

```js
const hCy = volume(70);
hCy(203,142);
hCy(220,122);
hCy(120,123);
```

或者是这样：

```js
volume(70)(90,30);
volume(70)(390,320);
volume(70)(940,340);
```


我们刚刚定义了专门的函数，用于计算任何长度(l)，70圆柱体积。

它接受3个参数和有2层嵌套函数，跟之前的接受3个参数和有3层嵌套函数的版本不一样。

但是这个版本并不是柯里化。我们只是做了一个部分应用的volume函数。

柯里化和部分应用函数有关联，但是它们是不同的概念。

部分应用函数是将一个函数转化为具有更少的元素（即更是的参数）的函数。

```js
function acidityRatio(x, y, z) {
    return performOp(x,y,z)
}
|
V
function acidityRatio(x) {
    return (y,z) => {
        return performOp(x,y,z)
    }
}
```


注：我故意没有实现performOp函数。因为这里，这个不是必要的。你所需要知道的是柯里化和部分应用函数背后的概念就可以。

这是acidityRatio函数的部分应用，并没有涉及柯里化。acidityRatio函数应用于接受更少的元数，比原来的函数期望更少的参数。

柯里化可以这样实现：

```js
function acidityRatio(x) {
    return (y) = > {
        return (z) = > {
            return performOp(x,y,z)
        }
    }
}
```


柯里化是根据函数的参数数量创建嵌套函数，每个函数接受一个参数。如果没有参数，那就没有柯里化。

可能存在一种情况，即柯里化和部分应用彼此相遇。假设我们有一个函数：

```js
function div(x,y) {
    return x/y;
}
```

如果写出部分应用形式，得到的结果：

```js
function div(x) {
    return (y) => {
        return x/y;
    }
}
```

同样地，柯里化也是同样地结果：

```js
function div(x) {
    return (y) => {
        return x/y;
    }
}
```


虽然柯里化和部分应用函数给出同样地结果，但它们是两个不同的存在。

像我们之前说的，柯里化和部分应用是相关的，但设计上实际是完全不一样的。相同之处就是它们都依赖闭包。

  
## 函数柯里化有用吗？

当然有用，柯里化马上能派上用场，如果你想：


### 1、编写轻松重用和配置的小代码块，就像我们使用npm一样：

举个例子，比如你有一间士多店并且你想给你优惠的顾客给个10%的折扣（即打九折）：

```js
function discount(price, discount) {
    return price * discount
}
```

当一位优惠的顾客买了一间价值$500的物品，你给他打折：

```js
const price = discount(500,0.10); // $50 
// $500  - $50 = $450
```

你可以预见，从长远来看，我们会发现自己每天都在计算10%的折扣：

```js
const price = discount(1500,0.10); // $150
// $1,500 - $150 = $1,350
const price = discount(2000,0.10); // $200
// $2,000 - $200 = $1,800
const price = discount(50,0.10); // $5
// $50 - $5 = $45
const price = discount(5000,0.10); // $500
// $5,000 - $500 = $4,500
const price = discount(300,0.10); // $30
// $300 - $30 = $270
```

我们可以将discount函数柯里化，这样我们就不用总是每次增加这0.01的折扣。

```js
function discount(discount) {
    return (price) => {
        return price * discount;
    }
}
const tenPercentDiscount = discount(0.1);
```

现在，我们可以只计算你的顾客买的物品都价格了：

```js
tenPercentDiscount(500); // $50
// $500 - $50 = $450
```


同样地，有些优惠顾客比一些优惠顾客更重要-让我们称之为超级客户。并且我们想给这些超级客户提供20%的折扣。

可以使用我们的柯里化的discount函数：

```js
const twentyPercentDiscount = discount(0.2);
```


我们通过这个柯里化的discount函数折扣调为0.2（即20%），给我们的超级客户配置了一个新的函数。

返回的函数twentyPercentDiscount将用于计算我们的超级客户的折扣：

```js
twentyPercentDiscount(500); // 100
// $500 - $100 = $400
twentyPercentDiscount(5000); // 1000
// $5,000 - $1,000 = $4,000
twentyPercentDiscount(1000000); // 200000
// $1,000,000 - $200,000 = $600,000
```


### 2、避免频繁调用具有相同参数的函数

举个例子，我们有一个计算圆柱体积的函数

```js
function volume(l, w, h) {
    return l * w * h;
}
```

碰巧仓库所有的气缸高度为100米，你将会看到你将重复调用此函数，h为100米

```js
volume(200,30,100) // 2003000l
volume(32,45,100); //144000l
volume(2322,232,100) // 53870400l
```

要解决以上问题，你可以将volume函数柯里化（像我们之前做的）：

```js
function volume(h) {
    return (w) => {
        return (l) => {
            return l * w * h
        }
    }
}
```

我们可以定义一个专门指定圆柱体高度的的函数：

```js
const hCylinderHeight = volume(100);
hCylinderHeight(200)(30); // 600,000l
hCylinderHeight(2322)(232); // 53,870,400l
```


## 通用的柯里化函数


我们来开发一个函数，它接受任何函数并返回一个柯里化版本的函数。

要做到这点，我们将有这个（虽然你的方法可能跟我的不一样）：

```js
function curry(fn, ...args) {
    return (..._arg) => {
        return fn(...args, ..._arg);
    }
}
```


上面代码做了什么？curry函数接受一个我们想要柯里化的函数（fn）和 一些可变数量的参数（…args）。剩下的操作用于将fn之后的参数数量收集到…args中。

然后，返回一个函数，同样地将余下的参数收集为… args。这个函数调用原始函数fn通过使用spread运算符作为参数传入... args和... args，然后，将值返回给使用。

现在我们可以用curry函数来创建特定的函数啦。

下面我们用curry函数来创建更多计算体检的特定函数（其中一个就是计算高度100米的圆柱体积函数）

```js
function volume(l,h,w) {
    return l * h * w
}
const hCy = curry(volume,100);
hCy(200,900); // 18000000l
hCy(70,60); // 420000l
```


## 结语

闭包使JavaScript柯里化成为可能。能够保留已经执行的函数的状态，使我们能够创建工厂函数 - 可以为其参数添加特定值的函数。柯里化、闭包和函数式编程是很棘手的。但是我可以保证，投入时间和练习，你就会开始掌握它，看看它多么有价值。


## 参考


[柯里化-维基百科][3]

[部分应用函数][4]

（完）

  
## 后记

以上译文仅用于学习交流，水平有限，难免有错误之处，敬请指正。


## 原文

https://blog.bitsrc.io/understanding-currying-in-javascript-ceb2188c339


[0]: https://medium.com/@kbrainwave
[1]: https://en.m.wikipedia.org/wiki/Currying
[2]: https://en.m.wikipedia.org/wiki/Currying
[3]: https://en.m.wikipedia.org/wiki/Currying
[4]: https://en.m.wikipedia.org/wiki/Partial_application