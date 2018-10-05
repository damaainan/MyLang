## 【行为型模式十六】模板方法模式-2（Template Method）

2016.11.25 15:01*

来源：[https://www.jianshu.com/p/0f19ba5860d3](https://www.jianshu.com/p/0f19ba5860d3)


          
## 3.4 典型应用：排序##

模板方法模式的一个非常典型的应用，就是实现排序的功能。至于有些朋友认为排序是策略模式的体现，这很值得商榷。先来看看在Java中排序功能的实现，然后再来说明为什么排序的实现主要体现了模板方法模式，而非策略模式。

在java.util包中，有一个Collections类，它里面实现了对列表排序的功能，它提供了一个静态的sort方法，接受一个列表和一个Comparator接口的实例，这个方法实现的大致步骤是：

先把列表转换成为对象数组；

通过Arrays的sort方法来对数组进行排序，传入Comparator接口的实例；

然后再把排好序的数组的数据设置回到原来的列表对象中去；

这其中的算法步骤是固定的，也就是算法骨架是固定的了，只是其中具体比较数据大小的步骤，需要由外部来提供，也就是传入的Comparator接口的实例，就是用来实现数据比较的，在算法内部会通过这个接口来回调具体的实现。

如果Comparator接口的compare()方法返回一个小于0的数，表示被比较的两个对象中，前面的对象小于后面的对象；如果返回一个等于0的数，表示被比较的两个对象相等；如果

返回一个大于0的数，表示被比较的两个对象中，前面的对象大于后面的对象。

下面一起看看使用Collections来对列表排序的例子，假如现在要实现对一个拥有多个用户数据模型的列表进行排序。

* **`当然，先要定义出封装用户数据的对象模型来，示例代码如下：`** 


```java
/**
 * 用户数据模型
 */
public class UserModel {
    private String userId,name;
    private int age;
    public UserModel(String userId,String name,int age) {
        this.userId = userId;
        this.name = name;
        this.age = age;
    }
    public String getUserId() {
        return userId;
    }
    public String getName() {
        return name;
    }
    public int getAge() {
        return age;
    }
    public String toString(){
        return "userId="+userId+",name="+name+",age="+age;
    }
}

```

* **`直接使用Collections来排序，写个客户端来测试一下，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
        //准备要测试的数据
        UserModel um1 = new UserModel("u1","user1",23);
        UserModel um2 = new UserModel("u2","user2",22);
        UserModel um3 = new UserModel("u3","user3",21);
        UserModel um4 = new UserModel("u4","user4",24);
        //添加到列表中
        List<UserModel> list = new ArrayList<UserModel>();
        list.add(um1);
        list.add(um2);
        list.add(um3);
        list.add(um4);
     
        System.out.println("排序前---------------------〉");
        printList(list);
        //实现比较器，也可以单独用一个类来实现
        Comparator c = new Comparator(){
            public int compare(Object obj1, Object obj2) {
                //假如实现按照年龄升序排序
                UserModel tempUm1 = (UserModel)obj1;
                UserModel tempUm2 = (UserModel)obj2;
                if(tempUm1.getAge() > tempUm2.getAge()){
                    return 1;
                }else if(tempUm1.getAge() == tempUm2.getAge()){
                    return 0;
                }else if(tempUm1.getAge() < tempUm2.getAge()){
                    return -1;
                }
                return 0;
            }
        };
     
        //排序 
        Collections.sort(list,c);
     
        System.out.println("排序后---------------------〉");
        printList(list);
    }
    private static void printList(List<UserModel> list){
        for(UserModel um : list){
            System.out.println(um);
        }
    }
}

```

运行一下，结果如下所示：

```java
排序前---------------------〉
userId=u1,name=user1,age=23
userId=u2,name=user2,age=22
userId=u3,name=user3,age=21
userId=u4,name=user4,age=24
排序后---------------------〉
userId=u3,name=user3,age=21
userId=u2,name=user2,age=22
userId=u1,name=user1,age=23
userId=u4,name=user4,age=24

```

* **`小结一下`** 


看了上面的示例，你会发现，`究竟列表会按照什么标准来排序，完全是依靠Comparator的具体实现`，上面实现的是按照年龄升序排列，你可以尝试修改这个排序的比较器，那么得到的结果就会不一样了。

也就是说，`排序的算法是已经固定了的，只是进行排序比较的这一个步骤，由外部来实现，我们就可以通过修改这个步骤的实现，从而实现不同的排序方式`。因此从排序比较这个功能来看，是策略模式的体现。

但是请注意一点，`你只是修改的排序的比较方式，并不是修改了整个排序的算法`，事实上，现在Collections的sort()方法使用的是合并排序的算法，无论你怎么修改比较器的实现，sort()方法实现的算法是不会改变的，不可能变成了冒泡排序或是其它的排序算法。

* **`排序，到底是模板方法模式的实例，还是策略模式的实例，到底哪个说法更合适？`** 

 **`认为是策略模式的实例的理由：`** 

首先上面的排序实现，并没有如同标准的模板方法模式那样，使用子类来扩展父类，至少从表面上看不太像模板方法模式；

其次排序使用的Comparator的实例，可以看成是不同的算法实现，在具体排序时，会选择使用不同的Comparator实现，就相当于是在切换算法的实现。

因此认为排序是策略模式的实例。 **`认为是模板方法模式的实例的理由：`** 

首先，模板方法模式的本质是固定算法骨架，虽然使用继承是标准的实现方式，但是通过回调来实现，也不能说这就不是模板方法模式；

其次，从整体程序上看，排序的算法并没有改变，不过是某些步骤的实现发生了变化，也就是说通过Comparator来切换的是不同的比较大小的实现，相对于整个排序算法而言，它不过是其中的一个步骤而已。

因此认为是模板方法模式的实例。

* **`总结语：`** 

`排序的实现，实际上组合使用了模板方法模式和策略模式，从整体来看是模板方法模式，但到了局部，比如排序比较算法的实现上，就是使用的策略模式了。`至于排序具体属于谁的实例，这或许是个仁者见仁、智者见智的事情，我们也不想做老好人，我们倾向于说：`排序是模板方法模式的实例`。毕竟设计模式的东西，`要从整体上、设计上、从本质上去看待问题，而不能从表面上或者是局部来看待问题`。
## 3.5 实现通用增删改查##

对于实现通用的增删改查的功能，基本上是每个做企业级应用系统的公司都有的功能，实现的方式也是多种多样，`一种很常见的设计就是泛型加上模板方法模式，再加上使用Java回调技术，尤其是在使用Spring和Hibernate等流行框架的应用系统中很是常见`。

为了突出主题，以免分散大家的注意力，我们不去使用Spring和Hibernate这样的流行框架，也不去使用泛型，只用模板方法模式来实现一个简单的、用JDBC实现的通用增删改查的功能。

先在数据库中定义一个演示用的表，演示用的是Oracle数据库，其实你可以用任意的数据库，只是数据类型要做相应的调整，简单的数据字典如下：表名是tbl_user


![][0]


Paste_Image.png


* **`定义相应的数据对象来描述数据，示例代码如下：`** 


```java
/**
 * 描述用户的数据模型
 */
public class UserModel {
    private String uuid;
    private String name;
    private int age;
    public String getUuid() {
        return uuid;
    }
    public void setUuid(String uuid) {
        this.uuid = uuid;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }  
    public String toString(){
        return "uuid="+uuid+",name="+name+",age="+age;
    }
}

```

* **`定义一个`用于封装通用查询数据的查询用的数据模型`，由于这个查询数据模型和上面定义的数据模型有很大一部分是相同的，因此让这个查询模型继承上面的数据模型，然后添加上多出来的查询条件。示例代码如下：`** 


```java
/**
 * 描述查询用户的条件数据的模型
 */
public class UserQueryModel extends UserModel{
    /**
     * 年龄是一个区间查询，也就是年龄查询的条件可以是：
     * age >= 条件值1  and  age <= 条件值2
     * 把UserModel中的age当作条件值1，
     * 这里定义的age2当作条件值2
     */
    private int age2;
    public int getAge2() {
        return age2;
    }
    public void setAge2(int age2) {
        this.age2 = age2;
    }
}

```

* **`为了让大家能更好的理解这个通用的实现，先不去使用模板方法模式，直接使用JDBC来实现增删改查的功能。`** 

 **`所有的方法都需要和数据库进行连接，因此先把和数据库连接的公共方法定义出来，没有使用连接池，用最简单的JDBC自己连接，示例代码如下：`** 

```java
/**
 * 获取与数据库的连接
 * @return 数据库连接
 * @throws Exception
 */
private Connection getConnection()throws Exception{
    Class.forName("你用的数据库对应的JDBC驱动类");
    return DriverManager.getConnection(
             "连接数据库的URL",
             "用户名","密码");
}

``` **`使用纯JDBC来实现新增的功能，示例代码如下：`** 

```java
public void create(UserModel um) {
    Connection conn = null;
    try {
        conn = this.getConnection();
        String sql = "insert into tbl_user values(?,?,?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, um.getUuid());
        pstmt.setString(2, um.getName());
        pstmt.setInt(3, um.getAge());

        pstmt.executeUpdate();

        pstmt.close();
    } catch (Exception err) {
        err.printStackTrace();
    } finally {
        try {
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

```

修改和删除的功能跟新增差不多，只是sql不同，还有设置sql中变量值不同，这里就不去写了。 **`接下来看看查询方面的功能，查询方面只做一个通用的查询实现，其它查询的实现基本上也差不多，示例代码如下：`** 

```java
public Collection getByCondition(UserQueryModel uqm){
    Collection col = new ArrayList();
    Connection conn = null;
    try{
        conn = this.getConnection();
        String sql = "select * from tbl_user where 1=1 ";
        sql = this.prepareSql(sql, uqm);

        PreparedStatement pstmt = conn.prepareStatement(sql);
        this.setValue(pstmt, uqm);
        ResultSet rs = pstmt.executeQuery();
        while(rs.next()){
            col.add(this.rs2Object(rs));
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
    return col;
}

/**
 * 为通用查询动态的拼接sql的条件部分，基本思路是：
 * 如果用户填写了相应的条件，那么才在sql中添加对应的条件
 * @param sql sql的主干部分
 * @param uqm 封装查询条件的数据模型
 * @return 拼接好的sql语句
 */
private String prepareSql(String sql,UserQueryModel uqm){
    StringBuffer buffer = new StringBuffer();
    buffer.append(sql);
    //绝对匹配
    if(uqm.getUuid()!=null&& uqm.getUuid().trim().length()>0){
        buffer.append(" and uuid=? ");
    }
    //模糊匹配
    if(uqm.getName()!=null&& uqm.getName().trim().length()>0){
        buffer.append(" and name like ? ");
    }
    //区间匹配
    if(uqm.getAge() > 0){
        buffer.append(" and age >=? ");
    }
    if(uqm.getAge2() > 0){
        buffer.append(" and age <=? ");
    }
    return buffer.toString();
}

/**
 * 为通用查询的sql动态设置条件的值
 * @param pstmt 预处理查询sql的对象
 * @param uqm 封装查询条件的数据模型
 * @throws Exception
 */
private void setValue(PreparedStatement pstmt,UserQueryModel uqm)throws Exception{
    int count = 1;
    if(uqm.getUuid()!=null && uqm.getUuid().trim().length()>0){
        pstmt.setString(count, uqm.getUuid());
        count++;
    }
    if(uqm.getName()!=null && uqm.getName().trim().length()>0){
        pstmt.setString(count, "%"+uqm.getName()+"%");
        count++;
    }
    if(uqm.getAge() > 0){
        pstmt.setInt(count, uqm.getAge());
        count++;
    }
    if(uqm.getAge2() > 0){
        pstmt.setInt(count, uqm.getAge2());
        count++;
    }
}

/**
 * 把查询返回的结果集转换成为对象
 * @param rs 查询返回的结果集
 * @return 查询返回的结果集转换成为对象
 * @throws Exception
 */
private UserModel rs2Object(ResultSet rs)throws Exception{
    UserModel um = new UserModel();
    String uuid = rs.getString("uuid");
    String name = rs.getString("name");
    int age = rs.getInt("age");
     
    um.setAge(age);
    um.setName(name);
    um.setUuid(uuid);
     
    return um;
}

```

* **`基本的JDBC实现写完了，该来看看如何把模板方法模式用上了。`模板方法是要定义算法的骨架，而具体步骤的实现还是由子类来完成，因此把固定的算法骨架抽取出来，就成了使用模板方法模式的重点了`。`** 


首先来观察新增、修改、删除的功能，发现哪些是固定的，哪些是变化的呢？分析发现变化的只有Sql语句，还有为Sql中的“？”设置值的语句，真正执行sql的过程是差不多的，是不变化的。

再来观察查询的方法，查询的过程是固定的，变化的除了有Sql语句、为Sql中的“？”设置值的语句之外，还多了一个如何把查询回来的结果集转换成对象集的实现。

好了，`找到变与不变之处，就可以来设计模板了，先定义出增删改查各自的实现步骤来`，也就是`定义好各自的算法骨架，然后把变化的部分定义成为原语操作或钩子操作`，`如果一定要子类实现的那就定义成为原语操作；在模板中提供默认实现，且不强制子类实现的功能定义成为钩子操作就可以了`。

另外，来回需要传递数据，由于是通用的方法，就不能用具体的类型了，又不考虑泛型，那么就定义成Object类型好了。

根据上面的思路，一个简单的、能实现对数据进行增删改查的模板就可以实现出来了，完整的示例代码如下：

```java
/**
 * 一个简单的实现JDBC增删改查功能的模板
 */
public abstract class JDBCTemplate {
    /**
     * 定义当前的操作类型是新增
     */
    protected final static int TYPE_CREATE = 1;
    /**
     * 定义当前的操作类型是修改
     */
    protected final static int TYPE_UPDATE = 2;
    /**
     * 定义当前的操作类型是删除
     */
    protected final static int TYPE_DELETE = 3;
    /**
     * 定义当前的操作类型是按条件查询
     */
    protected final static int TYPE_CONDITION = 4;
  
    /*---------------------模板方法---------------------*/  
    /**
     * 实现新增的功能
     * @param obj 需要被新增的数据对象
     */
    public final void create(Object obj){
       //1：获取新增的sql
       String sql = this.getMainSql(TYPE_CREATE);
       //2：调用通用的更新实现
       this.executeUpdate(sql, TYPE_CREATE,obj);
    }
    /**
     * 实现修改的功能
     * @param obj 需要被修改的数据对象
     */
    public final void update(Object obj){
       //1：获取修改的sql
       String sql = this.getMainSql(TYPE_UPDATE);
       //2：调用通用的更新实现
       this.executeUpdate(sql, TYPE_UPDATE,obj);
    }
    /**
     * 实现删除的功能
     * @param obj 需要被删除的数据对象
     */
    public final void delete(Object obj){
       //1：获取删除的sql
       String sql = this.getMainSql(TYPE_DELETE);
       //2：调用通用的更新实现
       this.executeUpdate(sql, TYPE_DELETE,obj);
    }
    /**
     * 实现按照条件查询的功能
     * @param qm 封装查询条件的数据对象
     * @return 符合条件的数据对象集合
     */
    public final Collection getByCondition(Object qm){
       //1：获取查询的sql
       String sql = this.getMainSql(TYPE_CONDITION);
       //2：调用通用的查询实现
       return this.getByCondition(sql, qm);
    }
  
    /*---------------------原语操作---------------------*/      
    /**
     * 获取操作需要的主干sql
     * @param type 操作类型
     * @return 操作对应的主干sql
     */
    protected abstract String getMainSql(int type);
    /**
     * 为更新操作的sql中的"?"设置值
     * @param type 操作类型
     * @param pstmt PreparedStatement对象
     * @param obj 操作的数据对象
     * @throws Exception
     */
    protected abstract void setUpdateSqlValue(int type, PreparedStatement pstmt,Object obj) throws Exception;
    /**
     * 为通用查询动态的拼接sql的条件部分，基本思路是：
     * 只有用户填写了相应的条件，那么才在sql中添加对应的条件
     * @param sql sql的主干部分
     * @param qm 封装查询条件的数据模型
     * @return 拼接好的sql语句
     */
    protected abstract String prepareQuerySql(String sql,Object qm);
    /**
     * 为通用查询的sql动态设置条件的值
     * @param pstmt 预处理查询sql的对象
     * @param qm 封装查询条件的数据模型
     * @throws Exception
     */
    protected abstract void setQuerySqlValue(PreparedStatement pstmt,Object qm)throws Exception;
    /**
     * 把查询返回的结果集转换成为数据对象
     * @param rs 查询返回的结果集
     * @return 查询返回的结果集转换成为数据对象
     * @throws Exception
     */
    protected abstract Object rs2Object(ResultSet rs)throws Exception;
  
    /*---------------------钩子操作---------------------*/      
    /**
     * 连接数据库的默认实现，可以被子类覆盖
     * @return 数据库连接
     * @throws Exception
     */
    protected Connection getConnection()throws Exception{
       Class.forName("你用的数据库对应的JDBC驱动类");
       return DriverManager.getConnection(
             "连接数据库的URL",
             "用户名","密码");
    }
    /**
     * 执行查询
     * @param sql 查询的主干sql语句
     * @param qm 封装查询条件的数据模型
     * @return 查询后的结果对象集合
     */
    protected Collection getByCondition(String sql,Object qm){
       Collection col = new ArrayList();
       Connection conn = null;
       try{
           //调用钩子方法
           conn = this.getConnection();
           //调用原语操作
           sql = this.prepareQuerySql(sql, qm);
           PreparedStatement pstmt = conn.prepareStatement(sql);
           //调用原语操作
           this.setQuerySqlValue(pstmt, qm);
           ResultSet rs = pstmt.executeQuery();
           while(rs.next()){
              //调用原语操作
              col.add(this.rs2Object(rs));
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
       return col;
    }
    /**
     * 执行更改数据的sql语句，包括增删改的功能
     * @param sql 需要执行的sql语句
     * @param callback 回调接口，回调为sql语句赋值的方法
     */
    protected void executeUpdate(String sql,int type,Object obj){
       Connection conn = null;
       try{
           //调用钩子方法        
           conn = this.getConnection();
           PreparedStatement pstmt = conn.prepareStatement(sql);
           //调用原语操作
           this.setUpdateSqlValue(type,pstmt,obj);         
           pstmt.executeUpdate();         
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
}

```

* **`简单但是可以通用的JDBC模板做好了，看看如何使用这个模板来实现具体的增删改查功能，示例代码如下：`** 


```java
/**
 * 具体的实现用户管理的增删改查功能
 */
public class UserJDBC extends JDBCTemplate{  
    protected String getMainSql(int type) {
       //根据操作类型，返回相应的主干sql语句
       String sql = "";
       if(type == TYPE_CREATE){
           sql = "insert into tbl_user values(?,?,?)";
       }else if(type == TYPE_DELETE){
           sql = "delete from tbl_user where uuid=?";
       }else if(type == TYPE_UPDATE){
           sql = "update tbl_user set name=?,age=? where uuid=?";
       }else if(type == TYPE_CONDITION){
           sql = "select * from tbl_user where 1=1 ";
       }
       return sql;
    }
    protected void setUpdateSqlValue(int type, PreparedStatement pstmt,Object obj) throws Exception{
       //设置增、删、改操作的sql中"?"对应的值
       if(type == TYPE_CREATE){
           this.setCreateValue(pstmt, (UserModel)obj);
       }else if(type == TYPE_DELETE){
           this.setDeleteValue(pstmt, (UserModel)obj);
       }else if(type == TYPE_UPDATE){
          this.setUpdateValue(pstmt, (UserModel)obj);
       }
    }
    protected Object rs2Object(ResultSet rs)throws Exception{
       UserModel um = new UserModel();
       String uuid = rs.getString("uuid");
       String name = rs.getString("name");
       int age = rs.getInt("age");
     
       um.setAge(age);
       um.setName(name);
       um.setUuid(uuid);
     
       return um;
    }
    protected String prepareQuerySql(String sql,Object qm){
       UserQueryModel uqm = (UserQueryModel)qm;
       StringBuffer buffer = new StringBuffer();
       buffer.append(sql);
       if(uqm.getUuid()!=null&& uqm.getUuid().trim().length()>0){
           buffer.append(" and uuid=? ");
       }
       if(uqm.getName()!=null&& uqm.getName().trim().length()>0){
           buffer.append(" and name like ? ");
       }
       if(uqm.getAge() > 0){
           buffer.append(" and age >=? ");
       }
       if(uqm.getAge2() > 0){
           buffer.append(" and age <=? ");
       }
       return buffer.toString();
    }
    protected void setQuerySqlValue(PreparedStatement pstmt, Object qm)throws Exception{
       UserQueryModel uqm = (UserQueryModel)qm;
       int count = 1;
       if(uqm.getUuid()!=null&& uqm.getUuid().trim().length()>0){
           pstmt.setString(count, uqm.getUuid());
           count++;
       }
       if(uqm.getName()!=null&& uqm.getName().trim().length()>0){
           pstmt.setString(count, "%"+uqm.getName()+"%");
           count++;
       }
       if(uqm.getAge() > 0){
           pstmt.setInt(count, uqm.getAge());
           count++;
       }
       if(uqm.getAge2() > 0){
           pstmt.setInt(count, uqm.getAge2());
           count++;
       }
    }
    private void setCreateValue(PreparedStatement pstmt,UserModel um)throws Exception{
       pstmt.setString(1, um.getUuid());
       pstmt.setString(2, um.getName());
       pstmt.setInt(3, um.getAge());
    }
    private void setUpdateValue(PreparedStatement pstmt,UserModel um)throws Exception{
       pstmt.setString(1, um.getName());
       pstmt.setInt(2, um.getAge());
       pstmt.setString(3, um.getUuid());
    }
    private void setDeleteValue(PreparedStatement pstmt,UserModel um)throws Exception{
       pstmt.setString(1, um.getUuid());
    }
}

```

看到这里，可能有些朋友会想，为何不把准备sql的方法、为sql中“？”赋值的方法、还有结果集映射成为对象的方法也做成公共的呢？
`其实这些方法是可以考虑做成公共的，用反射机制就可以实现，但是这里为了突出模板方法模式的使用，免得加的东西太多，把大家搞迷惑了。`事实上，用模板方法加上泛型再加上反射的技术，就可以实现可重用的，使用模板时几乎不用再写代码的数据层实现，这里就不去展开了。

* **`享受的时刻到了，来写个客户端，使用UserJDBC的实现，示例代码如下：`** 


```java
public class Client {
    public static void main(String[] args) {
       UserJDBC uj = new UserJDBC();
       //先新增几条
       UserModel um1 = new UserModel();
       um1.setUuid("u1");
       um1.setName("张三");
       um1.setAge(22);     
       uj.create(um1);     
     
       UserModel um2 = new UserModel();
       um2.setUuid("u2");
       um2.setName("李四");
       um2.setAge(25);     
       uj.create(um2);
     
       UserModel um3 = new UserModel();
       um3.setUuid("u3");
       um3.setName("王五");
       um3.setAge(32);     
       uj.create(um3);
     
       //测试修改
       um3.setName("王五被改了");
       um3.setAge(35);
       uj.update(um3);
     
       //测试查询
       UserQueryModel uqm = new UserQueryModel();
       uqm.setAge(20);
       uqm.setAge2(36);
       Collection<UserModel> col = uj.getByCondition(uqm);
       for(UserModel tempUm : col){
           System.out.println(tempUm);
       }
    }
}

```
## 3.6 模板方法模式的优缺点##

* **`实现代码复用`** 


模板方法模式是一种实现代码复用的很好的手段。通过把子类的公共功能提炼和抽取，把公共部分放到模板里面去实现。

* **`算法骨架不容易升级`** 


模板方法模式最基本的功能就是通过模板的制定，把算法骨架完全固定下来。`事实上模板和子类是非常耦合的，如果要对模板中的算法骨架进行变更，可能就会要求所有相关的子类进行相应的变化`。所以抽取算法骨架的时候要特别小心，尽量确保是不会变化的部分才放到模板中。
## 3.7 思考模板方法模式##

* **`模板方法模式的本质`** 

 **``模板方法模式的本质：固定算法骨架。``** 

模板方法模式主要是通过制定模板，把算法步骤固定下来，至于谁来实现，模板可以自己提供实现，也可以由子类去实现，还可以通过回调机制让其它类来实现。

通过固定算法骨架，来约束子类的行为，并在特定的扩展点，来让子类进行功能扩展，从而让程序既有很好的复用性，又有较好的扩展性。

* **`对设计原则的体现`** 

`模板方法很好的体现了开闭原则和里氏替换原则。``首先从设计上，先分离变与不变，然后把不变的部分抽取出来`，定义到父类里面，比如算法骨架，比如一些公共的、固定的实现等等。这些不变的部分被封闭起来，尽量不去修改它了，要扩展新的功能，那就使用子类来扩展，通过子类来实现可变化的步骤，对于这种新增功能的做法是开放的。
`其次，能够实现统一的算法骨架，通过切换不同的具体实现来切换不同的功能`，一个根本原因就是里氏替换原则，遵循这个原则，保证所有的子类实现的是同一个算法模板，并能在使用模板的地方，根据需要，切换不同的具体实现。

* **`何时选用模板方法模式`** 


建议在如下情况中，选用模板方法模式：

需要固定定义算法骨架，实现一个算法的不变的部分，并把可变的行为留给子类来实现的情况；

各个子类中具有公共行为，应该抽取出来，集中在一个公共类中去实现，从而避免代码重复；

需要控制子类扩展的情况。模板方法模式会在特定的点来调用子类的方法，这样只允许在这些点进行扩展；

## 3.8 相关模式##

* **`模板方法模式和工厂方法模式`** 


这两个模式可以配合使用。

模板方法模式可以通过工厂方法来获取需要调用的对象。

* **`模板方法模式和策略模式`** 


这两个模式的功能有些相似，但是是有区别的。

从表面上看，`两个模式都能实现算法的封装，但是模板方法封装的是算法的骨架，这个算法骨架是不变的，变化的是算法中某些步骤的具体实现；而策略模式是把某个步骤的具体实现算法封装起来，所有封装的算法对象是等价的，可以相互替换`。

因此，可以`在模板方法中使用策略模式，就是把那些变化的算法步骤通过使用策略模式来实现`，但是具体选取哪个策略还是要由外部来确定，`而整体的算法步骤，也就是算法骨架就由模板方法来定义了`。


[0]: ./img/2062729-ef179a2e31813b9f.png