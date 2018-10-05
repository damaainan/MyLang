## 【结构型模式十二】享元模式-1（Flyweight）

2016.08.11 10:49*

来源：[https://www.jianshu.com/p/3a9a6f15391b](https://www.jianshu.com/p/3a9a6f15391b)


          
## 1 场景问题#
## 1.1 加入权限控制##

考虑这样一个问题，给系统加入权限控制，这基本上是所有的应用系统都有的功能了。

对于应用系统而言，一般先要登录系统，才可以使用系统的功能，登录过后，用户的每次操作都需要经过权限系统的控制，确保该用户有操作该功能的权限，同时还要控制该用户对数据的访问权限、修改权限等等。总之一句话， **`一个安全的系统，需要对用户的每一次操作都要做权限检测，包括功能和数据，以确保只有获得相应授权的人，才能执行相应的功能，操作相应的数据`** 。

举个例子来说吧：普通人员都有能查看到本部门人员列表的权限，但是在人员列表中每个人员的薪资数据，普通人员是不可以看到的；而部门经理在查看本部门人员列表的时候，就可以看到每个人员相应的薪资数据。

现在就要来实现为系统加入权限控制的功能，该怎么实现呢？

为了让大家更好的理解后面讲述的知识，先介绍一点权限系统的基础知识。几乎所有的权限系统都分成两个部分， **`一个是授权部分，一个是验证部分`** ，为了理解它们，首先解释两个基本的名词： **`安全实体和权限`** 。

 **`安全实体：`** 就是被权限系统检测的对象，比如工资数据。 **`权限：`** 就是需要被校验的权限对象，比如查看、修改等。

 **`安全实体和权限通常要一起描述才有意义`** ，比如有这么个描述：“现在要检测登录人员对工资数据是否有查看的权限”， **`“工资数据”这个安全实体和“查看”这个权限一定要一起描述`** 。如果只出现安全实体描述，那就变成这样：“现在要检测登录人员对工资数据”，对工资数据干什么呀，没有后半截，一看就知道不完整；当然只有权限描述也不行，那就变成：“现在要检测登录人员是否有查看的权限”，对谁的查看权限啊，也不完整。所以安全实体和权限通常要一起描述。 **`了解了上面两个名词，来看看什么是授权和验证：`** 

 **`所谓授权是指：`** 把对某些安全实体的某些权限分配给某些人员的过程。 **`所谓验证是指：`** 判断某个人员对某个安全实体是否拥有某个或某些权限的过程。

也就是说， **`授权过程即是权限的分配过程，而验证过程则是权限的匹配过程`** 。在目前应用系统的开发中，多数是利用数据库来存放授权过程产生的数据，也就是说： **`授权是向数据库里面添加数据、或是维护数据的过程，而匹配过程就变成了从数据库中获取相应数据进行匹配的过程了`** 。

为了让问题相对简化一点，就不去考虑权限的另外两个特征， **`一个是继承性，一个是最近匹配原则`** ，都什么意思呢，还是解释一下：

* **`权限的继承性指的是：如果多个安全实体存在包含关系，而某个安全实体没有相应的权限限制，那么它会继承包含它的安全实体的相应权限。`** 


比如：某个大楼和楼内的房间都是安全实体，很明显大楼这个安全实体会包含楼内的房间这些安全实体，可以认为大楼是楼内房间的父级实体。现在来考虑一个具体的权限——进入某个房间的权限。如果这个房间没有门，也就是谁都可以进入，相当于这个房间对应的安全实体，没有进入房间的权限限制，那么是不是说所有的人都可以进入这个房间呢？当然不是，某人能进入这个房间的前提是：这个人要有权限进入这个大楼，也就是说，这个时候房间这个安全实体，它本身没有进入权限的限制，但是它会继承父级安全实体的进入权限。

* **`权限的最近匹配原则指的是：如果多个安全实体存在包含关系，而某个安全实体没有相应的权限限制，那么它会向上寻找并匹配相应权限限制，直到找到一个离这个安全实体最近的拥有相应权限限制的安全实体为止。如果把整个层次结构都寻找完了都没有匹配到相应权限限制的话，那就说明所有人对这个安全实体都拥有这个相应的权限限制。`** 


继续上面权限继承性的例子，如果现在这个大楼是坐落在某个机关大院内，这就演变成了，要进入某个房间，首先要有进入大楼的权限，要进入大楼又需要有能进入机关大院的权限。

所谓最近匹配原则就是，如果某个房间没有门，也就意味着这个房间没有进入的权限限制，那么它就会向上继续寻找并匹配，看看大楼有没有进入的权限限制，如果有就使用这个权限限制，终止寻找；如果没有，继续向上寻找，直到找到一个匹配的为止。如果最后大院也没有进入的权限限制，那就变成所有人都可以进入到这个房间里面来了。
## 1.2 不使用模式的解决方案##

* **`看看现在都已经有什么了`** 


系统的授权工作已经完成，授权数据记录在数据库里面，具体的数据结构就不去展开了，反正里面记录了人员对安全实体所拥有的权限。假如现在系统中已有如下的授权数据：

```java
张三  对  人员列表   拥有    查看的权限
李四  对  人员列表   拥有    查看的权限
李四  对  薪资数据   拥有    查看的权限
李四  对  薪资数据   拥有    修改的权限

```

* **`思路选择`** 


由于操作人员进行授权操作过后，各人员被授予的权限是记录在数据库中的，刚开始有开发人员提出，每次用户操作系统的时候，都直接到数据库里面去动态查询，以判断该人员是否拥有相应的权限，但很快就被否决掉了，试想一下，用户操作那么频繁，每次都到数据库里面动态查询，这会严重加剧数据库服务器的负担，使系统变慢。

 **`为了加快系统运行的速度，开发小组决定采用一定的缓存，当每个人员登录的时候，就把该人员能操作的权限获取到，存储在内存中，这样每次操作的时候，就直接在内存里面进行权限的校验，速度会大大加快，这是典型的以空间换时间的做法。`** 

* **`实现示例`** 

 **`（1）首先定义描述授权数据的数据对象，示例代码如下：`** 

```java
/**
   * 描述授权数据的数据model
   */
public class AuthorizationModel {
      /**
       * 人员
       */
      private String user;
      /**
       * 安全实体
       */
      private String securityEntity;
      /**
       * 权限
       */
      private String permit;
      public String getUser() {
         return user;
      }
      public void setUser(String user) {
         this.user = user;
      }
      public String getSecurityEntity() {
         return securityEntity;
      }
      public void setSecurityEntity(String securityEntity) {
         this.securityEntity = securityEntity;
      }
      public String getPermit() {
         return permit;
      }
      public void setPermit(String permit) {
         this.permit = permit;
      }
}

``` **`（2）为了测试方便，做一个模拟的内存数据库，把授权数据存储在里面，用最简单的字符串存储的方式。示例代码如下：`** 

```java
/**
   * 供测试用，在内存中模拟数据库中的值
   */
public class TestDB {
      /**
       * 用来存放授权数据的值
       */
      public static Collection<String> colDB = new ArrayList<String>();
      static{
         //通过静态块来填充模拟的数据    
         colDB.add("张三,人员列表,查看");
         colDB.add("李四,人员列表,查看");
         colDB.add("李四,薪资数据,查看");
         colDB.add("李四,薪资数据,修改");
         //增加更多的授权数据
         for(int i=0;i<3;i++){
             colDB.add("张三"+i+",人员列表,查看");
         }
      }  
}

``` **`（3）接下来实现登录和权限控制的业务，示例代码如下：`** 

```java
/**
   * 安全管理，实现成单例
   */
public class SecurityMgr {
      private static SecurityMgr securityMgr = new SecurityMgr();
      private SecurityMgr(){     
      }
      public static SecurityMgr getInstance(){
         return securityMgr;
      }
      /**
       * 在运行期间，用来存放登录人员对应的权限，
       * 在Web应用中，这些数据通常会存放到session中
       */
      private Map<String,Collection<AuthorizationModel>> map = new HashMap<String,Collection<AuthorizationModel>>();
  
      /**
       * 模拟登录的功能
       * @param user 登录的用户
       */
      public void login(String user){
         //登录时就需要把该用户所拥有的权限，从数据库中取出来，放到缓存中去
         Collection<AuthorizationModel> col = queryByUser(user);
         map.put(user, col);
      }
      /**
       * 判断某用户对某个安全实体是否拥有某权限
       * @param user 被检测权限的用户
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示拥有相应权限，false表示没有相应权限
       */
      public boolean hasPermit(String user,String securityEntity,String permit){
         Collection<AuthorizationModel> col = map.get(user);
         if(col==null || col.size()==0){
             System.out.println(user+"没有登录或是没有被分配任何权限");
             return false;
         }
         for(AuthorizationModel am : col){
             //输出当前实例，看看是否同一个实例对象
             System.out.println("am=="+am);
             if(am.getSecurityEntity().equals(securityEntity) && am.getPermit().equals(permit)){
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
      private Collection<AuthorizationModel> queryByUser(String user){
         Collection<AuthorizationModel> col = new ArrayList<AuthorizationModel>();
         for(String s : TestDB.colDB){
             String ss[] = s.split(",");
             if(ss[0].equals(user)){
                AuthorizationModel am = new AuthorizationModel();
                am.setUser(ss[0]);
                am.setSecurityEntity(ss[1]);
                am.setPermit(ss[2]);
            
                col.add(am);
             }
         }
         return col;
      }
}

``` **`（4）好不好用呢，写个客户端来测试一下，示例代码如下：`** 

```java
public class Client {
      public static void main(String[] args) {
         //需要先登录，然后再判断是否有权限
         SecurityMgr mgr = SecurityMgr.getInstance();
         mgr.login("张三");
         mgr.login("李四");   
         boolean f1 = mgr.hasPermit("张三","薪资数据","查看");
         boolean f2 = mgr.hasPermit("李四","薪资数据","查看");     
     
         System.out.println("f1=="+f1);
         System.out.println("f2=="+f2);
         for(int i=0;i<3;i++){
             mgr.login("张三"+i);
             mgr.hasPermit("张三"+i,"薪资数据","查看");
         }
      }
}

```

运行结果如下：

```java
am==cn.javass.dp.flyweight.example1.AuthorizationModel@1eed786
am==cn.javass.dp.flyweight.example1.AuthorizationModel@187aeca
am==cn.javass.dp.flyweight.example1.AuthorizationModel@e48e1b
f1==false
f2==true
am==cn.javass.dp.flyweight.example1.AuthorizationModel@12dacd1
am==cn.javass.dp.flyweight.example1.AuthorizationModel@119298d
am==cn.javass.dp.flyweight.example1.AuthorizationModel@f72617

```

输出结果中的f1为false，表示张三对薪资数据没有查看的权限；而f2为true，表示李四对对薪资数据有查看的权限，是正确的，基本完成了功能。
## 1.3 有何问题##

看了上面的实现，很简单，而且还考虑了性能的问题，在内存中缓存了每个人相应的权限数据，使得每次判断权限的时候，速度大大加快，实现得挺不错，难道有什么问题吗？

仔细想想，问题就来了， **`既有缓存这种方式固有的问题，也有我们自己实现上的问题`** 。先说说缓存固有的问题吧，这个不在本次讨论之列，大家了解一下。

* **`缓存时间长度的问题`** 


这些数据应该被缓存多久，如果是Web应用，这种跟登录人员相关的权限数据，多是放在session中进行缓存，这样session超时的时候，就会被清除掉。如果不是Web应用呢？就得自己来控制了，另外就算是在Web应用中，也不一定非要缓存到session超时才清除。 **`总之，控制缓存数据应该被缓存多长时间，是实现高效缓存的一个问题点。`** 

* **`缓存数据和真实数据的同步问题`** 

 **`这里的同步是指的数据同步，不是多线程的同步。`** 比如：上面的授权数据是存放在数据库里的，运行的时候缓存到内存里面，如果真实的授权数据在运行期间发生了改变，那么缓存里的数据就应该和数据库的数据同步，以保持一致，否则数据就错了。 **`如何合理的同步数据，也是实现高效缓存的一个问题点。`** 

* **`缓存的多线程并发控制`** 


对于缓存的数据，有些操作从里面取值，有些操作向缓存里面添加值，有些操作在清除过期的缓存数据，有些操作在进行缓存和真实数据的同步，在一个多线程的环境下， **`如何合理的对缓存进行并发控制，也是实现高效缓存的一个问题点。`** 

先简单提这么几个，事实上，实现合理、高效的缓存也不是一件很轻松的事情，好在这些问题，都不在我们这次的讨论之列，这里的重心还是来讲述模式，而不是缓存实现。

再来看看前面实现上的问题，仔细观察在上面输出结果中框住的部分，这些值是输出对象实例得到的， **`默认输出的是对象的hashCode值，而默认的hashCode值可以用来判断是不是同一对象实例。`** 在Java中，默认的equals方法比较的是内存地址，而equals方法和hashCode方法的关系是： **`equals方法返回true的话，那么这两个对象实例的hashCode必须相同；而hashCode相同，equals方法并不一定返回true，也就是说两个对象实例不一定是同一对象实例`** 。换句话说，如果hashCode不同的话，铁定不是同一个对象实例。

仔细看看上面输出结果，框住部分的值是不同的， **`表明这些对象实例肯定不是同一个对象实例，而是多个对象实例。`** 这就引出一个问题了，就是对象实例数目太多，为什么这么说呢？看看就描述这么几条数据，数数看有多少个对象实例呢？目前是一条数据就有一个对象实例，这很恐怖，数据库的数据量是很大的，如果有几万条，几十万条，岂不是需要几万个，甚至几十万个对象实例，这会耗费掉大量的内存。

另外， **`这些对象的粒度都很小，都是简单的描述某一个方面的对象，而且很多数据是重复的，在这些大量重复的数据上耗费掉了很多的内存`** 。比如在前面示例的数据中就会发现有重复的部分，见下面框住的部分：

```java
张三  对  人员列表   拥有    查看的权限
李四  对  人员列表   拥有    查看的权限
李四  对  薪资数据   拥有    查看的权限
李四  对  薪资数据   拥有    修改的权限

```

前面讲过， **`对于安全实体和权限一般要联合描述，因此对于“人员列表 这个安全实体 的 查看权限 限制”，就算是授权给不同的人员，这个描述是一样的。`** 假设在某极端情况下，要把“人员列表 这个安全实体 的 查看权限 限制”授权给一万个人，那么数据库里面会有一万条记录，按照前面的实现方式，会有一万个对象实例，而这些实例里面，有大部分的数据是重复的，而且会重复一万次，你觉得这是不是个很大的问题呢？

把上面的问题描述出来就是： **`在系统当中，存在大量的细粒度对象，而且存在大量的重复数据，严重耗费内存，如何解决？`** 

## 2 解决方案#
## 2.1 享元模式来解决##

用来解决上述问题的一个合理的解决方案就是享元模式。那么什么是享元模式呢？

* **`享元模式定义`** 



![][0]


享元模式定义


* **`应用享元模式来解决的思路`** 


仔细观察和分析上面的授权信息，会发现有一些数据是重复出现的，比如：人员列表、薪资数据、查看、修改等等。至于人员相关的数据，考虑到每个描述授权的对象都是和某个人员相关的，所以存放的时候，会把相同人员的授权信息组织在一起，就不去考虑人员数据的重复性了。

现在造成内存浪费的主要原因： **`就是细粒度对象太多，而且有大量重复的数据`** 。如果能够有效的减少对象的数量，减少重复的数据，那么就能够节省不少内存。一个基本的思路就是 **`缓存这些包含着重复数据的对象，让这些对象只出现一次，也就只耗费一份内存了`** 。

但是请注意， **`并不是所有的对象都适合缓存，因为缓存的是对象的实例，实例里面存放的主要是对象属性的值`** 。因此，如果被缓存的对象的属性值经常变动，那就不适合缓存了，因为真实对象的属性值变化了，那么缓存里面的对象也必须要跟着变化，否则缓存中的数据就跟真实对象的数据不同步，可以说是错误的数据了。

因此，需要分离出被缓存对象实例中，哪些数据是不变且重复出现的，哪些数据是经常变化的， **`真正应该被缓存的数据是那些不变且重复出现的数据，把它们称为对象的内部状态，而那些变化的数据就不缓存了，把它们称为对象的外部状态`** 。

这样在实现的时候， **`把内部状态分离出来共享，称之为享元，通过共享享元对象来减少对内存的占用`** 。 **`把外部状态分离出来，放到外部，让应用在使用的时候进行维护，并在需要的时候传递给享元对象使用`** 。 **`为了控制对内部状态的共享，并且让外部能简单的使用共享数据，提供一个工厂来管理享元，把它称为享元工厂`** 。
## 2.2 模式结构和说明##

享元模式的结构如图20.1所示：


![][1]


享元模式的结构


 **`Flyweight：享元接口`** ，通过这个接口flyweight可以接受并作用于外部状态。通过这个接口传入外部的状态，在享元对象的方法处理中可能会使用这些外部的数据。 **`ConcreteFlyweight：具体的享元实现对象`** ，必须是可共享的，需要封装flyweight的内部状态。 **`UnsharedConcreteFlyweight：非共享的享元实现对象`** ，并不是所有的Flyweight实现对象都需要共享。非共享的享元实现对象通常是对共享享元对象的组合对象。 **`FlyweightFactory：享元工厂`** ，主要用来创建并管理共享的享元对象，并对外提供访问共享享元的接口。 **`Client：享元客户端`** ，主要的工作是维持一个对flyweight的引用，计算或存储享元对象的外部状态，当然这里可以访问共享和不共享的flyweight对象。

## 2.3 享元模式示例代码##

* **`先看享元的接口定义，通过这个接口flyweight可以接受并作用于外部状态，示例代码如下：`** 


```java
/**
   * 享元接口，通过这个接口享元可以接受并作用于外部状态
   */
public interface Flyweight {
      /**
       * 示例操作，传入外部状态
       * @param extrinsicState 示例参数，外部状态
       */
      public void operation(String extrinsicState);
}

```

* **`接下来看看具体的享元接口的实现，先看共享享元的实现，封装flyweight的内部状态，当然也可以提供功能方法，示例代码如下：`** 


```java
/**
   * 享元对象
   */
public class ConcreteFlyweight implements Flyweight{
      /**
       * 示例，描述内部状态
       */
      private String intrinsicState;
      /**
       * 构造方法，传入享元对象的内部状态的数据
       * @param state 享元对象的内部状态的数据
       */
      public ConcreteFlyweight(String state){
         this.intrinsicState = state;
      }

      public void operation(String extrinsicState) {
         //具体的功能处理，可能会用到享元内部、外部的状态
      }  
}

```

再看看不需要共享的享元对象的实现， **`并不是所有的Flyweight对象都需要共享，Flyweight接口使共享成为可能，但并不强制共享`** 。示例代码如下：

```java
/**
   * 不需要共享的flyweight对象，
   * 通常是将被共享的享元对象作为子节点，组合出来的对象
   */
public class UnsharedConcreteFlyweight implements Flyweight{
      /**
       * 示例，描述对象的状态
       */
      private String allState;
  
      public void operation(String extrinsicState) {
         // 具体的功能处理
      }
}

```

* **`在享元模式中，客户端不能直接创建共享的享元对象实例，必须通过享元工厂来创建。接下来看看享元工厂的实现，示例代码如下：`** 


```java
/**
   * 享元工厂
   */
public class FlyweightFactory {
      /**
       * 缓存多个flyweight对象，这里只是示意一下
       */
      private Map<String,Flyweight> fsMap = new HashMap<String,Flyweight>();
      /**
       * 获取key对应的享元对象
       * @param key 获取享元对象的key，只是示意
       * @return key 对应的享元对象
       */
      public Flyweight getFlyweight(String key) {
         //这个方法里面基本的实现步骤如下：      
         //1：先从缓存里面查找，是否存在key对应的Flyweight对象
         Flyweight f = fsMap.get(key);

         //2：如果存在，就返回相对应的Flyweight对象
         if(f==null){
             //3：如果不存在
             //3.1：创建一个新的Flyweight对象
             f = new ConcreteFlyweight(key);
             //3.2：把这个新的Flyweight对象添加到缓存里面
             fsMap.put(key,f);
             //3.3：然后返回这个新的Flyweight对象
         }

         return f;
      }
}

```

* **`最后来看看客户端的实现，客户端通常会维持一个对flyweight的引用，计算或存储一个或多个flyweight的外部状态。示例代码如下：`** 


```java
/**
   * Client对象，通常会维持一个对flyweight的引用，
   * 计算或存储一个或多个flyweight的外部状态
   */
public class Client {
      //具体的功能处理
}

```
## 2.4 使用享元模式重写示例##

再次分析上面的授权信息， **`实际上重复出现的数据主要是对安全实体和权限的描述，又考虑到安全实体和权限的描述一般是不分开的，那么找出这些重复的描述`** ，比如：人员列表的查看权限。 **`而且这些重复的数据是可以重用的，比如给它们配上不同的人员，就可以组合成为不同的授权描述`** ，如图20.2所示：


![][2]


授权描述示意图


图20.2就可以描述如下的信息：

```java
张三  对  人员列表   拥有    查看的权限
李四  对  人员列表   拥有    查看的权限
王五  对  人员列表   拥有    查看的权限

```

很明显， **`可以把安全实体和权限的描述定义成为享元，而和它们结合的人员数据，就可以做为享元的外部数据`** 。为了演示简单，就把安全实体对象和权限对象简化成了字符串，描述一下它们的名字。

* **`按照享元模式，也为了系统的扩展性和灵活性，给享元定义一个接口，外部使用享元还是面向接口来编程，示例代码如下：`** 


```java
/**
   * 描述授权数据的享元接口
   */
public interface Flyweight {
      /**
       * 判断传入的安全实体和权限，是否和享元对象内部状态匹配
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示匹配，false表示不匹配
       */
      public boolean match(String securityEntity,String permit);
}

```

* **`定义了享元接口，该来实现享元对象了，这个对象需要封装授权数据中重复出现部分的数据，示例代码如下：`** 


```java
/**
   * 封装授权数据中重复出现部分的享元对象
   */
public class AuthorizationFlyweight implements Flyweight{
      /**
       * 内部状态，安全实体
       */
      private String securityEntity;
      /**
       * 内部状态，权限
       */
      private String permit;
      /**
       * 构造方法，传入状态数据
       * @param state 状态数据，包含安全实体和权限的数据，用","分隔
       */
      public AuthorizationFlyweight(String state){
         String ss[] = state.split(",");
         securityEntity = ss[0];
         permit = ss[1];
      }
  
      public String getSecurityEntity() {
         return securityEntity;
      }
      public String getPermit() {
         return permit;
      }

      public boolean match(String securityEntity, String permit) {
         if(this.securityEntity.equals(securityEntity) && this.permit.equals(permit)){
             return true;
         }
         return false;
      }  
}

```

* **`定义好了享元，来看看如何管理这些享元，提供享元工厂来负责享元对象的共享管理和对外提供访问享元的接口。`** 

 **`享元工厂一般不需要很多个，实现成为单例即可。享元工厂负责享元对象的创建和管理，基本的思路就是在享元工厂里面缓存享元对象。`** 在Java中最常用的缓存实现方式，就是定义一个Map来存放缓存的数据，而享元工厂对外提供的访问享元的接口，基本上就是根据key值到缓存的Map中获取相应的数据，这样只要有了共享，同一份数据就可以重复使用了，示例代码如下：

```java
/**
   * 享元工厂，通常实现成为单例
   */
public class FlyweightFactory {
      private static FlyweightFactory factory = new FlyweightFactory();
      private FlyweightFactory(){    
      }
      public static FlyweightFactory getInstance(){
         return factory;
      }
      /**
       * 缓存多个flyweight对象
       */
      private Map<String,Flyweight> fsMap = new HashMap<String,Flyweight>();
      /**
       * 获取key对应的享元对象
       * @param key 获取享元对象的key
       * @return key对应的享元对象
       */
      public Flyweight getFlyweight(String key) {
         Flyweight f = fsMap.get(key);
         if(f==null){
             f = new AuthorizationFlyweight(key);
             fsMap.put(key,f);
         }
         return f;
      }
}

```

* **`使用享元对象`** 


实现完享元工厂，该来看看如何使用享元对象了。按照前面的实现， **`需要一个对象来提供安全管理的业务功能，就是前面的那个SecurityMgr类`** ，这个类现在在享元模式中，就充当了Client的角色， **`注意：这个Client角色和我们平时说的测试客户端是两个概念，这个Client角色是使用享元的对象`** 。

SecurityMgr的实现方式基本上模仿前面的实现，也会有相应的改变，变化大致如下：

缓存的每个人员的权限数据，类型变成了Flyweight的了；

在原来queryByUser方法里面，通过new来创建授权对象的地方，修改成了通过享元工厂来获取享元对象，这是使用享元模式最重要的一点改变，也就是不是直接去创建对象实例，而是通过享元工厂来获取享元对象实例；

示例代码如下：

```java
/**
   * 安全管理，实现成单例
   */
public class SecurityMgr {
      private static SecurityMgr securityMgr = new SecurityMgr();
      private SecurityMgr(){     
      }
      public static SecurityMgr getInstance(){
         return securityMgr;
      }  
      /**
       * 在运行期间，用来存放登录人员对应的权限，
       * 在Web应用中，这些数据通常会存放到session中
       */
      private Map<String,Collection<Flyweight>> map = new HashMap<String,Collection<Flyweight>>();
      /**
       * 模拟登录的功能
       * @param user 登录的用户
       */
      public void login(String user){
         //登录时就需要把该用户所拥有的权限，从数据库中取出来，放到缓存中去
         Collection<Flyweight> col = queryByUser(user);
         map.put(user, col);
      }
      /**
       * 判断某用户对某个安全实体是否拥有某权限
       * @param user 被检测权限的用户
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示拥有相应权限，false表示没有相应权限
       */
      public boolean hasPermit(String user,String securityEntity,String permit){
         Collection<Flyweight> col = map.get(user);
         if(col==null || col.size()==0){
             System.out.println(user+"没有登录或是没有被分配任何权限");
             return false;
         }
         for(Flyweight fm : col){
             //输出当前实例，看看是否同一个实例对象
             System.out.println("fm=="+fm);
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
                Flyweight fm = FlyweightFactory.getInstance().getFlyweight(ss[1]+","+ss[2]);
                col.add(fm);
             }
         }
         return col;
      }
}

```

* **`所用到的TestDB没有任何变化，这里就不去赘述了。`** 

* **`客户端测试代码也没有任何变化，也不去赘述了。`** 


运行测试一下，看看效果，主要是看看是不是能有效地减少那些重复数据对象的数量。运行结果如下：

```java
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@e48e1b
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@e48e1b
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@12dacd1
f1==false
f2==true
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@e48e1b
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@e48e1b
fm==cn.javass.dp.flyweight.example3.AuthorizationFlyweight@e48e1b

```

仔细观察结果中框住的部分，会发现六条数据中，有五条的hashCode是同一个值， **`根据我们的实现，可以断定这是同一个对象`** 。也就是说，现在只有两个对象实例，而前面的实现中有六个对象实例。

如同示例的那样， **`对于封装安全实体和权限的这些细粒度对象，既是授权分配的单元对象，也是权限检测的单元对象`** 。可能有很多人对某个安全实体拥有某个权限，如果为每个人都重新创建一个对象来描述对应的安全实体和权限，那样就太浪费内存空间了。

 **`通过共享封装了安全实体和权限的对象，无论多少人拥有这个权限，实际的对象实例都是只有一个`** ，这样既减少了对象的数目，又节省了宝贵的内存空间，从而解决了前面提出的问题。

## 3 模式讲解#
## 3.1 认识享元模式##

* **`变与不变`** 

 **`享元模式设计的重点就在于分离变与不变，把一个对象的状态分成内部状态和外部状态，内部状态是不变的，外部状态是可变的。`** 然后通过共享不变的部分，达到减少对象数量、并节约内存的目的。在享元对象需要的时候，可以从外部传入外部状态给共享的对象，共享对象会在功能处理的时候，使用自己内部的状态和这些外部的状态。

事实上， **`分离变与不变是软件设计上最基本的方式之一`** ，比如预留接口，为什么在这个地方要预留接口，一个常见的原因就是这里存在变化，可能在今后需要扩展、或者是改变已有的实现，因此预留接口做为“可插入性的保证”。

* **`共享与不共享`** 


在享元模式中，享元对象又有共享与不共享之分，这种情况通常出现在跟组合模式合用的情况，通常共享的是叶子对象，一般不共享的部分是由共享部分组合而成的， **`由于所有细粒度的叶子对象都已经缓存了，那么缓存组合对象就没有什么意义了`** 。这个在后面给大家一个示例。

* **`内部状态和外部状态`** 

 **`享元模式的内部状态，通常指的是包含在享元对象内部的、对象本身的状态，通常是独立于使用享元的场景的信息`** ，一般创建过后就不再变化的状态，因此可以共享。 **`外部状态指的是享元对象之外的状态，取决于使用享元的场景，会根据使用场景而变化，因此不可共享`** 。如果享元对象需要这些外部状态的话，可以从外部传递到享元对象里面，比如通过方法的参数来传递。

也就是说 **`享元模式真正缓存和共享的数据是享元的内部状态，而外部状态是不应该被缓存共享的`** 。

另外一点， **`内部状态和外部状态是独立的，外部状态的变化不应该影响到内部状态`** 。

* **`实例池`** 


在享元模式中，为了创建和管理共享的享元部分， **`引入了享元工厂，享元工厂中一般都包含有享元对象的实例池，享元对象就是缓存在这个实例池中的`** 。

简单介绍一点实例池的知识， **`所谓实例池，指的是缓存和管理对象实例的程序，通常实例池会提供对象实例的运行环境，并控制对象实例的生命周期`** 。

工业级的实例池实现上有两个最基本的难点， **`一个就是动态控制实例数量，一个就是动态分配实例来提供给外部使用`** 。这些都是需要算法来做保证的。

假如实例池里面已有了3个实例，但是客户端请求非常多，有些忙不过来，那么实例池的管理程序就应该判断出来，到底几个实例才能满足现在的客户需求，理想状况是刚刚好，就是既能够满足应用的需要，又不会造成对象实例的浪费，假如经过判断5个实例正好，那么实例池的管理程序就应该能动态的创建2个新的实例。

这样运行了一段时间，客户端的请求减少了，这个时候实例池的管理程序又应该动态的判断，究竟几个实例是最好的，多了明显浪费资源，假如经过判断只需要1个实例就可以了，那么实例池的管理程序应该销毁掉多余的4个实例，以释放资源。 **`这就是动态控制实例数量`** 。

对于动态分配实例，也说明一下吧，假如实例池里面有3个实例，这个时候来了一个新的请求，到底调度哪一个实例去执行客户的请求呢，如果有空闲实例，那就是它了，要是没有空闲实例呢，是新建一个实例，还是等待运行中的实例，等它运行完了就来处理这个请求呢？具体如何调度，也是需要算法来保障的。

回到享元模式中来，享元工厂中的实例池可没有这么复杂， **`因为共享的享元对象基本上都是一个实例，一般不会出现同一个享元对象有多个实例的情况`** ，这样就不用去考虑动态创建和销毁享元对象实例的功能； **`另外只有一个实例，也就不存在动态调度的麻烦，反正就是它了`** 。

这也主要是 **`因为享元对象封装的多半是对象的内部状态，这些状态通常是不变的，有一个实例就够了，不需要动态控制生命周期，也不需要动态调度，它只需要做一个缓存而已，没有上升到真正的实例池那么个高度。`** 

* **`享元模式的调用顺序示意图`** 


享元模式的使用上，有两种情况， **`一种是没有“不需要共享”的享元对象`** ，就如同前面的示例那样，只有共享享元对象的情况； **`还有一种是既有共享享元对象，又有不需要共享的享元对象的情况`** ，这种情况后面再示例。

这里看看只有共享享元对象的情况下，享元模式的调用顺序，如图20.3所示：


![][3]


只有共享享元对象的情况下，享元模式的调用顺序


* **`谁来初始化共享对象`** 


在享元模式中， **`通常是在第一次向享元工厂请求获取共享对象的时候，进行共享对象的初始化，而且多半都是在享元工厂内部实现，不会从外部传入共享对象`** 。当然可以从外部传入一些创建共享对象需要的值，享元工厂可以按照这些值去初始化需要共享的对象，然后就把创建好的共享对象的实例放入享元工厂内部的缓存中，以后再请求这个共享对象的时候就不用再创建了。
## 3.2 不需要共享的享元实现##

可能有些朋友看到这个标题会很疑惑，享元不就是要共享的对象吗？不共享，叫什么享元啊？ **`确实有不需要共享的享元实现，这种情况多出现在组合结构中，对于使用已经缓存的享元组合出来的对象，就没有必要再缓存了，也就是把已经缓存的享元当做叶子结点，组合出来的组合对象就不需要再被缓存了。也把这种享元称为复合享元。`** 

比如上面的权限描述， **`如果出现组合权限描述，在这个组合对象里面包含很多个共享的权限描述，那么这个组合对象就不用缓存了，这个组合对象的存在只是为了在授权的时候更加方便`** 。

具体点说吧，比如要给某人分配“薪资数据”这个安全实体的“修改”权限，那么一定会把“薪资数据”的“查看权限”也分配给这个人，如果按照前面的做法，这就需要分配两个对象，为了方便，干脆把这两个描述组合起来，打包成一个对象，命名成为“操作薪资数据”，那么分配权限的时候，可以这么描述：

```java
把  “操作薪资数据”  分配给   张三

```

这句话的意思就相当于

```java
把  “薪资数据” 的  “查看”权限   分配给   张三
把  “薪资数据” 的  “修改”权限   分配给   张三

```

这样一来， **`“操作薪资数据”就相当于是一个不需要共享的享元`** ，它实际由享元“薪资数据 的 查看 权限”，和享元“薪资数据 的 修改 权限”这两个享元组合而成，因此“操作薪资数据”本身也就不需要再共享了。

这样分配权限的时候就会简单一点。 **`但是这种组合对象，在权限系统中一般不用于验证`** ，也就是说验证的时候还是一个一个进行判断， **`因为在存储授权信息的时候是一条一条存储的`** 。但也不排除有些时候始终要检查多个权限，干脆把这些权限打包，然后直接验证是否有这个组合权限，只是这种情况应用得比较少而已。

还是用示例来说明吧，在上面已经实现的系统里面添加不需要共享的享元实现。此时系统结构如图20.4所示：


![][4]


不需要共享享元的示例机构示意图


* **`首先要在享元接口上添加上对组合对象的操作，主要是要添加向组合对象中加入子对象的方法，示例代码如下：`** 


```java
/**
   * 描述授权数据的享元接口
   */
public interface Flyweight {
      /**
       * 判断传入的安全实体和权限，是否和享元对象内部状态匹配
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示匹配，false表示不匹配
       */
      public boolean match(String securityEntity,String permit);
      /**
       * 为flyweight添加子flyweight对象
       * @param f 被添加的子flyweight对象
       */
      public void add(Flyweight f);  
}

```

* **`享元接口改变了，那么原来共享的享元对象也需要实现这个方法，这个方法主要是针对组合对象的，因此在叶子对象里面抛出不支持的例外就好了，示例代码如下：`** 


```java
/**
   * 封装授权数据中重复出现部分的享元对象
   */
public class AuthorizationFlyweight implements Flyweight{
  
      public void add(Flyweight f) {
         throw new UnsupportedOperationException("对象不支持这个功能");
      }
}

```

* **`接下来实现新的不需要共享的享元对象，其实就是组合共享享元对象的对象，这个组合对象中，需要保存所有的子对象，另外它在实现match方法的时候，是通过递归的方式，在整个组合结构中进行匹配。示例代码如下：`** 


```java
/**
   * 不需要共享的享元对象的实现，也是组合模式中的组合对象
   */
public class UnsharedConcreteFlyweight implements Flyweight{
      /**
       * 记录每个组合对象所包含的子组件
       */
      private List<Flyweight> list = new ArrayList<Flyweight>();
  
      public void add(Flyweight f) {
         list.add(f);
      }
  
      public boolean match(String securityEntity, String permit) {
         for(Flyweight f : list){
             //递归调用
             if(f.match(securityEntity, permit)){
                return true;
             }
         }
         return false;
      }
}

```

* **`在继续实现之前，先来准备测试数据，也就是TestDB，需要有一些改变`** 


首先是授权数据要区分是单条的授权，还是组合的授权，这个在每条授权数据后面添加一个标识来描述

然后增加一个描述组合数据的记录，使用一个Map来存放

具体的示例代码如下：

```java
/**
   * 供测试用，在内存中模拟数据库中的值
   */
public class TestDB {
      /**
       * 用来存放单独授权数据的值
       */
      public static Collection<String> colDB = new ArrayList<String>();
      /**
       * 用来存放组合授权数据的值，
       * key为组合数据的id，value为该组合包含的多条授权数据的值
       */
      public static Map<String,String[]> mapDB = new HashMap<String,String[]>();
   
      static{
         //通过静态块来填充模拟的数据，增加一个标识来表明是否组合授权数据
         colDB.add("张三,人员列表,查看,1");
         colDB.add("李四,人员列表,查看,1");
         colDB.add("李四,操作薪资数据,,2");
     
         mapDB.put("操作薪资数据",new String[]{"薪资数据,查看","薪资数据,修改"});
     
         //增加更多的授权数据
         for(int i=0;i<3;i++){
             colDB.add("张三"+i+",人员列表,查看,1");
         }
      }
}

```

* **`享元工厂不需要变化，这里就不去赘述了`** 

* **`接下来该实现安全管理的类了，这个类相当于享元模式的Client角色，这次在这个类里面，不单纯使用共享的享元对象，它还会使用不需要共享的享元对象。`** 


主要的变化集中在queryByUser方法里面， **`原本只是通过享元工厂来获取共享的享元对象即可，但是这次还需要在这里创建不需要共享的享元对象`** 。示例代码如下：

```java
public class SecurityMgr {
      private static SecurityMgr securityMgr = new SecurityMgr();
      private SecurityMgr(){     
      }
      public static SecurityMgr getInstance(){
         return securityMgr;
      }
      /**
       * 在运行期间，用来存放登录人员对应的权限，
       * 在Web应用中，这些数据通常会存放到session中
       */
      private Map<String,Collection<Flyweight>> map = new HashMap<String,Collection<Flyweight>>();
      /**
       * 模拟登录的功能
       * @param user 登录的用户
       */
      public void login(String user){
         //登录时就需要把该用户所拥有的权限，从数据库中取出来，放到缓存中去
         Collection<Flyweight> col = queryByUser(user);
         map.put(user, col);
      }
      /**
       * 判断某用户对某个安全实体是否拥有某权限
       * @param user 被检测权限的用户
       * @param securityEntity 安全实体
       * @param permit 权限
       * @return true表示拥有相应权限，false表示没有相应权限
       */
      public boolean hasPermit(String user,String securityEntity,String permit){
         Collection<Flyweight> col = map.get(user);
         System.out.println("现在测试"+securityEntity+"的"+permit+"权限，map.size="+map.size());
         if(col==null || col.size()==0){
             System.out.println(user+"没有登录或是没有被分配任何权限");
             return false;
         }
         for(Flyweight fm : col){
             //输出当前实例，看看是否同一个实例对象
             System.out.println("fm=="+fm);
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

```

* **`客户端测试没有太大的变化，增加一条测试“李四对薪资数据的修改权限”，示例代码如下：`** 


```java
 public class Client {
      public static void main(String[] args) throws Exception{
         //需要先登录，然后再判断是否有权限
         SecurityMgr mgr = SecurityMgr.getInstance();
         mgr.login("张三");
         mgr.login("李四");   
         boolean f1 = mgr.hasPermit("张三","薪资数据","查看");
         boolean f2 = mgr.hasPermit("李四","薪资数据","查看");
         boolean f3 = mgr.hasPermit("李四","薪资数据","修改");
     
         System.out.println("f1=="+f1);
         System.out.println("f2=="+f2);
         System.out.println("f3=="+f3);
     
         for(int i=0;i<3;i++){
             mgr.login("张三"+i);
             mgr.hasPermit("张三"+i,"薪资数据","查看");
         }
      }
}

```

可以运行测试一下，看看效果，结果示例如下：

```java
现在测试薪资数据的查看权限，map.size=2
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1
现在测试薪资数据的查看权限，map.size=2
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1
fm==cn.javass.dp.flyweight.example4.UnsharedConcreteFlyweight@1ad086a
现在测试薪资数据的修改权限，map.size=2
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1
fm==cn.javass.dp.flyweight.example4.UnsharedConcreteFlyweight@1ad086a
f1==false
f2==true
f3==true
现在测试薪资数据的查看权限，map.size=3
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1
现在测试薪资数据的查看权限，map.size=4
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1
现在测试薪资数据的查看权限，map.size=5
fm==cn.javass.dp.flyweight.example4.AuthorizationFlyweight@12dacd1

```


[0]: ./img/2062729-18bc09a39db24070.png
[1]: ./img/2062729-59afe3fab92f40fb.png
[2]: ./img/2062729-76cfb42d02060bc5.png
[3]: ./img/2062729-bc4ea156128e1a85.png
[4]: ./img/2062729-f90cad432452cc1f.png