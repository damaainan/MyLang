## Python入门指引

来源：[https://segmentfault.com/a/1190000012938373](https://segmentfault.com/a/1190000012938373)

Python是比较热的语言，个人兴趣参考官方文档：[https://docs.python.org/2/tut...][0]
边看边翻译了一下（后面会持续更新），有兴趣的可以看看。
Python具有高级的数据结构，能高效地面向对象编程。它的优雅的语法、动态类型、解释属性使它能快速地在大部分平台开发应用程序。它的第三方包、工具和库都可以在这里找到：[https://www.python.org/][1]。
Python很容易通过C/C++函数或数据类型进行扩展。写扩展参看:[扩展指导][2]， [C/C++的Python API][3]
更多文档参看[Python标准库][4]，[Python的API][5]
通过这个入门教程，你将学习到Pyton的一些常用特性和标准库的一些方法或模块。

### 写在前面
对于每天在电脑面前工作的人来说，可能你需要做一些自动化的工作，比如批量替换，查找更改等，或者你想写一些界面程序，游戏等。
而对于专业的软件开发人员来说，通过C/C++/Java库去开发
、测试、编译等又太繁琐了。
这时候，Python是最佳的选择。
你可以写一些shell脚本或者bat脚本去移动文件或者修改数据，但不是很适合写界面程序或者游戏。C/C++/Java又太繁琐了。而Python比较适合快速的在各个平台（windows, Mac, Unix）完成你要的工作。
Python是一门真正的编程语言，它有高级的数据结构，比如可灵活操作的数组和字典。
Python是模块化的，它的标准库里面有你可用的一些模块，这些模块提供了比如文件I/O，sockets等功能。
Python可以写出比C/C++/Java更简洁的程序，原因有三：
1 有高级的数据结构
2 通过缩进进行区分声明块而不是括号
3 不需要变量或者参数声明
Python是可扩展的。你可以把Python解释器嵌入到C程序中。

### 使用Python解释器
运行python解释器
方式1：
Python解释器在linux下一般安装在/usr/local/bin/python目录下，切换到该目录下，输入以下命令可以运行python解释器

```python
python
```
windows下一般安装在C:Python27目录下，win+r快捷键，然后输入一下cmd，打开dos界面，输入以下命令，设置环境变量：

```python
set path=%path%;C:\python27
```
则任意目录下，输入python命令即可打开python解释器
方式2：

```python
python -c command [arg] ..
```
因为命令行可能有一些特殊字符或者空白，最好用单引号引起来。
退出python解释器：
Unix下在命令行界面输入快捷键：Control-D, Windows下输入Control-Z。
或者输入：

```python
quit()
```
调用python模块（模块也就是python源文件）：

```python
python -m module [arg] ...
```
进入交互命令模式：

```python
python -i ...
```
参数传递
命令行的参数会赋值给sys模块的argv变量。可以通过import sys访问参数。argv的长度至少有1。当没有参数的时候，sys.argv[0]是一个空串。当脚本的名字为"-",则sys.argv[0]是"-",当用了-c命令，则sys.argv[0]的值为"-c"。当用了-m，sys.argv[0]的值为模块的名字。-c和-m后面的参数，python解释器不会处理。
交互模式
多行模式前面是... 单行是>>>

```python
>>> the_world_is_flat = 1
>>> if the_world_is_flat:
...     print "Be careful not to fall off!"
...
```
解释器和环境
设置代码编码
一般情况是不用设置的 默认为utf-8

```python
#!/usr/bin/env python
# -*- coding: cp-1252 -*-
```
Python介绍
开头标识注释，>>>和...开头标识python语句

```python
>>>
>>> #这是注释
... a = 1;#这是注释
>>> print a
1
```
把python当做计算器

#### 数字

```python
>>> 2 + 2
4
>>> 50 - 5*6
20
>>> (50 - 5.0*6) / 4
5.0
>>> 8 / 5.0
1.6
```
这里2是int 5.0是float,/的结果是什么类型是根据参与计算的两个数，如果有一个数是float则返回float类型。
//操作符是向下取数，小数位为0。

```python
>>> 12//7.0
1.0
>>>
```
%是求余
**是多次方

```python
>>> 5**2
25
>>>
```
声明变量n=12
如果使用一个未声明的变量会报错

```python
>>> n
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: name 'n' is not defined
>>>
```
多项式计算，会自动进行数据类型的转换：int和float一起计算，int会自动转为float
交互模式下，最后一个打印的变量会赋值给_

```python
>>> tax = 12.5 / 100
>>> price = 100.50
>>> price * tax
12.5625
>>> price + _
113.0625
>>> round(_, 2)
113.06
```
_是只读的，不能被赋值。

#### 字符串
单引号或者双引号里表示字符串，用来转义
如果不想要转义：字符串前加一个r

```python
>>> print 'C:\some\name'  # here \n means newline!
C:\some
ame
>>> print r'C:\some\name'  # note the r before the quote
C:\some\name
```
多行字符串：三个"""或者'''

```python
print """\
Usage: thingy [OPTIONS]
     -h                        Display this usage message
     -H hostname               Hostname to connect to
"""
```
标识去掉换行，没有输出是这样的：

```python
>>> print """
... aef
... asdf
... """

aef
asdf
```
字符串拼接：+ 字符串重复:*

```python
>>> "un"*2 +" awef"
'unun awef'
>>>
```
自动拼接：

```python
>>> 'Py' 'thon'
'Python'
```
获取字符串的单个字符

```python
>>> a = "python"
>>> a[0]
'p'
```
负数标识从尾部开始读取: -0等于0 最后一个字符是-1

```python
>>> a = "python"
>>> a[-1]
'n'
>>>
```
取区间：

```python
>>> a = "python"
>>> a[0:2]
'py'
>>> a[2:]
'thon'
>>> a[:4]
'pyth'
>>> a[-2:]
'on'
>>>
```
越界访问数组会报错：

```python
>>> word[42]  # the word only has 6 characters
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
IndexError: string index out of range
```
但是取不存在的区间不会报错：

```python
>>> a[-2:45]
'on'
>>>
```
字符串无法被修改：

```python
>>> word[0] = 'J'
  ...
TypeError: 'str' object does not support item assignment
>>> word[2:] = 'py'
  ...
TypeError: 'str' object does not support item assignment
unicode字符串
```
支持unicode字符串：字符串前加u

```python
>>> u'Hello World !'
u'Hello World !'
>>> u'Hello\u0020World !'
u'Hello World !'
```
0x0020标识空格
支持原始模式： 字符串前面加入ur
python的默认编码方式是：ASCII码，如果Unicode字符串被打印或者写到文件或者是str()方法转化都会默认转为ASCII码，如果字符串不在0-127范围就会报错

```python
>>> u"abc"
u'abc'
>>> str(u"abc")
'abc'
>>> u"äöü"
u'\xe4\xf6\xfc'
>>> str(u"äöü")
Traceback (most recent call last):
  File "<stdin>", line 1, in ?
UnicodeEncodeError: 'ascii' codec can't encode characters in position 0-2: ordinal not in range(128)
```
转换为特定编码：方法的参数为小写

```python
>>> u"äöü".encode('utf-8')
'\xc3\xa4\xc3\xb6\xc3\xbc'
```

### 数组
定义一个数组

```python
>>> squares = [1, 4, 9, 16, 25]
>>> squares
[1, 4, 9, 16, 25]
```
获取数组内元素

```python
>>> squares[0]  # indexing returns the item
1
>>> squares[-1]
25
>>> squares[-3:]  # slicing returns a new list 例子三
[9, 16, 25]
```
获取数组内片段，比如上面例子三，会返回一个新的数组拷贝，原数组不会发生改变
数组合并：

```python
>>> squares + [36, 49, 64, 81, 100]
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```
字符串的内容是不能被更改的，而数组是可以被更改的：

```python
>>> cubes = [1, 8, 27, 65, 125]  # something's wrong here
>>> 4 ** 3  # the cube of 4 is 64, not 65!
64
>>> cubes[3] = 64  # replace the wrong value
>>> cubes
[1, 8, 27, 64, 125]
```
给数组添加元素：

```python
>>> cubes.append(216)  # add the cube of 6
>>> cubes.append(7 ** 3)  # and the cube of 7
>>> cubes
[1, 8, 27, 64, 125, 216, 343]
```
可以赋值给截取的数组：

```python
>>> letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
>>> letters
['a', 'b', 'c', 'd', 'e', 'f', 'g']
>>> # replace some values
>>> letters[2:5] = ['C', 'D', 'E']
>>> letters
['a', 'b', 'C', 'D', 'E', 'f', 'g']
>>> # now remove them
>>> letters[2:5] = []
>>> letters
['a', 'b', 'f', 'g']
>>> # clear the list by replacing all the elements with an empty list
>>> letters[:] = []
>>> letters
[]
```
获取数组的长度：

```python
>>> letters = ['a', 'b', 'c', 'd']
>>> len(letters)
4
```
数组的元素也可以是一个数组：

```python
>>> a = ['a', 'b', 'c']
>>> n = [1, 2, 3]
>>> x = [a, n]
>>> x
[['a', 'b', 'c'], [1, 2, 3]]
>>> x[0]
['a', 'b', 'c']
>>> x[0][1]
'b'
```
终于开始编程了！
如何实现一个斐波那契:

```python
>>> # 这是一个注释
... a, b = 0, 1  #分别给a赋值为0 b赋值为1 
>>> while b < 10:#这是一个循环
...     print b  #打印b的值（并且这里的代码前面有空格（也就是行缩进））
...     a, b = b, a+b #a赋值为b，b赋值为a+b的和
...
1
1
2
3
5
8
```
之前说过，行缩进标识接下来是一个代码块。
print方法，可以控制格式，比如增加空格：

```python
>>> i = 256*256
>>> print 'The value of i is', i
The value of i is 65536
```
在print语句最后加一个逗号，避免打印结果换行：

```python
>>> a, b = 0, 1
>>> while b < 1000:
...     print b,
...     a, b = b, a+b
...
1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987
```
控制流
if语句

```python
>>> x = int(raw_input("Please enter an integer: "))
Please enter an integer: 42
>>> if x < 0: #冒号可以开启多行模式
...     x = 0
...     print 'Negative changed to zero'
... elif x == 0:
...     print 'Zero'
... elif x == 1:
...     print 'Single'
... else:
...     print 'More'
...
```
if…elif..else(不是必须的)…
for
Python的for可以遍历数组和字符串（这个和C语言的for语句有略微不同)

```python
>>> # Measure some strings:
... words = ['cat', 'window', 'defenestrate']
>>> for w in words:
...     print w, len(w)
...
cat 3
window 6
defenestrate 12
```
在循环内修改一个数组：首先通过截取数组的方法对原数组进行拷贝（这个知识点之前有提过）

```python
>>> for w in words[:]:  # words[:]可以对原数组进行拷贝
...     if len(w) > 6:
...         words.insert(0, w)
...
>>> words
['defenestrate', 'cat', 'window', 'defenestrate']
range()函数
```
range函数能根据算法创建一个数组

```python
>>> range(5, 10) #创建所有元素为5到10区间并递增的数组
[5, 6, 7, 8, 9]
>>> range(0, 10, 3)#递增3
[0, 3, 6, 9]
>>> range(-10, -100, -30)#递减30
[-10, -40, -70]
```
遍历数组的索引：

```python
>>> a = ['Mary', 'had', 'a', 'little', 'lamb']
>>> for i in range(len(a)):
...     print i, a[i]
...
0 Mary
1 had
2 a
3 little
4 lamb
```
退出循环
break语句执行会退出里层的for循环;continue会跳过后面语句的执行（和C语言用法一样）。

```python
>>> for n in range(2, 10):
...     for x in range(2, n):
...         if n % x == 0:
...             print n, 'equals', x, '*', n/x
...             break
...     else:
...         # loop fell through without finding a factor
...         print n, 'is a prime number'
...
2 is a prime number
3 is a prime number
4 equals 2 * 2
5 is a prime number
6 equals 2 * 3
7 is a prime number
8 equals 2 * 4
9 equals 3 * 3
```
pass语句
pass语句不会做任何事，只是用来占位用的

```python
>>> class MyEmptyClass:
...     pass
...
>>> def initlog(*args):
...     pass   # Remember to implement this!
...
```
定义函数和调用函数

```python
>>> def fib(n):    # def关键字标识定义函数，这里函数名为fib
...     """Print a Fibonacci series up to n.""" #
...     a, b = 0, 1
...     while a < n:
...         print a,
...         a, b = b, a+b
...
>>> # Now call the function we just defined:
... fib(2000)
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597
```
注意函数体要代码要缩进
函数可以被赋值(fib会被加入符号表)：

```python
>>> fib
<function fib at 10042ed0>
>>> f = fib # f也会被加入符号表
>>> f(100)
0 1 1 2 3 5 8 13 21 34 55 89
```
即便函数没有return，也会返回一个None

```python
>>> fib(0)
>>> print fib(0)
None
```
return后面没有跟任何东西也是返回None

```python
>>> def fib2(n):  # return Fibonacci series up to n
...     result = []
...     a, b = 0, 1
...     while a < n:
...         result.append(a)    # 这里是调用数组的append方法
...         a, b = b, a+b
...     return result
...
>>> f100 = fib2(100)    # call it
>>> f100                # write the result
[0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
```
定义带参数的函数
参数带默认值：retries的默认值为4

```python
def ask_ok(prompt, retries=4, complaint='Yes or no, please!'):
    while True: # True是关键字
        ok = raw_input(prompt) #raw_input是内置的函数，用于IO输入
        if ok in ('y', 'ye', 'yes'):
            return True
        if ok in ('n', 'no', 'nop', 'nope'):
            return False
        retries = retries - 1
        if retries < 0:
            raise IOError('refusenik user') # raise是关键字 抛出异常
        print complaint
```
默认值可以为变量：i是一个变量

```python
i = 5

def f(arg=i):
    print arg

i = 6
f()
```
默认参数如果是一个可变的对象，会被赋值多次：

```python
def f(a, L=[]):
    L.append(a)
    return L

print f(1)
print f(2)
print f(3)
会打印出：

[1]
[1, 2]
[1, 2, 3]
```
如果你不想L被改变，你可以这么做：

```python
def f(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L
```
如果只接受一个参数，但是传递了两个参数会报错：

```python
>>> def function(a):
...     pass
...
>>> function(0, a=0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: function() got multiple values for keyword argument 'a'
**kewords接收字典参数：

def cheeseshop(kind, *arguments, **keywords):
    print "-- Do you have any", kind, "?"
    print "-- I'm sorry, we're all out of", kind
    for arg in arguments:
        print arg
    print "-" * 40
    keys = sorted(keywords.keys()) #按字典顺序 
    for kw in keys:
        print kw, ":", keywords[kw]
```
*arg接受不确定个数的参数：

```python
def write_multiple_items(file, separator, *args):
    file.write(separator.join(args))
```
自动解析参数：

```python
>>> range(3, 6)             # 正常情况调用方式
[3, 4, 5]
>>> args = [3, 6]
>>> range(*args)            # 从一个数组里解析参数
[3, 4, 5]
>>> def parrot(voltage, state='a stiff', action='voom'):
...     print "-- This parrot wouldn't", action,
...     print "if you put", voltage, "volts through it.",
...     print "E's", state, "!"
...
>>> d = {"voltage": "four million", "state": "bleedin' demised", "action": "VOOM"}
>>> parrot(**d)
-- This parrot wouldn't VOOM if you put four million volts through it. E's bleedin' demised !
```
文档字符串:

```python
>>> def my_function():
...     """Do nothing, but document it.
...
...     No, really, it doesn't do anything.
...     """
...     pass
...
>>> print my_function.__doc__
Do nothing, but document it.

    No, really, it doesn't do anything.
```
Lambda表达式一个匿名函数，lambda a, b: a+b. a和b是两个参数，结果返回a和b的和：

```python
>>> def make_incrementor(n):
...     return lambda x: x + n
...
>>> f = make_incrementor(42)
>>> f(0)
42
>>> f(1)
43
```
lambda也可以作为参数传递：

```python
>>> pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
>>> pairs.sort(key=lambda pair: pair[1])
>>> pairs
[(4, 'four'), (1, 'one'), (3, 'three'), (2, 'two')]
```

### 编码格式建议
不用Tab缩进，用4倍空格缩进
必要时换行（避免单行超出79个字符）
用空格区分函数或者类或者函数内部的一大段代码
代码前面加上必要的注释
用文档字符串
操作符liagn两边或者逗号后面必须空格
函数采用lower_case_width_underscore方式命令，类用驼峰(CanekCase)方式命名；总是用self当作类的第一个方法的参数
不要用特殊的编码格式（ASCII是兼容所有的）

### 数据结构

#### 数组
python数据默认有一些常用方法：比如append, extend, insert等等

#### 作为堆栈使用

```python
>>> stack = [3, 4, 5]
>>> stack.append(6)
>>> stack.append(7)
>>> stack
[3, 4, 5, 6, 7]
>>> stack.pop()
7
>>> stack
[3, 4, 5, 6]
>>> stack.pop()
6
>>> stack.pop()
5
>>> stack
[3, 4]
```

#### 作为队列使用

```python
>>> from collections import deque
>>> queue = deque(["Eric", "John", "Michael"])
>>> queue.append("Terry")          # Terry arrives
>>> queue.append("Graham")          # Graham arrives
>>> queue.popleft()                # The first to arrive now leaves
'Eric'
>>> queue.popleft()                # The second to arrive now leaves
'John'
>>> queue                          # Remaining queue in order of arrival
deque(['Michael', 'Terry', 'Graham'])
```

#### 一些常用的方法
filter(function, sequence) : 返回function的值为true的所有值

```python
>>> def f(x): return x % 3 == 0 or x % 5 == 0
...
>>> filter(f, range(2, 25))
[3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24]
```
map(function, sequence)： 返回处理后的值

```python
>>> def cube(x): return x*x*x
...
>>> map(cube, range(1, 11))
[1, 8, 27, 64, 125, 216, 343, 512, 729, 1000]
```
传递两个数组： 分别从一个数组里取出一个数 返回相加后的结果

```python
>>> seq = range(8)
>>> def add(x, y): return x+y
...
>>> map(add, seq, seq)
[0, 2, 4, 6, 8, 10, 12, 14]
```
reduce(function, sequence) ：把数组的第一个和第二个参数想加的和和第三个数再加。。如果数组为空，会返回异常

```python
>>> def add(x,y): return x+y
...
>>> reduce(add, range(1, 11))
55
```
reduce可以指定开始的第一个数的索引：

```python
>>> def sum(seq):
...    def add(x,y): return x+y
...    return reduce(add, seq, 0)
...
>>> sum(range(1, 11))
55
>>> sum([])
0
```
创建数组的几种形式：

```python
>>> squares = []
>>> for x in range(10):
...    squares.append(x**2)
...
>>> squares
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
```

```python
squares = [x**2 for x in range(10)]
```

```python
squares = map(lambda x: x**2, range(10))
```
更复杂点的例子：x，y作为一个整体 必须加上括号

```python
>>> [(x, y) for x in [1,2,3] for y in [3,1,4] if x != y]
[(1, 3), (1, 4), (2, 3), (2, 1), (2, 4), (3, 1), (3, 4)]
```
更多例子：

```python
>>> freshfruit = ['  banana', '  loganberry ', 'passion fruit  ']
>>> [weapon.strip() for weapon in freshfruit]
['banana', 'loganberry', 'passion fruit']
>>> [x, x**2 for x in range(6)]
  File "<stdin>", line 1, in <module>
    [x, x**2 for x in range(6)]
              ^
SyntaxError: invalid syntax
>>> # flatten a list using a listcomp with two 'for'
>>> vec = [[1,2,3], [4,5,6], [7,8,9]]
>>> [num for elem in vec for num in elem]
[1, 2, 3, 4, 5, 6, 7, 8, 9]
>>> from math import pi
>>> [str(round(pi, i)) for i in range(1, 6)]
['3.1', '3.14', '3.142', '3.1416', '3.14159']
```

#### 二维数组

```python
>>> matrix = [
...    [1, 2, 3, 4],
...    [5, 6, 7, 8],
...    [9, 10, 11, 12],
... ]
```
复杂点的例子：

```python
>>> [[row[i] for row in matrix] for i in range(4)]
[[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]
```
相当于：

```python
>>> transposed = []
>>> for i in range(4):
...    transposed.append([row[i] for row in matrix])
...
>>> transposed
[[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]
```
删除数组内元素：del

```python
>>> a = [-1, 1, 66.25, 333, 333, 1234.5]
>>> del a[0]
>>> a
[1, 66.25, 333, 333, 1234.5]
>>> del a[2:4]
>>> a
[1, 66.25, 1234.5]
>>> del a[:]
>>> a
[]
```
删除整个数组：

```python
>>> del a
```

#### 新类型：元组。
输入可以加括号，也可以不加。输出都是带括号的。

```python
>>> t = 12345, 54321, 'hello!'  # 输入 没加括号
>>> t[0]
12345
>>> t
(12345, 54321, 'hello!')  # 输出 带括号
>>> # Tuples may be nested:
... u = t, (1, 2, 3, 4, 5)
>>> u
((12345, 54321, 'hello!'), (1, 2, 3, 4, 5))
>>> # 无法被修改
... t[0] = 88888
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'tuple' object does not support item assignment
>>> # 内部的元素可以是可变的类型 比如数组等
... v = ([1, 2, 3], [3, 2, 1])
>>> v
([1, 2, 3], [3, 2, 1])
```
空元组和只有一个元素的元组：

```python
>>> empty = ()
>>> singleton = 'hello',    # <-- note trailing comma
>>> len(empty)
0
>>> len(singleton)
1
>>> singleton
('hello',)
```
逆序元素：

```python
>>> t = (12345, 54321, 'hello!')
>>> x, y, z = t
```

#### 新的类型：集合
创建空集合：set()

```python
>>> basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
>>> fruit = set(basket)              # 创建集合
>>> fruit
set(['orange', 'pear', 'apple', 'banana'])
>>> 'orange' in fruit                # 测试是否oranage是否是集合fruit内部
True
>>> 'crabgrass' in fruit
False
```
集合a, b 之间的交集 并集

```python
>>> a = set('abracadabra')
>>> b = set('alacazam')
>>> a                                  # unique letters in a
set(['a', 'r', 'b', 'c', 'd'])
>>> a - b                              # letters in a but not in b
set(['r', 'd', 'b'])
>>> a | b                              # letters in either a or b
set(['a', 'c', 'r', 'd', 'b', 'm', 'z', 'l'])
>>> a & b                              # letters in both a and b
set(['a', 'c'])
>>> a ^ b                              # letters in a or b but not both
set(['r', 'd', 'b', 'm', 'z', 'l'])
```

```python
>>> a = {x for x in 'abracadabra' if x not in 'abc'}
>>> a
set(['r', 'd'])
```

#### 新的类型：字典
字典是根据key索引的，而key数据类型可以为数字或者字符串，元组的元素都是不可变的，也可以作为key。数组不能作为key，因为数组可被修改

```python
>>> tel = {'jack': 4098, 'sape': 4139}
>>> tel['guido'] = 4127
>>> tel
{'sape': 4139, 'guido': 4127, 'jack': 4098}
>>> tel['jack']
4098
>>> del tel['sape']
>>> tel['irv'] = 4127
>>> tel
{'guido': 4127, 'irv': 4127, 'jack': 4098}
>>> tel.keys()
['guido', 'irv', 'jack']
>>> 'guido' in tel
True
```
dict方法直接创建字典：

```python
>>> dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
{'sape': 4139, 'jack': 4098, 'guido': 4127}
```

```python
>>> {x: x**2 for x in (2, 4, 6)}
{2: 4, 4: 16, 6: 36}
```

```python
>>> dict(sape=4139, guido=4127, jack=4098)
{'sape': 4139, 'jack': 4098, 'guido': 4127}
```

#### 遍历
通过enumerate方法

```python
>>> for i, v in enumerate(['tic', 'tac', 'toe']):
...    print i, v
...
0 tic
1 tac
2 toe
```
一次性遍历多个（这个特性不错。。

```python
>>> questions = ['name', 'quest', 'favorite color']
>>> answers = ['lancelot', 'the holy grail', 'blue']
>>> for q, a in zip(questions, answers):
...    print 'What is your {0}?  It is {1}.'.format(q, a)
...
What is your name?  It is lancelot.
What is your quest?  It is the holy grail.
What is your favorite color?  It is blue
```
逆序遍历：reversed

```python
>>> for i in reversed(xrange(1,10,2)):
...    print i
...
9
7
5
3
1
```
对数组排序(sorted方法)，然后遍历：

```python
>>> basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
>>> for f in sorted(set(basket)):
...    print f
...
apple
banana
orange
pear
```
遍历字典的时候，获得key和value:

```python
>>> knights = {'gallahad': 'the pure', 'robin': 'the brave'}
>>> for k, v in knights.iteritems():
...    print k, v
...
gallahad the pure
robin the brave
```
遍历的时候改变一个数组：

```python
>>> import math
>>> raw_data = [56.2, float('NaN'), 51.7, 55.3, 52.5, float('NaN'), 47.8]
>>> filtered_data = []
>>> for value in raw_data:
...    if not math.isnan(value):
...        filtered_data.append(value)
...
>>> filtered_data
[56.2, 51.7, 55.3, 52.5, 47.8]
```

#### 更多条件语句
比较运算符：
in和not in判断是否在序列里面； is和is not用来比较两个对象是否是同一个对象；
比较可以链式： a < b == c 判断a小于b，并且b等于c
布尔操作符：and和or  优先级比比较运算符低   not优先级最高 or最低
布尔运算符，当一个满足条件不会继续下面的计算
比较结果可以被赋值：

```python
>>> string1, string2, string3 = '', 'Trondheim', 'Hammer Dance'
>>> non_null = string1 or string2 or string3
>>> non_null
'Trondheim'
```

### 模块
退出解释器后，所有声明的函数或者变量都不存在了。所以我们需要创建一个python脚本，可持续地运行。每一个脚本文件称之为一个模块。
比如我们创建一个文件:fibo.py

```python
# 这是一个模块

def fib(n):    # 定义函数fib
    a, b = 0, 1
    while b < n:
        print b,
        a, b = b, a+b

def fib2(n):  # 定义函数fib2
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result
```
在解释器里面导入这个模块：

```python
>>> import fibo
```
访问模块的函数：

```python
>>> fibo.fib(1000)
1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987
>>> fibo.fib2(100)
[1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
>>> fibo.__name__
'fibo'
```
函数赋给一个变量

```python
>>> fib = fibo.fib
>>> fib(500)
1 1 2 3 5 8 13 21 34 55 89 144 233 377
```

### 执行模块脚本
这样运行一个模块

```python
python fibo.py <arguments>
```
和导入一个模块，并且把__name__设置为__main__是一样的：相当于把下面的代码放到模块的底部

```python
if __name__ == "__main__":
    import sys
    fib(int(sys.argv[1]))
```
这样单纯导入是不会运行这个脚本的：

```python
>>> import fibo
>>>
```

### 模块寻找路径
1 内置模块
2 搜索sys.path里面的所有目录
sys.path初始化的内容：
当前目录
PYTHONPATH （目录路径，它和环境变量的PATH语法一致）
Python安装路径
sys.path会被修改，当前目录优先于标准库路径。

### 编译后的Python文件
如果 spam.pyc（编译后的Python文件）和spam.py共存，会优先用编译后的文件。spam.pyc保存的编译时间和spam.py的修改时间不一致，则编译后的文件会被忽略（也就是用spam.py文件）。spam.pyc文件是平台独立的，也就是说能被各个平台共享。

### 标准模块
Python有自己的标准库。为了达到更底层的东西，有些模块已经内置到解析器中。而且有些内置模块依赖于环境，比如winreg模块只在window环境下提供。而一个值得关注的模块是：sys，它被内置到了每个Python解释器中。sys.ps1和sys.ps2表示Python的提示符

```python
>>>import sys
>>>sys.ps1
'>>> '
>>> sys.ps2
'... '
>>> sys.ps1 = 'C> '
C> print 'Yuck!'
Yuck!
C>
```
sys.path的值是解释器的模块搜索路径。我们可以增加路径：

```python
>>> import sys
>>> sys.path.append('/ufs/guido/lib/python')
```

#### dir()函数
dir()函数返回一个字符串的数组，它被用来表示一个模块定义了哪些名字

```python
>>> import fibo, sys
>>> dir(fibo)
['__name__', 'fib', 'fib2']
>>> dir(sys)  
['__displayhook__', '__doc__', '__excepthook__', '__name__', '__package__',
'__stderr__', '__stdin__', '__stdout__', '_clear_type_cache',
'_current_frames', '_getframe', '_mercurial', 'api_version', 'argv',
'builtin_module_names', 'byteorder', 'call_tracing', 'callstats',
'copyright', 'displayhook', 'dont_write_bytecode', 'exc_clear', 'exc_info',
'exc_traceback', 'exc_type', 'exc_value', 'excepthook', 'exec_prefix',
'executable', 'exit', 'flags', 'float_info', 'float_repr_style',
'getcheckinterval', 'getdefaultencoding', 'getdlopenflags',
'getfilesystemencoding', 'getobjects', 'getprofile', 'getrecursionlimit',
'getrefcount', 'getsizeof', 'gettotalrefcount', 'gettrace', 'hexversion',
'long_info', 'maxint', 'maxsize', 'maxunicode', 'meta_path', 'modules',
'path', 'path_hooks', 'path_importer_cache', 'platform', 'prefix', 'ps1',
'py3kwarning', 'setcheckinterval', 'setdlopenflags', 'setprofile',
'setrecursionlimit', 'settrace', 'stderr', 'stdin', 'stdout', 'subversion',
'version', 'version_info', 'warnoptions']
```
不带参数则返回当前你定义的模块函数变量名字

```python
>>> a = [1, 2, 3, 4, 5]
>>> import fibo
>>> fib = fibo.fib
>>> dir()
['__builtins__', '__name__', '__package__', 'a', 'fib', 'fibo', 'sys']
```
dir()不会返回内置的函数和变量。如果要打印内置的话，需要传递__builtin__

```python
>>> import __builtin__
>>> dir(__builtin__)  
['ArithmeticError', 'AssertionError', 'AttributeError', 'BaseException',
'BufferError', 'BytesWarning', 'DeprecationWarning', 'EOFError',
'Ellipsis', 'EnvironmentError', 'Exception', 'False', 'FloatingPointError',
'FutureWarning', 'GeneratorExit', 'IOError', 'ImportError', 'ImportWarning',
'IndentationError', 'IndexError', 'KeyError', 'KeyboardInterrupt',
'LookupError', 'MemoryError', 'NameError', 'None', 'NotImplemented',
'NotImplementedError', 'OSError', 'OverflowError',
'PendingDeprecationWarning', 'ReferenceError', 'RuntimeError',
'RuntimeWarning', 'StandardError', 'StopIteration', 'SyntaxError',
'SyntaxWarning', 'SystemError', 'SystemExit', 'TabError', 'True',
'TypeError', 'UnboundLocalError', 'UnicodeDecodeError',
'UnicodeEncodeError', 'UnicodeError', 'UnicodeTranslateError',
'UnicodeWarning', 'UserWarning', 'ValueError', 'Warning',
'ZeroDivisionError', '_', '__debug__', '__doc__', '__import__',
'__name__', '__package__', 'abs', 'all', 'any', 'apply', 'basestring',
'bin', 'bool', 'buffer', 'bytearray', 'bytes', 'callable', 'chr',
'classmethod', 'cmp', 'coerce', 'compile', 'complex', 'copyright',
'credits', 'delattr', 'dict', 'dir', 'divmod', 'enumerate', 'eval',
'execfile', 'exit', 'file', 'filter', 'float', 'format', 'frozenset',
'getattr', 'globals', 'hasattr', 'hash', 'help', 'hex', 'id', 'input',
'int', 'intern', 'isinstance', 'issubclass', 'iter', 'len', 'license',
'list', 'locals', 'long', 'map', 'max', 'memoryview', 'min', 'next',
'object', 'oct', 'open', 'ord', 'pow', 'print', 'property', 'quit',
'range', 'raw_input', 'reduce', 'reload', 'repr', 'reversed', 'round',
'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str', 'sum', 'super',
'tuple', 'type', 'unichr', 'unicode', 'vars', 'xrange', 'zip']
```

#### 包
包是组织Python模块的一种方式，比如A.B 标识包A下有一个子模块B。
一个包的结构类似如下：

```python
sound/                          Top-level package
      __init__.py              Initialize the sound package
      formats/                  Subpackage for file format conversions
              __init__.py
              wavread.py
              wavwrite.py
              aiffread.py
              aiffwrite.py
              auread.py
              auwrite.py
              ...
      effects/                  Subpackage for sound effects
              __init__.py
              echo.py
              surround.py
              reverse.py
              ...
      filters/                  Subpackage for filters
              __init__.py
              equalizer.py
              vocoder.py
              karaoke.py
              ...
```
那么我们怎么导入它:

```python
import sound.effects.echo
```
然后怎么引用: 必须用全名引用

```python
sound.effects.echo.echofilter(input, output, delay=0.7, atten=4)
```
另外一种引用的方式是：

```python
from sound.effects import echo
```
这种方式引入，可以避免全名

```python
echo.echofilter(input, output, delay=0.7, atten=4)
```
当然，你也可以引入函数或者变量：

```python
from sound.effects.echo import echofilter
```
直接调用函数：

```python
echofilter(input, output, delay=0.7, atten=4)
```
注意：以下方式导入，最后一个（subsubitem）必须是包

```python
import item.subitem.subsubitem
```

#### 导入包
在sound/effects/__init__.py 这个里面定义：

```python
__all__ = ["echo", "surround", "reverse"]
```
那么：通过以下方式会导入上面all指定的模块

```python
from sound.effects import *
```
如果all没定义，那么import导入的情况是不一定的。

```python
import sound.effects.echo
import sound.effects.surround
from sound.effects import *
```
比如上面这种写法，会导入echo和surround
不推荐使用*。

#### 内部包引用
可以使用相对导入：

```python
from . import echo
from .. import formats
from ..filters import equalizer
```

### 输入和输出

#### 输出格式
输出方法：sys.stdout标准输出， print write()方法等
格式输出: str.format()
转为字符串用repr()和str()函数 ：

```python
>>> s = 'Hello, world.'
>>> str(s)
'Hello, world.'
>>> repr(s)
"'Hello, world.'"
>>> str(1.0/7.0)
'0.142857142857'
>>> repr(1.0/7.0)
'0.14285714285714285'
>>> x = 10 * 3.25
>>> y = 200 * 200
>>> s = 'The value of x is ' + repr(x) + ', and y is ' + repr(y) + '...'
>>> print s
The value of x is 32.5, and y is 40000...
>>> # The repr() of a string adds string quotes and backslashes:
... hello = 'hello, world\n'
>>> hellos = repr(hello)
>>> print hellos
'hello, world\n'
>>> # The argument to repr() may be any Python object:
... repr((x, y, ('spam', 'eggs')))
"(32.5, 40000, ('spam', 'eggs'))"
```
打印表格形式：

```python
>>> for x in range(1, 11):
...    print repr(x).rjust(2), repr(x*x).rjust(3),
...    # Note trailing comma on previous line
...    print repr(x*x*x).rjust(4)
...
1  1    1
2  4    8
3  9  27
4  16  64
5  25  125
6  36  216
7  49  343
8  64  512
9  81  729
10 100 1000

>>> for x in range(1,11):
...    print '{0:2d} {1:3d} {2:4d}'.format(x, x*x, x*x*x)
...
1  1    1
2  4    8
3  9  27
4  16  64
5  25  125
6  36  216
7  49  343
8  64  512
9  81  729
10 100 1000
```
str.rjust() 对字符串右对齐
str.zfill() 字符串保证位数

```python
>>> '12'.zfill(5)
'00012'
>>> '-3.14'.zfill(7)
'-003.14'
>>> '3.14159265359'.zfill(5)
'3.14159265359'
```
str.format()的基本使用：

```python
>>> print 'We are the {} who say "{}!"'.format('knights', 'Ni')
We are the knights who say "Ni!"
```
交换位置：

```python
>>> print '{0} and {1}'.format('spam', 'eggs')
spam and eggs
>>> print '{1} and {0}'.format('spam', 'eggs')
eggs and spam
```
通过key访问：

```python
>>> print 'This {food} is {adjective}.'.format(
...      food='spam', adjective='absolutely horrible')
This spam is absolutely horrible.
```
混合使用：

```python
>>> print 'The story of {0}, {1}, and {other}.'.format('Bill', 'Manfred',
...                                                    other='Georg')
The story of Bill, Manfred, and Georg.
```
'!s' (调用str()) and '!r' (调用repr()) 打印前进行格式转换：

```python
>>> import math
>>> print 'The value of PI is approximately {}.'.format(math.pi)
The value of PI is approximately 3.14159265359.
>>> print 'The value of PI is approximately {!r}.'.format(math.pi)
The value of PI is approximately 3.141592653589793.
```
':' 可控制小数点：

```python
>>> import math
>>> print 'The value of PI is approximately {0:.3f}.'.format(math.pi)
The value of PI is approximately 3.142.
```
控制表格：

```python
>>> table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}
>>> for name, phone in table.items():
...    print '{0:10} ==> {1:10d}'.format(name, phone)
...
Jack      ==>      4098
Dcab      ==>      7678
Sjoerd    ==>      4127
```
通过[]访问key:

```python
>>> table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 8637678}
>>> print ('Jack: {0[Jack]:d}; Sjoerd: {0[Sjoerd]:d}; '
...        'Dcab: {0[Dcab]:d}'.format(table))
Jack: 4098; Sjoerd: 4127; Dcab: 8637678
```

#### % 操作符也可以格式化(老式的)

```python
>>> import math
>>> print 'The value of PI is approximately %5.3f.' % math.pi
The value of PI is approximately 3.142.
```

#### 读写文件
open（）打开文件：open(filename, mode)

```python
>>> f = open('workfile', 'w')
>>> print f
<open file 'workfile', mode 'w' at 80a0960
```
‘b’标识二进制形式，跨平台

#### 文件对象的方法
读文件：f.read(size)

```python
>>> f.read()
'This is the entire file.\n'
>>> f.read()
''
```
带换行：

```python
>>> f.readline()
'This is the first line of the file.\n'
>>> f.readline()
'Second line of the file\n'
>>> f.readline()
''
```
读取一个文件的所有行：

```python
>> for line in f:
        print line,

This is the first line of the file.
Second line of the file
```
或者list(f) or f.readlines()
字符串写入文件：

```python
>>> f.write('This is a test\n')
```
将其他类型写入文件需先转为字符串：

```python
>>> value = ('the answer', 42)
>>> s = str(value)
>>> f.write(s)
```
f.tell() 返回一个整数，表示当前文件的位置（计算字节）。比如：

```python
>>> f = open('workfile', 'r+')
>>> f.write('0123456789abcdef')
>>> f.seek(5)      # 到第6个字节
>>> f.read(1)
'5'
>>> f.seek(-3, 2)  # 倒数（2表示倒数）第三个字节位置
>>> f.read(1)
'd'
```
释放文件资源：

```python
>>> f.close()
>>> f.read()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: I/O operation on closed file
```
最佳实践是带上with：即便有异常抛出也能释放文件资源

```python
>>> with open('workfile', 'r') as f:
...    read_data = f.read()
>>> f.closed
True
```

#### 保存JSON数据
序列化：将json转为字符串 反序列化：将字符串转为json

```python
>>> import json
>>> json.dumps([1, 'simple', 'list'])
'[1, "simple", "list"]'
```
将对象序列化到一个文件中：f是一个文件对象

```python
json.dump(x, f)
```
从文件中读取：

```python
x = json.load(f)
```

### 错误和异常

#### 语法错误

```python
>>> while True print 'Hello world'
  File "<stdin>", line 1
    while True print 'Hello world'
                  ^
SyntaxError: invalid syntax
```

#### 执行异常

```python
>>> 10 * (1/0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ZeroDivisionError: integer division or modulo by zero
>>> 4 + spam*3
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: name 'spam' is not defined
>>> '2' + 2
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: cannot concatenate 'str' and 'int' objects
```

#### 处理异常

```python
>>> while True:
...    try:
...        x = int(raw_input("Please enter a number: "))
...        break
...    except ValueError:
...        print "Oops!  That was no valid number.  Try again..."
...
```
这里只捕获了ValueError，如果捕获更多异常：

```python
... except (RuntimeError, TypeError, NameError):
...    pass
```

```python
import sys

try:
    f = open('myfile.txt')
    s = f.readline()
    i = int(s.strip())
except IOError as e:
    print "I/O error({0}): {1}".format(e.errno, e.strerror)
except ValueError:
    print "Could not convert data to an integer."
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise
```
try...except...else..else后面的代码一定会执行

```python
for arg in sys.argv[1:]:
    try:
        f = open(arg, 'r')
    except IOError:
        print 'cannot open', arg
    else:
        print arg, 'has', len(f.readlines()), 'lines'
        f.close()
```
抛出异常：

```python
>>> try:
...    raise Exception('spam', 'eggs')
... except Exception as inst:
...    print type(inst)    # 异常实例
...    print inst.args      # arguments 存储在.args中
...    print inst          # __str__方法使得能直接打印参数而不需要引用它。
...    x, y = inst.args
...    print 'x =', x
...    print 'y =', y
...
<type 'exceptions.Exception'>
('spam', 'eggs')
('spam', 'eggs')
x = spam
```
函数内部的异常也能捕获：

```python
>>> def this_fails():
...    x = 1/0
...
>>> try:
...    this_fails()
... except ZeroDivisionError as detail:
...    print 'Handling run-time error:', detail
...
Handling run-time error: integer division or modulo by zero
```

#### 抛出异常

```python
>>> raise NameError('HiThere')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: HiThere
```
不处理异常，直接将异常抛出：

```python
>>> try:
...    raise NameError('HiThere')
... except NameError:
...    print 'An exception flew by!'
...    raise
...
An exception flew by!
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
NameError: HiThere
```

#### 自定义异常

```python
>>> class MyError(Exception):
...    def __init__(self, value):
...        self.value = value
...    def __str__(self):
...        return repr(self.value)
...
>>> try:
...    raise MyError(2*2)
... except MyError as e:
...    print 'My exception occurred, value:', e.value
...
My exception occurred, value: 4
>>> raise MyError('oops!')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
__main__.MyError: 'oops!'
```
重写了__init__方法，并且定义了一个value属性。
一般定义异常的方式是这样的：

```python
class Error(Exception):
    """Base class for exceptions in this module."""
    pass

class InputError(Error):
    """Exception raised for errors in the input.

    Attributes:
        expr -- input expression in which the error occurred
        msg  -- explanation of the error
    """

    def __init__(self, expr, msg):
        self.expr = expr
        self.msg = msg

class TransitionError(Error):
    """Raised when an operation attempts a state transition that's not
    allowed.

    Attributes:
        prev -- state at beginning of transition
        next -- attempted new state
        msg  -- explanation of why the specific transition is not allowed
    """

    def __init__(self, prev, next, msg):
        self.prev = prev
        self.next = next
        self.msg = msg
```

#### 清理工作

```python
>>> try:
...    raise KeyboardInterrupt
... finally:
...    print 'Goodbye, world!'
...
Goodbye, world!
KeyboardInterrupt
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
```
finally总是会被执行，而且如果异常没有被处理的话，在finally里面的代码执行完后会被重新抛出。
一个更复杂点的例子：

```python
>>> def divide(x, y):
...    try:
...        result = x / y
...    except ZeroDivisionError:
...        print "division by zero!"
...    else:
...        print "result is", result
...    finally:
...        print "executing finally clause"
...
>>> divide(2, 1)
result is 2
executing finally clause
>>> divide(2, 0)
division by zero!
executing finally clause
>>> divide("2", "1")
executing finally clause
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 3, in divide
TypeError: unsupported operand type(s) for /: 'str' and 'str'
```

#### 预清理
一定要带上with保证文件资源被释放

```python
with open("myfile.txt") as f:
    for line in f:
        print line,
```

### Python类

#### 定义类

```python
class MyClass:
    """A simple example class"""
    i = 12345

    def f(self):
        return 'hello world'
```

#### 引用类的属性和方法
MyClass.i和 MyClass.f
MyClass.__doc_ => “A simple example class”

#### 定义init方法，设置默认属性

```python
def __init__(self):
    self.data = []
```
传递给类的参数会传递给init:

```python
>>> class Complex:
...    def __init__(self, realpart, imagpart):
...        self.r = realpart
...        self.i = imagpart
...
>>> x = Complex(3.0, -4.5)
>>> x.r, x.i
(3.0, -4.5)
```

#### 类共享变量和实例变量

```python
class Dog:

    kind = 'canine'        # 类共享变量

    def __init__(self, name):
        self.name = name    # 实例变量

>>> d = Dog('Fido')
>>> e = Dog('Buddy')
>>> d.kind                  # shared by all dogs
'canine'
>>> e.kind                  # shared by all dogs
'canine'
>>> d.name                  # unique to d
'Fido'
>>> e.name                  # unique to e
'Buddy'
```

#### 注意引用变量避免被所有实例共享

```python
class Dog:

    tricks = []            # mistaken use of a class variable

    def __init__(self, name):
        self.name = name

    def add_trick(self, trick):
        self.tricks.append(trick)

>>> d = Dog('Fido')
>>> e = Dog('Buddy')
>>> d.add_trick('roll over')
>>> e.add_trick('play dead')
>>> d.tricks                # 这里tricks被所有实例共享了
['roll over', 'play dead']
```
正确的用法：

```python
class Dog:

    def __init__(self, name):
        self.name = name
        self.tricks = []    # creates a new empty list for each dog

    def add_trick(self, trick):
        self.tricks.append(trick)

>>> d = Dog('Fido')
>>> e = Dog('Buddy')
>>> d.add_trick('roll over')
>>> e.add_trick('play dead')
>>> d.tricks
['roll over']
>>> e.tricks
['play dead']
```

#### 函数的定义可以在类外部(不推荐)

```python
# Function defined outside the class
def f1(self, x, y):
    return min(x, x+y)

class C:
    f = f1

    def g(self):
        return 'hello world'

    h = g
```

#### 通过self引用函数

```python
class Bag:
    def __init__(self):
        self.data = []

    def add(self, x):
        self.data.append(x)

    def addtwice(self, x):
        self.add(x)
        self.add(x)
```
每一个值都是一个对象，它的对象存储在object.__class__

### 继承
语法：

```python
class DerivedClassName(BaseClassName):
    <statement-1>
    .
    .
    .
    <statement-N>
```
或(moduleName是导入的模块)

```python
class DerivedClassName(moduleName.BaseClassName):
```
如果引用的属性没有在当前类中找到，会找他的基类。继承的类可以重写基类的方法。
有两个内置的函数很有用：
判断实例的类型：isinstance(obj, int) 判断是否是继承自int类 ( 如果
obj.__class__ 是int或者继承自int类 返回true)
issubclass(bool, int)： 判断bool是否是int的子类

#### 多继承

```python
class DerivedClassName(Base1, Base2, Base3):
    <statement-1>
    .
    .
    .
    <statement-N>
```

#### 私有变量和类内引用
私有变量一般是以_下划线开头
内部调用方法__双下划线开头：

```python
class Mapping:
    def __init__(self, iterable):
        self.items_list = []
        self.__update(iterable)

    def update(self, iterable):
        for item in iterable:
            self.items_list.append(item)

    __update = update  # 拷贝一份update方法

class MappingSubclass(Mapping):

    def update(self, keys, values): # 子类可以重写update方法 并且不会影响到init方法
        for item in zip(keys, values):
            self.items_list.append(item)
```

#### 异常也是一个类
语法：

```python
raise Class, instance
raise instance  （raise instance.__class__, instance的简写）
```
比如：

```python
class B:
    pass
class C(B):
    pass
class D(C):
    pass

for c in [B, C, D]:
    try:
        raise c()
    except D:
        print "D"
    except C:
        print "C"
    except B:
        print "B"
```

#### 遍历
大部分的对象都可以遍历

```python
for element in [1, 2, 3]:
    print element
for element in (1, 2, 3):
    print element
for key in {'one':1, 'two':2}:
    print key
for char in "123":
    print char
for line in open("myfile.txt"):
    print line,
```
内部：for语句调用了iter()方法，然后调用next()方法访问下一个元素，如果没有下一个会抛出StopInteration异常

```python
>>> s = 'abc'
>>> it = iter(s)
>>> it
<iterator object at 0x00A1DB50>
>>> it.next()
'a'
>>> it.next()
'b'
>>> it.next()
'c'
>>> it.next()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
    it.next()
StopIteration
```
给类增加遍历器：

```python
class Reverse:
    """Iterator for looping over a sequence backwards."""
    def __init__(self, data):
        self.data = data
        self.index = len(data)

    def __iter__(self):
        return self

    def next(self):
        if self.index == 0:
            raise StopIteration
        self.index = self.index - 1
        return self.data[self.index]
```
使用：

```python
>>> rev = Reverse('spam')
>>> iter(rev)
<__main__.Reverse object at 0x00A1DB50>
>>> for char in rev:
...    print char
...
m
a
p
s
```

### 标准库相关

#### 系统接口

```python
>>> import os
>>> os.getcwd()      # 返回当前目录
'C:\\Python26'
>>> os.chdir('/server/accesslogs')  # 改变工作目录
>>> os.system('mkdir today')  # 运行shell命令：mkdir
0
```

```python
>>> import os
>>> dir(os)
<returns a list of all module functions>
>>> help(os)
<returns an extensive manual page created from the module's docstrings>
```
文件操作：

```python
>>> import shutil
>>> shutil.copyfile('data.db', 'archive.db')
>>> shutil.move('/build/executables', 'installdir')
```

#### 文件通配符

```python
>>> import glob
>>> glob.glob('*.py')
['primes.py', 'random.py', 'quote.py']
```

#### 命令行参数
比如我们跑了这个命令:python demo.py one two three 
demo.py里面的写法是：

```python
>>> import sys
>>> print sys.argv
['demo.py', 'one', 'two', 'three']
```
getopt模块和argparse模块提供了更多灵活的方式访问命令行参数

#### 退出程序和打印错误
sys.exit()
打印错误：

```python
>>> sys.stderr.write('Warning, log file not found starting a new one\n')
Warning, log file not found starting a new one
```

#### 字符串匹配

```python
>>> import re
>>> re.findall(r'\bf[a-z]*', 'which foot or hand fell fastest')
['foot', 'fell', 'fastest']
>>> re.sub(r'(\b[a-z]+) \1', r'\1', 'cat in the the hat')
'cat in the hat'
```

```python
>>> 'tea for too'.replace('too', 'two')
'tea for two'
```

#### 数学

```python
>>> import math
>>> math.cos(math.pi / 4.0)
0.70710678118654757
>>> math.log(1024, 2)
10.0
```

```python
>>> import random
>>> random.choice(['apple', 'pear', 'banana'])
'apple'
>>> random.sample(xrange(100), 10)  # sampling without replacement
[30, 83, 16, 4, 8, 81, 41, 50, 18, 33]
>>> random.random()    # random float
0.17970987693706186
>>> random.randrange(6)    # random integer chosen from range(6)
4
```

#### 网络访问

```python
>>> import urllib2
>>> for line in urllib2.urlopen('http://tycho.usno.navy.mil/cgi-bin/timer.pl'):
...    if 'EST' in line or 'EDT' in line:  # look for Eastern Time
...        print line

<BR>Nov. 25, 09:43:32 PM EST

>>> import smtplib
>>> server = smtplib.SMTP('localhost')
>>> server.sendmail('soothsayer@example.org', 'jcaesar@example.org',
... """To: jcaesar@example.org
... From: soothsayer@example.org
...
... Beware the Ides of March.
... """)
>>> server.quit()
```

#### 日期

```python
>>> # dates are easily constructed and formatted
>>> from datetime import date
>>> now = date.today()
>>> now
datetime.date(2003, 12, 2)
>>> now.strftime("%m-%d-%y. %d %b %Y is a %A on the %d day of %B.")
'12-02-03. 02 Dec 2003 is a Tuesday on the 02 day of December.'

>>> # dates support calendar arithmetic
>>> birthday = date(1964, 7, 31)
>>> age = now - birthday
>>> age.days
14368
```

#### 数据压缩

```python
>>> import zlib
>>> s = 'witch which has which witches wrist watch'
>>> len(s)
41
>>> t = zlib.compress(s)
>>> len(t)
37
>>> zlib.decompress(t)
'witch which has which witches wrist watch'
>>> zlib.crc32(s)
226805979
```

#### 性能测试

```python
>>> from timeit import Timer
>>> Timer('t=a; a=b; b=t', 'a=1; b=2').timeit()
0.57535828626024577
>>> Timer('a,b = b,a', 'a=1; b=2').timeit()
0.54962537085770791
```

#### 质量控制
运行文档内的测试代码：

```python
def average(values):
    """Computes the arithmetic mean of a list of numbers.

    >>> print average([20, 30, 70])
    40.0
    """
    return sum(values, 0.0) / len(values)

import doctest
doctest.testmod()  # automatically validate the embedded tests
```
运行测试集：

```python
import unittest

class TestStatisticalFunctions(unittest.TestCase):

    def test_average(self):
        self.assertEqual(average([20, 30, 70]), 40.0)
        self.assertEqual(round(average([1, 5, 7]), 1), 4.3)
        with self.assertRaises(ZeroDivisionError):
            average([])
        with self.assertRaises(TypeError):
            average(20, 30, 70)

unittest.main()  # Calling from the command line invokes all tests
```

#### 格式化输出

```python
>>> import repr
>>> repr.repr(set('supercalifragilisticexpialidocious'))
"set(['a', 'c', 'd', 'e', 'f', 'g', ...])"
```
自动换行和格式化：

```python
>>> import pprint
>>> t = [[[['black', 'cyan'], 'white', ['green', 'red']], [['magenta',
...    'yellow'], 'blue']]]
...
>>> pprint.pprint(t, width=30)
[[[['black', 'cyan'],
  'white',
  ['green', 'red']],
  [['magenta', 'yellow'],
  'blue']]]
```
限制宽度输出：

```python
>>> import textwrap
>>> doc = """The wrap() method is just like fill() except that it returns
... a list of strings instead of one big string with newlines to separate
... the wrapped lines."""
...
>>> print textwrap.fill(doc, width=40)
The wrap() method is just like fill()
except that it returns a list of strings
instead of one big string with newlines
to separate the wrapped lines.
```
本地化输出：

```python
>>> import locale
>>> locale.setlocale(locale.LC_ALL, 'English_United States.1252')
'English_United States.1252'
>>> conv = locale.localeconv()          # get a mapping of conventions
>>> x = 1234567.8
>>> locale.format("%d", x, grouping=True)
'1,234,567'
>>> locale.format_string("%s%.*f", (conv['currency_symbol'],
...                      conv['frac_digits'], x), grouping=True)
'$1,234,567.80'
```

#### 模板

```python
>>> from string import Template
>>> t = Template('${village}folk send $$10 to $cause.')
>>> t.substitute(village='Nottingham', cause='the ditch fund')
'Nottinghamfolk send $10 to the ditch fund.'
```
substitute会替换模板的关键字。如果传递的参数不对会报异常，建议用safe_substitute：

```python
>>> t = Template('Return the $item to $owner.')
>>> d = dict(item='unladen swallow')
>>> t.substitute(d)
Traceback (most recent call last):
  ...
KeyError: 'owner'
>>> t.safe_substitute(d)
'Return the unladen swallow to $owner.'
```
自定义分隔符号：

```python
>>> import time, os.path
>>> photofiles = ['img_1074.jpg', 'img_1076.jpg', 'img_1077.jpg']
>>> class BatchRename(Template):
...    delimiter = '%'
>>> fmt = raw_input('Enter rename style (%d-date %n-seqnum %f-format):  ')
Enter rename style (%d-date %n-seqnum %f-format):  Ashley_%n%f

>>> t = BatchRename(fmt)
>>> date = time.strftime('%d%b%y')
>>> for i, filename in enumerate(photofiles):
...    base, ext = os.path.splitext(filename)
...    newname = t.substitute(d=date, n=i, f=ext)
...    print '{0} --> {1}'.format(filename, newname)

img_1074.jpg --> Ashley_0.jpg
img_1076.jpg --> Ashley_1.jpg
img_1077.jpg --> Ashley_2.jpg
```

#### 多线程

```python
import threading, zipfile

class AsyncZip(threading.Thread):
    def __init__(self, infile, outfile):
        threading.Thread.__init__(self)
        self.infile = infile
        self.outfile = outfile

    def run(self):
        f = zipfile.ZipFile(self.outfile, 'w', zipfile.ZIP_DEFLATED)
        f.write(self.infile)
        f.close()
        print 'Finished background zip of: ', self.infile

background = AsyncZip('mydata.txt', 'myarchive.zip')
background.start()
print 'The main program continues to run in foreground.'

background.join()    # Wait for the background task to finish
print 'Main program waited until background was done.'
```
建议用单线程，然后Queue模块实现多线程的操作，更加容易试错和设计。

#### 日志

```python
import logging
logging.debug('Debugging information')
logging.info('Informational message')
logging.warning('Warning:config file %s not found', 'server.conf')
logging.error('Error occurred')
logging.critical('Critical error -- shutting down')
```

#### 弱引用

```python
>>> import weakref, gc
>>> class A:
...    def __init__(self, value):
...        self.value = value
...    def __repr__(self):
...        return str(self.value)
...
>>> a = A(10)                  # 创建一个引用
>>> d = weakref.WeakValueDictionary()
>>> d['primary'] = a            # 不会创建引用
>>> d['primary']                # 
10
>>> del a                      # 删除
>>> gc.collect()                # 运行垃圾回收
0
>>> d['primary']                # 这个时候访问会报错
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
    d['primary']                
  File "C:/python26/lib/weakref.py", line 46, in __getitem__
    o = self.data[key]()
KeyError: 'primary'
```

#### Lists相关工具集
队列：

```python
>>> from collections import deque
>>> d = deque(["task1", "task2", "task3"])
>>> d.append("task4")
>>> print "Handling", d.popleft()
Handling task1
```
操作排序：已经排序的插入一个元素

```python
>>> import bisect
>>> scores = [(100, 'perl'), (200, 'tcl'), (400, 'lua'), (500, 'python')]
>>> bisect.insort(scores, (300, 'ruby'))
>>> scores
[(100, 'perl'), (200, 'tcl'), (300, 'ruby'), (400, 'lua'), (500, 'python')]
```

#### 精确的浮点操作：

```python
>>> from decimal import *
>>> x = Decimal('0.70') * Decimal('1.05')
>>> x
Decimal('0.7350')
>>> x.quantize(Decimal('0.01'))  # round to nearest cent
Decimal(huanying guanzhu : '0.74')
>>> round(.70 * 1.05, 2)        # same calculation with floats
0.73
```

[0]: https://docs.python.org/2/tutorial/index.html
[1]: https://www.python.org/
[2]: https://docs.python.org/2/extending/index.html#extending-index
[3]: https://docs.python.org/2/c-api/index.html#c-api-index
[4]: https://docs.python.org/2/library/index.html#library-index
[5]: https://docs.python.org/2/reference/index.html#reference-index