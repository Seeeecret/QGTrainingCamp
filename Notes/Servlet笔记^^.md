# Servlet笔记

![1627234763207](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627234763207.png)

* Servlet是JavaWeb最为核心的内容，它是Java提供的一门==动态==web资源开发技术。

* 使用Servlet就可以实现，根据不同的登录用户在页面上动态显示不同内容。

* Servlet是JavaEE规范之一，其实就是一个接口，将来我们需要定义Servlet类实现Servlet接口，并由web服务器运行Servlet

    ![1627234972853](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627234972853.png)

## 1.0	快速入门

​	建立一个简单的Servlet类并部署的操作为:

1. 创建Web项目`web-demo`，导入Servlet依赖坐标

```xml
<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>3.1.0</version>
    <!--
      此处为什么需要添加该标签?
      provided指的是在编译和测试过程中有效,最后生成的war包时不会加入
       因为Tomcat的lib目录中已经有servlet-api这个jar包，如果在生成war包的时候生效就会和Tomcat中的jar包冲突，导致报错
    -->
    <scope>provided</scope>
</dependency>
```

2. 创建:定义一个类，实现Servlet接口，并重写接口中所有方法，并在service方法中输入一句话

```java
package com.itheima.web;

import javax.servlet.*;
import java.io.IOException;

public class ServletDemo1 implements Servlet {

    public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
        System.out.println("servlet hello world~");
    }
    public void init(ServletConfig servletConfig) throws ServletException {

    }

    public ServletConfig getServletConfig() {
        return null;
    }

    public String getServletInfo() {
        return null;
    }

    public void destroy() { 

    }
}
```

3. 配置:在类上使用@WebServlet注解，配置该Servlet的访问路径

```java
@WebServlet("/demo1")
```

4. 访问:启动Tomcat,浏览器中输入URL地址访问该Servlet

```
http://localhost:8080/web-demo/demo1
```

5. 访问后，在控制台会打印`servlet hello world~` 说明servlet程序已经成功运行。

## 2.0	执行流程

​		<u>**Servlet**对象由web服务器创建，**Servlet**方法由web服务器调用</u>![1627236923139](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627236923139.png)

* 浏览器发出`http://localhost:8080/web-demo/demo1`请求，从请求中可以解析出三部分内容，分别是`localhost:8080`、`web-demo`、`demo1`
    * 根据`localhost:8080`可以找到要访问的Tomcat Web服务器
    * 根据`web-demo`可以找到部署在Tomcat服务器上的web-demo项目
    * 根据`demo1`可以找到要访问的是项目中的哪个Servlet类，根据@WebServlet后面的值进行匹配
* 找到ServletDemo1这个类后，Tomcat Web服务器就会为ServletDemo1这个类创建一个对象，然后调用对象中的service方法
    * ServletDemo1实现了Servlet接口，所以类中必然会重写service方法供Tomcat Web服务器进行调用
    * service方法中有ServletRequest和ServletResponse两个参数，ServletRequest封装的是请求数据，ServletResponse封装的是响应数据，后期我们可以通过这两个参数实现前后端的数据交互

### 2.1	生命周期

* 生命周期: 对象的生命周期指一个对象从被创建到被销毁的整个过程。

* Servlet运行在Servlet容器(web服务器)中，其生命周期由容器来管理，分为4个阶段：

    1. **加载和实例化**：默认情况下，当Servlet第一次被访问时，由容器创建Servlet对象

    > 默认情况，Servlet会在第一次访问被容器创建，但是如果创建Servlet比较耗时的话，那么第一个访问的人等待的时间就比较长，用户的体验就比较差，那么我们能不能把Servlet的创建放到服务器启动的时候来创建，具体如何来配置?
    >
    > @WebServlet(urlPatterns = "/demo1",loadOnStartup = 1)
    > loadOnstartup的取值有两类情况
    > 	（1）负整数:第一次访问时创建Servlet对象
    > 	（2）0或正整数:服务器启动时创建Servlet对象，数字越小优先级越高

    2. **初始化**：在Servlet实例化之后，容器将调用Servlet的init()方法初始化这个对象，完成一些如加载配置文件、创建连接等初始化的工作。该方法只调用一次
    3. **请求处理**：**每次**请求Servlet时，Servlet容器都会调用Servlet的service()方法对请求进行处理
    4. **服务终止**：当需要释放内存或者容器关闭时，容器就会调用Servlet实例的==destroy()==方法完成资源的释放。在destroy()方法调用之后，容器会释放这个Servlet实例，该实例随后会被Java的垃圾收集器所回收

### 2.2	生命周期中涉及的三个方法

​	三个方法，分别是 init()、service()、destroy()

- **init方法**在Servlet对象被创建的时候执行，只执行1次

- **service方法**在Servlet被访问的时候调用，每访问1次就调用1次

- **destroy方法**在Servlet对象被销毁的时候调用，只执行1次

​	*注:直接按红色方块结束服务器并不能使得此方法被执行。*



### 2.3	方法介绍

​	Servlet中总共有5个方法

* 初始化方法，在Servlet被创建时执行，只执行一次

```java
void init(ServletConfig config) 
```

* 提供服务方法， 每次Servlet被访问，都会调用该方法

```java
void service(ServletRequest req, ServletResponse res)
```

* 销毁方法，当Servlet被销毁时，调用该方法。在内存释放或服务器关闭时销毁Servlet

```java
void destroy() 
```

剩下的两个方法是:

* 获取Servlet信息

```java
String getServletInfo() 
//该方法用来返回Servlet的相关信息，没有什么太大的用处，一般我们返回一个空字符串即可
public String getServletInfo() {
    return "";
}
```

* 获取ServletConfig对象

```java
ServletConfig getServletConfig()
```

​	ServletConfig对象，在init方法的参数中有，而Tomcat Web服务器在创建Servlet对象的时候会调用init方法，必定会传入一个ServletConfig对象，我们只需要将服务器传过来的ServletConfig进行返回即可。



### 2.4	体系结构

​	想编写一个Servlet就必须要实现Servlet接口，重写接口中的5个方法，虽然已经能完成要求，但是编写起来还是比较麻烦的，有更简单方式来创建Servlet。

​	![1627240593506](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627240593506.png)

​	因为我们将来开发B/S架构的web项目，都是针对HTTP协议，所以我们自定义Servlet, 会继承HttpServlet。

​	具体的编写格式如下:

```java
@WebServlet("/demo4")
public class ServletDemo4 extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //TODO GET 请求方式处理逻辑
        System.out.println("get...");
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //TODO Post 请求方式处理逻辑
        System.out.println("post...");
    }
}
```

* 要想发送一个GET请求，请求该Servlet，只需要通过浏览器发送`http://localhost:8080/web-demo/demo4`,就能看到doGet方法被执行了
* 要想发送一个POST请求，请求该Servlet，单单通过浏览器是无法实现的，这个时候就需要编写一个form表单来发送请求，在webapp下创建一个`a.html`页面，内容如下:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
    <form action="/web-demo/demo4" method="post">
        <input name="username"/><input type="submit"/>
    </form>
</body>
</html>
```

​	为了简化开发，HttpServlet类已经为我们写好了根据不同类型的请求分流进行不同的do操作的的`service`方法

```java
protected void service(HttpServletRequest req, HttpServletResponse resp)
        throws ServletException, IOException
    {
        String method = req.getMethod();

        if (method.equals(METHOD_GET)) {
            long lastModified = getLastModified(req);
            if (lastModified == -1) {
                // servlet doesn't support if-modified-since, no reason
                // to go through further expensive logic
                doGet(req, resp);
            } else {
                long ifModifiedSince = req.getDateHeader(HEADER_IFMODSINCE);
                if (ifModifiedSince < lastModified) {
                    // If the servlet mod time is later, call doGet()
                    // Round down to the nearest second for a proper compare
                    // A ifModifiedSince of -1 will always be less
                    maybeSetLastModified(resp, lastModified);
                    doGet(req, resp);
                } else {
                    resp.setStatus(HttpServletResponse.SC_NOT_MODIFIED);
                }
            }

        } else if (method.equals(METHOD_HEAD)) {
            long lastModified = getLastModified(req);
            maybeSetLastModified(resp, lastModified);
            doHead(req, resp);

        } else if (method.equals(METHOD_POST)) {
            doPost(req, resp);
            
        } else if (method.equals(METHOD_PUT)) {
            doPut(req, resp);
            
        } else if (method.equals(METHOD_DELETE)) {
            doDelete(req, resp);
            
        } else if (method.equals(METHOD_OPTIONS)) {
            doOptions(req,resp);
            
        } else if (method.equals(METHOD_TRACE)) {
            doTrace(req,resp);
            
        } else {
            //
            // Note that this means NO servlet supports whatever
            // method was requested, anywhere on this server.
            //

            String errMsg = lStrings.getString("http.method_not_implemented");
            Object[] errArgs = new Object[1];
            errArgs[0] = method;
            errMsg = MessageFormat.format(errMsg, errArgs);
            
            resp.sendError(HttpServletResponse.SC_NOT_IMPLEMENTED, errMsg);
        }
    }
```

​	我们只需要继承HttpServlet类并重写`doGet`和`doPost`方法即可。



### 2.5	urlPattern配置

​	Servlet类编写好后，要想被访问到，就需要配置其**访问路径（urlPattern）**

* 一个Servlet,可以配置多个urlPattern

    ![1627272805178](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627272805178.png)

    ```java
    package com.itheima.web;
    
    import javax.servlet.ServletRequest;
    import javax.servlet.ServletResponse;
    import javax.servlet.annotation.WebServlet;
    
    /**
    * urlPattern: 一个Servlet可以配置多个访问路径
    */
    @WebServlet(urlPatterns = {"/demo7","/demo8"})
    public class ServletDemo7 extends MyHttpServlet {
    
        @Override
        protected void doGet(ServletRequest req, ServletResponse res) {
            
            System.out.println("demo7 get...");
        }
        @Override
        protected void doPost(ServletRequest req, ServletResponse res) {
        }
    }
    ```

    在浏览器上输入`http://localhost:8080/web-demo/demo7`,`http://localhost:8080/web-demo/demo8`这两个地址都能访问到ServletDemo7的doGet方法。

    

    #### 2.51	urlPattern配置规则

    * 精确匹配

        ![1627273174144](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627273174144.png)

        ```java
        /**
         * UrlPattern:
         * * 精确匹配
         */
        @WebServlet(urlPatterns = "/user/select")
        public class ServletDemo8 extends MyHttpServlet {
        
            @Override
            protected void doGet(ServletRequest req, ServletResponse res) {
        
                System.out.println("demo8 get...");
            }
            @Override
            protected void doPost(ServletRequest req, ServletResponse res) {
            }
        }
        ```

        访问路径`http://localhost:8080/web-demo/user/select`

    * 目录匹配

        ![1627273184095](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627273184095.png)

        ```java
        package com.itheima.web;
        
        import javax.servlet.ServletRequest;
        import javax.servlet.ServletResponse;
        import javax.servlet.annotation.WebServlet;
        
        /**
         * UrlPattern:
         * * 目录匹配: /user/*
         */
        @WebServlet(urlPatterns = "/user/*")
        public class ServletDemo9 extends MyHttpServlet {
        
            @Override
            protected void doGet(ServletRequest req, ServletResponse res) {
        
                System.out.println("demo9 get...");
            }
            @Override
            protected void doPost(ServletRequest req, ServletResponse res) {
            }
        }
        ```

        访问路径`http://localhost:8080/web-demo/user/任意`

        思考:

        1. 访问路径`http://localhost:8080/web-demo/user`是否能访问到demo9的doGet方法?
        2. 访问路径`http://localhost:8080/web-demo/user/a/b`是否能访问到demo9的doGet方法?
        3. 访问路径`http://localhost:8080/web-demo/user/select`是否能访问到demo9还是demo8的doGet方法?

        答案是: 能、能、demo8，进而我们可以得到的结论是`/user/*`中的`/*`代表的是零或多个层级访问目录同时精确匹配优先级要高于目录匹配。

    * 扩展名匹配

        ![1627273194118](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627273194118.png)

        ```java
        package com.itheima.web;
        
        import javax.servlet.ServletRequest;
        import javax.servlet.ServletResponse;
        import javax.servlet.annotation.WebServlet;
        
        /**
         * UrlPattern:
         * * 扩展名匹配: *.do
         */
        @WebServlet(urlPatterns = "*.do")
        public class ServletDemo10 extends MyHttpServlet {
        
            @Override
            protected void doGet(ServletRequest req, ServletResponse res) {
        
                System.out.println("demo10 get...");
            }
            @Override
            protected void doPost(ServletRequest req, ServletResponse res) {
            }
        }
        ```

        访问路径`http://localhost:8080/web-demo/任意.do`

        *注意:*

        1. 如果路径配置的不是扩展名，那么在路径的前面就必须要加`/`否则会报错

        ![1627274483755](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627274483755.png)

        2. 如果路径配置的是`*.do`,那么在*.do的前面不能加`/`,否则会报错

        ![1627274368245](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627274368245.png)

    * 任意匹配

        ![1627273201370](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627273201370.png)

        ```java
        package com.itheima.web;
        
        import javax.servlet.ServletRequest;
        import javax.servlet.ServletResponse;
        import javax.servlet.annotation.WebServlet;
        
        /**
         * UrlPattern:
         * * 任意匹配： /
         */
        @WebServlet(urlPatterns = "/")
        public class ServletDemo11 extends MyHttpServlet {
        
            @Override
            protected void doGet(ServletRequest req, ServletResponse res) {
        
                System.out.println("demo11 get...");
            }
            @Override
            protected void doPost(ServletRequest req, ServletResponse res) {
            }
        }
        ```

        访问路径`http://localhost:8080/demo-web/任意`

        ```java
        package com.itheima.web;
        
        import javax.servlet.ServletRequest;
        import javax.servlet.ServletResponse;
        import javax.servlet.annotation.WebServlet;
        
        /**
         * UrlPattern:
         * * 任意匹配： /*
         */
        @WebServlet(urlPatterns = "/*")
        public class ServletDemo12 extends MyHttpServlet {
        
            @Override
            protected void doGet(ServletRequest req, ServletResponse res) {
        
                System.out.println("demo12 get...");
            }
            @Override
            protected void doPost(ServletRequest req, ServletResponse res) {
            }
        }
        
        ```

        访问路径`http://localhost:8080/demo-web/任意

        注意:`/`和`/*`的区别?

        1. 当我们的项目中的Servlet配置了 "/",会覆盖掉tomcat中的DefaultServlet,当其他的url-pattern都匹配不上时都会走这个Servlet

        2. 当我们的项目中配置了"/*",意味着匹配任意访问路径

        3. DefaultServlet是用来处理静态资源，如果配置了"/"会把默认的覆盖掉，就会引发请求静态资源的时候没有走默认的而是走了自定义的Servlet类，最终导致静态资源不能被访问

**小结**

1. urlPattern总共有四种配置方式，分别是精确匹配、目录匹配、扩展名匹配、任意匹配

2. 五种配置的优先级为 精确匹配 > 目录匹配> 扩展名匹配 > /* > / ,无需记，以最终运行结果为准。



### 2.6	XML配置

​	之前使用@WebServlet配置Servlet，这个是Servlet从3.0版本后开始支持的注解配置，3.0版本前只支持XML配置文件的配置方法。

​	XML配置省略。