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

### 

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

​	进入正题，Statement对象的作用就是用来执行SQL语句。而针对不同类型的SQL语句使用的方法也不一样。

| 方法                                          | 描述                                                         |
| --------------------------------------------- | ------------------------------------------------------------ |
| int executeUpdate() throws SQLException;      | 执行给定的SQL语句，主要是insert,update,delete等DML语句，或者不返回任何内容的DDL语句。 |
| ResultSet executeQuery() throws SQLException; | 执行DQL语句，返回单个ResultSet对象。                         |

​	DML的代码例子:

```java
@Test
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



[^1]: 工厂类是一个用来创建对象的类或方法，它可以根据传入的参数或者其他条件来决定创建哪种对象实例。工厂类可以隐藏对象创建的细节，提高代码的可维护性和扩展性。

