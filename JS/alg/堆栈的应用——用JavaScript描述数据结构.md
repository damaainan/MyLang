## 堆栈的应用——用JavaScript描述数据结构

来源：[http://www.cnblogs.com/walls/p/9452059.html](http://www.cnblogs.com/walls/p/9452059.html)

时间 2018-08-10 08:26:00

 
栈（stack）又名堆栈，它是一种运算受限的线性表。其限制是 **`仅允许在表的一端进行插入和删除运算`**  。这一端被称为栈顶，相对地，把另一端称为栈底。
 
## 一、实现一个栈类Stack
 
基于堆栈的特性，可以用数组做线性表进行存储。
 
初始化`Stack`类的结构如下：
 
```js
function Stack(){
    this.space = [];
}

Stack.prototype = {
    constructor: Stack,
    /* 接口code */
};
```
 
接下来，就是在原型上，对`入栈`、`出栈`、`清空栈`、`读取栈顶`、`读取整个栈数据`这几个接口的实现。
 `Stack`类默认以数组头部做栈底，尾部做栈顶。
 
### 1.1 入栈`push`入栈可以利用js数组的`push`方法，在数组尾部压入数据。
 
```js
Stack.prototype = {
    push: function(value){
        return this.space.push(value);
    }
}
```
 
### 1.2 出栈`pop`出栈同样是利用js数组的`pop`方法，在数组尾部推出数据。
 
```js
Stack.prototype = {
    pop: function(){
        return this.space.pop();
    }
}
```
 
### 1.3 清空栈`clear`清空栈相对简单，将存储数据的数组重置为空数组即可。
 
```js
Stack.prototype = {
    clear: function(){
        this.space = [];
    }
}
```
 
### 1.4 读取栈顶`read
Top`读取栈顶数据，采用数组下标的方式进行获取。带来的一个好处就是：下标超出数组有效范围时，返回值为`undefined`。
 
```js
Stack.prototype = {
    read
Top: function(){
        return this.space[this.space.length - 1];
    }
}
```
 
### 1.4 读取整个栈`read
`读取整个栈数据，直接返回当前数组即可。
 
```js
Stack.prototype = {
    read
: function(){
        return this.space;
    }
}
```
 
### 1.5 聚合
 
最后，将所有功能聚合后，如下所示，一个堆栈的数据结构就搞定了。
 
```js
function Stack(){
    this.space = [];
}

Stack.prototype = {
    constructor: Stack,
    push: function(value){
        return this.space.push(value);
    },
    pop: function(){
        return this.space.pop();
    },
    clear: function(){
        this.space = [];
    },
    read
Top: function(){
        return this.space[this.space.length - 1];
    },
    read
: function(){
        return this.space;
    }
};
```
 
## 二、实战
 
学数据结构和算法是为了更好、更高效率地解决工程问题。
 
这里学以致用，提供了几个真实的案例，来体会下数据结构和算法的魅力:)
 
### 2.1 数组`reverse`的实现 
 
当前案例，将用堆栈来实现数组的反转功能。
 
```js
function reverse(arr){
    var ArrStack = new Stack();

    for(var i = arr.length - 1; i >= 0; i--){
        ArrStack.push(arr[i]);
    }

    return ArrStack.read
();
}
```
 
如代码所示，可分为以下几个步骤：
 
```js
read


```
 
好像很简单，不用担心，复杂的在后面:)
 
### 2.2 十进制转换为二进制
 
数值转换进制的问题，是堆栈的小试牛刀。
 
讲解转换方法前，先来看一个小例子：
 
#### 将十进制的13转换成二进制
 
```js
2 | 13      1
      ￣￣￣
    2 |  6      0
      ￣￣￣
    2 |  3      1
      ￣￣￣￣
         1      1
```
 
如上所示：13的二进制码为`1101`。
 
将手工换算，变成堆栈存储，只需将 **`对2取余`**  的结果依次压入堆栈保存，最后反转输出即可。
 
```js
function binary(number){
    var tmp = number;
    var ArrStack = new Stack();

    if(number === 0){
        return 0;
    }

    while(tmp){
        ArrStack.push(tmp % 2);
        tmp = parseInt(tmp / 2, 10);
    }

    return reverse(ArrStack.read
()).join('');
}

binary(14); // 输出=> "1110"
binary(1024); // 输出=> "10000000000"
```
 
### 2.3 表达式求值
 
这个案例，其实可以理解为简化版的`eval`方法。
 
案例内容是对`1+7*(4-2)`的求值。
 
进入主题前，有必要先了解以下的数学理论：
 
 
* **`中缀表示法`**  （或中缀记法）是一个通用的算术或逻辑公式表示方法， 操作符是以中缀形式处于操作数的中间（例：3 + 4）。  
* **`逆波兰表示法`**  （Reverse Polish notation，RPN，或逆波兰记法），是一种是由波兰数学家扬·武卡谢维奇1920年引入的数学表达式方式，在逆波兰记法中，所有操作符置于操作数的后面，因此也被称为 **`后缀表示法`**  。逆波兰记法不需要括号来标识操作符的优先级。 
 常规中缀记法的“3 - 4 + 5”在逆波兰记法中写作“3 4 - 5 +”  
* [ 调度场算法 ][2] （Shunting Yard Algorithm）是一个用于将中缀表达式转换为后缀表达式的经典算法，由艾兹格·迪杰斯特拉引入，因其操作类似于火车编组场而得名。  
 
 
  
提前说明，这只是简单版实现。所以规定有两个：
 

 
* 数字要求为整数 
* 不允许表达式中出现多余的空格 
  
 
 
 
实现代码如下：
 
```js
function calculate(exp){
    var valueStack = new Stack(); // 数值栈
    var operatorStack = new Stack(); // 操作符栈 
    var expArr = exp.split(''); // 切割字符串表达式
    var FIRST_OPERATOR = ['+', '-']; // 加减运算符
    var SECOND_OPERATOR = ['*', '/']; // 乘除运算符
    var SPECIAL_OPERATOR = ['(', ')']; // 括号
    var tmp; // 临时存储当前处理的字符
    var tmpOperator; // 临时存储当前的运算符

    // 遍历表达式
    for(var i = 0, len = expArr.length; i < len; i++){
        tmp = expArr[i];
        switch(tmp){
            case '(':
                operatorStack.push(tmp);
                break;
            case ')':
                // 遇到右括号，先出栈括号内数据
                while( (tmpOperator = operatorStack.pop()) !== '(' && 
                    typeof tmpOperator !== 'undefined' ){
                    valueStack.push(calculator(tmpOperator, valueStack.pop(), valueStack.pop()));
                }
                break;
            case '+':
            case '-':
                while( typeof operatorStack.read
Top() !== 'undefined' && 
                    SPECIAL_OPERATOR.indexOf(operatorStack.read
Top()) === -1 &&
                    (SECOND_OPERATOR.indexOf(operatorStack.read
Top()) !== -1 || tmp != operatorStack.read
Top()) ){
                    // 栈顶为乘除或相同优先级运算，先出栈
                    valueStack.push(calculator(operatorStack.pop(), valueStack.pop(), valueStack.pop()));
                }
                operatorStack.push(tmp);
                break;
            case '*':
            case '/':
                while( typeof operatorStack.read
Top() != 'undefined' && 
                    FIRST_OPERATOR.indexOf(operatorStack.read
Top()) === -1 && 
                    SPECIAL_OPERATOR.indexOf(operatorStack.read
Top()) === -1 && 
                    tmp != operatorStack.read
Top()){
                    // 栈顶为相同优先级运算，先出栈
                    valueStack.push(calculator(operatorStack.pop(), valueStack.pop(), valueStack.pop()));
                }
                operatorStack.push(tmp);
                break;
            default:
                valueStack.push(tmp);
        }
    }

    // 处理栈内数据
    while( typeof (tmpOperator = operatorStack.pop()) !== 'undefined' ){
        valueStack.push(calculator(tmpOperator, valueStack.pop(), valueStack.pop()));
    }

    return valueStack.pop(); // 将计算结果推出

    /*
        @param operator 操作符
        @param initiativeNum 主动值
        @param passivityNum 被动值
    */
    function calculator(operator, passivityNum, initiativeNum){
        var result = 0;

        initiativeNum = typeof initiativeNum === 'undefined' ? 0 : parseInt(initiativeNum, 10);
        passivityNum = typeof passivityNum === 'undefined' ? 0 : parseInt(passivityNum, 10);

        switch(operator){
            case '+':
                result = initiativeNum + passivityNum;
                console.log(`${initiativeNum} + ${passivityNum} = ${result}`);
                break;
            case '-':
                result = initiativeNum - passivityNum;
                console.log(`${initiativeNum} - ${passivityNum} = ${result}`);
                break;
            case '*':
                result = initiativeNum * passivityNum;
                console.log(`${initiativeNum} * ${passivityNum} = ${result}`);
                break;
            case '/':
                result = initiativeNum / passivityNum;
                console.log(`${initiativeNum} / ${passivityNum} = ${result}`);
                break;
            default:;
        }

        return result;
    }
}
```
 
实现思路：
 
 
* 采用`调度场算法`，对中缀表达式进行读取，对结果进行合理运算。  
* 临界点采用`operatorStack.read
Top() !== 'undefined'`进行判定。有些书采用`#`做结束标志，个人觉得有点累赘。  
* 将字符串表达式用`split`进行拆分，然后进行遍历读取，压入堆栈。有提前要计算结果的，进行对应的出栈处理。  
* 将计算部分结果的方法，封装为独立的方法`calculator`。由于乘除运算符前后的数字，在运算上有区别，所以不能随意调换位置。  
 
 
### 2.4 中缀表达式转换为后缀表达式（逆波兰表示法）
 
逆波兰表示法，是一种对计算机友好的表示法，不需要使用括号。
 
下面案例，是对上一个案例的变通，也是用`调度场算法`，将中缀表达式转换为后缀表达式。
 
```js
function rpn(exp){
    var valueStack = new Stack(); // 数值栈
    var operatorStack = new Stack(); // 操作符栈 
    var expArr = exp.split('');
    var FIRST_OPERATOR = ['+', '-'];
    var SECOND_OPERATOR = ['*', '/'];
    var SPECIAL_OPERATOR = ['(', ')'];
    var tmp;
    var tmpOperator;

    for(var i = 0, len = expArr.length; i < len; i++){
        tmp = expArr[i];
        switch(tmp){
            case '(':
                operatorStack.push(tmp);
                break;
            case ')':
                // 遇到右括号，先出栈括号内数据
                while( (tmpOperator = operatorStack.pop()) !== '(' && 
                    typeof tmpOperator !== 'undefined' ){
                    valueStack.push(translate(tmpOperator, valueStack.pop(), valueStack.pop()));
                }
                break;
            case '+':
            case '-':
                while( typeof operatorStack.read
Top() !== 'undefined' && 
                    SPECIAL_OPERATOR.indexOf(operatorStack.read
Top()) === -1 &&
                    (SECOND_OPERATOR.indexOf(operatorStack.read
Top()) !== -1 || tmp != operatorStack.read
Top()) ){
                    // 栈顶为乘除或相同优先级运算，先出栈
                    valueStack.push(translate(operatorStack.pop(), valueStack.pop(), valueStack.pop()));
                }
                operatorStack.push(tmp);
                break;
            case '*':
            case '/':
                while( typeof operatorStack.read
Top() != 'undefined' && 
                    FIRST_OPERATOR.indexOf(operatorStack.read
Top()) === -1 && 
                    SPECIAL_OPERATOR.indexOf(operatorStack.read
Top()) === -1 && 
                    tmp != operatorStack.read
Top()){
                    // 栈顶为相同优先级运算，先出栈
                    valueStack.push(translate(operatorStack.pop(), valueStack.pop(), valueStack.pop()));
                }
                operatorStack.push(tmp);
                break;
            default:
                valueStack.push(tmp);
        }
    }

    while( typeof (tmpOperator = operatorStack.pop()) !== 'undefined' ){
        valueStack.push(translate(tmpOperator, valueStack.pop(), valueStack.pop()));
    }

    return valueStack.pop(); // 将计算结果推出

    /*
        @param operator 操作符
        @param initiativeNum 主动值
        @param passivityNum 被动值
    */
    function translate(operator, passivityNum, initiativeNum){
        var result = '';

        switch(operator){
            case '+':
                result = `${initiativeNum} ${passivityNum} +`;
                console.log(`${initiativeNum} + ${passivityNum} = ${result}`);
                break;
            case '-':
                result = `${initiativeNum} ${passivityNum} -`;
                console.log(`${initiativeNum} - ${passivityNum} = ${result}`);
                break;
            case '*':
                result = `${initiativeNum} ${passivityNum} *`;
                console.log(`${initiativeNum} * ${passivityNum} = ${result}`);
                break;
            case '/':
                result = `${initiativeNum} ${passivityNum} /`;
                console.log(`${initiativeNum} / ${passivityNum} = ${result}`);
                break;
            default:;
        }

        return result;
    }
}

rpn('1+7*(4-2)'); // 输出=> "1 7 4 2 - * +"
```
 
### 2.5 汉诺塔
 
![][0]
 
  
汉诺塔（港台：河内塔）是根据一个传说形成的数学问题：
 
有三根杆子A，B，C。A杆上有 N 个 (N>1) 穿孔圆盘，盘的尺寸由下到上依次变小。要求按下列规则将所有圆盘移至 C 杆：
 

 
* 每次只能移动一个圆盘；  
* 大盘不能叠在小盘上面。 
  
 
 
 
![][1]
 
堆栈的经典算法应用，首推就是`汉诺塔`。
 
理解该算法，要注意以下几点：
 
 
* 不要深究每次的移动，要抽象理解 
* 第一步：所有不符合要求的盘，从A塔统一移到B塔缓存 
* 第二步：将符合的盘移动到C塔 
* 第三步：把B塔缓存的盘全部移动到C塔 
 
 
以下是代码实现：
 
```js
var ATower = new Stack(); // A塔
var BTower = new Stack(); // B塔
var CTower = new Stack(); // C塔 (目标塔)
var TIER = 4; // 层数

for(var i = TIER; i > 0; i--){
    ATower.push(i);
}

function Hanoi(n, from, to, buffer){
    if(n > 0){
        Hanoi(n - 1, from, buffer, to);  // 所有不符合要求的盘（n-1），从A塔统一移到B塔缓存
        to.push(from.pop()); // 将符合的盘（n）移动到C塔
        Hanoi(n - 1, buffer, to, from); // 把B塔缓存的盘全部移动到C塔
    }
}

Hanoi(ATower.read
().length, ATower, CTower, BTower);
```
 
汉诺塔的重点，还是靠递归去实现。把一个大问题，通过递归，不断分拆为更小的问题。然后，集中精力解决小问题即可。
 
## 三、小结
 
不知不觉，写得有点多ORZ。
 
后面章节的参考链接，还是推荐看看。也许配合本文，你会有更深的理解。
 
## 参考
 
[1] [中缀表示法][3]
 
[2] [后缀表示法][4]
 
[3] [调度场算法][5]
 
[4] [汉诺塔][6]
 


[2]: https://zh.wikipedia.org/wiki/%E8%B0%83%E5%BA%A6%E5%9C%BA%E7%AE%97%E6%B3%95
[3]: https://zh.wikipedia.org/wiki/%E4%B8%AD%E7%BC%80%E8%A1%A8%E7%A4%BA%E6%B3%95
[4]: https://zh.wikipedia.org/wiki/%E9%80%86%E6%B3%A2%E5%85%B0%E8%A1%A8%E7%A4%BA%E6%B3%95
[5]: https://zh.wikipedia.org/wiki/%E8%B0%83%E5%BA%A6%E5%9C%BA%E7%AE%97%E6%B3%95
[6]: https://zh.wikipedia.org/wiki/%E6%B1%89%E8%AF%BA%E5%A1%94
[0]: https://img2.tuicool.com/QFJFbmQ.jpg!web
[1]: https://img2.tuicool.com/2aieIrJ.gif