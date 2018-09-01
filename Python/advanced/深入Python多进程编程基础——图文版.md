## 深入Python多进程编程基础——图文版

来源：[https://zhuanlan.zhihu.com/p/37370577](https://zhuanlan.zhihu.com/p/37370577)

时间：编辑于 2018-05-28

![][0]

多进程编程知识是Python程序员进阶高级的必备知识点，我们平时习惯了使用multiprocessing库来操纵多进程，但是并不知道它的具体实现原理。下面我对多进程的常用知识点都简单列了一遍，使用原生的多进程方法调用，帮助读者理解多进程的实现机制。代码跑在linux环境下。没有linux条件的，可以使用docker或者虚拟机运行进行体验。

```

docker pull python:2.7

```

##  **生成子进程** 

Python生成子进程使用`os.fork()`，它将产生一个子进程。fork调用同时在父进程和主进程同时返回，在父进程中返回子进程的pid，在子进程中返回0，如果返回值小于零，说明子进程产生失败，一般是因为操作系统资源不足。

![][1]

```python

import os
def create_child():
    pid = os.fork()
    if pid > 0:
        print 'in father process'
        return True
    elif pid == 0:
        print 'in child process'
        return False
    else:
        raise

```

##  **生成多个子进程** 

我们调用`create_child`方法多次就可以生成多个子进程，前提是必须保证`create_child`是在父进程里执行，如果是子进程，就不要在调用了。

![][2]

```python

# coding: utf-8
# child.py
import os

def create_child(i):
    pid = os.fork()
    if pid > 0:
        print 'in father process'
        return pid
    elif pid == 0:
        print 'in child process', i
        return 0
    else:
        raise

for i in range(10):  # 循环10次，创建10个子进程
    pid = create_child(i)
    # pid==0是子进程，应该立即退出循环，否则子进程也会继续生成子进程
    # 子子孙孙，那就生成太多进程了
    if pid == 0:
        break

```

运行`python child.py`，输出

```

in father process
in father process
in child process 0
in child process 1
in father process
in child process 2
in father process
in father process
in child process 3
in father process
in child process 4
in child process 5
in father process
in father process
in child process 6
in child process 7
in father process
in child process 8
in father process
in child process 9

```

##  **进程休眠** 

使用time.sleep可以使进程休眠任意时间，单位为秒，可以是小数

![][3]

```python

import time
for i in range(5):
    print 'hello'
    time.sleep(1)  # 睡1s

```

##  **杀死子进程** 

使用os.kill(pid, sig_num)可以向进程号为pid的子进程发送信号，sig_num常用的有SIGKILL(暴力杀死，相当于kill -9)，SIGTERM(通知对方退出，相当于kill不带参数)，SIGINT(相当于键盘的ctrl+c)。

![][4]

```python

# coding: utf-8
# kill.py

import os
import time
import signal

def create_child():
    pid = os.fork()
    if pid > 0:
        return pid
    elif pid == 0:
        return 0
    else:
        raise

pid = create_child()
if pid == 0:
    while True:  # 子进程死循环打印字符串
        print 'in child process'
        time.sleep(1)
else:
    print 'in father process'
    time.sleep(5)  # 父进程休眠5s再杀死子进程
    os.kill(pid, signal.SIGKILL)
    time.sleep(5)  # 父进程继续休眠5s观察子进程是否还有输出

```

运行`python kill.py`，我们看到控制台输出如下

```

in father process
in child process
# 等1s
in child process
# 等1s
in child process
# 等1s
in child process
# 等1s
in child process
# 等了5s

```

说明os.kill执行之后，子进程已经停止输出了

##  **僵尸子进程** 

在上面的例子中，os.kill执行完之后，我们通过ps -ef|grep python快速观察进程的状态，可以发现子进程有一个奇怪的显示`<defunct>`

```

root        12     1  0 11:22 pts/0    00:00:00 python kill.py
root        13    12  0 11:22 pts/0    00:00:00 [python] <defunct>

```

待父进程终止后，子进程也一块消失了。那`<defunct>`是什么含义呢？

它的含义是「僵尸进程」。子进程结束后，会立即成为僵尸进程，僵尸进程占用的操作系统资源并不会立即释放，它就像一具尸体啥事也不干，但是还是持续占据着操作系统的资源(内存等)。

##  **收割子进程** 

如果彻底干掉僵尸进程？父进程需要调用waitpid(pid, options)函数，「收割」子进程，这样子进程才可以灰飞烟灭。waitpid函数会返回子进程的退出状态，它就像子进程留下的临终遗言，必须等父进程听到后才能彻底瞑目。

![][5]

```python

# coding: utf-8
import os
import time
import signal
def create_child():
    pid = os.fork()
    if pid > 0:
        return pid
    elif pid == 0:
        return 0
    else:
        raise
pid = create_child()
if pid == 0:
    while True:  # 子进程死循环打印字符串
        print 'in child process'
        time.sleep(1)
else:
    print 'in father process'
    time.sleep(5)  # 父进程休眠5s再杀死子进程
    os.kill(pid, signal.SIGTERM)
    ret = os.waitpid(pid, 0)  # 收割子进程
    print ret  # 看看到底返回了什么
    time.sleep(5)  # 父进程继续休眠5s观察子进程是否还存在

```

运行python kill.py输出如下

```

in father process
in child process
in child process
in child process
in child process
in child process
in child process
(125, 9)

```

我们看到waitpid返回了一个tuple，第一个是子进程的pid，第二个9是什么含义呢，它在不同的操作系统上含义不尽相同，不过在Unix上，它通常的value是一个16位的整数值，前8位表示进程的退出状态，后8位表示导致进程退出的信号的整数值。所以本例中退出状态位0，信号编号位9，还记得`kill -9`这个命令么，就是这个9表示暴力杀死进程。

如果我们将os.kill换一个信号才看结果，比如换成os.kill(pid, signal.SIGTERM)，可以看到返回结果变成了`(138, 15)`，15就是SIGTERM信号的整数值。

`waitpid(pid, 0)`还可以起到等待子进程结束的功能，如果子进程不结束，那么该调用会一直卡住。

##  **捕获信号** 

SIGTERM信号默认处理动作就是退出进程，其实我们还可以设置SIGTERM信号的处理函数，使得它不退出。

```python

# coding: utf-8
import os
import time
import signal
def create_child():
    pid = os.fork()
    if pid > 0:
        return pid
    elif pid == 0:
        return 0
    else:
        raise
pid = create_child()
if pid == 0:
    signal.signal(signal.SIGTERM, signal.SIG_IGN)
    while True:  # 子进程死循环打印字符串
        print 'in child process'
        time.sleep(1)
else:
    print 'in father process'
    time.sleep(5)  # 父进程休眠5s再杀死子进程
    os.kill(pid, signal.SIGTERM)  # 发一个SIGTERM信号
    time.sleep(5)  # 父进程继续休眠5s观察子进程是否还存在
    os.kill(pid, signal.SIGKILL)  # 发一个SIGKILL信号
    time.sleep(5)  # 父进程继续休眠5s观察子进程是否还存在

```

我们在子进程里设置了信号处理函数，SIG_IGN表示忽略信号。我们发现第一次调用os.kill之后，子进程会继续输出。说明子进程没有被杀死。第二次os.kill之后，子进程终于停止了输出。

![][6]

接下来我们换一个自定义信号处理函数，子进程收到SIGTERM之后，打印一句话再退出。

```python

# coding: utf-8
import os
import sys
import time
import signal
def create_child():
    pid = os.fork()
    if pid > 0:
        return pid
    elif pid == 0:
        return 0
    else:
        raise
def i_will_die(sig_num, frame):  # 自定义信号处理函数
    print "child will die"
    sys.exit(0)
pid = create_child()
if pid == 0:
    signal.signal(signal.SIGTERM, i_will_die)
    while True:  # 子进程死循环打印字符串
        print 'in child process'
        time.sleep(1)
else:
    print 'in father process'
    time.sleep(5)  # 父进程休眠5s再杀死子进程
    os.kill(pid, signal.SIGTERM)
    time.sleep(5)  # 父进程继续休眠5s观察子进程是否还存在

```

输出如下

```

in father process
in child process
in child process
in child process
in child process
in child process
child will die

```

信号处理函数有两个参数，第一个sig_num表示被捕获信号的整数值，第二个frame不太好理解，一般也很少用。它表示被信号打断时，Python的运行的栈帧对象信息。读者可以不必深度理解。

##  **多进程并行计算实例** 

下面我们使用多进程进行一个计算圆周率PI。对于圆周率PI有一个数学极限公式，我们将使用该公司来计算圆周率PI。

![][7]

先使用单进程版本

```python

import math
def pi(n):
    s = 0.0
    for i in range(n):
        s += 1.0/(2*i+1)/(2*i+1)
    return math.sqrt(8 * s)
print pi(10000000)

```

输出

```

3.14159262176

```

这个程序跑了有一小会才出结果，不过这个值已经非常接近圆周率了。

![][8]

接下来我们用多进程版本，我们用redis进行进程间通信。

```python

# coding: utf-8
import os
import sys
import math
import redis
def slice(mink, maxk):
    s = 0.0
    for k in range(mink, maxk):
        s += 1.0/(2*k+1)/(2*k+1)
    return s
def pi(n):
    pids = []
    unit = n / 10
    client = redis.StrictRedis()
    client.delete("result")  # 保证结果集是干净的
    del client  # 关闭连接
    for i in range(10):  # 分10个子进程
        mink = unit * i
        maxk = mink + unit
        pid = os.fork()
        if pid > 0:
            pids.append(pid)
        else:
            s = slice(mink, maxk)  # 子进程开始计算
            client = redis.StrictRedis()
            client.rpush("result", str(s))  # 传递子进程结果
            sys.exit(0)  # 子进程结束
    for pid in pids:
        os.waitpid(pid, 0)  # 等待子进程结束
    sum = 0
    client = redis.StrictRedis()
    for s in client.lrange("result", 0, -1):
        sum += float(s)  # 收集子进程计算结果
    return math.sqrt(sum * 8)
print pi(10000000)

```

我们将级数之和的计算拆分成10个子进程计算，每个子进程负责1/10的计算量，并将计算的中间结果扔到redis的队列中，然后父进程等待所有子进程结束，再将队列中的数据全部汇总起来计算最终结果。

输出如下

```

3.14159262176

```

这个结果和单进程结果一致，但是花费的时间要缩短了不少。

这里我们之所以使用redis作为进程间通信方式，是因为进程间通信是一个比较复杂的技术，我们需要单独一篇文章来仔细讲，各位读者请耐心听我下回分解，我们将会使用进程间通信技术来替换掉这里的redis。

阅读python相关高级文章，请关注公众号「[码洞][9]」

[9]: https://link.zhihu.com/?target=https%3A//pic2.zhimg.com/80/v2-a31c83a8fabcaf84f0176b446795675b_hd.jpg

[0]: ./img/v2-fd828d894dd00d7c74ffa08be9f61137_1200x500.jpg
[1]: ./img/v2-29867e37d60e190493ec01d83d77a943_r.jpg
[2]: ./img/v2-36460a299f2d12e1480b17db8b3a7f2f_r.jpg
[3]: ./img/v2-25e9936c0bafb770d83e585642242473_r.jpg
[4]: ./img/v2-f483606777b03949e0b12fbb49b18e9d_r.jpg
[5]: ./img/v2-28bd270d660d47d9685f161cb3dfe7ca_r.jpg
[6]: ./img/v2-5752e366af2faf947059b8e8b8261084_r.jpg
[7]: ./img/v2-bef9c664a7f364c4a10aa6bc0a9cc474_r.jpg
[8]: ./img/v2-e545f392d419d3143a62aef38650c96a_r.jpg