# JDBC笔记

## 1.0	JDBC是什么

​	为了做到同一套Java代码操作不同的关系型数据库，sun公司就指定了一套标准接口（JDBC），JDBC中定义了所有操作关系型数据库的规则。众所周知接口是无法直接使用的，我们需要使用接口的实现类，而这套实现类（称之为：驱动）就由各自的数据库厂商给出。

![image-20210725130537815](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/image-20210725130537815.png)

​	所以JDBC就是使用<u>Java语言操作关系型数据库的一套API</u>。全称：( Java DataBase Connectivity ) Java 数据库连接

​	**本质**就是一套接口，各个数据库厂商去实现这套接口，提供数据库驱动jar包。我们可以使用这套接口（JDBC）编程，真正执行的代码是驱动jar包中的实现类

### 1.1	Java如何操作数据库

​	第一步：编写Java代码

​	第二步：Java代码将SQL发送到MySQL服务端

​	第三步：MySQL服务端接收到SQL语句并执行该SQL语句

​	第四步：将SQL语句执行的结果返回给Java代码

![image-20210725163745153](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/image-20210725163745153.png)

#### 1.11	基础操作步骤

​	1. 创建Project,新建lib文件夹,导入驱动jar包

![image-20210725133015535](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/image-20210725133015535.png)

2. 注册驱动

```sql
Class.forName("com.mysql.jdbc.Driver");
```

3. 获取连接

```sql
Connection conn = DriverManager.getConnection(url, username, password);
```

Java代码需要发送SQL给MySQL服务端，就需要先建立连接

4. 定义SQL语句

```sql
String sql =  “update…” ;
```

5. 获取执行SQL对象

    执行SQL语句需要SQL执行对象，而这个执行对象就是Statement对象

```sql
Statement stmt = conn.createStatement();
```

6. 执行SQL

```sql
stmt.executeUpdate(sql);  
```

7. 处理返回结果

8. 释放资源

​	代码参考:

```java
public class JDBCDemo {

    public static void main(String[] args) throws Exception {
        //1. 注册驱动
        //Class.forName("com.mysql.jdbc.Driver");
        //2. 获取连接
        String url = "jdbc:mysql://127.0.0.1:3306/db1";
        String username = "root";
        String password = "1234";
        Connection conn = DriverManager.getConnection(url, username, password);
        //3. 定义sql
        String sql = "update account set money = 2000 where id = 1";
        //4. 获取执行sql的对象 Statement
        Statement stmt = conn.createStatement();
        //5. 执行sql
        int count = stmt.executeUpdate(sql);//受影响的行数
        //6. 处理结果
        System.out.println(count);
        //7. 释放资源
        stmt.close();
        conn.close();
    }
}
```

## 2.0	JDBC的API功能介绍

### 2.1	DriverManager类

​	DriverManager类的作用是管理可用的JDBC驱动程序，并且负责建立数据库和合适的驱动程序之间的连接。它包含了一些方法，例如getConnection，getDrivers，registerDriver等。DriverManager类还支持Java标准版服务提供者机制，可以通过META-INF/services/java.sql.Driver文件来指定JDBC驱动程序的实现类。

#### 2.11	注册驱动

​	registerDriver()方法可用于注册驱动。

```java
public static synchronized void registerDriver(java.sql.Driver driver);
```

​	但上面的示例代码没有这样写，而是这样:

```java
Class.forName("com.mysql.jdbc.Driver");
```

​	翻阅原码可知，这是因为com.mysql.cj.jdbc.Driver类中有一个静态代码块:

```java
static {
        try {
            DriverManager.registerDriver(new Driver());
        } catch (SQLException var1) {
            throw new RuntimeException("Can't register driver!");
        }
    }
```

​	每当Driver类被加载，该静态代码块就会被执行，该静态代码块中会执行DriverManager对象的 registerDriver()方法，以此进行驱动的注册。

​	而 `Class.forName("com.mysql.jdbc.Driver");` 就可以加载 Driver类。

​	在MySQL 5之后的驱动包，可以省略注册驱动的步骤。Java会自动加载jar包中META-INF/services/java.sql.Driver文件中的驱动类。

#### 2.12	获取数据库连接

​	getConnection()可以获取与数据库的连接。

```java
public static Connection getConnection(String url,
        String user, String password) throws SQLException
```

##### 2.121	参数说明

 - url ： 连接路径

    - 语法：jdbc:mysql://ip地址(域名):端口号/数据库名称?参数键值对1&参数键值对2…

        示例：jdbc:mysql://127.0.0.1:3306/db1

        细节:

        * 如果连接的是本机mysql服务器，并且mysql服务默认端口是3306，则url可以简写为：jdbc:mysql:///数据库名称?参数键值对

        * 配置 useSSL=false 参数，禁用安全连接方式，解决警告提示(本人实操时未发现警告)

 - user ：用户名

- password ：密码



### 2.2	Connection接口

​	Connection是java.sql包下的一个接口，它表示一个Java应用程序和数据库之间的会话。它可以帮助建立和数据库的连接，并且提供了一些方法来执行SQL语句，**获取执行SQL对象**，**管理事务**等。Connection接口也是**Statement**，**PreparedStatement**和**DatabaseMetaData**的**工厂类**[^1]，即<u>可以通过Connection的实现类对象来获取这些对象</u>。



#### 2.21	获取执行SQL对象

​	

* **普通执行SQL对象**

    ```java
    Statement createStatement()
    ```

    入门案例中就是通过该方法获取的执行对象。

* **预编译SQL的执行SQL对象**：防止SQL注入

    ```java
    PreparedStatement  prepareStatement(sql)
    ```

    通过这种方式获取的 `PreparedStatement` SQL语句执行对象可以防止SQL注入。

* **执行存储过程的对象**

    ```java
    CallableStatement prepareCall(sql)
    ```

    通过这种方式获取的 `CallableStatement` 执行对象是用来执行存储过程的，而存储过程在MySQL中不常用，了解存在即可。

    

#### 2.22	事务管理

​	短暂复习MySQL事务的操作

* 开启事务 ： BEGIN; 或者 START TRANSACTION;
* 提交事务 ： COMMIT;
* 回滚事务 ： ROLLBACK;

​	<u>在Java中一般用异常处理方式**try{}catch{}**进行事务管理。</u>

​	相应方法:

| 方法                                                        | 描述                                                       |
| ----------------------------------------------------------- | ---------------------------------------------------------- |
| void setAutoCommit(boolean autoCommit) throws SQLException; | 事务自动提交模式的开关，设置为false时标志事务开启          |
| void commit() throws SQLException;                          | 提交当前事务，并释放此Connection对象当前持有的所有数据库锁 |
| void rollback() throws SQLException;                        | 回滚当前事务，并释放此Connection对象当前持有的所有数据库锁 |

​	代码示例:

```java
public class JDBCDemo3_Connection {

    public static void main(String[] args) throws Exception {
        //1. 注册驱动
        //Class.forName("com.mysql.jdbc.Driver");
        //2. 获取连接：如果连接的是本机mysql并且端口是默认的 3306 可以简化书写
        String url = "jdbc:mysql:///db1?useSSL=false";
        String username = "root";
        String password = "1234";
        Connection conn = DriverManager.getConnection(url, username, password);
        //3. 定义sql
        String sql1 = "update account set money = 3000 where id = 1";
        String sql2 = "update account set money = 3000 where id = 2";
        //4. 获取执行sql的对象 Statement
        Statement stmt = conn.createStatement();

        try {
            // ============开启事务==========
            conn.setAutoCommit(false);
            //5. 执行sql
            int count1 = stmt.executeUpdate(sql1);//受影响的行数
            //6. 处理结果
            System.out.println(count1);
            int i = 3/0;
            //5. 执行sql
            int count2 = stmt.executeUpdate(sql2);//受影响的行数
            //6. 处理结果
            System.out.println(count2);

            // ============提交事务==========
            //程序运行到此处，说明没有出现任何问题，则需求提交事务
            conn.commit();
        } catch (Exception e) {
            // ============回滚事务==========
            //程序在出现异常时会执行到这个地方，此时就需要回滚事务
            conn.rollback();
            e.printStackTrace();
        }

        //7. 释放资源
        stmt.close();
        conn.close();
    }
}
```





### 2.3	Statement接口

​	一开始我居然没有在IDEA的搜索中搜到有类实现了Connection类的createStatement方法。经过我一小时不断地翻源码，终于找到了Connection->JdbcConncetion(Interface)->**ConnectionImpl**(Class)的继承链。

![ConnectionImpl](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/ConnectionImpl.png)

​	其中底层返回一个**StatementImpl**的Statement的实现类对象:

![ConnectionImpl-16790615264121](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/ConnectionImpl-16790615264121.png)

​	进入正题，Statement对象的作用就是用来**执行SQL语句**。而针对不同类型的SQL语句使用的方法也不一样。

| 方法                                          | 描述                                                         |
| --------------------------------------------- | ------------------------------------------------------------ |
| int executeUpdate() throws SQLException;      | 执行给定的SQL语句，主要是insert,update,delete等DML语句，或者不返回任何内容的DDL语句。 |
| ResultSet executeQuery() throws SQLException; | 执行DQL语句，返回单个ResultSet对象。                         |

​	DML的代码例子:

```java
public void testDML() throws  Exception {
    //1. 注册驱动
    //Class.forName("com.mysql.jdbc.Driver");
    //2. 获取连接：如果连接的是本机mysql并且端口是默认的 3306 可以简化书写
    String url = "jdbc:mysql:///db1?useSSL=false";
    String username = "root";
    String password = "1234";
    Connection conn = DriverManager.getConnection(url, username, password);
    //3. 定义sql
    String sql = "update account set money = 3000 where id = 1";
    //4. 获取执行sql的对象 Statement
    Statement stmt = conn.createStatement();
    //5. 执行sql
    int count = stmt.executeUpdate(sql);//执行完DML语句，受影响的行数
    //6. 处理结果
    //System.out.println(count);
    if(count > 0){
        System.out.println("修改成功~");
    }else{
        System.out.println("修改失败~");
    }
    //7. 释放资源
    stmt.close();
    conn.close();
}
```

#### 2.31	在字符串中表示SQL语句或者其他语言的代码

​	我们可以在字符串中使用**双引号的单引号的嵌套**来表示SQL语句或者其他语言的代码:

```java
String sql = "SELECT * FROM users WHERE name = 'Tom';";
System.out.println(sql); // 输出 SELECT * FROM users WHERE name = 'Tom';
```

### 2.4	ResultSet

​	`ResultSet`表示数据库结果集的数据表，通常通过执行查询数据库的语句生成。上文Statement接口中的executeQuery()方法的返回值就是ResultSet实现类的对象。

​	相关继承链和实现:![ResultSet](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/ResultSet.png)

​	其中ResultSetImpl为定义在mysql JAR包内的实现类。

​	`ResultSet`对象维护指向其当前数据行的光标/游标。  最初，光标位于第一行之前。 `next`方法将光标移动到下一行，并且因为当`ResultSet`对象中没有更多行时它返回`false`  ，它可以在`while`循环中用于迭代结果集。

​                                                                	<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210725181320813.png" alt="image-20210725181320813" style="zoom:80%;" />  

​	一开始光标指定于第一行前，如图所示红色箭头指向于表头行。当我们调用了 `next()` 方法后，光标就下移到第一行数据，并且方法返回true，此时就可以通过 `getInt("id")` 获取当前行id字段的值，也可以通过 `getString("name")` 获取当前行name字段的值。如果想获取下一行的数据，继续调用 `next()`  方法，以此类推。

#### 2.31	主要方法

​	需要注意<u>列的编号是从1开始而不是0</u>。

| 方法                                                      | 介绍                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| boolean next()                                            | 将光标从当前位置向前移动一行并判断当前行是否为有效行         |
| String getString(int columnIndex) throws SQLException;    | 获取当前光标所在行的**第**columnIndex列数据，且该数据需为String |
| String getString(String columnLabel) throws SQLException; | 获取当前光标所在行的**名为**columnLabel的数据，且该数据需为String |
| xxx getXxx(参数)                                          | 接口中声明了若干种getter方法，格式同上行。                   |

​	用作getter方法输入的列名不区分大小写。  当使用列名调用getter方法并且多个列具有相同名称时，将返回第一个匹配列的值。  列名选项设计用于在生成结果集的SQL查询中使用列名时使用。 对于未在查询中明确命名的列，最好使用列号。

#### 2.32	代码样例

```java
/**
  * 需求: 查询account账户表数据，封装为Account对象中，并且存储到ArrayList集合中
  * 1. 定义实体类Account
  * 2. 查询数据，封装到Account对象中
  * 3. 将Account对象存入ArrayList集合中
  */
public void testResultSet2() throws  Exception {
    //1. 注册驱动
    //Class.forName("com.mysql.jdbc.Driver");
    //2. 获取连接：如果连接的是本机mysql并且端口是默认的 3306 可以简化书写
    String url = "jdbc:mysql:///db1?useSSL=false";
    String username = "root";
    String password = "1234";
    Connection conn = DriverManager.getConnection(url, username, password);

    //3. 定义sql
    String sql = "select * from account";

    //4. 获取statement对象
    Statement stmt = conn.createStatement();

    //5. 执行sql
    ResultSet rs = stmt.executeQuery(sql);

    // 创建集合
    List<Account> list = new ArrayList<>();
   
    // 6.1 光标向下移动一行，并且判断当前行是否有数据
    while (rs.next()){
        Account account = new Account();

        //6.2 获取数据  getXxx()
        int id = rs.getInt("id");
        String name = rs.getString("name");
        double money = rs.getDouble("money");

        //赋值
        account.setId(id);
        account.setName(name);
        account.setMoney(money);

        // 存入集合
        list.add(account);
    }

    System.out.println(list);

    //7. 释放资源
    rs.close();
    stmt.close();
    conn.close();
}
```



### 2.5	PreparedStatement接口

​	PreparedStatement的功能:

- 它可以提高执行效率，因为预编译的SQL语句只需要编译一次，然后可以重复使用多次。
- 它可以防止SQL注入攻击，因为它支持参数化查询，即使用占位符（?）代替实际的参数值，然后通过setXXX方法设置参数值。这样可以避免拼接字符串导致的SQL语法错误或恶意代码注入。
- 它可以方便地处理不同类型的参数值，例如日期、二进制、数组等，而不需要进行额外的转换或格式化。

​	继承链或实现类(部分):

![PreparedStatement](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/PreparedStatement.png)



#### 2.51	什么是SQL注入攻击?

​	SQL注入攻击是通过操作输入来修改事先定义好的SQL语句，用以达到执行代码对服务器进行攻击的方法。

​	SQL注入的原理是:

> ​	通过构造特殊的输入字符串，破坏后端程序原有的SQL查询语句的结构，使得攻击者可以在查询语句的结尾上添加额外的SQL语句，从而执行非预期的操作。

##### 2.511	一些SQL注入攻击的例子	

- 检索隐藏数据。在其中修改SQL查询以返回其他结果。例如：

```sql
http://www.armandhe.com/query.php?id=1' and 1=2 union select username,password from users --
```

这个输入会使后端查询语句变成：

```sql
select name,age,gender from t_students where id=1' and 1=2 union select username,password from users --;
```

由于`and 1=2`这个条件永远为假，所以第一个查询语句不会返回任何结果。然后使用`union`关键字来连接第二个查询语句，从users表中检索用户名和密码，并返回给用户。



- 颠覆应用程序逻辑。更改查询以干扰应用程序的逻辑。例如：

```sql
http://www.armandhe.com/login.php?username=admin' or '1'='1&password=
```

这个输入会使后端查询语句变成：

```sql
select * from users where username='admin' or '1'='1' and password='';
```

由于`or '1'='1'`这个条件永远为真，所以无论数据库中是否存在admin用户，都会返回所有用户信息，并使得攻击者可以无密码登录。



- 检查数据库。从中可以提取有关数据库版本和结构的信息。例如：

```sql
http://www.armandhe.com/query.php?id=0; select version() --
http://www.armandhe.com/query.php?id=0; select database() --
http://www.armandhe.com/query.php?id=0; select user() --
http://www.armandhe.com/query.php?id=0; select table_name from information_schema.tables --
```

这些输入会使后端执行多条查询语句，并返回相应的信息，如数据库版本、名称、用户、表名等。



- 盲SQL注入。控制的查询结果不会在应用程序的响应中返回。例如：

```sql
http://www.armandhe.com/query.php?id=0; if (user()='root', sleep(10), null) --
```

这个输入会使后端执行以下条件判断语句：

```sql
if (user()='root', sleep(10), null)
```

如果当前用户是root，则延迟10秒；否则什么也不做。通过观察页面响应时间，攻击者可以推断出当前用户是否是root。



##### 2.512	Java代码模拟

```java
public class SQLInjectionTest {
        public static void testLogin() throws  Exception {
            //2. 获取连接：如果连接的是本机mysql并且端口是默认的 3306 可以简化书写
            String url = "jdbc:mysql:///test02?useSSL=false";
            String username = "root";
            String password = "123456";
            Connection conn = DriverManager.getConnection(url, username, password);
            // 接收用户输入 ID和姓名
            String ID = "1";
            String name = "张无忌' or '1' = '1";
            String sql = "select * from emp where id = '"+ID+"' and name = '"+name+"'";
            // 获取stmt对象
            Statement stmt = conn.createStatement();
            // 执行sql
            ResultSet rs = stmt.executeQuery(sql);
            // 判断登录是否成功
            while(rs.next()){
                int id=rs.getInt("id");
                String name1 =rs.getString("name");
                String idcard = rs.getString("idcard");
                int salary = rs.getInt("salary");
                System.out.println(id+" "+name1+" "+idcard +" 薪水:"+ salary);
            }

            //7. 释放资源
            rs.close();
            stmt.close();
            conn.close();
        }
    }
```

​	上面代码是将ID和姓名拼接到sql语句中，拼接后的sql语句如下

```sql
select * from tb_user where ID = '1' and name = '张无忌'or '1' = '1'
```

​	从上面语句可以看出条件 `ID = '1' and name = '张无忌'` 不管是否满足，而 `or` 后面的 `'1' = '1'` 是始终满足的，最终条件是成立的，这样就可以查阅员工表emp里的所有敏感信息。

![SQLInjectionEXP2](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/SQLInjectionEXP2.png)

##### 2.513	规避方法

​	防止SQL注入攻击主要有以下几种方法:

- 使用<u>PreparedStatement接口</u>或其他参数化查询方式来避免拼接字符串。
- 对用户输入数据进行合法性检查和过滤，例如使用正则表达式、转义字符等。
- 设置数据库服务器和Web应用程序之间的最小权限原则，并使用不同账号和密码来访问不同级别和功能模块。
- 使用防火墙或其他安全工具来监控和拦截异常请求和响应。



#### 2.52	常用方法

​	注意**参数位置**从1开始。

| 方法                                           | 描述                                                         |
| ---------------------------------------------- | ------------------------------------------------------------ |
| PreparedStatement prepareStatement(String sql) | 此方法定义在**Connection接口**中,获取一个PreparedStatement的实现类的对象 |
| XXX setXXX(int parameterIndex, XXX value)      | 用于设置IN参数的值，其中XXX是Java类型，parameterIndex是参数的位置，value是参数的值 |
| ResultSet executeQuery()                       | 用于执行查询语句，并返回ResultSet对象                        |
| int executeUpdate()                            | 用于执行更新语句，并返回影响行数                             |

​	小例子:

```java
Connection con = DriverManager.getConnection(url, user, password);
PreparedStatement ps = con.prepareStatement("select * from emp where name=?");
ps.setString(1, "张三"); //设置第一个参数为张三
ResultSet rs = ps.executeQuery(); //执行查询并获取结果集
```

#### 

#### 2.53	原理

​	将敏感字符进行转义，而不是拼接，防止SQL注入。

![image-20210725195756848](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210725195756848.png)

​	Java代码操作数据库流程如图所示：

* 将sql语句发送到MySQL服务器端

* MySQL服务端会对sql语句进行如下操作

    * 检查SQL语句

        检查SQL语句的语法是否正确。

    * 编译SQL语句。将SQL语句编译成可执行的函数。

        检查SQL和编译SQL花费的时间比执行SQL的时间还要长。如果我们只是重新设置参数，那么检查SQL语句和编译SQL语句将不需要重复执行。这样就**提高了性能**。

    * 执行SQL语句



##### 2.531	预编译功能

* 开启预编译功能

    预编译功能**默认是关闭**的，在代码中编写url时需要加上以下参数。而我们之前根本就没有开启预编译功能，只是解决了SQL注入漏洞。

    ```java
    useServerPrepStmts=true;// 加到URL后
    // 例如:
    // String url = "jdbc:mysql:///databaseName?useServerPrepStmts=true";
    ```

* 配置MySQL执行日志（重启mysql服务后生效）

    在mysql配置文件（my.ini）中添加如下配置

    ```
    log-output=FILE
    general-log=1
    general_log_file="D:\mysql.log"
    slow-query-log=1
    slow_query_log_file="D:\mysql_slow.log"
    long_query_time=2
    ```

- 执行语句查看`D:\File\Code relative\MySQL relative\mysql.log`如下

![log](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/log.png)

- 总结:
    - 在获取PreparedStatement对象时，将sql语句发送给mysql服务器进行检查，编译（这些步骤很耗时）。
    - 执行时就不用再进行这些步骤了，速度更快。
    - 如果sql模板一样，则只需要进行一次检查、编译。





### 2.6	ResultSetMetaData接口

​	ResultSetMetaData是Java JDBC中的一个接口，它可以用来获取ResultSet对象的元数据，即关于数据的数据，或者说**表的结构信息**。

​	例如: 可以通过ResultSetMetaData来获取表的列数、列名、列类型、列大小等信息。

​	继承链:

![ResultSetMetaData](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/ResultSetMetaData.png)

#### 2.61	常用方法

| 方法定义                                             | 介绍                                                         |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| ResultSetMetaData getMetaData() throws SQLException; | 此方法声明在ResultSet接口中，由一个ResultSet对象调用         |
| int getColumnCount() throws SQLException;            | 获取表的列数                                                 |
| boolean isAutoIncrement(int columnIndex)             | 判断某列是否有Auto Increment约束                             |
| String getColumnName(int column)                     | 获取列名                                                     |
| String getColumnTypeName(int column)                 | 获取列的类型名                                               |
| int getColumnType(int column)                        | 获取列的类型代码，不同的类型代码对应不同的类型名称，要参考java.sql.Types类中定义的常量。 |

#### 2.62	代码样例

​	可以利用此接口简单快速遍历查询结果。

```java
		ResultSet rs = connectionStatement.executeQuery(sql);
        ResultSetMetaData rsmd = rs.getMetaData();
        // 获得列数
        int columnsNumber = rsmd.getColumnCount();

        // 打印列名
        for (int i = 1; i <= columnsNumber; i++) {
            System.out.print(rsmd.getColumnName(i) + "\t");
        }
        System.out.println();

        // 打印每行数据，似乎用getString可以识别并打印所有类型。         
		while (rs.next()) {
            for (int i = 1; i <= columnsNumber; i++) {
                System.out.print(rs.getString(i) + "\t");
            }
            System.out.println();
        }
```



## 3.0	数据库连接池

​	数据库连接池是个容器，负责分配、管理数据库连接(`Connection`)。它允许应用程序重复使用一个现有的数据库连接，而不是再重新建立一个。它的主要目的是减少执行数据库连接和读写数据库操作所涉及的开销简单来说，连接池是一种数据库连接缓存实现，可以根据特定需求进行配置。

​	它还可以<u>释放空闲时间超过最大空闲时间的数据库连接</u>，来**避免**因为没有释放数据库连接而引起的数据库连接遗漏。

![image-20210725210432985](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210725210432985.png)

​	之前我们代码中使用连接是没有使用都创建一个Connection对象，使用完毕就会将其销毁。这样重复创建销毁的过程是特别耗费计算机的性能的及消耗时间的。

* 好处总结
    * 资源重用
    * 提升系统响应速度
    * 避免数据库连接遗漏

#### 3.1	数据库连接池实现

​	官方(SUN公司)定义了一个提供的数据库连接池标准接口(`DataSource`)。该接口提供了获取连接的功能。一般由第三方组织实现此接口。

​	以Druid池为例:

```java
public DruidPooledConnection getConnection();
```

​	DruidPooledConnection的继承链:

![DruidPooledConnection](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/DruidPooledConnection.png)

​	以后就不需要通过 `DriverManager` 对象获取 `Connection` 对象，而是通过连接池（DataSource）获取 `Connection` 对象。

* 常见的数据库连接池

    * DBCP
    * C3P0
    * Druid

    我们现在使用更多的是Druid，它的性能比其他两个会好一些。

* Druid（德鲁伊）

    * Druid连接池是阿里巴巴开源的数据库连接池项目 

    * 功能强大，性能优秀，是Java语言最好的数据库连接池之一





### 3.2	Druid连接池介绍

​	Druid（德鲁伊）连接池是阿里巴巴开源的数据库连接池项目。功能强大，性能优秀，是Java语言最好的数据库连接池之一。

​	下载好jar包导入后还需编写配置文件:

![image-20210725213210091](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210725213210091.png)



​	配置文件如下：

```properties
driverClassName=com.mysql.jdbc.Driver
url=jdbc:mysql:///test02?useSSL=false&useServerPrepStmts=true
username=root
password=123456
# 初始化连接数量
initialSize=5
# 最大连接数
maxActive=10
# 最大等待时间
maxWait=3000
```

​	加载Druid包后的继承链和实现(部分):

![DataSource](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/DataSource.png)

​	使用druid的代码如下：

```java
import com.alibaba.druid.pool.DruidDataSourceFactory;

import javax.sql.DataSource;
import java.io.FileInputStream;
import java.sql.*;
import java.util.Properties;
public class DruidDemo {

    public static void main(String[] args) throws Exception {
        //1.导入jar包
        //2.定义配置文件
        //3. 加载配置文件
Properties prop = new Properties();
        prop.load(new FileInputStream("src/druid.properties"));
        //System.out.println(System.getProperty("user.dir"));调用可查看当前项目的绝对路径,方便上文路径填写
        //4. 获取连接池对象
        DataSource dataSource = DruidDataSourceFactory.createDataSource(prop);

        //5. 获取数据库连接 Connection
        Connection connection = dataSource.getConnection();
        Statement connectionStatement = connection.createStatement();
        String sql = "select * from emp";
        ResultSet rs = connectionStatement.executeQuery(sql);
        ResultSetMetaData rsmd = rs.getMetaData();

        // 获取字段数
        int columnsNumber = rsmd.getColumnCount();

        // 打印字段名
        for (int i = 1; i <= columnsNumber; i++) {
            System.out.print(rsmd.getColumnName(i) + "\t");
        }
        System.out.println();
        // 打印行数据
        while (rs.next()) {
            for (int i = 1; i <= columnsNumber; i++) {
                System.out.print(rs.getString(i) + "\t");
            }
            System.out.println();
        }
    }
}
```

​	Datasource对象需要DruidDataSourceFactory类下的createDataSource()方法来获得，传入参数为Properties对象。

​	**☆我扒半个小时源码找来的创建方法**:

| 方法                                                         | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| public static DataSource createDataSource(Properties properties) throws Exception | 传入参数为Properties对象，底层实际上是将Properties强转成Map后再调用下面的方法 |
| public static DataSource createDataSource(Map properties)throws Exception | 底层会new一个DruidDataSource对象，调用定义在本类中的config方法加载properties处理DruidDataSource对象，最后返回。 |

​	此后就可以用Datasource对象去getConnection了。









[^1]: 工厂类是一个用来创建对象的类或方法，它可以根据传入的参数或者其他条件来决定创建哪种对象实例。工厂类可以隐藏对象创建的细节，提高代码的可维护性和扩展性。

