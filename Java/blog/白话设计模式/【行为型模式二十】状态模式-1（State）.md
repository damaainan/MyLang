## 【行为型模式二十】状态模式-1（State）

2016.12.06 12:14*

来源：[https://www.jianshu.com/p/4d5975227485](https://www.jianshu.com/p/4d5975227485)


          
## 1 场景问题#
## 1.1 实现在线投票##

考虑一个在线投票的应用，要实现控制同一个用户只能投一票，如果一个用户反复投票，而且投票次数超过5次，则判定为恶意刷票，要取消该用户投票的资格，当然同时也要取消他所投的票。如果一个用户的投票次数超过8次，将进入黑名单，禁止再登录和使用系统。

该怎么实现这样的功能呢？
## 1.2 不用模式的解决方案##

分析上面的功能，为了控制用户投票，需要记录用户所投票的记录，同时还要记录用户投票的次数，为了简单，直接使用两个Map来记录。

在投票的过程中，又有四种情况：

一是用户是正常投票；

二是用户正常投票过后，有意或者无意的重复投票；

三是用户恶意投票；

四是黑名单用户；

这几种情况下对应的处理是不一样的。看看代码吧，示例代码如下：

```java
/**
 * 投票管理
 */
public class VoteManager {
    /**
     * 记录用户投票的结果,Map<String,String>对应Map<用户名称,投票的选项>
     */
    private Map<String,String> mapVote = new HashMap<String,String>();
    /**
     * 记录用户投票次数,Map<String,Integer>对应Map<用户名称,投票的次数>
     */
    private Map<String,Integer> mapVoteCount = new HashMap<String,Integer>();
    /**
     * 投票
     * @param user 投票人，为了简单，就是用户名称
     * @param voteItem 投票的选项
     */
    public void vote(String user,String voteItem){
       //1：先为该用户增加投票的次数
       //先从记录中取出已有的投票次数
       Integer oldVoteCount = mapVoteCount.get(user);
       if(oldVoteCount==null){
           oldVoteCount = 0;
       }
       oldVoteCount = oldVoteCount + 1;
       mapVoteCount.put(user, oldVoteCount);
      
       //2：判断该用户投票的类型，到底是正常投票、重复投票、恶意投票
       //还是上黑名单，然后根据投票类型来进行相应的操作  
       if(oldVoteCount==1){
           //正常投票
           //记录到投票记录中
           mapVote.put(user, voteItem);
           System.out.println("恭喜你投票成功");
       }else if(oldVoteCount>1 && oldVoteCount<5){
           //重复投票
           //暂时不做处理
           System.out.println("请不要重复投票");
       }else if(oldVoteCount >= 5 && oldVoteCount<8){
           //恶意投票
           //取消用户的投票资格，并取消投票记录
           String s = mapVote.get(user);
           if(s!=null){
              mapVote.remove(user);
           }
           System.out.println("你有恶意刷票行为，取消投票资格");
       }else if(oldVoteCount>=8){
           //黑名单
           //记入黑名单中，禁止登录系统了
           System.out.println("进入黑名单，将禁止登录和使用本系统");
       }
    }
}

```

写个客户端来测试看看，是否能满足功能要求，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
       VoteManager vm = new VoteManager();
       for(int i=0;i<8;i++){
           vm.vote("u1", "A");
       }
    }
}

```

运行结果如下：

```java
恭喜你投票成功
请不要重复投票
请不要重复投票
请不要重复投票
你有恶意刷票行为，取消投票资格
你有恶意刷票行为，取消投票资格
你有恶意刷票行为，取消投票资格
进入黑名单，将禁止登录和使用本系统

```
## 1.3 有何问题##

看起来很简单，是不是？幸亏这里只是示意，否则，你想想，在vote()方法中那么多判断，还有每个判断对应的功能处理都放在一起，是不是有点太杂乱了，那简直就是个大杂烩，如果把每个功能都完整的实现出来，那vote()方法会很长的。

一个问题是：`如果现在要修改某种投票情况所对应的具体功能处理，那就需要在那个大杂烩里面，找到相应的代码块，然后进行改动`。

另外一个问题是：`如果要添加新的功能，比如投票超过8次但不足10次的，给个机会，只是禁止登录和使用系统3天，如果再犯，才永久封掉账号，该怎么办呢？那就需要改动投票管理的源代码，在上面的if-else结构中再添加一个else if块进行处理`。
`不管哪一种情况，都是在一大堆的控制代码里面找出需要的部分，然后进行修改，这从来都不是好方法，那么该如何实现才能做到`：既能够很容易的给vote()方法添加新的功能，又能够很方便的修改已有的功能处理呢？
## 2 解决方案#
## 2.1 状态模式来解决##

用来解决上述问题的一个合理的解决方案就是状态模式。那么什么是状态模式呢？

* **`状态模式定义`** 



![][0]


状态模式定义


* **`应用状态模式来解决的思路`** 


仔细分析上面的问题，会发现，那几种用户投票的类型，`就相当于是描述了人员的几种投票状态，而各个状态和对应的功能处理具有很强的对应性，有点类似于“一个萝卜一个坑”，各个状态下的处理基本上都是不一样的，也不存在可以相互替换的可能`。

为了解决上面提出的问题，很自然的一个设计就是`首先把状态和状态对应的行为从原来的大杂烩代码中分离出来，把每个状态所对应的功能处理封装在一个独立的类里面`，这样选择不同处理的时候，其实就是在选择不同的状态处理类。

然后为了统一操作这些不同的状态类，`定义一个状态接口来约束它们，这样外部就可以面向这个统一的状态接口编程，而无需关心具体的状态类实现了`。

这样一来，要修改某种投票情况所对应的具体功能处理，`那就是直接修改或者扩展某个状态处理类的功能就可以了`。而要添加新的功能就更简单，直接添加新的状态处理类就可以了，当然在使用Context的时候，需要设置使用这个新的状态类的实例。
## 2.2 模式结构和说明##

状态模式的结构如图所示：


![][1]


状态模式的结构如图所示


 **`Context：环境`** ，也称上下文，通常用来定义客户感兴趣的接口，同时维护一个来具体处理当前状态的实例对象。 **`State：状态接口`** ，用来封装与上下文的一个特定状态所对应的行为。 **`ConcreteState：具体实现状态处理的类`** ，每个类实现一个跟上下文相关的状态的具体处理。

## 2.3 状态模式示例代码##

* **`首先来看状态接口，示例代码如下：`** 


```java
/**
 * 封装与Context的一个特定状态相关的行为
 */
public interface State {
    /**
     * 状态对应的处理
     * @param sampleParameter 示例参数，说明可以传入参数，具体传入
     *             什么样的参数，传入几个参数，由具体应用来具体分析
     */
    public void handle(String sampleParameter);
}

```

* **`再来看看具体的状态实现，目前具体的实现ConcreteStateA和ConcreteStateB示范的是一样的，只是名称不同，示例代码如下：`** 


```java
/**
 * 实现一个与Context的一个特定状态相关的行为
 */
public class ConcreteStateA implements State {
    public void handle(String sampleParameter) {
       //实现具体的处理
    }
}
/**
 * 实现一个与Context的一个特定状态相关的行为
 */
public class ConcreteStateB implements State {
    public void handle(String sampleParameter) {
       //实现具体的处理
    }
}

```

* **`再来看看上下文的具体实现，上下文通常用来定义客户感兴趣的接口，同时维护一个具体的处理当前状态的实例对象。示例代码如下：`** 


```java
/**
 * 定义客户感兴趣的接口，通常会维护一个State类型的对象实例
 */
public class Context {
    /**
     * 持有一个State类型的对象实例
     */
    private State state;
    /**
     * 设置实现State的对象的实例
     * @param state 实现State的对象的实例
     */
    public void setState(State state) {
       this.state = state;
    }
    /**
     * 用户感兴趣的接口方法
     * @param sampleParameter 示意参数
     */
    public void request(String sampleParameter) {
       //在处理中，会转调state来处理
       state.handle(sampleParameter);
    }
}

```
## 2.4 使用状态模式重写示例##

看完了上面的状态模式的知识，有些朋友跃跃欲试，打算使用状态模式来重写前面的示例，要使用状态模式，`首先就需要把投票过程的各种状态定义出来，然后把这些状态对应的处理从原来大杂烩的实现中分离出来，形成独立的状态处理对象`。`而原来的投票管理的对象就相当于Context了`。 **``把状态对应的行为分离出去过后，怎么调用呢？``** 

按照状态模式的示例，是在Context中，处理客户请求的时候，转调相应的状态对应的具体的状态处理类来进行处理。 **``那就引出下一个问题：那么这些状态怎么变化呢？``** 

看原来的实现，就是在投票方法里面，根据投票的次数进行判断，并维护投票类型的变化。那好，也依葫芦画瓢，就在投票方法里面来维护状态变化。

这个时候的程序结构如图所示：


![][2]


状态模式的示例程序机构示意图


* **`先来看状态接口的代码实现，示例代码如下：`** 


```java
/**
 * 封装一个投票状态相关的行为
 */
public interface VoteState {
    /**
     * 处理状态对应的行为
     * @param user 投票人
     * @param voteItem 投票项
     * @param voteManager 投票上下文，用来在实现状态对应的功能处理的时候，
     *                    可以回调上下文的数据
     */
    public void vote(String user,String voteItem, VoteManager voteManager);
}

```

* **`定义了状态接口，那就该来看看如何实现各个状态对应的处理了，现在的实现很简单，就是把原来的实现从投票管理类里面分离出来就可以了。先看正常投票状态对应的处理，示例代码如下：`** 


```java
public class NormalVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //正常投票
       //记录到投票记录中
       voteManager.getMapVote().put(user, voteItem);
       System.out.println("恭喜你投票成功");
    }
}

```

接下来看看重复投票状态对应的处理，示例代码如下：

```java
public class RepeatVoteState implements VoteState {
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //重复投票
       //暂时不做处理
       System.out.println("请不要重复投票");
    }
}

```

接下来看看恶意投票状态对应的处理，示例代码如下：

```java
public class SpiteVoteState implements VoteState{
    public void vote(String user, String voteItem,VoteManager voteManager) {
       //恶意投票
       //取消用户的投票资格，并取消投票记录
       String s = voteManager.getMapVote().get(user);
       if(s!=null){
           voteManager.getMapVote().remove(user);
       }
       System.out.println("你有恶意刷票行为，取消投票资格");
    }
}

```

接下来看看黑名单状态对应的处理，示例代码如下：

```java
public class BlackVoteState implements VoteState{
    public void vote(String user, String voteItem,VoteManager voteManager) {
       //黑名单
       //记入黑名单中，禁止登录系统了
       System.out.println("进入黑名单，将禁止登录和使用本系统");
    }
}

```

* **`定义好了状态接口和状态实现，看看现在的投票管理，相当于状态模式中的上下文，相对而言，它的改变如下：`** 


添加持有状态处理对象；

添加能获取记录用户投票结果的Map的方法，各个状态处理对象，在进行状态对应的处理的时候，需要获取上下文中的记录用户投票结果的Map数据；

在vote()方法实现里面，原来判断投票类型就变成了判断投票的状态，而原来每种投票类型对应的处理，现在已经封装到对应的状态对象里面去了，因此直接转调对应的状态对象的方法即可。示例代码如下：

```java
/**
 * 投票管理
 */
public class VoteManager {
    /**
     * 持有状态处理对象
     */
    private VoteState state = null;
    /**
     * 记录用户投票的结果,Map<String,String>对应Map<用户名称,投票的选项>
     */
    private Map<String,String> mapVote = new HashMap<String,String>();
    /**
     * 记录用户投票次数,Map<String,Integer>对应Map<用户名称,投票的次数>
     */
    private Map<String,Integer> mapVoteCount = new HashMap<String,Integer>();
    /**
     * 获取记录用户投票结果的Map
     * @return 记录用户投票结果的Map
     */
    public Map<String, String> getMapVote() {
       return mapVote;
    }
  
    /**
     * 投票
     * @param user 投票人，为了简单，就是用户名称
     * @param voteItem 投票的选项
     */
    public void vote(String user,String voteItem){
       //1：先为该用户增加投票的次数
       //先从记录中取出已有的投票次数
       Integer oldVoteCount = mapVoteCount.get(user);
       if(oldVoteCount==null){
            oldVoteCount = 0;
       }
       oldVoteCount = oldVoteCount + 1;
       mapVoteCount.put(user, oldVoteCount); 
       //2：判断该用户投票的类型，就相当于是判断对应的状态
       //到底是正常投票、重复投票、恶意投票还是上黑名单的状态
       if(oldVoteCount==1){
            state = new NormalVoteState();
       }else if(oldVoteCount>1 && oldVoteCount<5){
            state = new RepeatVoteState();
       }else if(oldVoteCount >= 5 && oldVoteCount<8){
            state = new SpiteVoteState();
       }else if(oldVoteCount>=8){
            state = new BlackVoteState();
       }

       //然后转调状态对象来进行相应的操作
       state.vote(user, voteItem, this);
    }
}

```

* **`该写个客户端来测试一下了，经过这么修改过后，好用吗？试试看就知道了。客户端没有任何的改变，跟前面实现的一样，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
       VoteManager vm = new VoteManager();
       for(int i=0;i<8;i++){
           vm.vote("u1", "A");
       }
    }
}

```

运行一下试试吧，结果应该是跟前面一样的，也就是说都是实现一样的功能，只是采用了状态模式来实现。测试结果如下：

```java
恭喜你投票成功
请不要重复投票
请不要重复投票
请不要重复投票
你有恶意刷票行为，取消投票资格
你有恶意刷票行为，取消投票资格
你有恶意刷票行为，取消投票资格
进入黑名单，将禁止登录和使用本系统

```

从上面的示例可以看出，`状态的转换基本上都是内部行为，主要在状态模式内部来维护`。比如对于投票的人员，任何时候他的操作都是投票，`但是投票管理对象的处理却不一定一样，会根据投票的次数来判断状态，然后根据状态去选择不同的处理`。
## 3 模式讲解#
## 3.1 认识状态模式##

* **`状态和行为`** 

`所谓对象的状态，通常指的就是对象实例的属性的值；而行为指的就是对象的功能，再具体点说，行为多半可以对应到方法上。``状态模式的功能就是分离状态的行为，通过维护状态的变化，来调用不同的状态对应的不同的功能。`也就是说，状态和行为是相关联的，它们的关系可以描述为：`状态决定行为`。

由于状态是在运行期被改变的，因此行为也会在运行期，根据状态的改变而改变，看起来，同一个对象，在不同的运行时刻，行为是不一样的，就像是类被修改了一样。

* **`行为的平行性`** 

`注意是平行性而不是平等性`。所谓平行性指的是各个状态的行为所处的层次是一样的，相互是独立的、没有关联的，是根据不同的状态来决定到底走平行线的那一条，行为是不同的，`当然对应的实现也是不同的，相互之间是不可替换的`。如图所示：


![][3]


状态的平行性示意图

`而平等性强调的是可替换性`，大家是同一行为的不同描述或实现，因此在同一个行为发生的时候，可以根据条件来挑选任意一个实现来进行相应的处理。如图所示：


![][4]


平等性的示意图


大家可能会发现状态模式的结构和策略模式的结构完全一样，但是，`它们的目的、实现、本质都是完全不一样的`。这个行为之间的特性也是状态模式和策略模式一个很重要的区别， **``状态模式的行为是平行性的，不可相互替换的；而策略模式的行为是平等性的，是可以相互替换的``** 。

* **`上下文和状态处理对象`** 


在状态模式中，`上下文是持有状态的对象，但是上下文自身并不处理跟状态相关的行为`，而是把处理状态的功能委托给了状态对应的状态处理类来处理。
`在具体的状态处理类里面经常需要获取上下文自身的数据，甚至在必要的时候会回调上下文的方法`，因此，通常将上下文自身当作一个参数传递给具体的状态处理类。

客户端一般只和上下文交互，客户端可以用状态对象来配置一个上下文，一旦配置完毕，就不再需要和状态对象打交道了，客户端通常不负责运行期间状态的维护，也不负责决定到底后续使用哪一个具体的状态处理对象。

* **`不完美的OCP体验`** 


好了，已经使用状态模式来重写了前面的示例，那么到底能不能解决前面提出的问题呢？也就是修改和扩展方不方便呢？一起来看一下。

先看修改已有的功能吧，由于现在每个状态对应的处理已经封装到对应的状态类里面了，要修改已有的某个状态的功能，直接扩展某个类进行修改就好了，对其它的程序没有影响。比如：现在要修改正常投票状态对应的功能，对于正常投票的用户给予积分奖励，那么只需要扩展正常投票状态对应的类，然后进行修改，示例代码如下：

```java
public class NormalVoteState2 extends NormalVoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //先调用已有的功能
       super.vote(user, voteItem, voteManager);
       //给予积分奖励，示意一下
       System.out.println("奖励积分10分");
    }
}

```

一切良好，对吧，可是怎么让VoteManager能使用这个新的实现类呢？`按照目前的实现，没有办法，只好去修改VoteManager的vote()方法中对状态的维护代码了`，把使用NormalVoteState的地方换成使用NormalVoteState2。

再看看如何添加新的功能，比如投票超过8次但不足10次的，给个机会，只是禁止登录和使用系统3天，如果再犯，才进入黑名单。要实现这个功能，先要对原来的投票超过8次进入黑名单的功能进行修改，修改成投票超过10次才进入黑名单；然后新加入一个功能，实现超过8次但不足10次的，只是禁止登录和使用系统3天的功能。把这个新功能实现出来，示例代码如下：

```java
public class BlackWarnVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //待进黑名单警告状态
       System.out.println("禁止登录和使用系统3天");
    }
}

```

实现好了这个类，该怎样加入到已有的系统呢？

同样需要去修改上下文的vote()方法中对于状态判断和维护的代码，示例代码如下：

```java
if(oldVoteCount==1){
    state = new NormalVoteState2();
}else if(oldVoteCount>1 && oldVoteCount<5){
    state = new RepeatVoteState();
}else if(oldVoteCount >= 5 && oldVoteCount<8){
    state = new SpiteVoteState();
}else if(oldVoteCount>=8 && oldVoteCount<10){
    state = new BlackWarnVoteState();
}else if(oldVoteCount>10){
    state = new BlackVoteState();
}

```

好像也实现了功能是不是，而且改动起来确实也变得简单点了，但是仔细想想，是不是没有完全遵循OCP原则？结论是很显然的，明显没有完全遵循OCP原则。

这里要说明一点，`设计原则是大家在设计和开发中尽量去遵守的，但不是一定要遵守，尤其是完全遵守，在实际开发中，完全遵守那些设计原则几乎是不可能完成的任务`。

就像状态模式的实际实现中，由于状态的维护和转换在状态模式结构里面，不管你是扩展了状态实现类，还是新添加了状态实现类，都需要修改状态维护和转换的地方，以使用新的实现。

虽然可以有好几个地方来维护状态的变化，这个后面会讲到，但是都是在状态模式结构里面的，所以都有这个问题，算是不完美的OCP体验吧。

* **`创建和销毁状态对象`** 


在应用状态模式的时候，有一个常见的考虑，那就是：究竟何时创建和销毁状态对象。常见的有几个选择：

一个是当需要使用状态对象的时候创建，使用完后就销毁它们；

另一个是提前创建它们并且始终不销毁；

还有一种是采用延迟加载和缓存合用的方式，就是当第一次需要使用状态对象的时候创建，使用完后并不销毁对象，而是把这个对象缓存起来，等待下一次使用，而且在合适的时候，会由缓存框架销毁状态对象

 **`怎么选择呢？下面给出选择建议：`** 

如果要进入的状态在运行时是不可知的，而且上下文是比较稳定的，不会经常改变状态，而且使用也不频繁，这个时候建议选第一种方案。

如果状态改变很频繁，也就是需要频繁的创建状态对象，而且状态对象还存储着大量的信息数据，这种情况建议选第二种方案。

如果无法确定状态改变是否频繁，而且有些状态对象的状态数据量大，有些比较小，一切都是未知的，建议选第三种方案。

事实上，`在实际工程开发中，第三种方案是首选，因为它兼顾了前面两种方案的优点，而又避免了它们的缺点，几乎能适应各种情况的需要`。只是这个方案在实现的时候，要实现一个合理的缓存框架，而且要考虑多线程并发的问题，因为需要由缓存框架来在合适的时候销毁状态对象，因此实现上难度稍高点。`另外在实现中还可以考虑结合享元模式，通过享元模式来共享状态对象`。

* **`状态模式的调用顺序示意图`** 


状态模式在实现上，对于状态的维护有不同的实现方式，前面的示例中，`采用的是在Context中进行状态的维护和转换`，这里就先画出这种方式的调用顺序示意图，其它的方式在后面讲到了再画。

在Context进行状态维护和转换的调用顺序示意图如图所示：


![][5]


在Context进行状态维护和转换的调用顺序示意图

## 3.2 状态维护和转换控制##
`所谓状态的维护，指的就是维护状态的数据，就是给状态设置不同的状态值；而状态的转换，指的就是根据状态的变化来选择不同的状态处理对象`。在状态模式中，通常有两个地方可以进行状态的维护和转换控制。

一个就是在上下文当中，因为状态本身通常被实现为上下文对象的状态，因此可以在上下文里面进行状态维护，当然也就可以控制状态的转换了。前面投票的示例就是采用的这种方式。

另外一个地方就是在状态的处理类里面，当每个状态处理对象处理完自身状态所对应的功能后，可以根据需要指定后继的状态，以便让应用能正确处理后续的请求。

先看看示例，为了对比学习，就来看看如何把前面投票的例子修改成：`在状态处理类里面进行后续状态的维护和转换`。

* **`同样先来看投票状态的接口，没有变化，示例代码如下：`** 


```java
/**
 * 封装一个投票状态相关的行为
 */
public interface VoteState {
    /**
     * 处理状态对应的行为
     * @param user 投票人
     * @param voteItem 投票项
     * @param voteManager 投票上下文，用来在实现状态对应的功能处理的时候，
     *                    可以回调上下文的数据
     */
    public void vote(String user,String voteItem,VoteManager voteManager);
}

```

* **`对于各个具体的状态实现对象，主要的变化在于：在处理完自己状态对应的功能后，还需要维护和转换状态对象。`** 


一个一个来看吧，先看看正常投票的状态处理对象，示例代码如下：

```java
public class NormalVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //正常投票，记录到投票记录中
       voteManager.getMapVote().put(user, voteItem);
       System.out.println("恭喜你投票成功");
       //正常投票完成，维护下一个状态，同一个人再投票就重复了
       voteManager.getMapState().put(user,new RepeatVoteState());
    }
}

```

接下来看看重复投票状态对应的处理对象，示例代码如下：

```java
public class RepeatVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //重复投票，暂时不做处理
       System.out.println("请不要重复投票");   
       //重复投票完成，维护下一个状态，重复投票到5次，就算恶意投票了
       //注意这里是判断大于等于4，因为这里设置的是下一个状态
       //下一个操作次数就是5了，就应该算是恶意投票了
       if(voteManager.getMapVoteCount().get(user) >= 4){
           voteManager.getMapState().put(user,new SpiteVoteState());
       }
    }
}

```

接下来看看恶意投票状态对应的处理对象，示例代码如下：

```java
public class SpiteVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //恶意投票，取消用户的投票资格，并取消投票记录
       String s = voteManager.getMapVote().get(user);
       if(s!=null){
           voteManager.getMapVote().remove(user);
       }
       System.out.println("你有恶意刷票行为，取消投票资格");    
       //恶意投票完成，维护下一个状态，投票到8次，就进黑名单了
       //注意这里是判断大于等于7，因为这里设置的是下一个状态
       //下一个操作次数就是8了，就应该算是进黑名单了
       if(voteManager.getMapVoteCount().get(user) >= 7){
           voteManager.getMapState().put(user,new BlackVoteState());
       }
    }
}

```

接下来看看黑名单状态对应的处理对象，没什么变化，示例代码如下：

```java
public class BlackVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //黑名单，记入黑名单中，禁止登录系统了
       System.out.println("进入黑名单，将禁止登录和使用本系统");
    }
}

```

* **`该来看看现在的投票管理类该如何实现了，跟在上下文中维护和转换状态相比，大致有如下的变化：`** 


需要按照每个用户来记录他们对应的投票状态，不同的用户，对应的投票状态是不同的，因此使用一个Map来记录，而不再是原来的一个单一的投票状态对象。

可能有些朋友会问，那为什么前面的实现可以呢？那是因为投票状态是由投票管理对象集中控制的，不同的人员在进入投票方法的时候，是重新判断该人员具体的状态对象的，而现在是要把状态维护分散到各个状态类里面去，因此需要记录各个状态类判断过后的结果。

需要把记录投票状态的数据，还有记录投票次数的数据，提供相应的getter方法，各个状态在处理的时候需要通过这些方法来访问数据。

原来在vote()方法里面进行的状态控制和转换去掉，变成直接根据人员来从状态记录的Map中获取对应的状态对象了。

看看实现代码吧，示例代码如下：

```java
public class VoteManager {
    /**
     * 记录当前每个用户对应的状态处理对象，每个用户当前的状态是不同的
     * Map<String,VoteState>对应Map<用户名称,当前对应的状态处理对象>
     */
    private Map<String,VoteState> mapState = new HashMap<String,VoteState>();
    /**
     * 记录用户投票的结果,Map<String,String>对应Map<用户名称,投票的选项>
     */
    private Map<String,String> mapVote = new HashMap<String,String>();
    /**
     * 记录用户投票次数,Map<String,Integer>对应Map<用户名称,投票的次数>
     */
    private Map<String,Integer> mapVoteCount = new HashMap<String,Integer>();
    /**
     * 获取记录用户投票结果的Map
     * @return 记录用户投票结果的Map
     */
    public Map<String, String> getMapVote() {
       return mapVote;
    }
    /**
     * 获取记录每个用户对应的状态处理对象的Map
     * @return 记录每个用户对应的状态处理对象的Map
     */
    public Map<String, VoteState> getMapState() {
       return mapState;
    }
    /**
     * 获取记录每个用户对应的投票次数的Map
     * @return 记录每个用户对应的投票次数的Map
     */
    public Map<String, Integer> getMapVoteCount() {
       return mapVoteCount;
    }
    /**
     * 投票
     * @param user 投票人，为了简单，就是用户名称
     * @param voteItem 投票的选项
     */
    public void vote(String user,String voteItem){
       //1：先为该用户增加投票的次数
       //先从记录中取出已有的投票次数
       Integer oldVoteCount = mapVoteCount.get(user);
       if(oldVoteCount==null){
           oldVoteCount = 0;
       }
       oldVoteCount = oldVoteCount + 1;
       mapVoteCount.put(user, oldVoteCount);    

       //2：获取该用户的投票状态
       VoteState state = mapState.get(user);
       //如果没有投票状态，说明还没有投过票，就初始化一个正常投票状态
       if(state==null){
           state = new NormalVoteState();
       }

       //然后转调状态对象来进行相应的操作
       state.vote(user, voteItem, this);
    }
}

```

* **`实现得差不多了，该来测试了，客户端没有变化，去运行一下，看看效果，看看两种维护状态变化的方式实现的结果一样吗？答案应该是一样的。`** 

 **`那么到底如何选择这两种方式呢？`** 
`一般情况下，如果状态转换的规则是一定的，一般不需要进行什么扩展规则，那么就适合在上下文中统一进行状态的维护`。
`如果状态的转换取决于前一个状态动态处理的结果，或者是依赖于外部数据`，为了增强灵活性，这种情况下，`一般是在状态处理类里面进行状态的维护`。

* **`采用让状态对象来维护和转换状态的调用顺序示意图如图所示：`** 



![][6]


状态对象来维护和转换状态的调用顺序示意图


* **`再来看看这种实现方式下，如何修改已有的功能，或者是添加新的状态处理。`** 


要修改已有的功能，同样是找到对应的状态处理对象，要么直接修改，要么扩展，前面已经示例过了，就不再赘述了。

对于添加新的状态处理的功能，这种实现方式会比较简单。`先直接添加新的状态处理的类，然后去找到需要转换到这个新状态的状态处理类，修改那个处理类，让其转换到这个新状态就可以了`。

比如还是来实现那个：投票超过8次但不足10次的，给个机会，只是禁止登录和使用系统3天，如果再犯，才进入黑名单的功能。按照现在的方式，示例代码如下：

```java
public class BlackWarnVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //待进黑名单警告状态
       System.out.println("禁止登录和使用系统3天");
       //待进黑名单警告处理完成，维护下一个状态，投票到10次，就进黑名单了
       //注意这里是判断大于等于9，因为这里设置的是下一个状态
       //下一个操作次数就是10了，就应该算是进黑名单了
       if(voteManager.getMapVoteCount().get(user) >= 9){
           voteManager.getMapState().put(user, new BlackVoteState());
       }
    }
}

```

那么如何加入系统呢？
`不再是去修改VoteManger了，而是找到应该转换到这个新状态的那个状态，修改它的状态维护和转换`。应该是在恶意投票处理里面，让它转换到这个新的状态，也就是把恶意投

票处理里面的下面这句话：

```java
voteManager.getMapState().put(user, new BlackVoteState());

```

替换成：

```java
voteManager.getMapState().put(user, new BlackWarnVoteState());

```

这样就自然的把现在新的状态处理添加到了已有的应用中。
## 3.3 使用数据库来维护状态##

在实际开发中，`还有一个方式来维护状态，那就是使用数据库`，在数据库中存储下一个状态的识别数据，也就是说，维护下一个状态，演化成了维护下一个状态的识别数据，比如状态编码。

这样在程序中，通过查询数据库中的数据来得到状态编码，然后再根据状态编码来创建出相应的状态对象，然后再委托相应的状态对象进行功能处理。

还是用前面投票的示例来说明，如果使用数据库来维护状态的话，大致如何实现。

* **`首先，就是每个具体的状态处理类中，原本在处理完成后，要判断下一个状态是什么，然后创建下一个状态对象，并设置回到上下文中。`** 


如果使用数据库的方式，那就不用创建下一个状态对象，也不用设置回到上下文中了，而是把下一个状态对应的编码记入数据库中，这样就可以了。还是示意一个，看看重复投票状态下的实现吧，示例代码如下：

```java
public class RepeatVoteState implements VoteState{
    public void vote(String user, String voteItem, VoteManager voteManager) {
       //重复投票，暂时不做处理
       System.out.println("请不要重复投票");
       //重复投票完成，维护下一个状态，重复投票到5次，就算恶意投票了
       if(voteManager.getMapVoteCount().get(user) >= 4){
           voteManager.getMapState().put(user,new SpiteVoteState());
           //直接把下一个状态的编码记录入数据库就好了
       }
    }
}

```

这里只是示意一下，并不真的去写和数据库操作的代码。其它的状态实现类，也做同样类似的修改，就不去赘述了。

* **`在Context里面，也就是投票管理对象里面，就不需要那个记录所有用户状态的Map了，直接从数据库中获取该用户当前对应的状态编码，然后根据状态编码来创建出状态对象来。原有的示例代码如下：`** 


```java
//2：获取该用户的投票状态
VoteState state = mapState.get(user);
//如果没有投票状态，说明还没有投过票，就初始化一个正常投票状态
if(state==null){
    state = new NormalVoteState();
}

```

现在被修改成，示例代码如下：

```java
VoteState state = null;
//2：直接从数据库获取该用户对应的下一个状态的状态编码
String stateId = "从数据库中获取这个状态编码";
//开始根据状态编码来创建需用的状态对象
if(stateId==null || stateId.trim().length()==0){
    //如果没有值，说明还没有投过票，就初始化一个正常投票状态
    state = new NormalVoteState();
}else if("重复投票".equals(stateId)){
    state = new RepeatVoteState();
}else if("恶意投票".equals(stateId)){
    state = new SpiteVoteState();
}else if("黑名单".equals(stateId)){
    state = new BlackVoteState();
}

```

可能有些朋友会发现，如果向数据库里面存储下一个状态对象的状态编码，那么上下文中就不需要再持有状态对象了，有点相当于把这个功能放到数据库中了。有那么点相似性，不过要注意，`数据库存储的只是状态编码，而不是状态对象，获取到数据库中的状态编码过后，在程序里面还是需要根据状态编码去真正创建对应的状态对象`。

当然，要想程序更通用一点，`可以通过配置文件来配置状态编码和对应的状态处理类，当然也可以直接在数据库中记录状态编码和对应的状态处理类`，这样的话，在上下文中，先获取下一个状态的状态编码，然后根据这个状态编码去获取对应的类，然后可以通过反射来创建对象，这样实现就避免了那一长串的if-else，而且以后添加新的状态编码和状态处理对象也不用再修改代码了。示例代码如下：

```java
VoteState state = null;
//2：直接从数据库获取该用户对应的下一个状态的状态编码
String stateId = "从数据库中获取这个值";
//开始根据状态编码来创建需用的状态对象
     
//根据状态编码去获取相应的类
String className = "根据状态编码去获取相应的类";
//使用反射创建对象实例，简单示意一下
Class c = Class.forName(className);
state = (VoteState)c.newInstance();

```

直接把“转移”记录到数据库中。还有一种情况是直接把“转移”记录到数据库中，这样会更灵活。`所谓转移，指的就是描述从A状态到B状态的这么一个转换变化`。


[0]: ./img/2062729-60f515ed7acb53b4.png
[1]: ./img/2062729-b0209b4309327949.png
[2]: ./img/2062729-5517e7c2ffe9616f.png
[3]: ./img/2062729-902213a7ce34da34.png
[4]: ./img/2062729-459a6b406425768d.png
[5]: ./img/2062729-56c392339af31f41.png
[6]: ./img/2062729-ba1d7c71d52c2954.png