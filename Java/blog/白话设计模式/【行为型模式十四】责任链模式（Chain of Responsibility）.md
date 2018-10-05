## 【行为型模式十四】责任链模式（Chain of Responsibility）

2016.11.23 19:30*

来源：[https://www.jianshu.com/p/9593b4b0d333](https://www.jianshu.com/p/9593b4b0d333)


          
## 1 场景问题#
## 1.1 申请聚餐费用##

来考虑这样一个功能：申请聚餐费用的管理。

很多公司都有这样的福利，就是项目组或者是部门可以向公司申请一些聚餐费用，用于组织项目组成员或者是部门成员进行聚餐活动，以增进人员之间的情感，更有利于工作中的相互合作。

申请聚餐费用的大致流程一般是：由申请人先填写申请单，然后交给领导审查，如果申请批准下来了，领导会通知申请人审批通过，然后申请人去财务核领费用，如果没有核准，领导会通知申请人审批未通过，此事也就此作罢了。

不同级别的领导，对于审批的额度是不一样的，比如：项目经理只能审批500元以内的申请；部门经理能审批1000元以内的申请；而总经理可以审核任意额度的申请。

也就是说，当某人提出聚餐费用申请的请求后，该请求会由项目经理、部门经理、总经理之中的某一位领导来进行相应的处理，但是提出申请的人并不知道最终会由谁来处理他的请求，一般申请人是把自己的申请提交给项目经理，或许最后是由总经理来处理他的请求，但是申请人并不知道应该由总经理来处理他的申请请求。

那么该怎样实现这样的功能呢？
## 1.2 不用模式的解决方案##

分析上面要实现的功能，主要就是要根据申请费用的多少，然后让不同的领导来进行处理就可以实现了。也就是有点逻辑判断而已，示例代码如下：

```java
/**
 * 处理聚餐费用申请的对象
 */
public class FeeRequest {
    /**
     * 提交聚餐费用申请给项目经理
     * @param user 申请人
     * @param fee 申请费用
     * @return 成功或失败的具体通知
     */
    public String requestToProjectManager(String user,double fee){
        String str = "";
        if(fee < 500){
            //项目经理的权限比较小，只能在500以内
            str = this.projectHandle(user, fee);
        }else if(fee < 1000){
            //部门经理的权限只能在1000以内
            str = this.depManagerHandle(user, fee);
        }else if(fee >= 1000){
            //总经理的权限很大，只要请求到了这里，他都可以处理
            str = this.generalManagerHandle(user, fee);
        }
        return str;
    }
    /**
     * 项目经理审批费用申请，参数、返回值和上面是一样的，省略了
     */
    private String projectHandle(String user, double fee) {
        String str = "";
        //为了测试，简单点，只同意小李的
        if("小李".equals(user)){
            str = "项目经理同意"+user+"聚餐费用"+fee+"元的请求";
        }else{
            //其它人一律不同意
            str = "项目经理不同意"+user+"聚餐费用"+fee+"元的请求";
        }
        return str;
    }
    /**
     * 部门经理审批费用申请，参数、返回值和上面是一样的，省略了
     */
    private String depManagerHandle(String user, double fee) {
        String str = "";
        //为了测试，简单点，只同意小李申请的
        if("小李".equals(user)){
            str = "部门经理同意"+user+"聚餐费用"+fee+"元的请求";
        }else{
            //其它人一律不同意
            str= "部门经理不同意"+user+"聚餐费用"+fee+"元的请求";
        }
        return str;
     }
    /**
     * 总经理审批费用申请，参数、返回值和上面是一样的，省略了
     */
    private String generalManagerHandle(String user, double fee) {
       String str = "";
      
       //为了测试，简单点，只同意小李的
       if("小李".equals(user)){
           str = "总经理同意"+user+"聚餐费用"+fee+"元的请求";
       }else{
           //其它人一律不同意
           str = "总经理不同意"+user+"聚餐费用"+fee+"元的请求";
       }
       return str;
    }
}

```

写个客户端来测试看看效果，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        FeeRequest request = new FeeRequest();
      
        //开始测试
        String ret1 = request.requestToProjectManager("小李", 300);
        System.out.println("the ret="+ret1);     
        String ret2 = request.requestToProjectManager("小张", 300);
        System.out.println("the ret="+ret2);
      
        String ret3 = request.requestToProjectManager("小李", 600);
        System.out.println("the ret="+ret3);     
        String ret4 = request.requestToProjectManager("小张", 600);
        System.out.println("the ret="+ret4);
      
        String ret5 = request.requestToProjectManager("小李", 1200);
        System.out.println("the ret="+ret5);     
        String ret6 = request.requestToProjectManager("小张", 1200);
        System.out.println("the ret="+ret6);
    }
}

```

运行结果如下：

```java
the ret1=项目经理同意小李聚餐费用300.0元的请求
the ret2=项目经理不同意小张聚餐费用300.0元的请求
the ret3=部门经理同意小李聚餐费用600.0元的请求
the ret4=部门经理不同意小张聚餐费用600.0元的请求
the ret5=总经理同意小李聚餐费用1200.0元的请求
the ret6=总经理不同意小张聚餐费用1200.0元的请求

```
## 1.3 有何问题##

上面的实现很简单，基本上没有什么特别的难度。仔细想想，这么实现有没有问题呢？仔细分析申请聚餐费用的业务功能和目前的实现，主要面临着如下问题：

聚餐费用申请的处理流程是可能会变动的。

比如现在的处理流程是：提交申请给项目经理，看看是否适合由项目经理处理，如果不是，看看是否适合由部门经理处理，如果不是，看看是否适合由总经理处理的步骤。今后可能会变化成：直接提交给部门经理，看看是否适合由部门经理处理，如果不是，总经理处理这样的步骤。也就是说，对于聚餐费用申请，要求处理的逻辑步骤是灵活的。

各个处理环节的业务处理也是会变动的。

因为处理流程可能发生变化，也会导致某些步骤的具体的业务功能发生变化，比如：原本部门经理审批聚餐费用的时候，只是判断是否批准；现在，部门经理可能在审批聚餐费用的时候，核算本部门的实时成本，这就出现新的业务处理功能了。

如果采用上面的实现，要是处理的逻辑发生了变化，解决的方法，`一个是生成一个子类，覆盖requestToProjectManager方法，然后在里面实现新的处理`；另外一个方法`就是修改处理申请的方法的源代码来实现`。`要是具体处理环节的业务处理的功能发生了变化，那就只好找到相应的处理方法，进行源代码修改了`。

总之都不是什么好方法，也就是说，如果出现聚餐费用申请的处理流程变化的情况，或者是出现各个处理环节的功能变化的时候，上面的实现方式是很难灵活的变化来适应新功能的要求的。

把上面的问题抽象一下： **`客户端发出一个请求，会有很多对象都可以来处理这个请求，而且不同对象的处理逻辑是不一样的。`** 对于客户端而言，无所谓谁来处理，反正有对象处理就可以了。

而且在上述处理中，还希望处理流程是可以灵活变动的，而处理请求的对象需要能方便的修改或者是被替换掉，以适应新的业务功能的需要。

请问如何才能实现上述要求？
## 2 解决方案#
## 2.1 职责链模式来解决##

用来解决上述问题的一个合理的解决方案，就是使用职责链模式。那么什么是职责链模式呢？

* **`职责链模式定义`** 



![][0]


**职责链模式定义**


* **`应用职责链模式来解决的思路`** 


仔细分析上面的场景，当客户端提出一个聚餐费用的申请，后续处理这个申请的对象，项目经理、部门经理和总经理，自然的形成了一个链，从项目经理-部门经理-总经理，客户端的申请请求就在这个链中传递，直到有领导处理为止。看起来，上面的功能要求很适合采用职责链来处理这个业务。

要想让处理请求的流程可以灵活的变动， **`一个基本的思路，那就是动态构建流程步骤`** ，这样随时都可以重新组合出新的流程来。而要让处理请求的对象也要很灵活，那就要让它足够简单，最好是只实现单一的功能，或者是有限的功能，这样更有利于修改和复用。

职责链模式就很好的体现了上述的基本思路， **`首先职责链模式会定义一个所有处理请求的对象都要继承实现的抽象类`** ，这样就有利于随时切换新的实现； **`其次每个处理请求对象只实现业务流程中的一步业务处理`** ，这样使其变得简单； **`最后职责链模式会动态的来组合这些处理请求的对象`** ，把它们按照流程动态组合起来，并要求它们依次调用，这样就动态的实现了流程。

这样一来， **`如果流程发生了变化，只要重新组合就好了`** ；如果某个处理的业务功能发生了变化，一个方案是修改该处理对应的处理对象，另一个方案是直接提供一个新的实现，然后在组合流程的时候，用新的实现替换掉旧的实现就可以了。
## 2.2 模式结构和说明##

职责链模式的结构如图所示：


![][1]


职责链模式结构图


`Handler：定义职责的接口`，通常在这里定义处理请求的方法，可以在这里实现后继链。
`ConcreteHandler：实现职责的类`，在这个类里面，实现对在它职责范围内请求的处理，如果不处理，就继续转发请求给后继者。
`Client：职责链的客户端`，向链上的具体处理者对象提交请求，让职责链负责处理。

## 2.3 职责链模式示例代码##

* **`先来看看职责的接口定义，示例代码如下：`** 


```java
/**
   * 职责的接口，也就是处理请求的接口
   */
public abstract class Handler {
    /**
     * 持有后继的职责对象
     */
    protected Handler successor;
    /**
     * 设置后继的职责对象
     * @param successor 后继的职责对象
     */
    public void setSuccessor(Handler successor) {
        this.successor = successor;
    }
    /**
     * 示意处理请求的方法，虽然这个示意方法是没有传入参数，
     * 但实际是可以传入参数的，根据具体需要来选择是否传递参数
     */
    public abstract void handleRequest();
}

```

* **`接下来看看具体的职责实现对象，示例代码如下：`** 


```java
/**
   * 具体的职责对象，用来处理请求
   */
public class ConcreteHandler1 extends Handler {
    public void handleRequest() {
        //根据某些条件来判断是否属于自己处理的职责范围
        //判断条件比如：从外部传入的参数，或者这里主动去获取的外部数据，
        //如从数据库中获取等，下面这句话只是个示意
        boolean someCondition = false;
     
        if(someCondition){
            //如果属于自己处理的职责范围，就在这里处理请求
            //具体的处理代码
            System.out.println("ConcreteHandler1 handle request");
        }else{
            //如果不属于自己处理的职责范围，那就判断是否还有后继的职责对象
            //如果有，就转发请求给后继的职责对象
            //如果没有，什么都不做，自然结束
            if(this.successor!=null){
                this.successor.handleRequest();
            }
        }
    }
}

```

另外一个ConcreteHandler2和上面ConcreteHandler1的示意代码几乎是一样的，因此就不去赘述了。

* **`接下来看看客户端的示意，示例代码如下：`** 


```java
/**
   * 职责链的客户端，这里只是个示意
   */
public class Client {
    public static void main(String[] args) {
        //先要组装职责链
        Handler h1 = new ConcreteHandler1();
        Handler h2 = new ConcreteHandler2();
     
        h1.setSuccessor(h2);    
        //然后提交请求
        h1.handleRequest();
    }
}

```
## 2.4 使用职责链模式重写示例##

要使用职责链模式来重写示例，还是先来实现如下的功能：当某人提出聚餐费用申请的请求后，该请求会在项目经理-部门经理-总经理这样一条领导处理链上进行传递，`发出请求的人并不知道谁会来处理他的请求，每个领导会根据自己的职责范围，来判断是处理请求还是把请求交给更高级的领导，只要有领导处理了，传递就结束了`。
`需要把每位领导的处理独立出来，实现成单独的职责处理对象，然后为它们提供一个公共的、抽象的父职责对象，这样就可以在客户端来动态的组合职责链，实现不同的功能要求了`。还是看一下示例的整体结构，会有助于对示例的理解和把握。如图所示：


![][2]


使用职责链模式的示例程序的结构示意图


* **`定义职责的抽象类`** 


首先来看看定义所有职责的抽象类，也就是所有职责的外观，在这个类里面持有下一个处理请求的对象，同时还要定义业务处理方法，示例代码如下：

```java
/**
 * 定义职责对象的接口
 */
public abstract class Handler {
    /**
     * 持有下一个处理请求的对象
     */
    protected Handler successor = null;
    /**
     * 设置下一个处理请求的对象
     * @param successor 下一个处理请求的对象
     */
    public void setSuccessor(Handler successor){
       this.successor = successor;
    }
    /**
     * 处理聚餐费用的申请
     * @param user 申请人
     * @param fee 申请的钱数
     * @return 成功或失败的具体通知
     */
    public abstract String handleFeeRequest(String user,double fee);
}

```

* **`实现各自的职责`** 


现在实现的处理聚餐费用流程是：申请人提出的申请交给项目经理处理，项目经理的处理权限是500元以内，超过500元，把申请转给部门经理处理，部门经理的处理权限是1000元以内，超过1000元，把申请转给总经理处理。

分析上述流程，对请求主要有三个处理环节，`把它们分别实现成为职责对象，一个对象实现一个环节的处理功能`，这样就会比较简单。 **`先看看项目经理的处理吧，示例代码如下：`** 

```java
public class ProjectManager extends Handler{
    public String handleFeeRequest(String user, double fee) {
        String str = "";
        //项目经理的权限比较小，只能在500以内
        if(fee < 500){
            //为了测试，简单点，只同意小李的
            if("小李".equals(user)){
                str = "项目经理同意"+user+"聚餐费用"+fee+"元的请求";
            }else{
                //其它人一律不同意
                str = "项目经理不同意"+user+"聚餐费用"+fee+"元的请求";
            }
            return str;
        }else{
            //超过500，继续传递给级别更高的人处理
            if(this.successor!=null){
                return successor.handleFeeRequest(user, fee);
            }
        }
        return str;
    }
}

``` **`接下来看看部门经理的处理，示例代码如下：`** 

```java
public class DepManager extends Handler{ 
    public String handleFeeRequest(String user, double fee) {
        String str = "";
        //部门经理的权限只能在1000以内
        if(fee < 1000){
            //为了测试，简单点，只同意小李申请的
            if("小李".equals(user)){
                str = "部门经理同意"+user+"聚餐费用"+fee+"元的请求";
            }else{
                //其它人一律不同意
                str = "部门经理不同意"+user+"聚餐费用"+fee+"元的请求";
            }
            return str;
        }else{
            //超过1000，继续传递给级别更高的人处理
            if(this.successor!=null){
                return this.successor.handleFeeRequest(user, fee);
            }
        }
        return str;
    }
}

``` **`再看总经理的处理，示例代码如下：`** 

```java
public class GeneralManager extends Handler{
    public String handleFeeRequest(String user, double fee) {
        String str = "";
        //总经理的权限很大，只要请求到了这里，他都可以处理
        if(fee >= 1000){
            //为了测试，简单点，只同意小李的
            if("小李".equals(user)){
                str = "总经理同意"+user+"聚餐费用"+fee+"元的请求";
            }else{
                //其它人一律不同意
                str = "总经理不同意"+user+"聚餐费用"+fee+"元的请求";
            }
            return str;
        }else{
            //如果还有后继的处理对象，继续传递
            if(this.successor!=null){
                return successor.handleFeeRequest(user, fee);
            }
        }
        return str;
    }
}

```

* **`使用职责链`** 


那么客户端如何使用职责链呢，最重要的就是要先构建职责链，然后才能使用。示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        //先要组装职责链   
        Handler h1 = new GeneralManager();
        Handler h2 = new DepManager();
        Handler h3 = new ProjectManager();
        h3.setSuccessor(h2);
        h2.setSuccessor(h1);
     
        //开始测试
        String ret1 = h3.handleFeeRequest("小李", 300);
        System.out.println("the ret1="+ret1); 
        String ret2 = h3.handleFeeRequest("小张", 300);
        System.out.println("the ret2="+ret2); 
     
        String ret3 = h3.handleFeeRequest("小李", 600);
        System.out.println("the ret3="+ret3); 
        String ret4 = h3.handleFeeRequest("小张", 600);
        System.out.println("the ret4="+ret4); 
     
        String ret5 = h3.handleFeeRequest("小李", 1200); 
        System.out.println("the ret5="+ret5); 
        String ret6 = h3.handleFeeRequest("小张", 1200);
        System.out.println("the ret6="+ret6); 
    }
}

```

运行结果如下：

```java
the ret1=项目经理同意小李聚餐费用300.0元的请求
the ret2=项目经理不同意小张聚餐费用300.0元的请求
the ret3=部门经理同意小李聚餐费用600.0元的请求
the ret4=部门经理不同意小张聚餐费用600.0元的请求
the ret5=总经理同意小李聚餐费用1200.0元的请求
the ret6=总经理不同意小张聚餐费用1200.0元的请求

```

看起来结果跟前面不用模式的实现方案的运行结果是一样的，它们本来就是实现的同样的功能，只不过实现方式不同而已。

* **`如何运行`** 


理解了示例的整体结构和具体实现，那么示例的具体运行过程是怎样的呢？

下面就以“小李申请聚餐费用1200元”这个费用申请为例来说明，调用过程的示意图如图所示：


![][3]


职责链示例调用过程示意图

## 3 模式讲解#
## 3.1 认识职责链模式##

* **`模式功能`** 


职责链模式主要用来处理： **`“客户端发出一个请求，有多个对象都有机会来处理这一个请求，但是客户端不知道究竟谁会来处理他的请求”`** ，这样的情况。`也就是需要让请求者和接收者解耦，这样就可以动态的切换和组合接收者了`。

要注意在标准的职责链模式里面，是只要没有有对象处理了请求，这个请求就到此为止，不再被传递和处理了。

如果是要变形使用职责链，就可以让这个请求继续传递，每个职责对象对这个请求进行一定的功能处理，从而形成一个处理请求的功能链。

* **`隐式接收者`** 


当客户端发出请求的时候，客户端并不知道谁会真正处理他的请求，客户端只知道他提交请求的第一个对象。从第一个处理对象开始，整个职责链里面的对象，要么自己处理请求，要么继续转发给下一个接收者。

也就是`对于请求者而言，并不知道最终的接收者是谁，但是一般情况下，总是会有一个对象来处理的，因此称为隐式接收者`。

* **`如何构建链`** 


职责链的链怎么构建呢？这是个大问题，实现的方式也是五花八门，归结起来大致有以下一些方式。 **`首先是按照实现的地方来说：`** 

可以实现在客户端，`在提交请求前组合链`，也就是在使用的时候动态组合链，称为外部链；

也可以在Handler里面实现链的组合，算是内部链的一种；

当然还有一种就是在各个职责对象里面，`由各个职责对象自行决定后续的处理对象`，这种实现方式要求每个职责对象除了进行业务处理外，还必须了解整个业务流程。

 **`按照构建链的数据来源，也就是决定了按照什么顺序来组合链的数据，又分为几种：`** 

一种就是在程序里面动态组合；

也可以通过外部，比如数据库来获取组合的数据，这种属于数据库驱动的方式；

还有一种方式就是通过配置文件传递进来，也可以是流程的配置文件；

如果是从外部获取数据来构建链，那么在程序运行的时候，会读取这些数据，然后根据数据的要求来获取相应的对象，并组合起来。

还有一种是不需要构建链，`因为已有的对象已经自然构成链了，这种情况多出现在组合模式构建的对象树中，这样子对象可以很自然的向上找到自己的父对象`。就像部门人员的组织结构一样，顶层是总经理，总经理下面是各个部门的经理，部门经理下面是项目经理，项目经理下面是各个普通员工，自然就可以形成：普通员工-项目经理-部门经理-总经理这样的链。

* **`谁来处理`** 


职责链中那么多处理对象，到底谁来处理请求呢，`这个是在运行时期动态决定的`。当请求被传递到某个处理对象的时候，这个对象会按照已经设定好的条件来判断，是否属于自己处理的范围，如果是就处理，如果不是就转发请求给下一个对象。

* **`请求一定会被处理吗`** 


在职责链模式中，请求不一定会被处理，因为可能没有合适的处理者，请求在职责链里面从头传递到尾，每个处理对象都判断不属于自己处理，最后请求就没有对象来处理。这一点是需要注意的。
`可以在职责链的末端始终加上一个不支持此功能处理的职责对象，这样如果传递到这里，就会出现提示，本职责链没有对象处理这个请求。`## 3.2 处理多种请求##

前面的示例都是`同一个职责链处理一种请求的情况`，现在有这样的需求，还是费用申请的功能，这次是申请预支差旅费，假设还是同一流程，也就是组合同一个职责链，从项目经理-传递给部门经理-传递给总经理，虽然流程相同，`但是每个处理类需要处理两种请求，它们的具体业务逻辑是不一样的`，那么该如何实现呢？

* **`简单的处理方式`** 


要解决这个问题，也不是很困难，`一个简单的方法就是为每种业务单独定义一个方法，然后客户端根据不同的需要调用不同的方法`，还是通过代码来示例一下。注意这里故意的把两个方法做的有些不一样，`一个是返回String类型的值，一个是返回boolean类型的值`；`另外一个是返回到客户端再输出信息，一个是直接在职责处理里面就输出信息`。 **`（1）首先是改造职责对象的接口，添加上新的业务方法，示例代码如下：`** 

```java
/**
 * 定义职责对象的接口
 */
public abstract class Handler {
    /**
     * 持有下一个处理请求的对象
     */
    protected Handler successor = null;
    /**
     * 设置下一个处理请求的对象
     * @param successor 下一个处理请求的对象
     */
    public void setSuccessor(Handler successor){
        this.successor = successor;
    }
    /**
     * 处理聚餐费用的申请
     * @param user 申请人
     * @param fee 申请的钱数
     * @return 成功或失败的具体通知
     */
    public abstract String handleFeeRequest(String user,double fee);
    /**
     * 处理预支差旅费用的申请
     * @param user 申请人
     * @param requestFee 申请的钱数
     * @return 是否同意
     */
    public abstract boolean handlePreFeeRequest(String user,double requestFee);
}

``` **`（2）职责的接口发生了改变，对应的处理类也要改变，这几个处理类是类似的，原有的功能不变，然后在新的实现方法里面，同样判断一下是否属于自己处理的范围，如果属于自己处理的范围那就处理，否则就传递到下一个处理。还是示范一个，看看项目经理的处理吧，示例代码如下：`** 

```java
public class ProjectManager extends Handler{
    public String handleFeeRequest(String user, double fee) {
        String str = "";
        //项目经理的权限比较小，只能在500以内
        if(fee < 500){
            //为了测试，简单点，只同意小李的
            if("小李".equals(user)){
                str = "项目经理同意"+user+"聚餐费用"+fee+"元的请求";
            }else{
               //其它人一律不同意
               str = "项目经理不同意"+user+"聚餐费用"+fee+"元的请求";
            }
            return str;
        }else{
            //超过500，继续传递给级别更高的人处理
            if(this.successor!=null){
                return successor.handleFeeRequest(user, fee);
            }
        }
        return str;
    }
    public boolean handlePreFeeRequest(String user, double requestNum) {
        //项目经理的权限比较小，只能在5000以内
        if(requestNum < 5000){
            //工作需要嘛，统统同意
            System.out.println("项目经理同意"+user+"预支差旅费用"+requestNum+"元的请求");
            return true;
        }else{
            //超过5000，继续传递给级别更高的人处理
            if(this.successor!=null){
                return this.successor.handlePreFeeRequest(user, requestNum);
            }
        }
        return false;
    }
}  

```

其它的处理类似，就不去演示了。 **`（3）准备好了各个处理职责的类，看看客户端如何调用，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
        //先要组装职责链   
        Handler h1 = new GeneralManager();
        Handler h2 = new DepManager();
        Handler h3 = new ProjectManager();
        h3.setSuccessor(h2);
        h2.setSuccessor(h1);
  
        //开始测试申请聚餐费用
        String ret1 = h3.handleFeeRequest("小李", 300);
        System.out.println("the ret1="+ret1);
        String ret2 = h3.handleFeeRequest("小李", 600);
        System.out.println("the ret2="+ret2);
        String ret3 = h3.handleFeeRequest("小李", 1200);
        System.out.println("the ret3="+ret3);
     
        //开始测试申请差旅费用
        h3.handlePreFeeRequest("小张", 3000);
        h3.handlePreFeeRequest("小张", 6000);
        h3.handlePreFeeRequest("小张", 32000);
   }
}

```

运行的结果如下：

```java
the ret1=项目经理同意小李聚餐费用300.0元的请求
the ret2=部门经理同意小李聚餐费用600.0元的请求
the ret3=总经理同意小李聚餐费用1200.0元的请求
项目经理同意小张预支差旅费用3000.0元的请求
部门经理同意小张预支差旅费用6000.0元的请求
总经理同意小张预支差旅费用32000.0元的请求

```

* **`通用请求的处理方式`** 


上面的实现看起来很容易，但是仔细想想，这样实现有没有什么问题呢？

这种实现方式有一个很明显的问题，`那就是只要增加一个业务，就需要修改职责的接口，这是很不灵活的，Java开发中很强调面向接口编程，因此接口应该相对保持稳定，接口一改，需要修改的地方就太多了，频繁修改接口绝对不是个好主意`。

那有没有什么好方法来实现呢？分析一下现在变化的东西：

一是不同的业务需要传递的业务数据不同；

二是不同的业务请求的方法不同；

三是不同的职责对象处理这些不同的业务请求的业务逻辑不同；

现在有一种简单的方式，可以较好的解决这些问题。 **`首先定义一套通用的调用框架，用一个通用的请求对象来封装请求传递的参数；然后定义一个通用的调用方法，这个方法不去区分具体业务，所有的业务都是这一个方法，那么具体的业务如何区分呢，就是在通用的请求对象里面会有一个业务的标记；到了职责对象里面，愿意处理就跟原来一样的处理方式，如果不愿意处理，就传递到下一个处理对象就好了`** 。
`对于返回值也可以来个通用的，最简单的就是使用Object类型`。

看例子吧，为了示范，先就假定只有一个业务方法，等把这一个方法搞定了，明白了，然后再扩展一个业务方法，就能清晰地看出这种设计的好处了。 **`（1）先看看通用的请求对象的定义，示例代码如下：`** 

```java
/**
 * 通用的请求对象
 */
public class RequestModel {
    /**
     * 表示具体的业务类型
     */
    private String type;
    /**
     * 通过构造方法把具体的业务类型传递进来
     * @param type 具体的业务类型
     */
    public RequestModel(String type){
        this.type = type;
    }
    public String getType() {
        return type;
    }  
}

``` **`（2）看看此时的通用职责处理对象，在这里要实现一个通用的调用框架，示例代码如下：`** 

```java
/**
 * 定义职责对象的接口
 */
public abstract class Handler {
    /**
     * 持有下一个处理请求的对象
     */
    protected Handler successor = null;
    /**
     * 设置下一个处理请求的对象
     * @param successor 下一个处理请求的对象
     */
    public void setSuccessor(Handler successor){
        this.successor = successor;
    }
    /**
     * 通用的请求处理方法
     * @param rm 通用的请求对象
     * @return 处理后需要返回的对象
     */
    public Object handleRequest(RequestModel rm){
        if(successor != null){
            //这个是默认的实现，如果子类不愿意处理这个请求，
            //那就传递到下一个职责对象去处理
            return this.successor.handleRequest(rm);
        }else{
            System.out.println("没有后续处理或者暂时不支持这样的功能处理");
            return false;
        }
    }
}

``` **`（3）现在来加上第一个业务，就是“聚餐费用申请”的处理，为了描述具体的业务数据，`需要扩展通用的请求对象，把业务数据封装进去`，另外定义一个请求对象，示例代码如下：`** 

```java
/**
 * 封装跟聚餐费用申请业务相关的请求数据
 */
public class FeeRequestModel extends RequestModel{
    /**
     * 约定具体的业务类型
     */
    public final static String FEE_TYPE = "fee";
    public FeeRequestModel() {
        super(FEE_TYPE);
    }
    /**
     * 申请人
     */
    private String user;
    /**
     * 申请金额
     */
    private double fee;
    public String getUser() {
        return user;
    }
    public void setUser(String user) {
        this.user = user;
    }
    public double getFee() {
        return fee;
    }
    public void setFee(double fee) {
        this.fee = fee;
    }
}

``` **`（4）接下来该实现职责对象的处理了，大同小异的，还是看一个就行了，看看项目经理的处理吧，在这个处理类里面，`首先要覆盖父类的通用业务处理方法，然后在里面处理自己想要实现的业务，不想处理的就让父类去处理，父类会默认的传递给下一个处理对象`，示例代码如下：`** 

```java
/**
 * 实现项目经理处理聚餐费用申请的对象
 */
public class ProjectManager extends Handler{
    public Object handleRequest(RequestModel rm){
        if(FeeRequestModel.FEE_TYPE.equals(rm.getType())){
            //表示聚餐费用申请
            return handleFeeRequest(rm);
        }else{
            //其它的项目经理暂时不想处理
            return super.handleRequest(rm);
        }
    }
    private Object handleFeeRequest(RequestModel rm) {
        //先把通用的对象造型回来
        FeeRequestModel frm = (FeeRequestModel)rm;
        String str = "";
        //项目经理的权限比较小，只能在500以内
        if(frm.getFee() < 500){
            //为了测试，简单点，只同意小李的
            if("小李".equals(frm.getUser())){
                str = "项目经理同意"+frm.getUser()+"聚餐费用"+frm.getFee()+"元的请求";
            }else{
                //其它人一律不同意
                str = "项目经理不同意"+frm.getUser()+"聚餐费用"+frm.getFee()+"元的请求";
            }
            return str;
        }else{
            //超过500，继续传递给级别更高的人处理
            if(this.successor!=null){
                return successor.handleRequest(rm);
            }
        }
        return str;
    }
}

```

部门经理、总经理的处理对象和项目经理的处理类似，就不去示例了。 **`（5）客户端也需要变化，对于客户端，唯一的麻烦是需要知道每个业务对应的具体的请求对象，因为要封装业务数据进去，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
        //先要组装职责链   
        Handler h1 = new GeneralManager();
        Handler h2 = new DepManager();
        Handler h3 = new ProjectManager();
        h3.setSuccessor(h2);
        h2.setSuccessor(h1);
     
        //开始测试申请聚餐费用
        FeeRequestModel frm = new FeeRequestModel();
        frm.setFee(300);
        frm.setUser("小李");
        //调用处理
        String ret1 = (String)h3.handleRequest(frm);
        System.out.println("ret1="+ret1);
     
        //重新设置申请金额，再调用处理
        frm.setFee(800);    
        h3.handleRequest(frm);
        String ret2 = (String)h3.handleRequest(frm);
        System.out.println("ret2="+ret2);
     
        //重新设置申请金额，再调用处理
        frm.setFee(1600);   
        h3.handleRequest(frm);
        String ret3 = (String)h3.handleRequest(frm);
        System.out.println("ret3="+ret3);
    }
}

```

运行结果如下：

```java
ret1=项目经理同意小李聚餐费用300.0元的请求
ret2=部门经理同意小李聚餐费用800.0元的请求
ret3=总经理同意小李聚餐费用1600.0元的请求

``` **`（6）接下来看看如何在不改动现有的框架的前提下，扩展新的业务，这样才能说明这种设计的灵活性。`** 

假如就是要实现上面示例过的另外一个功能“预支差旅费申请”吧。要想扩展新的业务，第一步就是新建一个封装业务数据的对象，示例代码如下：

```java
/**
 * 封装跟预支差旅费申请业务相关的请求数据
 */
public class PreFeeRequestModel extends RequestModel{
    /**
     * 约定具体的业务类型
     */
    public final static String FEE_TYPE = "preFee";
    public PreFeeRequestModel() {
        super(FEE_TYPE);
    }
    /**
     * 申请人
     */
    private String user;
    /**
     * 申请金额
     */
    private double fee;
    public String getUser() {
        return user;
    }
    public void setUser(String user) {
        this.user = user;
    }
    public double getFee() {
        return fee;
    }
    public void setFee(double fee) {
        this.fee = fee;
    }
}

```

有些朋友会发现，这个对象跟封装聚餐费用申请业务数据的对象几乎完全一样的，这里要说明一下，一样的原因主要是我们为了演示简单，设计得相似，实际业务中可能是不一样的，因此，最好还是一个业务一个对象，如果确实有公共的数据，可以定义公共的父类，最好不要让不同的业务使用统一个对象，容易混淆。 **`（7）对于具体进行职责处理的类，`比较好的方式就是扩展出子类来，然后在子类里面实现新加入的业务，当然也可以直接在原来的对象上改`。还是采用扩展出子类的方式吧，还是看看新的项目经理的处理类，示例代码如下：`** 

```java
/**
 * 实现为项目经理增加预支差旅费用申请处理的功能的子对象，
 * 现在的项目经理既可以处理聚餐费用申请，又可以处理预支差旅费用申请
 */
public class ProjectManager2 extends ProjectManager{
    public Object handleRequest(RequestModel rm){
        if(PreFeeRequestModel.FEE_TYPE.equals(rm.getType())){
            //表示预支差旅费用申请
            return myHandler(rm);
        }else{
            //其它的让父类去处理
            return super.handleRequest(rm);
        }
    }
    private Object myHandler(RequestModel rm) {
        //先把通用的对象造型回来
        PreFeeRequestModel frm = (PreFeeRequestModel)rm;
        //项目经理的权限比较小，只能在5000以内
        if(frm.getFee() < 5000){
            //工作需要嘛，统统同意
            System.out.println("项目经理同意"+frm.getUser()+"预支差旅费用"+frm.getFee()+"元的请求");
            return true;
        }else{
            //超过5000，继续传递给级别更高的人处理
            if(this.successor!=null){
                return this.successor.handleRequest(rm);
            }
        }
        return false;
    }
}

```

部门经理和总经理的处理类似，就不去示例了。 **`（8）看看此时的测试，示例如下：`** 

```java
public class Client {
    public static void main(String[] args) {
        //先要组装职责链   
        Handler h1 = new GeneralManager2();
        Handler h2 = new DepManager2();
        Handler h3 = new ProjectManager2();
        h3.setSuccessor(h2);
        h2.setSuccessor(h1);
     
        //开始测试申请聚餐费用
        FeeRequestModel frm = new FeeRequestModel();
        frm.setFee(300);
        frm.setUser("小李");
        //调用处理
        String ret1 = (String)h3.handleRequest(frm);
        System.out.println("ret1="+ret1);
     
        //重新设置申请金额，再调用处理
        frm.setFee(800);    
        h3.handleRequest(frm);
        String ret2 = (String)h3.handleRequest(frm);
        System.out.println("ret2="+ret2);
     
        //重新设置申请金额，再调用处理
        frm.setFee(1600);   
        h3.handleRequest(frm);
        String ret3 = (String)h3.handleRequest(frm);
        System.out.println("ret3="+ret3);
     
        //开始测试申请预支差旅费用
        PreFeeRequestModel pfrm = new PreFeeRequestModel();
        pfrm.setFee(3000);
        pfrm.setUser("小张");
        //调用处理
        h3.handleRequest(pfrm);
        //重新设置申请金额，再调用处理
        pfrm.setFee(6000);
        h3.handleRequest(pfrm);
        //重新设置申请金额，再调用处理
        pfrm.setFee(36000);
        h3.handleRequest(pfrm);
    }
}

```

运行一下，试试看，运行结果如下：

```java
ret1=项目经理同意小李聚餐费用300.0元的请求
ret2=部门经理同意小李聚餐费用800.0元的请求
ret3=总经理同意小李聚餐费用1600.0元的请求
项目经理同意小张预支差旅费用3000.0元的请求
部门经理同意小张预支差旅费用6000.0元的请求
总经理同意小张预支差旅费用36000.0元的请求

```

好好体会一下这种设计方式的好处，相当的通用和灵活，有了新业务，只需要添加实现新功能的对象就可以了，但是带来的缺陷就是`可能会造成对象层次过多，或者出现较多的细粒度的对象，极端情况下，每次就扩展一个方法，会出现大量只处理一个功能的细粒度对象`。
## 3.3 功能链##

在实际开发中，经常会出现一个把职责链稍稍变形的用法。`在标准的职责链中，一个请求在职责链中传递，只要有一个对象处理了这个请求，就会停止`。

现在稍稍变一下， **`改成一个请求在职责链中传递，每个职责对象负责处理请求的某一方面的功能，处理完成后，不是停止，而是继续向下传递请求，当请求通过很多职责对象处理过后，功能也就处理完了，把这样的职责链称为功能链。`** 

考虑这样一个功能，在实际应用开发中，在进行业务处理之前，通常需要进行权限检查、通用数据校验、数据逻辑校验等处理，然后才开始真正的业务逻辑实现。可以把这些功能分散到一个功能链中，这样做的目的是使程序结构更加灵活，而且复用性会更好，比如通用的权限检查就只需要做一份，然后就可以在多个功能链中使用了。

有些朋友看到这里，可能会想，这不是可以使用装饰模式来实现吗？没错，可以使用装饰模式来实现这样的功能，但是职责链会更灵活一些，因为装饰模式是在已有的功能上增加新的功能， **`多个装饰器之间会有一定的联系`** ；而职责链模式的各个职责对象实现的功能， **`相互之间是没有关联的，是自己实现属于自己处理的那一份功能`** 。

可能有些朋友会想到这很类似于在Web应用开发中的过滤器Filter，`没错，过滤器链就类似于一个功能链，每个过滤器负责自己的处理，然后转交给下一个过滤器，直到把所有的过滤器都走完，然后进入到Servlet里面进行处理`。最常见的过滤器功能，比如权限检查、字符集转换等，基本上都是Web应用的标配。

接下来在示例中，实现这样的功能：实现商品销售的业务处理，在真正进行销售的业务处理之前，需要对传入处理的数据，进行权限检查、通用数据检查和数据逻辑检查，只有这些检查都能通过的情况下，才说明传入的数据是正确的、有效的数据，才可以进行真正的业务功能处理。

* **`首先定义已有的业务功能和封装业务数据的对象，用前面出现过的那个保存销售信息的业务，为了简单，就不去定义接口了，示例代码如下：`** 


```java
/**
 * 商品销售管理模块的业务处理
 */
public class GoodsSaleEbo {
    /**
     * 保存销售信息，本来销售数据应该是多条，太麻烦了，为了演示，简单点
     * @param user 操作人员
     * @param customer 客户
     * @param saleModel 销售数据
     * @return 是否保存成功
     */
    public boolean sale(String user,String customer,SaleModel saleModel){
        //如果全部在这里处理，基本的顺序是
        //1：权限检查
        //2：通用数据检查（这个也可能在表现层已经作过了）
        //3：数据逻辑校验
     
        //4：真正的业务处理
     
        //但是现在通过功能链来做，这里就主要负责构建链
        //暂时还没有功能链，等实现好了各个处理对象再回来添加
        return true;
    }
}

```

对应的封装销售数据的对象，示例代码如下：

```java
/**
 * 封装销售单的数据，简单的示意一下
 */
public class SaleModel {
    /**
     * 销售的商品
     */
    private String goods;
    /**
     * 销售的数量
     */
    private int saleNum;
    public String getGoods() {
        return goods;
    }
    public void setGoods(String goods) {
        this.goods = goods;
    }
    public int getSaleNum() {
        return saleNum;
    }
    public void setSaleNum(int saleNum) {
        this.saleNum = saleNum;
    }
    public String toString(){
        return "商品名称="+goods+",销售数量="+saleNum;
    }
}

```

* **`定义一个用来处理保存销售数据功能的职责对象的接口，示例代码如下：`** 


```java
/**
 * 定义职责对象的接口
 */
public abstract class SaleHandler {
    /**
     * 持有下一个处理请求的对象
     */
    protected SaleHandler successor = null;
    /**
     * 设置下一个处理请求的对象
     * @param successor 下一个处理请求的对象
     */
    public void setSuccessor(SaleHandler successor){
        this.successor = successor;
    }
    /**
     * 处理保存销售信息的请求
     * @param user 操作人员
     * @param customer 客户
     * @param saleModel 销售数据
     * @return 是否处理成功
     */
    public abstract boolean sale(String user,String customer,SaleModel saleModel);
}

```

* **`实现各个职责处理对象，每个职责对象负责请求的一个方面的处理，把这些职责对象都走完了，功能也就实现完了。先定义处理安全检查的职责对象，示例代码如下：`** 


```java
/**
 * 进行权限检查的职责对象
 */
public class SaleSecurityCheck extends SaleHandler{
    public boolean sale(String user, String customer, SaleModel saleModel) {
        //进行权限检查，简单点，就小李能通过
        if("小李".equals(user)){
            return this.successor.sale(user, customer, saleModel);
        }else{
            System.out.println("对不起"+user+"，你没有保存销售信息的权限");
            return false;
        }     
    }
}

```

接下来定义通用数据检查的职责对象，示例代码如下：

```java
/**
 * 进行数据通用检查的职责对象
 */
public class SaleDataCheck extends SaleHandler{
    public boolean sale(String user, String customer, SaleModel saleModel) {
        //进行数据通用检查，稍麻烦点，每个数据都要检测
        if(user==null || user.trim().length()==0){
            System.out.println("申请人不能为空");
            return false;
        }
        if(customer==null || customer.trim().length()==0){
            System.out.println("客户不能为空");
            return false;
        }
        if(saleModel==null ){
            System.out.println("销售商品的数据不能为空");
            return false;
        }
        if(saleModel.getGoods() == null || saleModel.getGoods().trim().length()==0){
            System.out.println("销售的商品不能为空");
            return false;
        }
        if(saleModel.getSaleNum()==0){
            System.out.println("销售商品的数量不能为0");
            return false;
        }     
        //如果通过了上面的检测，那就向下继续执行
        return this.successor.sale(user, customer, saleModel);
     }
}

```

再看看进行数据逻辑检查的职责对象，示例代码如下：

```java
/**
 * 进行数据逻辑检查的职责对象
 */
public class SaleLogicCheck extends SaleHandler{
    public boolean sale(String user, String customer, SaleModel saleModel) {
        //进行数据的逻辑检查，比如检查ID的唯一性，主外键的对应关系等等
        //这里应该检查这种主外键的对应关系，比如销售商品是否存在
        //为了演示简单，直接通过吧
     
        //如果通过了上面的检测，那就向下继续执行
        return this.successor.sale(user, customer, saleModel);
    }
}

```

最后是真正的业务处理的职责对象，示例代码如下：

```java
/**
 * 真正处理销售的业务功能的职责对象
 */
public class SaleMgr extends SaleHandler{
    public boolean sale(String user, String customer, SaleModel saleModel) {
        //进行真正的业务逻辑处理
        System.out.println(user+"保存了"+customer+"购买 "+saleModel+" 的销售数据");
        return true;
    }
}

```

* **`实现好了各个职责对象处理，回过头来看看如何具体实现业务处理，在业务对象里面进行功能链的组合，示例代码如下：`** 


```java
public class GoodsSaleEbo {
    /**
     * 保存销售信息，本来销售数据应该是多条，太麻烦了，为了演示，简单点
     * @param user 操作人员
     * @param customer 客户
     * @param saleModel 销售数据
     * @return 是否保存成功
     */
    public boolean sale(String user,String customer,SaleModel saleModel){
        //如果全部在这里处理，基本的顺序是
        //1：权限检查
        //2：通用数据检查（这个也可能在表现层已经作过了）
        //3：数据逻辑校验
     
        //4：真正的业务处理
     
        //但是现在通过功能链来做，这里就主要负责构建链
        SaleSecurityCheck ssc = new SaleSecurityCheck();
        SaleDataCheck sdc = new SaleDataCheck();
        SaleLogicCheck slc = new SaleLogicCheck();
        SaleMgr sd = new SaleMgr();
        ssc.setSuccessor(sdc);
        sdc.setSuccessor(slc);
        slc.setSuccessor(sd);
        //向链上的第一个对象发出处理的请求
        return ssc.sale(user, customer, saleModel);
    }
}

```

* **`写个客户端，调用业务对象，测试一下看看，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //创建业务对象
        GoodsSaleEbo ebo = new GoodsSaleEbo();
        //准备测试数据
        SaleModel saleModel = new SaleModel();
        saleModel.setGoods("张学友怀旧经典");
        saleModel.setSaleNum(10);
     
        //调用业务功能
        ebo.sale("小李", "张三", saleModel);
        ebo.sale("小张", "李四", saleModel);
    }
}

```

运行一下，试试看，运行结果如下：

```java
小李保存了张三购买 商品名称=张学友怀旧经典,销售数量=10 的销售数据
对不起小张，你没有保存销售信息的权限

```
## 3.4 职责链模式的优缺点##

* **`请求者和接收者松散耦合`** 


在职责链模式里面，`请求者并不知道接收者是谁，也不知道具体如何处理，请求者只是负责向职责链发出请求就可以了`。而每个职责对象也不用管请求者或者是其它的职责对象，`只负责处理自己的部分，其它的就交由其它的职责对象去处理`。也就是说，请求者和接收者是完全解耦的。

* **`动态组合职责`** 


职责链模式会把功能处理分散到单独的职责对象里面，然后在使用的时候，可以动态组合职责形成职责链，从而可以灵活的给对象分配职责，也可以灵活的实现和改变对象的职责。

* **`产生很多细粒度对象`** 


职责链模式会把功能处理分散到单独的职责对象里面，也就是每个职责对象只是处理一个方面的功能，要把整个业务处理完，需要大量的职责对象的组合，这会产生大量的细粒度职责对象。

* **`不一定能被处理`** 


职责链模式的每个职责对象只负责自己处理的那一部分，因此可能会出现某个请求，把整个链传递完了，都没有职责对象处理它。`这就需要在使用职责链模式的时候注意，需要提供默认的处理，并且注意构建的链的有效性`。
## 3.5 思考职责链模式##

* **`职责链模式的本质`** 


`职责链模式的本质：分离职责，动态组合。`分离职责是前提，`只有先把复杂功能分开，拆分成很多的步骤和小的功能处理，然后才能合理规划和定义职责类`，可以有很多的职责类来负责处理某一个功能，让每个职责类负责处理功能的某一个方面，在运行期间进行动态组合，形成一个处理的链，把这个链运行完，那么功能也就处理完了。
`动态组合才是职责链模式的精华所在，因为要实现请求对象和处理对象的解耦，请求对象不知道谁才是真正的处理对象`，因此要动态的把可能的处理对象组合起来，由于组合的方式是动态的，这就意味着可以很方便的修改和添加新的处理对象，从而让系统更加灵活和具有更好的扩展性。

当然这么做还会有一个潜在的优点，就是可以增强职责功能的复用性。如果职责功能是很多地方都可以使用的公共功能，那么它可以应用在多个职责链中复用。

* **`何时选用职责链模式`** 


建议在如下情况中，选用职责链模式：

`如果有多个对象可以处理同一个请求，但是具体由哪个对象来处理该请求，是运行时刻动态确定的`。这种情况可以使用职责链模式，把处理请求的对象实现成为职责对象，然后把它们构成一个职责链，当请求在这个链中传递的时候，具体由哪个职责对象来处理，会在运行时动态判断。
`如果你想在不明确指定接收者的情况下，向多个对象中的一个提交一个请求的话，可以使用职责链模式`，职责链模式实现了请求者和接收者之间的解耦，请求者不需要知道究竟是哪一个接收者对象来处理了请求。
`如果想要动态指定处理一个请求的对象集合，可以使用职责链模式，职责链模式能动态的构建职责链`，也就是动态的来决定到底哪些职责对象来参与到处理请求中来，相当于是动态指定了处理一个请求的职责对象集合。

## 3.6 相关模式##

* **`职责链模式和组合模式`** 


这两个模式可以组合使用。
`可以把职责对象通过组合模式来组合`，这样可以通过组合对象自动递归的向上调用，由父组件作为子组件的后继，从而形成链。

这也就是前面提到过的使用外部已有的链接，这种情况在客户端使用的时候，就不用再构造链了，虽然不构造链，但是需要构造组合对象树，是一样的。

* **`职责链模式和装饰模式`** 


这两个模式相似，`从某个角度讲，可以相互模拟实现对方的功能`。
`装饰模式能够动态的给被装饰对象添加功能，要求装饰器对象和被装饰的对象实现相同的接口`。而`职责链模式可以实现动态的职责组合，标准的功能是有一个对象处理就结束，但是如果处理完本职责不急于结束，而是继续向下传递请求`，那么功能就和装饰模式的功能差不多了，每个职责对象就类似于装饰器，可以实现某种功能。

而且两个模式的本质也类似，`都需要在运行期间动态组合，装饰模式是动态组合装饰器，而职责链是动态组合处理请求的职责对象的链`。

但是从标准的设计模式上来讲，这两个模式还是有较大区别的，这点要注意。`首先是目的不同，装饰模式是要实现透明的为对象添加功能`，而`职责链模式是要实现发送者和接收者解耦`；另外一个，`装饰模式是无限递归调用的，可以有任意多个对象来装饰功能，但是职责链模式是有一个处理就结束`。

* **`职责链模式和策略模式`** 


这两个模式可以组合使用。

这两个模式有相似之处，`如果把职责链简化到直接就能选择到相应的处理对象，那就跟策略模式的选择差不多`，因此可以用职责链来模拟策略模式的功能。只是如果把职责链简化到这个地步，也就不存在链了，也就称不上是职责链了。

两个模式可以组合使用，`可以在职责链模式的某个职责的实现的时候，使用策略模式来选择具体的实现，同样也可以在策略模式的某个策略实现里面，使用职责链模式来实现功能处理`。

同理职责链模式也可以和状态模式组合使用。


[0]: ./img/2062729-149ee5326d700cdf.png
[1]: ./img/2062729-1616e8d61673643e.png
[2]: ./img/2062729-2be08de919550b8e.png
[3]: ./img/2062729-d6e7f1f399d46f07.png