## 【结构型模式十三】代理模式（Proxy）

2016.08.12 15:33*

来源：[https://www.jianshu.com/p/91cab56826d6](https://www.jianshu.com/p/91cab56826d6)


          
## 1 场景问题#
## 1.1 访问多条数据##

考虑这样一个实际应用：要一次性访问多条数据。

这个功能的背景是这样的；在一个HR（人力资源）应用项目中客户提出，当选择一个部门或是分公司的时候，要把这个部门或者分公司下的所有员工都显示出来，而且不要翻页，好方便他们进行业务处理。在显示全部员工的时候，只需要显示名称即可，但是也需要提供如下的功能：在必要的时候可以选择并查看某位员工的详细信息。

客户方是一个集团公司，有些部门或者分公司可能有好几百人，不让翻页，也就是要求一次性的获取这多条数据并展示出来。

该怎么样实现呢？
## 1.2 不用模式的解决方案##

不就是要获取某个部门或者某个分公司下的所有员工的信息吗？直接使用sql语句从数据库中查询就可以得到，示意性的SQL大致如下：

```java
String sql = "select * from 用户表,部门表 "
            +"where 用户表.depId=部门表.depId "
            +"and 部门表.depId like '"+用户选择查看的depId+"%'";

```

为了方便获取某个部门或者某个分公司下的所有员工的信息，设计部门编号的时候，是按照层级来进行编码的，比如：上一级部门的编码为“01”，那么本级的编码就是“0101”、“0102”……以此类推，下一级的编码就是“010101”、“010102”……。

这种设计方式，从设计上看虽然不够优雅，但是实用，像这种获取某个部门或者某个分公司下的所有员工的信息的功能，就不用递归去查找了，直接使用like，只要找到以该编号开头的所有部门就可以了。

示例涉及到的表有两个，一个是用户表，一个是部门表。两个表需要描述的字段都较多，尤其是用户表，多达好几十个，为了示例简洁，简化后简单的定义如下：

```java
DROP TABLE TBL_USER CASCADE CONSTRAINTS ;
DROP TABLE TBL_DEP CASCADE CONSTRAINTS ;
 
CREATE TABLE TBL_DEP (
    DEPID VARCHAR2(20)  PRIMARY KEY,
    NAME  VARCHAR2(20)
);
CREATE TABLE TBL_USER (
    USERID VARCHAR2(20)  PRIMARY KEY,
    NAME VARCHAR2(20) ,
    DEPID VARCHAR2(20) ,
    SEX VARCHAR2(10) ,
    CONSTRAINT TBL_USER_FK FOREIGN KEY(DEPID)
    REFERENCES TBL_DEP(DEPID)
);

```

全部采用大写，是基于Oracle开发的习惯。再来增加点测试数据，SQL如下：

```java
INSERT INTO TBL_DEP VALUES('01','总公司');
INSERT INTO TBL_DEP VALUES('0101','一分公司');
INSERT INTO TBL_DEP VALUES('0102','二分公司');
INSERT INTO TBL_DEP VALUES('010101','开发部');
INSERT INTO TBL_DEP VALUES('010102','测试部');
INSERT INTO TBL_DEP VALUES('010201','开发部');
INSERT INTO TBL_DEP VALUES('010202','客服部');
INSERT INTO TBL_USER VALUES('user0001','张三1','010101','男');
INSERT INTO TBL_USER VALUES('user0002','张三2','010101','男');
INSERT INTO TBL_USER VALUES('user0003','张三3','010102','男');
INSERT INTO TBL_USER VALUES('user0004','张三4','010201','男');
INSERT INTO TBL_USER VALUES('user0005','张三5','010201','男');
INSERT INTO TBL_USER VALUES('user0006','张三6','010202','男');
COMMIT;

```

准备好了表结构和测试数据，下面来看看具体的实现示例，为了示例的简洁，直接使用JDBC来完成。 **`（1）先来定义描述用户数据的对象，示例代码如下：`** 

```java
/**
 * 描述用户数据的对象
 */
public class UserModel {
    /**
     * 用户编号
     */
    private String userId;
    /**
     * 用户姓名
     */
    private String name;
    /**
     * 部门编号
     */
    private String depId;
    /**
     * 性别
     */
    private String sex; 
 
    public String getUserId() {
       return userId;
    }
    public void setUserId(String userId) {
       this.userId = userId;
    }
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
    public String getDepId() {
       return depId;
    }
    public void setDepId(String depId) {
       this.depId = depId;
    }
    public String getSex() {
       return sex;
    }
    public void setSex(String sex) {
       this.sex = sex;
    }  
    public String toString(){
       return "userId="+userId+",name="+name+",depId="+depId+",sex="+sex+"\n";
    }
}

``` **`（2）接下来使用JDBC来实现要求的功能，示例代码如下：`** 

```java
/**
 * 实现示例要求的功能
 */
public class UserManager {
    /**
     * 根据部门编号来获取该部门下的所有人员
     * @param depId 部门编号
     * @return 该部门下的所有人员
     */
    public Collection<UserModel> getUserByDepId(String depId)throws Exception{
       Collection<UserModel> col = new ArrayList<UserModel>();
       Connection conn = null;
       try{
           conn = this.getConnection();
           String sql = "select * from tbl_user u,tbl_dep d "
                        +"where u.depId=d.depId and d.depId like ?";
 
           PreparedStatement pstmt = conn.prepareStatement(sql);
           pstmt.setString(1, depId+"%");
          
           ResultSet rs = pstmt.executeQuery();
           while(rs.next()){
              UserModel um = new UserModel();
              um.setUserId(rs.getString("userId"));
              um.setName(rs.getString("name"));
              um.setDepId(rs.getString("depId"));
              um.setSex(rs.getString("sex"));
             
              col.add(um);
           }
           rs.close();
           pstmt.close();
       }finally{
           conn.close();
       }
       return col;
    }
    /**
     * 获取与数据库的连接
     * @return 数据库连接
     */
    private Connection getConnection() throws Exception {
       Class.forName("你用的数据库对应的JDBC驱动类");
       return DriverManager.getConnection("连接数据库的URL", "用户名", "密码");
    }
}

``` **`（3）写个客户端来测试看看，是否能满足功能要求，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) throws Exception{
       UserManager userManager = new UserManager();
       Collection<UserModel> col = userManager.getUserByDepId("0101");
       System.out.println(col);
    }
}

```

运行结果如下：

```java
[userId=user0001,name=张三1,depId=010101,sex=男
, userId=user0002,name=张三2,depId=010101,sex=男
, userId=user0003,name=张三3,depId=010102,sex=男
]

```
## 1.3 有何问题##

上面的实现看起来很简单，功能也正确，但是蕴含一个较大的问题，那就是： **`当一次性访问的数据条数过多，而且每条描述的数据量又很大的话，那会消耗较多的内存`** 。

前面也说了，对于用户表，事实上是有很多字段的，不仅仅是示例的那么几个，再加上不使用翻页，一次性访问的数据就可能会有很多条。如果一次性需要访问的数据较多的话，内存开销会比较大。

但是从客户使用角度来说，有很大的随机性，客户既可能访问每一条数据，也可能一条都不访问。也就是说， **`一次性访问很多条数据，消耗了大量内存，但是很可能是浪费掉了，客户根本就不会去访问那么多数据，对于每条数据，客户只需要看看姓名而已`** 。

那么该怎么实现，才能既把多条用户数据的姓名显示出来，而又能节省内存空间，当然还要实现在客户想要看到更多数据的时候，能正确访问到数据呢？
## 2 解决方案#
## 2.1 代理模式来解决##

用来解决上述问题的一个合理的解决方案就是代理模式。那么什么是代理模式呢？

* **`代理模式定义`** 



![][0]


代理模式定义


* **`应用代理模式来解决的思路`** 


仔细分析上面的问题，一次性访问多条数据，这个可能性是很难避免的，是客户的需要。也就是说，要想节省内存，就不能从减少数据条数入手了， **`那就只能从减少每条数据的数据量上来考虑。`** 

一个基本的思路如下：由于客户访问这多条用户数据的时候，基本上只需要看到用户的姓名，因此可以考虑刚开始从数据库查询返回的用户数据就只有用户编号和用户姓名，当客户想要详细查看某个用户的数据的时候，再次根据用户编号到数据库中获取完整的用户数据。这样一来，就可以在满足客户功能的前提下，大大减少对内存的消耗，只是每次需要重新查询一下数据库，算是一个以时间换空间的策略。

可是该如何来表示这个只有用户编号和姓名的对象呢？ **`它还需要实现在必要的时候访问数据库去重新获取完整的用户数据`** 。

代理模式引入一个Proxy对象来解决这个问题，刚开始只有用户编号和姓名的时候，不是一个完整的用户对象，而是一个代理对象，当需要访问完整的用户数据的时候，代理会从数据库中重新获取相应的数据，通常情况下是当客户需要访问除了用户编号和姓名之外的数据的时候，代理才会重新去获取数据。
## 2.2 模式结构和说明##

代理模式的结构如图11.1所示：


![][1]


代理模式的结构


 **`Proxy：代理对象`** ，通常具有如下功能：

```java
   1. 实现与具体的目标对象一样的接口，这样就可以使用代理来代替具体的目标对象

   2. 保存一个指向具体目标对象的引用，可以在需要的时候调用具体的目标对象，可以控制对具体目标对象的访问，并可能负责创建和删除它

``` **`Subject：目标接口，定义代理和具体目标对象的接口`** ，这样就可以在任何使用具体目标对象的地方使用代理对象 **`RealSubject：具体的目标对象`** ，真正实现目标接口要求的功能。

在运行时刻一种可能的代理结构的对象图如图11.2所示：


![][2]


运行时刻一种可能的代理结构的对象图

## 2.3 代理模式示例代码##

* **`先看看目标接口的定义，示例代码如下：`** 


```java
/**
   * 抽象的目标接口，定义具体的目标对象和代理公用的接口
   */
public interface Subject {
      /**
       * 示意方法：一个抽象的请求方法
       */
      public void request();
}

```

* **`接下来看看具体目标对象的实现示意，示例代码如下：`** 


```java
/**
   * 具体的目标对象，是真正被代理的对象
   */
public class RealSubject implements Subject{
      public void request() {
         //执行具体的功能处理
      }
}

```

* **`接下来看看代理对象的实现示意，示例代码如下：`** 


```java
/**
   * 代理对象
   */
public class Proxy implements Subject{
      /**
       * 持有被代理的具体的目标对象
       */
      private RealSubject realSubject=null;
      /**
       * 构造方法，传入被代理的具体的目标对象
       * @param realSubject 被代理的具体的目标对象
       */
      public Proxy(RealSubject realSubject){
         this.realSubject = realSubject;
      }
      public void request() {
         //在转调具体的目标对象前，可以执行一些功能处理
       
         //转调具体的目标对象的方法
         realSubject.request();
     
         //在转调具体的目标对象后，可以执行一些功能处理
      }
}

```
## 2.4 使用代理模式重写示例##

要使用代理模式来重写示例， **`首先就需要为用户对象定义一个接口，然后实现相应的用户对象的代理，这样在使用用户对象的地方，就使用这个代理对象就可以了。`** 

这个代理对象，在起初创建的时候，只需要装载用户编号和姓名这两个基本的数据，然后在客户需要访问除这两个属性外的数据的时候，才再次从数据库中查询并装载数据，从而达到节省内存的目的，因为如果用户不去访问详细的数据，那么那些数据就不需要被装载，那么对内存的消耗就会减少。

先看看这个时候系统的整体结构，如图11.3所示：


![][3]


代理模式重写示例的系统结构示意图


此时的UserManager类，充当了标准代理模式中的Client的角色，因为是它在使用代理对象和用户数据对象的接口。

* **`先看看新定义的用户数据对象的接口，非常简单，就是对用户数据对象属性操作的getter/setter方法，因此也没有必要去注释了，示例代码如下：`** 


```java
/**
   * 定义用户数据对象的接口
   */
public interface UserModelApi {
      public String getUserId();
      public void setUserId(String userId);
      public String getName();
      public void setName(String name);
      public String getDepId();
      public void setDepId(String depId);
      public String getSex();
      public void setSex(String sex);
}

```

* **`定义了接口，需要让UserModel来实现它。基本没有什么变化，只是要实现这个新的接口而已，就不去代码示例了。`** 

* **`接下来看看新加入的代理对象的实现，示例代码如下：`** 

```java
/**
   * 代理对象,代理用户数据对象
   */
public class Proxy implements UserModelApi{
      /**
       * 持有被代理的具体的目标对象
       */
      private UserModel realSubject=null;

      /**
       * 构造方法，传入被代理的具体的目标对象
       * @param realSubject 被代理的具体的目标对象
       */
      public Proxy(UserModel realSubject){
         this.realSubject = realSubject;
      }
      /**
       * 标示是否已经重新装载过数据了
       */
      private boolean loaded = false;
  
      public String getUserId() {
         return realSubject.getUserId();
      }
      public void setUserId(String userId) {
         realSubject.setUserId(userId);
      }
      public String getName() {
         return realSubject.getName();
      }
      public void setName(String name) {
         realSubject.setName(name);
      }
      public void setDepId(String depId) {
         realSubject.setDepId(depId);
      }
      public void setSex(String sex) {
         realSubject.setSex(sex);
      }
      public String getDepId() {
         //需要判断是否已经装载过了
         if(!this.loaded){
             //从数据库中重新装载
             reload();
             //设置重新装载的标志为true
             this.loaded = true;
         }
         return realSubject.getDepId();
      }  
      public String getSex() {
         if(!this.loaded){
             reload();
             this.loaded = true;
         }
         return realSubject.getSex();
      }
      /**
       * 重新查询数据库以获取完整的用户数据
       */
      private void reload(){
         System.out.println("重新查询数据库获取完整的用户数据，userId=="+realSubject.getUserId());
         Connection conn = null;
         try{
             conn = this.getConnection();
             String sql = "select * from tbl_user where userId=?";

             PreparedStatement pstmt = conn.prepareStatement(sql);
             pstmt.setString(1, realSubject.getUserId());        
             ResultSet rs = pstmt.executeQuery();
             if(rs.next()){
                //只需要重新获取除了userId和name外的数据
                realSubject.setDepId(rs.getString("depId"));
                realSubject.setSex(rs.getString("sex"));
             }
         
             rs.close();
             pstmt.close();
         }catch(Exception err){
             err.printStackTrace();
         }finally{
             try {
                conn.close();
             } catch (SQLException e) {
                e.printStackTrace();
             }
         }
      }
      public String toString(){
         return "userId="+getUserId()+",name="+getName()+",depId="+getDepId()+",sex="+getSex()+"\n";
      }
      private Connection getConnection() throws Exception {
         Class.forName("你用的数据库对应的JDBC驱动类");
         return DriverManager.getConnection("连接数据库的URL", "用户名", "密码");
      }
}

```

* **`看看此时UserManager的变化，大致如下：`** 


从数据库查询值的时候，不需要全部获取了，只需要查询用户编号和姓名的数据就可以了；

把数据库中获取的值转变成对象的时候，创建的对象不再是UserModel，而是代理对象，而且设置值的时候，也不是全部都设置，只是设置用户编号和姓名两个属性的值；

示例代码如下：

```java
/**
   * 实现示例要求的功能
   */
public class UserManager { 
      /**
       * 根据部门编号来获取该部门下的所有人员
       * @param depId 部门编号
       * @return 该部门下的所有人员
       */
      public Collection<UserModelApi> getUserByDepId(String depId)throws Exception{
         Collection<UserModelApi> col = new ArrayList<UserModelApi>();
         Connection conn = null;
         try{
             conn = this.getConnection();
             //只需要查询userId和name两个值就可以了
             String sql = "select u.userId,u.name "
              +"from tbl_user u,tbl_dep d "
              +"where u.depId=d.depId and d.depId like ?";

             PreparedStatement pstmt = conn.prepareStatement(sql);
             pstmt.setString(1, depId+"%");
         
             ResultSet rs = pstmt.executeQuery();
             while(rs.next()){
                //这里是创建的代理对象，而不是直接创建UserModel的对象
                Proxy proxy = new Proxy(new UserModel());
                //只是设置userId和name两个值就可以了
                proxy.setUserId(rs.getString("userId"));
                proxy.setName(rs.getString("name"));
            
                col.add(proxy);
             }
         
             rs.close();
             pstmt.close();
         }finally{
             conn.close();
         }
         return col;
      }

      private Connection getConnection() throws Exception {
         Class.forName("你用的数据库对应的JDBC驱动类");
         return DriverManager.getConnection("连接数据库的URL", "用户名", "密码");
      }
}

```

* **`写个客户端来测试看看，是否能正确实现代理的功能呢，示例代码如下：`** 


```java
public class Client {
      public static void main(String[] args) throws Exception{
         UserManager userManager = new UserManager();
         Collection<UserModelApi> col = userManager.getUserByDepId("0101");

         //如果只是显示用户名称，那么不需要重新查询数据库
         for(UserModelApi umApi : col){
             System.out.println("用户编号：="+umApi.getUserId()+",用户姓名：="+umApi.getName());
         }
         //如果访问非用户编号和用户姓名外的属性，那就会重新查询数据库
         for(UserModelApi umApi : col){
             System.out.println("用户编号：="+umApi.getUserId()+",用户姓名：="+umApi.getName()+",所属部门：="+umApi.getDepId());
         }
      }
}

```

运行结果如下：

```java
用户编号：=user0001,用户姓名：=张三1
用户编号：=user0002,用户姓名：=张三2
用户编号：=user0003,用户姓名：=张三3
重新查询数据库获取完整的用户数据，userId==user0001
用户编号：=user0001,用户姓名：=张三1,所属部门：=010101
重新查询数据库获取完整的用户数据，userId==user0002
用户编号：=user0002,用户姓名：=张三2,所属部门：=010101
重新查询数据库获取完整的用户数据，userId==user0003
用户编号：=user0003,用户姓名：=张三3,所属部门：=010102

```

仔细查看上面的结果数据会发现，如果只是访问用户编号和用户姓名的数据，是不需要重新查询数据库的，只有当访问到这两个数据以外的数据时，才需要重新查询数据库以获得完整的数据。这样一来，如果客户不访问除这两个数据以外的数据，那么就不需要重新查询数据库，也就不需要装载那么多数据，从而节省内存。

* **`1+N次查询`** 


看完上面的示例，可能有些朋友会发现，这种实现方式有一个潜在的问题，就是如果客户对每条用户数据都要求查看详细的数据的话，那么总的查询数据库的次数会是1+N次之多。 **`第一次查询，获取到N条数据的用户编号和姓名，然后展示给客户看。`** 如果这个时候，客户对每条数据都点击查看详细信息的话，那么每一条数据都需要重新查询数据库，那么最后总的查询数据库的次数就是1+N次了。

从上面的分析可以看出，这种做法最合适的场景就是： **`客户大多数情况下只需要查看用户编号和姓名，而少量的数据需要查看详细数据。`** 这样既节省了内存，又减少了操作数据库的次数。

看到这里，可能会有朋友想起，Hibernate这类ORM的框架，在Lazy Load的情况下，也存在1+N次查询的情况，原因就在于， **`Hibernate的Lazy Load就是使用代理来实现的，具体的实现细节这里就不去讨论了，但是原理是一样的`** 。
## 3 模式讲解#
## 3.1 认识代理模式##

* **`代理模式的功能`** 


 **`代理模式是通过创建一个代理对象，用这个代理对象去代表真实的对象，客户端得到这个代理对象过后，对客户端没有什么影响，就跟得到了真实对象一样来使用。`** 

 **`当客户端操作这个代理对象的时候，实际上功能最终还是会由真实的对象来完成，只不过是通过代理操作的，也就是客户端操作代理，代理操作真正的对象。`** 

正是因为有代理对象夹在客户端和被代理的真实对象中间，相当于一个中转，那么在中转的时候就有很多花招可以玩，比如：判断一下权限，如果没有足够的权限那就不给你中转了，等等。

* **`代理的分类`** 


事实上代理又被分成多种，大致有如下一些：

 **`虚代理：`** 根据需要来创建开销很大的对象， **`该对象只有在需要的时候才会被真正创建`** ； **`远程代理：用来在不同的地址空间上代表同一个对象`** ，这个不同的地址空间可以是在本机，也可以在其它机器上，在Java里面最典型的就是RMI技术； **`Copy-on-Write代理：`** 在客户端操作的时候， **`只有对象确实改变了，才会真的拷贝（或克隆）一个目标对象`** ，算是虚代理的一个分支； **`保护代理：控制对原始对象的访问`** ，如果有需要，可以给不同的用户提供不同的访问权限，以控制他们对原始对象的访问； **`Cache代理：为那些昂贵的操作的结果提供临时的存储空间`** ，以便多个客户端可以共享这些结果； **`防火墙代理：保护对象不被恶意用户访问和操作`** ； **`同步代理：使多个用户能够同时访问目标对象而没有冲突`** ； **`智能指引：在访问对象时执行一些附加操作`** ，比如：对指向实际对象的引用计数、第一次引用一个持久对象时，将它装入内存等；

在这些代理类型中，最常见的是： **`虚代理、保护代理、远程代理和智能指引`** 这几种。

对于远程代理，没有去讨论， **`因为在Java中，远程代理的典型体现是RMI技术`** ，要把远程代理讲述清楚，就需要把RMI讲述清楚，这不在本书讨论范围之内。

对于智能指引，基本的实现方式和保护代理的实现类似，只是实现的具体功能有所不同，因此也没有具体去讨论和示例。

* **`虚代理的示例`** 


前面的例子就是一个典型的虚代理的实现。

起初每个代理对象只有用户编号和姓名的数据，直到需要的时候，才会把整个用户的数据装载到内存中来。

也就是说，要根据需要来装载整个UserModel的数据，虽然用户数据对象是前面已经创建好了的，但是只有用户编号和姓名的数据，可以看成是一个“虚”的对象，直到通过代理把所有的数据都设置好，才算是一个完整的用户数据对象。

* **`Copy-on-Write`** 


拷贝一个大的对象是很消耗资源的， **`如果这个被拷贝的对象从上次操作以来，根本就没有被修改过，那么再拷贝这个对象是没有必要的，白白消耗资源而已`** 。那么就可以使用代理来延迟拷贝的过程，可以等到对象被修改的时候才真的对它进行拷贝。

Copy-on-Write可以大大降低拷贝大对象的开销，因此它算是一种优化方式，可以根据需要来拷贝或者克隆对象。

* **`具体目标和代理的关系`** 


从代理模式的结构图来看，好像是有一个具体目标类就有一个代理类，其实不是这样的。 **`如果代理类能完全通过接口来操作它所代理的目标对象，那么代理对象就不需要知道具体的目标对象，这样就无须为每一个具体目标类都创建一个代理类了`** 。 **`但是，如果代理类必须要实例化它代理的目标对象，那么代理类就必须知道具体被代理的对象`** ，这种情况下，一个具体目标类通常会有一个代理类。这种情况多出现在虚代理的实现里面。

* **`代理模式调用顺序示意图`** 



![][4]


代理模式调用顺序示意图

## 3.2 保护代理## **`保护代理是一种控制对原始对象访问的代理，多用于对象应该有不同的访问权限的时候。`** 保护代理会检查调用者是否具有请求所必需的访问权限，如果没有相应的权限，那么就不会调用目标对象，从而实现对目标对象的保护。

* **`示例需求`** 


现在有一个订单系统，要求是：一旦订单被创建，只有订单的创建人才可以修改订单中的数据，其他人不能修改。

相当于现在如果有了一个订单对象实例，那么就需要控制外部对它的访问，满足条件的可以访问，而不满足条件的就不能访问了。

* **`示例实现`** 

 **`（1）订单对象的接口定义`** 

要实现这个功能需要，先来定义订单对象的接口，很简单，主要是对订单对象的属性的getter/setter方法，示例代码如下：

```java
/**
   * 订单对象的接口定义
   */
public interface OrderApi {
      /**
       * 获取订单订购的产品名称
       * @return 订单订购的产品名称
       */
      public String getProductName();
      /**
       * 设置订单订购的产品名称
       * @param productName 订单订购的产品名称
       * @param user 操作人员
       */
      public void setProductName(String productName,String user);
      /**
       * 获取订单订购的数量
       * @return 订单订购的数量
       */
      public int getOrderNum();
      /**
       * 设置订单订购的数量
       * @param orderNum 订单订购的数量
       * @param user 操作人员
       */
      public void setOrderNum(int orderNum,String user);
      /**
       * 获取创建订单的人员
       * @return 创建订单的人员
       */
      public String getOrderUser();
      /**
       * 设置创建订单的人员
       * @param orderUser 创建订单的人员
       * @param user 操作人员
       */
      public void setOrderUser(String orderUser,String user);
}

``` **`（2）订单对象`** 

接下来定义订单对象，原本订单对象需要描述的属性很多，为了简单，只描述三个就好了，示例代码如下：

```java
/**
   * 订单对象
   */
public class Order implements OrderApi{
      /**
       * 订单订购的产品名称
       */
      private String productName;
      /**
       * 订单订购的数量
       */
      private int orderNum;
      /**
       * 创建订单的人员
       */
      private String orderUser;
  
      /**
       * 构造方法，传入构建需要的数据
       * @param productName 订单订购的产品名称
       * @param orderNum 订单订购的数量
       * @param orderUser 创建订单的人员
       */
      public Order(String productName,int orderNum,String orderUser){
         this.productName = productName;
         this.orderNum = orderNum;
         this.orderUser = orderUser;
      }
  
      public String getProductName() {
         return productName;
      }
      public void setProductName(String productName,String user) {
         this.productName = productName;
      }
      public int getOrderNum() {
         return orderNum;
      }
      public void setOrderNum(int orderNum,String user) {
         this.orderNum = orderNum;
      }
      public String getOrderUser() {
         return orderUser;
      }
      public void setOrderUser(String orderUser,String user) {
         this.orderUser = orderUser;
      }
}

``` **`（3）订单对象的代理`** 

创建好了订单对象，需要创建对它的代理对象了。 **`既然订单代理就相当于一个订单，那么最自然的方式就是让订单代理跟订单对象实现一样的接口`** ；要控制对订单setter方法的访问，那么就需要在代理的方法里面进行权限判断，有权限就调用订单对象的方法，没有权限就提示错误并返回。示例代码如下：

```java
/**
   * 订单的代理对象
   */
public class OrderProxy implements OrderApi{
      /**
       * 持有被代理的具体的目标对象
       */
      private Order order=null;
      /**
       * 构造方法，传入被代理的具体的目标对象
       * @param realSubject 被代理的具体的目标对象
       */
      public OrderProxy(Order realSubject){
         this.order = realSubject;
      }

      public void setProductName(String productName,String user) {
         //控制访问权限，只有创建订单的人员才能够修改
         if(user!=null && user.equals(this.getOrderUser())){
             order.setProductName(productName, user);
         }else{
             System.out.println("对不起"+user+"，您无权修改订单中的产品名称。");
         }
      }
      public void setOrderNum(int orderNum,String user) {
         //控制访问权限，只有创建订单的人员才能够修改
         if(user!=null && user.equals(this.getOrderUser())){
             order.setOrderNum(orderNum, user);
         }else{
             System.out.println("对不起"+user+"，您无权修改订单中的订购数量。");
         }
      }
      public void setOrderUser(String orderUser,String user) {
         //控制访问权限，只有创建订单的人员才能够修改
         if(user!=null && user.equals(this.getOrderUser())){
             order.setOrderUser(orderUser, user);
         }else{
             System.out.println("对不起"+user+"，您无权修改订单中的订购人。");
         }
      }

      public int getOrderNum() {
         return this.order.getOrderNum();
      }
      public String getOrderUser() {
         return this.order.getOrderUser();
      }
      public String getProductName() {
         return this.order.getProductName();
      }
      public String toString(){
         return "productName="+this.getProductName()+",orderNum="+this.getOrderNum()+",orderUser="+this.getOrderUser();
      }
}

``` **`（4）测试代码`** 

一起来看看如何使用刚刚完成的订单代理，示例代码如下：

```java
public class Client {
      public static void main(String[] args) {
         //张三先登录系统创建了一个订单
         OrderApi order = new OrderProxy(new Order("设计模式",100,"张三"));
         //李四想要来修改，那就会报错
         order.setOrderNum(123, "李四");
         //输出order
         System.out.println("李四修改后订单记录没有变化："+order);
         //张三修改就不会有问题
         order.setOrderNum(123, "张三");
         //再次输出order
         System.out.println("张三修改后，订单记录："+order);
      }
}

```

运行结果如下：

```java
对不起李四，您无权修改订单中的订购数量。
李四修改后订单记录没有变化：
productName=设计模式,orderNum=100,orderUser=张三
张三修改后，订单记录：productName=设计模式,orderNum=123,orderUser=张三

```

从上面的运行结果就可以看出，在通过代理转调目标对象的时候，在代理对象里面，对访问的用户进行了权限判断，如果不满足要求，就不会转调目标对象的方法，从而保护了目标对象的方法，只让有权限的人操作。
## 3.3 Java中的代理##

Java对代理模式提供了内建的支持，在java.lang.reflect包下面， **`提供了一个Proxy的类和一个InvocationHandler的接口`** 。 **`通常把前面自己实现的代理模式，称为Java的静态代理。`** 这种实现方式有一个较大的缺点，就是如果Subject接口发生变化，那么代理类和具体的目标实现都要变化，不是很灵活， **`而使用Java内建的对代理模式支持的功能来实现则没有这个问题。`**  **`通常把使用Java内建的对代理模式支持的功能来实现的代理称为Java的动态代理。`** 动态代理跟静态代理相比，明显的变化是：静态代理实现的时候，在Subject接口上定义很多的方法，代理类里面自然也要实现很多方法； **`而动态代理实现的时候，虽然Subject接口上定义了很多方法，但是动态代理类始终只有一个invoke方法。`** 这样当Subject接口发生变化的时候，动态代理的接口就不需要跟着变化了。

 **`Java的动态代理目前只能代理接口，基本的实现是依靠Java的反射机制和动态生成class的技术，来动态生成被代理的接口的实现对象。`** 具体的内部实现细节这里不去讨论。 **`如果要实现类的代理，可以使用cglib（一个开源的Code Generation Library）。`** 

还是来看看示例，那就修改上面保护代理的示例，看看如何使用Java的动态代理来实现同样的功能。

* 订单接口的定义是完全一样的，就不去赘述了。

* 订单对象的实现，只是添加了一个toString，以方便测试输出，这里也不去示例了。在前面的示例中，toString是实现在代理类里面了。

* 直接看看代理类的实现，大致有如下变化：


要实现InvocationHandler接口；

需要提供一个方法来实现：把具体的目标对象和动态代理绑定起来，并在绑定好过后，返回被代理的目标对象的接口，以利于客户端的操作；

需要实现invoke方法，在这个方法里面，去具体判断当前是在调用什么方法，需要如何处理；

示例代码如下：

```java
/**
   * 使用Java中的动态代理
   */
public class DynamicProxy implements InvocationHandler{
      /**
       * 被代理的对象
       */
      private OrderApi order = null;
      /**
       * 获取绑定好代理和具体目标对象后的目标对象的接口
       * @param order 具体的订单对象，相当于具体目标对象
       * @return 绑定好代理和具体目标对象后的目标对象的接口
       */
      public OrderApi getProxyInterface(Order order){
         //设置被代理的对象，好方便invoke里面的操作
         this.order = order;
         //把真正的订单对象和动态代理关联起来
         OrderApi orderApi = (OrderApi) Proxy.newProxyInstance(
                order.getClass().getClassLoader(),
                order.getClass().getInterfaces(),
                this);
         return orderApi;
      }
  
      public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
         //如果是调用setter方法就需要检查权限
         if(method.getName().startsWith("set")){
             //如果不是创建人，那就不能修改
             if(order.getOrderUser()!=null && order.getOrderUser().equals(args[1])){
                //可以操作
                return method.invoke(order, args);
             }else{
                System.out.println("对不起，"+args[1]+"，您无权修改本订单中的数据");
             }
         }else{
             //不是调用的setter方法就继续运行
             return method.invoke(order, args);
         }
         return null;
      }
}

```

* **`看看现在的客户端如何使用这个动态代理，示例代码如下：`** 


```java
public class Client {
      public static void main(String[] args) {
         //张三先登录系统创建了一个订单
         Order order = new Order("设计模式",100,"张三");
      
         //创建一个动态代理
         DynamicProxy dynamicProxy = new DynamicProxy();     
         //然后把订单和动态代理关联起来
         OrderApi orderApi = dynamicProxy.getProxyInterface(order);
     
         //以下就需要使用被代理过的接口来操作了
         //李四想要来修改，那就会报错
         orderApi.setOrderNum(123, "李四");
         //输出order
         System.out.println("李四修改后订单记录没有变化："+orderApi);
         //张三修改就不会有问题
         orderApi.setOrderNum(123, "张三");
         //再次输出order
         System.out.println("张三修改后，订单记录："+orderApi);
      }
}

```

运行结果如下：

```java
对不起，李四，您无权修改本订单中的数据
李四修改后订单记录没有变化：
productName=设计模式,orderNum=100,orderUser=张三
张三修改后，订单记录：productName=设计模式,orderNum=123,orderUser=张三

```

事实上， **`Java的动态代理还是实现AOP（面向方面编程）的一个重要手段`** ，AOP的知识这里暂时不去讲述，大家先了解这一点就可以了。
## 3.4 代理模式的优缺点##

代理模式在客户和被客户访问的对象之间，引入了一定程度的间接性，客户是直接使用代理，让代理来与被访问的对象进行交互。不同的代理类型，这种附加的间接性有不同的用途，也就是有不同的特点：

 **`远程代理：隐藏了一个对象存在于不同的地址空间的事实`** ，也即是客户通过远程代理去访问一个对象，根本就不关心这个对象在哪里，也不关心如何通过网络去访问到这个对象，从客户的角度来讲，它只是在使用代理对象而已。 **`虚代理：可以根据需要来创建“大”对象，只有到必须创建对象的时候，虚代理才会创建对象`** ，从而大大加快程序运行速度，并节省资源。通过虚代理可以对系统进行优化。 **`保护代理：可以在访问一个对象的前后，执行很多附加的操作`** ，除了进行权限控制之外，还可以进行很多跟业务相关的处理，而不需要修改被代理的对象。也就是说，可以通过代理来给目标对象增加功能。 **`智能指引：跟保护代理类似`** ，也是允许在访问一个对象的前后，执行很多附加的操作，这样一来就可以做很多额外的事情，比如：引用计数等。

## 3.5 思考代理模式##

* **`代理模式的本质`** 


 **`代理模式的本质：控制对象访问。`** 

代理模式通过代理目标对象，把代理对象插入到客户和目标对象之间，从而为客户和目标对象引入一定的间接性，正是这个间接性，给了代理对象很多的活动空间，代理对象可以在调用具体的目标对象前后，附加很多操作，从而实现新的功能或是扩展目标对象的功能，更狠的是，代理对象还可以不去创建和调用目标对象，也就是说，目标对象被完全代理掉了，或是被替换掉了。

从实现上看， **`代理模式主要是使用对象的组合和委托，尤其是在静态代理的实现里面，会看得更清楚`** 。但是也可以采用对象继承的方式来实现代理，这种实现方式在某些情况下，比使用对象组合还要来得简单。

* **`何时选用代理模式`** 


建议在如下情况中，选用代理模式：

 **`需要为一个对象在不同的地址空间提供局部代表的时候`** ，可以使用远程代理； **`需要按照需要创建开销很大的对象的时候`** ，可以使用虚代理； **`需要控制对原始对象的访问的时候`** ，可以使用保护代理； **`需要在访问对象的时候执行一些附加操作的时候`** ，可以使用智能指引代理；

## 3.6 相关模式##

* **`代理模式和适配器模式`** 


这两个模式有一定的相似性，但也有差异。 **`这两个模式有相似性，它们都为另一个对象提供间接性的访问，而且都是从自身以外的一个接口向这个对象转发请求。`** 

但是从功能上，两个模式是不一样的。 **`适配器模式主要用来解决接口之间不匹配的问题，它通常是为所适配的对象提供一个不同的接口；而代理模式会实现和目标对象相同的接口。`** 

* **`代理模式和装饰模式`** 


这两个模式从实现上相似，但是功能上是不同的。

装饰模式的实现和保护代理的实现上是类似的，都是在转调其它对象的前后执行一定的功能。但是它们的目的和功能都是不同的。

 **`装饰模式的目的是为了让你不生成子类就可以给对象添加职责，也就是为了动态的增加功能`** ；而 **`代理模式的主要目的是控制对对象的访问`** 。


[0]: ./img/2062729-bc4a3731be001163.png
[1]: ./img/2062729-2c65e3ad5fabe114.png
[2]: ./img/2062729-dfdfc83aabc3ee7f.png
[3]: ./img/2062729-b03898c7b200d7a2.png
[4]: ./img/2062729-f91e525c81350707.png