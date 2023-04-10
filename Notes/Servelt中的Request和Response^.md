# Servelt中的Request和Response

​	Request是请求对象，Response是响应对象。

![1628735746602](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628735746602.png)

* request:获取请求数据
    * 浏览器会发送HTTP请求到后台服务器[Tomcat]
    * HTTP的请求中会包含很多请求数据[请求行+请求头+请求体]
    * 后台服务器[Tomcat]会对HTTP请求中的数据进行解析并把解析结果存入到一个对象中
    * 所存入的对象即为request对象，所以我们可以从request对象中获取请求的相关参数
    * 获取到数据后就可以继续后续的业务，比如获取用户名和密码就可以实现登录操作的相关业务
* response:设置响应数据
    * 业务处理完后，后台就需要给前端返回业务处理的结果即响应数据
    * 把响应数据封装到response对象中
    * 后台服务器[Tomcat]会解析response对象,按照[响应行+响应头+响应体]格式拼接结果
    * 浏览器最终解析结果，把内容展示在浏览器给用户浏览

## 1.0	Request对象

​	首先，我们先来看下Request的继承体系:

![1628740441008](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628740441008.png)

​	从上图中可以看出，ServletRequest和HttpServletRequest都是Java提供的，所以我们可以打开JavaEE提供的API文档[参考: 资料/JavaEE7-api.chm],打开后可以看到:

![1628741839475](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628741839475.png)

​	所以ServletRequest和HttpServletRequest是继承关系，并且两个都是接口，接口是无法创建对象，这个时候就引发了下面这个问题:

![1628742224589](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628742224589.png)

​	这个时候，我们就需要用到Request继承体系中的`RequestFacade`:

* 该类实现了HttpServletRequest接口，也间接实现了ServletRequest接口。
* Servlet类中的service方法、doGet方法或者是doPost方法最终都是由Web服务器[Tomcat]来调用的，所以Tomcat提供了方法参数接口的具体实现类，并完成了对象的创建
* 要想了解RequestFacade中都提供了哪些方法，我们可以直接查看JavaEE的API文档中关于ServletRequest和HttpServletRequest的接口文档，因为RequestFacade实现了其接口就需要重写接口中的方法

​	所以说是Tmocat解析请求数据，并将数据封装为request对象,并且创建request对象传递到service方法。



### 1.1	Request获取请求数据

​	HTTP请求数据总共分为三部分内容，分别是请求行、请求头、请求体，对于这三部分内容的数据，分别该如何获取，首先我们先来学习请求行数据如何获取?

#### 1.11	获取请求行数据

​	请求行包含三块内容，分别是`请求方式`、`请求资源路径`、`HTTP协议及版本`

![1628748240075](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628748240075.png)

​	对于这三部分内容，request对象都提供了对应的API方法来获取，具体如下:

* 获取请求方式: `GET`

```
String getMethod()
```

* 获取虚拟目录(项目访问路径): `/request-demo`

```
String getContextPath()
```

* 获取URL(统一资源定位符): `http://localhost:8080/request-demo/req1`

```
StringBuffer getRequestURL()
```

* 获取URI(统一资源标识符): `/request-demo/req1`

```
String getRequestURI()
```

* 获取请求参数(GET方式): `username=zhangsan&password=123`

```
String getQueryString()
```

​	代码样例:

```java
/**
 * request 获取请求数据
 */
@WebServlet("/req1")
public class RequestDemo1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        // String getMethod()：获取请求方式： GET
        String method = req.getMethod();
        System.out.println(method);//GET
        // String getContextPath()：获取虚拟目录(项目访问路径)：/request-demo
        String contextPath = req.getContextPath();
        System.out.println(contextPath);
        // StringBuffer getRequestURL(): 获取URL(统一资源定位符)：http://localhost:8080/request-demo/req1
        StringBuffer url = req.getRequestURL();
        System.out.println(url.toString());
        // String getRequestURI()：获取URI(统一资源标识符)： /request-demo/req1
        String uri = req.getRequestURI();
        System.out.println(uri);
        // String getQueryString()：获取请求参数（GET方式）
        String queryString = req.getQueryString();
        System.out.println(queryString);
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
}
```

​	启动服务器，访问`http://localhost:8080/request-demo/req1?username=zhangsan&passwrod=123`，获取的结果如下:

![1628762794935](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628762794935.png)

### 1.2	获取请求头数据

​	对于请求头的数据，格式为`key: value`如下:

![1628768652535](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628768652535.png)

​	所以根据请求头名称获取对应值的方法为:

```
String getHeader(String name)
```

​	接下来，在代码中如果想要获取客户端浏览器的版本信息，则可以使用

```java
/**
 * request 获取请求数据
 */
@WebServlet("/req2")
public class RequestDemo2 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //获取请求头: user-agent: 浏览器的版本信息
        String agent = req.getHeader("user-agent");
		System.out.println(agent);
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
}

```

​	重新启动服务器后，`http://localhost:8080/request-demo/req2?username=zhangsan&passwrod=123`，获取的结果如下:

```html
Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/111.0
```



### 1.3	获取请求体数据

​	浏览器在发送GET请求的时候是没有请求体的，所以需要把请求方式变更为POST，请求体中的数据格式如下:

![1628768665185](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628768665185.png)

对于请求体中的数据，Request对象提供了如下两种方式来获取其中的数据，分别是:

* 获取字节输入流，如果前端发送的是字节数据，比如传递的是文件数据，则使用该方法

```java
ServletInputStream getInputStream()
//该方法可以获取字节
```

* 获取字符输入流，如果前端发送的是纯文本数据，则使用该方法

```java
BufferedReader getReader()
```

具体实现的步骤如下:

1. 准备一个页面，在页面中添加form表单,用来发送post请求

2. 在Servlet的doPost方法中获取请求体数据

3. 在doPost方法中使用request的getReader()或者getInputStream()来获取

4. 访问测试

1. 在项目的webapp目录下添加一个html页面，名称为：`req.html`

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<!-- 
    action:form表单提交的请求地址
    method:请求方式，指定为post
-->
<form action="/request-demo/req1" method="post">
    <input type="text" name="username">
    <input type="password" name="password">
    <input type="submit">
</form>
</body>
</html>
```

2. 在Servlet的doPost方法中获取数据

```java
/**
 * request 获取请求数据
 */
@WebServlet("/req1")
public class RequestDemo1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //在此处获取请求体中的数据
    }
}
```

3. 调用getReader()或者getInputStream()方法，因为目前前端传递的是纯文本数据，所以我们采用getReader()方法来获取

```java
/**
 * request 获取请求数据
 */
@WebServlet("/req1")
public class RequestDemo1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
         //获取post 请求体：请求参数
        //1. 获取字符输入流
        BufferedReader br = req.getReader();
        //2. 读取数据
        String line = br.readLine();
        System.out.println(line);
    }
}
```

​	注意:

​	BufferedReader流是通过request对象来获取的，当请求完成后request对象就会被销毁，request对象被销毁后，BufferedReader流就会自动关闭，所以此处就不需要手动关闭流了。

4. 启动服务器，通过浏览器访问`http://localhost:8080/request-demo/req.html`

![1628770516387](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628770516387.png)

​	点击`提交`按钮后，就可以在控制台看到前端所发送的请求数据

![1628770585480](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628770585480.png)

​	**小结**

​	HTTP请求数据中包含了`请求行`、`请求头`和`请求体`，针对这三部分内容，Request对象都提供了对应的API方法来获取对应的值:

* **请求行**
    * getMethod()获取请求方式
    * getContextPath()获取项目访问路径
    * getRequestURL()获取请求URL
    * getRequestURI()获取请求URI
    * getQueryString()获取GET请求方式的请求参数
* **请求头**
    * getHeader(String name)根据请求头名称获取其对应的值
* **请求体**
    * 注意: 浏览器发送的POST请求才有请求体
    * 如果是纯文本数据:getReader()
    * 如果是字节数据如文件数据:getInputStream()



### 1.4	设计通用方法统一处理两种请求方式的方法

​	request对象已经将上述获取请求参数的方法进行了封装，并且request提供的方法实现的功能更强大。比如

`getParameter`方法:

​	(1)根据不同的请求方式获取请求参数，获取的内容如下:

![1628778931277](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628778931277.png)

​	(2)把获取到的内容进行分割，内容如下:

![1628779067793](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628779067793.png)

​	(3)把分割后端数据，存入到一个Map集合中:

![1628779368501](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628779368501.png)

**注意**:因为参数的值可能是一个，也可能有多个，所以Map的值的类型为String数组。

基于上述理论，request对象为我们提供了如下方法:

* 获取所有参数Map集合

```
Map<String,String[]> getParameterMap()
```

* 根据名称获取参数值（数组）

```
String[] getParameterValues(String name)
```

* 根据名称获取参数值(单个值)

```
String getParameter(String name)
```

​	接下来，我们通过案例来把上述的三个方法进行实例演示:

1. 修改req.html页面，添加爱好选项，爱好可以同时选多个

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<form action="/request-demo/req2" method="get">
    <input type="text" name="username"><br>
    <input type="password" name="password"><br>
    <input type="checkbox" name="hobby" value="1"> 游泳
    <input type="checkbox" name="hobby" value="2"> 爬山 <br>
    <input type="submit">

</form>
</body>
</html>
```

![1628780937599](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628780937599.png)

2. 在Servlet代码中获取页面传递GET请求的参数值

​	2.1 获取GET方式的所有请求参数

```java
/**
 * request 通用方式获取请求参数
 */
@WebServlet("/req2")
public class RequestDemo2 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //GET请求逻辑
        System.out.println("get....");
        //1. 获取所有参数的Map集合
        Map<String, String[]> map = req.getParameterMap();
        for (String key : map.keySet()) {
            // username:zhangsan lisi
            System.out.print(key+":");

            //获取值
            String[] values = map.get(key);
            for (String value : values) {
                System.out.print(value + " ");
            }

            System.out.println();
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
}
```

​	获取的结果为:

![1628780965283](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628780965283.png)

​	 2.2 获取GET请求参数中的爱好，结果是数组值

```java
/**
 * request 通用方式获取请求参数
 */
@WebServlet("/req2")
public class RequestDemo2 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //GET请求逻辑
        //...
        System.out.println("------------");
        String[] hobbies = req.getParameterValues("hobby");
        for (String hobby : hobbies) {
            System.out.println(hobby);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
}
```

​	获取的结果为:

![1628781031437](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628781031437.png)

​	 2.3 获取GET请求参数中的用户名和密码，结果是单个值

```java
/**
 * request 通用方式获取请求参数
 */
@WebServlet("/req2")
public class RequestDemo2 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //GET请求逻辑
        //...
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        System.out.println(username);
        System.out.println(password);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    }
}
```

​	获取的结果为:

![1628781176434](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628781176434.png)

3. 在Servlet代码中获取页面传递POST请求的参数值

3.1 将req.html页面form表单的提交方式改成post

3.2 将doGet方法中的内容复制到doPost方法中即可

**小结**

* req.getParameter()方法使用的频率会比较高

* 以后我们再写代码的时候，就只需要按照如下格式来编写:

```java
public class RequestDemo1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
       //采用request提供的获取请求参数的通用方式来获取请求参数
       //编写其他的业务代码...
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req,resp);
    }
}
```



### 1.5 IDEA快速创建Servlet

​	使用通用方式获取请求参数后，屏蔽了GET和POST的请求方式代码的不同，则代码可以定义如下格式:

![1628781419752](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628781419752.png)

​	由于格式固定，所以我们可以使用IDEA提供的模板来制作一个Servlet的模板，这样我们后期在创建Servlet的时候就会更高效，具体如何实现:

​	(1)按照自己的需求，修改Servlet创建的模板内容

![1628781545912](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628781545912.png)

​	（2）使用servlet模板创建Servlet类

![1628782117420](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628782117420.png)

### 1.6	Tomcat8.0以前的中文乱码问题

​	虽然我用的9.0已经不存在这个问题，但是解决类似问题的思路我觉得还是需要学习一下。

​	在Tomcat7及其以前版本中:	

* POST请求和GET请求的参数中如果有中文，后台接收数据就会出现中文乱码问题

    GET请求在Tomcat8.0以后的版本就不会出现了

* POST请求解决方案是:设置输入流的编码

    ```
    request.setCharacterEncoding("UTF-8");
    注意:设置的字符集要和页面保持一致
    ```

* 通用方式（GET/POST）：需要先解码，再编码

    ```
    new String(username.getBytes("ISO-8859-1"),"UTF-8");
    ```

2. URL编码实现方式:

* 编码:

    ```
    URLEncoder.encode(str,"UTF-8");
    ```

* 解码:

    ```
    URLDecoder.decode(s,"ISO-8859-1");
    ```

### 1.7	Request请求转发

​	**请求转发(forward)**是一种在服务器内部的资源跳转方式。

![1628851404283](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628851404283.png)

1. 浏览器发送请求给服务器，服务器中对应的资源A接收到请求

2. 资源A处理完请求后将请求发给资源B

3. 资源B处理完后将结果响应给浏览器

4. 请求从资源A到资源B的过程就叫**请求转发**

#### 1.71	实现方式

```java
req.getRequestDispatcher("/req6").forward(req,resp); //在/req5的Servlet中
```

​	为了在请求转发中传递或共享数据，我们需要使用**Request对象和它的方法**:

* 存储数据到request域[范围,数据是存储在request对象中

```
void setAttribute(String name,Object o);
```

* 根据key获取值

```
Object getAttribute(String name);
```

* 根据key删除该键值对

```
void removeAttribute(String name);
```

#### 1.72	特点

* 浏览器地址栏路径不发生变化

    ​	虽然后台从`/req5`转发到`/req6`,但是浏览器的地址一直是`/req5`,未发生变化

    ![1628857365153](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628857365153.png)

* 只能转发到当前服务器的内部资源

    ​	不能从一个服务器通过转发访问另一台服务器

* 即使只有一次请求，也可以在转发资源间使用request共享数据



## 2.0	Response对象

![1628857632899](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628857632899.png)

​	复习一下:

* Request:使用request对象来获取请求数据
* Response:使用response对象来设置响应数据

​	Reponse的继承体系和Request的继承体系也非常相似:

![1628857761317](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628857761317.png)

### 2.1	Response设置响应数据功能介绍

​	HTTP响应数据总共分为三部分内容，分别是响应行、响应头、响应体，对于这三部分内容的数据，respone对象都提供了哪些方法来进行设置?

1. 响应行

![1628858926498](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628858926498.png)

​	对于响应行，比较常用的就是设置响应状态码:

```
void setStatus(int sc);
```

2. 响应头

![1628859051368](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628859051368.png)

​	设置响应头键值对：

```
void setHeader(String name,String value);
```

3. 响应体

![1628859268095](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628859268095.png)

​	对于响应体，是通过字符、字节输出流的方式往浏览器写，

​	获取字符输出流:

```
PrintWriter getWriter();
```

​	获取字节输出流

```
ServletOutputStream getOutputStream();
```

​	介绍完这些方法后，后面我们会通过案例把这些方法都用一用，首先先来完成下重定向的功能开发。

### 2.2	Respones请求重定向

1. Response**重定向(redirect)**:一种资源跳转方式。

![1628859860279](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628859860279.png)

​	(1)浏览器发送请求给服务器，服务器中对应的资源A接收到请求

​	(2)资源A现在无法处理该请求，就会给浏览器响应一个302的状态码+location的一个访问资源B的路径

​	(3)浏览器接收到响应状态码为302就会重新发送请求到location对应的访问地址去访问资源B

​	(4)资源B接收到请求后进行处理并最终给浏览器响应结果，这整个过程就叫==重定向==

2. 重定向的实现方式:

```java
resp.setStatus(302);
resp.setHeader("location","资源B的访问路径");// 虚拟目录: 包名/虚拟目录
```

​	具体如何来使用，我们先来看下需求:

​	上面这个版本有些麻烦,其实Java中封装好了相关的方法:

```java
resposne.sendRedirect("/request-demo/resp2");
```

3. 重定向的特点

* 浏览器地址栏路径发送变化

    当进行重定向访问的时候，由于是由浏览器发送的两次请求，所以地址会发生变化

    ![1628861893130](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628861893130.png)

* 可以重定向到任何位置的资源(服务内容、外部均可)

    因为第一次响应结果中包含了浏览器下次要跳转的路径，所以这个路径是可以任意位置资源。

* 两次请求，不能在多个资源使用request共享数据

​	**重定向和请求转发的特点对比**

![1628862170296](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628862170296.png)

### 2.3 路径问题

1. 问题1：转发的时候路径上没有加`/request-demo`而重定向加了，那么到底什么时候需要加，什么时候不需要加呢?

![1628862652700](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628862652700.png)

其实判断的依据很简单，只需要记住下面的规则即可:

* <u>**浏览器使用:需要加虚拟目录(项目访问路径)**</u>
* <u>**服务端使用:不需要加虚拟目录**</u>

对于转发来说，因为是在服务端进行的，所以不需要加虚拟目录

对于重定向来说，路径最终是由浏览器来发送请求，就需要添加虚拟目录。

掌握了这个规则，接下来就通过一些练习来强化下知识的学习:

* `<a href='路劲'>`
* `<form action='路径'>`
* req.getRequestDispatcher("路径")
* resp.sendRedirect("路径")

答案:

```
1.超链接，从浏览器发送，需要加
2.表单，从浏览器发送，需要加
3.转发，是从服务器内部跳转，不需要加
4.重定向，是由浏览器进行跳转，需要加。
```

2. 问题2：在重定向的代码中，`/request-demo`是固定编码的，如果后期通过Tomcat插件配置了项目的访问路径，那么所有需要重定向的地方都需要重新修改，该如何优化?

![1628863270545](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1628863270545.png)

​	可以在代码中动态去获取项目访问的虚拟目录，具体如何获取，可以借助request对象中的**getContextPath()方法**，修改后的代码如下:

```java
@WebServlet("/resp1")
public class ResponseDemo1 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        System.out.println("resp1....");

        //简化方式完成重定向
        //动态获取虚拟目录
        String contextPath = request.getContextPath();
        response.sendRedirect(contextPath+"/resp2");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        this.doGet(request, response);
    }
}
```

​	重新启动访问测试，功能依然能够实现，此时就可以动态获取项目访问的虚拟路径，从而降低代码的耦合度。