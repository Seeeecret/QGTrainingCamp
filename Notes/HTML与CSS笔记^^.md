# HTML和CSS笔记

​	**HTML(HyperText Markup Language)**:超文本标记语言

> 超文本:超越了文本的限制，比普通文本更强大。除了文字信息，还可以定义图片、音频
> 视频等内容
>
> 标记语言:由标签构成的语言

​	**HTML的特点:**	

- 所有的网页都是用HTML这门语言编写出来的。

- HTML运行在浏览器上，HTML标签由浏览器来解析。

- HTML 标签都是预定义好的。例如:使用<img>展示图片

- 标签内还可以写标签的**属性**可以对标签定义的功能进行一定程度的修改和扩充。

* HTML 标签不区分大小写

* HTML 标签属性值 单双引皆可

    如上案例中的color属性值使用双引号也是可以的。&lt;font color="red">&lt;/font> 

* HTML 语法松散

    比如 font 标签不加结束标签也是可以展示出效果的。

​	**W3C标准:**网页主要由三部分组成

- 结构: HTML

 - 表现: CSS
 - 行为: JavaScript



## 1.0	结构标签

​	HTML快速入门:

​	1.新建文本文件，后缀名改为 .html/.htm

​	2.编写 HTML结构标签

​	3.在&lt;body>中使用&lt;h1>定义标题字体

​	4.使用&lt;img>标签定义图片

​	5.保存后，使用浏览器打开该文件

| 结构标签   | 描述               |
| ---------- | ------------------ |
| &lt;HTML>  | 定义 HTML 文档     |
| &lt;head>  | 定义关于文档的信息 |
| &lt;title> | 定义文档的标题     |
| &lt;body>  | 定义文档的主体     |

```html
<html>
	<head>
    	<title>html 快速入门</title>
    </head>
    <body>
        <font color='red'>乾坤未定，你我皆是黑马~</font>
    </body>
</html>
```



## 2.0	基础标签

​	基础标签

| 标签                      | 描述                               |
| ------------------------- | ---------------------------------- |
| &lt;h1&gt;  ~  &lt;h6&gt; | 定义标题，h1最大，h6最小           |
| &lt;font&gt;              | 定义文本的字体、字体尺寸、字体颜色 |
| **&lt;b&gt;**             | 定义粗体文本                       |
| **&lt;i&gt;**             | 定义斜体文本                       |
| **&lt;u&gt;**             | 定义文本下划线                     |
| &lt;center&gt;            | 定义文本居中                       |
| **&lt;p&gt;**             | 定义段落                           |
| **&lt;br&gt;**            | 定义换行                           |
| &lt;hr&gt;                | 定义一条水平线                     |

​	font：字体标签(已不建议使用)

* face 属性：用来设置字体。如 "楷体"、"宋体"等

* color 属性：设置文字颜色。颜色有三种表示方式

    * **英文单词**：red,pink,blue...

        这种方式表示的颜色特别有限，所以一般不用。

    * **rgb(值1,值2,值3)**：值的取值范围：0~255  

        此种方式也就是三原色（红绿蓝）设置方式。 例如： rgb(255,0,0)。

        这种书写起来比较麻烦，一般不用。

    * **#值1值2值3**：值的范围：00~FF

        这种方式是rgb方式的简化写法，以后基本都用此方式。

        值1表示红色的范围，值2表示绿色的范围，值3表示蓝色范围。例如： #ff0000

* size 属性：设置文字大小

```html
<font face="楷体" size="5" color="#ff0000">传智教育</font>
```

​	转移标签

| HTML 原代码 | 显示结果 | 描述                   |
| ----------- | -------- | ---------------------- |
| \&lt;       | <        | 小于号或显示标记       |
| \&gt ;      | >        | 大于号或显示标记       |
| \&amp;      | &        | 可用于显示其它特殊字符 |
| \&quot;     | “        | 引号                   |
| \&reg;      | ®        | 已注册                 |
| \&copy;     | ©        | 版权                   |
| \&trade;    | ™        | 商标                   |
| \&nbsp;     |          | 不断行的空白           |



## 3.0	图片、音频、视频标签

| 标签          | 描述     |
| ------------- | -------- |
| &lt;img&gt;   | 定义图片 |
| &lt;audio&gt; | 定义音频 |
| &lt;video&gt; | 定义视频 |

- img：定义图片

    - src：规定显示图像的 URL

        - (网上或本地)绝对路径和相对路径

        - 1．绝对路径:完整路径

            2．相对路径:相对位置关系
            xxx / html/02-图片音频视频.html

            xxx/ html/a .jpg

            - 上一级路径下的:  ../directory/ a.jpg & a.jpg
            - 本级路径下的:  ./directory/a.jpg

    - height：定义图像的高度

    - width：定义图像的宽度

        - 尺寸单位:
            1.pX:像素

            2.百分比:

- audio：定义音频。支持的音频格式：MP3、WAV、OGG 

    - src：规定音频的 URL
    - controls：显示播放控件

- video：定义视频。支持的音频格式：MP4, WebM、OGG

    - src：规定视频的 URL
    - controls：显示播放控件



## 4.0	超链接标签

​	

| 标签      | 描述                             |
| --------- | -------------------------------- |
| &lt;a&gt; | 定义超链接，用于链接到另一个资源 |

​	相关属性:

* href：指定访问资源的URL
* target：指定打开资源的方式
    *  __self:默认值，在当前页面打开_
    * _blank：在空白页面打开



## 5.0	列表标签

| 标签                      | 描述         |
| ------------------------- | ------------ |
| &lt;ol&gt; (order list)   | 定义有序列表 |
| &lt;ul&gt; (unorder list) | 定义无序列表 |
| &lt;li&gt;                | 定义列表项   |

* type：设置符号的类型

​	例子:

```html
<ol>
	<li>咖啡</li>
    <li>茶</li>
    <li>牛奶</li>
</ol>
```

​	相关**属性**:

| 属性 | 描述           |
| ---- | -------------- |
| type | 定义序号的种类 |
|      |                |



## 6.0	表格标签

​	

| 标签          | 描述           |
| ------------- | -------------- |
| &lt;table&gt; | 定义表格       |
| &lt;tr&gt;    | 定义行         |
| &lt;td&gt;    | 定义单元格     |
| &lt;th&gt;    | 定义表头单元格 |

* table：设置符号的类型和其属性

    * table：定义表格
        * width：宽度
        * border：边框
        * cellpadding：定义内容和单元格的距离
        * cellspacing：定义单元格之间的距离。如果指定为0，则单元格的线会合为一条、
        * bgcolor：背景色
        * align：对齐方式
    * tr：定义行
        * bgcolor：背景色
        * align：对齐方式: centercente等
    * td：定义单元格
        * colspan：合并列
        * rowspan：合并行
            * 使用上述两个属性进行合并后对应的行/列的数量会减少。
    * th：定义表头单元格
        * &lt;caption>：表格标题



## 7.0	布局标签

| 标签         | 描述                                                         |
| ------------ | ------------------------------------------------------------ |
| &lt;div&gt;  | 块级标签，会填充满整一行。定义 HTML 文档中的一个区域部分，经常与 CSS 一起使用，用来布局网页 |
| &lt;span&gt; | 行内标签。用于组合行内元素。                                 |





## 8.0	表单标签

​	**表单**:在网页中主要负责<u>数据采集功能</u>，使用&lt;form>标签定义表单

​	**表单项(元素)**:不同类型的input元素、下拉列表、文本域等

| 标签             | 描述                                                 |
| ---------------- | ---------------------------------------------------- |
| &lt;form&gt;     | 定义表单                                             |
| &lt;input&gt;    | 定义表单项，通过type属性控制输入形式                 |
| &lt;label&gt;    | 为表单项定义标注,能用for属性再设置实现与其它标签关联 |
| &lt;select&gt;   | 定义下拉列表                                         |
| &lt;option&gt;   | 定义下拉列表的列表项                                 |
| &lt;textarea&gt; | 定义文本域                                           |

- form:定义个空表单

    - action:规定当提交表单时向何处发送表单数据，URL
        - 以后会将数据提交到服务端，该属性需要书写服务端的URL。写`#`将会提交到当前页面
    
     - method :规定用于发送表单数据的方式
        - get:浏览器会将数据直接附在表单的action URL之后。大小有限制(4KB)
        - post:浏览器会将数据放到http请求协议的请求体中。大小无限制

​	下例:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
    <form action="#">
        <input type="text" name="username">  <!-- 要想提交数据，`input` 输入框必须设置 `name` 属性 -->
        <input type="submit">
    </form>
</body>
</html>
```



### 8.1	input等表单项标签

- &lt;input>标签通过**type**属性控制输入形式。

| type 取值 | 描述                                           |
| --------- | ---------------------------------------------- |
| text      | 默认值。定义单行的输入字段                     |
| password  | 定义密码字段                                   |
| radio     | 定义单选按钮                                   |
| checkbox  | 定义复选框                                     |
| file      | 定义文件上传按钮                               |
| hidden    | 定义隐藏的输入字段                             |
| submit    | 定义提交按钮，提交按钮会把表单数据发送到服务器 |
| reset     | 定义重置按钮，重置按钮会清除表单中的所有数据   |
| button    | 定义可点击按钮                                 |
| value     | 更改按钮的显示内容，也可以设置提交时的值       |
| name      | 设置一样的name配合单选框可实现互斥单选         |

- &lt;select>: 定义下拉列表, &lt;option>定义列表项

![image-20210812223708205](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210812223708205.png)

- &lt;textarea>: 文本域

    ![image-20210812223744522](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210812223744522.png)


​	注意：

* 以上标签项的内容要想提交，必须得定义 `name` 属性。
* 每一个标签都有id属性，id属性值是唯一的标识。
* 单选框、复选框、下拉列表需要使用 `value` 属性指定提交的值。



## 10.0	CSS

### 10.1	简单介绍

​	CSS 是一门语言，用于控制网页表现。我们之前介绍过W3C标准。W3C标准规定了网页是由以下组成：

* 结构：HTML
* 表现：CSS
* 行为：JavaScript

CSS也有一个专业的名字：**Cascading Style Sheet**（层叠样式表）。

如下面的代码， `style` 标签中定义的就是css代码。该代码描述了将 div 标签的内容的字体颜色设置为 红色。

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
        div{
            color: red;
        }
    </style>
</head>
<body>
    <div>Hello CSS~</div>
</body>
</html>
```

在浏览器中的效果如下：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210812225424174.png" alt="image-20210812225424174" style="zoom:60%;" />

### 10.2	CSS导入方式

​	css 导入方式其实就是 css 代码和 html 代码的结合方式。CSS 导入 HTML有三种方式：

* 内联样式：在标签内部使用style属性，属性值是css属性键值对

    ```html
    <div style="color: red">Hello CSS~</div>
    ```

    ​	此方式只能作用在这一个标签上，如果其他的标签也想使用同样的样式，那就需要在其他标签上写上相同的样式。复用性太差。

* 内部样式：定义<**style**>标签，在标签内部定义css样式

    ```html
    <style type="text/css">
    	div{
    		color: red;
        }
    </style>
    ```

    ​	此方式可以做到在该页面中复用。

* 外部样式：定义link标签，引入外部的css文件

    编写一个css文件。名为：demo.css，内容如下:

    ```css
    div{
    	color: red;
    }
    ```

    在html中引入 css 文件。

    ```html
    <link rel="stylesheet"  href="demo.css">
    ```

    ​	这种方式可以在多个页面进行复用。其他的页面想使用同样的样式，只需要使用 `link` 标签引入该css文件。实际开发中一般用这种

### 10.3	css 选择器

css 选择器就是选取需设置样式的元素（标签），比如如下css代码：

```css
div {
	color:red;
}
```

如上代码中的 `div` 就是 css 中的选择器。我们只讲下面三种选择器：

* 元素选择器

    格式：

    ```css
    元素名称{color: red;}
    ```

    例子：

    ```html
    div {color:red}  <!--该代码表示将页面中所有的div标签的内容的颜色设置为红色-->
    ```

* id选择器

    格式：

    ```css
    #id属性值{color: red;}
    ```

    例子：

    html代码如下：

    ```html
    <div id="name">hello css2</div>
    ```

    css代码如下：

    ```css
    #name{color: red;}/*该代码表示将页面中所有的id属性值是 name 的标签的内容的颜色设置为红色,id是唯一的*/
    ```

* 类选择器

    格式：

    ```css
    .class属性值{color: red;}
    ```

    例子：

    html代码如下：

    ```html
    <div class="cls">hello css3</div>
    ```

    css代码如下：

    ```css
    .cls{color: red;} /*该代码表示将页面中所有的class属性值是 cls 的标签的内容的颜色设置为红色*/
    ```

