## 【结构型模式八】适配器(Adapter)

2016.07.21 11:21*

来源：[https://www.jianshu.com/p/6f93a4e0ae27](https://www.jianshu.com/p/6f93a4e0ae27)


          
## 1 场景问题#
## 1.1 装配电脑的例子##

* **`旧的硬盘和电源`** 


小李有一台老的台式电脑，硬盘实在是太小了，仅仅40GB，但是除了这个问题外，整机性能还不错，废弃不用太可惜了，于是决定去加装一块新的硬盘。

在装机公司为小李的电脑加装新硬盘的时候，小李也在边上观看，顺便了解点硬件知识。很快的，装机人员把两块硬盘都安装好了，细心的小李发现，这两块硬盘的连接方式是不一样的。

经过装机人员的耐心讲解，小李搞清楚了它们的不同。 **`以前的硬盘是串口的`** ，如图4.1，电脑电源如图4.2，那么连接电源的时候是直接连接。


![][0]


旧的硬盘和电脑电源


* **`加入新的硬盘`** 

 **`但是现在的新硬盘是并口的`** ，如图4.3，电源的输出口无法直接连接到新的硬盘上了， **`于是就有了转接线，一边和电源的输出口连接，一边和新的硬盘电源输入口连接，解决了电源输出接口和硬盘输入接口不匹配的问题`** ，如图4.4：


![][1]


新的硬盘是并口的


* **`有何问题`** 


如果把上面的问题抽象一下，用对象来描述，那就是：有一个电源类和旧的硬盘类配合工作得很好，现在又有了一个新的硬盘类，现在想让新的硬盘类和电源类也配合使用，但是发现它们的接口无法匹配，问题就产生了： **`如何让原有的电源类的接口能够适应新的硬盘类的电源接口的需要呢？`** 

* **`如何解决`** 

 **`解决方法是采用一个转接线类，转接线可以把电源的接口适配成为新的硬盘所需要的接口`** ，那么这个转接线类就类似本章的主角——适配器。
## 1.2 同时支持数据库和文件的日志管理##

看了上面这个例子，估计对适配器模式有一点感觉了。这是个在生活中常见的例子，类似的例子很多，比如：各种管道的转接头、不同制式的插座等等。但是这种例子只能帮助大家理解适配器模式的功能，跟实际的应用系统开发总是有那么些差距，会感觉到好像是理解了模式的功能，但是一到真实的系统开发中，就不知道如何使用这个模式了，有些隔靴搔痒的感觉。因此，下面还是以实际系统中的例子来讲述，以帮助大家真正理解和应用适配器模式。

考虑一个记录日志的应用，由于用户对日志记录的要求很高，使得开发人员不能简单的采用一些已有的日志工具或日志框架来满足用户的要求，而需要按照用户的要求重新开发新的日志管理系统。当然这里不可能完全按照实际系统那样去完整实现，只是抽取跟适配器模式相关的部分来讲述。

* **`日志管理第一版`** 


在第一版的时候，用户要求日志以文件的形式记录。开发人员遵照用户的要求，对日志文件的存取实现如下。

先简单定义日志对象，也就是描述日志的对象模型，由于这个对象需要被写入文件中，因此这个对象需要序列化，示例代码如下：

```java
/**
   * 日志数据对象
   */
public class LogModel implements Serializable  {
    /**
     * 日志编号
     */
    private String logId;
    /**
     * 操作人员
     */
    private String operateUser;
    /**
     * 操作时间，以yyyy-MM-dd HH:mm:ss的格式记录
     */
    private String operateTime;
    /**
     * 日志内容
     */
    private String logContent;

    public String getLogId() {
        return logId;
    }
    public void setLogId(String logId) {
        this.logId = logId;
    }
    public String getOperateUser() {
        return operateUser;
    }
    public void setOperateUser(String operateUser) {
        this.operateUser = operateUser;
    }
    public String getOperateTime() {
        return operateTime;
    }
    public void setOperateTime(String operateTime) {
        this.operateTime = operateTime;
    }
    public String getLogContent() {
        return logContent;
    }
    public void setLogContent(String logContent) {
        this.logContent = logContent;
    }
    public String toString() {
        return "logId="+logId+",operateUser="+operateUser+",operateTime="+operateTime+",logContent="+logContent;
    }
}

```

接下来定义一个操作日志文件的接口，示例代码如下：

```java
/**
   * 日志文件操作接口
   */
public interface LogFileOperateApi {
    /**
     * 读取日志文件，从文件里面获取存储的日志列表对象
     * @return 存储的日志列表对象
     */
    public List<LogModel> readLogFile();
    /**
     * 写日志文件，把日志列表写出到日志文件中去
     * @param list 要写到日志文件的日志列表
     */
    public void writeLogFile(List<LogModel> list);
}

```

实现日志文件的存取，现在的实现也很简单，就是读写文件，示例代码如下：

```java
/**
   * 实现对日志文件的操作
   */
public class LogFileOperate implements LogFileOperateApi{
    /**
     * 日志文件的路径和文件名称，默认是当前项目的根下的AdapterLog.log
     */
    private String logFilePathName = "AdapterLog.log";
    /**
     * 构造方法，传入文件的路径和名称
     * @param logFilePathName 文件的路径和名称
     */
    public LogFileOperate(String logFilePathName) {
        //先判断是否传入了文件的路径和名称，如果是，
        //就重新设置操作的日志文件的路径和名称
        if(logFilePathName!=null && logFilePathName.trim().length()>0){
            this.logFilePathName = logFilePathName;
        }
    }
    public  List<LogModel> readLogFile() {
        List<LogModel> list = null;
        ObjectInputStream oin = null;
        try {
            File f = new File(logFilePathName);
            if(f.exists()) {
                oin = new ObjectInputStream(new BufferedInputStream(new FileInputStream(f)));
                list = (List<LogModel>)oin.readObject();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if(oin!=null) {
                    oin.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return list;
    }
    public void writeLogFile(List<LogModel> list){
        File f = new File(logFilePathName);
        ObjectOutputStream oout = null;
        try {
            oout = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(f)));
            oout.writeObject(list);        
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                oout.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

```

写个客户端来测试一下，看看好用不，示例代码如下：

```java
public class Client {
    public static void main(String[] args) {
        //准备日志内容，也就是测试的数据
        LogModel lm1 = new LogModel();
        lm1.setLogId("001");
        lm1.setOperateUser("admin");
        lm1.setOperateTime("2010-03-0210:08:18");
        lm1.setLogContent("这是一个测试");
    
        List<LogModel> list = new ArrayList<LogModel>();
        list.add(lm1);
        //创建操作日志文件的对象
        LogFileOperateApi api = new LogFileOperate("");
        //保存日志文件
        api.writeLogFile(list);
    
        //读取日志文件的内容
        List<LogModel> readLog = api.readLogFile();
        System.out.println("readLog="+readLog);
    }
}

```

至此就简单的实现了用户的要求，把日志保存到文件中，并能从文件中把日志内容读取出来，进行管理。看上去很容易，对吧，别慌，接着来。

* **`日志管理第二版`** 


用户使用日志管理的第一版一段时间过后，开始考虑升级系统， **`决定要采用数据库来管理日志，很快，按照数据库的日志管理也实现出来了`** ，并定义了日志管理的操作接口，主要是针对日志的增删改查方法，接口的示例代码如下：

```java
/**
   * 定义操作日志的应用接口，为了示例的简单，只是简单的定义了增删改查的方法
   */
public interface LogDbOperateApi {
    /**
     * 新增日志
     * @param lm 需要新增的日志对象
     */
    public void createLog(LogModel lm);
    /**
     * 修改日志
     * @param lm 需要修改的日志对象
     */
    public void updateLog(LogModel lm);
    /**
     * 删除日志
     * @param lm 需要删除的日志对象
     */
    public void removeLog(LogModel lm);
    /**
     * 获取所有的日志
     * @return 所有的日志对象
     */
    public List<LogModel> getAllLog();
}

```

对于使用数据库来保存日志的实现，这里就不去涉及了，反正知道有这么一个实现就可以了。

客户提出了新的要求，能不能让日志管理的第二版，实现同时支持数据库存储和文件存储两种方式？
## 1.3 有何问题##

有朋友可能会想，这有什么困难的呢，两种实现方式不是都已经实现了的吗，合并起来不就可以了？

问题就在于，现在的业务是使用的第二版的接口，直接使用第二版新加入的实现是没有问题的，第二版新加入了保存日志到数据库中； **`但是对于已有的实现方式，也就是在第一版中采用的文件存储的方式，它的操作接口和第二版不一样，这就导致现在的客户端，无法以同样的方式来直接使用第一版的实现`** ，如下图4.5所示：


![][2]


无法兼容第一版的接口示意图


这就意味着，要想同时支持文件和数据库存储两种方式，需要再额外的做一些工作，才可以让第一版的实现适应新的业务的需要。

可能有朋友会想，干脆按照第二版的接口要求重新实现一个文件操作的对象不就可以了，这样确实可以，但是何必要重新做已经完成的功能呢？ **`应该要想办法复用，而不是重新实现`** 。

一种很容易想到的方式是直接修改已有的第一版的代码。这种方式是不太好的，如果直接修改了第一版的代码，那么可能会导致其它依赖于这些实现的应用不能正常运行，再说，有可能第一版和第二版的开发公司是不一样的，在第二版实现的时候，根本拿不到第一版的源代码。

那么该如何来实现呢？
## 2 解决方案#
## 2.1 适配器模式来解决##

用来解决上述问题的一个合理的解决方案就是适配器模式。那么什么是适配器模式呢？

* **`适配器模式定义`** 



![][3]


适配器模式定义


* **`应用适配器模式来解决的思路`** 


仔细分析上面的问题， **`问题的根源在于接口的不兼容`** ，功能是基本实现了的，也就是说，只要想办法让两边的接口匹配起来，就可以复用第一版的功能了。

按照适配器模式的实现方式， **`可以定义一个类来实现第二版的接口，然后在内部实现的时候，转调第一版已经实现了的功能`** ，这样就可以通过对象组合的方式，既复用了第一版已有的功能，同时又在接口上满足了第二版调用的要求。完成上述工作的这个类就是适配器。

## 2.2 模式结构和说明##

适配器模式的结构如图所示：


![][4]


适配器模式的结构图


 **`Client：客户端`** ，调用自己需要的领域接口Target。 **`Target：定义客户端需要的跟特定领域相关的接口。`**  **`Adaptee：已经存在的接口`** ，通常能满足客户端的功能要求， **`但是接口与客户端要求的特定领域接口不一致，需要被适配`** 。 **`Adapter：适配器，把Adaptee适配成为Client需要的Target。`** 

## 2.3 适配器模式示例代码##

* **`先看看Target接口的定义，示例代码如下：`** 


```java
/**
   * 定义客户端使用的接口，与特定领域相关
   */
public interface Target {
    /**
     * 示意方法，客户端请求处理的方法
     */
    public void request();
}

```

* **`再看看需要被适配的对象定义，示例代码如下：`** 


```java
/**
   * 已经存在的接口，这个接口需要被适配
   */
public class Adaptee {
    /**
     * 示意方法，原本已经存在，已经实现的方法
     */
    public void specificRequest() {
        //具体的功能处理
    }
}

```

* **`再看看适配器对象的基本实现，示例代码如下：`** 


```java
/**
   * 适配器
   */
public class Adapter implements Target {
    /**
     * 持有需要被适配的接口对象
     */
    private Adaptee adaptee;
    /**
     * 构造方法，传入需要被适配的对象
     * @param adaptee 需要被适配的对象
     */
    public Adapter(Adaptee adaptee) {
        this.adaptee = adaptee;
    }
    public void request() {
        //可能转调已经实现了的方法，进行适配
        adaptee.specificRequest();
    }
}

```

* **`再来看看使用适配器的客户端，示例代码如下：`** 


```java
/**
   * 使用适配器的客户端
   */
public class Client {  
    public static void main(String[] args) {
        // 创建需被适配的对象
        Adaptee adaptee = new Adaptee();
        // 创建客户端需要调用的接口对象
        Target target = new Adapter(adaptee);
        // 请求处理
        target.request();
    }
}

```
## 2.4 使用适配器模式来实现示例##

要使用适配器模式来实现示例， **`关键就是要实现这个适配器对象，它需要实现第二版的接口，但是在内部实现的时候，需要调用第一版已经实现的功能`** 。也就是说， **`第二版的接口就相当于适配器模式中的Target接口，而第一版已有的实现就相当于适配器模式中的Adaptee对象`** 。

* **`把这个适配器简单的实现出来，示意一下，示例代码如下：`** 


```java
/**
   * 适配器对象，把记录日志到文件的功能适配成第二版需要的增删改查的功能
   */
public class Adapter implements LogDbOperateApi{
    /**
     * 持有需要被适配的接口对象
     */
    private LogFileOperateApi adaptee;
    /**
     * 构造方法，传入需要被适配的对象
     * @param adaptee 需要被适配的对象
     */
    public Adapter(LogFileOperateApi adaptee) {
        this.adaptee = adaptee;
    }

    public void createLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = adaptee.readLogFile();
        //2：加入新的日志对象
        list.add(lm);
        //3：重新写入文件
        adaptee.writeLogFile(list);
    }
    public List<LogModel> getAllLog() {
        return adaptee.readLogFile();
    }
    public void removeLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = adaptee.readLogFile();
        //2：删除相应的日志对象
        list.remove(lm);
        //3：重新写入文件
        adaptee.writeLogFile(list);
    }
    public void updateLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = adaptee.readLogFile();
        //2：修改相应的日志对象
        for(int i=0;i<list.size();i++){
            if(list.get(i).getLogId().equals(lm.getLogId())){
                list.set(i, lm);
                break;
            }
        }
        //3：重新写入文件
        adaptee.writeLogFile(list);
    }
}

```

* **`此时的客户端也需要一些改变，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //准备日志内容，也就是测试的数据
        LogModel lm1 = new LogModel();
        lm1.setLogId("001");
        lm1.setOperateUser("admin");
        lm1.setOperateTime("2010-03-0210:08:18");
        lm1.setLogContent("这是一个测试");
        List<LogModel> list = new ArrayList<LogModel>();
        list.add(lm1);
        //创建操作日志文件的对象
        LogFileOperateApi logFileApi = new LogFileOperate("");
    
        //创建新版的操作日志的接口对象
        LogDbOperateApi api = new Adapter(logFileApi);
    
        //保存日志文件
        api.createLog(lm1);    
        //读取日志文件的内容
        List<LogModel> allLog = api.getAllLog();
        System.out.println("allLog="+allLog);
    }
}

```

* **`小结一下思路`** 


① 原有文件存取日志的方式，运行得很好，如图所示：


![][5]


原有文件存取日志的方式


② 现在有了新的基于数据库的实现，新的实现有自己的接口，如图所示：


![][6]


新的基于数据库的实现


③ 现在想要在第二版的实现里面，能够同时兼容第一版的功能，那么就应有一个类来实现第二版的接口，然后在这个类里面去调用已有的功能实现，这个类就是适配器，如下图所示：


![][7]


加入适配器的实现结构示意图


上面是分步的思路，现在来看一下前面示例的整体结构，如图所示：


![][8]


适配器实现的示例的结构示意图


如同上面的例子，原本新的日志操作接口不能和旧的文件实现一起工作，但是经过适配器适配后，新的日志操作接口就能和旧的文件实现日志存储一起工作了。
## 3 模式讲解#
## 3.1 认识适配器模式##

* **`模式的功能`** 

 **`适配器模式的主要功能是进行转换匹配，目的是复用已有的功能，而不是来实现新的接口`** 。也就是说，客户端需要的功能应该是已经实现好了的，不需要适配器模式来实现， **`适配器模式主要负责把不兼容的接口转换成客户端期望的样子就好了`** 。

但这并不是说，在适配器里面就不能实现功能，适配器里面可以实现功能， **`称这种适配器为智能适配器`** 。再说了，在接口匹配和转换的过程中，也是有可能需要额外实现一定的功能，才能够转换过来的，比如需要调整参数以进行匹配等。

* **`Adaptee和Target的关系`** 

 **`适配器模式中被适配的接口Adaptee和适配成为的接口Target是没有关联的`** ，也就是说，Adaptee和Target中的方法既可以相同，也可以不同，极端情况下两个接口里面的方法可能是完全不同的，当然极端情况下也可以完全相同。

这里所说的相同和不同，是指的方法定义的名称、参数列表、返回值、包括方法本身的功能都可以相同和不同。

* **`对象组合`** 


根据前面的实现，你会发现， **`适配器的实现方式其实是依靠对象组合的方式`** 。通过给适配器对象组合被适配的对象，然后当客户端调用Target的时候，适配器会把相应的功能，委托给被适配的对象去完成。
## 3.2 适配器模式的实现##

* **`适配器的常见实现`** 


在实现适配器的时候，适配器通常是一个类，一般会让适配器类去实现Target接口，然后在适配器的具体实现里面调用Adaptee。 **`也就是说适配器通常是一个Target类型，而不是Adaptee类型`** 。如同前面的例子演示的那样。

* **`智能适配器`** 


在实际开发中，适配器也可以实现一些Adaptee没有实现，但是在Target中定义的功能，这种情况就需要在适配器的实现里面，加入新功能的实现，这种适配器被称为智能适配器。

如果要使用智能适配器，一般新加入的功能的实现，会用到很多Adaptee的功能，相当于利用Adaptee的功能来实现更高层的功能。当然也可以完全实现新加的功能，跟已有的功能都不靠边，变相是扩展了功能。

* **`适配多个Adaptee`** 

 **`适配器在适配的时候，可以适配多个Adaptee`** ，也就是说实现某个新的Target的功能的时候， **`需要调用到多个模块的功能，适配多个模块的功能才能满足新接口的要求`** 。

* **`适配器Adapter实现的复杂程度`** 

 **`适配器Adapter实现的复杂程度，取决于Target和Adaptee的相似程度。`** 

如果相似程度很高，比如只有方法名称不一样，那么Adapter只是需要简单的转调一下接口就好了。

如果相似程度低，比如两边接口的方法定义的功能完全不一样，在Target中定义的一个方法，可能在Adaptee中定义了三个更小的方法，那么这个时候在实现Adapter的时候，就需要组合调用了。

* **`缺省适配`** 

 **`缺省适配的意思是：为一个接口提供缺省实现。`** 有了它，就不用直接去实现接口，而是 **`采用继承这个缺省适配对象，从而让子类可以有选择的去覆盖实现需要的方法`** ，对于不需要的方法，就使用缺省适配的方法就可以了。
## 3.3 双向适配器##

适配器也可以实现双向的适配， **`前面我们讲的都是把Adaptee适配成为Target，其实也可以把Target适配成为Adaptee，也就是说这个适配器可以同时当作Target和Adaptee来使用`** 。

继续前面讲述的例子，如果说由于某些原因，第一版和第二版会同时共存一段时间，比如第二版的应用还在不断调整中，也就是第二版还不够稳定。客户提出，希望在两版共存期间，主要还是在使用第一版，同时希望第一版的日志也能记入到数据库中，也就是客户虽然操作的接口是第一版的日志接口，界面也是第一版的界面，但是可以使用第二版的把日志记录到数据库的功能。

也就是说希望两版能实现双向的适配，结构如下图所示：


![][9]


双向适配结构图


这里只加了几个新的东西，一个就是DB存储日志的实现，前面的例子是没有的，因为直接被适配成使用文件存储日志的实现了；另外一个就是双向适配器，其实与把文件存储的方式适配成为DB实现的接口是一样的，只需要新加上把DB实现的功能适配成为文件实现的接口就好了。

* **`先看看DB存储日志的实现，为了简单，这里就不去真的实现和数据库交互了，示意一下，示例代码如下：`** 


```java
/**
   * DB存储日志的实现，为了简单，这里就不去真的实现和数据库交互了，示意一下
   */
public class LogDbOperate implements LogDbOperateApi{
    public void createLog(LogModel lm) {
        System.out.println("now in LogDbOperate createLog,lm="+lm);
    }
    public List<LogModel> getAllLog() {
        System.out.println("now in LogDbOperate getAllLog");
        return null;
    }
    public void removeLog(LogModel lm) {
        System.out.println("now in LogDbOperate removeLog,lm="+lm);
    }
    public void updateLog(LogModel lm) {
        System.out.println("now in LogDbOperate updateLog,lm="+lm);
    }
}

```

* 然后看看新的适配器的实现，由于是双向的适配器， **`一个方向是：把新的DB实现的接口适配成为旧的文件操作需要的接口；另外一个方向是把旧的文件操作的接口适配成为新的DB实现需要的接口`** 。示例代码如下：


```java
/**
   * 双向适配器对象
   */
public class TwoDirectAdapter implements LogDbOperateApi,LogFileOperateApi{
    /**
     * 持有需要被适配的文件存储日志的接口对象
     */
    private LogFileOperateApi fileLog;
    /**
     * 持有需要被适配的DB存储日志的接口对象
     */
    private LogDbOperateApi  dbLog;
    /**
     * 构造方法，传入需要被适配的对象
     * @param fileLog 需要被适配的文件存储日志的接口对象
     * @param dbLog 需要被适配的DB存储日志的接口对象
     */
    public TwoDirectAdapter(LogFileOperateApi fileLog, LogDbOperateApi dbLog) {
        this.fileLog = fileLog;
        this.dbLog = dbLog;
    }
    /*-----以下是把文件操作的方式适配成为DB实现方式的接口-----*/
    public void createLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = fileLog.readLogFile();
        //2：加入新的日志对象
        list.add(lm);
        //3：重新写入文件
        fileLog.writeLogFile(list);
    }
    public List<LogModel> getAllLog() {
        return fileLog.readLogFile();
    }
    public void removeLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = fileLog.readLogFile();
        //2：删除相应的日志对象
        list.remove(lm);
        //3：重新写入文件
        fileLog.writeLogFile(list);
    }
    public void updateLog(LogModel lm) {
        //1：先读取文件的内容
        List<LogModel> list = fileLog.readLogFile();
        //2：修改相应的日志对象
        for(int i=0;i<list.size();i++){
            if(list.get(i).getLogId().equals(lm.getLogId())){
                list.set(i, lm);
                break;
            }
        }
        //3：重新写入文件
        fileLog.writeLogFile(list);
    }
    /*-----以下是把DB操作的方式适配成为文件实现方式的接口-----*/
    public List<LogModel> readLogFile() {
        return dbLog.getAllLog();
    }
    public void writeLogFile(List<LogModel> list) {
        //1：最简单的实现思路，先删除数据库中的数据
        //2：然后循环把现在的数据加入到数据库中
        for(LogModel lm : list){
            dbLog.createLog(lm);
        }    
    }
}

```

* **`看看如何使用这个双向适配器，测试一下，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //准备日志内容，也就是测试的数据
        LogModel lm1 = new LogModel();
        lm1.setLogId("001");
        lm1.setOperateUser("admin");
        lm1.setOperateTime("2010-03-0210:08:18");
        lm1.setLogContent("这是一个测试");
        List<LogModel> list = new ArrayList<LogModel>();
        list.add(lm1);
        //创建操作日志文件的对象
        LogFileOperateApi fileLogApi = new LogFileOperate("");
        LogDbOperateApi dbLogApi = new LogDbOperate();
    
        //创建经过双向适配后的操作日志的接口对象
        LogFileOperateApi fileLogApi2 = new TwoDirectAdapter(fileLogApi,dbLogApi);
        LogDbOperateApi dbLogApi2 = new TwoDirectAdapter(fileLogApi,dbLogApi);
    
        //先测试从文件操作适配到第二版，
        //虽然调用的是第二版的接口，其实是文件操作在实现
        dbLogApi2.createLog(lm1);
        List<LogModel> allLog = dbLogApi2.getAllLog();
        System.out.println("allLog="+allLog);
    
        //再测试从数据库存储适配成第一版的接口，
        //也就是调用第一版的接口，其实是数据实现
        fileLogApi2.writeLogFile(list);
        fileLogApi2.readLogFile();
    }
}

```

事实上，使用适配器有一个潜在的问题，就是被适配的对象不再兼容Adaptee的接口， **`因为适配器只是实现了Target的接口，这导致并不是所有Adaptee对象可以被使用的地方都可以使用适配器`** 。

而双向适配器就解决了这样的问题， **`双向适配器同时实现了Target和Adaptee的接口，使得双向适配器可以在Target或Adaptee被使用的地方使用`** ，以提供对所有客户的透明性，尤其在两个不同的客户需要用不同的方式查看同一个对象时，适合使用双向适配器。
## 3.4 适配器模式的优缺点##

* **`更好的复用性`** 


如果功能是已经有了的，只是接口不兼容，那么通过适配器模式就可以让这些功能得到更好的复用。

* **`更好的可扩展性`** 


在实现适配器功能的时候，可以调用自己开发的功能，从而自然的扩展系统的功能。

* **`过多的使用适配器，会让系统非常零乱，不容易整体进行把握`** 


比如：明明看到调用的是A接口，其实内部被适配成了B接口来实现，一个系统如果太多这种情况，无异于一场灾难。因此如果不是很有必要，可以不使用适配器，而是直接对系统进行重构。
## 3.5 思考适配器模式##

* **`适配器模式的本质`** 

 **`适配器模式的本质：转换匹配，复用功能。`** 

适配器通过转换调用已有的实现，从而能把已有的实现匹配成需要的接口，使之能满足客户端的需要。 **`也就是说转换匹配是手段，而复用已有的功能才是目的。`** 

在进行转换匹配的过程中，适配器还可以在转换调用的前后实现一些功能处理，也就是实现智能的适配。

* **`何时选用适配器模式`** 


建议在如下情况中，选用适配器模式：

 **`如果你想要使用一个已经存在的类，但是它的接口不符合你的需求`** ，这种情况可以使用适配器模式，来把已有的实现转换成你需要的接口 **`如果你想创建一个可以复用的类，这个类可能和一些不兼容的类一起工作`** ，这种情况可以使用适配器模式，到时候需要什么就适配什么 **`如果你想使用一些已经存在的子类，但是不可能对每一个子类都进行适配`** ，这种情况可以选用对象适配器，直接适配这些子类的父类就可以了。

## 3.6 相关模式##

* **`适配器模式与桥接模式`** 


其实这两个模式除了结构略为相似外，功能上完全不同。 **`适配器模式是把两个或者多个接口的功能进行转换匹配；而桥接模式是让接口和实现部分相分离，以便它们可以相对独立的变化。`** 

* **`适配器模式与装饰模式`** 


从某种意义上讲， **`适配器模式能模拟实现简单的装饰模式的功能，也就是为已有功能增添功能`** 。比如我们在适配器里面这么写：

```java
public void adapterMethod(){
      System.out.println("在调用Adaptee的方法之前完成一定的工作");
      //调用Adaptee的相关方法
      adaptee.method();
      System.out.println("在调用Adaptee的方法之后完成一定的工作");
}

```

如上的写法，就相当于在调用Adaptee的被适配方法前后添加了新的功能，这样适配过后，客户端得到的功能就不单纯是Adaptee的被适配方法的功能了。看看是不是类似装饰模式的功能呢？

注意，仅仅是类似，造成这种类似的原因： **`两种设计模式在实现上都是使用的对象组合`** ，都可以在转调组合对象的功能前后进行一些附加的处理，因此有这么一个相似性。 **`它们的目的和本质都是不一样的`** 。

两个模式有一个很大的不同： **`一般适配器适配过后是需要改变接口的，如果不改接口就没有必要适配了；而装饰模式是不改接口的，无论多少层装饰都是一个接口`** 。因此装饰模式可以很容易的支持递归组合，而适配器就做不到了，每次的接口不同，没法递归。

* **`适配器模式和代理模式`** 


适配器模式可以跟代理模式组合使用， **`在实现适配器的时候，可以通过代理来调用Adaptee`** ，这可以获得更大的灵活性。

* **`适配器模式和抽象工厂模式`** 


在适配器实现的时候， **`通常需要得到被适配的对象，如果被适配的是一个接口，那么就可以结合一些可以创造对象实例的设计模式，来得到被适配的对象示例`** 。比如：抽象工厂模式、单例模式、工厂方法模式等等。


[0]: ./img/2062729-7bfd016fff1b2992.png
[1]: ./img/2062729-a4252b823880e40c.png
[2]: ./img/2062729-5b5284135ff513ca.png
[3]: ./img/2062729-4959a0bc4fe76ce7.png
[4]: ./img/2062729-d57a037f08d65119.png
[5]: ./img/2062729-b36a8f45cc67405c.png
[6]: ./img/2062729-766a8e9fbc074a24.png
[7]: ./img/2062729-2e1b7a02dccbc422.png
[8]: ./img/2062729-b81d9116ababbe8a.png
[9]: ./img/2062729-7b023850bbcefbde.png