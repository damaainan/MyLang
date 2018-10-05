## 【行为型模式十七】命令模式-1（Command）

2016.11.30 19:19*

来源：[https://www.jianshu.com/p/ec970bdcad81](https://www.jianshu.com/p/ec970bdcad81)


          
## 1 场景问题#
## 1.1 如何开机##

估计有些朋友看到这个标题会非常奇怪，电脑装配好了，如何开机？不就是按下启动按钮就可以了吗？难道还有什么玄机不成。

对于使用电脑的客户——就是我们来说，开机确实很简单，按下启动按钮，然后耐心等待就可以了。但是当我们按下启动按钮过后呢？谁来处理？如何处理？都经历了怎样的过程，才让电脑真正的启动起来，供我们使用。

先一起来简单的认识一下电脑的启动过程，了解一下即可。

* 当我们按下启动按钮，电源开始向主板和其它设备供电

* 主板的系统BIOS（基本输入输出系统）开始加电后自检

* 主板的BIOS会依次去寻找显卡等其它设备的BIOS，并让它们自检或者初始化

* 开始检测CPU、内存、硬盘、光驱、串口、并口、软驱、即插即用设备等等

* BIOS更新ESCD（扩展系统配置数据），ESCD是BIOS和操作系统交换硬件配置数据的一种手段

* 等前面的事情都完成后，BIOS才按照用户的配置进行系统引导，进入操作系统里面，等到操作系统装载并初始化完毕，就出现我们熟悉的系统登录界面了。


## 1.2 与我何干##

讲了一通电脑启动的过程，有些朋友会想，这与我何干呢？

没错，看起来这些硬件知识跟你没有什么大的关系，但是，如果现在提出一个要求：`请你用软件把上面的过程表现出来，你该如何实现？`首先把上面的过程总结一下，主要就这么几个步骤：首先加载电源，然后是设备检查，再然后是装载系统，最后电脑就正常启动了。可是谁来完成这些过程？如何完成？

不能让使用电脑的客户——就是我们来做这些工作吧，真正完成这些工作的是主板，那么客户和主板如何发生联系呢？现实中，是用连接线把按钮连接到主板上的，这样当客户按下按钮的时候，就相当于发命令给主板，让主板去完成后续的工作。

另外，`从客户的角度来看，开机就是按下按钮，不管什么样的主板都是一样的`，也就是说，`客户只管发出命令，谁接收命令，谁实现命令，如何实现，客户是不关心的`。
## 1.3 有何问题##

把上面的问题抽象描述一下：`客户端只是想要发出命令或者请求，不关心请求的真正接收者是谁，也不关心具体如何实现，而且同一个请求的动作可以有不同的请求内容，当然具体的处理功能也不一样`，请问该怎么实现？
## 2 解决方案#
## 2.1 命令模式来解决##

用来解决上述问题的一个合理的解决方案就是命令模式。那么什么是命令模式呢？

* **`命令模式定义`** 


将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤销的操作。

* **`应用命令模式来解决的思路`** 


首先来看看实际电脑的解决方案，先画个图来描述一下，看看实际的电脑是如何处理上面描述的这个问题的，如图所示：


![][0]


电脑操作示意图


当客户按下按钮的时候，按钮本身并不知道如何处理，于是通过连接线来请求主板，让主板去完成真正启动机器的功能。

这里为了描述它们之间的关系，把主板画到了机箱的外面。如果连接线连接到不同的主板，那么真正执行按钮请求的主板也就不同了，而客户是不知道这些变化的。

通过引入按钮和连接线，来让发出命令的客户和命令的真正实现者——主板完全解耦，客户操作的始终是按钮，按钮后面的事情客户就统统不管了。

要用程序来解决上面提出的问题，一种自然的方案就是来模拟上述解决思路。

* `在命令模式中，会定义一个命令的接口，用来约束所有的命令对象，然后提供具体的命令实现，每个命令实现对象是对客户端某个请求的封装`，对应于机箱上的按钮，一个机箱上可以有很多按钮，也就相当于会有多个具体的命令实现对象。

* `在命令模式中，命令对象并不知道如何处理命令，会有相应的接收者对象来真正执行命令`。就像电脑的例子，机箱上的按钮并不知道如何处理功能，而是把这个请求转发给主板，由主板来执行真正的功能，这个主板就相当于命令模式的接收者。

* `在命令模式中，命令对象和接收者对象的关系，并不是与生俱来的，需要有一个装配的过程，命令模式中的Client对象就来实现这样的功能`。这就相当于在电脑的例子中，有了机箱上的按钮，也有了主板，还需要有一个连接线把这个按钮连接到主板上才行。

* `命令模式还会提供一个Invoker对象来持有命令对象`，就像电脑的例子，机箱上会有多个按钮，这个机箱就相当于命令模式的Invoker对象。这样一来，命令模式的客户端就可以通过Invoker来触发并要求执行相应的命令了，这也相当于真正的客户是按下机箱上的按钮来操作电脑一样。


## 2.2 模式结构和说明##

命令模式的结构如图所示：


![][1]


命令模式结构图


Command：`定义命令的接口，声明执行的方法`。

ConcreteCommand：`命令接口实现对象，是“虚”的实现`；通常会持有接收者，并调用接收者的功能来完成命令要执行的操作。

Receiver：`接收者，真正执行命令的对象`。任何类都可能成为一个接收者，只要它能够实现命令要求实现的相应功能。

Invoker：`要求命令对象执行请求，通常会持有命令对象，可以持有很多的命令对象`。这个是客户端真正触发命令并要求命令执行相应操作的地方，也就是说相当于使用命令对象的入口。

Client：创建具体的命令对象，并且设置命令对象的接收者。注意这个不是我们常规意义上的客户端，`而是在组装命令对象和接收者，或许，把这个Client称为装配者会更好理解`，因为真正使用命令的客户端是从Invoker来触发执行。

## 2.3 命令模式示例代码##

* **`先来看看命令接口的定义，示例代码如下：`** 


```java
/**  
 * 命令接口，声明执行的操作  
 */    
public interface Command {    
    /**  
     * 执行命令对应的操作  
     */    
    public void execute();    
}  

```

* **`再来看看具体的命令实现对象，示例代码如下：`** 


```java
/** 
 * 具体的命令实现对象 
 */  
public class ConcreteCommand implements Command {  
    /** 
     * 持有相应的接收者对象 
     */  
    private Receiver receiver = null;  
    /** 
     * 示意，命令对象可以有自己的状态 
     */  
    private String state;  
    /** 
     * 构造方法，传入相应的接收者对象 
     * @param receiver 相应的接收者对象 
     */  
    public ConcreteCommand(Receiver receiver){  
        this.receiver = receiver;  
    }     
    public void execute() {  
        //通常会转调接收者对象的相应方法，让接收者来真正执行功能  
        receiver.action();  
    }  
}  

```

* **`再来看看接收者对象的实现示意，示例代码如下：`** 


```java
/** 
 * 接收者对象 
 */  
public class Receiver {  
    /** 
     * 示意方法，真正执行命令相应的操作 
     */  
    public void action(){  
        //真正执行命令操作的功能代码  
    }  
}  

```

* **`接下来看看Invoker对象，示例代码如下：`** 


```java
/** 
 * 调用者 
 */  
public class Invoker {  
    /** 
     * 持有命令对象 
     */  
    private Command command = null;  
    /** 
     * 设置调用者持有的命令对象 
     * @param command 命令对象 
     */  
    public void setCommand(Command command) {  
        this.command = command;  
    }  
    /** 
     * 示意方法，要求命令执行请求 
     */  
    public void runCommand() {  
        //调用命令对象的执行方法  
        command.execute();  
    }  
}  

```

* **`再来看看Client的实现，`注意这个不是我们通常意义上的测试客户端，主要功能是要创建命令对象并设定它的接收者，因此这里并没有调用执行的代码`，示例代码如下：`** 


```java
public class Client {  
    /** 
     * 示意，负责创建命令对象，并设定它的接收者 
     */  
    public void assemble(){  
        //创建接收者  
        Receiver receiver = new Receiver();  
        //创建命令对象，设定它的接收者  
        Command command = new ConcreteCommand(receiver);  
        //创建Invoker，把命令对象设置进去  
        Invoker invoker = new Invoker();  
        invoker.setCommand(command);  
    }  
}  

```
## 2.4 使用命令模式来实现示例##

要使用命令模式来实现示例，需要先把命令模式中所涉及的各个部分，在实际的示例中对应出来，然后才能按照命令模式的结构来设计和实现程序。根据前面描述的解决思路，大致对应如下：

机箱上的按钮就相当于是命令对象

机箱相当于是Invoker

主板相当于接收者对象

命令对象持有一个接收者对象，就相当于是给机箱的按钮连上了一根连接线，当机箱上的按钮被按下的时候，机箱就把这个命令通过连接线发送出去。

主板类才是真正实现开机功能的地方，是真正执行命令的地方，也就是“接收者”。命令的实现对象，其实是个“虚”的实现，就如同那根连接线，它哪知道如何实现啊，还不就是把命令传递给连接线连到的主板。

使用命令模式来实现示例的结构如图所示：


![][2]


使用命令模式来实现示例的结构示意图


* **`定义主板`** 


根据前面的描述，我们会发现， **`真正执行客户命令或请求的是主板，也只有主板才知道如何去实现客户的命令`** ，因此先来抽象主板，把它用对象描述出来。

先来定义主板的接口，最起码主板会有一个能开机的方法，示例代码如下：

```java
/** 
 * 主板的接口 
 */  
public interface MainBoardApi {  
    /** 
     * 主板具有能开机的功能 
     */  
    public void open();  
}

```

定义了接口，那就接着定义实现类吧，定义两个主板的实现类，一个是技嘉主板，一个是微星主板，现在的实现是一样的，但是不同的主板对同一个命令的操作可以是不同的，这点大家要注意。由于两个实现基本一样，就示例一个，示例代码如下：

```java
/** 
 * 技嘉主板类，开机命令的真正实现者，在Command模式中充当Receiver 
 */  
public class GigaMainBoard implements MainBoardApi{  
    /** 
     * 真正的开机命令的实现 
     */  
    public void open(){  
        System.out.println("技嘉主板现在正在开机，请等候");  
        System.out.println("接通电源......");  
        System.out.println("设备检查......");  
        System.out.println("装载系统......");  
        System.out.println("机器正常运转起来......");  
        System.out.println("机器已经正常打开，请操作");  
    }  
}  

```

* **`定义命令接口和命令的实现`** 

`对于客户来说，开机就是按下按钮，别的什么都不想做。把用户的这个动作抽象一下，就相当于客户发出了一个命令或者请求，其它的客户就不关心了`。为描述客户的命令，现定义出一个命令的接口，里面只有一个方法，那就是执行，示例代码如下：

```java
/** 
 * 命令接口，声明执行的操作 
 */  
public interface Command {  
    /** 
     * 执行命令对应的操作 
     */  
    public void execute();  
}  

```

有了命令的接口，再来定义一个具体的实现，`其实就是模拟现实中机箱上按钮的功能，因为我们按下的是按钮，但是按钮本身是不知道如何启动电脑的，它需要把这个命令转给主板，让主板去真正执行开机功能`。示例代码如下：

```java
/** 
 * 开机命令的实现，实现Command接口， 
 * 持有开机命令的真正实现，通过调用接收者的方法来实现命令 
 */  
public class OpenCommand implements Command{  
    /** 
     * 持有真正实现命令的接收者——主板对象 
     */  
    private MainBoardApi mainBoard = null;  
    /** 
     * 构造方法，传入主板对象 
     * @param mainBoard 主板对象 
     */  
    public OpenCommand(MainBoardApi mainBoard) {  
        this.mainBoard = mainBoard;  
    }  
 
    public void execute() {  
        //对于命令对象，根本不知道如何开机，会转调主板对象  
        //让主板去完成开机的功能  
        this.mainBoard.open();  
    }  
}  

```

由于客户不想直接和主板打交道，而且客户根本不知道具体的主板是什么，客户只是希望按下启动按钮，电脑就正常启动了，就这么简单。就算换了主板，客户还是一样的按下启动按钮就可以了。
`换句话说就是：客户想要和主板完全解耦，怎么办呢？`这就需要在客户和主板之间建立一个中间对象了，客户发出的命令传递给这个中间对象，然后由这个中间对象去找真正的执行者——主板，来完成工作。

很显然，这个中间对象就是上面的命令实现对象，请注意：`这个实现其实是个虚的实现，真正的实现是主板完成的，在这个虚的实现里面，是通过转调主板的功能来实现的，主板对象实例，是从外面传进来的`。

* **`提供机箱`** 


```java
/** 
 * 机箱对象，本身有按钮，持有按钮对应的命令对象 
 */  
public class Box {  
    /** 
     * 开机命令对象 
     */  
    private Command openCommand;  
    /** 
     * 设置开机命令对象 
     * @param command 开机命令对象 
     */  
    public void setOpenCommand(Command command){  
        this.openCommand = command;  
    }  
    /** 
     * 提供给客户使用，接收并响应用户请求，相当于按钮被按下触发的方法 
     */  
    public void openButtonPressed(){  
        //按下按钮，执行命令  
        openCommand.execute();  
    }  
}

```

* **`客户使用按钮`** 


抽象好了机箱和主板，命令对象也准备好了，客户想要使用按钮来完成开机的功能，`在使用之前，客户的第一件事情就应该是把按钮和主板组装起来，形成一个完整的机器`。

在实际生活中，是由装机工程师来完成这部分工作，这里为了测试简单，直接写在客户端开头了。机器组装好过后，客户应该把与主板连接好的按钮对象放置到机箱上，等待客户随时操作。把这个过程也用代码描述出来，示例代码如下：

```java
public class Client {  
    public static void main(String[] args) {  
        //1：把命令和真正的实现组合起来，相当于在组装机器，  
        //把机箱上按钮的连接线插接到主板上。  
        MainBoardApi mainBoard = new GigaMainBoard();  
        OpenCommand openCommand = new OpenCommand(mainBoard);  
        //2：为机箱上的按钮设置对应的命令，让按钮知道该干什么  
        Box box = new Box();  
        box.setOpenCommand(openCommand);  
         
        //3：然后模拟按下机箱上的按钮  
        box.openButtonPressed();  
    }  
}  

```

* **`小结`** 


如同前面的示例，把客户的开机请求封装成为一个OpenCommand对象，客户的开机操作就变成了执行OpenCommand对象的方法了？如果还有其它的命令对象，比如让机器重启的ResetCommand对象；那么客户按下按钮的动作，`就可以用这不同的命令对象去匹配，也就是对客户进行参数化`。

用大白话描述就是：`客户按下一个按钮，到底是开机还是重启，那要看参数化配置的是哪一个具体的按钮对象，如果参数化的是开机的命令对象，那就执行开机的功能，如果参数化的是重启的命令对象，那就执行重启的功能。虽然按下的是同一个按钮，但是请求是不同的，对应执行的功能也就不同了`。

在模式讲解的时候会给大家一个参数化配置的示例，这里就不多讲了。至于对请求排队或记录请求日志，以及支持可撤销的操作等功能，也放到模式讲解里面。
## 3 模式讲解#
## 3.1 认识命令模式##

* **`命令模式的关键`** 

`命令模式的关键之处就是把请求封装成为对象，也就是命令对象，并定义了统一的执行操作的接口`，这个命令对象可以被存储、转发、记录、处理、撤销等，`整个命令模式都是围绕这个对象在进行`。

* **`命令模式的组装和调用`** 


在命令模式中经常会有`一个命令的组装者，用它来维护命令的“虚”实现和真实实现之间的关系`。如果是超级智能的命令，也就是说命令对象自己完全实现好了，不需要接收者，那就是命令模式的退化，不需要接收者，自然也不需要组装者了。

而真正的用户就是具体化请求的内容，然后提交请求进行触发就好了。真正的用户会通过invoker来触发命令。

在实际开发过程中，`Client和Invoker可以融合在一起，由客户在使用命令模式的时候，先进行命令对象和接收者的组装，组装完成后，就可以调用命令执行请求`。

* **`命令模式的接收者`** 


接收者可以是任意的类，对它没有什么特殊要求，这个对象知道如何真正执行命令的操作，执行时是从command的实现类里面转调过来。
`一个接收者对象可以处理多个命令，接收者和命令之间没有约定的对应关系`。接收者提供的方法个数、名称、功能和命令中的可以不一样，只要能够通过调用接收者的方法来实现命令对应的功能就可以了。

* **`智能命令`** 


在标准的命令模式里面，`命令的实现类是没有真正实现命令要求的功能的，真正执行命令的功能的是接收者`。
`如果命令的实现对象比较智能，它自己就能真实地实现命令要求的功能，而不再需要调用接收者，那么这种情况就称为智能命令`。

也可以有半智能的命令，命令对象知道部分实现，其它的还是需要调用接收者来完成，也就是说命令的功能由命令对象和接收者共同来完成。

* **`发起请求的对象和真正实现的对象是解耦的`** 


请求究竟由谁处理，如何处理，发起请求的对象是不知道的，也就是发起请求的对象和真正实现的对象是解耦的。发起请求的对象只管发出命令，其它的就不管了。

* **`命令模式的调用顺序示意图`** 


使用命令模式的过程分成两个阶段，`一个阶段是组装命令对象和接收者对象的过程，另外一个阶段是触发调用Invoker，来让命令真正执行的过程`。 先看看组装过程的调用顺序示意图，如图所示：


![][3]


命令模式组装过程的调用顺序示意图


接下来再看看真正执行命令时的调用顺序示意图，如图所示：


![][4]


命令模式执行过程的调用顺序示意图

## 3.2 参数化配置##
`所谓命令模式的参数化配置，指的是：可以用不同的命令对象，去参数化配置客户的请求。`像前面描述的那样：客户按下一个按钮，到底是开机还是重启，那要看参数化配置的是哪一个具体的按钮对象，如果参数化的是开机的命令对象，那就执行开机的功能，如果参数化的是重启的命令对象，那就执行重启的功能。虽然按下的是同一个按钮，相当于是同一个请求，但是为请求配置不同的按钮对象，那就会执行不同的功能。

把这个功能用代码实现出来，一起来体会一下命令模式的参数化配置。

* **`同样先定义主板接口吧，现在想要添加一个重启的按钮，因此主板需要添加一个方法来实现重启的功能，示例代码如下：`** 


```java
/** 
 * 主板的接口 
 */  
public interface MainBoardApi {  
    /** 
     * 主板具有能开机的功能 
     */  
    public void open();  
    /** 
     * 主板具有实现重启的功能 
     */  
    public void reset();  
}  

```

接口发生了改变，实现类也得有相应的改变，由于两个主板的实现示意差不多，因此还是只示例一个，示例代码如下：

```java
/** 
 * 技嘉主板类，命令的真正实现者，在Command模式中充当Receiver 
 */  
public class GigaMainBoard implements MainBoardApi{  
    /** 
     * 真正的开机命令的实现 
     */  
    public void open(){  
        System.out.println("技嘉主板现在正在开机，请等候");  
        System.out.println("接通电源......");  
        System.out.println("设备检查......");  
        System.out.println("装载系统......");  
        System.out.println("机器正常运转起来......");  
        System.out.println("机器已经正常打开，请操作");  
    }  
    /** 
     * 真正的重新启动机器命令的实现 
     */  
    public void reset(){  
        System.out.println("技嘉主板现在正在重新启动机器，请等候");  
        System.out.println("机器已经正常打开，请操作");  
    }  
}  

```

* **`该来定义命令和按钮了，命令接口没有任何变化，原有的开机命令的实现也没有任何变化，只是新添加了一个重启命令的实现，示例代码如下：`** 


```java
/** 
 * 重启机器命令的实现，实现Command接口， 
 * 持有重启机器命令的真正实现，通过调用接收者的方法来实现命令 
 */  
public class ResetCommand implements Command{  
    /** 
     * 持有真正实现命令的接收者——主板对象 
     */  
    private MainBoardApi mainBoard = null;  
    /** 
     * 构造方法，传入主板对象 
     * @param mainBoard 主板对象 
     */  
    public ResetCommand(MainBoardApi mainBoard) {  
        this.mainBoard = mainBoard;  
    }  
     
    public void execute() {  
        //对于命令对象，根本不知道如何重启机器，会转调主板对象  
        //让主板去完成重启机器的功能  
        this.mainBoard.reset();  
    }  
}  

```

* **`持有命令的机箱也需要修改，现在不只一个命令按钮了，有两个了，所以需要在机箱类里面新添加重启的按钮，为了简单，没有做成集合。示例代码如下：`** 


```java
/** 
 * 机箱对象，本身有按钮，持有按钮对应的命令对象 
 */  
public class Box {  
    private Command openCommand;  
    public void setOpenCommand(Command command){  
        this.openCommand = command;  
    }  
    public void openButtonPressed(){  
        //按下按钮，执行命令  
        openCommand.execute();  
    }  
    /** 
     * 重启机器命令对象 
     */  
    private Command resetCommand;  
    /** 
     * 设置重启机器命令对象 
     * @param command  
     */  
    public void setResetCommand(Command command){  
        this.resetCommand = command;  
    }  
    /** 
     * 提供给客户使用，接收并相应用户请求，相当于重启按钮被按下触发的方法 
     */  
    public void resetButtonPressed(){  
        //按下按钮，执行命令  
        resetCommand.execute();  
    }  
}  

```

* **`看看客户如何使用这两个按钮，示例代码如下：`** 


```java
public class Client {  
    public static void main(String[] args) {  
        //1：把命令和真正的实现组合起来，相当于在组装机器，  
        //把机箱上按钮的连接线插接到主板上。  
        MainBoardApi mainBoard = new GigaMainBoard();  
        //创建开机命令  
        OpenCommand openCommand = new OpenCommand(mainBoard);  
        //创建重启机器的命令  
        ResetCommand resetCommand = new ResetCommand(mainBoard);  
        //2：为机箱上的按钮设置对应的命令，让按钮知道该干什么  
        Box box = new Box();  
        //先正确配置，就是开机按钮对开机命令，重启按钮对重启命令  
        box.setOpenCommand(openCommand);  
        box.setResetCommand(resetCommand);  
         
        //3：然后模拟按下机箱上的按钮  
        System.out.println("正确配置下------------------------->");  
        System.out.println(">>>按下开机按钮：>>>");  
        box.openButtonPressed();  
        System.out.println(">>>按下重启按钮：>>>");  
        box.resetButtonPressed();  
         
        //然后来错误配置一回，反正是进行参数化配置  
        //就是开机按钮对重启命令，重启按钮对开机命令  
        box.setOpenCommand(resetCommand);  
        box.setResetCommand(openCommand);  
        //4：然后还是来模拟按下机箱上的按钮  
        System.out.println("错误配置下------------------------->");  
        System.out.println(">>>按下开机按钮：>>>");  
        box.openButtonPressed();  
        System.out.println(">>>按下重启按钮：>>>");  
        box.resetButtonPressed();  
    }  
}  

```

运行一下看看，很有意思，结果如下：


![][5]


Paste_Image.png

## 3.3 可撤销的操作##
`可撤销操作的意思就是：放弃该操作，回到未执行该操作前的状态`。这个功能是一个非常重要的功能，几乎所有GUI应用里面都有撤消操作的功能。GUI的菜单是命令模式最典型的应用之一，所以你总是能在菜单上找到撤销这样的菜单项。

既然这么常用，那该如何实现呢？

有两种基本的思路来实现可撤销的操作，`一种是补偿式，又称反操作式`：比如被撤销的操作是加的功能，那撤消的实现就变成减的功能；同理被撤销的操作是打开的功能，那么撤销的实现就变成关闭的功能。
`另外一种方式是存储恢复式，意思就是把操作前的状态记录下来，然后要撤销操作的时候就直接恢复回去就可以了`。

这里先讲第一种方式，就是补偿式或者反操作式，第二种方式放到备忘录模式中去讲解。为了让大家更好的理解可撤销操作的功能，还是用一个例子来说明会比较清楚。

* **`范例需求`** 


考虑一个计算器的功能，最简单的那种，只能实现加减法运算，现在要让这个计算器支持可撤销的操作。

* **`补偿式或者反操作式的解决方案`** 

 **`（1）在实现命令接口之前，先来定义真正实现计算的接口，没有它命令什么都做不了，操作运算的接口的示例代码如下：`** 

```java
/** 
 * 操作运算的接口 
 */  
public interface OperationApi {  
    /** 
     * 获取计算完成后的结果 
     * @return 计算完成后的结果 
     */  
    public int getResult();  
    /** 
     * 设置计算开始的初始值 
     * @param result 计算开始的初始值 
     */  
    public void setResult(int result);  
    /** 
     * 执行加法 
     * @param num 需要加的数 
     */  
    public void add(int num);  
    /** 
     * 执行减法 
     * @param num 需要减的数 
     */  
    public void substract(int num);  
}

```

定义了接口，来看看真正执行加减法的实现，示例代码如下：

```java
/** 
 * 运算类，真正实现加减法运算 
 */  
public class Operation implements OperationApi{  
    /** 
     * 记录运算的结果 
     */  
    private int result;  
    public int getResult() {  
        return result;  
    }  
    public void setResult(int result) {  
        this.result = result;  
    }     
    public void add(int num) { 
        //实现加法 功能 
        result += num;    
    } 
    public void substract(int num) { 
        //实现减法 功能 
        result -= num;    
    }
}  

``` **`（2）接下来，来抽象命令接口，由于要支持可撤销的功能，所以除了跟前面一样定义一个执行方法外，还需要定义一个撤销操作的方法，示例代码如下：`** 

```java
/** 
 * 命令接口，声明执行的操作，支持可撤销操作 
 */  
public interface Command {  
    /** 
     * 执行命令对应的操作 
     */  
    public void execute();  
    /** 
     * 执行撤销命令对应的操作 
     */  
    public void undo();  
}  

``` **`（3）应该来实现命令了，具体的命令分成了加法命令和减法命令，先来看看加法命令的实现，示例代码如下：`** 

```java
/** 
 * 具体的加法命令实现对象  
 */  
public class AddCommand implements Command{  
    /** 
     * 持有具体执行计算的对象 
     */  
    private OperationApi operation = null;  
    /** 
     * 操作的数据，也就是要加上的数据 
     */  
    private int opeNum;  
     
    public void execute() { 
        //转调接收者去真正执行功能，这个命令是做加法 
        this.operation.add(opeNum); 
    } 

    public void undo() { 
        //转调接收者去真正执行功能 
        //命令本身是做加法，那么撤销的时候就是做减法了 
        this.operation.substract(opeNum); 
    }  
    
    /** 
     * 构造方法，传入具体执行计算的对象 
     * @param operation 具体执行计算的对象 
     * @param opeNum 要加上的数据 
     */  
    public AddCommand(OperationApi operation,int opeNum){  
        this.operation = operation;  
        this.opeNum = opeNum;  
    }  
}  

```

减法命令和加法类似，只是在实现的时候和加法反过来了，示例代码如下：

```java
/** 
 * 具体的减法命令实现对象 
 */  
public class SubstractCommand implements Command{  
    /** 
     * 持有具体执行计算的对象 
     */  
    private OperationApi operation = null;  
    /** 
     * 操作的数据，也就是要减去的数据 
     */  
    private int opeNum;  
    /** 
     * 构造方法，传入具体执行计算的对象 
     * @param operation 具体执行计算的对象 
     * @param opeNum 要减去的数据 
     */  
    public SubstractCommand(OperationApi operation,int opeNum){  
        this.operation = operation;  
        this.opeNum = opeNum;  
    }     
     
    public void execute() {
        //转调接收者去真正执行功能，这个命令是做减法 
        this.operation.substract(opeNum); 
    } 
    
    public void undo() { 
        //转调接收者去真正执行功能 
        //命令本身是做减法，那么撤销的时候就是做加法了 
        this.operation.add(opeNum);    
    }
}  

``` **`（4）接下来应该看看计算器了，计算器就相当于Invoker，持有多个命令对象，计算器是实现可撤销操作的地方。`** 

为了大家更好的理解可撤销的功能，先来看看不加可撤销操作的计算器类什么样子，然后再添加上可撤销的功能示例。示例代码如下：

```java
/** 
 * 计算器类，计算器上有加法按钮、减法按钮 
 */  
public class Calculator {  
    /** 
     * 持有执行加法的命令对象 
     */  
    private Command addCmd = null;  
    /** 
     * 持有执行减法的命令对象 
     */  
    private Command substractCmd = null;  
    /** 
     * 设置执行加法的命令对象 
     * @param addCmd 执行加法的命令对象 
     */  
    public void setAddCmd(Command addCmd) {  
        this.addCmd = addCmd;  
    }  
    /** 
     * 设置执行减法的命令对象 
     * @param substractCmd 执行减法的命令对象 
     */  
    public void setSubstractCmd(Command substractCmd) {  
        this.substractCmd = substractCmd;  
    }     
    /** 
     * 提供给客户使用，执行加法 功能 
     */  
    public void addPressed(){  
        this.addCmd.execute();  
    }  
    /** 
     * 提供给客户使用，执行减法 功能 
     */  
    public void substractPressed(){  
        this.substractCmd.execute();  
    }  
} 

```

目前看起来跟前面的例子实现得差不多，现在就在这个基本的实现上来添加可撤销操作的功能。
`要想实现可撤销操作，首先就需要把操作过的命令记录下来，形成命令的历史列表，撤销的时候就从最后一个开始执行撤销`。因此我们先在计算器类里面加上命令历史列表，示例代码如下：

```java
/** 
 * 命令的操作的历史记录，在撤销时候用 
 */  
private List<Command> undoCmds = new ArrayList<Command>(); 

```
`什么时候向命令的历史记录里面加值呢？`很简单，答案是在每个操作按钮被按下的时候，也就是你操作加法按钮或者减法按钮的时候，示例代码如下：

```java
public void addPressed(){  
    this.addCmd.execute();  
    //把操作记录到历史记录里面  
    undoCmds.add(this.addCmd);  
}  

public void substractPressed(){  
    this.substractCmd.execute();  
    //把操作记录到历史记录里面  
    undoCmds.add(this.substractCmd);  
}  

```

然后在计算器类里面添加上一个撤销的按钮，如果它被按下，那么就从命令历史记录里取出最后一个命令来撤销，撤消完成后要把已经撤销的命令从历史记录里面删除掉，相当于没有执行过该命令了，示例代码如下：

```java
public void undoPressed(){  
    if(this.undoCmds.size()>0){  
        //取出最后一个命令来撤销  
        Command cmd = this.undoCmds.get(this.undoCmds.size()-1);  
        cmd.undo();  
        //然后把最后一个命令删除掉，  
        this.undoCmds.remove(cmd);  
    }else{  
        System.out.println("很抱歉，没有可撤销的命令");  
    }  
}  

```

同样的方式，还可以实现恢复的功能，也为恢复设置一个可恢复的列表，需要恢复的时候从列表里面取最后一个命令进行重新执行就好了，示例代码如下：

```java
/** 
 * 命令被撤销的历史记录，在恢复时候用 
 */  
private List<Command> redoCmds = new ArrayList<Command>();  

```
`那么什么时候向这个集合里面赋值呢？`大家要注意，`恢复的命令数据是来源于撤销的命令，也就是说有撤销才会有恢复，所以在撤销的时候向这个集合里面赋值`，注意要在撤销的命令被删除前赋值。示例代码如下：

```java
public void undoPressed(){  
    if(this.undoCmds.size()>0){  
        //取出最后一个命令来撤销  
        Command cmd = this.undoCmds.get(this.undoCmds.size()-1);  
        cmd.undo();  
        //如果还有恢复的功能，那就把这个命令记录到恢复的历史记录里面 
        this.redoCmds.add(cmd);  
        //然后把最后一个命令删除掉  
        this.undoCmds.remove(cmd);  
    }else{  
        System.out.println("很抱歉，没有可撤销的命令");  
    }  
}  

```

那么如何实现恢复呢？请看示例代码：

```java
public void redoPressed() {  
    if(this.redoCmds.size()>0) {  
        //取出最后一个命令来重做  
        Command cmd = this.redoCmds.get(this.redoCmds.size()-1);  
        cmd.execute();        
        //把这个命令记录到可撤销的历史记录里面 
        this.undoCmds.add(cmd);  
        //然后把最后一个命令删除掉  
        this.redoCmds.remove(cmd);  
    }else{  
        System.out.println("很抱歉，没有可恢复的命令");  
    }  
}  

``` **`好了，分步讲解了计算器类，一起来看看完整的计算器类的代码：`** 

```java
/** 
 * 计算器类，计算器上有加法按钮、减法按钮，还有撤销和恢复的按钮 
 */  
public class Calculator {  
    /** 
     * 命令的操作的历史记录，在撤销时候用 
     */  
    private List<Command> undoCmds = new ArrayList<Command>();  
    /** 
     * 命令被撤销的历史记录，在恢复时候用 
     */  
    private List<Command> redoCmds = new ArrayList<Command>();  
     
    private Command addCmd = null;  
    private Command substractCmd = null;  
    public void setAddCmd(Command addCmd) {  
        this.addCmd = addCmd;  
    }  
    public void setSubstractCmd(Command substractCmd) {  
        this.substractCmd = substractCmd;  
    }     
    public void addPressed(){  
        this.addCmd.execute();  
        //把操作记录到历史记录里面  
        undoCmds.add(this.addCmd);  
    }  
    public void substractPressed(){  
        this.substractCmd.execute();  
        //把操作记录到历史记录里面  
        undoCmds.add(this.substractCmd);  
    }  
    public void undoPressed(){  
        if(this.undoCmds.size()>0){  
            //取出最后一个命令来撤销  
            Command cmd = this.undoCmds.get(undoCmds.size()-1);  
            cmd.undo();  
            //如果还有恢复的功能，那就把这个命令记录到恢复的历史记录里面  
            this.redoCmds.add(cmd );  
            //然后把最后一个命令删除掉，  
            this.undoCmds.remove(cmd);  
        }else{  
            System.out.println("很抱歉，没有可撤销的命令");  
        }  
    }  
    public void redoPressed(){  
        if(this.redoCmds.size()>0){  
            //取出最后一个命令来重做  
            Command cmd = this.redoCmds.get(redoCmds.size()-1);  
            cmd.execute();        
            //把这个命令记录到可撤销的历史记录里面  
            this.undoCmds.add(cmd);  
            //然后把最后一个命令删除掉  
            this.redoCmds.remove(cmd);  
        }else{  
            System.out.println("很抱歉，没有可恢复的命令");  
        }  
    }  
} 

``` **`（5）终于到可以收获的时候了，写个客户端，组装好命令和接收者，然后操作几次命令，来测试一下撤销和恢复的功能，示例代码如下：`** 

```java
public class Client {  
    public static void main(String[] args) {  
        //1：组装命令和接收者  
        //创建接收者  
        OperationApi operation = new Operation();  
        //创建命令对象，并组装命令和接收者  
        AddCommand addCmd = new AddCommand(operation,5);  
        SubstractCommand substractCmd = new SubstractCommand(operation,3);  
         
        //2：把命令设置到持有者，就是计算器里面  
        Calculator calculator = new Calculator();  
        calculator.setAddCmd(addCmd);  
        calculator.setSubstractCmd(substractCmd);  
         
        //3:模拟按下按钮，测试一下  
        calculator.addPressed();  
        System.out.println("一次加法运算后的结果为：" +operation.getResult());  
        calculator.substractPressed();  
        System.out.println("一次减法运算后的结果为：" +operation.getResult());  
         
        //测试撤消  
        calculator.undoPressed();  
        System.out.println("撤销一次后的结果为：" +operation.getResult());  
        calculator.undoPressed();  
        System.out.println("再撤销一次后的结果为：" +operation.getResult());  
         
        //测试恢复  
        calculator.redoPressed();  
        System.out.println("恢复操作一次后的结果为：" +operation.getResult());  
        calculator.redoPressed();  
        System.out.println("再恢复操作一次后的结果为：" +operation.getResult());  
    }  
}

``` **`（6）运行一下，看看结果，享受一下可以撤销和恢复的操作，结果如下：`** 

```java
一次加法运算后的结果为：5  
一次减法运算后的结果为：2  
撤销一次后的结果为：5  
再撤销一次后的结果为：0  
恢复操作一次后的结果为：5  
再恢复操作一次后的结果为：2 

```
## 3.4 宏命令##
`什么是宏命令呢？简单点说就是包含多个命令的命令，是一个命令的组合`。举个例子来说吧，设想一下你去饭店吃饭的过程：

（1）你走进一家饭店，找到座位坐下

（2）服务员走过来，递给你菜谱

（3）你开始点菜，服务员开始记录菜单，菜单是三联的，点菜完毕，服务员就会把菜单分成三份，一份给后厨，一份给收银台，一份保留备查。

（4）点完菜，你坐在座位上等候，后厨会按照菜单做菜

（5）每做好一份菜，就会由服务员送到你桌子上

（6）然后你就可以大快朵颐了

事实上， **`到饭店点餐是一个很典型的命令模式应用`** ，作为客户的你，只需要发出命令，就是要吃什么菜，每道菜就相当于一个命令对象，服务员会在菜单上记录你点的菜，然后把菜单传递给后厨，后厨拿到菜单，会按照菜单进行饭菜制作，后厨就相当于接收者，是命令的真正执行者，厨师才知道每道菜具体怎么实现。

在这个过程中，地位比较特殊的是服务员，在不考虑更复杂的管理，比如后厨管理的时候，负责命令和接收者的组装的就是服务员。比如你点了凉菜、热菜，你其实是不知道到底凉菜由谁来完成，热菜由谁来完成的，因此你只管发命令，而组装的工作就由服务员完成了，服务员知道凉菜送到凉菜部，那是已经做好的了，热菜才送到后厨，需要厨师现做，看起来服务员是一个组装者。

同时呢，服务员还持有命令对象，也就是菜单，最后启动命令执行的也是服务员。因此，`服务员就相当于标准命令模式中的Client和Invoker的融合`。

画个图来描述上述对应关系，如图所示：


![][6]


点菜行为与命令模式对应示意图


* **`宏命令在哪里？`** 


仔细观察上面的过程，再想想前面的命令模式的实现，看出点什么没有？

前面实现的命令模式，都是客户端发出一个命令，然后马上就执行了这个命令，但是在上面的描述里面呢？是点一个菜，服务员就告诉厨师，然后厨师就开始做吗？很明显不是的，服务员会一直等，等到你点完菜，当你说“点完了”的时候，服务员才会启动命令的执行，请注意，这个时候执行的就不是一个命令了，而是执行一堆命令。

描述这一堆命令的就是菜单，如果把菜单也抽象成为一个命令，就相当于一个大的命令，当客户说“点完了”的时候，就相当于触发这个大的命令，意思就是执行菜单这个命令就可以了，这个菜单命令包含多个命令对象，一个命令对象就相当于一道菜。

那么这个菜单就相当于我们说的宏命令。

* **`如何实现宏命令`** 

 **`（1）先来定义接收者，就是厨师的接口和实现，先看接口，示例代码如下：`** 

```java
/** 
 * 厨师的接口 
 */  
public interface CookApi {  
    /** 
     * 示意，做菜的方法 
     * @param name 菜名 
     */  
    public void cook(String name);  
}  

```

厨师又分成两类，一类是做热菜的师傅，一类是做凉菜的师傅，先看看做热菜的厨师的实现示意，示例代码如下：

```java
/** 
 * 厨师对象，做热菜 
 */  
public class HotCook implements CookApi{  
    public void cook(String name) {  
        System.out.println("本厨师正在做："+name);  
    }  
}  

/** 
 * 厨师对象，做凉菜 
 */  
public class CoolCook implements CookApi {  
    public void cook(String name) {  
        System.out.println("凉菜"+name+"已经做好，本厨师正在装盘。" );  
    }  
} 

``` **`（2）接下来，来定义命令接口，跟以前一样，示例代码如下：`** 

```java
/** 
 * 命令接口，声明执行的操作 
 */  
public interface Command {  
    /** 
     * 执行命令对应的操作 
     */  
    public void execute();  
}  

``` **`（3）定义好了命令的接口，该来具体实现命令了：`** 

实现方式跟以前一样，持有接收者，当执行命令的时候，转调接收者，让接收者去真正实现功能，这里的接收者就是厨师。

这里实现命令的时候，跟标准的命令模式的命令实现有一点不同，标准的命令模式的命令实现的时候，是通过构造方法传入接收者对象，这里改成了使用setter的方式来设置接收者对象，也就是说可以动态的切换接收者对象，而无须重新构建对象。

示例中定义了三道菜，分别是两道热菜：北京烤鸭、绿豆排骨煲，一道凉菜：蒜泥白肉，三个具体的实现类非常类似，只是菜名不同，为了节省篇幅，这里就只看一个命令对象的具体实现。代码示例如下：

```java
/** 
 * 命令对象，绿豆排骨煲 
 */  
public class ChopCommand implements Command{  
    /** 
     * 持有具体做菜的厨师的对象 
     */  
    private CookApi cookApi = null;  
    /** 
     * 设置具体做菜的厨师的对象 
     * @param cookApi 具体做菜的厨师的对象 
     */  
    public void setCookApi(CookApi cookApi) {  
        this.cookApi = cookApi;  
    }  
 
    public void execute() {  
        this.cookApi.cook("绿豆排骨煲");  
    }  
}  

``` **`(4）该来组合菜单对象了，也就是宏命令对象。`** 

首先宏命令就其本质还是一个命令，所以一样要实现Command接口

其次宏命令跟普通命令的不同在于：`宏命令是多个命令组合起来的，因此在宏命令对象里面会记录多个组成它的命令对象`第三，既然是包含多个命令对象，得有方法让这多个命令对象能被组合进来

第四，既然宏命令包含了多个命令对象，执行宏命令对象就相当于依次执行这些命令对象，也就是循环执行这些命令对象

看看代码示例会更清晰些，代码示例如下：

```java
/** 
 * 菜单对象，是个宏命令对象 
 */  
public class MenuCommand implements Command {  
    /** 
     * 用来记录组合本菜单的多道菜品，也就是多个命令对象 
     */  
    private Collection<Command> col = new ArrayList<Command>();  
    /** 
     * 点菜，把菜品加入到菜单中 
     * @param cmd 客户点的菜 
     */  
    public void addCommand(Command cmd){  
        col.add(cmd);  
    }  
    public void execute() {  
        //执行菜单其实就是循环执行菜单里面的每个菜  
        for(Command cmd : col){  
            cmd.execute();  
        }  
    }  
}  

``` **`(5）该服务员类重磅登场了，它实现的功能，相当于标准命令模式实现中的Client加上Invoker，前面都是文字讲述，看看代码如何实现，示例代码如下：`** 

```java
/** 
 * 服务员，负责组合菜单，负责组装每个菜和具体的实现者， 
 * 还负责执行调用，相当于标准Command模式的Client+Invoker 
 */  
public class Waiter {  
    /** 
     * 持有一个宏命令对象——菜单 
     */  
    private MenuCommand menuCommand = new MenuCommand();  
    /** 
     * 客户点菜 
     * @param cmd 客户点的菜，每道菜是一个命令对象 
     */  
    public void orderDish(Command cmd){  
        //客户传过来的命令对象是没有和接收者组装的  
        //在这里组装吧  
        CookApi hotCook = new HotCook();  
        CookApi coolCook = new CoolCook();  
        //判读到底是组合凉菜师傅还是热菜师傅  
        //简单点根据命令的原始对象的类型来判断  
        if(cmd instanceof DuckCommand){  
            ((DuckCommand)cmd).setCookApi(hotCook);  
        }else if(cmd instanceof ChopCommand){  
            ((ChopCommand)cmd).setCookApi(hotCook);  
       }else if(cmd instanceof PorkCommand){  
            //这是个凉菜，所以要组合凉菜的师傅  
            ((PorkCommand)cmd).setCookApi(coolCook);  
        }  
        //添加到菜单中  
        menuCommand.addCommand(cmd);  
    }  
    /** 
     * 客户点菜完毕，表示要执行命令了，这里就是执行菜单这个组合命令 
     */  
    public void orderOver(){  
        this.menuCommand.execute();  
    }  
}  

``` **`（6）费了这么大力气，终于可以坐下来歇息一下，点菜吃饭吧，一起来看看客户端怎么使用这个宏命令，其实在客户端非常简单，根本看不出宏命令来，代码示例如下：`** 

```java
public class Client {  
    public static void main(String[] args) {  
        //客户只是负责向服务员点菜就好了  
        //创建服务员  
        Waiter waiter = new Waiter();  
         
        //创建命令对象，就是要点的菜  
        Command chop = new ChopCommand();  
        Command duck = new DuckCommand();  
        Command pork = new PorkCommand();  
         
        //点菜，就是把这些菜让服务员记录下来  
        waiter.orderDish(chop);  
        waiter.orderDish(duck);  
        waiter.orderDish(pork);  
         
        //点菜完毕  
        waiter.orderOver();  
    }  
}  

```

运行一下，享受一下成果，结果如下：

```java
本厨师正在做：绿豆排骨煲
本厨师正在做：北京烤鸭
凉菜蒜泥白肉已经做好，本厨师正在装盘。

```


[0]: ./img/2062729-db34ee0d5604c3f4.png
[1]: ./img/2062729-1ea59db8adac1010.png
[2]: ./img/2062729-247acf0214469b37.png
[3]: ./img/2062729-f09929fd7930a315.png
[4]: ./img/2062729-e2dc620cfca4dd4b.png
[5]: ./img/2062729-43260b723a1b8f25.png
[6]: ./img/2062729-caae228ef113d624.png