## 【行为型模式二十四】备忘录模式（Memento）

2016.12.08 14:14*

来源：[https://www.jianshu.com/p/714dc05feb12](https://www.jianshu.com/p/714dc05feb12)


          
## 1 场景问题#
## 1.1 开发仿真系统##

考虑这样一个仿真应用，功能是：模拟运行针对某个具体问题的多个解决方案，记录运行过程的各种数据，在模拟运行完成过后，好对这多个解决方案进行比较和评价，从而选定最优的解决方案。

这种仿真系统，在很多领域都有应用，比如：工作流系统，对同一问题制定多个流程，然后通过仿真运行，最后来确定最优的流程做为解决方案；在工业设计和制造领域，仿真系统的应用就更广泛了。

由于都是解决同一个具体的问题，这多个解决方案并不是完全不一样的，假定它们的前半部分运行是完全一样的，只是在后半部分采用了不同的解决方案，后半部分需要使用前半部分运行所产生的数据。

由于要模拟运行多个解决方案，而且最后要根据运行结果来进行评价，`这就意味着每个方案的后半部分的初始数据应该是一样，也就是说在运行每个方案后半部分之前，要保证数据都是由前半部分运行所产生的数据`，当然，咱们这里并不具体的去深入到底有哪些解决方案，也不去深入到底有哪些状态数据，这里只是示意一下。

那么，这样的系统该如何实现呢？尤其是每个方案运行需要的初始数据应该一样，要如何来保证呢？
## 1.2 不用模式的解决方案##

要保证初始数据的一致，实现思路也很简单：

首先模拟运行流程第一个阶段，得到后阶段各个方案运行需要的数据，并把数据保存下来，以备后用；

每次在模拟运行某一个方案之前，用保存的数据去重新设置模拟运行流程的对象，这样运行后面不同的方案时，对于这些方案，初始数据就是一样的了；

根据上面的思路，来写出仿真运行的示意代码，示例代码如下：

```java
/**
 * 模拟运行流程A，只是一个示意，代指某个具体流程
 */
public class FlowAMock {
    /**
     * 流程名称，不需要外部存储的状态数据
     */
    private String flowName;
    /**
     * 示意，代指某个中间结果，需要外部存储的状态数据
     */
    private int tempResult;
    /**
     * 示意，代指某个中间结果，需要外部存储的状态数据
     */
    private String tempState;
    /**
     * 构造方法，传入流程名称
     * @param flowName 流程名称
     */
    public FlowAMock(String flowName){
       this.flowName = flowName;
    }
   
    public String getTempState() {
       return tempState;
    }
    public void setTempState(String tempState) {
       this.tempState = tempState;
    }
    public int getTempResult() {
       return tempResult;
    }
    public void setTempResult(int tempResult) {
       this.tempResult = tempResult;
    }
   
    /**
     * 示意，运行流程的第一个阶段
     */
    public void runPhaseOne(){
       //在这个阶段，可能产生了中间结果，示意一下
       tempResult = 3;
       tempState = "PhaseOne";
    }
    /**
     * 示意，按照方案一来运行流程后半部分
     */
    public void schema1(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema1";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 11;
    }
    /**
     * 示意，按照方案二来运行流程后半部分
     */
    public void schema2(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema2";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 22;
    }  
}

```

看看如何使用这个模拟流程的对象，写个客户端来测试一下。示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        // 创建模拟运行流程的对象
        FlowAMock mock = new FlowAMock("TestFlow");
        //运行流程的第一个阶段
        mock.runPhaseOne();
        //得到第一个阶段运行所产生的数据，后面要用
        int tempResult = mock.getTempResult();
        String tempState = mock.getTempState();
      
        //按照方案一来运行流程后半部分
        mock.schema1();
      
        //把第一个阶段运行所产生的数据重新设置回去
        mock.setTempResult(tempResult);
        mock.setTempState(tempState);
      
        //按照方案二来运行流程后半部分
        mock.schema2();
    }
}

```

运行结果如下：

```java
PhaseOne,Schema1 : now run 3
PhaseOne,Schema2 : now run 3

```

仔细看，上面结果中框住的部分，是一样的值，这说明运行时，它们的初始数据是一样的，基本满足了功能要求。
## 1.3 有何问题##

看起来实现很简单，是吧，想一想有没有什么问题呢？

上面的实现有一个不太好的地方，`那就是数据是一个一个零散着在外部存放的，如果需要外部存放的数据多了，会显得很杂乱`。这个好解决，只需要定义一个数据对象来封装这些需要外部存放的数据就可以了，上面那样做是故意的，好提醒大家这个问题。这个就不去示例了。

还有一个严重的问题，那就是：`为了把运行期间的数据放到外部存储起来，模拟流程的对象被迫把内部数据结构开放出来，这暴露了对象的实现细节，而且也破坏了对象的封装性`。本来这些数据只是模拟流程的对象内部数据，应该是不对外的。

那么究竟如何实现这样的功能会比较好呢？
## 2 解决方案#
## 2.1 备忘录模式来解决##

来解决上述问题的一个合理的解决方案就是备忘录模式。那么什么是备忘录模式呢？

* **`备忘录模式定义`** 



![][0]


备忘录模式定义


一个备忘录是一个对象，它存储另一个对象在某个瞬间的内部状态，后者被称为备忘录的原发器。

* **`应用备忘录模式来解决的思路`** 


仔细分析上面的示例功能，`需要在运行期间捕获模拟流程运行的对象的内部状态，这些需要捕获的内部状态就是它运行第一个阶段产生的内部数据，并且在该对象之外来保存这些状态，因为在后面它有不同的运行方案`。但是这些不同的运行方案需要的初始数据是一样的，都是流程在第一个阶段运行所产生的数据，`这就要求运行每个方案后半部分前，要把该对象的状态恢复回到第一个阶段运行结束时候的状态`。

在这个示例中出现的、需要解决的问题就是：`如何能够在不破坏对象的封装性的前提下，来保存和恢复对象的状态`。

看起来跟备忘录模式要解决的问题是如此的贴切，简直备忘录模式像是专为这个应用打造的一样。那么使用备忘录模式如何来解决这个问题呢？
`备忘录模式引入一个存储状态的备忘录对象，为了让外部无法访问这个对象的值，一般把这个对象实现成为需要保存数据的对象的内部类，通常还是私有的，这样一来，除了这个需要保存数据的对象，外部无法访问到这个备忘录对象的数据，这就保证了对象的封装性不被破坏`。
`但是这个备忘录对象需要存储在外部，为了避免让外部访问到这个对象内部的数据，备忘录模式引入了一个备忘录对象的窄接口，这个接口一般是空的，什么方法都没有，这样外部存储的地方，只是知道存储了一些备忘录接口的对象，但是由于接口是空的，它们无法通过接口去访问备忘录对象内的数据`。
## 2.2 模式结构和说明##

备忘录模式结构如图所示：


![][1]


备忘录模式结构如图


Memento：`备忘录。主要用来存储原发器对象的内部状态，但是具体需要存储哪些数据是由原发器对象来决定的`。另外备忘录应该只能由原发器对象来访问它内部的数据，原发器外部的对象不应该能访问到备忘录对象的内部数据。

Originator：原发器。`使用备忘录来保存某个时刻原发器自身的状态，也可以使用备忘录来恢复内部状态`。

Caretaker：备忘录管理者，或者称为备忘录负责人。`主要负责保存备忘录对象，但是不能对备忘录对象的内容进行操作或检查`。

## 2.3 备忘录模式示例代码##

* **`先看看备忘录对象的窄接口，就是那个Memento接口，这个实现最简单，是个空的接口，没有任何方法定义，示例代码如下：`** 


```java
/**
 * 备忘录的窄接口，没有任何方法定义
 */
public interface Memento {
    //
}

```

* **`看看原发器对象，它里面会有备忘录对象的实现，因为真正的备忘录对象当作原发器对象的一个私有内部类来实现了。示例代码如下：`** 


```java
/**
 * 原发器对象
 */
public class Originator {
    /**
     * 示意，表示原发器的状态
     */
    private String state = "";
    /**
     * 创建保存原发器对象的状态的备忘录对象
     * @return 创建好的备忘录对象
     */
    public Memento createMemento() {
       return new MementoImpl(state);
    }
    /**
     * 重新设置原发器对象的状态，让其回到备忘录对象记录的状态
     * @param memento 记录有原发器状态的备忘录对象
     */
    public void setMemento(Memento memento) {
       MementoImpl mementoImpl = (MementoImpl)memento;
       this.state = mementoImpl.getState();
    }
    /**
     * 真正的备忘录对象，实现备忘录窄接口
     * 实现成私有的内部类，不让外部访问
     */
    private static class MementoImpl implements Memento{
       /**
        * 示意，表示需要保存的状态
        */
       private String state = "";
       public MementoImpl(String state){
           this.state = state;
       }
       public String getState() {
           return state;
       }
    }
}

```

* **`接下来看看备忘录管理者对象，示例代码如下：`** 


```java
/**
 * 负责保存备忘录的对象
 */
public class Caretaker{
    /**
     * 记录被保存的备忘录对象
     */
    private Memento memento = null;
    /**
     * 保存备忘录对象
     * @param memento 被保存的备忘录对象
     */
    public void saveMemento(Memento memento){
       this.memento = memento;
    }
    /**
     * 获取被保存的备忘录对象
     * @return 被保存的备忘录对象
     */
    public Memento retriveMemento(){
       return this.memento;
    }
}

```
## 2.4 使用备忘录模式重写示例##

学习了备忘录模式的基本知识过后，来尝试一下，使用备忘录模式把前面的示例重写一下，好看看如何使用备忘录模式。

首先，那个模拟流程运行的对象，就相当于备忘录模式中的原发器；

而它要保存的数据，原来是零散的，现在做一个备忘录对象来存储这些数据，并且把这个备忘录对象实现成为内部类；

当然为了保存这个备忘录对象，还是需要提供管理者对象的；

`为了和管理者对象交互，管理者需要知道保存对象的类型，那就提供一个备忘录对象的窄接口来供管理者使用，相当于标识了类型`。

此时程序的结构如图所示：


![][2]


使用备忘录模式重写示例的结构示意图


* **`先来看看备忘录对象的窄接口吧，示例代码如下：`** 


```java
/**
 * 模拟运行流程A的对象的备忘录接口，是个窄接口
 */
public interface FlowAMockMemento {
    //空的
}

```

* **`再来看看新的模拟运行流程A的对象，相当于原发器对象了，它的变化比较多，大致有如下变化：`** 


首先这个对象原来暴露出去的内部状态，不用再暴露出去了，也就是内部状态不用再对外提供getter/setter方法了；

在这个对象里面提供一个私有的备忘录对象，里面封装想要保存的内部状态，同时让这个备忘录对象实现备忘录对象的窄接口；

在这个对象里面提供创建备忘录对象，和根据备忘录对象恢复内部状态的方法；

具体的示例代码如下：

```java
/**
 * 模拟运行流程A，只是一个示意，代指某个具体流程
 */
public class FlowAMock {
    /**
     * 流程名称，不需要外部存储的状态数据
     */
    private String flowName;
    /**
     * 示意，代指某个中间结果，需要外部存储的状态数据
     */
    private int tempResult;
    /**
     * 示意，代指某个中间结果，需要外部存储的状态数据
     */
    private String tempState;
    /**
     * 构造方法，传入流程名称
     * @param flowName 流程名称
     */
    public FlowAMock(String flowName){
       this.flowName = flowName;
    }
    /**
     * 示意，运行流程的第一个阶段
     */
    public void runPhaseOne(){
       //在这个阶段，可能产生了中间结果，示意一下
       tempResult = 3;
       tempState = "PhaseOne";
    }
    /**
     * 示意，按照方案一来运行流程后半部分
     */
    public void schema1(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema1";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 11;
    }
    /**
     * 示意，按照方案二来运行流程后半部分
     */
    public void schema2(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema2";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 22;
    }  
    /**
     * 创建保存原发器对象的状态的备忘录对象
     * @return 创建好的备忘录对象
     */
    public FlowAMockMemento createMemento() {
       return new MementoImpl(this.tempResult,this.tempState);
    }
    /**
     * 重新设置原发器对象的状态，让其回到备忘录对象记录的状态
     * @param memento 记录有原发器状态的备忘录对象
     */
    public void setMemento(FlowAMockMemento memento) {
       MementoImpl mementoImpl = (MementoImpl)memento;
       this.tempResult = mementoImpl.getTempResult();
       this.tempState = mementoImpl.getTempState();
    }
    /**
     * 真正的备忘录对象，实现备忘录窄接口
     * 实现成私有的内部类，不让外部访问
     */
    private static class MementoImpl implements FlowAMockMemento{
       /**
        * 示意，保存某个中间结果
        */
       private int tempResult;
       /**
        * 示意，保存某个中间结果
        */
       private String tempState;
       public MementoImpl(int tempResult,String tempState){
           this.tempResult = tempResult;
           this.tempState = tempState;
       }
       public int getTempResult() {
           return tempResult;
       }
       public String getTempState() {
           return tempState;
       }
    }
}

```

* **`接下来要来实现提供保存备忘录对象的管理者了，示例代码如下：`** 


```java
/**
 * 负责保存模拟运行流程A的对象的备忘录对象
 */
public class FlowAMementoCareTaker {
    /**
     * 记录被保存的备忘录对象
     */
    private FlowAMockMemento memento = null;
    /**
     * 保存备忘录对象
     * @param memento 被保存的备忘录对象
     */
    public void saveMemento(FlowAMockMemento memento){
       this.memento = memento;
    }
    /**
     * 获取被保存的备忘录对象
     * @return 被保存的备忘录对象
     */
    public FlowAMockMemento retriveMemento(){
       return this.memento;
    }
}

```

* **`最后来看看，如何使用上面按照备忘录模式实现的这些对象呢，写个新的客户端来测试一下，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
       // 创建模拟运行流程的对象
       FlowAMock mock = new FlowAMock("TestFlow");
       //运行流程的第一个阶段
       mock.runPhaseOne();     
       //创建一个管理者
       FlowAMementoCareTaker careTaker = new FlowAMementoCareTaker();
       //创建此时对象的备忘录对象，并保存到管理者对象那里，后面要用
       FlowAMockMemento memento = mock.createMemento();
       careTaker.saveMemento(memento);
     
       //按照方案一来运行流程后半部分
       mock.schema1();
     
       //从管理者获取备忘录对象，然后设置回去，
       //让模拟运行流程的对象自己恢复自己的内部状态
       mock.setMemento(careTaker.retriveMemento());
     
       //按照方案二来运行流程后半部分
       mock.schema2();
    }
}

```

运行结果跟前面的示例是一样的，结果如下：

```java
PhaseOne,Schema1 : now run 3
PhaseOne,Schema2 : now run 3

```

好好体会一下上面的示例，`由于备忘录对象是一个私有的内部类，外面只能通过备忘录对象的窄接口来获取备忘录对象，而这个接口没有任何方法，仅仅起到了一个标识对象类型的作用，从而保证内部的数据不会被外部获取或是操作，保证了原发器对象的封装性，也就不再暴露原发器对象的内部结构了`。
## 3 模式讲解#
## 3.1 认识备忘录模式##

* **`备忘录模式的功能`** 


备忘录模式的功能，`首先是在不破坏封装性的前提下，捕获一个对象的内部状`态。这里要注意两点，`一个是不破坏封装性，也就是对象不能暴露它不应该暴露的细节`；另外`一个是捕获的是对象的内部状态，而且通常还是运行期间某个时刻，对象的内部状态`。 **`为什么要捕获这个对象的内部状态呢？捕获这个内部状态有什么用呢？`** 
`是要在以后的某个时候，将该对象的状态恢复到备忘录所保存的状态，这才是备忘录真正的目的`，前面保存状态就是为了后面恢复，虽然不是一定要恢复，但是目的是为了恢复。这也是很多人理解备忘录模式的时候，忽视掉的地方，他们太关注备忘，而忽视了恢复，这是不全面的理解。 **`捕获的状态存放在哪里呢？`** 

备忘录模式中，`捕获的内部状态，存储在备忘录对象中`；`而备忘录对象，通常会被存储在原发器对象之外`，也就是被保存状态的对象的外部，通常是存放在管理者对象哪里。

* **`备忘录对象`** 


在备忘录模式中，`备忘录对象，通常就是用来记录原发器需要保存的状态的对象`，简单点的实现，也就是个封装数据的对象。

但是这个备忘录对象和普通的封装数据的对象还是有区别的，主要就是这个备忘录对象，`一般只让原发器对象来操作，而不是像普通的封装数据的对象那样，谁都可以使用`。为了保证这一点，`通常会把备忘录对象作为原发器对象的内部类来实现，而且会实现成私有的，这就断绝了外部来访问这个备忘录对象的途径`。

但是备忘录对象需要保存在原发器对象之外，`为了与外部交互，通常备忘录对象都会实现一个窄接口，来标识对象的类型`。

* **`原发器对象`** 

`原发器对象，就是需要被保存状态的对象，也是有可能需要恢复状态的对象`。`原发器一般会包含备忘录对象的实现`。
`通常原发器对象应该提供捕获某个时刻对象内部状态的方法`，在这个方法里面，原发器对象会创建备忘录对象，把需要保存的状态数据设置到备忘录对象中，然后把备忘录对象提供给管理者对象来保存。

当然，原发器对象也应该提供这样的方法：`按照外部要求来恢复内部状态到某个备忘录对象记录的状态`。

* **`管理者对象`** 


在备忘录模式中，`管理者对象，主要是负责保存备忘录对象`，这里有几点要讲一下。
`并不一定要特别的做出一个管理者对象来`，广义地说，`调用原发器获得备忘录对象后，备忘录对象放在哪里，哪个对象就可以算是管理者对象`。
`管理者对象并不是只能管理一个备忘录对象，一个管理者对象可以管理很多的备忘录对象`，虽然前面的示例中是保存一个备忘录对象，别忘了那只是个示意，并不是只能实现成那样。
`狭义的管理者对象，是只管理同一类的备忘录对象，但是广义管理者对象是可以管理不同类型的备忘录对象的`。

管理者对象需要实现的基本功能主要就是：`存入备忘录对象、保存备忘录对象、获取备忘录对象`，如果从功能上看，`就是一个缓存功能的实现，或者是一个简单的对象实例池的实现`。
`管理者虽然能存取备忘录对象，但是不能访问备忘录对象内部的数据`。

* **`窄接口和宽接口`** 


在备忘录模式中，为了控制对备忘录对象的访问，出现了窄接口和宽接口的概念。

窄接口：管理者只能看到备忘录的窄接口，`窄接口的实现里面通常没有任何的方法，只是一个类型标识`，窄接口使得管理者只能将备忘录传递给其它对象。

宽接口：`原发器能够看到一个宽接口，允许它访问所需的所有数据，来返回到先前的状态`。理想状况是：只允许生成备忘录的原发器来访问该备忘录的内部状态，通常实现成为原发器内的一个私有内部类。

在前面的示例中，定义了一个名称为FlowAMockMemento的接口，里面没有定义任何方法，然后让备忘录来实现这个接口，从而标识备忘录就是这么一个FlowAMockMemento的类型，`这个接口就是窄接口`。

在前面的实现中，备忘录对象是实现在原发器内的一个私有内部类，只有原发器对象能访问它，原发器可以访问到备忘录对象所有的内部状态，`这就是宽接口`。

这也算是备忘录模式的标准实现方式，`那就是窄接口没有任何的方法，把备忘录对象实现成为原发器对象的私有内部类`。

那么能不能在窄接口里面提供备忘录对象对外的方法，变相对外提供一个“宽”点的接口呢？

通常情况是不会这么做的，因为这样一来，`所有能拿到这个接口的对象就可以通过这个接口来访问备忘录内部的数据或是功能，这违反了备忘录模式的初衷，备忘录模式要求“在不破坏封装性的前提下”，如果这么做，那就等于是暴露了内部细节`，因此，备忘录模式在实现的时候，对外多是采用窄接口，而且通常不会定义任何方法。

* **`使用备忘录的潜在代价`** 

`标准的备忘录模式的实现机制是依靠缓存来实现的`，因此，当需要备忘的数据量较大时，或者是存储的备忘录对象数据量不大但是数量很多的时候，或者是用户很频繁的创建备忘录对象的时候，这些都会导致非常大的开销。

因此在使用备忘录模式的时候，一定要好好思考应用的环境，如果使用的代价太高，就不要选用备忘录模式，可以采用其它的替代方案。

* **`增量存储`** 


如果需要频繁的创建备忘录对象，而且创建和应用备忘录对象来恢复状态的顺序是可控的，那么可以让备忘录进行增量存储，`也就是备忘录可以仅仅存储原发器内部相对于上一次存储状态后的增量改变`。

比如：在命令模式实现可撤销命令的实现中，就可以使用备忘录来保存每个命令对应的状态，然后在撤销命令的时候，使用备忘录来恢复这些状态。`由于命令的历史列表是按照命令操作的顺序来存放的，也是按照这个历史列表来进行取消和重做的，因此顺序是可控的`。那么这种情况，还可以让备忘录对象只存储一个命令所产生的增量改变而不是它所影响的每一个对象的完整状态。

* **`备忘录模式调用顺序示意图`** 


在使用备忘录模式的时候，分成了两个阶段，`第一个阶段是创建备忘录对象的阶段，第二个阶段是使用备忘录对象来恢复原发器对象的状态的阶段`。它们的调用顺序是不一样的，下面分开用图来示意一下。

先看创建备忘录对象的阶段，调用顺序如图所示：


![][3]


创建备忘录对象的调用顺序示意图


再看看使用备忘录对象来恢复原发器对象的状态的阶段，调用顺序如图所示：


![][4]


使用备忘录对象来恢复原发器对象的状态的调用顺序示意图

## 3.2 结合原型模式##

在原发器对象创建备忘录对象的时候，`如果原发器对象中全部或者大部分的状态都需要保存，一个简洁的方式就是直接克隆一个原发器对象`。也就是说，`这个时候备忘录对象里面存放的是一个原发器对象的实例`。

还是通过示例来说明。只需要修改原发器对象就可以了，大致有如下变化：

首先原发器对象要实现可克隆的，好在这个原发器对象的状态数据都很简单，都是基本数据类型，所以直接用默认的克隆方法就可以了，不用自己实现克隆，更不涉及深度克隆，否则，正确实现深度克隆还是个问题；

备忘录对象的实现要修改，只需要存储原发器对象克隆出来的实例对象就可以了；

相应的创建和设置备忘录对象的地方都要做修改；

示例代码如下：

```java
/**
 * 模拟运行流程A，只是一个示意，代指某个具体流程
 */
public class FlowAMockPrototype implements Cloneable {
    private String flowName;
    private int tempResult;
    private String tempState;
    public FlowAMockPrototype(String flowName){
       this.flowName = flowName;
    }
   
    public void runPhaseOne(){
       //在这个阶段，可能产生了中间结果，示意一下
       tempResult = 3;
       tempState = "PhaseOne";
    }
    public void schema1(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema1";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 11;
    }
   
    public void schema2(){
       //示意，需要使用第一个阶段产生的数据
       this.tempState += ",Schema2";
       System.out.println(this.tempState + " : now run "+tempResult);
       this.tempResult += 22;
    }  
    /**
     * 创建保存原发器对象的状态的备忘录对象
     * @return 创建好的备忘录对象
     */
    public FlowAMockMemento createMemento() {
       try {
           return new MementoImplPrototype((FlowAMockPrototype) this.clone());
       } catch (CloneNotSupportedException e) {
           e.printStackTrace();
       }
       return null;
    }
    /**
     * 重新设置原发器对象的状态，让其回到备忘录对象记录的状态
     * @param memento 记录有原发器状态的备忘录对象
     */
    public void setMemento(FlowAMockMemento memento) {
       MementoImplPrototype mementoImpl = (MementoImplPrototype)memento;
       this.tempResult = mementoImpl.getFlowAMock().tempResult;
       this.tempState = mementoImpl.getFlowAMock().tempState;
    }
    /**
     * 真正的备忘录对象，实现备忘录窄接口，实现成私有的内部类，不让外部访问
     */
    private static class MementoImplPrototype implements FlowAMockMemento{
       private FlowAMockPrototype flowAMock = null;
      
       public MementoImplPrototype(FlowAMockPrototype f){
           this.flowAMock = f;
       }
 
       public FlowAMockPrototype getFlowAMock() {
           return flowAMock;
       }
    }
}

```

好了，结合原型模式来实现备忘录模式的示例就写好了，在前面的客户测试程序中，创建原发器对象的时候，使用这个新实现的原发器对象就可以了。去测试和体会一下，看看是否能正确实现需要的功能。

不过要注意一点，`就是如果克隆对象非常复杂，或者需要很多层次的深度克隆，实现克隆的时候会比较麻烦`。
## 3.3 离线存储##

标准的备忘录模式，没有讨论离线存储的实现。

事实上，`从备忘录模式的功能和实现上，是可以把备忘录的数据实现成为离线存储的，也就是不仅限于存储于内存中，可以把这些备忘数据存储到文件中、xml中、数据库中，从而支持跨越会话的备份和恢复功能`。

离线存储甚至能帮助应对应用崩溃，然后关闭重启的情况，应用重启过后，从离线存储里面获取相应的数据，然后重新设置状态，恢复到崩溃前的状态。

当然，并不是所有的备忘数据都需要离线存储，一般来讲，需要存储很长时间、或者需要支持跨越会话的备份和恢复功能、或者是希望系统关闭后还能被保存的备忘数据，这些情况建议采用离线存储。

离线存储的实现也很简单，就以前面模拟运行流程的应用来说，如果要实现离线存储，主要需要修改管理者对象，把它保存备忘录对象的方法，实现成为保存到文件中，而恢复备忘录对象实现成为读取文件就可以了。对于其它相关对象，主要是要实现序列化，只有可序列化的对象才能被存储到文件中。

如果实现保存备忘录对象到文件，就不用在内存中保存了，去掉用来“记录被保存的备忘录对象”的这个属性。示例代码如下：

```java
/**
 * 负责在文件中保存模拟运行流程A的对象的备忘录对象
 */
public class FlowAMementoFileCareTaker {
    /**
     * 保存备忘录对象
     * @param memento 被保存的备忘录对象
     */
    public void saveMemento(FlowAMockMemento memento){
       //写到文件中
       ObjectOutputStream out = null;
       try{
           out = new ObjectOutputStream(
                  new BufferedOutputStream(
                         new FileOutputStream("FlowAMemento")
                  )
           );
           out.writeObject(memento);
       }catch(Exception err){
           err.printStackTrace();
       }finally{
           try {
              out.close();
           } catch (IOException e) {
              e.printStackTrace();
           }
       }
    }
    /**
     * 获取被保存的备忘录对象
     * @return 被保存的备忘录对象
     */
    public FlowAMockMemento retriveMemento(){
       FlowAMockMemento memento = null;
       //从文件中获取备忘录数据
       ObjectInputStream in = null;
       try{
           in = new ObjectInputStream(
                  new BufferedInputStream(
                         new FileInputStream("FlowAMemento")
                  )
           );
           memento = (FlowAMockMemento)in.readObject();
       }catch(Exception err){
           err.printStackTrace();
       }finally{
           try {
              in.close();
           } catch (IOException e) {
              e.printStackTrace();
           }
       }
       return memento;
    }
}

```
`同时需要让备忘录对象的窄接口继承可序列化接口`，示例代码如下：

```java
/**
 * 模拟运行流程A的对象的备忘录接口，是个窄接口
 */
public interface FlowAMockMemento extends Serializable  {
}

```

还有FlowAMock对象，也需要实现可序列化示例代码如下：

```java
/**
 * 模拟运行流程A，只是一个示意，代指某个具体流程
 */
public class FlowAMock implements Serializable  {
    //中间的实现省略了
}

```

好了，保存到文件的存储就实现好了，在前面的客户测试程序中，创建管理者对象的时候，使用这个新实现的管理者对象就可以了。去测试和体会一下。
## 3.4 再次实现可撤销操作##

在命令模式中，讲到了可撤销的操作，在那里讲到：`有两种基本的思路来实现可撤销的操作，一种是补偿式或者反操作式`：比如被撤销的操作是加的功能，那撤消的实现就变成减的功能；同理被撤销的操作是打开的功能，那么撤销的实现就变成关闭的功能。
`另外一种方式是存储恢复式`，意思就是把操作前的状态记录下来，然后要撤销操作的时候就直接恢复回去就可以了。

这里就该来实现第二种方式，就是存储恢复式，为了让大家更好的理解可撤销操作的功能，还是用原来的那个例子，对比学习会比较清楚。

这也相当于是`命令模式和备忘录模式结合的一个例子，而且由于命令列表的存在，对应保存的备忘录对象也是多个`。

* **`范例需求`** 


考虑一个计算器的功能，最简单的那种，只能实现加减法运算，现在要让这个计算器支持可撤销的操作。

* **`存储恢复式的解决方案`** 


存储恢复式的实现，可以使用备忘录模式，大致实现的思路如下：

把原来的运算类，就是那个Operation类，当作原发器，原来的内部状态result，就只提供一个getter方法，来让外部获取运算的结果；

在这个原发器里面，实现一个私有的备忘录对象；

把原来的计算器类，就是Calculator类，当作管理者，把命令对应的备忘录对象保存在这里。当需要撤销操作的时候，就把相应的备忘录对象设置回到原发器去，恢复原发器的状态；

 **`（1）定义备忘录对象的窄接口，示例代码如下：`** 

```java
public interface Memento {
    //空的
}

``` **`（2）定义命令的接口，有几点修改：`** 

修改原来的undo方法，传入备忘录对象

添加一个redo方法，传入备忘录对象

添加一个createMemento的方法，获取需要被保存的备忘录对象

示例代码如下：

```java
/**
 * 定义一个命令的接口
 */
public interface Command {
    /**
     * 执行命令
     */
    public void execute();
    /**
     * 撤销命令，恢复到备忘录对象记录的状态
     * @param m 备忘录对象
     */
    public void undo(Memento m);
    /**
     * 重做命令，恢复到备忘录对象记录的状态
     * @param m 备忘录对象
     */
    public void redo(Memento m);
    /**
     * 创建保存原发器对象的状态的备忘录对象
     * @return 创建好的备忘录对象
     */
    public Memento createMemento();
}

``` **`（3）再来定义操作运算的接口，相当于计算器类这个原发器对外提供的接口，它需要做如下的调整：`** 

去掉原有的setResult方法，内部状态，不允许外部操作

添加一个createMemento的方法，获取需要保存的备忘录对象

添加一个setMemento的方法，来重新设置原发器对象的状态

示例代码如下：

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
     * 执行加法
     * @param num 需要加的数
     */
    public void add(int num);
    /**
     * 执行减法
     * @param num 需要减的数
     */
    public void substract(int num);
    /**
     * 创建保存原发器对象的状态的备忘录对象
     * @return 创建好的备忘录对象
     */
    public Memento createMemento();
    /**
     * 重新设置原发器对象的状态，让其回到备忘录对象记录的状态
     * @param memento 记录有原发器状态的备忘录对象
     */
    public void setMemento(Memento memento);
}

``` **`（4）`由于现在撤销和恢复操作是通过使用备忘录对象，直接来恢复原发器的状态`，因此就不再需要按照操作类型来区分了，对于所有的命令实现，它们的撤销和重做都是一样的。原来的实现是要区分的，如果是撤销加的操作，那就是减，而撤销减的操作，那就是加。现在就不区分了，统一使用备忘录对象来恢复。`** 

因此，`实现一个所有命令的公共对象，在里面把公共功能都实现了，这样每个命令在实现的时候就简单了`。顺便把设置持有者的公共实现也放到这个公共对象里面来，这样各个命令对象就不用再实现这个方法了，示例代码如下：

```java
/**
 * 命令对象的公共对象，实现各个命令对象的公共方法
 */
public abstract class AbstractCommand implements Command{
    /**
     * 具体的功能实现，这里不管
     */
    public abstract void execute();
    /**
     * 持有真正的命令实现者对象
     */
    protected OperationApi operation = null;
    public void setOperation(OperationApi operation) {
       this.operation = operation;
    }
    public Memento createMemento() {
       return this.operation.createMemento();
    }
    public void redo(Memento m) {
       this.operation.setMemento(m);
    }
    public void undo(Memento m) {
       this.operation.setMemento(m);
    }
}

``` **`（5）有了公共的命令实现对象，`各个具体命令的实现就简单了，实现加法命令的对象实现，不再直接实现Command接口了，而是继承命令的公共对象`，这样只需要实现跟自己命令相关的业务方法就好了，示例代码如下：`** 

```java
public class AddCommand extends AbstractCommand{
    private int opeNum;
    public AddCommand(int opeNum){
       this.opeNum = opeNum;
    }
    public void execute() {
       this.operation.add(opeNum);
    }
}

```

看看减法命令的实现，跟加法命令的实现差不多，示例代码如下：

```java
public class SubstractCommand extends AbstractCommand{
    private int opeNum;
    public SubstractCommand(int opeNum){
       this.opeNum = opeNum;
    }
    public void execute() {
       this.operation.substract(opeNum);
    }
}

``` **`（6）接下来看看运算类的实现，相当于是原发器对象，它的实现有如下改变：`** 

不再提供setResult方法，内部状态，不允许外部来操作

添加了createMemento和setMemento方法的实现

添加实现了一个私有的备忘录对象

示例代码如下：

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
    public void add(int num){
       result += num;
    }
    public void substract(int num){
       result -= num;
    }
    public Memento createMemento() {
       MementoImpl m = new MementoImpl(result);
       return m;
    }
    public void setMemento(Memento memento) {
       MementoImpl m = (MementoImpl)memento;
       this.result = m.getResult();
    }
    /**
     * 备忘录对象
     */
    private static class MementoImpl implements Memento{
       private int result = 0;
       public MementoImpl(int result){
           this.result = result;
       }
       public int getResult() {
           return result;
       }
    }
}

``` **`（7）接下来该看看如何具体的使用备忘录对象来实现撤销操作和重做操作了。同样在计算器类里面实现，这个时候，计算器类就相当于是备忘录模式管理者对象。`** 

实现思路：`由于对于每个命令对象，撤销和重做的状态是不一样的，撤销是回到命令操作前的状态，而重做是回到命令操作后的状态`，因此对每一个命令，使用一个备忘录对象的数组来记录对应的状态。
`这些备忘录对象是跟命令对象相对应的，因此也跟命令历史记录一样，设立相应的历史记录，它的顺序跟命令完全对应起来`。在操作命令的历史记录的同时，对应操作相应的备忘录对象记录。

示例代码如下：

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
    /**
     * 命令操作对应的备忘录对象的历史记录，在撤销时候用,
     * 数组有两个元素，第一个是命令执行前的状态，第二个是命令执行后的状态
     */
    private List<Memento[]> undoMementos = new ArrayList<Memento[]>();
    /**
     * 被撤销命令对应的备忘录对象的历史记录，在恢复时候用,
     * 数组有两个元素，第一个是命令执行前的状态，第二个是命令执行后的状态
     */
    private List<Memento[]> redoMementos = new ArrayList<Memento[]>();
  
    private Command addCmd = null;
    private Command substractCmd = null;
    public void setAddCmd(Command addCmd) {
       this.addCmd = addCmd;
    }
    public void setSubstractCmd(Command substractCmd) {
       this.substractCmd = substractCmd;
    }  

    public void addPressed(){
       //获取对应的备忘录对象，并保存在相应的历史记录里面
       Memento m1 = this.addCmd.createMemento();
     
       //执行命令
       this.addCmd.execute();
       //把操作记录到历史记录里面
       undoCmds.add(this.addCmd);

       //获取执行命令后的备忘录对象
       Memento m2 = this.addCmd.createMemento();
       //设置到撤销的历史记录里面
       this.undoMementos.add(new Memento[]{m1,m2});
    }
    public void substractPressed(){
       //获取对应的备忘录对象，并保存在相应的历史记录里面    
       Memento m1 = this.substractCmd.createMemento();
     
       //执行命令
       this.substractCmd.execute();
       //把操作记录到历史记录里面
       undoCmds.add(this.substractCmd);
     
       //获取执行命令后的备忘录对象
       Memento m2 = this.substractCmd.createMemento();
       //设置到撤销的历史记录里面
       this.undoMementos.add(new Memento[]{m1,m2});
    }
    public void undoPressed(){
       if(undoCmds.size()>0){
           //取出最后一个命令来撤销
           Command cmd = undoCmds.get(undoCmds.size()-1);
           //获取对应的备忘录对象
           Memento[] ms = undoMementos.get(undoCmds.size()-1);
          
           //撤销
           cmd.undo(ms[0]);
         
           //如果还有恢复的功能，那就把这个命令记录到恢复的历史记录里面
           redoCmds.add(cmd);
           //把相应的备忘录对象也添加过去
           redoMementos.add(ms);
         
           //然后把最后一个命令删除掉，
           undoCmds.remove(cmd);
           //把相应的备忘录对象也删除掉
           undoMementos.remove(ms);
       }else{
           System.out.println("很抱歉，没有可撤销的命令");
       }
    }
    public void redoPressed(){
       if(redoCmds.size()>0){
           //取出最后一个命令来重做
           Command cmd = redoCmds.get(redoCmds.size()-1);
           //获取对应的备忘录对象
           Memento[] ms = redoMementos.get(redoCmds.size()-1);
         
           //重做
           cmd.redo(ms[1]);
         
           //把这个命令记录到可撤销的历史记录里面
           undoCmds.add(cmd);
           //把相应的备忘录对象也添加过去
           undoMementos.add(ms);
           //然后把最后一个命令删除掉
           redoCmds.remove(cmd);
           //把相应的备忘录对象也删除掉
           redoMementos.remove(ms);
       }else{
           System.out.println("很抱歉，没有可恢复的命令");
       }
    }
}

``` **`（8）客户端跟以前的实现没有什么变化，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
       //1：组装命令和接收者
       //创建接收者
       OperationApi operation = new Operation();
       //创建命令
       AddCommand addCmd = new AddCommand(5);
       SubstractCommand substractCmd = new SubstractCommand(3);
       //组装命令和接收者
       addCmd.setOperation(operation);
       substractCmd.setOperation(operation);
     
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

```

运行结果，示例如下：

```java
一次加法运算后的结果为：5
一次减法运算后的结果为：2
撤销一次后的结果为：5
再撤销一次后的结果为：0
恢复操作一次后的结果为：5
再恢复操作一次后的结果为：2

```

跟前面采用补偿式或者反操作式得到的结果是一样的。好好体会一下，对比两种实现方式，看看都是怎么实现的。顺便也体会一下命令模式和备忘录模式是如何结合起来实现功能的。
## 3.5 备忘录模式的优缺点##

* **`更好的封装性`** 

`备忘录模式通过使用备忘录对象，来封装原发器对象的内部状态`，虽然这个对象是保存在原发器对象的外部，但是`由于备忘录对象的窄接口并不提供任何方法，这样有效的保证了对原发器对象内部状态的封装，不把原发器对象的内部实现细节暴露给外部`。

* **`简化了原发器`** 


备忘录模式中，备忘录对象被保存到原发器对象之外，让客户来管理他们请求的状态，从而让原发器对象得到简化。

* **`窄接口和宽接口`** 


备忘录模式，通过引入窄接口和宽接口，使得不同的地方，对备忘录对象的访问是不一样的。`窄接口保证了只有原发器才可以访问备忘录对象的状态`。

* **`可能会导致高开销`** 

`备忘录模式基本的功能，就是对备忘录对象的存储和恢复`，它的基本实现方式就是缓存备忘录对象。这样一来，如果需要缓存的数据量很大，或者是特别频繁的创建备忘录对象，开销是很大的。
## 3.6 思考备忘录模式##

* **`备忘录模式的本质`** 

`备忘录模式的本质：保存和恢复内部状态。``保存是手段，恢复才是目的`，备忘录模式备忘些什么东西呢？

就是原发器对象的内部状态，备忘录模式备忘的就是这些内部状态，这些内部状态是不对外的，只有原发器对象才能够进行操作。

标准的备忘录模式保存数据的手段是：`通过内存缓存，广义的备忘录模式实现的时候，可以采用离线存储的方式，把这些数据保存到文件或者数据库等地方`。

备忘录模式为何要保存数据呢，`目的就是为了在有需要的时候，恢复原发器对象的内部状态，所以恢复是备忘录模式的目的`。

根据备忘录模式的本质，`从广义上讲，进行数据库存取操作`；或者是web应用中的request、session、servletContext等的attribute数据存取；更进一步，大多数基于缓存功能的数据操作都可以视为广义的备忘录模式。`不过广义到这个地步，还提备忘录模式已经没有什么意义了，所以对于备忘录模式还是多从狭义上来说`。

事实上，对于备忘录模式最主要的一个点，`就是封装状态的备忘录对象，不应该被除了原发器对象之外的对象访问`，至于如何存储那都是小事情。因为备忘录模式要解决的主要问题就是：`在不破坏对象封装性的前提下，来保存和恢复对象的内部状态`。这是一个很主要的判断点，`如果备忘录对象可以让原发器对象外的对象访问的话，那就算是广义的备忘录模式了，其实提不提备忘录模式已经没有太大的意义了`。

* **`何时选用备忘录模式`** 


建议在如下情况中，选用备忘录模式：

`如果必须保存一个对象在某一个时刻的全部或者部分状态，这样在以后需要的时候，可以把该对象恢复到先前的状态`。可以使用备忘录模式，使用备忘录对象来封装和保存需要保存的内部状态，然后把备忘录对象保存到管理者对象里面，在需要的时候，再从管理者对象里面获取备忘录对象，来恢复对象的状态。
`如果需要保存一个对象的内部状态，但是如果用接口来让其它对象直接得到这些需要保存的状态，将会暴露对象的实现细节并破坏对象的封装性`。可以使用备忘录模式，把备忘录对象实现成为原发器对象的内部类，而且还是私有的，从而保证只有原发器对象才能访问该备忘录对象。这样既保存了需要保存的状态，又不会暴露原发器对象的内部实现细节。

## 3.7 **`相关模式`** ##

* **`备忘录模式和命令模式`** 


这两个模式可以组合使用。

命令模式实现中，`在实现命令的撤销和重做的时候，可以使用备忘录模式`，在命令操作的时候记录下操作前后的状态，然后在命令撤销和重做的时候，直接使用相应的备忘录对象来恢复状态就可以了。

在这种撤销的执行顺序和重做执行顺序可控的情况下，备忘录对象还可以采用增量式记录的方式，可以减少缓存的数据量。

* **`备忘录模式和原型模式`** 


这两个模式可以组合使用。

在原发器对象创建备忘录对象的时候，`如果原发器对象中全部或者大部分的状态都需要保存，一个简洁的方式就是直接克隆一个原发器对象`。也就是说，这个时候备忘录对象里面存放的是一个原发器对象的实例，这个在前面已经示例过了，这里就不赘述了。


[0]: ./img/2062729-f91102e9a2200808.png
[1]: ./img/2062729-c3b7d93be7908d0d.png
[2]: ./img/2062729-e9f25938f45c7a67.png
[3]: ./img/2062729-b518c65e45f59d46.png
[4]: ./img/2062729-9cff2d59c00fcc69.png