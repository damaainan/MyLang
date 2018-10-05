## 【行为型模式二十二】迭代器模式（Iterator）

2016.12.07 12:12*

来源：[https://www.jianshu.com/p/909b4153dc86](https://www.jianshu.com/p/909b4153dc86)


          
## 1 场景问题#
## 1.1 工资表数据的整合##

考虑这样一个实际应用：整合工资表数据。

这个项目的背景是这样的，项目的客户方收购了一家小公司，这家小公司有自己的工资系统，现在需要整合到客户方已有的工资系统上。

客户方已有的工资系统，在内部是采用的List来记录工资列表；而新收购的这家公司的工资系统，在内部是采用的数组来记录工资列表；但是幸运的是，两个系统用来描述工资的数据模型是差不多的。

要整合这两个工资系统的工资数据，当然最简单的方式是考虑直接把新收购的这家公司的工资系统，也改成内部使用List来记录工资列表，但是经过仔细查看源代码，发现有很多的代码跟这个数组相关，还有很多是比较重要的逻辑处理，比如计算工资等，因此只好作罢。

现在除了要把两个工资系统整合起来外，老板还希望能够通过决策辅助系统来统一查看工资数据，他不想看到两份不同的工资表。那么应该如何实现呢？
## 1.2 有何问题##

本来就算内部描述形式不一样，只要不需要整合在一起，两个系统单独输出自己的工资表，是没有什么问题的。但是，老板还希望能够以一个统一的方式来查看所有的工资数据，也就是说从外部看起来，两个系统输出的工资表应该是一样的。

经过分析，要满足老板的要求，而且要让两边的系统改动都尽可能的小的话，`问题的核心就在于如何能够以一种统一的方式来提供工资数据给决策辅助系统`，换句说来说就是：`如何能够以一个统一的方式来访问内部实现不同的聚合对象`。
## 2 解决方案#
## 2.1 迭代器模式来解决##

用来解决上述问题的一个合理的解决方案就是迭代器模式。那么什么是迭代器模式呢？

* **`迭代器模式定义`** 



![][0]


迭代器模式定义

`所谓聚合是：指一组对象的组合结构，比如：Java中的集合、数组等。`

* **`应用迭代器模式来解决的思路`** 


仔细分析上面的问题，`要以一个统一的方式来访问内部实现不同的聚合对象`，那么首先就需要把这个统一的访问方式定义出来，按照这个统一的访问方式定义出来的接口，在迭代器模式中对应的就是Iterator接口。
`迭代器迭代的是具体的聚合对象，那么不同的聚合对象就应该有不同的迭代器`，为了让迭代器以一个统一的方式来操作聚合对象，`因此给所有的聚合对象抽象出一个公共的父类，让它提供操作聚合对象的公共接口，这个抽象的公共父类在迭代器模式中对应的就是Aggregate对象`。

接下来就该考虑如何创建迭代器了，由于迭代器和相应的聚合对象紧密相关，因此让具体的聚合对象来负责创建相应的迭代器对象。
## 2.2 模式结构和说明#

迭代器模式的结构如图所示：


![][1]


迭代器模式结构示意图


 **`Iterator：迭代器接口。`** 定义访问和遍历元素的接口。 **`ConcreteIterator：具体的迭代器实现对象。`** 实现对聚合对象的遍历，并跟踪遍历时的当前位置。 **`Aggregate：聚合对象。`** 定义创建相应迭代器对象的接口。 **`ConcreteAggregate：具体聚合对象。`** 实现创建相应的迭代器对象。

## 2.3 迭代器模式示例代码##

* **`先来看看迭代器接口的定义，示例代码如下：`** 


```java
/**
 * 迭代器接口，定义访问和遍历元素的操作
 */
public interface Iterator {
    /**
     * 移动到聚合对象的第一个位置
     */
    public void first();
    /**
     * 移动到聚合对象的下一个位置
     */
    public void next();
    /**
     * 判断是否已经移动到聚合对象的最后一个位置
     * @return true表示已经移动到聚合对象的最后一个位置，
     *         false表示还没有移动到聚合对象的最后一个位置
     */
    public boolean isDone();
    /**
     * 获取迭代的当前元素
     * @return 迭代的当前元素
     */
    public Object currentItem();
}

```

* **`接下来看看具体的迭代器实现示意，示例代码如下：`** 


```java
/**
 * 具体迭代器实现对象，示意的是聚合对象为数组的迭代器
 * 不同的聚合对象相应的迭代器实现是不一样的
 */
public class ConcreteIterator implements Iterator {
    /**
     * 持有被迭代的具体的聚合对象
     */
    private ConcreteAggregate aggregate;
    /**
     * 内部索引，记录当前迭代到的索引位置。
     * -1表示刚开始的时候，迭代器指向聚合对象第一个对象之前
     */
    private int index = -1;
    /**
     * 构造方法，传入被迭代的具体的聚合对象
     * @param aggregate 被迭代的具体的聚合对象
     */
    public ConcreteIterator(ConcreteAggregate aggregate) {
       this.aggregate = aggregate;
    }

    public void first(){
       index = 0;
    }
    public void next(){
       if(index < this.aggregate.size()){
           index = index + 1;
       }
    }
    public boolean isDone(){
       if(index == this.aggregate.size()){
           return true;
       }
       return false;
    }
    public Object currentItem(){
       return this.aggregate.get(index);
    }
}

```

* **`再来看看聚合对象的定义，示例代码如下：`** 


```java
/**
 * 聚合对象的接口，定义创建相应迭代器对象的接口
 */
public abstract class Aggregate {
    /**
     * 工厂方法，创建相应迭代器对象的接口
     * @return 相应迭代器对象的接口
     */
    public abstract Iterator createIterator();
}

```

* **`接下来看看具体的聚合对象的实现，这里示意的是数组，示例代码如下：`** 


```java
/**
 * 具体的聚合对象，实现创建相应迭代器对象的功能
 */
public class ConcreteAggregate extends Aggregate {
    /**
     * 示意，表示聚合对象具体的内容
     */
    private String[] ss = null;

    /**
     * 构造方法，传入聚合对象具体的内容
     * @param ss 聚合对象具体的内容
     */
    public ConcreteAggregate(String[] ss){
       this.ss = ss;
    }
  
    public Iterator createIterator() {
       //实现创建Iterator的工厂方法
       return new ConcreteIterator(this);
    }
    /**
     * 获取索引所对应的元素
     * @param index 索引
     * @return 索引所对应的元素
     */
    public Object get(int index){
       Object retObj = null;
       if(index < ss.length){
           retObj = ss[index];
       }
       return retObj;
    }
    /**
     * 获取聚合对象的大小
     * @return 聚合对象的大小
     */
    public int size(){
       return this.ss.length;
    }
}

```

* **`最后来看看如何使用这个聚合对象和迭代器对象，示例代码如下：`** 


```java
public class Client {
    /**
     * 示意方法，使用迭代器的功能。
     * 这里示意使用迭代器来迭代聚合对象
     */
    public void someOperation(){
       String[] names = {"张三","李四","王五"};
       //创建聚合对象
       Aggregate aggregate = new ConcreteAggregate(names);
       //循环输出聚合对象中的值
       Iterator it = aggregate.createIterator();
       //首先设置迭代器到第一个元素
       it.first();
       while(!it.isDone()){
           //取出当前的元素来
           Object obj = it.currentItem();
           System.out.println("the obj=="+obj);
           //如果还没有迭代到最后，那么就向下迭代一个
           it.next();
       }
    }
    public static void main(String[] args) {
       //可以简单的测试一下
       Client client = new Client();
       client.someOperation();
    }
}

```
## 2.4 使用迭代器模式来实现示例##

要使用迭代器模式来实现示例，先来看看已有的两个工资系统现在的情况，然后再根据前面学习的迭代器模式来改造。

* **`已有的系统`** 

 **`（1）首先是有一个已经统一了的工资描述模型，为了演示简单，这里只留下最基本的字段，描述一下支付工资的人员、支付的工资数额，其它的包括时间等都不描述了；同时为了后面调试方便，实现了toString方法。示例代码如下：`** 

```java
/**
 * 工资描述模型对象
 */
public class PayModel {
    /**
     * 支付工资的人员
     */
    private String userName;
    /**
     * 支付的工资数额
     */
    private double pay;
    public String getUserName() {
       return userName;
    }
    public void setUserName(String userName) {
       this.userName = userName;
    }
    public double getPay() {
       return pay;
    }
    public void setPay(double pay) {
       this.pay = pay;
    }
    public String toString(){
       return "userName="+userName+",pay="+pay;
    }
}

``` **`（2）客户方已有的工资管理系统中的工资管理类，内部是通过List来管理的，简单的示例代码如下：`** 

```java
/**
 * 客户方已有的工资管理对象
 */
public class PayManager{
    /**
     * 聚合对象，这里是Java的集合对象
     */
    private List list = new ArrayList();
    /**
     * 获取工资列表
     * @return 工资列表
     */
    public List getPayList(){
       return list;
    }
    /**
     * 计算工资，其实应该有很多参数，为了演示从简
     */
    public void calcPay(){
       //计算工资，并把工资信息填充到工资列表里面
       //为了测试，做点数据进去
       PayModel pm1 = new PayModel();
       pm1.setPay(3800);
       pm1.setUserName("张三");
     
       PayModel pm2 = new PayModel();
       pm2.setPay(5800);
       pm2.setUserName("李四");
     
       list.add(pm1);
       list.add(pm2);
    }
}

``` **`（3）客户方收购的那家公司的工资管理系统中的工资管理类，内部是通过数组来管理的，简单的示例代码如下：`** 

```java
/**
 * 被客户方收购的那个公司的工资管理类
 */
public class SalaryManager{
    /**
     * 用数组管理
     */
    private PayModel[] pms = null;
    /**
     * 获取工资列表
     * @return 工资列表
     */
    public PayModel[] getPays(){
       return pms;
    }
    /**
     * 计算工资，其实应该有很多参数，为了演示从简
     */
    public void calcSalary(){
       //计算工资，并把工资信息填充到工资列表里面
       //为了测试，做点数据进去
       PayModel pm1 = new PayModel();
       pm1.setPay(2200);
       pm1.setUserName("王五");
     
       PayModel pm2 = new PayModel();
       pm2.setPay(3600);
       pm2.setUserName("赵六");
     
       pms = new PayModel[2];
       pms[0] = pm1;
       pms[1] = pm2;
    }
}

``` **`（4）如果此时从外部来访问这两个工资列表，外部要采用不同的访问方式，一个是访问数组，一个是访问集合对象，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
       //访问集团的工资列表
       PayManager payManager= new PayManager();
       //先计算再获取
       payManager.calcPay();
       Collection payList = payManager.getPayList();
       Iterator it = payList.iterator();
       System.out.println("集团工资列表：");
       while(it.hasNext()){
           PayModel pm = (PayModel)it.next();
           System.out.println(pm);
       }
     
       //访问新收购公司的工资列表
       SalaryManager salaryManager = new SalaryManager();
       //先计算再获取
       salaryManager.calcSalary();
       PayModel[] pms = salaryManager.getPays();
       System.out.println("新收购的公司工资列表：");
       for(int i=0;i<pms.length;i++){
           System.out.println(pms[i]);
       }
    }
}

```

仔细查看框住的代码，会发现它们的访问方式是完全不一样的。运行结果如下：

```java
集团工资列表：
userName=张三,pay=3800.0
userName=李四,pay=5800.0
新收购的公司工资列表：
userName=王五,pay=2200.0
userName=赵六,pay=3600.0

```

* **`统一访问聚合的接口`** 


要使用迭代器模式来整合访问上面两个聚合对象，`那就需要先定义出抽象的聚合对象和迭代器接口来，然后再提供相应的实现`。

使用迭代器模式实现示例的结构如图所示：


![][2]


使用迭代器模式实现示例的结构示意图

 **`（1）为了让客户端能够以一个统一的方式进行访问，`最好想的方式就是为它们定义一个统一的接口，都通过统一的接口来访问就简单了`。这个示例用的Iterator跟模式的示例代码是一样的，这里就不去注释了，示例代码如下：`** 

```java
public interface Iterator {
    public void first();
    public void next();
    public boolean isDone();
    public Object currentItem();
}

``` **`（2）定义好了统一的接口，那就得分别实现这个接口。一个是List实现的，一个是数组实现的，先看数组实现的访问吧，示例代码如下：`** 

```java
/**
 * 用来实现访问数组的迭代接口
 */
public class ArrayIteratorImpl implements Iterator{
    /**
     * 用来存放被迭代的聚合对象
     */
    private SalaryManager aggregate = null;
    /**
     * 用来记录当前迭代到的位置索引
     * -1表示刚开始的时候，迭代器指向聚合对象第一个对象之前
     */
    private int index = -1;
  
    public ArrayIteratorImpl(SalaryManager aggregate){
       this.aggregate = aggregate;
    }
    public void first(){
       index = 0;
    }
    public void next(){
       if(index < this.aggregate.size()){
           index = index + 1;
       }
    }
    public boolean isDone(){
       if(index == this.aggregate.size()){
           return true;
       }
       return false;
    }
    public Object currentItem(){
       return this.aggregate.get(index);
    }
}

```

为了让客户端能以统一的方式访问数据，所以对集合也提供一个对接口Iterator的实现，示例代码如下：

```java
/**
 * 用来实现访问Collection集合的迭代接口，为了外部统一访问方式
 */
public class CollectionIteratorImpl implements Iterator{
    /**
     * 用来存放被迭代的聚合对象
     */
    private PayManager aggregate = null;
    /**
     * 用来记录当前迭代到的位置索引
     * -1表示刚开始的时候，迭代器指向聚合对象第一个对象之前
     */
    private int index = -1;
  
    public CollectionIteratorImpl(PayManager aggregate){
       this.aggregate = aggregate;
    }
    public void first(){
       index = 0;
    }
    public void next(){
       if(index < this.aggregate.size()){
           index = index + 1;
       }
    }
    public boolean isDone(){
       if(index == this.aggregate.size()){
           return true;
       }
       return false;
    }
    public Object currentItem(){
       return this.aggregate.get(index);
    }
}

``` **`（3）获取访问聚合的接口`** 

定义好了统一的访问聚合的接口，也分别实现了这个接口，新的问题是，在客户端要如何才能获取这个访问聚合的接口呢？而且还要以统一的方式来获取。
`一个简单的方案就是定义一个获取访问聚合的接口的接口，客户端先通过这个接口来获取访问聚合的接口，然后再访问聚合对象`。示例代码如下：

```java
public abstract class Aggregate {
    /**
     * 工厂方法，创建相应迭代器对象的接口
     * @return 相应迭代器对象的接口
     */
    public abstract Iterator createIterator();
}

```

然后让具体的聚合对象PayManger和SalaryManager来继承这个抽象类，提供分别访问它们的访问聚合的接口。

修改PayManager对象，添加createIterator方法的实现，另外再添加迭代器回调聚合对象的方法，一个方法是获取聚合对象的大小，一个方法是根据索引获取聚合对象中的元素，示例代码如下：

```java
public class PayManager extends Aggregate{
    public Iterator createIterator(){
       return new CollectionIteratorImpl(this);
    }
    public Object get(int index){
       Object retObj = null;
       if(index < this.list.size()){
           retObj = this.list.get(index);
       }
       return retObj;
    }
    public int size(){
       return this.list.size();
    }
}

```

同理修改SalaryManager对象，示例代码如下：

```java
public class SalaryManager extends Aggregate{
    public Iterator createIterator(){
       return new ArrayIteratorImpl(this);
    }
    public Object get(int index){
       Object retObj = null;
       if(index < pms.length){
           retObj = pms[index];
        }
       return retObj;
    }
    public int size(){
       return this.pms.length;
    }
}

``` **`（4）统一访问的客户端`** 

下面就来看看客户端，如何通过迭代器接口来访问聚合对象，为了显示是统一的访问，干脆把通过访问聚合的接口来访问聚合对象的功能独立成一个方法。虽然是访问不同的聚合对象，但是都调用这个方法去访问。示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
       //访问集团的工资列表
       PayManager payManager= new PayManager();
       //先计算再获取
       payManager.calcPay();
       System.out.println("集团工资列表：");
       test(payManager.createIterator());
     
       //访问新收购公司的工资列表
       SalaryManager salaryManager = new SalaryManager();
       //先计算再获取
       salaryManager.calcSalary();
       System.out.println("新收购的公司工资列表：");
       test(salaryManager.createIterator());
    }

    /**
     * 测试通过访问聚合对象的迭代器，是否能正常访问聚合对象
     * @param it 聚合对象的迭代器
     */
    private static void test(Iterator it){
       //循环输出聚合对象中的值
       //首先设置迭代器到第一个元素
       it.first();
       while(!it.isDone()){
           //取出当前的元素来
           Object obj = it.currentItem();
           System.out.println("the obj=="+obj);
           //如果还没有迭代到最后，那么就向下迭代一个
           it.next();
       }
    }
}

```

小提示：

估计有些朋友看到这里，会觉得上面的实现特麻烦，会认为“Java里面就有Iterator接口，而且Java集合框架中的聚合对象也大都实现了Iterator接口的功能，还有必要像上面这么做吗？”

其实这么做，是为了让大家看到迭代器模式的全貌，后面会讲到用Java中的迭代器来实现。另外，有些时候还是需要自己来扩展和实现迭代器模式的，所以还是应该先独立学习迭代器模式。

 **`（5）迭代器示例小结`** 

如同前面示例，提供了一个统一访问聚合对象的接口，通过这个接口就可以顺序的访问聚合对象的元素，对于客户端而言，只是面向这个接口在访问，根本不知道聚合对象内部的表示方法。

事实上，前面的例子故意做了一个集合类型的聚合对象和一个数组类型的聚合对象，但是从客户端来看，访问聚合的代码是完全一样的，根本看不出任何的差别，也看不出到底聚合对象内部是什么类型。
## 3 模式讲解#
## 3.1 认识迭代器模式##

* **`迭代器模式的功能`** 

`迭代器模式的功能主要在于提供对聚合对象的迭代访问`。迭代器就围绕着这个“访问”做文章，延伸出很多的功能来。比如：

以不同的方式遍历聚合对象，比如向前、向后等；

对同一个聚合同时进行多个遍历；

以不同的遍历策略来遍历聚合，比如是否需要过滤等；

多态迭代，含义是：`为不同的聚合结构，提供统一的迭代接口，也就是说通过一个迭代接口可以访问不同的聚合结构，这就叫做多态迭代`。上面的示例就已经实现了多态迭代，事实上，标准的迭代模式实现基本上都是支持多态迭代的；

但是请注意：多态迭代可能会带来类型安全的问题，`可以考虑使用泛型`；

* **`迭代器模式的关键思想`** 


聚合对象的类型很多，如果对聚合对象的迭代访问跟聚合对象本身融合在一起的话，会严重影响到聚合对象的可扩展性和可维护性。

因此`迭代器模式的关键思想就是把对聚合对象的遍历和访问从聚合对象中分离出来，放入到单独的迭代器中，这样聚合对象会变得简单一些；而且迭代器和聚合对象可以独立的变化和发展，会大大加强系统的灵活性`。

* **`内部迭代器和外部迭代器`** 


所谓内部迭代器，`指的是由迭代器自己来控制迭代下一个元素的步骤，客户端无法干预`，因此，如果想要在迭代的过程中完成工作的话，客户端就需要把操作传给迭代器，迭代器在迭代的时候会在每个元素上执行这个操作，类似于Java的回调机制。

所谓外部迭代器，`指的是由客户端来控制迭代下一个元素的步骤`，像前面的示例一样，客户端必须显示的调用next来迭代下一个元素。

总体来说外部迭代器比内部迭代器要灵活一些，因此我们常见的实现多属于外部迭代器，前面的例子也是实现的外部迭代器。

* **`Java中最简单的统一访问聚合的方式`** 


如果只是想要使用一种统一的访问方式来访问聚合对象，在Java中有更简单的方式，简单到几乎什么都不用做，利用Java 5以上版本本身的特性即可。

但是请注意，这只是从访问形式上一致了，但是也暴露了聚合的内部实现，因此并不能算是标准迭代器模式的实现，但是从某种意义上说，可以算是隐含的实现了部分迭代器模式的功能。

那么怎么做呢？

为了简单，让我们回到没有添加任何迭代器模式的情况下。很简单，只要让聚合对象中的结合实现范型即可，示例如下：

```java
public class PayManager{
    private List<PayModel> list = new ArrayList<PayModel>();
    /**
     * 获取工资列表
     * @return 工资列表
     */
    public List<PayModel> getPayList(){
       return list;
    }  
}

```

这样一来，`客户端的代码就可以改成使用增强的for循环来实现了，对于数组、范型的集合都可以采用一样的方法来实现了，从代码层面上看，就算是统一了访问聚合的方式了`，修改后的客户端代码如下：

```java
public class Client {
    public static void main(String[] args) {
       //访问集团的工资列表
       PayManager payManager= new PayManager();
       //先计算再获取
       payManager.calcPay();

       Collection<PayModel> payList = payManager.getPayList();
       System.out.println("集团工资列表：");

//     Iterator it = payList.iterator();
//     while(it.hasNext()){
//         PayModel pm = (PayModel)it.next();
//         System.out.println(pm);
//     }

//     这两段新的访问方式是否一样呢？

       for(PayModel pm : payList){
           System.out.println(pm);
       }
       //访问新收购公司的工资列表
       SalaryManager salaryManager = new SalaryManager();
       //先计算再获取
       salaryManager.calcSalary();
       PayModel[] pms = salaryManager.getPays();
       System.out.println("新收购的公司工资列表：");
//     for(int i=0;i<pms.length;i++){
//         System.out.println(pms[i]);
//     }
       for(PayModel pm : pms){
           System.out.println(pm);
       }
    }
}

```
## 3.2 使用Java的迭代器##

大家都知道，在java.util包里面有一个Iterator的接口，在Java中实现迭代器模式是非常简单的，而且java的集合框架中的聚合对象，基本上都是提供了迭代器的。

下面就来把前面的例子改成用Java中的迭代器实现，一起来看看有些什么改变。

不再需要自己实现的Iterator接口，直接实现java.util.Iterator接口就可以了，所有使用自己实现的Iterator接口的地方都需要修改过来；

Java中Iterator接口跟前面自己定义的接口相比，需要实现的方法是不一样的；

集合已经提供了Iterator，那么CollectionIteratorImpl类就不需要了，直接去掉；

好了，还是一起来看看代码吧。

* **`PayModel类没有任何变化，就不示例了。`** 

* **`抽象的Aggregate类就是把创建迭代器方法返回的类型换成java中的Iterator了。示例代码如下：`** 

```java
import java.util.Iterator;

public abstract class Aggregate {
    public abstract Iterator createIterator();
}

```

* **`原来的ArrayIteratorImpl类，实现的接口改变了，实现代码也需要跟着改变，示例代码如下：`** 


```java
/**
 * 用来实现访问数组的迭代接口
 */
public class ArrayIteratorImpl implements Iterator{
    /**
     * 用来存放被迭代的聚合对象
     */
    private SalaryManager aggregate = null;
    /**
     * 用来记录当前迭代到的位置索引
     */
    private int index = 0;
    public ArrayIteratorImpl(SalaryManager aggregate){
       this.aggregate = aggregate;
    }
  
    public boolean hasNext() {
       //判断是否还有下一个元素
       if(aggregate!=null && index<aggregate.size()){
           return true;
       }
       return false;
    }
    public Object next() {
       Object retObj = null;
       if(hasNext()){
           retObj = aggregate.get(index);
           //每取走一个值，就把已访问索引加1
           index++;
       }
       return retObj;
    }
    public void remove() {
       //暂时可以不实现   
    }
}

```

* **`对于PayManager类，在实现创建迭代器的方法上发生了改变，不再使用自己实现的迭代器，改用java的集合框架实现的迭代器了。示例代码如下：`** 


```java
public class PayManager extends Aggregate{
    private List<PayModel> list = new ArrayList<PayModel>();
    public List<PayModel> getPayList(){
       return list;
    }
    public void calcPay(){
       //计算工资，并把工资信息填充到工资列表里面
       //为了测试，做点数据进去
       PayModel pm1 = new PayModel();
       pm1.setPay(3800);
       pm1.setUserName("张三");
     
       PayModel pm2 = new PayModel();
       pm2.setPay(5800);
       pm2.setUserName("李四");
     
       list.add(pm1);
       list.add(pm2);
    }  
    public Iterator createIterator() {
       return list.iterator();
    }
}

```

* **`对于SalaryManager类，除了创建迭代器方法返回的类型改变外，其它都没有改变，还是用ArrayIteratorImpl来实现迭代器。`** 

* **`接下来写个客户端来测试看看，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
       //访问集团的工资列表
       PayManager payManager= new PayManager();
       //先计算再获取
       payManager.calcPay();
       System.out.println("集团工资列表：");
       test(payManager.createIterator());

       //访问新收购公司的工资列表
       SalaryManager salaryManager = new SalaryManager();
       //先计算再获取
       salaryManager.calcSalary();
       System.out.println("新收购的公司工资列表：");
       test(salaryManager.createIterator());
    }
    /**
     * 测试通过访问聚合对象的迭代器，是否能正常访问聚合对象
     * @param it 聚合对象的迭代器
     */
    private static void test(Iterator it){
       while(it.hasNext()){
           PayModel pm = (PayModel)it.next();
           System.out.println(pm);
       }
    }
}

```

很明显改用Java的Iterator来实现，比自己全部重新去做，还是要简单一些的。
## 3.3 带迭代策略的迭代器##

由于`迭代器模式把聚合对象和访问聚合的机制实现了分离`，所以可以在迭代器上实现不同的迭代策略，`最为典型的就是实现过滤功能的迭代器`。

在实际开发中，对于经常被访问的一些数据可以使用缓存，把这些数据存放在内存中。但是不同的业务功能需要访问的数据是不同的，还有不同的业务访问权限能访问的数据也是不同的，对于这种情况，就可以使用实现过滤功能的迭代器，让不同功能使用不同的迭代器来访问。当然，这种情况也可以结合策略模式来实现。

在实现过滤功能的迭代器中，又有两种常见的需要过滤的情况，`一种是对数据进行整条过滤`，比如只能查看自己部门的数据；`另外一种情况是对数据进行部分过滤`，比如某些人不能查看工资数据。
`带迭代策略的迭代器实现的一个基本思路，就是先把聚合对象的聚合数据获取到，并存储到迭代器里面来，这样迭代器就可以按照不同的策略来迭代数据了。`

* **`带迭代策略的迭代器示例`** 


沿用上一个例子，来修改ArrayIteratorImpl来简单的示意一下，不去考虑复杂的算法，大致的修改有：

原来是持有聚合对象的，现在直接把这个聚合对象的内容取出来存放到迭代器里面，也就是迭代的时候，直接在迭代器里面来获取具体的聚合对象的元素，这样才好控制迭代的数据；

在迭代器的具体实现上加入过滤的功能；

示例代码如下：

```java
/**
 * 用来实现访问数组的迭代接口,加入了迭代策略
 */
public class ArrayIteratorImpl implements Iterator{
    /**
     * 用来存放被迭代的数组
     */
    private PayModel[] pms = null;
    /**
     * 用来记录当前迭代到的位置索引
     */
    private int index = 0;
  
    public ArrayIteratorImpl(SalaryManager aggregate){
       //在这里先对聚合对象的数据进行过滤，比如工资必须在3000以下
       Collection<PayModel> tempCol = new ArrayList<PayModel>();
       for(PayModel pm : aggregate.getPays()){
           if(pm.getPay() < 3000){
              tempCol.add(pm);
           }
       }
       //然后把符合要求的数据存放到用来迭代的数组
       this.pms = new PayModel[tempCol.size()];
       int i=0;
       for(PayModel pm : tempCol){
           this.pms[i] = pm;
           i++;
       }
    }
    public boolean hasNext() {
       //判断是否还有下一个元素
       if(pms!=null && index<=(pms.length-1)){
           return true;
       }
       return false;
    }
    public Object next() {
       Object retObj = null;
       if(hasNext()){
           retObj = pms[index];
           //每取走一个值，就把已访问索引加1
           index++;
       }
       //在这里对要返回的数据进行过滤，比如不让查看工资数据
       ((PayModel)retObj).setPay(0.0);
     
       return retObj;
    }
    public void remove() {
       //暂时可以不实现   
    }
}

```

* **`谁定义遍历算法的问题`** 


在实现迭代器模式的时候，一个常见的问题就是：谁来定义遍历算法？其实带策略的迭代器讲述的也是这个问题。

在迭代器模式的实现中，常见有两个地方可以来定义遍历算法，`一个就是聚合对象本身，另外一个就是迭代器负责遍历算法`。
`在聚合对象本身定义遍历的算法这种情况下，通常会在遍历过程中，用迭代器来存储当前迭代的状态，这种迭代器被称为游标，因为它仅用来指示当前的位置`。比如在2.4里面示例的迭代器就属于这种情况。
`在迭代器里面定义遍历算法，会易于在相同的聚合上使用不同的迭代算法，同时也易于在不同的聚合上重用相同的算法`。比如上面带策略的迭代器的示例，迭代器把需要迭代的数据从聚合对象中取出并存放到自己对象里面，然后再迭代自己的数据，这样一来，除了刚开始创建迭代器的时候需要访问聚合对象外，真正迭代过程已经跟聚合对象无关了。

当然，`在迭代器里面定义遍历算法，如果实现遍历算法的时候需要访问聚合对象的私有变量，那么将遍历算法放入迭代器中会破坏聚合对象的封装性`。

至于究竟使用哪一种方式，要具体问题具体分析。
## 3.4 双向迭代器##
`所谓双向迭代器的意思就是：可以同时向前和向后遍历数据的迭代器。`在Java util包中的ListIterator接口就是一个双向迭代器的示例，当然自己实现双向迭代器也非常容易，只要在自己的Iterator接口中添加向前的判断和向前获取值的方法，然后在实现中实现即可。

延续前面2.4的示例，来自己实现双向迭代器，相同的部分就不去示范了，只演示不同的地方，先看看新的迭代器接口，示例代码如下：

```java
/**
 * 迭代器接口，定义访问和遍历元素的操作，实现双向迭代
 */
public interface Iterator {
    public void first();
    public void next();
    public boolean isDone();
    public Object currentItem();
    /**
     * 判断是否为第一个元素
     * @return 如果为第一个元素，返回true，否则返回false
     */
    public boolean isFirst();
    /**
     * 移动到聚合对象的上一个位置
     */
    public void previous();
}

```

有了新的迭代器接口，也应该有新的实现。示例代码如下：

```java
/**
 * 用来实现访问数组的双向迭代接口
 */
public class ArrayIteratorImpl implements Iterator{
    private SalaryManager aggregate = null;
    private int index = -1; 
    public ArrayIteratorImpl(SalaryManager aggregate){
       this.aggregate = aggregate;
    }
    public void first(){
       index = 0;
    }
    public void next(){
       if(index < this.aggregate.size()){
           index = index + 1;
       }
    }
    public boolean isDone(){
       if(index == this.aggregate.size()){
           return true;
       }
       return false;
    }
    public Object currentItem(){
       return this.aggregate.get(index);
    }
   
    public boolean isFirst(){
       if(index==0){
           return true;
       }
       return false;
    }
    public void previous(){
       if(index > 0 ){
           index = index - 1;
       }
    }
}

```

基本实现完了，写个客户端来享受一下双向迭代的乐趣。`由于这个实现要考虑同时控制向前和向后迭代取值，而控制当前索引的是同一个值，因此在获取向前取值得时候，要先把已访问索引减去1，然后再取值，这个跟向后取值是反过来的，注意一下`。示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
       //访问新收购公司的工资列表
       SalaryManager salaryManager = new SalaryManager();
       //先计算再获取
       salaryManager.calcSalary();
      
       //得到双向迭代器
       Iterator it = salaryManager.createIterator();
       //首先设置迭代器到第一个元素
       it.first();
      
       //先next一个
       if(!it.isDone()){
           PayModel pm = (PayModel)it.currentItem();
           System.out.println("next1 == "+pm);
           //向下迭代一个
           it.next();
       }
       //然后previous一个
       if(!it.isFirst()){
           //向前迭代一个
           it.previous();
           PayModel pm = (PayModel)it.currentItem();
           System.out.println("previous1 == "+pm);         
       }
       //再next一个
       if(!it.isDone()){
           PayModel pm = (PayModel)it.currentItem();
           System.out.println("next2 == "+pm);
           //向下迭代一个
           it.next();
       }
       //继续next一个
       if(!it.isDone()){
           PayModel pm = (PayModel)it.currentItem();
           System.out.println("next3 == "+pm);
           //向下迭代一个
           it.next();
       }
       //然后previous一个
       if(!it.isFirst()){
           //向前迭代一个
           it.previous();
           PayModel pm = (PayModel)it.currentItem();
           System.out.println("previous2 == "+pm);         
       }
      
    }
}

```

上面的示例故意先向后取值，然后再向前取值，这样反复才能看出双向迭代器的效果。运行的结果如下：

```java
next1 == userName=王五,pay=2200.0
previous1 == userName=王五,pay=2200.0
next2 == userName=王五,pay=2200.0
next3 == userName=赵六,pay=3600.0
previous2 == userName=赵六,pay=3600.0

```

可能有些人会疑惑：为什么next1和previous1取出来的值是一样的呢？

这是因为现在是顺序迭代，当next显示第一条的时候，内部索引已经指向第二条了，所以这个时候再previous向前一条的时候，数据就是第一条数据了。

再仔细看上面的结果，发现这个时候继续next数据时，数据还是第一条数据，同理，刚才previous向前一条的时候，内部索引已经指向第一条之前了。
## 3.5 迭代器模式的优缺点##

* **`更好的封装性`** 


迭代器模式可以让你访问一个聚合对象的内容，而无需暴露该聚合对象的内部表示，从而提高聚合对象的封装性；

* **`可以以不同的遍历方式来遍历一个聚合`** 


使用迭代器模式，使得聚合对象的内容和具体的迭代算法分离开，这样就可以通过使用不同的迭代器的实例，就可以使用不同的遍历方式来遍历一个聚合对象了，比如上面示例的带迭代策略的迭代器。

* **`迭代器简化了聚合的接口`** 


有了迭代器的接口，那么聚合本身就不需要再定义这些接口了，从而简化了聚合的接口定义。

* **`简化客户端调用`** 


迭代器为遍历不同的聚合对象提供了一个统一的接口，使得客户端遍历聚合对象的内容变得更简单

* **`同一个聚合上可以有多个遍历`** 


每个迭代器保持它自己的遍历状态，比如前面实现中的迭代索引位置，因此可以对同一个聚合对象同时进行多个遍历。
## 3.6 思考迭代器模式##

* **`迭代器模式的本质`** 

`迭代器模式的本质：控制访问聚合对象中的元素。`迭代器能实现“无需暴露聚合对象的内部实现，就能够访问到聚合对象中各个元素”的功能，看起来其本质应该是“透明访问聚合对象中的元素”。

但仔细思考一下，除了透明外，迭代器就没有别的功能了吗？很明显还有其它的功能，前面也讲到了一些，比如“带迭代策略的迭代器”。那么综合来看，`迭代器模式的本质应该是“控制访问聚合对象中的元素”，而非单纯的“透明”，事实上，“透明”访问也是“控制访问”的一种情况`。

认识这个本质，对于识别和变形使用迭代器模式很有帮助。大家想想，现在的迭代模式默认的都是向前或者向后获取一个值，也就是说都是单步迭代，那么，如果想要控制一次迭代多条怎么办呢？

这个在实际开发中是很有用的，比如在实际开发中很常用的翻页功能的实现，常见的翻页功能有如下几种实现方式：

（1）纯数据库实现：依靠SQL提供的功能实现翻页，用户每次请求翻页的数据，就会到数据库中获取相应的数据；

（2）纯内存实现：就是一次性从数据库中把需要的所有数据都取出来放到内存中，然后用户请求翻页时，从内存中获取相应的数据；

（3）上面两种方式各有优缺点：

```java
    第一种方案明显是时间换空间的策略，每次获取翻页的数据都要访问数据库，运行速度相对比较慢，而且很耗数据库资源，但是节省内存空间。

    第二种方案是典型的空间换时间，每次是直接从内存中获取翻页的数据，运行速度快，但是很耗内存。

```

```java
    在实际开发中，小型系统一般采用第一种方案，基本没有单独采用第二种方案的，因为内存实在是太宝贵了，中大型的系统一般是把两个方案结合起来，综合利用它们的优点，而又规避它们的缺点，从而更好的实现翻页的功能。

```

（4）纯数据库实现 + 纯内存实现，思路是这样的：如果每页显示10条记录，根据判断，用户很少翻到10页过后，那好了，第一次访问的时候，就一次性从数据库中获取前10页的数据，也就是100条记录，把这100条记录放在内存里面。

这样一来，当用户在前10页内进行翻页操作的时候，就不用再访问数据库了，而是直接从内存中获取数据，这样速度就快了。

当用户想要获取第11页的数据，这个时候才会再次访问数据库，对于这个时候到底获取多少页的数据，简单的处理就是继续获取10页的数据，`比较好的方式就是根据访问统计进行衰减访问`，比如折半获取，也就是第一次访问数据库获取10页的数据，那么第二次就只获取5页，如此操作直到一次从数据库中获取一页的数据。`这也符合正常规律，因为越到后面，被用户翻页到的机会也就越小了。`

* **`何时选用迭代器模式`** 


建议在如下情况中，选用迭代器模式：

如果你希望提供访问一个聚合对象的内容，但是又不想暴露它的内部表示的时候，可以使用迭代器模式来提供迭代器接口，从而让客户端只是通过迭代器的接口来访问聚合对象，而无需关心聚合对象内部实现。

如果你希望有多种遍历方式可以访问聚合对象，可以使用迭代器模式。

如果你希望为遍历不同的聚合对象提供一个统一的接口，可以使用迭代器模式。

## 3.8 相关模式##

* **`迭代器模式和组合模式`** 


这两个模式可以组合使用。
`组合模式是一种递归的对象结构，在枚举某个组合对象的子对象的时候，通常会使用迭代器模式`。

* **`迭代器模式和工厂方法模式`** 


这两个模式可以组合使用。
`在聚合对象创建迭代器的时候，通常会采用工厂方法模式来实例化相应的迭代器对象`。


[0]: ./img/2062729-e646e920ff195a07.png
[1]: ./img/2062729-89eab9fef9da9e07.png
[2]: ./img/2062729-b864ec9829de6f00.png