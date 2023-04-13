# Listener和Ajax笔记

* Listener 表示监听器，是 JavaWeb 三大组件(Servlet、Filter、Listener)之一。

* 监听器可以监听就是在 `application`，`session`，`request` 三个对象创建、销毁或者往其中添加修改删除属性时自动执行代码的功能组件。

    request 和 session 我们学习过。而 `application` 是 `ServletContext` 类型的对象。

    `ServletContext` 代表整个web应用，在服务器启动的时候，tomcat会自动创建该对象。在服务器关闭时会自动销毁该对象。

## 1.0	分类

​	JavaWeb 提供了8个监听器：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823230820586.png" alt="image-20210823230820586" style="zoom:80%;" />

​	这里面只有 `ServletContextListener` 这个监听器后期我们会接触到，`ServletContextListener` 是用来监听 `ServletContext` 对象的创建和销毁。

`ServletContextListener` 接口中有以下两个方法

* `void contextInitialized(ServletContextEvent sce)`：`ServletContext` 对象被创建了会自动执行的方法
* `void contextDestroyed(ServletContextEvent sce)`：`ServletContext` 对象被销毁时会自动执行的方法

### 1.1	代码演示

​	演示一下 `ServletContextListener` 监听器

* 定义一个类，实现`ServletContextListener` 接口
* 重写所有的抽象方法
* 使用 `@WebListener` 进行配置

代码如下：

```java
@WebListener
public class ContextLoaderListener implements ServletContextListener {
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        //加载资源
        System.out.println("ContextLoaderListener...");
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        //释放资源
    }
}
```

​	启动服务器，就可以在启动的日志信息中看到 `contextInitialized()` 方法输出的内容，同时也说明了 `ServletContext` 对象在服务器启动的时候被创建了。

## 2.0	Ajax

### 2.1  概述

​	`AJAX` (Asynchronous JavaScript And XML)：异步的 JavaScript 和 XML。

​	概念中的 `JavaScript` 和 `XML`，`JavaScript` 表明该技术和前端相关；`XML` 是指以此进行数据交换。

#### 2.1.1  作用

​	AJAX 作用有以下两方面：

1. **与服务器进行数据交换**：通过AJAX可以给服务器发送请求，服务器将数据直接响应回给浏览器。如下图

​	之前做功能的流程如下图：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823235114367.png" alt="image-20210823235114367" style="zoom:70%;" />

​	如上图，`Servlet` 调用完业务逻辑层后将数据存储到域对象中，然后跳转到指定的 `jsp` 页面，在页面上使用 `EL表达式` 和 `JSTL` 标签库进行数据的展示。



​	而学习了AJAX 后，就可以**使用AJAX和服务器进行通信**，以达到使用 HTML+AJAX来替换JSP页面了。如下图，浏览器发送请求servlet，servlet 调用完业务逻辑层后将数据直接响应回给浏览器页面，页面使用 HTML 来进行数据展示。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210823235006847.png" alt="image-20210823235006847" style="zoom:70%;" />

2. **异步交互**：可以在不**重新加载整个页面**的情况下，与服务器交换数据并==更新部分网页==的技术，如：搜索联想、用户名是否可用校验，等。

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210824000706401.png" alt="image-20210824000706401" style="zoom:80%;" />

​	上图所示的效果我们经常见到，在我们输入一些关键字（例如 `奥运`）后就会在下面联想出相关的内容，而联想出来的这部分数据肯定是存储在百度的服务器上，而我们并没有看出页面重新刷新，这就是 **更新局部页面** 的效果。再如下图：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210824001015706.png" alt="image-20210824001015706" style="zoom:80%;" />

​	我们在用户名的输入框输入用户名，当输入框一失去焦点，如果用户名已经被占用就会在下方展示提示的信息；在这整个过程中也没有页面的刷新，只是在局部展示出了提示信息，这就是 **更新局部页面** 的效果。

#### 2.1.2  同步和异步

知道了局部刷新后，接下来我们再聊聊同步和异步:

* 同步发送请求过程如下

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210824001443897.png" alt="image-20210824001443897" style="zoom:80%;" />

​	浏览器页面在发送请求给服务器，在服务器处理请求的过程中，浏览器页面不能做其他的操作。只能等到服务器响应结束后才能，浏览器页面才能继续做其他的操作。

* 异步发送请求过程如下

    <img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210824001608916.png" alt="image-20210824001608916" style="zoom:80%;" />

    浏览器页面发送请求给服务器，在服务器处理请求的过程中，浏览器页面还可以做其他的操作。

### 2.2  快速入门

#### 2.2.1 服务端实现

在项目的创建 `com.itheima.web.servlet` ，并在该包下创建名为  `AjaxServlet` 的servlet

```java
@WebServlet("/ajaxServlet")
public class AjaxServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //1. 响应数据
        response.getWriter().write("hello ajax~");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        this.doGet(request, response);
    }
}
```

#### 2.2.2  客户端实现

在 `webapp` 下创建名为 `01-ajax-demo1.html` 的页面，在该页面书写 `ajax` 代码

* 创建核心对象，不同的浏览器创建的对象是不同的

    ```js
     var xhttp;
    if (window.XMLHttpRequest) {
        xhttp = new XMLHttpRequest();
    } else {
        // code for IE6, IE5
        xhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    ```

* 发送请求

    ```js
    //建立连接
    xhttp.open("GET", "http://localhost:8080/ajax-demo/ajaxServlet");
    //发送请求
    xhttp.send();
    ```

* 获取响应

    ```js
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            // 通过 this.responseText 可以获取到服务端响应的数据
            alert(this.responseText);
        }
    };
    ```

**完整代码如下：**

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>

<script>
    //1. 创建核心对象
    var xhttp;
    if (window.XMLHttpRequest) {
        xhttp = new XMLHttpRequest();
    } else {
        // code for IE6, IE5
        xhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    //2. 发送请求
    xhttp.open("GET", "http://localhost:8080/ajax-demo/ajaxServlet");
    xhttp.send();

    //3. 获取响应
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            alert(this.responseText);
        }
    };
</script>
</body>
</html>
```

## 3.0	JSON

​	概念：`JavaScript Object Notation`。JavaScript 对象表示法.

​	如下是 `JavaScript` 对象的定义格式：

```js
{
	name:"zhangsan",
	age:23,
	city:"北京"
}
```

​	接下来我们再看看 `JSON` 的格式：

```json
{
	"name":"zhangsan",
	"age":23,
	"city":"北京"
}
```

​	通过上面 js 对象格式和 json 格式进行对比，发现两个格式特别像。只不过 js 对象中的属性名可以使用引号（可以是单引号，也可以是双引号）；而 `json` 格式中的键要求必须使用双引号括起来，这是 `json` 格式的规定。`json` 格式的数据有什么作用呢？

作用：由于其语法格式简单，层次结构鲜明，现多用于作为**数据载体**，在网络中进行数据传输。如下图所示就是服务端给浏览器响应的数据，这个数据比较简单，如果现需要将 JAVA 对象中封装的数据响应回给浏览器的话，应该以何种数据传输呢？

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210830232718632.png" alt="image-20210830232718632" style="zoom:80%;" />

大家还记得 `ajax` 的概念吗？ 是**异步的 JavaScript 和 xml**。这里的 **xml**就是以前进行数据传递的方式，如下：

```xml
<student>
    <name>张三</name>
    <age>23</age>
    <city>北京</city>
</student>
```

再看 `json` 描述以上数据的写法：

```json
{	
	"name":"张三",
    "age":23,
    "city":"北京"
}
```

上面两种格式进行对比后就会发现 `json` 格式数据的简单，以及所占的字节数少等优点。

### 3.1	JSON基础语法

#### 3.1.1  定义格式

​	`	JSON` 本质就是一个字符串，但是该字符串内容是有一定的格式要求的。 定义格式如下：

```js
var 变量名 = '{"key":value,"key":value,...}';
```

​	`	JSON` 串的键要求必须使用双引号括起来，而值根据要表示的类型确定。value 的数据类型分为如下

* 数字（整数或浮点数）
* 字符串（使用双引号括起来）
* 逻辑值（true或者false）
* 数组（在方括号中）
* 对象（在花括号中）
* null

​	示例：

```js
var jsonStr = '{"name":"zhangsan","age":23,"addr":["北京","上海","西安"]}'
```

#### 3.1.2  代码演示

​	创建一个页面，在该页面的 `<script>` 标签中定义json字符串

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<script>
    //1. 定义JSON字符串
    var jsonStr = '{"name":"zhangsan","age":23,"addr":["北京","上海","西安"]}'
    alert(jsonStr);

</script>
</body>
</html>
```

​	通过浏览器打开，页面效果如下图所示:

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210831223339530.png" alt="image-20210831223339530" style="zoom:80%;" />

​	现在我们需要获取到该 `JSON` 串中的 `name` 属性值，应该怎么处理呢？

​		如果它是一个 js 对象，我们就可以通过 `js对象.属性名` 的方式来获取数据。JS 提供了一个对象 `JSON` ，该对象有如下两个方法：

* `parse(str)` ：将 JSON串转换为 js 对象。使用方式是： `var jsObject = JSON.parse(jsonStr);`
* `stringify(obj)` ：将 js 对象转换为 JSON 串。使用方式是：`var jsonStr = JSON.stringify(jsObject)`

代码演示：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<script>
    //1. 定义JSON字符串
    var jsonStr = '{"name":"zhangsan","age":23,"addr":["北京","上海","西安"]}'
    alert(jsonStr);

    //2. 将 JSON 字符串转为 JS 对象
    let jsObject = JSON.parse(jsonStr);
    alert(jsObject)
    alert(jsObject.name)
    //3. 将 JS 对象转换为 JSON 字符串
    let jsonStr2 = JSON.stringify(jsObject);
    alert(jsonStr2)
</script>
</body>
</html>
```

#### 3.1.3  发送异步请求携带参数



> 注意：
>
> * 发送异步请求时，如果请求参数是 `JSON` 格式，那请求方式必须是 `POST`。因为 `JSON` 串需要放在请求体中。

### 3.2  JSON串和Java对象的相互转换

​	以后我们会以 json 格式的数据进行前后端交互。前端发送请求时，如果是复杂的数据就会以 json 提交给后端；而后端如果需要响应一些复杂的数据时，也需要以 json 格式将数据响应回给浏览器。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210831104901912.png" alt="image-20210831104901912" style="zoom:70%;" />

​	在后端我们就需要重点学习以下两部分操作：

* 请求数据：JSON字符串转为Java对象
* 响应数据：Java对象转为JSON字符串

​	接下来介绍一个Java的外部库 `Fastjson`

#### 3.2.1  Fastjson 概述

​	`Fastjson` 是阿里巴巴提供的一个Java语言编写的高性能功能完善的 `JSON` 库，是目前Java语言中最快的 `JSON` 库，可以实现 `Java` 对象和 `JSON` 字符串的相互转换。

#### 3.2.2  Fastjson 使用

​	`Fastjson` 使用也是比较简单的，分为以下三步完成

1. **导入坐标**

    ```xml
    <dependency>
        <groupId>com.alibaba</groupId>
        <artifactId>fastjson</artifactId>
        <version>1.2.62</version>
    </dependency>
    ```

2. **Java对象转JSON**

    ```java
    String jsonStr = JSON.toJSONString(obj);
    ```

    将 Java 对象转换为 JSON 串，只需要使用 `Fastjson` 提供的 `JSON` 类中的 `toJSONString()` 静态方法即可。

3. **JSON字符串转Java对象**

    ```java
    User user = JSON.parseObject(jsonStr, User.class);
    ```

    将 json 转换为 Java 对象，只需要使用 `Fastjson` 提供的 `JSON` 类中的 `parseObject()` 静态方法即可。

#### 3.2.3  代码演示

* 引入坐标

* 创建一个类，专门用来测试 Java 对象和 JSON 串的相互转换，代码如下：

    ```java
    public class FastJsonDemo {
    
        public static void main(String[] args) {
            //1. 将Java对象转为JSON字符串
            User user = new User();
            user.setId(1);
            user.setUsername("zhangsan");
            user.setPassword("123");
    
            String jsonString = JSON.toJSONString(user);
            System.out.println(jsonString);//{"id":1,"password":"123","username":"zhangsan"}
    
    
            //2. 将JSON字符串转为Java对象
            User u = JSON.parseObject("{\"id\":1,\"password\":\"123\",\"username\":\"zhangsan\"}", User.class);
            System.out.println(u);
        }
    }
    ```

    

## 4.0	JQuery框架

* jQuery是一个快速、简洁的JavaScript框架，是继Prototype之后又一个优秀的JavaScript代码库（或JavaScript框架）。jQuery设计的宗旨	是“Write Less，Do More”，即倡导写更少的代码，做更多的事情。它封装JavaScript常用的功能代码，提供一种简便的JavaScript设计模式，优化HTML文档操作、事件处理、动画设计和Ajax交互。

* JavaScript框架：本质上就是一些js文件，封装了js的原生代码而已

* jQuery 库包含以下功能：
    - HTML 元素选取
    - HTML 元素操作
    - CSS 操作
    - HTML 事件函数
    - JavaScript 特效和动画
    - HTML DOM 遍历和修改
    - AJAX
    - Utilities

​	JQuery对象和JS对象区别与转换:

1. JQuery对象在操作时，更加方便。
 2. JQuery对象和js对象方法不通用的.
 3. 两者相互转换
    * jq -- > js : jq对象[索引] 或者 jq对象.get(索引)
    * js -- > jq : $(js对象)

### 4.1	基本语法

​	Jquery 的基本语法是：

```javascript
$(selector).action()
```

其中，$ 是 Jquery 的标识符，表示使用 Jquery 库；selector 是选择器，用于选取 HTML 元素；action 是要执行的操作，可以是一个或多个 Jquery 方法。

### 4.2	基本选择器

​	Jquery 提供了多种选择器，可以根据元素的 id、类名、属性、内容等进行选择。例如：

```javascript
$("#test") // 选择 id 为 test 的元素
$(".demo") // 选择 class 为 demo 的元素
$("p") // 选择所有的 p 元素
$("[href]") // 选择所有带有 href 属性的元素
$("[name='p']") // 选取所有name="p"的元素
$(":button") // 选择所有的按钮元素
$("p:first") // 选择第一个 p 元素
$("p:contains('Hello')") // 选择包含 Hello 文本的 p 元素
$('*')// 选择所有元素
$('p, div')// 选择多个元素
```

### 4.3	基本操作

​	Jquery 的方法可以实现对选中元素的各种操作，例如改变样式、内容、属性、事件等。例如：

```javascript
$("#test").hide() // 隐藏 id 为 test 的元素
$(".demo").show() // 显示 class 为 demo 的元素
$("p").css("color", "red") // 设置所有 p 元素的颜色为红色
$("p").html("Hello World!") // 设置所有 p 元素的 HTML 内容为 Hello World!
$("p").text("Hello World!") // 设置所有 p 元素的文本内容为 Hello World!
$("img").attr("src", "logo.png") // 设置所有图片元素的 src 属性为 logo.png
$("p").click(function() { // 给所有 p 元素绑定点击事件的回调函数
    alert("You clicked me!");
});
```

​	以下是详细举例

#### 4.3.1	获取和设置元素内容

​	JQuery 中的 .attr() 方法是用来获取或设置被选元素的属性值的。根据该方法不同的参数，其工作方式也有所差异。以下是 .attr() 方法的四种用法：

1. .attr(属性名) //获取属性的值（取得第一个匹配元素的属性值）。
2. .attr(属性名, 属性值) //设置属性的值（为所有匹配的元素设置一个属性值）。
3. .attr(属性名, 函数) //设置属性的值（通过函数返回值计算出要设置的属性值）。
4. .attr(对象) //设置多个属性和值（为所有匹配的元素设置多个属性值）。

举例说明：

```javascript
//获取 img 元素的 src 属性值
var src = $("img").attr("src");

//设置 img 元素的 src 属性值为 logo.png
$("img").attr("src", "logo.png");

//设置 img 元素的 src 属性值为 index 值加 1
$("img").attr("src", function(index) {
    return "logo" + (index + 1) + ".png";
});

//设置 img 元素的 src 和 alt 属性值
$("img").attr({
    src: "logo.png",
    alt: "logo"
});
```

#### 4.3.2	遍历元素

​	可以使用 .each() 方法来对匹配的每个元素执行一个函数，也可以使用 .map() 方法来把当前匹配集合中的每个元素传递给一个函数，并返回一个新的 Jquery 对象。

```javascript
$("li").each(function(index) {
    alert(index + ": " + $(this).text()); //输出每个 li 元素的索引和文本内容
});

var arr = $("li").map(function() {
    return $(this).text(); //返回每个 li 元素的文本内容
}).get(); //获取一个包含所有返回值的数组
console.log(arr); //打印数组
```



#### 4.3.3	添加和删除元素

​	Jquery 中有多种方式可以添加或删除元素，根据添加或删除的位置和范围，可以分为以下几类：

- 添加元素：可以使用 .append()、.prepend()、.after()、.before() 等方法来在被选元素的内部或外部插入新的内容，可以是文本、HTML、Jquery 对象或 DOM 元素等。
- 删除元素：可以使用 .remove() 或 .empty() 方法来删除被选元素及其子元素，或者只删除被选元素的子元素。也可以使用选择器来过滤要删除的元素。

举例说明：

```javascript
//添加元素
$("div").append("<p>Some appended text.</p>"); //在 div 元素的结尾插入一个 p 元素
$("div").prepend("<p>Some prepended text.</p>"); //在 div 元素的开头插入一个 p 元素
$("div").after("<p>Some text after.</p>"); //在 div 元素之后插入一个 p 元素
$("div").before("<p>Some text before.</p>"); //在 div 元素之前插入一个 p 元素

//删除元素
$("div").remove(); //删除 div 元素及其子元素
$("div").empty(); //删除 div 元素的子元素
$("p").remove(".italic"); //删除 class 为 italic 的 p 元素
```



### 4.4	方法会提供的自动参数

​	有些 Jquery 方法会自动提供参数，这些参数是由方法内部定义的，通常是一些常用的值，例如元素的索引位置、对象、事件对象等。你可以在函数中使用这些参数来实现一些基于参数的逻辑，但是你需要注意参数的顺序和含义，不同的方法提供的参数可能不同。例如：

```javascript
$("li").map(function(index, element) {
    return index + ": " + $(element).text(); //返回每个 li 元素的索引和文本内容
});
```

​	这段代码的作用是遍历所有的 li 元素，并在函数中使用 index 和 element 两个参数来获取元素的索引位置和对象。index 和 element 是 Jquery 的 .map() 方法自动提供的两个参数，分别表示元素的索引位置和对象。

```javascript
$("p").click(function(event) {
    alert("You clicked at: " + event.pageX + ", " + event.pageY); //弹出点击位置的坐标
});
```

​	这段代码的作用是给所有的 p 元素绑定点击事件的回调函数，并在函数中使用 event 参数来获取事件对象，然后弹出点击位置的坐标。event 参数是 Jquery 的 .click() 方法自动提供的一个参数，表示触发事件的对象。



### 4.5	事件处理

​	Jquery 中有多种事件处理的方法，根据事件的类型、范围、触发方式等，可以分为以下几类：

- 事件绑定：可以使用 .bind()、.on()、.delegate()、.live() 等方法来给元素添加一个或多个事件处理程序，可以是当前或未来的元素，可以是单个或多个事件类型。常用的事件有 `click`、`mouseover`、`keydown` 等：
- 事件触发：可以使用 .click()、.dblclick()、.hover()、.focus()、.blur() 等方法来触发元素的指定事件，或者使用 .trigger() 或 .triggerHandler() 方法来触发元素的所有或特定事件。
- 事件移除：可以使用 .unbind()、.off()、.undelegate()、.die() 等方法来移除元素的一个或多个事件处理程序，可以是当前或未来的元素，可以是单个或多个事件类型。
- 事件对象：可以使用 event 参数来获取事件对象，该对象包含了一些有用的属性和方法，例如 event.type、event.target、event.preventDefault()、event.stopPropagation() 等。

举例说明：

```javascript
//事件绑定
$("p").bind("click", function() {
    alert("You clicked a paragraph.");
}); //给所有的 p 元素绑定 click 事件
$("p").on("click", function() {
    alert("You clicked a paragraph.");
}); //给所有的 p 元素绑定 click 事件（推荐）
$("div").delegate("p", "click", function() {
    alert("You clicked a paragraph inside a div.");
}); //给所有在 div 元素内的 p 元素绑定 click 事件
$("p").live("click", function() {
    alert("You clicked a paragraph.");
}); //给所有现在或未来的 p 元素绑定 click 事件（已废弃）

// 添加鼠标移入事件处理程序
$('#my-element').on('mouseover', function() {
  $(this).addClass('hover')
})

// 添加按键事件处理程序
$(document).on('keydown', function(event) {
  console.log(event.keyCode)
})

//事件触发
$("p").click(); //触发所有的 p 元素的 click 事件
$("p").trigger("click"); //触发所有的 p 元素的 click 事件（推荐）
$("p").triggerHandler("click"); //触发所有的 p 元素的 click 事件，但不冒泡

//事件移除
$("p").unbind("click"); //移除所有的 p 元素的 click 事件
$("p").off("click"); //移除所有的 p 元素的 click 事件（推荐）
$("div").undelegate("p", "click"); //移除所有在 div 元素内的 p 元素的 click 事件
$("p").die("click"); //移除所有现在或未来的 p 元素的 click 事件（已废弃）

//事件对象
$("p").click(function(event) {
    console.log(event.type); //打印 "click"
    console.log(event.target); //打印被点击的 p 元素
    event.preventDefault(); //阻止默认行为
    event.stopPropagation(); //阻止冒泡
});
```

### 4.6	动画效果(没学略过)

​	可以使用 jQuery 提供的动画效果方法，例如 `.show()`、`.hide()`、`.fadeIn()`、`.fadeOut()`、`.slideUp()` 和 `.slideDown()` 等来实现动画效果：

```javascript
javascriptCopy code// 显示元素
$('#my-element').show()

// 隐藏元素
$('#my-element').hide()

// 淡入元素
$('#my-element').fadeIn()

// 淡出元素
$('#my-element').fadeOut()

// 向上滑动元素
$('#my-element').slideUp()

// 向下滑动元素
$('#my-element').slideDown()
```

### 4.7	AJAX

​	可以使用 jQuery 提供的 `.ajax()` 方法与服务器进行异步通信：

```javascript
javascriptCopy code// 发送 GET 请求
$.ajax({
  url: 'http://example.com/api/data',
  method: 'GET',
  success: function(data) {
    console.log(data)
  }else{
    alert("sth")
}
})

// 发送 POST 请求
$.ajax({
  url: 'http://example.com/api/data',
  method: 'POST',
  data: {
    name: 'John',
    age: 30
  },
  success: function(data) {
    console.log(data)
   }else{
     alert("sth");
}
})
```

### 4.8	方法中的this

​	Jquery 的方法中的 this 是一个关键字，表示当前的元素对象，也就是触发事件或执行方法的元素。你可以使用 this 来获取或操作当前的元素，例如：

```javascript
$("p").click(function() {
    $(this).hide(); //隐藏当前被点击的 p 元素
});
```

这段代码的作用是给所有的 p 元素绑定点击事件，并在函数中使用 this 来获取当前被点击的 p 元素，然后隐藏它。$(this) 是一个 Jquery 对象，表示把 this 转换成 Jquery 对象，这样就可以使用 Jquery 的方法了。

### 4.9	一些杂项细节

​	Jquery中有快速设置入口函数(页面加载开始/完成时执行)的方法:

```javascript
$(function(){

});
```

​	也可以用传统写法:

```javascript
  $(document).ready(function(){
        $("#loginBtn").click(function(){
            let username = $("#username").val();
            let password = $("#password").val();
            $.ajax({
                type: "GET",
                url: "http://localhost:8080/AjaxJSONDemo_war/login",
                data: {
                    username: username,
                    password: password
                },
                dataType: "json",
                success: function(response){
                    if(response.code === 200){
                        localStorage.setItem("username", username);
                        alert("Successfully login");
                        window.location.href = "http://localhost:8080/AjaxJSONDemo_war/meritMenu.html?username=" +localStorage.getItem("username");

                    }else{

                        alert("Username or password is incorrect");

                    }
                },
                error: function(){
                    alert("System error");
                }
            });
        });
        $("#registerBtn").click(function(){
            let username = $("#username").val();
            let password = $("#password").val();
            $.ajax({
                type: "GET",
                url: "http://localhost:8080/AjaxJSONDemo_war/register",
                data: {
                    username: username,
                    password: password
                },
                dataType: "json",
                success: function(response){
                    if(response.code === 200){
                        alert("Successfully register");

                    }else{
                        alert("Username is already exist");
                    }
                },
                error: function(){
                    alert("System error");
                }
            });
        });
        $("#changePasswordBtn").click(function(){
            let username = $("#username").val();
            let password = $("#password").val();
            $.ajax({
                type: "GET",
                url: "http://localhost:8080/AjaxJSONDemo_war/changePassword",
                data: {
                    username: username,
                    password: password
                },
                dataType: "json",
                success: function(response){
                    if(response.code === 200){
                        alert("Successfully change password");

                    }else{
                        alert("Username is incorrect");
                    }
                },
                error: function(){
                    alert("System error");
                }
            });
        });
        $("#deleteUserBtn").click(function(){
            let username = $("#username").val();
            let password = $("#password").val();
            $.ajax({
                type: "GET",
                url: "http://localhost:8080/AjaxJSONDemo_war/delete",
                data: {
                    username: username,
                    password: password
                },
                dataType: "json",
                success: function(response){
                    if(response.code === 200){

                        alert("Successfully delete user");

                    }else{
                        alert("Username or password is incorrect");
                    }
                },
                error: function(){
                    alert("System error");
                }
            });
        });
    });

```

