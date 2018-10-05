## 【创建型模式六】原型模式(Prototype)

2016.06.18 16:12*

来源：[https://www.jianshu.com/p/1638e7b068c1](https://www.jianshu.com/p/1638e7b068c1)


          
## 1 场景问题#
## 1.1 订单处理系统##

考虑这样一个实际应用：订单处理系统。

现在有一个订单处理的系统，里面有个保存订单的业务功能，在这个业务功能里面，客户有这么一个需求：每当订单的预定产品数量超过1000的时候，就需要把订单拆成两份订单来保存，如果拆成两份订单后，还是超过1000，那就继续拆分，直到每份订单的预定产品数量不超过1000。至于为什么要拆分，原因是好进行订单的后续处理，后续是由人工来处理，每个人工工作小组的处理能力上限是1000。

根据业务，目前的订单类型被分成两种：一种是个人订单，一种是公司订单。现在想要实现一个通用的订单处理系统，也就是说，不管具体是什么类型的订单，都要能够正常的处理。

该怎么实现呢？
## 1.2 不用模式的解决方案##

来分析上面要求实现的功能，有朋友会想，这很简单嘛，一共就一个功能，没什么困难的，真的是这样吗？先来尝试着实现看看。

* **`定义订单接口`** 


首先，要想实现通用的订单处理，而不关心具体的订单类型，那么很明显， **`订单处理的对象应该面向一个订单的接口或是一个通用的订单对象来编程`** ，这里就选用面向订单接口来处理吧，先把这个订单接口定义出来，示例代码如下：

```java
/**
   * 订单的接口
   */
public interface OrderApi {
    /**
     * 获取订单产品数量
     * @return 订单中产品数量
     */
    public int getOrderProductNum();
    /**
     * 设置订单产品数量
     * @param num 订单产品数量
     */
    public void setOrderProductNum(int num);
}

```

* **`既然定义好了订单的接口，那么接下来把各种类型的订单实现出来，先看看个人的订单实现，示例代码如下：`** 


```java
/**
   * 个人订单对象
   */
public class PersonalOrder implements OrderApi{
    /**
     * 订购人员姓名
     */
    private String customerName;
    /**
     * 产品编号
     */
    private String productId;
    /**
     * 订单产品数量
     */
    private int orderProductNum = 0;

    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getCustomerName() {
       return customerName;
    }
    public void setCustomerName(String customerName) {
       this.customerName = customerName;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "本个人订单的订购人是="+this.customerName+"，订购产品是="+this.productId+"，订购数量为="+this.orderProductNum;
    }
}

```

再看看企业订单的实现，示例代码如下：

```java
/**
   * 企业订单对象
   */
public class EnterpriseOrder implements OrderApi {
    /**
     * 企业名称
     */
    private String enterpriseName;
    /**
     * 产品编号
     */
    private String productId;  
    /**
     * 订单产品数量
     */
    private int orderProductNum = 0;

    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getEnterpriseName() {
       return enterpriseName;
    }
    public void setEnterpriseName(String enterpriseName) {
       this.enterpriseName = enterpriseName;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "本企业订单的订购企业是="+this.enterpriseName+"，订购产品是="+this.productId+"，订购数量为="+this.orderProductNum;
    }
}

```

有些朋友看到这里，可能会有这样的疑问：看上去上面两种类型的订单对象，仅仅是一个数据封装的对象，而且还有一些数据是相同的，为何不抽出一个父类来，把共同的数据定义在父类里面呢？

这里有两个考虑，一个是：这里仅仅是一个示意，实际情况远比这复杂，实际开发中不会仅仅是数据封装对象这么简单。另外一个是：为了后续示例的重点突出，这里要学习的是原型模式，因此就没有去抽取父类，以免对象层级过多，影响主题的展示。

* **`实现好了订单对象，接下来看看如何实现通用的订单处理，先把订单处理的对象大概定义出来，示例代码如下：`** 


```java
/**
   * 处理订单的业务对象
   */
public class OrderBusiness {
    /**
     * 创建订单的方法
     * @param order 订单的接口对象
     */
    public void saveOrder(OrderApi order){
        //等待具体实现
    }
}

```

现在的中心任务就是要来实现这个saveOrder的方法，传入的参数是一个订单的接口对象，这个方法要实现的功能：根据业务要求，当订单的预定产品数量超过1000的时候，就需要把订单拆成两份订单。

那好，来尝试着实现一下，因为预定的数量可能会很大，因此采用一个while循环来处理，直到拆分后订单的数量不超过1000，先把实现的思路写出来，示例代码如下：

```java
public class OrderBusiness {
    public void saveOrder(OrderApi order){
        //1：判断当前的预定产品数量是否大于1000
        while(order.getOrderProductNum() > 1000){
            //2：如果大于，还需要继续拆分
            //2.1再新建一份订单，跟传入的订单除了数量不一样外，其它都相同
            OrderApi newOrder = null;

            ...
        }
    }
}

```

大家会发现，才刚写到第二步就写不下去了，为什么呢？

 **`因为现在判断需要拆分订单，也就是需要新建一个订单对象，可是订单处理对象面对的是订单的接口，它根本就不知道现在订单具体的类型，也不知道具体的订单实现，它无法创建出新的订单对象来，也就无法实现订单拆分的功能了。`** 

* **`一个简单的解决办法`** 


有朋友提供了这么一个解决的思路，他说：不就是在saveOrder方法里面不知道具体的类型，从而导致无法创建对象吗？ **`很简单，使用instanceof来判断不就可以了，他还给出了他的实现示意`** ，示意代码如下：

```java
public class OrderBusiness {
    public void saveOrder(OrderApi order){
       while(order.getOrderProductNum() > 1000)
           //定义一个表示被拆分出来的新订单对象
           OrderApi newOrder = null;         
           if(order instanceof PersonalOrder){
              //创建相应的订单对象
              PersonalOrder p2 = new PersonalOrder();
              //然后进行赋值等，省略了
              //然后再设置给newOrder
              newOrder = p2;
           }else if(order instanceof EnterpriseOrder){
               //创建相应的订单对象
              EnterpriseOrder e2 = new EnterpriseOrder();
              //然后进行赋值等，省略了
              //然后再设置给newOrder
              newOrder = e2;
           }         
           //然后进行拆分和其它业务功能处理，省略了
       }     
    }
}

```

好像能解决问题，对吧。那我们就来按照他提供的思路，把这个通用的订单处理对象实现出来，示例代码如下：

```java
/**
   * 处理订单的业务对象
   */
public class OrderBusiness {
    /**
     * 创建订单的方法
     * @param order 订单的接口对象
     */
    public void saveOrder(OrderApi order){
       //根据业务要求，当订单预定产品数量超过1000时，就要把订单拆成两份订单
       //当然如果要做好，这里的1000应该做成常量，这么做是为了演示简单

       //1：判断当前的预定产品数量是否大于1000
       while(order.getOrderProductNum() > 1000){
           //2：如果大于，还需要继续拆分
           //2.1再新建一份订单，跟传入的订单除了数量不一样外，其它都相同
           OrderApi newOrder = null;
           if(order instanceof PersonalOrder){
              //创建相应的新的订单对象
              PersonalOrder p2 = new PersonalOrder();
              //然后进行赋值，但是产品数量为1000
              PersonalOrder p1 = (PersonalOrder)order;
              p2.setCustomerName(p1.getCustomerName());
              p2.setProductId(p1.getProductId());          
              p2.setOrderProductNum(1000);
              //然后再设置给newOrder
              newOrder = p2;
           }else if(order instanceof EnterpriseOrder){
              //创建相应的订单对象
              EnterpriseOrder e2 = new EnterpriseOrder();
              //然后进行赋值，但是产品数量为1000
              EnterpriseOrder e1 = (EnterpriseOrder)order;
              e2.setEnterpriseName(e1.getEnterpriseName());
              e2.setProductId(e1.getProductId());
              e2.setOrderProductNum(1000);
              //然后再设置给newOrder
              newOrder = e2;
           }         

           //2.2原来的订单保留，把数量设置成减少1000
           order.setOrderProductNum(order.getOrderProductNum()-1000);

           //然后是业务功能处理，省略了，打印输出，看一下
           System.out.println("拆分生成订单=="+newOrder);
       }     
       //3：不超过1000，那就直接业务功能处理，省略了，打印输出，看一下
       System.out.println("订单=="+order);   
    }
}

```

* **`写个客户端来测试一下，示例代码如下：`** 


```java
public class OrderClient {
    public static void main(String[] args) {
       //创建订单对象，这里为了演示简单，直接new了
       PersonalOrder op = new PersonalOrder();
       //设置订单数据
       op.setOrderProductNum(2925);
       op.setCustomerName("张三");
       op.setProductId("P0001");

       //这里获取业务处理的类，也直接new了，为了简单，连业务接口都没有做
       OrderBusiness ob = new OrderBusiness();
       //调用业务来保存订单对象
       ob.saveOrder(op);
    }
}

```

运行结果如下：

```java
拆分生成订单==本个人订单的订购人是=张三，订购产品是=P0001，订购数量为=1000
拆分生成订单==本个人订单的订购人是=张三，订购产品是=P0001，订购数量为=1000
订单==本个人订单的订购人是=张三，订购产品是=P0001，订购数量为=925

```

根据订单中订购产品的数量，一份订单被拆分成了三份。同样的，你还可以传入企业订单，看看是否能正常满足功能要求。
## 1.3 有何问题##

看起来，上面的实现确实不难，好像也能够通用的进行订单处理，而不需要关心订单的类型和具体实现这样的功能。

仔细想想，真的没有关心订单的类型和具体实现吗？答案是“否定的”。

事实上，在实现订单处理的时候，上面的实现是按照订单的类型和具体实现来处理的，就是instanceof的那一段。有朋友可能会问，这样实现有何不可吗？这样的实现有如下几个问题：

 **`既然想要实现通用的订单处理，那么对于订单处理的实现对象，是不应该知道订单的具体实现的，更不应该依赖订单的具体实现。`** 但是上面的实现中，很明显订单处理的对象依赖了订单的具体实现对象。

这种实现方式另外一个问题就是： **`难以扩展新的订单类型`** 。假如现在要加入一个大客户专用订单的类型，那么就需要修改订单处理的对象，要在里面添加对新的订单类型的支持，这算哪门子的通用处理。

因此，上面的实现是不太好的，把上面的问题再抽象描述一下： **`已经有了某个对象实例后，如何能够快速简单地创建出更多的这种对象？`** 比如上面的问题，就是已经有了订单接口类型的对象实例，然后在方法中需要创建出更多的这种对象。怎么解决呢？
## 2 解决方案#
## 2.1 原型模式来解决##

用来解决上述问题的一个合理的解决方案就是原型模式。那么什么是原型模式呢？

* **`原型模式定义`** 



![][0]


原型模式定义


* **`应用原型模式来解决的思路`** 


仔细分析上面的问题，在saveOrder方法里面，已经有了订单接口类型的对象实例，是从外部传入的，但是这里只是知道这个实例对象的种类是订单的接口类型，并不知道其具体的实现类型，也就是不知道它到底是个人订单还是企业订单，但是现在需要在这个方法里面创建一个这样的订单对象，看起来就像是要通过接口来创建对象一样。

 **`原型模式就可以解决这样的问题，原型模式会要求对象实现一个可以“克隆”自身的接口，这样就可以通过拷贝或者是克隆一个实例对象本身，来创建一个新的实例。如果把这个方法定义在接口上，看起来就像是通过接口来创建了新的接口对象。`** 

这样一来，通过原型实例创建新的对象，就不再需要关心这个实例本身的类型，也不关心它的具体实现，只要它实现了克隆自身的方法，就可以通过这个方法来获取新的对象，而无须再去通过new来创建。
## 2.2 模式结构和说明##


![][1]


原型模式结构


 **`Prototype：声明一个克隆自身的接口`** ，用来约束想要克隆自己的类，要求它们都要实现这里定义的克隆方法。 **`ConcretePrototype：实现Prototype接口的类`** ，这些类真正实现了克隆自身的功能。 **`Client：使用原型的客户端`** ，首先要获取到原型实例对象，然后通过原型实例克隆自身来创建新的对象实例。

## 2.3 原型模式示例代码##

* **`先来看看原型接口的定义，示例代码如下：`** 


```java
/**
   * 声明一个克隆自身的接口
   */
public interface Prototype {
    /**
     * 克隆自身的方法
     * @return 一个从自身克隆出来的对象
     */
    public Prototype clone();
}

```

* **`接下来看看具体的原型实现对象，示例代码如下：`** 


```java
/**
   * 克隆的具体实现对象
   */
public class ConcretePrototype1 implements Prototype {
    public Prototype clone() {
       //最简单的克隆，新建一个自身对象，由于没有属性，就不去复制值了
       Prototype prototype = new ConcretePrototype1();
       return prototype;
    }
}

/**
 * 克隆的具体实现对象
 */
public class ConcretePrototype2 implements Prototype {
    public Prototype clone() {
       //最简单的克隆，新建一个自身对象，由于没有属性，就不去复制值了
       Prototype prototype = new ConcretePrototype2();
       return prototype;
    }
}

```

为了跟上面原型模式的结构示意图保持一致，因此这两个具体的原型实现对象，都没有定义属性。 **`事实上，在实际使用原型模式的应用中，原型对象多是有属性的，克隆原型的时候也是需要克隆原型对象的属性的，特此说明一下`** 。

* **`再看看使用原型的客户端，示例代码如下：`** 


```java
/**
   * 使用原型的客户端
   */
public class Client {
    /**
     * 持有需要使用的原型接口对象
     */
    private Prototype prototype;
    /**
     * 构造方法，传入需要使用的原型接口对象
     * @param prototype 需要使用的原型接口对象
     */
    public Client(Prototype prototype){
       this.prototype = prototype;
    }
    /**
     * 示意方法，执行某个功能操作
     */
    public void operation(){
       //会需要创建原型接口的对象
       Prototype newPrototype = prototype.clone();
    }
}

```
## 2.4 使用原型模式重写示例##

要使用原型模式来重写示例，先要在订单的接口上定义出克隆的接口，然后要求各个具体的订单对象克隆自身，这样就可以解决：在订单处理对象里面通过订单接口来创建新的订单对象的问题。

使用原型模式来重写示例的结构如图所示：


![][2]


原型模式来重写示例的结构


* **`复制谁和谁来复制的问题`** 


有了一个对象实例，要快速的创建跟它一样的实例，最简单的办法就是复制？这里又有两个小的问题：

 **`复制谁呢？`** 当然是复制这个对象实例，复制实例的意思是连带着数据一起复制。 **`谁来复制呢？`** 应该让这个类的实例自己来复制，自己复制自己。

可是每个对象不会那么听话，自己去实现复制自己的。于是 **`原型模式决定对这些对象实行强制要求，给这些对象定义一个接口，在接口里面定义一个方法，这个方法用来要求每个对象实现自己复制自己`** 。

由于现在存在订单的接口，因此就把这个要求克隆自身的方法定义在订单的接口里面，示例代码如下：

```java
/**
   * 订单的接口，声明了可以克隆自身的方法
   */
public interface OrderApi {
    public int getOrderProductNum();
    public void setOrderProductNum(int num);
    /**
     * 克隆方法
     * @return 订单原型的实例
     */
    public OrderApi cloneOrder();
}

```

* **`如何克隆`** 


定义好了克隆的接口，那么在订单的实现类里面，就得让它实现这个接口，并具体的实现这个克隆方法，新的问题出来了，如何实现克隆呢？

很简单， **`只要先new一个自己对象的实例，然后把自己实例中的数据取出来，设置到新的对象实例中去，不就可以完成实例的复制了嘛`** ，复制的结果就是有了一个跟自身一模一样的实例。

```java
/**
   * 个人订单对象
   */
public class PersonalOrder implements OrderApi{
    private String customerName;
    private String productId;
    private int orderProductNum = 0;

    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getCustomerName() {
       return customerName;
    }
    public void setCustomerName(String customerName) {
       this.customerName = customerName;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "本个人订单的订购人是="+this.customerName+"，订购产品是="+this.productId+"，订购数量为="+this.orderProductNum;
    }  
    public OrderApi cloneOrder() {
       //创建一个新的订单，然后把本实例的数据复制过去
       PersonalOrder order = new PersonalOrder();
       order.setCustomerName(this.customerName);
       order.setProductId(this.productId);
       order.setOrderProductNum(this.orderProductNum);

       return order;
    }
}

```

接下来看看企业订单的具体实现，示例代码如下：

```java
/**
   * 企业订单对象
   */
public class EnterpriseOrder implements OrderApi{
    private String enterpriseName;
    private String productId;  
    private int orderProductNum = 0;
    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getEnterpriseName() {
       return enterpriseName;
    }
    public void setEnterpriseName(String enterpriseName) {
       this.enterpriseName = enterpriseName;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "本企业订单的订购企业是="+this.enterpriseName+"，订购产品是="+this.productId+"，订购数量为="+this.orderProductNum;
    }
    public OrderApi cloneOrder() {
       //创建一个新的订单，然后把本实例的数据复制过去
       EnterpriseOrder order = new EnterpriseOrder();
       order.setEnterpriseName(this.enterpriseName);
       order.setProductId(this.productId);
       order.setOrderProductNum(this.orderProductNum);
       return order;
    }  
}

```

* **`使用克隆方法`** 


这里使用订单接口的克隆方法的，是订单的处理对象，也就是说， **`订单的处理对象就相当于原型模式结构中的Client。`** 

当然，客户端在调用clone方法之前，还需要先获得相应的实例对象，有了实例对象，才能调用该实例对象的clone方法。

这里使用克隆方法的时候，跟标准的原型实现有一些不同，在标准的原型实现的示例代码里面， **`客户端是持有需要克隆的对象，而这里变化成了通过方法传入需要使用克隆的对象`** ，这点大家注意一下。示例代码如下：

```java
public class OrderBusiness {
    /**
     * 创建订单的方法
     * @param order 订单的接口对象
     */
    public void saveOrder(OrderApi order){
       //1：判断当前的预定产品数量是否大于1000
       while(order.getOrderProductNum() > 1000){
           //2：如果大于，还需要继续拆分
           //2.1再新建一份订单，跟传入的订单除了数量不一样外，其它都相同
           OrderApi newOrder = order.cloneOrder();
           //然后进行赋值，产品数量为1000
           newOrder.setOrderProductNum(1000);

           //2.2原来的订单保留，把数量设置成减少1000
           order.setOrderProductNum(order.getOrderProductNum()-1000);

           //然后是业务功能处理，省略了，打印输出，看一下
           System.out.println("拆分生成订单=="+newOrder);
       }     
       //3：不超过，那就直接业务功能处理，省略了，打印输出，看一下
       System.out.println("订单=="+order);
    }
}

```
## 2.5 小提示##

看到这里，可能有些朋友会认为：Java的Object里面本身就有clone方法，还用搞得这么麻烦吗？ **`虽然Java里面有clone方法，上面这么做还是很有意义的，可以让我们更好的、更完整的体会原型这个设计模式`** 。当然，后面会讲述如何使用Java里面的clone方法来实现克隆，不要着急。
## 3 模式讲解#
## 3.1 认识原型模式##

* **`原型模式的功能`** 


原型模式的功能实际上包含两个方面：

一个是通过克隆来创建新的对象实例；

另一个是为克隆出来的新的对象实例复制原型实例属性的值；

原型模式要实现的主要功能就是： **`通过克隆来创建新的对象实例。一般来讲，新创建出来的实例的数据是和原型实例一样的`** 。但是具体如何实现克隆，需要由程序自行实现，原型模式并没有统一的要求和实现算法。

* **`原型与new`** 


原型模式从某种意义上说，就像是new操作，在前面的例子实现中，克隆方法就是使用new来实现的，但请注意，只是“类似于new”而不是“就是new”。

克隆方法和new操作最明显的不同就在于：

 **`new一个对象实例，一般属性是没有值的，或者是只有默认值；如果是克隆得到的一个实例，通常属性是有值的，属性的值就是原型对象实例在克隆的时候，原型对象实例的属性的值`** 。

* **`原型实例和克隆的实例`** 

 **`原型实例和克隆出来的实例，本质上是不同的实例，克隆完成后，它们之间是没有关联的，如果克隆完成后，克隆出来的实例的属性的值发生了改变，是不会影响到原型实例的`** 。下面写个示例来测试一下，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
       //先创建原型实例
       OrderApi oa1 = new PersonalOrder();

       //设置原型实例的订单数量的值
       oa1.setOrderProductNum(100);
       //为了简单，这里仅仅输出数量
       System.out.println("这是第一次获取的对象实例==="+oa1.getOrderProductNum());

       //通过克隆来获取新的实例
       OrderApi oa2 = (OrderApi)oa1.cloneOrder();
       //修改它的数量
       oa2.setOrderProductNum(80);
       //输出克隆出来的对象的值
       System.out.println("输出克隆出来的实例==="+oa2.getOrderProductNum());

       //再次输出原型实例的值
       System.out.println("再次输出原型实例==="+oa1.getOrderProductNum());  
    }
}

```

运行一下，看看结果：

```java
这是第一次获取的对象实例===100
输出克隆出来的实例===80
再次输出原型实例===100

```

仔细观察上面的结果，会发现 **`原型实例和克隆出来的实例是完全独立的，也就是它们指向不同的内存空间`** 。因为克隆出来的实例的值已经被改变了，而原型实例的值还是原来的值，并没有变化，这就说明两个实例是对应的不同内存空间。

* **`原型模式的调用顺序示意图`** 



![][3]


原型模式的调用顺序示意图

## 3.2 Java中的克隆方法##

在Java语言中已经提供了clone方法，定义在Object类中。关于Java中clone方法的知识，这里不去赘述，下面看看怎么使用Java里面的克隆方法来实现原型模式。 **`需要克隆功能的类，只需要实现java.lang.Cloneable接口，这个接口没有需要实现的方法，是一个标识接口。`** 因此在前面的实现中，把订单接口中的克隆方法去掉，现在直接实现Java中的接口就好了。新的订单接口实现，示例代码如下：

```java
public interface OrderApi {
    public int getOrderProductNum();
    public void setOrderProductNum(int num);
    // public OrderApi cloneOrder();
}

```

另外在具体的订单实现对象里面，实现方式上会有一些改变，个人订单和企业订单的克隆实现是类似的，因此示范一个就好了，看看个人订单的实现吧，示例代码如下：

```java
/**
 * 个人订单对象,利用Java的Clone功能
 */
public class PersonalOrder implements Cloneable  , OrderApi {
    private String customerName;
    private String productId;
    private int orderProductNum = 0;
    public int getOrderProductNum() {
        return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
        this.orderProductNum = num;
    }  
    public String getCustomerName() {
        return customerName;
    }
    public void setCustomerName(String customerName) {
        this.customerName = customerName;
    }
    public String getProductId() {
        return productId;
    }
    public void setProductId(String productId) {
        this.productId = productId;
    }
    public String toString(){
        return "本个人订单的订购人是="+this.customerName+"，订购产品是="+this.productId+"，订购数量为="+this.orderProductNum;
    }
    // public OrderApi cloneOrder() {
        // 创建一个新的订单，然后把本实例的数据复制过去
    //    PersonalOrder order = new PersonalOrder();
    //    order.setCustomerName(this.customerName);
    //    order.setProductId(this.productId);
    //    order.setOrderProductNum(this.orderProductNum);     
    //    return order;
    // }
    public Object clone() {
        //克隆方法的真正实现，直接调用父类的克隆方法就可以了
        Object obj = null;
        try {
            obj = super.clone();
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        return obj;
    }
}

```

看起来，比完全由自己实现原型模式要稍稍简单点，是否好用呢？还是测试一下，看看效果。客户端跟上一个示例相比，作了两点修改：

一个是原来的“OrderApi oa1 = new PersonalOrder();”这句话，要修改成：“PersonalOrder oa1 = new PersonalOrder();”。原因是现在的接口上并没有克隆的方法，因此需要修改成原型的类型；

另外一个是“通过克隆来获取新的实例”的实现，需要修改成使用原型来调用在Object里面定义的clone()方法了，不再是调用原来的cloneOrder()了。

看看测试用的代码，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        //先创建原型实例
        PersonalOrder oa1 = new PersonalOrder();     
        //设置原型实例的订单数量的值
        oa1.setOrderProductNum(100);
        System.out.println("这是第一次获取的对象实例==="+oa1.getOrderProductNum());      
        //通过克隆来获取新的实例
        PersonalOrder oa2 = (PersonalOrder)oa1.clone();
        oa2.setOrderProductNum(80);
        System.out.println("输出克隆出来的实例==="+oa2.getOrderProductNum());     
        //再次输出原型实例的值
        System.out.println("再次输出原型实例==="+oa1.getOrderProductNum());  
    }
}

```
## 3.3 浅度克隆和深度克隆##

无论你是自己实现克隆方法，还是采用Java提供的克隆方法，都存在一个浅度克隆和深度克隆的问题，那么什么是浅度克隆？什么是深度克隆呢？简单地解释一下：

 **`浅度克隆：`** 只负责克隆按值传递的数据（比如：基本数据类型、String类型） **`深度克隆：`** 除了浅度克隆要克隆的值外，还负责克隆引用类型的数据，基本上就是被克隆实例所有的属性的数据都会被克隆出来。

 **`深度克隆还有一个特点，如果被克隆的对象里面的属性数据是引用类型，也就是属性的类型也是对象，那么需要一直递归的克隆下去。`** 这也意味着，要想深度克隆成功，必须要整个克隆所涉及的对象都要正确实现克隆方法，如果其中有一个没有正确实现克隆，那么就会导致克隆失败。

在前面的例子中实现的克隆就是典型的浅度克隆，下面就来看看如何实现深度克隆。

* **`自己实现原型的深度克隆`** 

 **`（1）要演示深度克隆，需要给订单对象添加一个引用类型的属性，这样实现克隆过后，才能看出深度克隆的效果来。`** 

那就定义一个产品对象，也需要让它实现克隆的功能，产品对象实现的是一个浅度克隆。先来定义产品的原型接口，示例代码如下：

```java
/**
   * 声明一个克隆产品自身的接口
   */
public interface ProductPrototype {
    /**
     * 克隆产品自身的方法
     * @return 一个从自身克隆出来的产品对象
     */
    public ProductPrototype cloneProduct();
}

```

接下来看看具体的产品对象实现，示例代码如下：

```java
/**
   * 产品对象
   */
public class Product implements ProductPrototype{
    /**
     * 产品编号
     */
    private String productId;  
    /**
     * 产品名称
     */
    private String name;
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "产品编号="+this.productId+"，产品名称="+this.name;
    }
    public ProductPrototype cloneProduct() {
       //创建一个新的订单，然后把本实例的数据复制过去
       Product product = new Product();
       product.setProductId(this.productId);
       product.setName(this.name);    
       return product;
    }
}

``` **`（2）订单的具体实现上也需要改变一下，需要在其属性上添加一个产品类型的属性，然后也需要实现克隆方法，示例代码如下：`** 

```java
public class PersonalOrder implements OrderApi{
    private String customerName;
    private int orderProductNum = 0;
    /**
     * 产品对象
     */
    private Product product = null;
    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getCustomerName() {
       return customerName;
    }
    public void setCustomerName(String customerName) {
       this.customerName = customerName;
    }
    public Product getProduct() {
       return product;
    }
    public void setProduct(Product product) {
       this.product = product;
    }  
    public String toString(){
       //简单点输出
       return "订购产品是="+this.product.getName()+"，订购数量为="+this.orderProductNum;
    }
    public OrderApi cloneOrder() {
       //创建一个新的订单，然后把本实例的数据复制过去
       PersonalOrder order = new PersonalOrder();
       order.setCustomerName(this.customerName);
       order.setOrderProductNum(this.orderProductNum);
       //对于对象类型的数据，深度克隆的时候需要继续调用这个对象的克隆方法
       order.setProduct((Product)this.product.cloneProduct());
       return order;
    }
}

``` **`（3）写个客户端来测试看看，是否深度克隆成功，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
       //先创建原型实例
       PersonalOrder oa1 = new PersonalOrder();
       //设置原型实例的值
       Product product = new Product();
       product.setName("产品1");
       oa1.setProduct(product);
       oa1.setOrderProductNum(100);

       System.out.println("这是第一次获取的对象实例="+oa1);

       //通过克隆来获取新的实例
       PersonalOrder oa2 = (PersonalOrder)oa1.cloneOrder();
       //修改它的值
       oa2.getProduct().setName("产品2");
       oa2.setOrderProductNum(80);
       //输出克隆出来的对象的值
       System.out.println("输出克隆出来的实例="+oa2);

       //再次输出原型实例的值
       System.out.println("再次输出原型实例="+oa1);
    }
}

``` **`（4）运行结果如下，很明显，我们自己做的深度克隆是成功的：`** 

```java
这是第一次获取的对象实例=订购产品是=产品1，订购数量为=100
输出克隆出来的实例=订购产品是=产品2，订购数量为=80
再次输出原型实例=订购产品是=产品1，订购数量为=100

``` **`（5）小结`** 

看来自己实现深度克隆也不是很复杂，但是比较麻烦，如果产品类里面又有属性是引用类型的话，在产品类实现克隆方法的时候，又需要调用那个引用类型的克隆方法了，这样一层一层调下去，如果中途有任何一个对象没有正确实现深度克隆，那将会引起错误，这也是深度克隆容易出错的原因。

* **`Java中的深度克隆`** 

 **`（1）产品类没有太大的不同，主要是把实现的接口变成了Cloneable，这样一来，实现克隆的方法就不是cloneProduct，而是变成clone方法了；另外一个是克隆方法的实现变成了使用“super.clone();”了，示例代码如下：`** 

```java
public class Product implements Cloneable{
    private String productId;  
    private String name;
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
    public String getProductId() {
       return productId;
    }
    public void setProductId(String productId) {
       this.productId = productId;
    }
    public String toString(){
       return "产品编号="+this.productId+"，产品名称="+this.name;
    }
    public Object clone() {
       Object obj = null;
       try {
           obj = super.clone();
       } catch (CloneNotSupportedException e) {
           e.printStackTrace();
       }
       return obj;
    }  
}

``` **`（2）具体的订单实现类，除了改变接口外，更重要的是在实现clone方法的时候，除了调用“super.clone();”外，必须显示的调用引用类型属性的clone方法，也就是产品的clone方法，示例代码如下：`** 

```java
public class PersonalOrder implements Cloneable , OrderApi{
    private String customerName;
    private Product product = null;
    private int orderProductNum = 0;  
    public int getOrderProductNum() {
       return this.orderProductNum;
    }  
    public void setOrderProductNum(int num) {
       this.orderProductNum = num;
    }  
    public String getCustomerName() {
       return customerName;
    }
    public void setCustomerName(String customerName) {
       this.customerName = customerName;
    }
    public Product getProduct() {
       return product;
    }
    public void setProduct(Product product) {
       this.product = product;
    }  
    public String toString(){
       //简单点输出
       return "订购产品是="+this.product.getName()+"，订购数量为="+this.orderProductNum;
    }
    public Object clone(){
       PersonalOrder obj=null;
       try {
          obj =(PersonalOrder)super.clone();
          //下面这一句话不可少
          obj.setProduct((Product)this.product.clone());
       } catch (CloneNotSupportedException e) {
          e.printStackTrace();
       }     
       return obj;
    }
}

``` **`（3）特别强调：不可缺少“obj.setProduct((Product)this.product.clone());”这句话。为什么呢？`** 

原因在于调用super.clone()方法的时候， **`Java是先开辟一块内存的空间，然后把实例对象的值原样拷贝过去，对于基本数据类型这样做是没有问题的，而属性product是一个引用类型，把值拷贝过去的意思就是把对应的内存地址拷贝过去了，也就是说克隆后的对象实例的product和原型对象实例的product指向的是同一块内存空间，是同一个产品实例`** 。

因此要想正确的执行深度拷贝， **`必须手工的对每一个引用类型的属性进行克隆，并重新设置，覆盖掉super.clone()所拷贝的值`** 。
## 3.4 原型管理器##

如果一个系统中原型的数目不固定，比如系统中的原型可以被动态的创建和销毁，那么就需要在系统中维护一个当前可用的原型的注册表，这个注册表就被称为原型管理器。

其实如果把原型当成一个资源的话， **`原型管理器就相当于一个资源管理器，在系统开始运行的时候初始化，然后运行期间可以动态的添加资源和销毁资源`** 。从这个角度看，原型管理器就可以相当于一个缓存资源的实现，只不过里面缓存和管理的是原型实例而已。 **`有了原型管理器过后，一般情况下，除了向原型管理器里面添加原型对象的时候是通过new来创造的对象，其余时候都是通过向原型管理器来请求原型实例，然后通过克隆方法来获取新的对象实例，这就可以实现动态管理、或者动态切换具体的实现对象实例。`** 

还是通过示例来说明，如何实现原型管理器。

* **`先定义原型的接口，非常简单，除了克隆方法，提供一个名称的属性，示例代码如下：`** 


```java
public interface Prototype {
    public Prototype clone();
    public String getName();
    public void setName(String name);
}

```

* **`再来看看两个具体的实现，实现方式基本上是一样的，分别看看。先看第一个原型的实现，示例代码如下：`** 


```java
public class ConcretePrototype1 implements Prototype {
    private String name;
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
    public Prototype clone() {
       ConcretePrototype1 prototype = new ConcretePrototype1();
       prototype.setName(this.name);
       return prototype;
    }
    public String toString(){
       return "Now in Prototype1，name="+name;
    }
}

```

再看看第二个原型的实现，示例代码如下：

```java
public class ConcretePrototype2 implements Prototype {
    private String name;
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
    public Prototype clone() {
       ConcretePrototype2 prototype = new ConcretePrototype2();
       prototype.setName(this.name);
       return prototype;
    }  
    public String toString(){
       return "Now in Prototype2，name="+name;
    }
}

```

* **`接下来看看原型管理器的实现示意，示例代码如下：`** 


```java
/**
 * 原型管理器
 */
public class PrototypeManager {
    /**
     * 用来记录原型的编号和原型实例的对应关系
     */
    private static Map<String,Prototype> map = new HashMap<String,Prototype>();
    /**
     * 私有化构造方法，避免外部无谓的创建实例
     */
    private PrototypeManager(){
       //
    }
    /**
     * 向原型管理器里面添加或是修改某个原型注册
     * @param prototypeId 原型编号
     * @param prototype 原型实例
     */
    public synchronized static void setPrototype(String prototypeId,Prototype prototype){
       map.put(prototypeId, prototype);
    }
    /**
     * 从原型管理器里面删除某个原型注册
     * @param prototypeId 原型编号
     */
    public synchronized static void removePrototype(String prototypeId){
       map.remove(prototypeId);
    }
    /**
     * 获取某个原型编号对应的原型实例
     * @param prototypeId 原型编号
     * @return 原型编号对应的原型实例
     * @throws Exception 如果原型编号对应的原型实例不存在，报出例外
     */
    public synchronized static Prototype getPrototype(String prototypeId)throws Exception{
       Prototype prototype = map.get(prototypeId);
       if(prototype == null){
           throw new Exception("您希望获取的原型还没有注册或已被销毁");
       }
       return prototype;
    }
}

```

大家会发现， **`原型管理器是类似一个工具类的实现方式，而且对外的几个方法都是加了同步的，这主要是因为如果在多线程环境下使用这个原型管理器的话，那个map属性很明显就成了大家竞争的资源，因此需要加上同步`** 。

* **`接下来看看客户端，如何使用这个原型管理器，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
       try {
           // 初始化原型管理器
           Prototype p1 = new ConcretePrototype1();
           PrototypeManager.setPrototype("Prototype1", p1);

           // 获取原型来创建对象
           Prototype p3 = PrototypeManager.getPrototype("Prototype1").clone();
           p3.setName("张三");
           System.out.println("第一个实例：" + p3);

           // 有人动态的切换了实现
           Prototype p2 = new ConcretePrototype2();
           PrototypeManager.setPrototype("Prototype1", p2);

           // 重新获取原型来创建对象
           Prototype p4 = PrototypeManager.getPrototype("Prototype1").clone();
           p4.setName("李四");
           System.out.println("第二个实例：" + p4);

           // 有人注销了这个原型
           PrototypeManager.removePrototype("Prototype1");

           // 再次获取原型来创建对象
           Prototype p5 = PrototypeManager.getPrototype("Prototype1").clone();
           p5.setName("王五");
           System.out.println("第三个实例：" + p5);
       } catch (Exception err) {
           System.err.println(err.getMessage());
       }
    }
}

```

运行一下，看看结果，结果示例如下：

```java
第一个实例：Now in Prototype1，name=张三
第二个实例：Now in Prototype2，name=李四
您希望获取的原型还没有注册或已被销毁

```
## 3.5  原型模式的优缺点##

* **`对客户端隐藏具体的实现类型`** 


原型模式的客户端，只知道原型接口的类型，并不知道具体的实现类型，从而减少了客户端对这些具体实现类型的依赖。

* **`在运行时动态改变具体的实现类型`** 


原型模式可以在运行期间，由客户来注册符合原型接口的实现类型，也可以动态的改变具体的实现类型，看起来接口没有任何变化，但其实运行的已经是另外一个类实例了。因为克隆一个原型就类似于实例化一个类。

* **`深度克隆方法实现会比较困难`** 


原型模式最大的缺点就在于每个原型的子类都必须实现clone的操作，尤其在包含引用类型的对象时，clone方法会比较麻烦，必须要能够递归的让所有的相关对象都要正确的实现克隆。
## 3.6 思考原型模式##

* **`原型模式的本质`** 

 **`原型模式的本质：克隆生成对象。`**  **`克隆是手段，目的还是生成新的对象实例`** 。正是因为原型的目的是为了生成新的对象实例， **`原型模式通常是被归类为创建型的模式`** 。

原型模式也可以用来解决“只知接口而不知实现的问题”，使用原型模式，可以出现一种独特的“接口造接口”的景象，这在面向接口编程中很有用。同样的功能也可以考虑使用工厂来实现。

另外， **`原型模式的重心还是在创建新的对象实例`** ，至于创建出来的对象，其属性的值是否一定要和原型对象属性的值完全一样，这个并没有强制规定，只不过在目前大多数实现中，克隆出来的对象和原型对象的属性值是一样的。

也就是说， **`可以通过克隆来创造值不一样的实例，但是对象类型必须一样`** 。可以有部分甚至是全部的属性的值不一样，可以有选择性的克隆，就当是标准原型模式的一个变形使用吧。

* **`何时选用原型模式`** 


建议在如下情况中，选用原型模式：

 **`如果一个系统想要独立于它想要使用的对象时`** ，可以使用原型模式，让系统只面向接口编程，在系统需要新的对象的时候，可以通过克隆原型来得到； **`如果需要实例化的类是在运行时刻动态指定时`** ，可以使用原型模式，通过克隆原型来得到需要的实例；

## 3.7 相关模式##

* **`原型模式和抽象工厂模式`** 


功能上有些相似，都是用来获取一个新的对象实例的。

不同之处在于， **`原型模式的着眼点是在如何创造出实例对象来，最后选择的方案是通过克隆`** ；而 **`抽象工厂模式的着眼点则在于如何来创造产品簇，至于具体如何创建出产品簇中的每个对象实例，抽象工厂模式不是很关注`** 。

正是因为它们的关注点不一样，所以它们也可以配合使用，比如在抽象工厂模式里面，具体创建每一种产品的时候就可以使用该种产品的原型，也就是抽象工厂管产品簇，具体的每种产品怎么创建则可以选择原型模式。

* **`原型模式和生成器模式`** 


这两种模式可以配合使用。 **`生成器模式关注的是构建的过程`** ，而在构建的过程中，很可能需要某个部件的实例，那么很自然地就可以应用上原型模式，通过原型模式来得到部件的实例。


[0]: ./img/2062729-326eeb44b0083a75.png
[1]: ./img/2062729-f14ec24f866b6cfb.png
[2]: ./img/2062729-e239004f5eadfc40.png
[3]: ./img/2062729-7304586f9fd0550c.png