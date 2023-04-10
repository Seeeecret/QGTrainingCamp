# JSP笔记

​	**JSP（Java Server Pages）**：Java 服务端页面。是一种动态的网页技术，其中既可以定义 HTML、JS、CSS等静态内容，还可以定义 Java代码的动态内容，也就是 `JSP = HTML + Java`。如下就是jsp代码

```jsp
<html>
    <head>
        <title>Title</title>
    </head>
    <body>
        <h1>JSP,Hello World</h1>
        <%
        	System.out.println("hello,jsp~");
        %>
    </body>
</html>
```

​	上面代码 `h1` 标签内容是展示在页面上，而 Java 的输出语句是输出在 idea 的控制台。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818103352432.png" alt="image-20210818103352432" style="zoom:70%;" />

​	上面代码可以看到里面基本都是 `HTML` 标签，而动态数据使用 Java 代码进行展示；这样操作看起来要比用 `servlet` 实现要舒服很多。

​	小结: JSP 作用：简化开发，避免了在Servlet中直接输出HTML标签。

## 1.0	JSP快速入门

​	先在maven项目的pom.xml下添加JSP的依赖`javax.servlet.jsp`。该依赖的 `scope` **必须**设置为 `provided`，因为 tomcat 中有这个jar包了，所以在打包时我们是不希望将该依赖打进到我们工程的war包中。

​	之后新建文件，写入代码，启动服务器，在对应路径访问即可。

## 2.0	JSP原理

​	JSP 本质上就是一个 Servlet。	<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818111039350.png" alt="image-20210818111039350" style="zoom:70%;" />

1. 浏览器第一次访问 `hello.jsp` 页面
2. `tomcat` 会将 `hello.jsp` 转换为名为 `hello_jsp.java` 的一个 `Servlet`
3. `tomcat` 再将转换的 `servlet` 编译成字节码文件 `hello_jsp.class`
4. `tomcat` 会执行该字节码文件，向外提供服务

我们可以到项目所在磁盘目录下找 `target\tomcat\work\Tomcat\localhost\jsp-demo\org\apache\jsp` 目录，而这个目录下就能看到转换后的 `servlet`

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818112613589.png" alt="image-20210818112613589" style="zoom:80%;" />

​	打开 `hello_jsp.java` 文件，来查看里面的代码

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818112724462.png" alt="image-20210818112724462" style="zoom:80%;" />

​	由上面的类的继承关系可以看到继承了名为 `HttpJspBase` 这个类，查看该类的继承关系

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818113118802.png" alt="image-20210818113118802" style="zoom:80%;" />

可以看到该类继承了 `HttpServlet` ；那么 `hello_jsp` 这个类就间接的继承了 `HttpServlet` ，也就说明 `hello_jsp` 是一个 `servlet`。

继续阅读 `hello_jsp` 类的代码，可以看到有一个名为 `_jspService()` 的方法，该方法就是每次访问 `jsp` 时自动执行的方法，和 `servlet` 中的 `service` 方法一样 。

而在 `_jspService()` 方法中可以看到往浏览器写标签的代码：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818114008998.png" alt="image-20210818114008998" style="zoom:80%;" />

以前我们自己写 `servlet` 时，这部分代码是由我们自己来写，现在有了 `jsp` 后，由tomcat完成这部分功能。

## 3.0	JSP 脚本	

​	JSP脚本用于在 JSP页面内定义 Java代码。

### 3.1	JSP 脚本分类

JSP 脚本有如下三个分类：

* <%...%>：内容会直接放到_jspService()方法之中
* <%=…%>：内容会放到out.print()中，作为out.print()的参数
* <%!…%>：内容会放到_jspService()方法之外，被类直接包含

**代码演示：**

①  <%...%>

在 `hello.jsp` 中书写

```jsp
<%
    System.out.println("hello,jsp~");
    int i = 3;
%>
```

通过浏览器访问 `hello.jsp` 后，查看转换的 `hello_jsp.java` 文件，i 变量定义在了 `_jspService()` 方法中

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818123606231.png" alt="image-20210818123606231" style="zoom:80%;" />



②  <%=...%>

在 `hello.jsp` 中书写

```jsp
<%="hello"%>
<%=i%>
```

通过浏览器访问 `hello.jsp` 后，查看转换的 `hello_jsp.java` 文件，该脚本的内容被放在了 `out.print()` 中，作为参数

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818123820571.png" alt="image-20210818123820571" style="zoom:80%;" />

③ <%!...%>

在 `hello.jsp` 中书写

```jsp
<%!
    void  show(){}
	String name = "zhangsan";
%>
```

通过浏览器访问 `hello.jsp` 后，查看转换的 `hello_jsp.java` 文件，该脚本的内容被放在了成员位置

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818123946272.png" alt="image-20210818123946272" style="zoom:80%;" />

### 3.2	代码样例

​	需求: 使用JSP脚本展示品牌数据

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818125203390.png" alt="image-20210818125203390" style="zoom:80%;" />

#### 	代码如下:

```jsp
<%@ page import="com.itheima.pojo.Brand" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%
    // 查询数据库
    List<Brand> brands = new ArrayList<Brand>();
    brands.add(new Brand(1,"三只松鼠","三只松鼠",100,"三只松鼠，好吃不上火",1));
    brands.add(new Brand(2,"优衣库","优衣库",200,"优衣库，服适人生",0));
    brands.add(new Brand(3,"小米","小米科技有限公司",1000,"为发烧而生",1));// 自定义的POJO类

%>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<input type="button" value="新增"><br>
<hr>
<table border="1" cellspacing="0" width="800">
    <tr>
        <th>序号</th>
        <th>品牌名称</th>
        <th>企业名称</th>
        <th>排序</th>
        <th>品牌介绍</th>
        <th>状态</th>
        <th>操作</th>
    </tr>
    <%
        for (int i = 0; i < brands.size(); i++) {
            Brand brand = brands.get(i);
    %>

    <tr align="center">
        <td><%=brand.getId()%></td>
        <td><%=brand.getBrandName()%></td>
        <td><%=brand.getCompanyName()%></td>
        <td><%=brand.getOrdered()%></td>
        <td><%=brand.getDescription()%></td>
		<td><%=brand.getStatus() == 1 ? "启用":"禁用"%></td>
        <td><a href="#">修改</a> <a href="#">删除</a></td>
    </tr>

    <%
        }
    %>
</table>
</body>
</html>
```



## 4.0	JSP的缺点

​	由于 JSP页面内，既可以定义 HTML 标签，又可以定义 Java代码，造成了以下问题：

* 书写麻烦：特别是复杂的页面

    既要写 HTML 标签，还要写 Java 代码

* 阅读麻烦

    上面案例的代码，相信你后期再看这段代码时还需要花费很长的时间去梳理

* 复杂度高：运行需要依赖于各种环境，JRE，JSP容器，JavaEE…

* 占内存和磁盘：JSP会自动生成.java和.class文件占磁盘，运行的是.class文件占内存

* 调试困难：出错后，需要找到自动生成的.java文件进行调试

* 不利于团队协作：前端人员不会 Java，后端人员不精 HTML

    如果页面布局发生变化，前端工程师对静态页面进行修改，然后再交给后端工程师，由后端工程师再将该页面改为 JSP 页面

​	由于上述的问题， JSP 已逐渐退出历史舞台，以后开发更多的是使用 **HTML** +  **Ajax** 来替代。Ajax 是我们后续会重点学习的技术。有个这个技术后，前端工程师负责前端页面开发，而后端工程师只负责前端代码开发。此之谓**前后端分离**

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818150346332.png" alt="image-20210818150346332" style="zoom:80%;" />

​	所以简单了解JSP，学习了解一些必备知识即可: 

​		使用 `Servlet` 进行逻辑代码开发，而使用 `JSP` 进行数据展示

<img src="../../学习相关/笔记/黑马笔记/day10-JSP/ppt/assets/image-20210818151232955.png" alt="image-20210818151232955" style="zoom:67%;" />

## 5.0	EL表达式

​	**EL（Expression Language ）**表达式语言，用于简化 JSP 页面内的 Java 代码。

​	EL 表达式的主要作用是获取数据。其实就是从域对象中获取数据，然后将数据展示在页面上。

​	而 EL 表达式的语法也比较简单，${expression} 。例如：${brands} 就是获取域中存储的 key 为 brands 的数据。

​	以下是一个小例子:

* 定义servlet，在 servlet 中封装一些数据并存储到 request 域对象中并转发到 `el-demo.jsp` 页面。

    ```java
    @WebServlet("/demo1")
    public class ServletDemo1 extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            //1. 准备数据
            List<Brand> brands = new ArrayList<Brand>();
            brands.add(new Brand(1,"三只松鼠","三只松鼠",100,"三只松鼠，好吃不上火",1));
            brands.add(new Brand(2,"优衣库","优衣库",200,"优衣库，服适人生",0));
            brands.add(new Brand(3,"小米","小米科技有限公司",1000,"为发烧而生",1));
    
            //2. 存储到request域中
            request.setAttribute("brands",brands);
    
            //3. 转发到 el-demo.jsp
            request.getRequestDispatcher("/el-demo.jsp").forward(request,response);
        }
    
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            this.doGet(request, response);
        }
    }
    ```

    > 注意： 此处需要用转发，因为转发才可以使用 request 对象作为域对象进行数据共享

* 在 `el-demo.jsp` 中通过 EL表达式 获取数据

    ```jsp
    <%@ page contentType="text/html;charset=UTF-8" language="java" %>
    <html>
    <head>
        <title>Title</title>
    </head>
    <body>
        ${brands}
    </body>
    </html>
    ```

* 在浏览器的地址栏输入 `http://localhost:8080/jsp-demo/demo1` ，页面效果如下：

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818152536484.png" alt="image-20210818152536484" style="zoom:80%;" />

### 5.1	域对象

​	JavaWeb中有四大域对象，分别是：

* page：当前页面有效
* request：当前请求有效
* session：当前会话有效
* application：当前应用有效

​	el 表达式获取数据，会依次从这4个域中寻找，直到找到为止。而这四个域对象的作用范围如下图所示

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818152857407.png" alt="image-20210818152857407" style="zoom:60%;" />

​	例如： ${brands}，el 表达式获取数据，会先从page域对象中获取数据，如果没有再到 requet 域对象中获取数据，如果再没有再到 session 域对象中获取，如果还没有才会到 application 中获取数据。

## 6.0	JSTL标签

​	JSP标准标签库(Jsp Standarded Tag Library) ，使用标签取代JSP页面上的Java代码。如下代码就是JSTL标签。

```jsp
<c:if test="${flag == 1}">
    男
</c:if>
<c:if test="${flag == 2}">
    女
</c:if>
```

​	JSTL 提供了很多标签，如下图

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818153646575.png" alt="image-20210818153646575" style="zoom:80%;" />

​	JSTL 使用也是比较简单的，分为如下步骤：

* 导入坐标

    ```xml
    <dependency>
        <groupId>jstl</groupId>
        <artifactId>jstl</artifactId>
        <version>1.2</version>
    </dependency>
    <dependency>
        <groupId>taglibs</groupId>
        <artifactId>standard</artifactId>
        <version>1.1.2</version>
    </dependency>
    ```

* 在JSP页面上引入JSTL标签库

    ```jsp
    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %> 
    ```

* 使用标签

### 6.1	if 标签

​	`<c:if>`：相当于 if 判断

* 属性：test，用于定义条件表达式

```jsp
<c:if test="${flag == 1}">
    男
</c:if>
<c:if test="${flag == 2}">
    女
</c:if>
```

​	**代码演示：**

* 定义一个 `servlet` ，在该 `servlet` 中向 request 域对象中添加 键是 `status` ，值为 `1` 的数据

    ```java
    @WebServlet("/demo2")
    public class ServletDemo2 extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            //1. 存储数据到request域中
            request.setAttribute("status",1);
    
            //2. 转发到 jstl-if.jsp
            数据request.getRequestDispatcher("/jstl-if.jsp").forward(request,response);
        }
    
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            this.doGet(request, response);
        }
    }
    ```

* 定义 `jstl-if.jsp` 页面，在该页面使用 `<c:if>` 标签

    ```jsp
    <%@ page contentType="text/html;charset=UTF-8" language="java" %>
    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
    <html>
    <head>
        <title>Title</title>
    </head>
    <body>
        <%--
            c:if：来完成逻辑判断，替换java  if else
        --%>
        <c:if test="${status ==1}">
            启用
        </c:if>
    
        <c:if test="${status ==0}">
            禁用
        </c:if>
    </body>
    </html>
    ```

    > 注意：在该页面已经要引入 JSTL核心标签库
    >
    > `<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>`

### 6.2	forEach 标签

​	`<c:forEach>`：相当于 for 循环。java中有增强for循环和普通for循环，JSTL 中的 `<c:forEach>` 也有两种用法

#### 6.2.1	用法一

​	类似于 Java 中的增强for循环。涉及到的 `<c:forEach>` 中的属性如下

* items：被遍历的容器

* var：遍历产生的临时变量

* varStatus：遍历状态对象

​	如下代码，是从域对象中获取名为 brands 数据，该数据是一个集合；遍历遍历，并给该集合中的每一个元素起名为 `brand`，是 Brand对象。在循环里面使用 EL表达式获取每一个Brand对象的属性值

```jsp
<c:forEach items="${brands}" var="brand">
    <tr align="center">
        <td>${brand.id}</td>
        <td>${brand.brandName}</td>
        <td>${brand.companyName}</td>
        <td>${brand.description}</td>
    </tr>
</c:forEach>
```

​	**代码演示：**

* `servlet` 还是使用之前的名为 `ServletDemo1` 。

* 定义名为 `jstl-foreach.jsp` 页面，内容如下：

    ```jsp
    <%@ page contentType="text/html;charset=UTF-8" language="java" %>
    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
    
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Title</title>
    </head>
    <body>
    <input type="button" value="新增"><br>
    <hr>
    <table border="1" cellspacing="0" width="800">
        <tr>
            <th>序号</th>
            <th>品牌名称</th>
            <th>企业名称</th>
            <th>排序</th>
            <th>品牌介绍</th>
            <th>状态</th>
            <th>操作</th>
        </tr>
    
        <c:forEach items="${brands}" var="brand" varStatus="status">
            <tr align="center">
                <%--<td>${brand.id}</td>--%>
                <td>${status.count}</td>
                <td>${brand.brandName}</td>
                <td>${brand.companyName}</td>
                <td>${brand.ordered}</td>
                <td>${brand.description}</td>
                <c:if test="${brand.status == 1}">
                    <td>启用</td>
                </c:if>
                <c:if test="${brand.status != 1}">
                    <td>禁用</td>
                </c:if>
                <td><a href="#">修改</a> <a href="#">删除</a></td>
            </tr>
        </c:forEach>
    </table>
    </body>
    </html>
    ```

#### 6.3.2	用法二

​	类似于 Java 中的普通for循环。涉及到的 `<c:forEach>` 中的属性如下

* begin：开始数

* end：结束数

* step：步长

​	实例代码：

​	从0循环到10，变量名是 `i` ，每次自增1

```jsp
<c:forEach begin="0" end="10" step="1" var="i">
    ${i}
</c:forEach>
```

​	配合超链接可以用来实现类似**分页链接**的效果

## 7，MVC模式和三层架构

​	MVC 模式和三层架构是一些理论的知识，将来我们使用了它们进行代码开发会让我们代码维护性和扩展性更好。

### 7.1  MVC模式

​	MVC 是一种分层开发的模式，其中：

* M：Model，业务模型，处理业务

* V：View，视图，界面展示

* C：Controller，控制器，处理请求，调用模型和视图

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818163348642.png" alt="image-20210818163348642" style="zoom:70%;" />

​	控制器（serlvlet）用来接收浏览器发送过来的请求，控制器调用模型（JavaBean）来获取数据，比如从数据库查询数据；控制器获取到数据后再交由视图（JSP）进行数据展示。

**MVC 好处：**

* 职责单一，互不影响。每个角色做它自己的事，各司其职。

* 有利于分工协作。

* 有利于组件重用

### 7.2  三层架构

​	三层架构是将我们的项目分成了三个层面，分别是 `表现层`、`业务逻辑层`、`数据访问层`。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818165439826.png" alt="image-20210818165439826" style="zoom:60%;" />

* 数据访问层：对数据库的CRUD基本操作
* 业务逻辑层：对业务逻辑进行封装，组合数据访问层层中基本功能，形成复杂的业务逻辑功能。例如 `注册业务功能` ，我们会先调用 `数据访问层` 的 `selectByName()` 方法判断该用户名是否存在，如果不存在再调用 `数据访问层` 的 `insert()` 方法进行数据的添加操作
* 表现层：接收请求，封装数据，调用业务逻辑层，响应数据

​	而整个流程是，浏览器发送请求，表现层的Servlet接收请求并调用业务逻辑层的方法进行业务逻辑处理，而业务逻辑层方法调用数据访问层方法进行数据的操作，依次返回到serlvet，然后servlet将数据交由 JSP 进行展示。

​	上图中的蓝色字是对对应的**层**进行封装的框架。

三层架构的每一层都有特有的包名称：

* 表现层： `com.itheima.controller` 或者 `com.itheima.web`
* 业务逻辑层：`com.itheima.service`
* 数据访问层：`com.itheima.dao` 或者 `com.itheima.mapper`

### 7.3  MVC 和 三层架构

​	MVC模式和三层架构有什么区别和联系？

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210818165808589.png" alt="image-20210818165808589" style="zoom:60%;" />

​	如上图上半部分是 MVC 模式，上图下半部分是三层架构。 `MVC 模式` 中的 C（控制器）和 V（视图）就是 `三层架构` 中的表现层，而 `MVC 模式` 中的 M（模型）就是 `三层架构` 中的 业务逻辑层 和 数据访问层。

​	可以将 `MVC 模式` 理解成是一个大的概念，而 `三层架构` 是对 `MVC 模式` 实现架构的思想。 那么我们以后按照要求将不同层的代码写在不同的包下，每一层里功能职责做到单一，将来如果将表现层的技术换掉，而业务逻辑层和数据访问层的代码不需要发生变化。