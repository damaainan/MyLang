## 【行为型模式十九】访问者模式（Visitor）

2016.12.05 21:25*

来源：[https://www.jianshu.com/p/62289b9bcfcb](https://www.jianshu.com/p/62289b9bcfcb)


          
## 1 场景问题#
## 1.1 扩展客户管理的功能##

考虑这样一个应用：扩展客户管理的功能。

既然是扩展功能，那么肯定是已经存在一定的功能了，`先看看已有的功能：公司的客户分成两大类，一类是企业客户，一类是个人客户，现有的功能非常简单，就是能让客户提出服务申请`。目前的程序结构如图所示：


![][0]


已有的客户管理程序结构示意图


现有的实现很简单，先看看Customer的实现，示例代码如下：

```java
/**
 * 各种客户的父类
 */
public abstract class Customer {
    /**
     * 客户编号
     */
    private String customerId;
    /**
     * 客户名称
     */
    private String name;
 
    /**
     * 客户提出服务请求的方法，示意一下
     */
    public abstract void serviceRequest();
}

```

接下来看看企业客户的实现示例代码如下：

```java
/**
 * 企业客户
 */
public class EnterpriseCustomer extends Customer {
    /**
     * 联系人
     */
    private String linkman;
    /**
     * 联系电话
     */
    private String linkTelephone;
    /**
     * 企业注册地址
     */
    private String registerAddress;
 
    /**
     * 企业客户提出服务请求的方法，示意一下
     */
    public void serviceRequest(){
        //企业客户提出的具体服务请求
        System.out.println(this.getName()+"企业提出服务请求");
    }
}

```

再看看个人客户的实现示例代码如下：

```java
/**
 * 个人客户
 */
public class PersonalCustomer extends Customer{
    /**
     * 联系电话
     */
    private String telephone;
    /**
     * 年龄
     */
    private int age;
    /**
     * 企业注册地址
     */
    private String registerAddress;
 
    /**
     * 个人客户提出服务请求的方法，示意一下
     */
    public void serviceRequest(){
        //个人客户提出的具体服务请求
        System.out.println("客户"+this.getName()+"提出服务请求");
    }
}

```

从上面的实现可以看出来，以前对客户的管理功能是很少的，现在随着业务的发展，需要加强对客户管理的功能，假设现在需要增加如下的功能：

 **`客户对公司产品的偏好分析`** ，针对企业客户和个人客户有不同的分析策略，主要是根据以往购买的历史、潜在购买意向等进行分析，对于企业客户还要添加上客户所在行业的发展趋势、客户的发展预期等的分析。 **`客户价值分析`** ，针对企业客户和个人客户，有不同的分析方式和策略。主要是根据购买的金额大小、购买的产品和服务的多少、购买的频率等进行分析。

其实除了这些功能，还有很多潜在的功能，只是现在还没有要求实现，比如：针对不同的客户进行需求调查；针对不同的客户进行满意度分析；客户消费预期分析等等。虽然现在没有要求实现，但不排除今后有可能会要求实现。
## 1.2 不用模式的解决方案##

要实现上面要求的功能，也不是很困难，一个很基本的想法就是：既然不同类型的客户操作是不同的，那么在不同类型的客户里面分别实现这些功能，不就可以了。

由于这些功能的实现依附于很多其它功能的实现，或者是需要很多其它的业务数据，在示例里面不太好完整的体现其功能实现，都是示意一下，因此提前说明一下。

按照上述的想法，这个时候的程序结构如图所示：


![][1]


扩展客户管理功能的结构示意图


* **`先看看抽象的父类，主要就是加入了两个新的方法，示例代码如下：`** 


```java
public abstract class Customer {

    private String customerId;
   
    private String name;

    public abstract void serviceRequest();

    /**
     * 客户对公司产品的偏好分析，示意一下
     */
    public abstract void predilectionAnalyze();
    /**
     * 客户价值分析，示意一下
     */
    public abstract void worthAnalyze();
}

```

* **`接下来看看企业客户的示意实现，示例代码如下：`** 


```java
public class EnterpriseCustomer extends Customer {

    private String linkman;
    
    private String linkTelephone;
    
    private String registerAddress;

    public void serviceRequest(){
        //企业客户提出的具体服务请求
        System.out.println(this.getName()+"企业提出服务请求");
    }

    /**
     * 企业客户对公司产品的偏好分析，示意一下
     */
    public void predilectionAnalyze(){
        //根据过往购买的历史、潜在购买意向
        //以及客户所在行业的发展趋势、客户的发展预期等的分析
        System.out.println("现在对企业客户"+this.getName()+"进行产品偏好分析");
    }

    /**
     * 企业客户价值分析，示意一下
     */
    public void worthAnalyze(){
        //根据购买的金额大小、购买的产品和服务的多少、购买的频率等进行分析
        //企业客户的标准会比个人客户的高
        System.out.println("现在对企业客户"+this.getName()+"进行价值分析");
    }
}

```

* **`接下来看看个人客户的示意实现，示例代码如下：`** 


```java
public class PersonalCustomer extends Customer{
    
    private String telephone;
   
    private int age;
  
    public void serviceRequest(){
        //个人客户提出的具体服务请求
        System.out.println("客户"+this.getName()+"提出服务请求");
    }

    /**
     * 个人客户对公司产品的偏好分析，示意一下
     */
    public void predilectionAnalyze(){
        System.out.println("现在对个人客户"+this.getName()+"进行产品偏好分析");
    }

    /**
     * 个人客户价值分析，示意一下
     */
    public void worthAnalyze(){
        System.out.println("现在对个人客户"+this.getName()+"进行价值分析");
    }
}

```

* **`如何使用上面实现的功能呢，写个客户端来测试一下，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //准备点测试数据
        Collection<Customer> colCustomer = preparedTestData();
        //循环对客户进行操作
        for(Customer cm : colCustomer){
            //进行偏好分析
            cm.predilectionAnalyze();
            //进行价值分析
            cm.worthAnalyze();
        }
    }
    private static Collection<Customer> preparedTestData(){
        Collection<Customer> colCustomer = new ArrayList<Customer>();
        //为了测试方便，准备点数据
        Customer cm1 = new EnterpriseCustomer();
        cm1.setName("ABC集团");
        colCustomer.add(cm1);
     
        Customer cm2 = new EnterpriseCustomer();
        cm2.setName("CDE公司");
        colCustomer.add(cm2);
     
        Customer cm3 = new PersonalCustomer();
        cm3.setName("张三");
        colCustomer.add(cm3);
     
        return colCustomer;
    }
}

```

运行结果如下：

```java
现在对企业客户ABC集团进行产品偏好分析
现在对企业客户ABC集团进行价值分析
现在对企业客户CDE公司进行产品偏好分析
现在对企业客户CDE公司进行价值分析
现在对个人客户张三进行产品偏好分析
现在对个人客户张三进行价值分析

```
## 1.3 有何问题##

以很简单的方式，实现了要求的功能，这种实现有没有什么问题呢？仔细分析上面的实现，发现有两个主要的问题：

在企业客户和个人客户的类里面，都分别实现了提出服务请求、进行产品偏好分析、进行客户价值分析等功能，也就是说，`这些功能的实现代码是混杂在同一个类里面的`；`而且相同的功能分散到了不同的类中去实现，这会导致整个系统难以理解、难以维护`。

更为痛苦的是，采用这样的实现方式，如果要给客户扩展新的功能，比如前面提到的针对不同的客户进行需求调查；针对不同的客户进行满意度分析；客户消费预期分析等等。`每次扩展，都需要改动企业客户的类和个人客户的类`，当然`也可以通过为它们扩展子类的方式，但是这样可能会造成过多的对象层次`。

那么有没有办法，能够在不改变客户这个对象结构中各元素类的前提下，为这些类定义新的功能？也就是要求不改变企业客户和个人客户类，就能为企业客户和个人客户类定义新的功能？
## 2 解决方案#
## 2.1 访问者模式来解决##

用来解决上述问题的一个合理的解决方案，就是使用访问者模式。那么什么是访问者模式呢？

* **`访问者模式定义`** 



![][2]


访问者模式定义


* **`应用访问者模式来解决的思路`** 


仔细分析上面的示例，对于客户这个对象结构，不想改变类，又要添加新的功能， **`很明显就需要一种动态的方式，在运行期间把功能动态地添加到对象结构中去。`** 

有些朋友可能会想起装饰模式， **`装饰模式可以实现为一个对象透明的添加功能，但装饰模式基本上是在现有的功能的基础之上进行功能添加，实际上是对现有功能的加强或者改造。`** 并不是在现有功能不改动的情况下，为对象添加新的功能。

看来需要另外寻找新的解决方式了，可以应用访问者模式来解决这个问题，访问者模式实现的基本思路如下：

 **`首先定义一个接口来代表要新加入的功能`** ，为了通用，也就是定义一个通用的功能方法来代表新加入的功能； **`然后在对象结构上添加一个方法`** ，作为通用的功能方法，也就是可以代表被添加的功能，在这个方法中传入具体的实现新功能的对象； **`然后在对象结构的具体实现对象里面实现这个方法`** ，回调传入具体的实现新功能的对象，就相当于调用到新功能上了； **`接下来的步骤就是提供实现新功能的对象`** ； **`最后再提供一个能够循环访问整个对象结构的类`** ，让这个类来提供符合客户端业务需求的方法，来满足客户端调用的需要；

这样一来， **`只要提供实现新功能的对象给对象结构，就可以为这些对象添加新的功能`** ，由于在对象结构中定义的方法是通用的功能方法，所以什么新功能都可以加入。
## 2.2 模式结构和说明##

访问者模式的结构如图所示：


![][3]


访问者模式结构示意图


 **`Visitor：访问者接口`** ，为所有的访问者对象声明一个visit方法，`用来代表为对象结构添加的功能，理论上可以代表任意的功能`。 **`ConcreteVisitor：具体的访问者实现对象`** ，`实现要真正被添加到对象结构中的功能`。 **`Element：抽象的元素对象`** ，对象结构的顶层接口，定义接受访问的操作。 **`ConcreteElement：具体元素对象，对象结构中具体的对象`** ，也是被访问的对象，通常会回调访问者的真实功能，同时开放自身的数据供访问者使用。 **`ObjectStructure：对象结构，通常包含多个被访问的对象`** ，它可以遍历这多个被访问的对象，也可以让访问者访问它的元素。可以是一个复合或是一个集合，如一个列表或无序集合。

但是请注意：这个ObjectStructure并不是我们在前面讲到的对象结构，`前面一直讲的对象结构是指的一系列对象的定义结构，是概念上的东西`；`而ObjectStructure可以看成是对象结构中的一系列对象的一个集合，是用来辅助客户端访问这一系列对象的`，所以为了不造成大家的困惑，后面提到ObjectStructure的时候，就用英文名称来代替，不把它翻译成中文。
## 2.3 访问者模式示例代码##

* **``首先需要定义一个接口来代表要新加入的功能，把它称作访问者，访问谁呢？当然是访问对象结构中的对象了`。既然是访问，不能空手而去吧，这些访问者在进行访问的时候，就会携带新的功能，也就是说，`访问者携带着需要添加的新的功能去访问对象结构中的对象，就相当于给对象结构中的对象添加了新的功能`。示例代码如下：`** 


```java
/**
 * 访问者接口
 */
public interface Visitor {
    /**
     * 访问元素A，相当于给元素A添加访问者的功能
     * @param elementA 元素A的对象
     */
    public void visitConcreteElementA(ConcreteElementA elementA);
    /**
     * 访问元素B，相当于给元素B添加访问者的功能
     * @param elementB 元素B的对象
     */
    public void visitConcreteElementB(ConcreteElementB elementB);
}

```

* **`看看抽象的元素对象定义，示例代码如下：`** 


```java
/**
 * 被访问的元素的接口
 */
public abstract class Element {
    /**
     * 接受访问者的访问
     * @param visitor 访问者对象
     */
    public abstract void accept(Visitor visitor);
}

```

* **`接下来看看元素对象的具体实现，先看元素A的实现，示例代码如下：`** 


```java
/**
 * 具体元素的实现对象
 */
public class ConcreteElementA extends Element {
    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitConcreteElementA(this);
    }
    /**
     * 示例方法，表示元素已有的功能实现
     */
    public void opertionA(){
        //已有的功能实现
    }
}

```

再看看元素B的实现，示例代码如下：

```java
/**
 * 具体元素的实现对象
 */
public class ConcreteElementB extends Element {
    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitConcreteElementB(this);
    }
    /**
     * 示例方法，表示元素已有的功能实现
     */
    public void opertionB(){
        //已有的功能实现
    }
}

```

* **`接下来看看访问者的具体实现，先看访问者1的实现，示例代码如下：`** 


```java
/**
 * 具体的访问者实现
 */
public class ConcreteVisitor1 implements Visitor {
    public void visitConcreteElementA(ConcreteElementA element) {
        //把去访问ConcreteElementA时，需要执行的功能实现在这里
        //可能需要访问元素已有的功能，比如：
        element.opertionA();
    }
    public void visitConcreteElementB(ConcreteElementB element) {
        //把去访问ConcreteElementB时，需要执行的功能实现在这里
        //可能需要访问元素已有的功能，比如：
        element.opertionB();
    }
}

```

* **`该来看看ObjectStructure的实现了，示例代码如下：`** 


```java
/**
 * 对象结构,通常在这里对元素对象进行遍历，让访问者能访问到所有的元素
 */
public class ObjectStructure {
    /**
     * 示意，表示对象结构，可以是一个组合结构或是集合
     */
    private Collection<Element> col = new ArrayList<Element>();
    /**
     * 示意方法，提供给客户端操作的高层接口
     * @param visitor 客户端需要使用的访问者
     */
    public void handleRequest(Visitor visitor){
        //循环对象结构中的元素，接受访问
        for(Element ele : col){
            ele.accept(visitor);
        }
    }
    /**
     * 示意方法，组建对象结构，向对象结构中添加元素。
     * 不同的对象结构有不同的构建方式
     * @param ele 加入到对象结构的元素
     */
    public void addElement(Element ele){
        this.col.add(ele);
    }
}

```

* **`接下来看看客户端的示意实现，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //创建ObjectStructure
        ObjectStructure os = new ObjectStructure();
        //创建要加入对象结构的元素
        Element eleA = new ConcreteElementA();
        Element eleB = new ConcreteElementB();
        //把元素加入对象结构
        os.addElement(eleA);
        os.addElement(eleB);    
        //创建访问者
        Visitor visitor = new ConcreteVisitor1();    
        //调用业务处理的方法
        os.handleRequest(visitor);     
    }
}

```
## 2.4 使用访问者模式重写示例##

要使用访问者模式来重写示例，首先就要按照访问者模式的结构，分离出两个类层次来，`**一个是对应于元素的类层次，一个是对应于访问者的类层次**`。
`对于对应于元素的类层次，现在已经有了，就是客户的对象层次`。`而对应于访问者的类层次，现在还没有，不过，按照访问者模式的结构`，应该是先定义一个访问者接口，然后把每种业务实现成为一个单独的访问者对象，也就是说应该使用一个访问者对象来实现对客户的偏好分析，而用另外一个访问者对象来实现对客户的价值分析。

在分离好两个类层次过后，`为了方便客户端的访问，定义一个ObjectStructure，其实就类似于前面示例中的客户管理的业务对象`。新的示例的结构如图所示：


![][4]


新的示例的结构如图所示


仔细查看图所示的程序结构示意图，细心的朋友会发现，`在图上没有出现对客户进行价值分析的功能了`。这是`为了示范“使用访问者模式来实现示例功能过后，可以很容易的给对象结构增加新的功能”，所以先不做这个功能，等都实现好了，再来扩展这个功能`。接下来还是看看代码实现，以更好的体会访问者模式。

* **`先来看看Customer的代码，Customer相当于访问者模式中的Element，它的实现跟以前相比有如下的改变：`** 


新增一个接受访问者访问的方法；

把能够分离出去放到访问者中实现的方法，从Customer中删除掉，包括：客户提出服务请求的方法、对客户进行偏好分析的方法、对客户进行价值分析的方法等；

示例代码如下：

```java
public abstract class Customer {

    private String customerId;
   
    private String name;
   
    /**
     * 接受访问者的访问
     * @param visitor 访问者对象
     */
    public abstract void accept(Visitor visitor);
}

```

* **`看看两种客户的实现，先看企业客户的实现，示例代码如下：`** 


```java
public class EnterpriseCustomer extends Customer{
    
    private String linkman;
    
    private String linkTelephone;
    
    private String registerAddress;

    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitEnterpriseCustomer(this);
    }
}

```

再看看个人客户的实现，示例代码如下：

```java
public class PersonalCustomer extends Customer{
   
    private String telephone;
    
    private int age;
  
    public void accept(Visitor visitor) {
       //回调访问者对象的相应方法
       visitor.visitPersonalCustomer(this);
    }
}

```

* **`看看访问者的接口定义，示例代码如下：`** 


```java
/**
 * 访问者接口
 */
public interface Visitor {
    /**
     * 访问企业客户，相当于给企业客户添加访问者的功能
     * @param ec 企业客户的对象
     */
    public void visitEnterpriseCustomer(EnterpriseCustomer ec);
    /**
     * 访问个人客户，相当于给个人客户添加访问者的功能
     * @param pc 个人客户的对象
     */
    public void visitPersonalCustomer(PersonalCustomer pc);
}

```

* **`接下来看看各个访问者的实现，每个访问者对象负责一类的功能处理，先看实现客户提出服务请求的功能的访问者，示例代码如下：`** 


```java
/**
 * 具体的访问者，实现客户提出服务请求的功能
 */
public class ServiceRequestVisitor implements Visitor {
    
    public void visitEnterpriseCustomer(EnterpriseCustomer ec){
        //企业客户提出的具体服务请求
        System.out.println(ec.getName()+"企业提出服务请求");
    }

    public void visitPersonalCustomer(PersonalCustomer pc){
        //个人客户提出的具体服务请求
        System.out.println("客户"+pc.getName()+"提出服务请求");
    }
}

```

接下来看看实现对客户偏好分析功能的访问者，示例代码如下：

```java
/**
 * 具体的访问者，实现对客户的偏好分析
 */
public class PredilectionAnalyzeVisitor implements Visitor {
    
    public void visitEnterpriseCustomer(EnterpriseCustomer ec){
        //根据过往购买的历史、潜在购买意向
        //以及客户所在行业的发展趋势、客户的发展预期等的分析
        System.out.println("现在对企业客户"+ec.getName()+"进行产品偏好分析");
    }
   
    public void visitPersonalCustomer(PersonalCustomer pc){
        System.out.println("现在对个人客户"+pc.getName()+"进行产品偏好分析");
    }
}

```

* **`接下来看看ObjectStructure的实现，示例代码如下：`** 


```java
public class ObjectStructure {
    /**
     * 要操作的客户集合
     */
    private Collection<Customer> col = new ArrayList<Customer>();
    /**
     * 提供给客户端操作的高层接口，具体的功能由客户端传入的访问者决定
     * @param visitor 客户端需要使用的访问者
     */
    public void handleRequest(Visitor visitor){
        //循环对象结构中的元素，接受访问
        for(Customer cm : col){
            cm.accept(visitor);
        }
    }
    /**
     * 组建对象结构，向对象结构中添加元素。
     * 不同的对象结构有不同的构建方式
     * @param ele 加入到对象结构的元素
     */
    public void addElement(Customer ele){
        this.col.add(ele);
    }
}

```

* **`该来写个客户端测试一下了，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //创建ObjectStructure
        ObjectStructure os = new ObjectStructure();
        //准备点测试数据，创建客户对象，并加入ObjectStructure
        Customer cm1 = new EnterpriseCustomer();
        cm1.setName("ABC集团");
        os.addElement(cm1);
     
        Customer cm2 = new EnterpriseCustomer();
        cm2.setName("CDE公司");
        os.addElement(cm2);
     
        Customer cm3 = new PersonalCustomer();
        cm3.setName("张三");
        os.addElement(cm3);
     
        //客户提出服务请求，传入服务请求的Visitor
        ServiceRequestVisitor srVisitor = new ServiceRequestVisitor();
        os.handleRequest(srVisitor);
     
        //要对客户进行偏好分析，传入偏好分析的Visitor
        PredilectionAnalyzeVisitor paVisitor = new PredilectionAnalyzeVisitor();
        os.handleRequest(paVisitor);
    }
}

```

运行结果如下：

```java
ABC集团企业提出服务请求
CDE公司企业提出服务请求
客户张三提出服务请求
现在对企业客户ABC集团进行产品偏好分析
现在对企业客户CDE公司进行产品偏好分析
现在对个人客户张三进行产品偏好分析

```

* **`使用访问者模式来重新实现了前面示例的功能，把各类相同的功能放到单独的访问者对象里面，`使得代码不再杂乱，系统结构也更清晰，能方便的维护了`，算是解决了前面示例的一个问题。`** 

`还有一个问题，就是看看能不能方便的增加新的功能`，前面在示例的时候，故意留下了一个对客户进行价值分析的功能没有实现，那么接下来就看看如何把这个功能增加到已有的系统中。在访问者模式中要给对象结构增加新的功能，只需要把新的功能实现成为访问者，然后在客户端调用的时候使用这个访问者对象来访问对象结构即可。

接下来看看实现对客户价值分析功能的访问者，示例代码如下：

```java
/**
 * 具体的访问者，实现对客户价值分析
 */
public class WorthAnalyzeVisitor implements Visitor {
    public void visitEnterpriseCustomer(EnterpriseCustomer ec){
        //根据购买的金额大小、购买的产品和服务的多少、购买的频率等进行分析
        //企业客户的标准会比个人客户的高
        System.out.println("现在对企业客户"+ec.getName()+"进行价值分析");
    }
   
    public void visitPersonalCustomer(PersonalCustomer pc){
        System.out.println("现在对个人客户"+pc.getName()+"进行价值分析");
    }
}

```

使用这个功能，只要在客户端添加如下的代码即可，示例代码如下：

```java
//要对客户进行价值分析，传入价值分析的Visitor
WorthAnalyzeVisitor waVisitor = new WorthAnalyzeVisitor();
os.handleRequest(waVisitor);

```
## 3 模式讲解#
## 3.1 认识访问者模式##

* **`访问者的功能`** 

`访问者模式能给一系列对象，透明的添加新功能`。从而避免在维护期间，对这一系列对象进行修改，而且`还能变相实现复用访问者所具有的功能`。

由于是针对一系列对象的操作，这也导致，如果只想给一系列对象中的部分对象添加功能，就会有些麻烦；而且要始终能保证把这一系列对象都要调用到，不管是循环也好，还是递归也好，总之要让每个对象都要被访问到。

* **`调用通路`** 


访问者之所以能实现“为一系列对象透明的添加新功能”，`注意是透明的，也就是这一系列对象是不知道被添加功能的`。
`重要的就是依靠通用方法`，访问者这边说要去访问，就提供一个访问的方法，如visit方法；而对象那边说，好的，我接受你的访问，提供一个接受访问的方法，如accept方法。这两个方法并不代表任何具体的功能，只是构成一个调用的通路，那么真正的功能实现在哪里呢？又如何调用到呢？

很简单，`就在accept方法里面，回调visit的方法，从而回调到访问者的具体实现上，而这个访问者的具体实现的方法才是要添加的新的功能`。

* **`两次分发技术`** 


访问者模式能够实现在不改变对象结构的情况下，就能给对象结构中的类增加功能，`实现这个效果所使用的核心技术就是两次分发的技术`。

在访问者模式中，当客户端调用ObjectStructure的时候，会遍历ObjectStructure中所有的元素，`调用这些元素的accept方法，让这些元素来接受访问，这是请求的第一次分发`；

在具体的元素对象中实现accept方法的时候，`会回调访问者的visit方法，等于请求被第二次分发了`，请求被分发给访问者来进行处理，真正实现功能的正是访问者的visit方法；

两次分发技术具体的调用过程示意如图所示：


![][5]


两次分发

`两次分发技术使得客户端的请求不再被静态的绑定在元素对象上`，这个时候真正执行什么样的功能同时取决于访问者类型和元素类型，就算是同一种元素类型，只要访问者类型不一样，最终执行的功能也不会一样，这样一来，就可以在元素对象不变的情况下，通过改变访问者的类型，来改变真正执行的功能。
`两次分发技术还有一个优点，就是可以在程序运行期间进行动态的功能组装和切换，只需要在客户端调用时，组合使用不同的访问者对象实例即可。`从另一个层面思考，`Java回调技术也有点类似于两次分发技术，客户端调用某方法，这个方法就类似于accept方法，传入一个接口的实现对象，这个接口的实现对象就有点像是访问者，在方法内部，会回调这个接口的方法，就类似于调用访问者的visit方法，最终执行的还是接口的具体实现里面实现的功能`。

* **`为何不在Component中实现回调visit方法`** 


在看上面的示例的时候，细心的朋友会发现，在企业客户对象和个人客户对象中实现的accept方法从表面上看是相似的，都需要回调访问者的方法，可能就会有朋友想，为什么不把回调访问者方法的调用语句放到父类中去，那样不就可以复用了吗？

请注意，这是不可以的，虽然看起来是相似的语句，但其实是不同的，`主要的玄机就在传入的this身上`。this是代表当前的对象实例的，在企业客户对象中传递的就是企业客户对象的实例，在个人客户对象中传递的就是个人客户对象的实例，这样在访问者的实现中，就可以通过这不同的对象实例来访问不同的实例对象的数据了。
`如果把这句话放到父类中，那么传递的就是父类对象的实例，是没有子对象的数据的，因此这句话不能放到父类中去。`

* **`访问者模式的调用顺序示意图`** 


访问者模式的调用顺序如图所示：


![][6]


访问者模式的调用顺序


* **`空的访问方法`** 

`并不是所有的访问方法都需要实现，由于访问者模式默认的是访问对象结构中的所有元素`，因此在实现某些功能的时候，如果不需要涉及到某些元素的访问方法，这些方法可以实现成为空的，比如：这个访问者只想要处理组合对象 ，那么访问叶子对象的方法就可以为空，虽然还是需要访问所有的元素对象。
`还有一种就是有条件接受访问`，在自己的accept方法里面进行判断，满足要求的接受，不满足要求的，就相当于空的访问方法，什么都不用做。
## 3.2 操作组合对象结构##
`访问者模式一个很常见的应用，就是和组合模式结合使用，通过访问者模式来给由组合模式构建的对象结构增加功能。`对于使用组合模式构建的组合对象结构，对外有一个统一的外观，要想添加新的功能也不是很困难，只要在组件的接口上定义新的功能就可以了，麻烦的是这样一来，需要修改所有的子类。而且，每次添加一个新功能，都需要这么痛苦一回，修改组件接口，然后修改所有的子类，这是相当糟糕的。
`为了让组合对象结构更灵活、更容易维护和更好的扩展性，接下来把它改造成访问者模式和组合模式组合来实现`。这样在今后再进行功能改造的时候，就不需要再改动这个组合对象结构了。
`访问者模式和组合模式组合使用的思路：`首先把组合对象结构中的功能方法分离出来，虽然维护组合对象结构的方法也可以分离出来，但是为了维持组合对象结构本身，这些方法还是放在组合对象结构里面；然后把这些功能方法分别实现成为访问者对象，通过访问者模式添加到组合的对象结构中去。

下面通过访问者模式和组合模式组合来实现如下功能：输出对象的名称，在组合对象的名称前面添加“节点：”，在叶子对象的名称前面添加“叶子：”。

* **`先来定义访问者接口`** 


访问者接口非常简单，只需要定义访问对象结构中不同对象的方法，示例代码如下：

```java
/**
 * 访问组合对象结构的访问者接口
 */
public interface Visitor {
    /**
     * 访问组合对象，相当于给组合对象添加访问者的功能
     * @param composite 组合对象
     */
    public void visitComposite(Composite composite);
    /**
     * 访问叶子对象，相当于给叶子对象添加访问者的功能
     * @param leaf 叶子对象
     */
    public void visitLeaf(Leaf leaf);
}

```

* **`改造组合对象的定义`** 


然后来对已有的组合对象进行改造，添加通用的功能方法，当然在参数上需要传入访问者。先在组件定义上添加这个方法，然后到具体的实现类里面去实现。除了新加这个方法外，组件定义没有其它改变，示例代码如下：

```java
/**
 * 抽象的组件对象，相当于访问者模式中的元素对象
 */
public abstract class Component {
    /**
     * 接受访问者的访问
     * @param visitor 访问者对象
     */
    public abstract void accept(Visitor visitor);
    /**
     * 向组合对象中加入组件对象
     * @param child 被加入组合对象中的组件对象
     */
    public void addChild(Component child) {
        // 缺省实现，抛出例外，叶子对象没这个功能，或子组件没有实现这个功能
        throw new UnsupportedOperationException("对象不支持这个功能");
    }
    /**
     * 从组合对象中移出某个组件对象
     * @param child 被移出的组件对象
     */
    public void removeChild(Component child) {
        // 缺省实现，抛出例外，叶子对象没这个功能，或子组件没有实现这个功能
        throw new UnsupportedOperationException("对象不支持这个功能");
    }
    /**
     * 返回某个索引对应的组件对象
     * @param index 需要获取的组件对象的索引，索引从0开始
     * @return 索引对应的组件对象
     */
    public Component getChildren(int index) {
        throw new UnsupportedOperationException("对象不支持这个功能");
    }
}

```

* **`实现组合对象和叶子对象`** 


改变了组件定义，`那么需要在组合类和叶子类上分别实现这个方法，组合类中实现的时候，通常会循环让所有的子元素都接受访问，这样才能为所有的对象都添加上新的功能`，示例代码如下：

```java
/**
 * 组合对象，可以包含其它组合对象或者叶子对象，
 * 相当于访问者模式的具体Element实现对象
 */
public class Composite extends Component{
    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitComposite(this);
        //循环子元素，让子元素也接受访问
        for(Component c : childComponents){
            //调用子对象接受访问，变相实现递归
            c.accept(visitor);
        }
    }
    /**
     * 用来存储组合对象中包含的子组件对象
     */
    private List<Component> childComponents = new ArrayList<Component>();
    /**
     * 组合对象的名字
     */
    private String name = "";
    /**
     * 构造方法，传入组合对象的名字
     * @param name 组合对象的名字
     */
    public Composite(String name){
        this.name = name;
    }
    public void addChild(Component child) {
        childComponents.add(child);
    }
    public String getName() {
        return name;
    }
}

```

叶子对象的基本实现，示例代码如下：

```java
/**
 * 叶子对象，相当于访问者模式的具体Element实现对象
 */
public class Leaf extends Component{
    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitLeaf(this);
    }
    /**
     * 叶子对象的名字
     */
    private String name = "";
    /**
     * 构造方法，传入叶子对象的名字
     * @param name 叶子对象的名字
     */
    public Leaf(String name){
        this.name = name;
    }
    public String getName() {
        return name;
    }
}

```

* **`实现一个访问者`** 


组合对象结构已经改造好了，现在需要提供一个访问者的实现，它会实现真正的功能，也就是要添加到对象结构中的功能。示例代码如下：

```java
/**
 * 具体的访问者，实现：输出对象的名称，在组合对象的名称前面添加"节点："，
 * 在叶子对象的名称前面添加"叶子："
 */
public class PrintNameVisitor implements Visitor {
    public void visitComposite(Composite composite) {
        //访问到组合对象的数据
        System.out.println("节点："+composite.getName());
    }
    public void visitLeaf(Leaf leaf) {
        //访问到叶子对象的数据     
        System.out.println("叶子："+leaf.getName());
    }
}

```

* **`访问所有元素对象的对象——ObjectStructure`** 

`访问者是给一系列对象添加功能的，因此一个访问者需要访问所有的对象`，为了方便遍历整个对象结构，通常会定义一个专门的类出来，在这个类里面进行元素迭代访问，同时这个类提供客户端访问元素的接口。

对于这个示例，由于在组合对象结构里面，已经实现了对象结构的遍历，本来是可以不需要这个ObjectStructure的，但是为了更清晰的展示访问者模式的结构，也为了今后的扩展或实现方便，还是定义一个ObjectStructure。示例代码如下：

```java
/**
 * 对象结构,通常在这里对元素对象进行遍历，让访问者能访问到所有的元素
 */
public class ObjectStructure {
    /**
     * 表示对象结构，可以是一个组合结构
     */
    private Component root = null;
    /**
     * 提供给客户端操作的高层接口
     * @param visitor 客户端需要使用的访问者
     */
    public void handleRequest(Visitor visitor){
        //让组合对象结构中的根元素，接受访问
        //在组合对象结构中已经实现了元素的遍历
        if(root!=null){
            root.accept(visitor);
        }
    }
    /**
     * 传入组合对象结构
     * @param ele 组合对象结构
     */
    public void setRoot(Component ele){
        this.root = ele;
    }
}

```

* **`写个客户端，来看看如何通过访问者去为对象结构添加新的功能，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //定义所有的组合对象
        Component root = new Composite("服装");
        Component c1 = new Composite("男装");
        Component c2 = new Composite("女装");
        //定义所有的叶子对象
        Component leaf1 = new Leaf("衬衣");
        Component leaf2 = new Leaf("夹克");
        Component leaf3 = new Leaf("裙子");
        Component leaf4 = new Leaf("套装");
        //按照树的结构来组合组合对象和叶子对象
        root.addChild(c1);
        root.addChild(c2);
     
        c1.addChild(leaf1);
        c1.addChild(leaf2);
     
        c2.addChild(leaf3);
        c2.addChild(leaf4);
     
        //创建ObjectStructure
        ObjectStructure os = new ObjectStructure();
        os.setRoot(root);
     
        //调用ObjectStructure来处理请求功能
        Visitor psVisitor = new PrintNameVisitor();
        os.handleRequest(psVisitor);
    }
}

```

输出的效果如下：

```java
节点：服装
节点：男装
叶子：衬衣
叶子：夹克
节点：女装
叶子：裙子
叶子：套装

```

看看结果，是不是期望的那样呢？

好好体会一下，想想访问者模式是如何实现动态的给组件添加功能的？尤其是要想想，实现的机制是什么？真正实现新功能的地方在哪里？

* **`现在的程序结构`** 


前面是分步的示范，大家已经体会了一番，接下来小结一下。

如同前面的示例，`访问者的方法就相当于作用于组合对象结构中各个元素的操作，是一种通用的表达，同样的访问者接口和同样的方法，只要提供不同的访问者具体实现，就表示不同的功能`。

同时在组合对象中，接受访问的方法，也是一个通用的表达，不管你是什么样的功能，统统接受就好了，然后回调回去执行真正的功能。这样一来，各元素的类就不用再修改了，`只要提供不同的访问者实现，然后通过这个通用表达，就结合到组合对象中来了，就相当于给所有的对象提供了新的功能`。

示例的整体结构，如图所示：


![][7]


访问者模式结合组合模式的示例的结构示意图

## 3.3 谁负责遍历所有元素对象##

在访问者模式中，`访问者必须要能够访问到对象结构中的每个对象，因为访问者要为每个对象添加功能`，为此特别在模式中定义出一个ObjectStructure来，然后由ObjectStructure来负责遍历访问一系列对象中的每个对象。

* **`在ObjectStructure迭代所有的元素时，又分成两种情况。`** 


`一种是元素的对象结构是通过集合来组织的，那么直接在ObjectStructure中对集合进行迭代`，对每一个元素调用accept就好了。
`另一种情况是元素的对象结构是通过组合模式来组织的，通常可以构成对象树，这种情况一般就不需要在ObjectStructure中迭代了`，而通常的做法是在组合对象的accept方法里面，递归遍历它的子元素，然后调用子元素的accept方法。

* **`不需要ObjectStructure的时候`** 


在实际开发中，`有一种典型的情况可以不需要ObjectStructure对象，那就是只有一个被访问对象的时候`。只有一个被访问对象，当然就不需要使用ObjectStructure来组合和迭代了，只要调用这个对象就好了。

事实上还有一种情况也可以不使用ObjectStructure，比如上面访问的组合对象结构，从客户端的角度看，他访问的其实就是一个对象，因此可以把ObjectStructure去掉，然后直接从客户端调用元素的accept方法。

还是通过示例来说明，`先把ObjectStructure类去掉，由于没有了ObjectStructure，那么客户端调用的时候就直接调用组合对象结构的根元素的accept方法`，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        //定义组件数据，组装对象树，跟刚才的测试一样，这里就省略了 

        Visitor psVisitor = new PrintNameVisitor();
        root.accept(psVisitor);
    }
}

```

* **`有些时候，`遍历元素的方法也可以放到访问者当中去，当然也是需要递归遍历它的子元素的`。出现这种情况的主要原因是：想在访问者中实现特别复杂的遍历，访问者的实现依赖于对象结构的操作结果。`** 


使用访问者模式和组合模式组合来实现了输出名称的功能，如果现在要实现把组合的对象结构按照树的形式输出，就是按照在组合模式中示例的那样，输出如下的树形结构：

```java
+服装
+男装
 -衬衣
 -夹克
+女装
 -裙子
 -套装

```
`要实现这个功能，在组合对象结构中去遍历子对象的方式就比较难于实现，因为要输出这个树形结构，需要控制每个对象在输出的时候，向后的退格数量，这个需要在对象结构的循环中来控制，这种功能可以选择在访问者当中去遍历对象结构。`来改造上面的示例，看看通过访问者来遍历元素如何实现这样的功能。

首先在Composite的accept实现中去除掉递归调用子对象的代码，同时添加一个让访问者访问到其所包含的子对象的方法，示例代码如下：

```java
public class Composite extends Component {
    //其它相同部分就省略了，只看变化的方法
    public void accept(Visitor visitor) {
        //回调访问者对象的相应方法
        visitor.visitComposite(this);
        // for(Component c : childComponents) {
        //    // 调用子对象接受访问，变相实现递归
        //    c.accept(visitor);
        // }
    }
    public List<Component> getChildComponents() {
        return childComponents;
    }
}

```

然后新实现一个访问者对象，在相应的visit实现里面，添加递归迭代所有子对象，示例代码如下：

```java
/**
 * 具体的访问者，实现：输出组合对象自身的结构
 */
public class PrintStructVisitor implements Visitor {
    /**
     * 用来累计记录对象需要向后退的格
     */
    private String preStr = "";
    public void visitComposite(Composite composite) {
        //先把自己输出去
        System.out.println(preStr+"+"+composite.getName());
        //如果还包含有子组件，那么就输出这些子组件对象
        if(composite.getChildComponents()!=null){
            //然后添加一个空格，表示向后缩进一个空格
            preStr+=" ";     
            //输出当前对象的子对象了
            for(Component c : composite.getChildComponents()){
                //递归输出每个子对象
                c.accept(this);
            }
            //把循环子对象所多加入的一个退格给去掉
            preStr = preStr.substring(0,preStr.length()-1);
        }
    }
    public void visitLeaf(Leaf leaf) {
        //访问到叶子对象的数据     
        System.out.println(preStr+"-"+leaf.getName());
    }
}

```

写个客户端来测试一下看看，是否能实现要求的功能。示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        //定义所有的组合对象过程跟上一个client是一样的，这里省略了   
        //调用根元素的方法来接受请求功能
        Visitor psVisitor = new PrintStructVisitor();
        root.accept(psVisitor);
    }
}

```
## 3.4 访问者模式优缺点##

* **`好的扩展性`** 


能够在不修改对象结构中的元素的情况下，给对象结构中的元素添加新的功能。

* **`好的复用性`** 


可以通过访问者来定义整个对象结构通用的功能，从而提高复用程度。

* **`分离无关行为`** 


可以通过访问者来分离无关的行为，把相关的行为封装在一起，构成一个访问者，这样每一个访问者的功能都比较单一。

* **`对象结构变化很困难`** 


不适用于对象结构中的类经常变化的情况，因为对象结构发生了改变，访问者的接口和访问者的实现都要发生相应的改变，代价太高。

* **`破坏封装`** 


访问者模式通常需要对象结构开放内部数据给访问者和ObjectStructrue，这破坏了对象的封装性。
## 3.5 思考访问者模式##

* **`访问者模式的本质`** 

 **``访问者模式的本质：预留通路，回调实现。``** 

仔细思考访问者模式，`它的实现主要就是通过预先定义好调用的通路，在被访问的对象上定义accept方法，在访问者的对象上定义visit方法；然后在调用真正发生的时候，通过两次分发的技术，利用预先定义好的通路，回调到访问者具体的实现上`。
`明白了访问者模式的本质，就可以在定义一些通用功能，或者设计工具类的时候让访问者模式派上大用场了`。你可以把已经实现好的一些功能，把它们作为已有的对象结构，因为在今后可能会根据实际需要给它们增加新的功能，甚至你希望开放接口来让其它开发人员扩展这些功能，那么你就可以用访问者模式来设计，在这个对象结构上预留好通用的调用通路，在以后添加功能，或者是其它开发人员来扩展的时候，只需要提供新的访问者实现，就能够很好的加入到系统中来了。

* **`何时选用访问者模式`** 


建议在如下情况中，选用访问者模式：

如果想对一个对象结构，实施一些依赖于对象结构中的具体类的操作，可以使用访问者模式。

如果想对一个对象结构中的各个元素，进行很多不同的而且不相关的操作，为了避免这些操作使得类变得杂乱，可以使用访问者模式，把这些操作分散到不同的访问者对象中去，每个访问者对象实现同一类功能。

如果对象结构很少变动，但是需要经常给对象结构中的元素对象定义新的操作，可以使用访问者模式。

## 3.6 相关模式##

* **`访问者模式和组合模式`** 


这两个模式可以组合使用。

如同前面示例的那样，通过访问者模式给组合对象预留下扩展功能的接口，使得给组合模式的对象结构添加功能非常容易。

* **`访问者模式和装饰模式`** 


这两个模式从表面看功能有些相似，`都能够实现在不修改原对象结构的情况下修改原对象的功能`。但是`装饰模式更多的是实现对已有功能加强、或者修改、或者完全全新实现`；而`访问者模式更多的是实现给对象结构添加新的功能`。

* **`访问者模式和解释器模式`** 


这两个模式可以组合使用。
`解释器模式在构建抽象语法树的时候，是使用组合模式来构建的`，也就是说`解释器模式解释并执行的抽象语法树是一个组合对象结构`，这个组合对象结构是很少变动的，`但是可能经常需要为解释器增加新的功能`，实现对同一对象结构的不同解释和执行的功能，这正好是访问者模式的优势所在，因此这在使用解释器模式的时候通常会组合访问者模式来使用。


[0]: ./img/2062729-570bc95e69969088.png
[1]: ./img/2062729-8a57b4259316fec3.png
[2]: ./img/2062729-aae9463997f6a242.png
[3]: ./img/2062729-72a4f9177a4daebd.png
[4]: ./img/2062729-cd86d0a552b4acc0.png
[5]: ./img/2062729-b7ad2fdacb763026.png
[6]: ./img/2062729-9f376b375d7a29f1.png
[7]: ./img/2062729-e4922ef07ce087c2.png