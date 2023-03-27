# Maven笔记

## 1.0	Maven是什么?

​	Apache Maven是专门用于管理和构建Java项目的工具，于项目对象模型(POM)的概念，通过一小段描述信息来管理项目的构建、报告和文档。它的主要功能有：

* 提供了一套标准化的项目结构
* 提供了一套标准化的构建流程（编译，测试，打包，发布……）
* 提供了一套依赖管理机制

### 1.1	标准化的项目结构

​	每一个开发工具（IDE）都有自己不同的项目结构，它们互相之间不通用。在eclipse中创建的目录，无法在idea中进行使用，这就造成了很大的不方便。

​	而Maven提供了一套标准化的项目结构，所有的IDE使用Maven构建的项目完全一样，所以IDE创建的Maven项目可以通用。如下图右边就是Maven构建的项目结构。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726153815028.png" alt="image-20210726153815028" style="zoom:80%;" />

### 1.2	标准化的构建流程：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726154144488.png" alt="image-20210726154144488" style="zoom:80%;" />

​	如上图所示开发了一套系统，代码需要进行**编译**、**测试**、**打包**、**发布**，这些操作如果需要反复进行就显得特别麻烦，而Maven提供了一套简单的命令来完成项目构建。

### 1.3	依赖管理

​	依赖管理其实就是管理你项目所依赖的第三方资源（jar包、插件）。如之前我们项目中需要使用JDBC和Druid的话，就需要去网上下载对应的依赖包（当前之前是老师已经下载好提供给大家了），复制到项目中，还要将jar包加入工作环境这一系列的操作。如下图所示

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726154753631.png" alt="image-20210726154753631" style="zoom:80%;" />

而Maven使用标准的 ==坐标== 配置来管理各种依赖，只需要简单的配置就可以完成依赖管理。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726154922337.png" alt="image-20210726154922337" style="zoom:80%;" />

如上图右边所示就是mysql驱动包的坐标，在项目中只需要写这段配置，其他都不需要我们担心，Maven都帮我们进行操作了。

### 1.4	Maven本身的一些细节

#### 1.41	Maven模型

​	有以下三个重要概念

* 项目对象模型 (Project Object Model)
* 依赖管理模型(Dependency)
* 插件(Plugin)



<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726155759621.png" alt="image-20210726155759621" style="zoom:80%;" />

​	如上图所示就是Maven的模型，紫色框框起来的部分，他就是用来完成 **标准化构建流程**的 。如我们需要编译，Maven提供了一个编译插件供我们使用，我们需要打包，Maven就提供了一个打包插件提供我们使用等。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726160928515.png" alt="image-20210726160928515" style="zoom:80%;" />

​	上图中紫色框起来的部分，项目对象模型就是将我们自己抽象成一个对象模型，有自己专属的坐标，如下图所示是一个Maven项目：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726161340796.png" alt="image-20210726161340796" style="zoom:80%;" />

​	**依赖管理模型**则是使用坐标来描述当前项目依赖哪儿些第三方jar包，如下图所示

![image-20210726161616034](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726161616034.png)

#### 1.42	仓库

​	在以前，依赖jar包是存储在我们的**本地仓库**中。而项目运行时从本地仓库中拿需要的依赖jar包。现在我们有更多选择。

​	**仓库分类：**

* 本地仓库：自己计算机上的一个目录

* 中央仓库：由Maven团队维护的全球唯一的仓库

    * 地址： https://repo1.maven.org/maven2/

* 远程仓库(私服)：一般由公司团队搭建的私有仓库


​	当项目中使用坐标引入对应依赖jar包后，首先会查找本地仓库中是否有对应的jar包：

* 如果有，则在项目直接引用;

* 如果没有，则去中央仓库中下载对应的jar包到本地仓库。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726162605394.png" alt="image-20210726162605394" style="zoom:70%;" />

如果还可以搭建远程仓库，将来jar包的查找顺序则变为：

> 本地仓库 --> 远程仓库--> 中央仓库

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726162815045.png" alt="image-20210726162815045" style="zoom:70%;" />

### 1.5	Maven基本命令

​	Maven的基本命令有以下几个:

* compile ：编译

* clean：清理

* test：测试

* package：打包

* install：安装

​	每个Maven项目都会有一个pom.xml文件, 称为 **Project Object Model（项目对象模型）**，它用于描述整个 Maven 项目，所以也称为 Maven 描述文件。

​	使用命令也是在Maven项目的这个文件的路径下通过命令行使用的。在IDEA中导入Maven项目也是在IDEA中选择.xml文件来结束操作。在IDEA中创建Maven项目或创建Maven模块则需要在创建时`Generators`选择Maven的选项、`Catalog`选择Internal、`Archetype`推荐选择`quickstart`后缀的(实操时第一个要下载一大堆东西最后还用不了:crying_cat_face:）

由于一般都在IDEA内使用集成后的Maven这里不再做记录。



### 1.6	Maven生命周期

​	Maven 构建项目生命周期描述的是一次构建过程经历经历了多少个事件

​	Maven 对项目构建的生命周期划分为3套：

* clean ：清理工作。
* default ：核心工作，例如编译，测试，打包，安装等。
* site ： 产生报告，发布站点等。这套声明周期一般不会使用。

​	同一套生命周期内，执行后边的命令，前面的所有命令会自动执行。例如默认（default）生命周期如下：

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726173153576.png" alt="image-20210726173153576" style="zoom:80%;" />

​	当我们执行 `install`（安装）命令时，它会先执行 `compile`命令，再执行 `test ` 命令，再执行 `package` 命令，最后执行 `install` 命令。

​	当我们执行 `package` （打包）命令时，它会先执行 `compile` 命令，再执行 `test` 命令，最后执行 `package` 命令。



### 1.7	Maven 坐标详解

#### 1.71	什么是坐标?

* Maven 中的坐标是**资源的唯一标识**
* 使用坐标来定义项目或引入项目中需要的依赖

#### 1.72	Maven 坐标主要组成

* groupId：定义当前Maven项目隶属组织名称（通常是域名反写，例如：com.itheima）
* artifactId：定义当前Maven项目名称（通常是模块名称，例如 order-service、goods-service）
* version：定义当前项目版本号

​	下图就是使用坐标表示一个项目：

![image-20210726174718176](https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726174718176.png)

​	*注意：上面所说的**资源**可以是**插件、依赖、当前项目**。我们的项目如果被其他的项目依赖时，也是需要坐标来引入的。*



## 2.0	依赖

### 2.1	依赖管理

​	在bing or google上在apache maven上搜索到坐标，复制到pom.xml的对应位置。Alt+Insert有相应的快捷方式，但目前我还不会用。

### 2.2	依赖范围

​	通过设置坐标的**依赖范围(scope)**，可以设置 对应jar包的作用范围：**编译环境、测试环境、运行环境**。

​	如下图所示给 `junit` 依赖通过 `scope` 标签指定依赖的作用范围。 那么这个依赖就只能作用在测试环境，其他环境下不能使用。

<img src="https://mytyporapicute.oss-cn-guangzhou.aliyuncs.com/typoraPics/image-20210726194703845.png" alt="image-20210726194703845" style="zoom:70%;" />

| **依赖范围** | 编译classpath | 测试classpath | 运行classpath | 例子              |
| ------------ | ------------- | ------------- | ------------- | ----------------- |
| **compile**  | Y             | Y             | Y             | logback           |
| **test**     | -             | Y             | -             | Junit             |
| **provided** | Y             | Y             | -             | servlet-api       |
| **runtime**  | -             | Y             | Y             | jdbc驱动          |
| **system**   | Y             | Y             | -             | 存储在本地的jar包 |

* compile ：作用于编译环境、测试环境、运行环境。
* test ： 作用于测试环境。典型的就是Junit坐标，以后使用Junit时，都会将scope指定为该值
* provided ：作用于编译环境、测试环境。后续学习 `servlet-api` ，在使用它时，必须将 `scope` 设置为该值，不然运行时就会报错
* runtime  ： 作用于测试环境、运行环境。jdbc驱动一般将 `scope` 设置为该值，当然不设置也没有任何问题 

*注意：如果引入坐标不指定 `scope` 标签时，默认就是 compile  值。以后大部分jar包都是使用默认值。*