# HTTP笔记

​	HyperText Transfer Protocol(超文本传输协议), 规定了浏览器和服务器之间**数据传输的规则**[^1]。学习HTTP主要就是学习请求和响应数据的具体格式内容。

​	**HTTP协议特点**

HTTP协议有它自己的一些特点，分别是:

* 基于TCP协议: 面向连接，安全

    TCP是一种面向连接的(建立连接之前是需要经过三次握手)、可靠的、基于字节流的传输层通信协议，在数据传输方面更安全。

* 基于请求-响应模型的:一次请求对应一次响应

    请求和响应是一一对应关系

* HTTP协议是无状态协议:对于事物处理没有记忆能力。每次请求-响应都是独立的

    无状态指的是客户端发送HTTP请求给服务端之后，服务端根据请求响应数据，响应完后，不会记录任何信息。这种特性有优点也有缺点，

    * 缺点:多次请求间不能共享数据
    * 优点:速度快

    请求之间无法共享数据会引发的问题，如:

    * 京东购物，`加入购物车`和`去购物车结算`是两次请求，
    * HTTP协议的无状态特性，加入购物车请求响应结束后，并未记录加入购物车是何商品
    * 发起去购物车结算的请求后，因为无法获取哪些商品加入了购物车，会导致此次请求无法正确展示数据

    具体使用的时候，我们发现京东是可以正常展示数据的，原因是Java早已考虑到这个问题，并提出了使用`会话技术(Cookie、Session)`来解决这个问题。

## 1.0	请求数据格式

### 1.1	格式介绍

请求数据总共分为三部分内容，分别是请求行、请求头、请求体

![1627050004221](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627050004221.png)

* 请求行: HTTP请求中的第一行数据，请求行包含三块内容，分别是 GET[请求方式] /[请求URL路径] HTTP/1.1[HTTP协议及版本]

    请求方式有七种,最常用的是GET和POST

* 请求头: 第二行开始，格式为key: value形式

    请求头中会包含若干个属性，常见的HTTP请求头有:

    ```
    Host: 表示请求的主机名
    User-Agent: 浏览器版本,例如Chrome浏览器的标识类似Mozilla/5.0 ...Chrome/79，IE浏览器的标识类似Mozilla/5.0 (Windows NT ...)like Gecko；
    Accept：表示浏览器能接收的资源类型，如text/*，image/*或者*/*表示所有；
    Accept-Language：表示浏览器偏好的语言，服务器可以据此返回不同语言的网页；
    Accept-Encoding：表示浏览器可以支持的压缩类型，例如gzip, deflate等。
    ```

     **这些数据有什么用处?**

    举例说明:服务端可以根据请求头中的内容来获取客户端的相关信息，有了这些信息服务端就可以处理不同的业务需求，比如:

    * 不同浏览器解析HTML和CSS标签的结果会有不一致，所以就会导致相同的代码在不同的浏览器会出现不同的效果
    * 服务端根据客户端请求头中的数据获取到客户端的浏览器类型，就可以根据不同的浏览器设置不同的代码来达到一致的效果
    * 这就是我们常说的浏览器兼容问题

* 请求体: POST请求的最后一部分，存储请求参数

    ![1627050930378](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627050930378.png)

    如上图红线框的内容就是请求体的内容，请求体和请求头之间是有一个空行隔开。此时浏览器发送的是POST请求，为什么不能使用GET呢?这时就需要回顾GET和POST两个请求之间的区别了:

    * GET请求请求参数在请求行中，没有请求体，POST请求请求参数在请求体中



### 1.2	实例演示

把 `代码\http` 拷贝到IDEA的工作目录中，比如`D:\workspace\web`目录，

![1627278511902](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627278511902.png)

使用IDEA打开

![1627278583127](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627278583127.png)

打开后，可以点击项目中的`html\19-表单验证.html`，使用浏览器打开，通过修改页面中form表单的method属性来测试GET请求和POST请求的参数携带方式。

![1627278725007](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627278725007.png)



**小结**:

1. 请求数据中包含三部分内容，分别是请求行、请求头和请求体

2. POST请求数据在请求体中，GET请求数据在请求行上

## 2.0	响应数据格式

### 2.1	格式介绍

响应数据总共分为三部分内容，分别是响应行、响应头、响应体

![1627053710214](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627053710214.png)

* 响应行：响应数据的第一行,响应行包含三块内容，分别是 HTTP/1.1[HTTP协议及版本] 200[响应状态码] ok[状态码的描述]

* 响应头：第二行开始，格式为key：value形式

    响应头中会包含若干个属性，常见的HTTP响应头有:

    ```
    Content-Type：表示该响应内容的类型，例如text/html，image/jpeg；
    Content-Length：表示该响应内容的长度（字节数）；
    Content-Encoding：表示该响应压缩算法，例如gzip；
    Cache-Control：指示客户端应如何缓存，例如max-age=300表示可以最多缓存300秒
    ```

* 响应体： 最后一部分。存放响应数据

    上图中<html>...</html>这部分内容就是响应体，它和响应头之间有一个空行隔开。

#### 2.11	响应状态码

参考: 资料/1.HTTP/《响应状态码.md》

关于响应状态码，我们先主要认识三个状态码，其余的等后期用到了再去掌握:

* 200  ok 客户端请求成功
* 404  Not Found 请求资源不存在
* 500 Internal Server Error 服务端发生不可预期的错误

**小结**

1. 响应数据中包含三部分内容，分别是响应行、响应头和响应体

2. 掌握200，404，500这三个响应状态码所代表含义，分布是成功、所访问资源不存在和服务的错误



# 3.0	Tomcat

## 3.1 简介

### 3.11 什么是Web服务器

​	Web服务器是一个应用程序（软件），对HTTP协议的操作进行封装，使得程序员不必直接对协议进行操作，让Web开发更加便捷。主要功能是"提供网上信息浏览服务"。

![1627058356051](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627058356051.png)

​	 Web服务器是安装在服务器端的一款软件，将来我们把自己写的Web项目部署到Web Tomcat服务器软件中，当Web服务器软件启动后，部署在Web服务器软件中的页面就可以直接通过浏览器来访问了。

**Web服务器软件使用步骤**

* 准备静态资源
* 下载安装Web服务器软件
* 将静态资源部署到Web服务器上
* 启动Web服务器使用浏览器访问对应的资源

​	上述内容在演示的时候，使用的是Apache下的Tomcat软件，至于Tomcat软件如何使用，后面会详细的讲到。而对于Web服务器来说，实现的方案有很多，Tomcat只是其中的一种，而除了Tomcat以外，还有很多优秀的Web服务器，比如:

![1627060368806](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627060368806.png)





​	Tomcat就是一款软件，我们主要是以学习如何去使用为主。具体我们会从以下这些方向去学习:

1. 简介: 初步认识下Tomcat

2. 基本使用: 安装、卸载、启动、关闭、配置和项目部署，这些都是对Tomcat的基本操作

3. IDEA中如何创建Maven Web项目

4. IDEA中如何使用Tomcat,后面这两个都是我们以后开发经常会用到的方式

## 3.2	Tomcat的相关概念:

* Tomcat是Apache软件基金会一个核心项目，是一个开源免费的轻量级Web服务器，支持Servlet/JSP少量JavaEE规范。

* 概念中提到了JavaEE规范，那什么又是JavaEE规范呢?

    JavaEE: Java Enterprise Edition,Java企业版。指Java企业级开发的技术规范总和。包含13项技术规范:JDBC、JNDI、EJB、RMI、JSP、Servlet、XML、JMS、Java IDL、JTS、JTA、JavaMail、JAF。

* 因为Tomcat支持Servlet/JSP规范，所以Tomcat也被称为Web容器、Servlet容器。Servlet需要依赖Tomcat才能运行。

* Tomcat的官网: https://tomcat.apache.org/ 从官网上可以下载对应的版本进行使用。

**Tomcat的LOGO**

![1627176045795](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627176045795.png)

**小结**

通过这一节的学习，我们需要掌握以下内容:

1. Web服务器的作用

> 封装HTTP协议操作，简化开发
>
> 可以将Web项目部署到服务器中，对外提供网上浏览服务

2. Tomcat是一个轻量级的Web服务器，支持Servlet/JSP少量JavaEE规范，也称为Web容器，Servlet容器。

## 3.3	基本使用

### 3.33	启动

双击: bin\startup.bat

![1627179006011](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627179006011.png)

​	启动后，通过浏览器访问 `http://localhost:8080`能看到Apache Tomcat的内容就说明Tomcat已经启动成功。

![1627199957728](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627199957728.png)

*注意: 启动的过程中，控制台有中文乱码，需要修改conf/logging.prooperties*

![1627199827589](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627199827589.png)

### 3.34	关闭

​	关闭有三种方式 

* 直接x掉运行窗口:强制关闭[不建议]
* bin\shutdown.bat：正常关闭
* ctrl+c： 正常关闭

### 3.35	配置

​	**修改端口**

* Tomcat默认的端口是8080，要想修改Tomcat启动的端口号，需要修改 conf/server.xml

![1627200509883](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627200509883.png)

*注: HTTP协议默认端口号为80，如果将Tomcat端口号改为80，则将来访问Tomcat时，将不用输入端口号。*

​	**启动时可能出现的错误**

* Tomcat的端口号取值范围是0-65535之间任意未被占用的端口，如果设置的端口号被占用，启动的时候就会包如下的错误

    ![1627200780590](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627200780590.png)

* Tomcat启动的时候，启动窗口一闪而过: 需要检查JAVA_HOME环境变量是否正确配置

![1627201248802](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627201248802.png)

### 3.36	部署

* Tomcat部署项目： 将项目放置到webapps目录下，即部署完成。

    * 将 `资料/2. Tomcat/hello` 目录拷贝到Tomcat的webapps目录下

    * 通过浏览器访问`http://localhost/hello/a.html`，能看到下面的内容就说明项目已经部署成功。

        ![1627201572748](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627201572748.png)

        但是呢随着项目的增大，项目中的资源也会越来越多，项目在拷贝的过程中也会越来越费时间，该如何解决呢?

* 一般JavaWeb项目会被打包称==war==包，然后将war包放到Webapps目录下，Tomcat会自动解压缩war文件

    * 将 `资料/2. Tomcat/haha.war`目录拷贝到Tomcat的webapps目录下

    * Tomcat检测到war包后会自动完成解压缩，在webapps目录下就会多一个haha目录

    * 通过浏览器访问`http://localhost/haha/a.html`，能看到下面的内容就说明项目已经部署成功。

        ![1627201868752](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627201868752.png)

​	至此，Tomcat的部署就已经完成了，至于如何获得项目对应的war包，后期我们会借助于IDEA工具来生成。

## 3.4	Maven创建Web项目

​	以后Tomcat中运行的绝大多数都是Web项目，而使用Maven工具能更加简单快捷的把Web项目给创建出来。

​	在真正创建Maven Web项目之前，我们先要知道Web项目长什么样子。

### 3.41	Web项目结构

​	Web项目的结构分为:开发中的项目和开发完可以部署的Web项目,这两种项目的结构是不一样的，我们一个个来介绍下:

* Maven Web项目结构: 开发中的项目

    ![1627202865978](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627202865978.png)

* 开发完成部署的Web项目

    ![1627202903750](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627202903750.png)

    * 开发项目通过执行Maven打包命令package可以获取到部署的Web项目目录
    * 编译后的Java字节码文件和resources的资源文件，会被放到WEB-INF下的classes目录下
    * pom.xml中依赖坐标对应的jar包，会被放入WEB-INF下的lib目录下

### 3.42	创建Maven Web项目的方式

​	创建Maven Web项目的方式分为两种:

1. 使用**骨架(archetype)**

​		创建后补全缺失了小部分目录结构,（可能）调整删除pom.xml中的多余内容即可

2. 不使用**骨架**

​		在pom.xml设置打包方式为war，补全大部分缺失的webapp的目录结构并补齐Maven Web项目缺失WEB-INF/web.xml的目录结构。

​	有选项设置可以实现快速补齐:

![1627229676800](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627229676800.png)

​	最终项目结构如下:



![1627229478030](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627229478030.png)

​	上述两种方式，创建的web项目，都不是很全，需要手动补充内容,根据各自的喜好来选择使用即可。

## 3.5	IDEA使用Tomcat

* Maven Web项目创建成功后，通过Maven的package命令可以将项目打包成war包，将war文件拷贝到Tomcat的webapps目录下，启动Tomcat就可以将项目部署成功，然后通过浏览器进行访问即可。
* 然而我们在开发的过程中，项目中的内容会经常发生变化，如果按照上面这种方式来部署测试，是非常不方便的，下面是在IDEA中使用Tomcat提高效率的方法:
    * 在IDEA中集成使用Tomcat有两种方式，分别是: 集成本地Tomcat==和Tomcat Maven插件


### 3.5.1 集成本地Tomcat

目标: 将刚才本地安装好的Tomcat8集成到IDEA中，完成项目部署，具体的实现步骤

1. 打开添加本地Tomcat的面板

    ![1627229992900](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627229992900.png)

2. 指定本地Tomcat的具体路径

    ![1627230313062](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627230313062.png)

3. 修改Tomcat的名称，此步骤可以不改，只是让名字看起来更有意义，HTTP port中的端口也可以进行修改，比如把8080改成80

    ![1627230366658](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627230366658.png)

4. 将开发项目部署项目到Tomcat中

    ![1627230913259](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627230913259.png)

    扩展内容： xxx.war和 xxx.war exploded这两种部署项目模式的区别?

    * war模式是将WEB工程打成war包，把war包发布到Tomcat服务器上

    * war exploded模式是将WEB工程以当前文件夹的位置关系发布到Tomcat服务器上
    * war模式部署成功后，Tomcat的webapps目录下会有部署的项目内容
    * war exploded模式部署成功后，Tomcat的webapps目录下没有，而使用的是项目的target目录下的内容进行部署
    * 建议大家都选war模式进行部署，更符合项目部署的实际情况

5. 部署成功后，就可以启动项目，为了能更好的看到启动的效果，可以在webapp目录下添加a.html页面

    ![1627233265351](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627233265351.png)

6. 启动成功后，可以通过浏览器进行访问测试

    ![1627232743706](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627232743706.png)

7. 最终的注意事项

    ![1627232916624](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627232916624.png)


 ### 3.52	Tomcat Maven插件

在IDEA中使用本地Tomcat进行项目部署，相对来说步骤比较繁琐，所以我们需要一种更简便的方式来替换它，那就是直接使用Maven中的Tomcat插件来部署项目，具体的实现步骤，只需要两步，分别是:

1. 在pom.xml中添加Tomcat插件

    ```xml
    <build>
        <plugins>
        	<!--Tomcat插件 -->
            <plugin>
                <groupId>org.apache.tomcat.maven</groupId>
                <artifactId>tomcat7-maven-plugin</artifactId>
                <version>2.2</version>
            </plugin>
        </plugins>
    </build>
    ```

2. 使用Maven Helper插件快速启动项目，选中项目，右键-->Run Maven --> tomcat7:run

![1627233963315](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/1627233963315.png)

​	注意:

* 如果选中项目并右键点击后，看不到Run Maven和Debug Maven，这个时候就需要在IDEA中下载Maven Helper插件，具体的操作方式为: File --> Settings --> Plugins --> Maven Helper ---> Install,安装完后按照提示重启IDEA，就可以看到了。

* Maven Tomcat插件目前只有Tomcat7版本，没有更高的版本可以使用
* 使用Maven Tomcat插件，要想修改Tomcat的端口和访问路径，可以直接修改pom.xml

```xml
<build>
    <plugins>
    	<!--Tomcat插件 -->
        <plugin>
            <groupId>org.apache.tomcat.maven</groupId>
            <artifactId>tomcat7-maven-plugin</artifactId>
            <version>2.2</version>
            <configuration>
            	<port>80</port><!--访问端口号 -->
                <!--项目访问路径
					未配置访问路径: http://localhost:80/tomcat-demo2/a.html
					配置/后访问路径: http://localhost:80/a.html
					如果配置成 /hello,访问路径会变成什么?
						答案: http://localhost:80/hello/a.html
				-->
                <path>/</path>
            </configuration>
        </plugin>
    </plugins>
</build>
```

​	目前貌似只有Tomcat7能用





































































































[^1]: 请求数据和响应数据需要按照指定的格式进行传输tomcat