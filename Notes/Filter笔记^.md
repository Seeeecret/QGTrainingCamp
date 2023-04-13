# Filter笔记

## 1.0	Filter概述

​	Filter 表示过滤器，是 JavaWeb 三大组件(**Servlet、Filter、Listener**)之一。其中**Servlet** 之前都已经学习过了。

​	过滤器可以把对资源的请求**拦截**下来，从而实现一些特殊的功能。

​	如下图所示，浏览器理论上可以访问服务器上的所有的资源（servlet、jsp、html等）

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823184519509.png" alt="image-20210823184519509" style="zoom:50%;" />

​	而在访问到这些资源之前可以使用**过滤器**来拦截，也就是说在访问<u>资源之前会先经过 Filter</u>，如下图

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823184657328.png" alt="image-20210823184657328" style="zoom:57%;" />

​	拦截器拦截到后可以做什么功能呢？

​	过滤器可以实现一些比较**通用**、**可复用**的功能，例如`权限控制`, `统一编码处理`,`敏感字符处理` 

### 1.2  Filter快速入门

#### 1.2.1  开发步骤

​	过滤器是 Web 三大组件之一，所以我们将 `filter` 创建在 `com.itheima.web.filter` 包下，起名为 `FilterDemo`

​	进行 `Filter` 开发分成以下三步实现

* 定义类，实现 Filter接口，并重写其所有方法

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823191006878.png" alt="image-20210823191006878" style="zoom:60%;" />

* 配置Filter拦截资源的路径：在类上定义 `@WebFilter` 注解。而注解的 `value` 属性值 `/*` 表示拦截所有的资源

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823191037163.png" alt="image-20210823191037163" style="zoom:67%;" />

* 在doFilter方法中输出一句话，并放行

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823191200201.png" alt="image-20210823191200201" style="zoom:60%;" />

    > 上述代码中的 `chain.doFilter(request,response);` 就是放行，也就是让其访问本该访问的资源。

### 1.3	Filter执行流程

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823194830074.png" alt="image-20210823194830074" style="zoom:70%;" />

​	如上图是使用过滤器的流程，我们通过以下问题来研究过滤器的执行流程：

* 放行后访问对应资源，资源访问完成后，还会回到Filter中吗？

    从上图就可以看出肯定会回到Filter中

* 如果回到Filter中，是重头执行还是执行放行后的逻辑呢？

    如果是重头执行的话，就意味着 `放行前逻辑` 会被执行两次，肯定不会这样设计了；所以访问完资源后，会回到 `放行后逻辑`，执行该部分代码。

​	通过上述的说明，我们就可以总结Filter的执行流程如下：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823195434581.png" alt="image-20210823195434581" style="zoom:70%;" />

​	我们可以将对请求进行处理的代码放在放行之前进行处理，而如果请求完资源后还要对响应的数据进行处理时可以在放行后进行逻辑处理。

### 1.4  Filter拦截路径配置

​	拦截路径表示 Filter 会对请求的哪些资源进行拦截，使用 `@WebFilter` 注解进行配置。如：`@WebFilter("拦截路径")` 

​	拦截路径有如下四种配置方式：

* **拦截具体的资源**：/index.jsp：只有访问index.jsp时才会被拦截
* **目录拦截**：/user/*：访问/user下的所有资源，都会被拦截
* **后缀名拦截**：*.jsp：访问后缀名为jsp的资源，都会被拦截
* **拦截所有**：/*：访问所有资源，都会被拦截

​	过滤器拦截路径的配置方式和 `Servlet` 的请求资源路径配置方式一样，但是表示的含义不同。

### 1.5  过滤器链

#### 1.5.1  概述

过滤器链是指在一个Web应用，可以配置多个过滤器，这多个过滤器称为过滤器链。

如下图就是一个过滤器链，我们学习过滤器链主要是学习过滤器链执行的流程

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823215835812.png" alt="image-20210823215835812" style="zoom:70%;" />

上图中的过滤器链执行是按照以下流程执行：

1. 执行 `Filter1` 的放行前逻辑代码
2. 执行 `Filter1` 的放行代码
3. 执行 `Filter2` 的放行前逻辑代码
4. 执行 `Filter2` 的放行代码
5. 访问到资源
6. 执行 `Filter2` 的放行后逻辑代码
7. 执行 `Filter1` 的放行后逻辑代码

以上流程串起来就像一条链子，故称之为过滤器链。

#### 1.5.2	执行顺序问题

​	使用的是注解配置过滤器`Filter`，而这种配置方式的优先级是按照过滤器类名(字符串)的**自然排序**。比如有如下两个名称的过滤器 ： `BFilterDemo` 和 `AFilterDemo` 。那一定是 `AFilterDemo` 过滤器先执行。

### 1.6  案例

#### 1.6.1  需求

​	访问服务器资源时，需要先进行登录验证，如果没有登录，则自动跳转到登录页面

#### 1.6.2  分析

​	我们要实现该功能是在每一个资源里加入登陆状态校验的代码吗？显然是不需要的，只需要写一个 `Filter` ，在该过滤器中进行登陆状态校验即可。而在该 `Filter` 中逻辑如下：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823223214525.png" alt="image-20210823223214525" style="zoom:70%;" />