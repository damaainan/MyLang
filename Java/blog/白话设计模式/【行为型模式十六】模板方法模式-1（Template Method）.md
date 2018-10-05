## 【行为型模式十六】模板方法模式-1（Template Method）

2016.11.25 14:52*

来源：[https://www.jianshu.com/p/d393545b1309](https://www.jianshu.com/p/d393545b1309)


          
## 1 场景问题#
## 1.1 登录控制##

几乎所有的应用系统，都需要系统登录控制的功能，有些系统甚至有多个登录控制的功能，比如：普通用户可以登录前台，进行相应的业务操作；而工作人员可以登录后台，进行相应的系统管理或业务处理。

现在有这么一个基于Web的企业级应用系统，需要实现这两种登录控制，直接使用不同的登录页面来区分它们，把基本的功能需求分别描述如下： **`先看看普通用户登录前台的登录控制的功能：`** 

前台页面：用户能输入用户名和密码；提交登录请求，让系统去进行登录控制；

后台：从数据库获取登录人员的信息；

后台：判断从前台传递过来的登录数据，和数据库中已有的数据是否匹配；

前台Action：如果匹配就转向首页，如果不匹配就返回到登录页面，并显示错误提示信息；

 **`再来看看工作人员登录后台的登录控制功能：`** 

前台页面：用户能输入用户名和密码；提交登录请求，让系统去进行登录控制；

后台：从数据库获取登录人员的信息；

后台：把从前台传递过来的密码数据，使用相应的加密算法进行加密运算，得到加密后的密码数据；

后台：判断从前台传递过来的用户名和加密后的密码数据，和数据库中已有的数据是否匹配；

前台Action：如果匹配就转向首页，如果不匹配就返回到登录页面，并显示错误提示信息；

说明：普通用户和工作人员在数据库里面是存储在不同表里面的；当然也是不同的模块来维护普通用户的数据和工作人员的数据；另外工作人员的密码是加密存放的。
## 1.2 不用模式的解决方案##

由于普通用户登录和工作人员登录是不同的模块，有不同的页面，不同的逻辑处理，不同的数据存储，因此，在实现上完全当成两个独立的小模块去完成了。这里把它们的逻辑处理部分分别实现出来。

* **`先看普通用户登录的逻辑处理部分，示例代码如下：`** 


```java
/**
 * 普通用户登录控制的逻辑处理
 */
public class NormalLogin {
    /**
     * 判断登录数据是否正确，也就是是否能登录成功
     * @param lm 封装登录数据的Model
     * @return true表示登录成功，false表示登录失败
     */
    public boolean login(LoginModel lm) {
       //1：从数据库获取登录人员的信息，就是根据用户编号去获取人员的数据
       UserModel um = this.findUserByUserId(lm.getUserId());
       //2：判断从前台传递过来的登录数据，和数据库中已有的数据是否匹配
       //先判断用户是否存在，如果um为null，说明用户肯定不存在
       //但是不为null，用户不一定存在，因为数据层可能返回new UserModel();
       //因此还需要做进一步的判断
       if (um != null) {
           //如果用户存在，检查用户编号和密码是否匹配
           if (um.getUserId().equals(lm.getUserId()) && um.getPwd().equals(lm.getPwd())) {
              return true;
           }
       }
       return false;
    }
    /**
     * 根据用户编号获取用户的详细信息
     * @param userId 用户编号
     * @return 对应的用户的详细信息
     */
    private UserModel findUserByUserId(String userId) {
       // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
       UserModel um = new UserModel();
       um.setUserId(userId);
       um.setName("test");
       um.setPwd("test");
       um.setUuid("User0001");
       return um;
    }
}

```

对应的LoginModel，示例代码如下：

```java
/**
 * 描述登录人员登录时填写的信息的数据模型
 */
public class LoginModel {
    private String userId,pwd;
    public String getUserId() {
       return userId;
    }
    public void setUserId(String userId) {
       this.userId = userId;
    }
    public String getPwd() {
       return pwd;
    }
    public void setPwd(String pwd) {
       this.pwd = pwd;
    }
}

```

对应的UserModel，示例代码如下：

```java
/**
 * 描述用户信息的数据模型
 */
public class UserModel {
    private String uuid,userId,pwd,name;
    public String getUuid() {
       return uuid;
    }
    public void setUuid(String uuid) {
       this.uuid = uuid;
    }
    public String getUserId() {
       return userId;
    }
    public void setUserId(String userId) {
       this.userId = userId;
    }
    public String getPwd() {
       return pwd;
    }
    public void setPwd(String pwd) {
       this.pwd = pwd;
    }
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
}  

```

* **`再看看工作人员登录的逻辑处理部分，示例代码如下：`** 


```java
/**
 * 工作人员登录控制的逻辑处理
 */
public class WorkerLogin {
    /**
     * 判断登录数据是否正确，也就是是否能登录成功
     * @param lm 封装登录数据的Model
     * @return true表示登录成功，false表示登录失败
     */
    public boolean login(LoginModel lm) {
        //1：根据工作人员编号去获取工作人员的数据
        WorkerModel wm = findWorkerByWorkerId(lm.getWorkerId());
        //2：判断从前台传递过来的用户名和加密后的密码数据，
        //和数据库中已有的数据是否匹配
        //先判断工作人员是否存在，如果wm为null，说明工作人员肯定不存在
        //但是不为null，工作人员不一定存在，
        //因为数据层可能返回new WorkerModel();因此还需要做进一步的判断
        if (wm != null) {
            //3：把从前台传来的密码数据，使用相应的加密算法进行加密运算
            String encryptPwd = this.encryptPwd(lm.getPwd());
            //如果工作人员存在，检查工作人员编号和密码是否匹配
            if (wm.getWorkerId().equals(lm.getWorkerId()) && wm.getPwd().equals(encryptPwd)) {
                return true;
            }
        }
        return false;
    }
    /**
     * 对密码数据进行加密
     * @param pwd 密码数据
     * @return 加密后的密码数据
     */
    private String encryptPwd(String pwd){
        //这里对密码进行加密，省略了
        return pwd;
    }
    /**
     * 根据工作人员编号获取工作人员的详细信息
     * @param workerId 工作人员编号
     * @return 对应的工作人员的详细信息
     */
    private WorkerModel findWorkerByWorkerId(String workerId) {
        // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
        WorkerModel wm = new WorkerModel();
        wm.setWorkerId(workerId);
        wm.setName("Worker1");
        wm.setPwd("worker1");
        wm.setUuid("Worker0001");
        return wm;
    }
}

```

对应的LoginModel，示例代码如下：

```java
/**
 * 描述登录人员登录时填写的信息的数据模型
 */
public class LoginModel{
    private String workerId,pwd;
    public String getWorkerId() {
       return workerId;
    }
    public void setWorkerId(String workerId) {
       this.workerId = workerId;
    }
    public String getPwd() {
       return pwd;
    }
    public void setPwd(String pwd) {
       this.pwd = pwd;
    }
}

```

对应的WorkerModel，示例代码如下：

```java
/**
 * 描述工作人员信息的数据模型
 */
public class WorkerModel {
    private String uuid,workerId,pwd,name;
    public String getUuid() {
       return uuid;
    }
    public void setUuid(String uuid) {
       this.uuid = uuid;
    }
    public String getWorkerId() {
       return workerId;
    }
    public void setWorkerId(String workerId) {
       this.workerId = workerId;
    }
    public String getPwd() {
       return pwd;
    }
    public void setPwd(String pwd) {
       this.pwd = pwd;
    }
    public String getName() {
       return name;
    }
    public void setName(String name) {
       this.name = name;
    }
}

```
## 1.3 有何问题##

看了上面的实现示例，是不是很简单。但是，仔细看看，总会觉得有点问题，`两种登录的实现太相似了，现在是完全分开，当作两个独立的模块来实现的`，如果今后要扩展功能，比如要添加“控制同一个编号同时只能登录一次”的功能，那么两个模块都需要修改，是很麻烦的。`而且，现在的实现中，也有很多相似的地方，显得很重复`。另外，具体的实现和判断的步骤混合在一起，不利于今后变换功能，比如要变换加密算法等。

总之，上面的实现，`有两个很明显的问题：一是重复或相似代码太多；二是扩展起来很不方便`。

那么该怎么解决呢？该如何实现才能让系统既灵活又能简洁的实现需求功能呢？
## 2 解决方案#
## 2.1 模板方法模式来解决##

用来解决上述问题的一个合理的解决方案就是模板方法模式。那么什么是模板方法模式呢？

* **`模板方法模式定义`** 



![][0]


模板方法模式定义


* **`应用模板方法模式来解决的思路`** 


仔细分析上面的问题，`重复或相似代码太多、扩展不方便`，出现这些问题的原因在哪里？ **`主要就是两个实现是完全分开、相互独立的，没有从整体上进行控制。`** 如果把两个模块合起来看，就会发现，那些重复或相似的代码就应该被抽取出来，做成公共的功能，而不同的登录控制就可以去扩展这些公共的功能。这样一来，扩展的时候，如果出现有相同的功能，那就直接扩展公共功能就可以了。

使用模板方法模式，就可以很好的来实现上面的思路。分析上面两个登录控制模块，会发现它们在实现上，有着大致相同的步骤，只是在每步具体的实现上，略微有些不同，因此，可以把这些运算步骤看作是算法的骨架，把具体的不同的步骤实现，延迟到子类去实现，这样就可以通过子类来提供不同的功能实现了。

经过分析总结，登录控制大致的逻辑判断步骤如下：

根据登录人员的编号去获取相应的数据；

获取对登录人员填写的密码数据进行加密后的数据，如果不需要加密，那就是直接返回登录人员填写的密码数据；

判断登录人员填写的数据和从数据库中获取的数据是否匹配；

在这三个步骤里面，第一个和第三个步骤是必不可少的，而第二个步骤是可选的。 **`那么就可以定义一个父类，在里面定义一个方法来定义这个算法骨架，这个方法就是模板方法，然后把父类无法确定的实现，延迟到具体的子类来实现就可以了。`** 

通过这样的方式，如果要修改加密的算法，那就在模板的子类里面重新覆盖实现加密的方法就好了，完全不需要去改变父类的算法结构，就可以重新定义这些特定的步骤。
## 2.2 模式结构和说明##

模板方法模式的结构如图所示：


![][1]


模板方法模式的结构


 **`AbstractClass：抽象类。`** 用来定义算法骨架和原语操作，具体的子类通过重定义这些原语操作来实现一个算法的各个步骤。在这个类里面，还可以提供算法中通用的实现。 **`ConcreteClass：具体实现类。`** 用来实现算法骨架中的某些步骤，完成跟特定子类相关的功能。

## 2.3 模板方法模式示例代码##

* **`先来看看AbstractClass的写法，示例代码如下：`** 


```java
/**
 * 定义模板方法、原语操作等的抽象类
 */
public abstract class AbstractClass {
    /**
     * 原语操作1，所谓原语操作就是抽象的操作，必须要由子类提供实现
     */
    public abstract void doPrimitiveOperation1();
    /**
     * 原语操作2
     */
    public abstract void doPrimitiveOperation2();
    /**
     * 模板方法，定义算法骨架
     */
    public final void templateMethod() {
       doPrimitiveOperation1();
       doPrimitiveOperation2();
    }
}

```

* **`再看看具体实现类的写法，示例代码如下：`** 


```java
/**
 * 具体实现类，实现原语操作
 */
public class ConcreteClass extends AbstractClass {
    public void doPrimitiveOperation1() {
       //具体的实现
    }
    public void doPrimitiveOperation2() {
       //具体的实现
    }
}

```
## 2.4 使用模板方法模式重写示例##

要使用模板方法模式来实现前面的示例，按照模板方法模式的定义和结构，需要定义出一个抽象的父类，在这个父类里面定义模板方法，这个模板方法应该实现进行登录控制的整体的算法步骤。当然公共的功能，就放到这个父类去实现，而这个父类无法决定的功能，就延迟到子类去实现。

这样一来，两种登录控制就做为这个父类的子类，分别实现自己需要的功能。此时系统的结构如图所示：


![][2]


使用模板方法模式实现示例的结构示意图


* **`为了把原来的两种登录控制统一起来，首先需要把封装登录控制所需要的数据模型统一起来，不再区分是用户编号还是工作人员编号，而是统一称为登录人员的编号，还有把其它用不上的数据去掉，这样就直接使用一个数据模型就可以了。当然，如果各个子类实现需要其它的数据，还可以自行扩展。示例代码如下：`** 


```java
/**
 * 封装进行登录控制所需要的数据
 */
public class LoginModel {
    /**
     * 登录人员的编号，通用的，可能是用户编号，也可能是工作人员编号
     */
    private String loginId;
    /**
     * 登录的密码
     */
    private String pwd;
    public String getLoginId() {
        return loginId;
    }
    public void setLoginId(String loginId) {
        this.loginId = loginId;
    }
    public String getPwd() {
        return pwd;
    }
    public void setPwd(String pwd) {
        this.pwd = pwd;
    }  
}

```

* **`接下来定义公共的登录控制算法骨架，示例代码如下：`** 


```java
/**
 *  登录控制的模板
 */
public abstract class LoginTemplate {
    /**
     * 判断登录数据是否正确，也就是是否能登录成功
     * @param lm 封装登录数据的Model
     * @return true表示登录成功，false表示登录失败
     */
    public final boolean login(LoginModel lm){
        //1：根据登录人员的编号去获取相应的数据
        LoginModel dbLm = this.findLoginUser(lm.getLoginId());
        if(dbLm!=null){
            //2：对密码进行加密
            String encryptPwd = this.encryptPwd(lm.getPwd());
            //把加密后的密码设置回到登录数据模型里面
            lm.setPwd(encryptPwd);
            //3：判断是否匹配
            return this.match(lm, dbLm);
        }
        return false;
    }
    /**
     * 根据登录编号来查找和获取存储中相应的数据
     * @param loginId 登录编号
     * @return 登录编号在存储中相对应的数据
     */
    public abstract LoginModel findLoginUser(String loginId);
    /**
     * 对密码数据进行加密
     * @param pwd 密码数据
     * @return 加密后的密码数据
     */
    public String encryptPwd(String pwd){
       return pwd;
    }
    /**
     * 判断用户填写的登录数据和存储中对应的数据是否匹配得上
     * @param lm 用户填写的登录数据
     * @param dbLm 在存储中对应的数据
     * @return true表示匹配成功，false表示匹配失败
     */
    public boolean match(LoginModel lm,LoginModel dbLm){
        if(lm.getLoginId().equals(dbLm.getLoginId()) && lm.getPwd().equals(dbLm.getPwd())){
            return true;
        }
        return false;
    }
}

```

* **`实现新的普通用户登录控制的逻辑处理，示例代码如下：`** 


```java
/**
 * 普通用户登录控制的逻辑处理
 */
public class NormalLogin extends LoginTemplate{
    public LoginModel findLoginUser(String loginId) {
        // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
        LoginModel lm = new LoginModel();
        lm.setLoginId(loginId);
        lm.setPwd("testpwd");
        return lm;
    }
}

```

* **`实现新的工作人员登录控制的逻辑处理，示例代码如下：`** 


```java
/**
 * 工作人员登录控制的逻辑处理
 */
public class WorkerLogin extends LoginTemplate{
    public LoginModel findLoginUser(String loginId) {
        // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
        LoginModel lm = new LoginModel();
        lm.setLoginId(loginId);
        lm.setPwd("workerpwd");
        return lm;
    }

    public String encryptPwd(String pwd){
        //覆盖父类的方法，提供真正的加密实现
        //这里对密码进行加密，比如使用：MD5、3DES等等，省略了
        System.out.println("使用MD5进行密码加密");
        return pwd;
    }
}

```

* **`通过上面的示例，可以看出来，把原来的实现改成使用模板方法模式来实现，也并不困难，写个客户端测试一下，以便更好的体会，示例代码如下：`** 


```java
public class Client {
   public static void main(String[] args) {
       //准备登录人的信息
       LoginModel lm = new LoginModel();
       lm.setLoginId("admin");
       lm.setPwd("workerpwd");

       //准备用来进行判断的对象
       LoginTemplate lt = new WorkerLogin();
       LoginTemplate lt2 = new NormalLogin();

       //进行登录测试
       boolean flag = lt.login(lm);
       System.out.println("可以登录工作平台="+flag);
      
       boolean flag2 = lt2.login(lm);
       System.out.println("可以进行普通人员登录="+flag2);
   }
}

```

运行结果示例如下：

```java
使用MD5进行密码加密
可以登录工作平台=true
可以进行普通人员登录=false

```
## 3 模式讲解#
## 3.1 认识模板方法模式##

* **`模式的功能`** 


 **`模板方法的功能在于固定算法骨架，而让具体算法实现可扩展。`** 

这在实际应用中非常广泛，尤其是在设计框架级功能的时候非常有用。 **`框架定义好了算法的步骤，在合适的点让开发人员进行扩展，实现具体的算法。`** 比如在DAO实现中，设计通用的增删改查功能，这个后面会给大家示例。 **`模板方法还额外提供了一个好处，就是可以控制子类的扩展。`** 因为在父类里面定义好了算法的步骤，`只是在某几个固定的点才会调用到被子类实现的方法，因此也就只允许在这几个点来扩展功能，这些个可以被子类覆盖以扩展功能的方法通常被称为“钩子”方法`，后面也会给大家示例。

* **`为何不是接口`** 


有的朋友可能会问一个问题，不是说在Java中应该尽量面向接口编程吗，为何模板方法的模板是采用的抽象方法呢？

要回答这个问题，要首先搞清楚抽象类和接口的关系：

接口是一种特殊的抽象类，所有接口中的属性自动是常量，也就是public final static的，而所有接口中的方法必须是抽象的；

抽象类，简单点说是用abstract修饰的类。这里要特别注意的是抽象类和抽象方法的关系，记住两句话：`抽象类不一定包含抽象方法；有抽象方法的类一定是抽象类`；

抽象类和接口相比较， **`最大的特点就在于抽象类里面是可以有具体的实现方法的，而接口中所有的方法都是没有具体的实现的`** ；

因此，虽然Java编程中倡导大家“面向接口编程”，并不是说就不再使用抽象类了，那么什么时候使用抽象类呢？

通常在 **`“既要约束子类的行为，又要为子类提供公共功能”`** 的时候使用抽象类；

按照这个原则来思考模板方法模式的实现， **`模板方法模式需要固定定义算法的骨架，这个骨架应该只有一份，算是一个公共的行为`** ，但是里面具体的步骤的实现又可能是各不相同的，恰好符合选择抽象类的原则。

把模板实现成为抽象类， **`为所有的子类提供了公共的功能`** ，就是定义了具体的算法骨架；同时在模板里面把需要由子类扩展的具体步骤的算法定义成为抽象方法， **`要求子类去实现这些方法`** ，这就约束了子类的行为。

因此综合考虑，用抽象类来实现模板是一个很好的选择。

* **`变与不变`** 

 **`程序设计的一个很重要的思考点就是“变与不变”，`** 也就是分析程序中哪些功能是可变的，哪些功能是不变的，然后把不变的部分抽象出来，进行公共的实现，把变化的部分分离出去，用接口来封装隔离，或者是用抽象类来约束子类行为。

模板方法模式很好的体现了这一点。 **`模板类实现的就是不变的方法和算法的骨架，而需要变化的地方，都通过抽象方法，把具体实现延迟到子类去了，而且还通过父类的定义来约束了子类的行为，从而使系统能有更好的复用性和扩展性。`** 

* **`好莱坞法则`** 


什么是好莱坞法则呢？简单点说，就是`“不要找我们，我们会联系你”`。

模板方法模式很好的体现了这一点， **`做为父类的模板会在需要的时候，调用子类相应的方法，也就是由父类来找子类，而不是让子类来找父类`** 。

这其实也是一种反向的控制结构，按照通常的思路，是子类找父类才对，也就是应该是子类来调用父类的方法，因为父类根本就不知道子类，而子类是知道父类的，但是在模板方法模式里面，是父类来找子类，所以是一种反向的控制结构。

那么，在Java里面能实现这样功能的理论依据在哪里呢？

理论依据就在于`Java的动态绑定采用的是“后期绑定”技术`，对于出现子类覆盖父类方法的情况，`在编译时是看数据类型，运行时看实际的对象类型（new操作符后跟的构造方法是哪个类的）`，一句话：new谁就调用谁的方法。

因此在使用模板方法模式的时候，虽然用的数据类型是模板类型，但是在创建类实例的时候是创建的具体的子类的实例，因此调用的时候，会被动态绑定到子类的方法上去，从而实现反向控制。 **`其实在写父类的时候，它调用的方法是父类自己的抽象方法，只是在运行的时候被动态绑定到了子类的方法上。`** 

* **`扩展登录控制`** 


在使用模板方法模式实现过后，如果想要扩展新的功能，有如下几种情况：

一种情况是只需要提供新的子类实现就可以了，比如想要切换不同的加密算法，现在是使用的MD5，想要实现使用3DES的加密算法，那就新做一个子类，然后覆盖实现父类加密的方法，在里面使用3DES来实现即可，已有的实现不需要做任何变化。

另外一种情况是想要给两个登录模块都扩展同一个功能，这种情况多属于需要修改模板方法的算法骨架的情况，应该尽量避免，但是万一前面没有考虑周全，后来出现了这种情况，怎么办呢？`最好就是重构，也就是考虑修改算法骨架，尽量不要去找其它的替代方式，替代的方式也许能把功能实现了，但是会破坏整个程序的结构`。

还有一种情况是既需要加入新的功能，也需要新的数据。比如：现在对于普通人员登录，要实现一个加强版，要求登录人员除了编号和密码外，还需要提供注册时留下的验证问题和验证答案，验证问题和验证答案是记录在数据库中的，不是验证码，一般Web开发中登录使用的验证码会放到session中，这里不去讨论它。

假如进行最后一种情况的扩展，应该怎么实现呢？由于需要一些其它的数据，那么就需要扩展LoginModel，加入自己需要的数据；同时可能需要覆盖由父类提供的一些公共的方法，来实现新的功能。

还是看看代码示例吧，会比较清楚。 **`首先呢，需要扩展LoginModel，把具体功能需要的数据封装起来，只是增加父类没有的数据就可以了，示例代码如下：`** 

```java
/**
 * 封装进行登录控制所需要的数据，在公共数据的基础上，
 * 添加具体模块需要的数据
 */
public class NormalLoginModel extends LoginModel{
    /**
     * 密码验证问题
     */
    private String question;
    /**
     * 密码验证答案
     */
    private String answer;
    public String getQuestion() {
        return question;
    }
    public void setQuestion(String question) {
        this.question = question;
    }
    public String getAnswer() {
        return answer;
    }
    public void setAnswer(String answer) {
       this.answer = answer;
    }
}

``` **`其次呢，就是提供新的登录模块控制实现，示例代码如下：`** 

```java
/**
 * 普通用户登录控制加强版的逻辑处理
 */
public class NormalLogin2 extends LoginTemplate{
    public LoginModel findLoginUser(String loginId) {
        // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
        //注意一点：这里使用的是自己需要的数据模型了
        NormalLoginModel nlm = new NormalLoginModel();
        nlm.setLoginId(loginId);
        nlm.setPwd("testpwd");
        nlm.setQuestion("testQuestion");
        nlm.setAnswer("testAnswer");
     
        return nlm;
    }
    public boolean match(LoginModel lm,LoginModel dbLm){
        //这个方法需要覆盖，因为现在进行登录控制的时候，
        //需要检测4个值是否正确，而不仅仅是缺省的2个
     
        //先调用父类实现好的，检测编号和密码是否正确
        boolean f1 = super.match(lm, dbLm);
        if(f1){
            //如果编号和密码正确，继续检查问题和答案是否正确
         
            //先把数据转换成自己需要的数据
            NormalLoginModel nlm = (NormalLoginModel)lm;
            NormalLoginModel dbNlm = (NormalLoginModel)dbLm;
            //检查问题和答案是否正确
            if(dbNlm.getQuestion().equals(nlm.getQuestion()) && dbNlm.getAnswer().equals(nlm.getAnswer())){
                return true;
            }
        }
        return false;
    }
}

``` **`看看这个时候的测试，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
        //准备登录人的信息
        NormalLoginModel nlm = new NormalLoginModel();
        nlm.setLoginId("testUser");
        nlm.setPwd("testpwd");
        nlm.setQuestion("testQuestion");
        nlm.setAnswer("testAnswer");
        //准备用来进行判断的对象
        LoginTemplate lt3 = new NormalLogin2();
        //进行登录测试
        boolean flag3 = lt3.login(nlm);
        System.out.println("可以进行普通人员加强版登录="+flag3);
    }
}

```

运行看看，能实现功能吗？好好测试体会一下，看看是如何扩展功能的。
## 3.2 模板的写法##

在实现模板的时候，到底哪些方法实现在模板上呢？模板能不能全部实现了，也就是模板不提供抽象方法呢？当然，`就算没有抽象方法，模板一样可以定义成为抽象类`。

通常在模板里面包含如下操作类型：

 **`模板方法`** ：就是定义算法骨架的方法 。 **`具体的操作`** ：`在模板中直接实现某些步骤的方法，通常这些步骤的实现算法是固定的，而且是不怎么变化的，因此就可以当作公共功能实现在模板里面`。`如果不需提供给子类访问这些方法的话，还可以是private的`。这样一来，子类的实现就相对简单些。`如果是子类需要访问，可以把这些方法定义为protected final的`，因为通常情况下，这些实现不能够被子类覆盖和改变了。 **`具体的AbstractClass操作`** ：在模板中实现某些公共功能，可以提供给子类使用，一般不是具体的算法步骤的实现，只是一些辅助的公共功能。 **`原语操作`** ：`就是在模板中定义的抽象操作，通常是模板方法需要调用的操作，是必需的操作`，而且在父类中还没有办法确定下来如何实现，需要子类来真正实现的方法。 **`钩子操作`** ：`在模板中定义，并提供默认实现的操作`。这些方法通常被视为可扩展的点，但不是必须的，子类可以有选择的覆盖这些方法，以提供新的实现来扩展功能。比如：模板方法中定义了5步操作，但是根据需要，某一种具体的实现只需要其中的1、2、3这几个步骤，因此它就只需要覆盖实现1、2、3这几个步骤对应的方法。那么4和5步骤对应的方法怎么办呢，由于有默认实现，那就不用管了。`也就是说钩子操作是可以被扩展的点，但不是必须的`。

Factory Method：在模板方法中，`如果需要得到某些对象实例的话，可以考虑通过工厂方法模式来获取，把具体的构建对象的实现延迟到子类中去`。

 **`总结起来，一个较为完整的模板定义示例，示例代码如下：`** 

```java
/**
 * 一个较为完整的模版定义示例
 */
public abstract class AbstractTemplate {
    /**
     * 模板方法，定义算法骨架
     */
    public final void templateMethod(){
        //第一步
        this.operation1();
        //第二步      
        this.operation2();
        //第三步
        this.doPrimitiveOperation1();
        //第四步
        this.doPrimitiveOperation2();
        //第五步
        this.hookOperation1();
    }
    /**
     * 具体操作1，算法中的步骤，固定实现，而且子类不需要访问
     */
    private void operation1(){
        //在这里具体的实现
    }
    /**
     * 具体操作2，算法中的步骤，固定实现，子类可能需要访问，
     * 当然也可以定义成protected的，不可以被覆盖，因此是final的
     */
    protected final void operation2(){
        //在这里具体的实现
    }
    /**
     * 具体的AbstractClass操作，子类的公共功能，
     * 但通常不是具体的算法步骤
     */
    protected void commonOperation(){
         //在这里具体的实现
    }
    /**
     * 原语操作1，算法中的必要步骤，父类无法确定如何真正实现，需要子类来实现
     */
    protected abstract void doPrimitiveOperation1();
    /**
     * 原语操作2，算法中的必要步骤，父类无法确定如何真正实现，需要子类来实现
     */
    protected abstract void doPrimitiveOperation2();
    /**
     * 钩子操作，算法中的步骤，不一定需要，提供缺省实现
     * 由子类选择并具体实现
     */
    protected void hookOperation1(){
        //在这里提供缺省的实现
    }
    /**
     * 工厂方法，创建某个对象，这里用Object代替了，在算法实现中可能需要
     * @return 创建的某个算法实现需要的对象
     */
    protected abstract Object createOneObject();
}

```

对于上面示例的模板写法，其中定义成为protected的方法，可以根据需要进行调整，如果是允许所有的类都可以访问这些方法，那么可以把它们定义成为public的，如果只是子类需要访问这些方法，那就使用protected的，都是正确的写法。
## 3.3 Java回调与模板方法模式## **`模板方法模式的一个目的，就在于让其它类来扩展或具体实现在模板中固定的算法骨架中的某些算法步骤。`** 在标准的模板方法模式实现中，主要是使用继承的方式，来让父类在运行期间可以调用到子类的方法。

其实在Java开发中，还有另外一个方法可以实现同样的功能或是效果， **`那就是——Java回调技术，通过回调在接口中定义的方法，调用到具体的实现类中的方法，其本质同样是利用Java的动态绑定技术，在这种实现中，可以不把实现类写成单独的类，而是使用匿名内部类来实现回调方法`** 。

应用Java回调来实现模板方法模式，在实际开发中使用得也非常多，就算是模板方法模式的一种变形实现吧。

还是来示例一下，这样会更清楚。为了大家好对比理解，把前面用标准模板方法模式实现的例子，采用Java回调来实现一下。

* **`先定义一个模板方法需要的回调接口`** 

`在这个接口中需要把所有可以被扩展的方法都要定义出来`。实现的时候，可以不扩展，直接转调模板中的默认实现，但是不能不定义出来，因为是接口，不定义出来，对于想要扩展这些功能的地方就没有办法了。示例代码如下：

```java
/**
 * 登录控制的模板方法需要的回调接口，需要把所有需要的接口方法都定义出来,
 * 或者说是所有可以被扩展的方法都需要被定义出来
 */
public interface LoginCallback {
    /**
     * 根据登录编号来查找和获取存储中相应的数据
     * @param loginId 登录编号
     * @return 登录编号在存储中相对应的数据
     */
    public LoginModel findLoginUser(String loginId);
    /**
     * 对密码数据进行加密
     * @param pwd 密码数据
     * @param template LoginTemplate对象，通过它来调用在
     *             LoginTemplate中定义的公共方法或缺省实现
     * @return 加密后的密码数据
     */
    public String encryptPwd(String pwd,LoginTemplate template);
    /**
     * 判断用户填写的登录数据和存储中对应的数据是否匹配得上
     * @param lm 用户填写的登录数据
     * @param dbLm 在存储中对应的数据
     * @param template LoginTemplate对象，通过它来调用在
     *             LoginTemplate中定义的公共方法或缺省实现
     * @return true表示匹配成功，false表示匹配失败
     */
    public boolean match(LoginModel lm, LoginModel dbLm, LoginTemplate template);
}

```

* **`这里使用的LoginModel跟以前没有任何变化，就不去赘述了。`** 

* **`该来定义登录控制的模板了，它的变化相对较多，大致有以下一些：`** 


不再是抽象的类了，所有的抽象方法都去掉了；

对模板方法就是login的那个方法，添加一个参数，传入回调接口；

在模板方法实现中，除了在模板中固定的实现外，所有可以被扩展的方法，都应该通过回调接口进行调用；

示例代码如下：

```java
/**
 *  登录控制的模板
 */
public class LoginTemplate {
    /**
     * 判断登录数据是否正确，也就是是否能登录成功
     * @param lm 封装登录数据的Model
     * @param callback LoginCallback对象
     * @return true表示登录成功，false表示登录失败
     */
    public final boolean login(LoginModel lm,LoginCallback callback){
        //1：根据登录人员的编号去获取相应的数据
        LoginModel dbLm = callback.findLoginUser(lm.getLoginId());
        if(dbLm!=null){
            //2：对密码进行加密
            String encryptPwd = callback.encryptPwd(lm.getPwd(),this);
            //把加密后的密码设置回到登录数据模型里面
            lm.setPwd(encryptPwd);
            //3：判断是否匹配
            return callback.match(lm, dbLm,this);
        }
        return false;
    }
    /**
     * 对密码数据进行加密
     * @param pwd 密码数据
     * @return 加密后的密码数据
     */
    public String encryptPwd(String pwd){
        return pwd;
    }
    /**
     * 判断用户填写的登录数据和存储中对应的数据是否匹配得上
     * @param lm 用户填写的登录数据
     * @param dbLm 在存储中对应的数据
     * @return true表示匹配成功，false表示匹配失败
     */
    public boolean match(LoginModel lm,LoginModel dbLm){
        if(lm.getLoginId().equals(dbLm.getLoginId()) && lm.getPwd().equals(dbLm.getPwd())){
            return true;
        }
        return false;
    }
}

```

* **`由于是直接在调用的地方传入回调的实现，`通常可以通过匿名内部类的方式来实现回调接口`，当然实现成为具体类也是可以的。如果采用匿名内部类的方式来使用模板，那么就不需要原来的NormalLogin和WorkerLogin了。`** 

* **`写个客户端来测试看看，客户端需要使用匿名内部类来实现回调接口，并实现其中想要扩展的方法，示例代码如下：`** 

```java
public class Client {
    public static void main(String[] args) {
        //准备登录人的信息
        LoginModel lm = new LoginModel();
        lm.setLoginId("admin");
        lm.setPwd("workerpwd");
        //准备用来进行判断的对象
        LoginTemplate lt = new LoginTemplate();
     
        //进行登录测试，先测试普通人员登录
        boolean flag = lt.login(lm,new LoginCallback(){
            public String encryptPwd(String pwd, LoginTemplate template) {
                //自己不需要，直接转调模板中的默认实现
                return template.encryptPwd(pwd);
            }
            public LoginModel findLoginUser(String loginId) {
                // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
                LoginModel lm = new LoginModel();
                lm.setLoginId(loginId);
                lm.setPwd("testpwd");
                return lm;
            }
            public boolean match(LoginModel lm, LoginModel dbLm, LoginTemplate template) {
                //自己不需要覆盖，直接转调模板中的默认实现
                return template.match(lm, dbLm);
            }
        });
        System.out.println("可以进行普通人员登录="+flag);
     
        //测试工作人员登录
        boolean flag2 = lt.login(lm,new LoginCallback(){
            public String encryptPwd(String pwd, LoginTemplate template) {
                //覆盖父类的方法，提供真正的加密实现
                //这里对密码进行加密，比如使用：MD5、3DES等等，省略了
                System.out.println("使用MD5进行密码加密");
                return pwd;
            }
            public LoginModel findLoginUser(String loginId) {
                // 这里省略具体的处理，仅做示意，返回一个有默认数据的对象
                LoginModel lm = new LoginModel();
                lm.setLoginId(loginId);
                lm.setPwd("workerpwd");
                return lm;
            }
            public boolean match(LoginModel lm, LoginModel dbLm, LoginTemplate template) {
                //自己不需要覆盖，直接转调模板中的默认实现
                return template.match(lm, dbLm);
            }         
        });   
        System.out.println("可以登录工作平台="+flag2);
    }
}

```

运行一下，看看效果是不是跟前面采用继承的方式实现的结果是一样的，然后好好比较一下这两种实现方式。

* **`简单小结一下，对于模板方法模式的这两种实现方式：`** 



* 使用继承的方式，抽象方法和具体实现的关系， **`是在编译期间静态决定的，是类级的关系；`** 
* 使用Java回调， **`这个关系是在运行期间动态决定的，是对象级的关系。`** 


相对而言，使用回调机制会更灵活，因为Java是单继承的，如果使用继承的方式，对于子类而言，今后就不能继承其它对象了，而使用回调，是基于接口的。 **`从另一方面说，回调机制是通过委托的方式来组合功能，它的耦合强度要比继承低一些，这会给我们更多的灵活性。`** 比如某些模板实现的方法，在回调实现的时候可以不调用模板中的方法，而是调用其它实现中的某些功能，也就是说功能不再局限在模板和回调实现上了，可以更灵活组织功能。 **`相对而言，使用继承方式会更简单点，因为父类提供了实现的方法，子类如果不想扩展，那就不用管。`** 如果使用回调机制，回调的接口需要把所有可能被扩展的方法都定义进去，这就导致实现的时候，不管你要不要扩展，你都要实现这个方法，哪怕你什么都不做，只是转调模板中已有的实现，都要写出来。

事实上，在前面讲命令模式的时候也提到了Java回调，还通过退化命令模式来实现了Java回调的功能，所以也有这样的说法： **`命令模式可以作为模板方法模式的一种替代实现，那就是因为可以使用Java回调来实现模板方法模式`** 。


[0]: ./img/2062729-e4c30a20594c9e4f.png
[1]: ./img/2062729-06057e6545314d07.png
[2]: ./img/2062729-5bfd20239d0d1cb3.png