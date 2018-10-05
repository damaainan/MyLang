## 【创建型模式三】抽象工厂(Abstract Factory)

2016.06.07 15:35*

来源：[https://www.jianshu.com/p/e873855e88a0](https://www.jianshu.com/p/e873855e88a0)


          
## 1 场景问题#
## 1.1 选择组装电脑的配件##

举个生活中常见的例子——组装电脑，我们在组装电脑的时候，通常需要选择一系列的配件，比如：CPU、硬盘、内存、主板、电源、机箱等等。为了使讨论简单点，只考虑选择CPU和主板的问题。

事实上，我们在选择CPU的时候，面临一系列的问题，比如：品牌、型号、针脚数目、主频等问题，只有把这些都确定下来，才能确定具体的CPU。同样，在选择主板的时候，也有一系列的问题，比如：品牌、芯片组、集成芯片、总线频率等问题，也只有这些都确定了，才能确定具体的主板。

选择不同的CPU和主板，是每个客户去组装电脑的时候，向装机公司提出的要求，也就是我们每个人自己拟定的装机方案。

在最终确定这个装机方案之前，还需要整体考虑各个配件之间的兼容性，比如：CPU和主板，如果CPU针脚数和主板提供的CPU插口不兼容，是无法组装的。也就是说， **`装机方案是有整体性的，里面选择的各个配件之间是有关联的`** 。

对于装机工程师而言，他只知道组装一台电脑，需要相应的配件，但是具体使用什么样的配件，还得由客户说了算。 **`也就是说装机工程师只是负责组装，而客户负责选择装配所需要的具体的配件。`** 因此，当装机工程师为不同的客户组装电脑时，只需要按照客户的装机方案，去获取相应的配件，然后组装即可。

现在需要使用程序来把这个装机的过程，尤其是选择组装电脑配件的过程实现出来，该如何实现呢？
## 1.2 不用模式的解决方案##

考虑客户的功能，需要选择自己需要的CPU和主板，然后告诉装机工程师自己的选择，接下来就等着装机工程师组装机器了。

对装机工程师而言，只是知道CPU和主板的接口，而不知道具体实现，很明显可以用上简单工厂或工厂方法模式，为了简单，这里选用简单工厂吧。客户告诉装机工程师自己的选择，然后装机工程师会通过相应的工厂去获取相应的实例对象。

* **`先来看看CPU和主板的接口，先看CPU的接口定义，示例代码如下：`** 


```java
/** 
   * CPU的接口 
   */  
public interface CPUApi {  
      /** 
       * 示意方法，CPU具有运算的功能 
       */  
      public void calculate();  
}  

```

再看看主板的接口定义，示例代码如下：

```java
/**
   * Mainboard的接口
   */
public interface MainboardApi {
     public void installCPU();
}

```

* **`接下来看看具体的CPU实现，先看Intel的CPU实现，示例代码如下：`** 


```java
/** 
   * Intel的CPU实现 
   */  
public class IntelCPU implements CPUApi{  
      /** 
       * CPU的针脚数目 
       */  
      private int pins = 0;  
      /** 
       * 构造方法，传入CPU的针脚数目 
       * @param pins CPU的针脚数目 
       */  
      public IntelCPU(int pins){  
          this.pins = pins;  
      }  
      public void calculate() {  
          System.out.println("now in Intel CPU,pins="+pins);  
      }  
}  

```

再看看AMD的CPU实现，示例代码如下：

```java
/** 
   * AMD的CPU实现 
   */  
public class AMDCPU implements CPUApi{  
      /** 
       * CPU的针脚数目 
       */  
      private int pins = 0;  
      /** 
       * 构造方法，传入CPU的针脚数目 
       * @param pins CPU的针脚数目 
       */  
      public AMDCPU(int pins){  
          this.pins = pins;  
      }  
      public void calculate() {  
          System.out.println("now in AMD CPU,pins="+pins);  
      }  
}  

```

* **`接下来看看具体的主板实现，先看技嘉的主板实现，示例代码如下：`** 


```java
/** 
   * 技嘉的主板 
   */  
public class GAMainboard implements MainboardApi {  
      /** 
       * CPU插槽的孔数 
       */  
      private int cpuHoles = 0;  
      /** 
       * 构造方法，传入CPU插槽的孔数 
       * @param cpuHoles CPU插槽的孔数 
       */  
      public GAMainboard(int cpuHoles){  
          this.cpuHoles = cpuHoles;  
      }  
      public void installCPU() {  
          System.out.println("now in GAMainboard,cpuHoles=" + cpuHoles);  
      }  
}  

```

再看看微星的主板实现，示例代码如下：

```java
/** 
   * 微星的主板 
   */  
public class MSIMainboard implements MainboardApi{  
      /** 
       * CPU插槽的孔数 
       */  
      private int cpuHoles = 0;  
      /** 
       * 构造方法，传入CPU插槽的孔数 
       * @param cpuHoles CPU插槽的孔数 
       */  
      public MSIMainboard(int cpuHoles){  
          this.cpuHoles = cpuHoles;  
      }  
      public void installCPU() {  
          System.out.println("now in MSIMainboard,cpuHoles=" + cpuHoles);  
      }
}  

```

* **`接下来看看创建CPU和主板的工厂，先看创建CPU的工厂实现，示例代码如下：`** 


```java
/** 
   * 创建CPU的简单工厂 
   */  
public class CPUFactory {  
      /** 
       * 创建CPU接口对象的方法 
       * @param type 选择CPU类型的参数 
       * @return CPU接口对象的方法 
       */  
      public static CPUApi createCPUApi(int type){  
          CPUApi cpu = null;  
          //根据参数来选择并创建相应的CPU对象  
          if(type==1){  
              cpu = new IntelCPU(1156);  
          }else if(type==2){  
              cpu = new AMDCPU(939);  
          }  
          return cpu;  
      }    
}  

```

再看看创建主板的工厂实现，示例代码如下：

```java
/** 
   * 创建主板的简单工厂 
   */  
public class MainboardFactory {  
      /** 
       * 创建主板接口对象的方法 
       * @param type 选择主板类型的参数 
       * @return 主板接口对象的方法 
       */  
      public static MainboardApi createMainboardApi(int type){  
          MainboardApi mainboard = null;  
          //根据参数来选择并创建相应的主板对象  
          if(type==1){  
              mainboard = new GAMainboard(1156);  
          }else if(type==2){  
              mainboard = new MSIMainboard(939);  
          }  
          return mainboard;  
      }  
}  

```

* **`接下来看看装机工程师的实现，示例代码如下：`** 


```java
/** 
   * 装机工程师的类 
   */  
public class ComputerEngineer {  
      /** 
       * 定义组装机器需要的CPU 
       */  
      private CPUApi cpu= null;  
      /** 
       * 定义组装机器需要的主板 
       */  
      private MainboardApi mainboard = null;  
      /** 
       * 装机过程 
       * @param cpuType 客户选择所需CPU的类型 
       * @param mainboardType 客户选择所需主板的类型 
       */  
      public void makeComputer(int cpuType,int mainboardType){  
          //1：首先准备好装机所需要的配件  
          prepareHardwares(cpuType,mainboardType);  
          //2：组装机器       
          //3：测试机器       
          //4：交付客户  
      }  
      /** 
       * 准备装机所需要的配件 
       * @param cpuType 客户选择所需CPU的类型 
       * @param mainboardType 客户选择所需主板的类型 
       */  
      private void prepareHardwares(int cpuType,int mainboardType){  
          //这里要去准备CPU和主板的具体实现，为了示例简单，这里只准备这两个  
          //可是，装机工程师并不知道如何去创建，怎么办呢？  

          //直接找相应的工厂获取  
          this.cpu = CPUFactory.createCPUApi(cpuType);  
          this.mainboard = MainboardFactory.createMainboardApi(mainboardType);  
          //测试一下配件是否好用  
          this.cpu.calculate();  
          this.mainboard.installCPU();  
      }  
} 

```

* **`看看此时的客户端，应该通过装机工程师来组装电脑，客户需要告诉装机工程师他选择的配件，示例代码如下：`** 


```java
public class Client {  
      public static void main(String[] args) {  
          //创建装机工程师对象  
          ComputerEngineer engineer = new ComputerEngineer();  
          //告诉装机工程师自己选择的配件，让装机工程师组装电脑  
          engineer.makeComputer(1,1);  
      }  
}  

```
## 1.3 有何问题##

看了上面的实现，会感觉到很简单嘛，通过使用简单工厂来获取需要的CPU和主板对象，然后就可以组装电脑了。有何问题呢？

虽然上面的实现，通过简单工厂解决解决了：对于装机工程师，只知CPU和主板的接口，而不知道具体实现的问题。但还有一个问题没有解决，什么问题呢？ **`那就是这些CPU对象和主板对象其实是有关系的，是需要相互匹配的`** 。而在上面的实现中，并没有维护这种关联关系，CPU和主板是由客户随意选择的。这是有问题的。 **`这就是没有维护配件之间的关系造成的。该怎么解决这个问题呢？`** 
## 2 解决方案#
## 2.1 抽象工厂模式来解决##

用来解决上述问题的一个合理的解决方案就是抽象工厂模式。那么什么是抽象工厂模式呢？

* **`抽象工厂模式定义`** 



![][0]


抽象工厂模式定义


* **`应用抽象工厂模式来解决的思路`** 


仔细分析上面的问题，其实有两个问题点，一个是只知道所需要的一系列对象的接口，而不知具体实现，或者是不知道具体使用哪一个实现；另外一个是这一系列对象是相关或者相互依赖的。 **`也就是说既要创建接口的对象，还要约束它们之间的关系。`** 

有朋友可能会想，工厂方法模式或者是简单工厂，不就可以解决只知接口而不知实现的问题吗？怎么这些问题又冒出来了呢？

请注意，这里要解决的问题和工厂方法模式或简单工厂解决的问题是有很大不同的， **`工厂方法模式或简单工厂关注的是单个产品对象的创建`** ，比如创建CPU的工厂方法，它就只关心如何创建CPU的对象，而创建主板的工厂方法，就只关心如何创建主板对象。

 **`这里要解决的问题是，要创建一系列的产品对象，而且这一系列对象是构建新的对象所需要的组成部分，也就是这一系列被创建的对象相互之间是有约束的。`** 

 **`解决这个问题的一个解决方案就是抽象工厂模式。`** 在这个模式里面，会定义一个抽象工厂，在里面虚拟的创建客户端需要的这一系列对象， **`所谓虚拟的就是定义创建这些对象的抽象方法，并不去真的实现，然后由具体的抽象工厂的子类来提供这一系列对象的创建`** 。这样一来可以为同一个抽象工厂提供很多不同的实现，那么创建的这一系列对象也就不一样了，也就是说， **`抽象工厂在这里起到一个约束的作用，并提供所有子类的一个统一外观，来让客户端使用`** 。
## 2.2 模式结构和说明##

抽象工厂模式结构如图所示：


![][1]


抽象工厂模式结构


AbstractFactory：抽象工厂，定义创建一系列产品对象的操作接口。

ConcreteFactory：具体的工厂，实现抽象工厂定义的方法，具体实现一系列产品对象的创建。

AbstractProduct：定义一类产品对象的接口。

ConcreteProduct：具体的产品实现对象，通常在具体工厂里面，会选择具体的产品实现对象，来创建符合抽象工厂定义的方法返回的产品类型的对象。

Client：客户端，主要使用抽象工厂来获取一系列所需要的产品对象，然后面向这些产品对象的接口编程，以实现需要的功能。

## 2.3 抽象工厂模式示例代码##

* **`先看看抽象工厂的定义，示例代码如下：`** 


```java
/** 
   * 抽象工厂的接口，声明创建抽象产品对象的操作 
   */  
public interface AbstractFactory {  
      /** 
       * 示例方法，创建抽象产品A的对象 
       * @return 抽象产品A的对象 
       */  
      public AbstractProductA createProductA();  
      /** 
       * 示例方法，创建抽象产品B的对象 
       * @return 抽象产品B的对象 
       */  
      public AbstractProductB createProductB();  
}  

```

* **`接下来看看产品的定义，由于只是示意，并没有去定义具体的方法，示例代码如下：`** 


```java
/** 
   * 抽象产品A的接口 
   */  
public interface AbstractProductA {  
      //定义抽象产品A相关的操作  
} 

/** 
   * 抽象产品B的接口 
   */  
public interface AbstractProductB {  
      //定义抽象产品B相关的操作  
}  

```

* **`同样的，产品的各个实现对象也是空的，示例代码如下：`** 


```java
/** 
   * 产品A的具体实现 
   */  
public class ProductA1 implements AbstractProductA {  
      //实现产品A的接口中定义的操作  
}  

/** 
   * 产品A的具体实现 
   */  
public class ProductA2 implements AbstractProductA {  
      //实现产品A的接口中定义的操作  
} 

/** 
   * 产品B的具体实现 
   */  
public class ProductB1 implements AbstractProductB {  
      //实现产品B的接口中定义的操作  
}  

/** 
   * 产品B的具体实现 
   */  
public class ProductB2 implements AbstractProductB {  
      //实现产品B的接口中定义的操作  
}

```

* **`接下来看看具体的工厂的实现示意，示例代码如下：`** 


```java
/** 
   * 具体的工厂实现对象，实现创建具体的产品对象的操作 
   */  
public class ConcreteFactory1 implements AbstractFactory {  
      public AbstractProductA createProductA() {  
          return new ProductA1();  
      }  
      public AbstractProductB createProductB() {  
          return new ProductB1();  
      }  
} 

/** 
   * 具体的工厂实现对象，实现创建具体的产品对象的操作 
   */  
public class ConcreteFactory2 implements AbstractFactory {  
      public AbstractProductA createProductA() {  
          return new ProductA2();  
      }  
      public AbstractProductB createProductB() {  
          return new ProductB2();  
      }  
}   

```

* **`最后来看看客户端的实现示意，示例代码如下：`** 


```java
public class Client {  
      public static void main(String[] args) {  
          //创建抽象工厂对象  
          AbstractFactory af = new ConcreteFactory1();  
          //通过抽象工厂来获取一系列的对象，如产品A和产品B  
          af.createProductA();  
          af.createProductB();  
      }  
}  

```
## 2.4 使用抽象工厂模式重写示例##

要使用抽象工厂模式来重写示例，先来看看如何使用抽象工厂模式来解决前面提出的问题。

装机工程师要组装电脑对象，需要一系列的产品对象，比如CPU、主板等，于是创建一个抽象工厂给装机工程师使用，在这个抽象工厂里面定义抽象的创建CPU和主板的方法， **`这个抽象工厂就相当于一个抽象的装机方案，在这个装机方案里面，各个配件是能够相互匹配的`** 。

每个装机的客户，会提出他们自己的具体装机方案， **`或者是选择已有的装机方案，相当于为抽象工厂提供了具体的子类`** ，在这些具体的装机方案类里面，会创建具体的CPU和主板实现对象。

此时系统的结构如图所示：


![][2]


系统的结构


虽然说是重写示例，但并不是前面写的都不要了，而是修改前面的示例，使它能更好的实现需要的功能。

* **`前面示例实现的CPU接口和CPU实现对象，还有主板的接口和实现对象，都不需要变化，这里就不去赘述了。`** 

* **`前面示例中的创建CPU的简单工厂和创建主板的简单工厂，都不再需要了，直接删除即可，这里也就不去管了。`** 

* **`看看新加入的抽象工厂的定义，示例代码如下：`** 

```java
/** 
   * 抽象工厂的接口，声明创建抽象产品对象的操作 
   */  
public interface AbstractFactory {  
      /** 
       * 创建CPU的对象 
       * @return CPU的对象 
       */  
      public CPUApi createCPUApi();  
      /** 
       * 创建主板的对象 
       * @return 主板的对象 
       */  
      public MainboardApi createMainboardApi();  
}  

```

* **`再看看抽象工厂的实现对象，也就是具体的装机方案对象，先看看装机方案一的实现，示例代码如下：`** 


```java
/** 
   * 装机方案一：Intel 的CPU + 技嘉的主板 
   * 这里创建CPU和主板对象的时候，是对应的，能匹配上的 
   */  
public class Schema1 implements AbstractFactory{  
      public CPUApi createCPUApi() {  
          return new IntelCPU(1156);  
      }  
      public MainboardApi createMainboardApi() {  
          return new GAMainboard(1156);  
      }    
}  

/** 
   * 装机方案二：AMD的CPU + 微星的主板 
   * 这里创建CPU和主板对象的时候，是对应的，能匹配上的 
   */  
public class Schema2 implements AbstractFactory{  
      public CPUApi createCPUApi() {  
          return new AMDCPU(939);  
      }  
      public MainboardApi createMainboardApi() {  
          return new MSIMainboard(939);  
      }    
}

```

* **`再来看看装机工程师类的实现，在现在的实现里面，装机工程师相当于使用抽象工厂的客户端，虽然是由真正的客户来选择和创建具体的工厂对象，但是使用抽象工厂的是装机工程师对象。`** 


装机工程师类跟前面的实现相比，主要的变化是：从客户端，不再传入选择CPU和主板的参数，而是直接传入客户选择并创建好的装机方案对象。 **`这样就避免了单独去选择CPU和主板，客户要选就是一套，就是一个系列`** 。示例代码如下：

```java
/** 
   * 装机工程师的类 
   */  
public  class ComputerEngineer {  
      /** 
       * 定义组装机器需要的CPU 
       */  
      private CPUApi cpu= null;  
      /** 
       * 定义组装机器需要的主板 
       */  
      private MainboardApi mainboard = null;  

      /** 
       * 装机过程 
       * @param schema 客户选择的装机方案 
       */  
      public void makeComputer(AbstractFactory schema){  
          //1：首先准备好装机所需要的配件  
          prepareHardwares(schema);  
          //2：组装机器       
          //3：测试机器       
          //4：交付客户  
      }  
      /** 
       * 准备装机所需要的配件 
       * @param schema 客户选择的装机方案 
       */  
      private void prepareHardwares(AbstractFactory schema){  
          //这里要去准备CPU和主板的具体实现，为了示例简单，这里只准备这两个  
          //可是，装机工程师并不知道如何去创建，怎么办呢？  

          //使用抽象工厂来获取相应的接口对象  
          this.cpu = schema.createCPUApi();  
          this.mainboard = schema.createMainboardApi();  

          //测试一下配件是否好用  
          this.cpu.calculate();  
          this.mainboard.installCPU();  
      }  
}  

```

* **`都定义好了，看看客户端如何使用抽象工厂，示例代码如下：`** 


```java
public class Client {  
      public static void main(String[] args) {  
          //创建装机工程师对象  
          ComputerEngineer engineer = new ComputerEngineer();  
          //客户选择并创建需要使用的装机方案对象  
          AbstractFactory schema = new Schema1();  
          //告诉装机工程师自己选择的装机方案，让装机工程师组装电脑  
          engineer.makeComputer(schema);  
      }
}

```

如同前面的示例，定义了一个抽象工厂AbstractFactory，在里面定义了创建CPU和主板对象的接口的方法，但是在抽象工厂里面，并没有指定具体的CPU和主板的实现，也就是无须指定它们具体的实现类。

CPU和主板是相关的对象，是构建电脑的一系列相关配件，这个抽象工厂就相当于一个装机方案，客户选择装机方案的时候，一选就是一套，CPU和主板是确定好的，不让客户分开选择，这就避免了出现不匹配的错误。
## 3 模式讲解#
## 3.1 认识抽象工厂模式##

* **`模式的功能`** 


抽象工厂的功能是为一系列相关对象或相互依赖的对象创建一个接口， **`一定要注意，这个接口内的方法不是任意堆砌的，而是一系列相关或相互依赖的方法`** ，比如上面例子中的CPU和主板，都是为了组装一台电脑的相关对象。

从某种意义上看， **`抽象工厂其实是一个产品系列，或者是产品簇`** 。上面例子中的抽象工厂就可以看成是电脑簇，每个不同的装机方案，代表一种具体的电脑系列。

* **`实现成接口`** 

 **`AbstractFactory在Java中通常实现成为接口`** ，大家不要被名称误导了，以为是实现成为抽象类，当然， **`如果需要为这个产品簇提供公共的功能，也不是不可以把AbstractFactory实现成为抽象类`** ，但一般不这么做。

* **`使用工厂方法`** 


AbstractFactory定义了创建产品所需要的接口，具体的实现是在实现类里面，通常在实现类里面就需要选择多种更具体的实现， **`所以AbstractFactory定义的创建产品的方法可以看成是工厂方法，而这些工厂方法的具体实现就延迟到了具体的工厂里面`** 。也就是说 **`使用工厂方法来实现抽象工厂`** 。

* **`切换产品簇`** 


由于抽象工厂定义的一系列对象，通常是相关或者相依赖的，这些产品对象就构成了一个产品簇，也就是抽象工厂定义了一个产品簇。这就带来非常大的灵活性， **`切换一个产品簇的时候，只要提供不同的抽象工厂实现就好了，也就是说现在是以产品簇做为一个整体被切换`** 。

* **`抽象工厂模式的调用顺序示意图`** 



![][3]


抽象工厂模式的调用顺序示意图

## 3.2 定义可扩展的工厂##

在前面的示例中，抽象工厂为每一种它能创建的产品对象都定义了相应的方法，比如创建CPU的方法和创建主板的方法等。

 **`这种实现有一个麻烦，就是如果在产品簇中要新增加一种产品，比如现在要求抽象工厂除了能够创建CPU和主板外，还要能够创建内存对象，那么就需要在抽象工厂里面添加创建内存的这么一个方法。当抽象工厂一发生变化，所有的具体工厂实现都要发生变化，这非常的不灵活。`** 

现在有一种相对灵活，但是不太安全的改进方式来解决这个问题，思路如下： **`抽象工厂里面不需要定义那么多方法，定义一个方法就可以了，给这个方法设置一个参数，通过这个参数来判断具体创建什么产品对象；由于只有一个方法，在返回类型上就不能是具体的某个产品类型了，只能是所有的产品对象都继承或者实现的这么一个类型，比如让所有的产品都实现某个接口，或者干脆使用Object类型。`** 

还是看看代码来体会一下，把前面那个示例改造成可扩展的工厂实现。

* **`先来改造抽象工厂，示例代码如下：`** 


```java
/** 
   * 可扩展的抽象工厂的接口 
   */  
public interface AbstractFactory {  
      /** 
       * 一个通用的创建产品对象的方法，为了简单，直接返回Object 
       * 也可以为所有被创建的产品定义一个公共的接口 
       * @param type 具体创建的产品类型标识 
       * @return 创建出的产品对象 
       */  
      public Object createProduct(int type);  
}

```

这里要特别注意传入createProduct的参数所代表的含义， **`这个参数只是用来标识现在是在创建什么类型的产品`** ，比如标识现在是创建CPU还是创建主板，一般这个type的含义到此就结束了，不再进一步表示具体是什么样的CPU或具体什么样的主板， **`也就是说type不再表示具体是创建Intel的CPU还是创建AMD的CPU，这就是一个参数所代表的含义的深度的问题，要注意`** 。虽然也可以延伸参数的含义到具体的实现上，但这不是可扩展工厂这种设计方式的本意，一般也不这么做。

* **`CPU的接口和实现，主板的接口和实现跟前面的示例是一样的，就不再示范了。CPU还是分成Intel的CPU和AMD的CPU，主板还是分成技嘉的主板和微星的主板。`** 

* **`下面来提供具体的工厂实现，也就是相当于以前的装机方案，先改造原来的方案一吧，现在的实现会有较大的变化，示例代码如下：`** 

```java
/** 
   * 装机方案一：Intel 的CPU + 技嘉的主板 
   * 这里创建CPU和主板对象的时候，是对应的，能匹配上的 
   */  
public class Schema1 implements AbstractFactory{  
      public Object createProduct(int type) {  
          Object retObj = null;  
          //type为1表示创建CPU，type为2表示创建主板  
          if(type==1){  
              retObj = new IntelCPU(1156);  
          }else if(type==2){  
              retObj = new GAMainboard(1156);  
          }  
          return retObj;  
      }    
} 

/** 
   * 装机方案二：AMD的CPU + 微星的主板 
   * 这里创建CPU和主板对象的时候，是对应的，能匹配上的 
   */  
public class Schema2 implements AbstractFactory{  
      public Object createProduct(int type) {  
          Object retObj = null;  
          //type为1表示创建CPU，type为2表示创建主板  
          if(type==1){  
              retObj = new AMDCPU(939);  
          }else if(type==2){  
              retObj = new MSIMainboard(939);  
          }  
          return retObj;  
      }    
}

```

* **`看看这个时候使用抽象工厂的客户端实现，也就是在装机工程师类里面，通过抽象工厂来获取相应的配件产品对象，示例代码如下：`** 


```java
public  class ComputerEngineer {  
      private CPUApi cpu= null;  
      private MainboardApi mainboard = null;  
      public void makeComputer(AbstractFactory schema){  
          prepareHardwares(schema);  
      }  
      private void prepareHardwares(AbstractFactory schema){  
          //这里要去准备CPU和主板的具体实现，为了示例简单，这里只准备这两个  
          //可是，装机工程师并不知道如何去创建，怎么办呢？  

          //使用抽象工厂来获取相应的接口对象  
          this.cpu = (CPUApi)schema.createProduct(1);  
          this.mainboard = (MainboardApi)schema.createProduct(2);  

          //测试一下配件是否好用  
          this.cpu.calculate();  
          this.mainboard.installCPU();  
      }  
}  

```

通过上面的示例，能看到可扩展工厂的基本实现。从客户端的代码会发现，为什么说这种方式是不太安全的呢？

 **`你会发现创建产品对象返回来过后，需要造型成为具体的对象，因为返回的是Object，如果这个时候没有匹配上，比如返回的不是CPU对象，但是要强制造型成为CPU，那么就会发生错误，因此这种实现方式的一个潜在缺点就是不太安全。`** 

* **`接下来，体会一下这种方式的灵活性：`** 


假如现在要加入一个新的产品——内存，当然可以提供一个新的装机方案来使用它，这样已有的代码就不需要变化了。

先看看内存的接口吧，示例代码如下：

```java
/** 
   * 内存的接口 
   */  
public interface MemoryApi {  
      /** 
       * 示意方法，内存具有缓存数据的能力 
       */  
      public void cacheData();  
} 

```

提供一个现代内存的基本实现，示例代码如下：

```java
/** 
   * 现代内存的类 
   */  
public class HyMemory implements MemoryApi{  
      public void cacheData() {  
          System.out.println("现在正在使用现代内存");  
      }  
}  

```

现在想要使用这个新加入的产品，以前实现的代码都不用变化，只需新添加一个方案，在这个方案里面使用新的产品，然后客户端使用这个新的方案即可，示例代码如下：

```java
/** 
   * 装机方案三：Intel 的CPU + 技嘉的主板 + 现代的内存 
   */  
public class Scheme3 implements AbstractFactory{  
      public Object createProduct(int type) {  
          Object retObj = null;  
          //type为1表示创建CPU，type为2表示创建主板，type为3表示创建内存  
          if(type==1){  
              retObj = new IntelCPU(1156);  
          }else if(type==2){  
              retObj = new GAMainboard(1156);  
          }  
          //创建新添加的产品  
          else if(type==3){  
              retObj = new HyMemory();  
          }  
          return retObj;  
      }  
}  

```

这个时候的装机工程师类，如果要创建带内存的机器，需要在装机工程师类里面添加对内存的使用，示例代码如下：

```java
public  class ComputerEngineer {  
      private CPUApi cpu= null;  
      private MainboardApi mainboard = null;  
      /** 
       * 定义组装机器需要的内存 
       */  
      private MemoryApi memory = null;  
      public void makeComputer(AbstractFactory schema){  
          prepareHardwares(schema);  
      }  
      private void prepareHardwares(AbstractFactory schema){  
          //使用抽象工厂来获取相应的接口对象  
          this.cpu = (CPUApi)schema.createProduct(1);  
          this.mainboard = (MainboardApi)schema.createProduct(2);  
          this.memory = (MemoryApi)schema.createProduct(3);  

          //测试一下配件是否好用  
          this.cpu.calculate();  
          this.mainboard.installCPU();  
          if(memory!=null){  
              this.memory.cacheData();  
          }  
      }  
}  

```
## 3.3 抽象工厂模式和DAO##

* **`首先来看看什么是DAO`** 


DAO：数据访问对象，是Data Access Object首字母的简写。

DAO是JEE（也称JavaEE，原J2EE）中的一个标准模式，通过它来解决访问数据对象所面临的一系列问题，比如：数据源不同、存储类型不同、访问方式不同、供应商不同、版本不同等等，这些不同会造成访问数据的实现上差别很大。

 **`数据源的不同`** ，比如存放于数据库的数据源，存放于LDAP（轻型目录访问协议）的数据源；又比如存放于本地的数据源和远程服务器上的数据源等等 **`存储类型的不同`** ，比如关系型数据库（RDBMS）、面向对象数据库（ODBMS）、纯文件、XML等等 **`访问方式的不同`** ，比如访问关系型数据库，可以用JDBC、EntityBean、JPA等来实现，当然也可以采用一些流行的框架，如Hibernate、IBatis等等 **`供应商的不同`** ，比如关系型数据库，流行如Oracel、DB2、SqlServer、MySql等等，它们的供应商是不同的 **`版本不同`** ，比如关系型数据库，不同的版本，实现的功能是有差异的，就算是对标准的SQL的支持，也是有差异的

但是对于需要进行数据访问的逻辑层而言，它可不想面对这么多不同，也不想处理这么多差异，它希望能以一个统一的方式来访问数据。此时系统结构如图所示：


![][4]


系统结构如图

 **`也就是说，DAO需要抽象和封装所有对数据的访问，DAO承担和数据仓库交互的职责，这也意味着，访问数据所面临的所有问题，都需要DAO在内部来自行解决。`** 

* **`DAO和抽象工厂的关系`** 


事实上， **`在实现DAO模式的时候，最常见的实现策略就是使用工厂的策略，而且多是通过抽象工厂模式来实现，当然在使用抽象工厂模式来实现的时候，可以结合工厂方法模式`** 。因此DAO模式和抽象工厂模式有很大的联系。

* **`DAO模式的工厂实现策略`** 

 **`（1）采用工厂方法模式`** 

假如现在在一个订单处理的模块里面，大家都知道，订单通常又分成两个部分，一个部分是订单主记录或者是订单主表，另一个部分是订单明细记录或者是订单子表，那么现在业务对象需要操作订单的主记录，也需要操作订单的子记录。

如果这个时候的业务比较简单，而且对数据的操作是固定的，比如就是操作数据库，不管订单的业务如何变化，底层数据存储都是一样的，那么这种情况下，可以采用工厂方法模式，此时系统结构如图所示：


![][5]


系统结构如图


从上面的结构示意图可以看出，如果底层存储固定的时候，DAOFactory就相当于工厂方法模式中的Creator，在里面定义两个工厂方法，分别创建订单主记录的DAO对象和创建订单子记录的DAO对象，因为固定是数据库实现，因此提供一个具体的工厂RdbDAOFactory（Rdb：关系型数据库），来实现对象的创建。也就是说DAO可以采用工厂方法模式来实现。

采用工厂方法模式的情况，要求DAO底层存储实现方式是固定的，这种多用在一些简单的小项目开发上。 **`（2）采用抽象工厂模式`** 

实际上更多的时候，DAO底层存储实现方式是不固定的，DAO通常会支持多种存储实现方式，具体使用哪一种存储方式可能是由应用动态决定，或者是通过配置来指定。这种情况多见于产品开发、或者是稍复杂的应用、或者是较大的项目中。

对于底层存储方式不固定的时候，一般是采用抽象工厂模式来实现DAO。比如现在的实现除了RDB的实现，还会有Xml的实现，它们会被应用动态的选择，此时系统结构如图所示：


![][6]


系统结构如图


从上面的结构示意图可以看出，采用抽象工厂模式来实现DAO的时候，DAOFactory就相当于抽象工厂，里面定义一系列创建相关对象的方法，分别是创建订单主记录的DAO对象和创建订单子记录的DAO对象，此时OrderMainDAO和OrderDetailDAO就相当于被创建的产品，RdbDAOFactory和XmlDAOFactory就相当于抽象工厂的具体实现，在它们里面会选择相应的具体的产品实现来创建对象。

* **`代码示例使用抽象工厂实现DAO模式`** 

 **`（1）先看看抽象工厂的代码实现，示例代码如下：`** 

```java
/** 
   * 抽象工厂，创建订单主、子记录对应的DAO对象 
   */  
public abstract class DAOFactory {  
      /** 
       * 创建订单主记录对应的DAO对象 
       * @return 订单主记录对应的DAO对象 
       */  
      public abstract OrderMainDAO createOrderMainDAO();  
      /** 
       * 创建订单子记录对应的DAO对象 
       * @return 订单子记录对应的DAO对象 
       */  
      public abstract OrderDetailDAO createOrderDetailDAO();  
}  

``` **`（2）看看产品对象的接口，就是订单主、子记录的DAO定义，先看订单主记录的DAO定义，示例代码如下：`** 

```java
/** 
   * 订单主记录对应的DAO操作接口 
   */  
public interface OrderMainDAO {  
      /** 
       * 示意方法，保存订单主记录 
       */  
      public void saveOrderMain();  
}

```

再看看订单子记录的DAO定义，示例代码如下：

```java
/** 
   * 订单子记录对应的DAO操作接口 
   */  
public interface OrderDetailDAO {  
      /** 
       * 示意方法，保存订单子记录 
       */  
      public void saveOrderDetail();  
}

``` **`（3）接下来实现订单主、子记录的DAO，先看关系型数据库的实现方式，示例代码如下：`** 

```java
public class RdbMainDAOImpl implements OrderMainDAO{  
      public void saveOrderMain() {  
          System.out.println("now in RdbMainDAOImpl saveOrderMain");  
      }  
}  

public class RdbDetailDAOImpl implements OrderDetailDAO{  
      public void saveOrderDetail() {  
          System.out.println("now in RdbDetailDAOImpl saveOrderDetail");  
      }  
}  

```

Xml实现的方式一样，为了演示简单，都是输出了一句话，示例代码如下：

```java
public class XmlMainDAOImpl implements OrderMainDAO{  
      public void saveOrderMain() {  
          System.out.println("now in XmlMainDAOImpl saveOrderMain");  
      }  
}  

``` **`（4）再看看具体的工厂实现，先看关系型数据库实现方式的工厂，示例代码如下：`** 

```java
public class RdbDAOFactory extends DAOFactory{  
      public OrderDetailDAO createOrderDetailDAO() {  
          return new RdbDetailDAOImpl();  
      }  
      public OrderMainDAO createOrderMainDAO() {  
          return new RdbMainDAOImpl();  
      }  
}  

```

Xml实现方式的工厂，示例代码如下：

```java
public class XmlDAOFactory extends DAOFactory {  
      public OrderDetailDAO createOrderDetailDAO() {  
          return new XmlDetailDAOImpl();  
      }  
      public OrderMainDAO createOrderMainDAO() {  
          return new XmlMainDAOImpl();  
      }  
}  

``` **`（5）好了，使用抽象工厂来简单的实现了DAO模式，那么在客户端，通常是由业务对象来调用DAO，那么该怎么使用这个DAO呢？示例代码如下：`** 

```java
public class BusinessObject {  
      public static void main(String[] args) {  
          //创建DAO的抽象工厂  
          DAOFactory df = new RdbDAOFactory();  
          //通过抽象工厂来获取需要的DAO接口  
          OrderMainDAO mainDAO = df.createOrderMainDAO();  
          OrderDetailDAO detailDAO = df.createOrderDetailDAO();  
          //调用DAO来完成数据存储的功能  
          mainDAO.saveOrderMain();  
          detailDAO.saveOrderDetail();  
      }  
}

```

通过上面的示例，可以看出DAO可以采用抽象工厂模式来实现，这也是大部分DAO实现采用的方式。
## 3.4 模式的优缺点##

* **`分离接口和实现`** 


客户端使用抽象工厂来创建需要的对象，而客户端根本就不知道具体的实现是谁，客户端只是面向产品的接口编程而已，也就是说，客户端从具体的产品实现中解耦。

* **`使得切换产品簇变得容易`** 


因为一个具体的工厂实现代表的是一个产品簇，比如上面例子的Scheme1代表装机方案一：Intel 的CPU + 技嘉的主板，如果要切换成为Scheme2，那就变成了装机方案二：AMD的CPU + 微星的主板。

客户端选用不同的工厂实现，就相当于是在切换不同的产品簇。

* **`不太容易扩展新的产品`** 


前面也提到这个问题了， **`如果需要给整个产品簇添加一个新的产品，那么就需要修改抽象工厂，这样就会导致修改所有的工厂实现类。在前面提供了一个可以扩展工厂的方式来解决这个问题，但是又不够安全`** 。如何选择，根据实际应用来权衡吧。

* **`容易造成类层次复杂`** 


在使用抽象工厂模式的时候，如果需要选择的层次过多，那么会造成整个类层次变得复杂。

举个例子来说，就比如前面讲到的那个DAO的示例，现在这个DAO只有一个选择的层次，也就是选择一下是使用关系型数据库来实现，还是用Xml来实现。现在考虑这样一种情况，如果关系型数据库实现里面又分成几种，比如：基于Oracle的实现，基于SqlServer的实现，基于MySql的实现等等。

那么客户端怎么选呢？不会把所有可能的实现情况全部都做到一个层次上吧，这个时候客户端就需要一层一层选择，也就是 **`整个抽象工厂的实现也需要分出层次来，每一层负责一种选择，也就是一层屏蔽一种变化，这样很容易造成复杂的类层次结构`** 。
## 3.5 思考抽象工厂模式##

* **`抽象工厂模式的本质`** 

 **`抽象工厂模式的本质：选择产品簇的实现。`** 

工厂方法是选择单个产品的实现，虽然一个类里面可以有多个工厂方法， **`但是这些方法之间一般是没有联系的，即使看起来像有联系`** 。

但是抽象工厂着重的就是为一个产品簇选择实现， **`定义在抽象工厂里面的方法通常是有联系的，它们都是产品的某一部分或者是相互依赖的`** 。如果抽象工厂里面只定义一个方法，直接创建产品，那么就退化成为工厂方法了。

* **`何时选用抽象工厂模式`** 


建议在如下情况中，选用抽象工厂模式：

 **`如果希望一个系统独立于它的产品的创建，组合和表示的时候`** ，换句话说，希望一个系统只是知道产品的接口，而不关心实现的时候。 **`如果一个系统要由多个产品系列中的一个来配置的时候`** ，换句话说，就是可以动态的切换产品簇的时候。 **`如果要强调一系列相关产品的接口，以便联合使用它们的时候`** 。

## 3.6  相关模式##

* **`抽象工厂模式和工厂方法模式`** 


这两个模式既有区别，又有联系，可以组合使用。

工厂方法模式一般是针对单独的产品对象的创建，而抽象工厂模式注重产品簇对象的创建，这是它们的区别。

如果把抽象工厂创建的产品簇简化，这个产品簇就只有一个产品，那么这个时候的抽象工厂跟工厂方法是差不多的，也就是 **`抽象工厂可以退化成工厂方法，而工厂方法又可以退化成简单工厂，这是它们的联系`** 。

在抽象工厂的实现中，还可以使用工厂方法来提供抽象工厂的具体实现，也就是说它们可以组合使用。

* **`抽象工厂模式和单例模式`** 


这两个模式可以组合使用。

在抽象工厂模式里面，具体的工厂实现，在整个应用中，通常一个产品系列只需要一个实例就可以了，因此可以把具体的工厂实现成为单例。


[0]: ./img/2062729-e67f3bc02dd54291.png
[1]: ./img/2062729-e645ed69d1174705.png
[2]: ./img/2062729-5309f0a48e2dbc3f.png
[3]: ./img/2062729-d379776003cce319.png
[4]: ./img/2062729-be0728ea29afd71d.png
[5]: ./img/2062729-f4f3d21bb26d601e.png
[6]: ./img/2062729-5b3487f2d76ea412.png