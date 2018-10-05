## 【行为型模式十七】命令模式-2（Command）

2016.11.30 19:30*

来源：[https://www.jianshu.com/p/16db20a8267e](https://www.jianshu.com/p/16db20a8267e)


          
## 3.5 队列请求##
`所谓队列请求，就是对命令对象进行排队，组成工作队列，然后依次取出命令对象来执行`。多用多线程或者线程池来进行命令队列的处理，当然也可以不用多线程，就是一个线程，一个命令一个命令的循环处理，就是慢点。

继续宏命令的例子，其实在后厨，会收到很多很多的菜单，一般是按照菜单传递到后厨的先后顺序来进行处理，对每张菜单，假定也是按照菜品的先后顺序进行制作，那么在后厨就自然形成了一个菜品的队列，也就是很多个用户的命令对象的队列。

后厨有很多厨师，每个厨师都从这个命令队列里面取出一个命令，然后按照命令做出菜来，就相当于多个线程在同时处理一个队列请求。

因此后厨就是一个很典型的队列请求的例子。

提示一点：`后厨的厨师与命令队列之间是没有任何关联的，也就是说是完全解耦的`。命令队列是客户发出的命令，厨师只是负责从队列里面取出一个，处理，然后再取下一个，再处理，仅此而已，厨师不知道也不管客户是谁。

* **`如何实现命令模式的队列请求`** 

 **`（1）先从命令接口开始，除了execute方法外，新加了一个返回发出命令的桌号，就是点菜的桌号，还有一个是为命令对象设置接收者的方法，也把它添加到接口上，这个是为了后面多线程处理的时候方便使用。示例代码如下：`** 

```java
/** 
 * 命令接口，声明执行的操作 
 */  
public interface Command {  
    /** 
     * 执行命令对应的操作 
     */  
    public void execute();  
    /** 
     * 设置命令的接收者 
     * @param cookApi 命令的接收者  
     */  
    public void setCookApi(CookApi cookApi);  
    /** 
     * 返回发起请求的桌号，就是点菜的桌号 
     * @return 发起请求的桌号 
     */  
    public int getTableNum();  
}

``` **`（2）厨师的接口也发生了一点变化，在cook的方法上添加了发出命令的桌号，这样在多线程输出信息的时候，才知道到底是在给哪个桌做菜，示例代码如下：`** 

```java
/** 
 * 厨师的接口 
 */  
public interface CookApi {  
    /** 
     * 示意，做菜的方法 
     * @param tableNum 点菜的桌号 
     * @param name 菜名 
     */  
    public void cook(int tableNum,String name);  
}  

```

** (3）开始来实现命令接口，为了简单，这次只有热菜，因为要做工作都在后厨的命令队列里面，因此凉菜就不要了，示例代码如下：**

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
    /** 
     * 点菜的桌号 
     */  
    private int tableNum;  
    /** 
     * 构造方法，传入点菜的桌号 
     * @param tableNum 点菜的桌号 
     */  
    public ChopCommand(int tableNum){  
        this.tableNum = tableNum;  
    }  
    public int getTableNum(){  
        return this.tableNum;  
    }  
    public void execute() {  
        this.cookApi.cook(tableNum,"绿豆排骨煲");  
    }  
}  

``` **`（4）接下来构建很重要的命令对象的队列，其实也不是有多难，多个命令对象嘛，用个集合来存储就好了，然后按照放入的顺序，先进先出即可。`** 

```java
/** 
 * 命令队列类 
 */  
public class CommandQueue {  
    /** 
     * 用来存储命令对象的队列 
     */  
    private static List<Command> cmds = new ArrayList<Command>();  
    /** 
     * 服务员传过来一个新的菜单，需要同步， 
     * 因为同时会有很多的服务员传入菜单，而同时又有很多厨师在从队列里取值 
     * @param menu 传入的菜单 
     */  
    public synchronized static void addMenu(MenuCommand menu){  
        //一个菜单对象包含很多命令对象  
        for(Command cmd : menu.getCommands()){  
            cmds.add(cmd);  
        }  
    }  
    /** 
     * 厨师从命令队列里面获取命令对象进行处理，也是需要同步的 
     */  
    public synchronized static Command getOneCommand(){  
        Command cmd = null;  
        if(cmds.size() > 0 ){  
            //取出队列的第一个，因为是约定的按照加入的先后来处理  
            cmd = cmds.get(0);  
            //同时从队列里面取掉这个命令对象  
            cmds.remove(0);  
        }  
        return cmd;  
    }  
}  

```

提示：这里并没有考虑一些复杂的情况，比如：`如果命令队列里面没有命令，而厨师又来获取命令怎么办？`这里只是做一个基本的示范，并不是完整的实现，所以这里就没有去处理这些问题了，`当然出现这种问题，就需要使用wait/notify来进行线程调度了`。 **`（5）有了命令队列，谁来向这个队列里面传入命令呢？`** 

很明显是服务员，当客户点菜完成，服务员就会执行菜单，现在执行菜单就相当于把菜单直接传递给后厨，也就是要把菜单里的所有命令对象加入到命令队列里面。因此菜单对象的实现需要改变，示例代码如下：

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
    public void setCookApi(CookApi cookApi){  
        //什么都不用做  
    }  
    public int getTableNum(){  
        //什么都不用做  
        return 0;  
    }  
    /** 
     * 获取菜单中的多个命令对象 
     * @return 菜单中的多个命令对象 
     */  
    public Collection<Command> getCommands(){  
        return this.col;  
    }     
 
    public void execute() {  
        //执行菜单就是把菜单传递给后厨  
        CommandQueue.addMenu(this);  
    }  
}  

``` **`（6）现在有了命令队列，也有人负责向队列里面添加命令了，可是谁来执行命令队列里面的命令呢？`** 

答案是：由厨师从命令队列里面获取命令，并真正处理命令，而且厨师在处理命令前会把自己设置到命令对象里面去当接收者，表示这个菜由我来实际做。

厨师对象的实现，大致有如下的改变：

为了更好的体现命令队列的用法，再说实际情况也是多个厨师，这里用多线程来模拟多个厨师，他们自己从命令队列里面获取命令，然后处理命令，然后再获取下一个，如此反复，因此厨师类要实现多线程接口。

还有一个改变，为了在多线程中输出信息，让我们知道是哪一个厨师在执行命令，给厨师添加了一个姓名的属性，通过构造方法传入。

另外一个改变是为了在多线程中看出效果，在厨师真正做菜的方法里面使用随机数模拟了一个做菜的时间。

好了，介绍完了改变的地方，一起看看代码吧，示例代码如下：

```java
/** 
 * 厨师对象，做热菜的厨师 
 */  
public class HotCook implements CookApi,Runnable{  
    /** 
     * 厨师姓名 
     */  
    private String name;  
    /** 
     * 构造方法，传入厨师姓名 
     * @param name 厨师姓名 
     */  
    public HotCook(String name){  
        this.name = name;  
    }     
    public void cook(int tableNum,String name) {  
        //每次做菜的时间是不一定的，用个随机数来模拟一下  
        int cookTime = (int)(20 * Math.random());  
        System.out.println(this.name+"厨师正在为"+tableNum+"号桌做："+name);  
        try {  
            //让线程休息这么长时间，表示正在做菜  
            Thread.sleep(cookTime);  
        } catch (InterruptedException e) {  
            e.printStackTrace();  
        }  
        System.out.println(this.name+"厨师为"+tableNum+"号桌做好了："+name+",共计耗时="+cookTime+"秒");  
    }  
    public void run() {  
        while(true){  
            //到命令队列里面获取命令对象  
            Command cmd = CommandQueue.getOneCommand();  
            if(cmd != null){  
                //说明取到命令对象了，这个命令对象还没有设置接收者  
                //因为前面都还不知道到底哪一个厨师来真正执行这个命令  
                //现在知道了，就是当前厨师实例，设置到命令对象里面  
                cmd.setCookApi(this);  
                //然后真正执行这个命令  
                cmd.execute();  
            }  
            //休息1秒  
            try {  
                Thread.sleep(1000L);  
            } catch (InterruptedException e) {  
                e.printStackTrace();  
            }  
        }  
    }  
} 

``` **`(7）该来看看服务员类了，由于现在考虑了后厨的管理，因此从实际来看，这次服务员也不知道到底命令的真正接收者是谁了，也就是说服务员也不知道某个菜到底最后由哪一位厨师完成，所以服务员类就简单了。`** 

组装命令对象和接收者的功能后移到厨师类的线程里面了，当某个厨师从命令队列里面获取一个命令对象的时候，这个厨师就是这个命令的真正接收者。

```java
/** 
 * 服务员，负责组合菜单,还负责执行调用 
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

``` **`（8）在见到曙光之前，还有一个问题要解决，就是谁来启动多线程的厨师呢？`** 

为了实现后厨的管理，`为此专门定义一个后厨管理的类，在这个类里面去启动多个厨师的线程`。而且这种启动在运行期间应该只有一次。示例代码如下：

```java
/** 
 * 后厨的管理类，通过此类让后厨的厨师进行运行状态 
 */  
public class CookManager {  
    /** 
     * 用来控制是否需要创建厨师，如果已经创建过了就不要再执行了 
     */  
    private static boolean runFlag = false;  
    /** 
     * 运行厨师管理，创建厨师对象并启动他们相应的线程， 
     * 无论运行多少次，创建厨师对象和启动线程的工作就只做一次 
     */  
    public static void runCookManager(){  
        if(!runFlag){  
            runFlag = true;  
            //创建三位厨师  
            HotCook cook1 = new HotCook("张三");  
            HotCook cook2 = new HotCook("李四");  
            HotCook cook3 = new HotCook("王五");  
 
            //启动他们的线程  
            Thread t1 = new Thread(cook1);  
            t1.start();  
            Thread t2 = new Thread(cook2);  
            t2.start();  
            Thread t3 = new Thread(cook3);  
            t3.start();  
        }  
    }  
}  

``` **`（9）曙光来临了，写个客户端测试测试，示例代码如下：`** 

```java
public class Client {  
    public static void main(String[] args) {  
        //先要启动后台，让整个程序运行起来  
        CookManager.runCookManager();  
          
        //为了简单，直接用循环模拟多个桌号点菜  
        for(int i = 0;i<5;i++){  
            //创建服务员  
            Waiter waiter = new Waiter();  
            //创建命令对象，就是要点的菜  
            Command chop = new ChopCommand(i);  
            Command duck = new DuckCommand(i);  
 
            //点菜，就是把这些菜让服务员记录下来  
            waiter.orderDish(chop);  
            waiter.orderDish(duck);  
 
            //点菜完毕  
            waiter.orderOver();  
        }         
    }  
} 

``` **`（10）运行一下，看看效果，可能每次运行的效果不一样，毕竟是使用多线程在处理请求队列，某次运行的结果如下：`** 


![][0]


Paste_Image.png


好好观察上面的数据，`在多线程环境下，虽然保障了命令对象取出的顺序是先进先出，但是究竟是哪一个厨师来做，还有具体做多长时间都是不定的`。
## 3.7 命令模式的优缺点##

* **`更松散的耦合`** 


命令模式使得发起命令的对象——客户端，和具体实现命令的对象——接收者对象完全解耦，也就是说发起命令的对象，完全不知道具体实现对象是谁，也不知道如何实现。

* **`更动态的控制`** 


命令模式把请求封装起来，可以动态对它进行参数化、队列化和日志化等操作，从而使得系统更灵活。

* **`能很自然的复合命令`** 


命令模式中的命令对象，能够很容易的组合成为复合命令，就是前面讲的宏命令，从而使系统操作更简单，功能更强大。

* **`更好的扩展性`** 


由于发起命令的对象和具体的实现完全解耦，因此扩展新的命令就很容易，只需要实现新的命令对象，然后在装配的时候，把具体的实现对象设置到命令对象里面，然后就可以使用这个命令对象，已有的实现完全不用变化。
## 3.8 思考命令模式##

* **`命令模式的本质`** 

`命令模式的本质：封装请求。`前面讲了，`命令模式的关键就是把请求封装成为命令对象，然后就可以对这个对象进行一系列的处理了`，比如上面讲到的参数化配置、可撤销操作、宏命令、队列请求、日志请求等功能处理。

* **`何时选用命令模式`** 


建议在如下情况中，选用命令模式：

 **`如果需要抽象出需要执行的动作，并参数化这些对象`** ，可以选用命令模式，把这些需要执行的动作抽象成为命令，然后实现命令的参数化配置 **`如果需要在不同的时刻指定、排列和执行请求`** ，可以选用命令模式，把这些请求封装成为命令对象，然后实现把请求队列化 **`如果需要支持取消操作`** ，可以选用命令模式，通过管理命令对象，能很容易的实现命令的恢复和重做的功能 **`如果需要支持当系统崩溃时，能把对系统的操作功能重新执行一遍`** ，可以选用命令模式，把这些操作功能的请求封装成命令对象，然后实现日志命令，就可以在系统恢复回来后，通过日志获取命令列表，从而重新执行一遍功能 **`在需要事务的系统中`** ，可以选用命令模式，命令模式提供了对事务进行建模的方法，命令模式有一个别名就是Transaction。

## 3.9 退化的命令模式##

在领会了命令模式本质后，来思考一个命令模式退化的情况。

前面讲到了智能命令，`如果命令的实现对象超级智能，实现了命令所要求的功能，那么就不需要接收者了，既然没有了接收者，那么也就不需要组装者了`。

* **`举个最简单的示例来说明`** 


比如现在要实现一个打印服务，由于非常简单，所以基本上就没有什么讲述，依次来看，命令接口定义如下：

```java
public interface Command {  
    public void execute();  
}  

```

命令的实现示例代码如下：

```java
public class PrintService implements Command{  
    /** 
     * 要输出的内容 
     */  
    private String str = "";  
    /** 
     * 构造方法，传入要输出的内容 
     * @param s 要输出的内容 
     */  
    public PrintService(String s){  
        str = s;  
    }  
    public void execute() {  
        //智能的体现，自己知道怎么实现命令所要求的功能，并真的实现了相应的功能，不再转调接收者了  
        System.out.println("打印的内容为="+str);  
    }  
}  

```

此时的Invoker示例代码如下：

```java
public class Invoker {  
    /** 
     * 持有命令对象 
     */  
    private Command cmd = null;  
    /** 
     * 设置命令对象 
     * @param cmd 命令对象 
     */  
    public void setCmd(Command cmd){  
        this.cmd = cmd;  
    }  
    /** 
     * 开始打印 
     */  
    public void startPrint(){  
        //执行命令的功能  
        this.cmd.execute();  
    }  
}  

```

最后看看客户端的代码，示例如下：

```java
public class Client {  
    public static void main(String[] args) {  
        //准备要发出的命令  
        Command cmd = new PrintService("退化的命令模式示例");  
        //设置命令给持有者  
        Invoker invoker = new Invoker();  
        invoker.setCmd(cmd);      
 
        //按下按钮，真正启动执行命令  
        invoker.startPrint();  
    }  
}  

```

测试结果如下：

```java
打印的内容为=退化的命令模式示例

```

* **`继续变化`** 


如果此时继续变化，Invoker也开始变得智能化，`在Invoker的startPrint方法里面，Invoker加入了一些实现，同时Invoker对持有命令也有意见，觉得自己是个傀儡，要求改变一下，直接在调用方法的时候传递命令对象进来`，示例代码如下：

```java
public class Invoker {  
    public void startPrint(Command cmd){      
        System.out.println("在Invoker中，输出服务前");  
        cmd.execute();  
        System.out.println("输出服务结束");  
    }  
}  

```

看起来Invoker退化成一个方法了。

这个时候Invoker很高兴，宣称自己是一个智能的服务，不再是一个傻傻的转调者，而是有自己功能的服务了。`这个时候Invoker调用命令对象的执行方法，也不叫转调，改名叫“回调”，意思是在我Invoker需要的时候，会回调你命令对象，命令对象你就乖乖的写好实现，等我“回调”你就可以了`。
`事实上这个时候的命令模式的实现，基本上就等同于Java回调机制的实现，可能有些朋友看起来感觉还不是佷像，那是因为在Java回调机制的常见实现上，经常没有单独的接口实现类，而是采用匿名内部类的方式来实现的`。

* **`再进一步`** 

`把单独实现命令接口的类改成用匿名内部类实现，这个时候就只剩下命令的接口、Invoker类，还有客户端了`。

为了使用匿名内部类，还要设置要输出的值，对命令接口做点小改动，增加一个设置输出值的方法，示例代码如下：

```java
public interface Command {  
    public void execute();  
    /** 
     * 设置要输出的内容 
     * @param s 要输出的内容 
     */  
    public void setStr(String s);  
}  

```

此时Invoker就是上面那个，而客户端会有些改变，客户端的示例代码如下：

```java
public class Client {  
    public static void main(String[] args) {  
        //准备要发出的命令，没有具体实现类了  
        //匿名内部类来实现命令   
        Command cmd = new Command() {  
            private String str = "";  
            public void setStr(String s) {  
                str = s;  
            }  
            public void execute() {  
                System.out.println("打印的内容为="+str);  
            }  
        };
        cmd.setStr("退化的命令模式类似于Java回调的示例");        
        //这个时候的Invoker或许该称为服务了  
        Invoker invoker = new Invoker();  
        //按下按钮，真正启动执行命令  
        invoker.startPrint(cmd);  
    }  
}  

```

运行测试一下，结果如下：

```java
在Invoker中，输出服务前  
打印的内容为=退化的命令模式类似于Java回调的示例  
输出服务结束  

```

* **`现在是不是看出来了，`这个时候的命令模式的实现，基本上就等同于Java回调机制的实现`。这也是很多人大谈特谈命令模式可以实现Java回调的意思。`** 


当然更狠的是连Invoker也不要了，直接把那个方法搬到Client中，那样测试起来就更方便了。在实际开发中，应用命令模式来实现回调机制的时候，Invoker通常还是有的，但可以智能化实现，更准确的说Invoker充当客户调用的服务实现，而回调的方法只是实现服务功能中的一个或者几个步骤。
## 3.10 相关模式##

* **`命令模式和组合模式`** 


这两个模式可以组合使用。
`在命令模式中，实现宏命令的功能，就可以使用组合模式来实现`。前面的示例并没有按照组合模式来做，那是为了保持示例的简单，还有突出命令模式的实现，这点请注意。

* **`命令模式和备忘录模式`** 


这两个模式可以组合使用。

在命令模式中，实现可撤销操作功能时，前面讲了有两种实现方式，`其中有一种就是保存命令执行前的状态，撤销的时候就把状态恢复回去`。如果采用这种方式实现，就可以考虑使用备忘录模式。

如果状态存储在命令对象里面，那么还可以使用原型模式，把命令对象当作原型来克隆一个新的对象，然后把克隆出来的对象通过备忘录模式存放。

* **`命令模式和模板方法模式`** 


这两个模式从某种意义上有相似的功能，`命令模式可以作为模板方法的一种替代模式，也就是说命令模式可以模仿实现模板方法模式的功能`。

如同前面讲述的退化的命令模式可以实现Java的回调，而Invoker智能化后向服务进化，如果Invoker的方法就是一个算法骨架，其中有两步在这个骨架里面没有具体实现，需要外部来实现，这个时候就可以通过回调命令接口来实现。

而类似的功能在模板方法里面，一个算法骨架，其中有两步在这个骨架里面没有具体实现，是先调用抽象方法，然后等待子类来实现。

可以看出虽然实现方式不一样，但是可以实现相同的功能。


[0]: ./img/2062729-a2d4ad7dcc12f91e.png