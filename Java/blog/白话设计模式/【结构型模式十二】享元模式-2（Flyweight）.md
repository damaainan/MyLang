## 【结构型模式十二】享元模式-2（Flyweight）

2016.08.11 12:08*

来源：[https://www.jianshu.com/p/66c975d785da](https://www.jianshu.com/p/66c975d785da)


          
## 3.3 对享元对象的管理##

虽然享元模式对于共享的享元对象实例的管理要求，没有实例池对实例管理的要求那么高，但是也还是有很多自身的特点功能，比如：引用计数、垃圾清除等。 **`所谓垃圾，就是在缓存中存在，但是不再需要被使用的缓存中的对象`** 。

 **`所谓引用计数，就是享元工厂能够记录每个享元被使用的次数；而垃圾清除，则是大多数缓存管理都有的功能，缓存不能只往里面放数据，在不需要这些数据的时候，应该把这些数据从缓存中清除，释放相应的内存空间，以节省资源。`** 

在前面的示例中，共享的享元对象是很多人共享的，基本上可以一直存在于系统中，不用清除。但是垃圾清除是享元对象管理的一个很常见功能，还是通过示例给大家讲一下，看看如何实现这些常见的功能。

* **`实现引用计数的基本思路`** 


要实现引用计数，就在享元工厂里面定义一个Map，它的key值跟缓存享元对象的key是一样的，而value就是被引用的次数，这样当外部每次获取该享元的时候，就把对应的引用计数取出来加上1，然后再记录回去。

* **`实现垃圾回收的基本思路`** 


要实现垃圾回收就比较麻烦点，首先要能确定哪些是垃圾？其次是何时回收？还有由谁来回收？如何回收？解决了这些问题，也就能实现垃圾回收了。

为了确定哪些是垃圾， **`一个简单的方案是这样的，定义一个缓存对象的配置对象，在这个对象中描述了缓存的开始时间和最长不被使用的时间`** ，这个时候判断是垃圾的计算公式如下：当前的时间 - 缓存的开始时间 >= 最长不被使用的时间。当然，每次这个对象被使用的时候，就把那个缓存开始的时间更新为使用时的当前时间，也就是说如果一直有人用的话，这个对象是不会被判断为垃圾的。

何时回收的问题，当然是判断出来是垃圾了就可以回收了。

关键是谁来判断垃圾，还有谁来回收垃圾的问题。 **`一个简单的方案是定义一个内部的线程，这个线程在享元工厂被创建的时候就启动运行。`** 由这个线程每隔一定的时间来循环缓存中所有对象的缓存配置，看看是否是垃圾，如果是垃圾，那就可以启动回收了。

怎么回收呢？这个比较简单， **`就是直接从缓存的map对象中删除掉相应的对象，让这些对象没有引用的地方，那么这些对象就可以等着被虚拟机的垃圾回收来回收掉了`** 。

* **`代码示例`** 

 **`（1）分析了这么多，还是看代码示例会比较清楚，先看缓存配置对象，示例代码如下：`** 

```java
/**
   * 描述享元对象缓存的配置对象
   */
public class CacheConfModel{
      /**
       * 缓存开始计时的开始时间
       */
      private long beginTime;
      /**
       * 缓存对象存放的持续时间，其实是最长不被使用的时间
       */
      private double durableTime;
      /**
       * 缓存对象需要被永久存储，也就是不需要从缓存中删除
       */
      private boolean forever;
      public boolean isForever() {
         return forever;
      }
      public void setForever(boolean forever) {
         this.forever = forever;
      }
      public long getBeginTime() {
         return beginTime;
      }
      public void setBeginTime(long beginTime) {
         this.beginTime = beginTime;
      }
      public double getDurableTime() {
         return durableTime;
      }
      public void setDurableTime(double durableTime) {
         this.durableTime = durableTime;
      }
}

``` **`（2）对享元对象的管理的工作，是由享元工厂来完成的，因此上面的功能，也集中在享元工厂里面来实现，在上一个例子的基础之上，来实现这些功能，改进后的享元工厂相对而言稍复杂一点，大致有如下改变：`** 

添加一个Map，来缓存被共享对象的缓存配置的数据；

添加一个Map，来记录缓存对象被引用的次数；

为了测试方便，定义了一个常量来描述缓存的持续时间；

提供获取某个享元被使用的次数的方法；

在获取享元的对象里面，就要设置相应的引用计数和缓存设置了，示例采用的是内部默认设置一个缓存设置，其实也可以改造一下获取享元的方法，从外部传入缓存设置的数据；

提供一个清除缓存的线程，实现判断缓存数据是否已经是垃圾了，如果是，那就把它从缓存中清除掉；

基本上重新实现了享元工厂，示例代码如下：

```java
/**
   * 享元工厂，通常实现成为单例
   * 加入实现垃圾回收和引用计数的功能
   */
public class FlyweightFactory {
      private static FlyweightFactory factory = new FlyweightFactory();
      private FlyweightFactory(){
         //启动清除缓存值的线程
         Thread t = new ClearCache();
         t.start();
      }
      public static FlyweightFactory getInstance(){
         return factory;
      }

      /**
       * 缓存多个flyweight对象
       */
      private Map<String,Flyweight> fsMap = new HashMap<String,Flyweight>();
      /**
       * 用来缓存被共享对象的缓存配置，key值和上面map的一样
       */
      private Map<String,CacheConfModel> cacheConfMap = new HashMap<String,CacheConfModel>();
      /**
       * 用来记录缓存对象被引用的次数，key值和上面map的一样
       */
      private Map<String,Integer> countMap = new HashMap<String,Integer>();
      /**
       * 默认保存6秒钟，主要为了测试方便，这个时间可以根据应用的要求设置
       */
      private final long DURABLE_TIME = 6*1000L;
  
      /**
       * 获取某个享元被使用的次数
       * @param key 享元的key
       * @return 被使用的次数
       */
      public synchronized int getUseTimes(String key){
         Integer count = countMap.get(key);
         if(count==null){
             count = 0;
         }
         return count;
      }
      /**
       * 获取key对应的享元对象
       * @param key 获取享元对象的key
       * @return key对应的享元对象
       */
      public synchronized Flyweight getFlyweight(String key) {
         Flyweight f = fsMap.get(key);
         if(f==null){
             f = new AuthorizationFlyweight(key);
             fsMap.put(key,f);
             //同时设置引用计数
             countMap.put(key, 1);

             //同时设置缓存配置数据
             CacheConfModel cm = new CacheConfModel();
             cm.setBeginTime(System.currentTimeMillis());
             cm.setForever(false);
             cm.setDurableTime(DURABLE_TIME);
         
             cacheConfMap.put(key, cm);
         }else{
             //表示还在使用，那么应该重新设置缓存配置
             CacheConfModel cm = cacheConfMap.get(key);
             cm.setBeginTime(System.currentTimeMillis());
             //设置回去
             this.cacheConfMap.put(key, cm);
             //同时计数加1
             Integer count = countMap.get(key);
             count++;
             countMap.put(key, count);
         }
         return f;
      }
      /**
       * 删除key对应的享元对象，连带清除对应的缓存配置和引用次数的记录，不对外
       * @param key 要删除的享元对象的key
       */
      private synchronized void removeFlyweight(String key){
         this.fsMap.remove(key);
         this.cacheConfMap.remove(key);
         this.countMap.remove(key);
      }
      /**
       * 维护清除缓存的线程，内部使用
       */
      private  class ClearCache extends Thread{
         public void run(){
             while(true){
                Set<String> tempSet = new HashSet<String>();
                Set<String> set = cacheConfMap.keySet();
                for(String key : set){
                    CacheConfModel ccm = cacheConfMap.get(key);
                    //比较是否需要清除
                    if((System.currentTimeMillis() - ccm.getBeginTime()) >= ccm.getDurableTime()){
                       //可以清除，先记录下来
                       tempSet.add(key);
                    }
                }
                //真正清除
                for(String key : tempSet){
                    FlyweightFactory.getInstance().removeFlyweight(key);
                }
                System.out.println("now thread="+fsMap.size() +",fsMap=="+fsMap.keySet());
                //休息1秒再重新判断
                try {
                    Thread.sleep(1000L);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
             }
         }
      }
}

```

注意：getUseTimes、removeFlyweight和getFlyweight这几个方法是加了同步的， **`原因是在多线程环境下使用它们，容易出现并发错误`** ，比如一个线程在获取享元对象，而另一个线程在删除这个缓存对象。

 **`（3）要想看出引用计数的效果来，SecurityMgr需要进行一点修改，至少不要再缓存数据了，要直接从享元工厂中获取数据，否则就没有办法准确引用计数了，大致改变如下：`** 

去掉了放置登录人员对应权限数据的缓存；

不需要实现登录功能，在这个示意程序里面，登录方法已经不用实现任何功能，因此直接去掉；

原来通过map获取值的地方，直接通过queryByUser获取就好了；

示例代码如下：

```java
public class SecurityMgr {
      private static SecurityMgr securityMgr = new SecurityMgr();
      private SecurityMgr(){     
      }
      public static SecurityMgr getInstance(){
         return securityMgr;
      }
      /**
       * 判断某用户对某个安全实体是否拥有某权限
       * @param user 被检测权限的用户
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示拥有相应权限，false表示没有相应权限
       */
      public boolean hasPermit(String user,String securityEntity,String permit){
         Collection<Flyweight> col = this.queryByUser(user);
         if(col==null || col.size()==0){
             System.out.println(user+"没有登录或是没有被分配任何权限");
             return false;
         }
         for(Flyweight fm : col){
             if(fm.match(securityEntity, permit)){
                return true;
             }
         }
         return false;
      }
      /**
       * 从数据库中获取某人所拥有的权限
       * @param user 需要获取所拥有的权限的人员
       * @return 某人所拥有的权限
       */
      private Collection<Flyweight> queryByUser(String user){
         Collection<Flyweight> col = new ArrayList<Flyweight>();
     
         for(String s : TestDB.colDB){
             String ss[] = s.split(",");
             if(ss[0].equals(user)){
                Flyweight fm = null;
                if(ss[3].equals("2")){
                    //表示是组合
                    fm = new UnsharedConcreteFlyweight();
                    //获取需要组合的数据
                    String tempSs[] = TestDB.mapDB.get(ss[1]);
                    for(String tempS : tempSs){
                       Flyweight tempFm = FlyweightFactory.getInstance().getFlyweight(tempS);
                       //把这个对象加入到组合对象中
                       fm.add(tempFm);
                    }
                }else{
                    fm = FlyweightFactory.getInstance().getFlyweight(ss[1]+","+ss[2]);
                }            
                col.add(fm);
             }
         }
         return col;
      }  
}

``` **`（4）还是写个客户端来试试看，上面的享元工厂能否实现对享元对象的管理，尤其是对于垃圾回收和计数方面的功能，对于垃圾回收的功能不需要新加任何的测试代码，而对于引用计数的功能，需要写代码来调用才能看到效果，示例代码如下：`** 

```java
public class Client {
      public static void main(String[] args) throws Exception{
         SecurityMgr mgr = SecurityMgr.getInstance();
         boolean f1 = mgr.hasPermit("张三","薪资数据","查看");
         boolean f2 = mgr.hasPermit("李四","薪资数据","查看");
         boolean f3 = mgr.hasPermit("李四","薪资数据","修改");

         for(int i=0;i<3;i++){
             mgr.hasPermit("张三"+i,"薪资数据","查看");
         }  
     
         //特别提醒：这里查看的引用次数，不是指测试使用的次数，指的是
         //SecurityMgr的queryByUser方法通过享元工厂去获取享元对象的次数
         System.out.println("薪资数据,查看 被引用了"+FlyweightFactory.getInstance().getUseTimes("薪资数据,查看")+"次");
         System.out.println("薪资数据,修改 被引用了"+FlyweightFactory.getInstance().getUseTimes("薪资数据,修改")+"次");
         System.out.println("人员列表,查看 被引用了"+FlyweightFactory.getInstance().getUseTimes("人员列表,查看")+"次");
      }
}

```

进行缓存的垃圾回收功能的是个线程在运行，所以你不终止该线程运行，程序会一直运行下去，运行部分结果如下：

```java
薪资数据,查看 被引用了2次
薪资数据,修改 被引用了2次
人员列表,查看 被引用了6次
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=3,fsMap==[人员列表,查看, 薪资数据,查看, 薪资数据,修改]
now thread=0,fsMap==[]
now thread=0,fsMap==[]

```
## 3.4 享元模式的优缺点##

* **`减少对象数量，节省内存空间`** 


可能有的朋友认为共享对象会浪费空间， **`但是如果这些对象频繁使用，那么其实是节省空间的`** 。因为占用空间的大小等于每个对象实例占用的大小再乘以数量，对于享元对象来讲， **`基本上就只有一个实例，大大减少了享元对象的数量，并节省不少的内存空间`** 。

节省的空间取决于以下几个因素：因为共享而减少的实例数目、每个实例本身所占用的空间。假如每个对象实例占用2个字节，如果不共享数量是100个，而共享过后就只有一个了，那么节省的空间约等于：(100-1) X 2 字节。

* **`维护共享对象，需要额外开销`** 


如同前面演示的享元工厂， **`在维护共享对象的时候，如果功能复杂，会有很多额外的开销`** ，比如有一个线程来维护垃圾回收。
## 3.5 思考享元模式##

* **`享元模式的本质`** 


 **`享元模式的本质：分离与共享。`** 

 **`分离的是对象状态中变与不变的部分，共享的是对象中不变的部分。`** 享元模式的关键之处就在于分离变与不变，把不变的部分作为享元对象的内部状态，而变化部分就作为外部状态，由外部来维护，这样享元对象就能够被共享，从而减少对象数量，并节省大量的内存空间。

理解了这个本质后，在使用享元模式的时候，就会去考虑，哪些状态需要分离？如何分离？分离后如何处理？哪些需要共享？如何管理共享的对象？外部如何使用共享的享元对象？是否需要不共享的对象？等等问题。

把这些问题都思考清楚，找到相应的解决方法，那么享元模式也就应用起来了，可能是标准的应用，也可能是变形的应用，但万变不离其宗。

* **`何时选用享元模式`** 


建议在如下情况中，选用享元模式：

 **`如果一个应用程序使用了大量的细粒度对象`** ，可以使用享元模式来减少对象数量； **`如果由于使用大量的对象，造成很大的存储开销`** ，可以使用享元模式来减少对象数量，并节约内存； **`如果对象的大多数状态都可以转变为外部状态`** ，比如通过计算得到，或是从外部传入等，可以使用享元模式来实现内部状态和外部状态的分离； **`如果不考虑对象的外部状态，可以用相对较少的共享对象取代很多组合对象`** ，可以使用享元模式来共享对象，然后组合对象来使用这些共享对象；

## 3.6 相关模式##

* **`享元模式与单例模式`** 


这两个模式可以组合使用。

通常情况下， **`享元模式中的享元工厂可以实现成为单例`** 。另外， **`享元工厂里面缓存的享元对象，都是单实例的，可以看成是单例模式的一种变形控制`** ，在享元工厂里面来单例享元对象。

* **`享元模式与组合模式`** 


这两个模式可以组合使用。

在享元模式里面，存在不需要共享的享元实现，这些不需要共享的享元通常是对共享的享元对象的组合对象，也就是说， **`享元模式通常会和组合模式组合使用，来实现更复杂的对象层次结构。`** 

* **`享元模式与状态模式`** 


这两个模式可以组合使用。

可以使用享元模式来共享状态模式中的状态对象， **`通常在状态模式中，会存在数量很大的、细粒度的状态对象，而且它们基本上都是可以重复使用的，都是用来处理某一个固定的状态的`** ，它们需要的数据通常都是由上下文传入，也就是变化部分都分离出去了，所以可以用享元模式来实现这些状态对象。

* **`享元模式与策略模式`** 


这两个模式可以组合使用。

可以使用享元模式来实现策略模式中的策略对象，跟状态模式一样， **`在策略模式中也存在大量细粒度的策略对象`** ，它们需要的数据同样是从上下文传入的，所以可以使用享元模式来实现这些策略对象。

