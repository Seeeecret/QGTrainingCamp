#                                    Java基本语法



## 1.0	变量与常量

​	Java是一种强类型语言,所有的变量在使用之前必须定义或声明,所有的变量必须具有确定的数据类型。数据类型表示在变量中可以存放什么样的数据,变量中只能存放指定类型的数据,程序运行过程中也不能改变变量的类型。

​	变量名必须是一个以字母开头并由字母或数字构成的序列。需要注意，与大多数程序设计语言相比，Java 中“ 字母” 和“ 数字” 的范围更大。在某种语言中表示字母的任何 Unicode 字符都可以用作变量名,如德国用户可以用德文字母,希腊用户可以用π。

**注:①如果想要知道哪些 Unicode 字符属于 Java 中的“字母”， 可以使用 Character 类的*

*isJavaldentifierStart 和 isJavaldentifierPart 方法来检查*

​       *②C/C++区分变量的声明与定义,但Java不。*

### char类型

​	char 类型原本用于表示单个字符。不过，现在情况已经有所变化。 如今，有些 Unicode

字符可以用一个 char值描述，另外一些 Unicode 字符(辅助字符)则需要两个 char 值。

​	所有转义序列都可以出现在加引号的字符字面量或字符串中。例如，’ \u2122' 或 "Hello\n”。转

义序列 \u还可以出现在加引号的字符常量或字符串之外（而其他所有转义序列不可以）。

​		例如:

​			public static void main(String\u0058\u005D args){}				//其中\u0058和\u005D是汉字"和"的编码

###### 注意:

​	Unicode 转义序列会在解析代码之前得到处理。 例如，"\u0022+\u0022 ” 并不是一个由引号（U+0022) 包围加号构成的字符串("+")。 实际上， \u0022 会在解析之前转换为 "， 这实际上会得到""+"", 即一个空串。特别地， 一定要当心注释中的 \u。

​		例如:

​			注释

​			// \u00A0 is a newline

​			会产生一个语法错误， 因为读程序时 \u00A0 会替换为一个换行符

​			类似地，下面这个注释

​			// Look inside c:\users

​			也会产生一个语法错误， 因为 \u 后面并未跟着 4 个十六进制数。

*后注:在IDEA实操时并没有报错,运行时前一行代码运行正常,后一行会报错。*





### boolean类型（布尔类型）

​	有两个值flase和true。与C/C++不同,Java的布尔值与整形值之间不能相互转换且不通用。





### 常量

​	在 Java 中， 利用关键字 final 指示常量。例如：

```java
public class Constants{
    public static void main(String[] args){
        final double CM_PER_INCH = 2.54;
        //下略......
        //.......
    }
}
```

​	关键字final表示这个变量只能被赋值一次,之后便不能更改。使用方式上类似C/C++的const, 性质上更接近C/C++的define。const也是Java的保留字。

​	在 Java 中，经常希望某个常量可以在一个类中的多个方法中使用，通常将这些常量称为类常量。可以使用关键字**static final**设置一个类常量。 下面是使用类常量的示例：

```java
public class Constants2{
public static final double CM_PER_INCH = 2.54;//类似C/C++中的全局变量或define定义的常量
public static void main(Stringn args){
double paperWidth = 8.5;
double paperHeight = 11;
System.out.println("Paper size in centimeters: "
+ paperWidth * CMJERJNCH + by " + paperHeight * CM_PER_INCH) ;
}
}
```





### 类型转换

​	在必要的时候,Java中int类型的值会自动地转换为double类型,而不会像C/C++一样统一阶段。

​	long类型的值也不能直接赋给int类型的值,需要进行强制类型转换。





## 2.0	运算符

​	各项内容大致与C/C++相同。但需要注意的是，在 C/C++ 中，>>不能保证是完成算术移位（扩展符号位，填充高位）还是逻辑移位（高位填充 0。) 实现者可以选择其中更高效的任何一种做法。 这意味着 C/C++ »运算符对于负数生成的结果可能会依赖于具体的实现。Java 则消除了这种不确定性:

​		用符号位填充高位:	>>

​		用0填充高位:	>>>

​	特别注意: ①&&优先级比||高

​                     ②+=是右结合运算符

​					 ③Java不使用逗号运算符



## 3.0	字符串

​	Java没有内置的字符串类型,而是在标准Java类库中提供了一个预定义类:String

### 子串

​	String 类的 substring 方法可以从一个较大的字符串提取出一个子串。

​	例:

```java
String greeting = "Hello";
String s = greeting.substring(0, 3);
```

​	创建了一个由字符"Hel"组成的字符串并赋值给字符串s,从第0个字符开始,到第3个字符为止(前闭后开)

### 拼接

​	Java语言允许使用+号连接/拼接两个字符串,即使它们只是字符串变量名。

​    如果需要把多个字符串放在一起,并用一个界定符分隔,可以使用**静态join方法**:

```java
 String all = String.join("/","M","S","L","XL","XXL"); 
```

​	输入的第一个字符串为界定符(例中为"/")

### 不可变字符串

​	String类没有提供用于修改字符串的方法,它不是C/C++里的字符型数组,只**大致类似于**char*指针。

​	要修改String类,只能使用取原字符串的子串再添加重组或直接赋新值的方法。

​    同时,不用像C/C++一样担心字符串的内存溢出问题。

### 检测字符串是否相等

​	可使用equals方法和equalsIgnoreCase方法或compareTo方法:

```java
String s ="hello";
String t ="Heil";
s.equals(t);//区分大小写
if(s.compareTo("hello")== 0)//用法与C/C++的strcmp完全一致,相同返回0
"Hello".equalsIgnoreCase("hel1o");//不区分大小写
//"hello".equals(t)也是合法的
```

​	如果字符串s与字符串t相等,则返回true,否则返回false。s与t可以是字符串变量,也可以使字符串字面量。

### 空串和Null串

​	空串 "" 是长度为 0 的字符串。可以调用以下代码检查一个字符串是否为空：

```java
if (str.length() = 0){
    //...
}
if (str.equals("")){
    //...
}
```

​	空串是一个 Java 对象， 有自己的串长度（ 0 ) 和内容（空）。不过， String 变量还可以存放一个特殊的值， 名为 null, 这表示目前没有任何对象与该变量关联。要检查一个字符串是否为 null, 要使用以下代码:

```java
if (str == null)
```

​	有时要检查一个字符串既不是 null 也不为空串,并必须首先检查 str 不为 null。

```java
if (str != null && str.length() != 0)
```

​	 如果在一个null 值上调用方法， 会出现错误。

### 码点与代码单元

​	Java 字符串由 char 值序列组成。 char 数据类型是一个采用 UTF-16 编码表示 Unicode 码点的代码单元。char类型相关请翻阅前文。

​	length 方法将返回采用 UTF-16 编码表示的给定字符串所需要的代码单元数量。例如：

```java
String greeting = "Hello";
int n = greeting.length();//is 5
```

​	要想得到实际的长度，即码点数量，可以调用：

```java
String greeting = "Hello";
int cpCount = greeting.codePointCount(0, greeting.length());
```

​	调用 s.charAt(n) 将返回位置 n 的代码单元，n 介于 0 ~ s.length() - 1 之间。例如：

```java
String greeting = "Hello";
char first = greeting.charAtO); // first is 'H'
char last = greeting.charAt(4); // last is ’o’
```

​	要想得到第 i个码点，应该使用下列语句:

```java
String greeting = "Hello";
int index = greeting.offsetByCodePoints(0, i);

int cp = greeting.codePointAt(index);
```

### 构建字符串(使用StringBuilder类)

​	有些时候, 需要由较短的字符串构建字符串， 例如,按键或来自文件中的单词。采用字符串连接的方式达到此目的效率比较低。每次连接字符串, 都会构建一个新的 String 对象,既耗时, 又浪费空间。使用 StringBuilder类就可以避免这个问题的发生。

​	如果需要用许多小段的字符串构建一个字符串， 那么应该按照下列步骤进行:

​		首先， 构建一个空的字符串构建器：

```java
StringBuilder builder = new StringBuilder();
```

​		当每次需要添加一部分内容时， 就调用 append 方法:

```java
builder.append(ch); // appends a single character
bui1der.append(str); // appends a string
```

​		在需要构建字符串时就调用 toString 方法, 将可以得到一个 String 对象, 其中包含了构建器中的字符序列:

```java
String completedString = builder.toString();
```

​		toString方法会返回包含 a 中数据元素的字符串， 这些数据元素被放在括号内， 并用逗号分隔。如

​			"{ 17, 19, 23, 29, 31, 37 }"

## 4.0	输入输出

### 读取输入

​	要想通过控制台进行输入, 首先需要构造一个Scanner对象, 并与“标准输入流”System.in关联:

```java
Scanner in = new Scanner(System.in);
```

​	之后, 就可以使用Scanner类的各种方法实现输入操作了。例如:

​		nextLine方法将输入一行:

```java
System.out.print("What is your name? ");
String name = in.nextLine();
```

​		在这里，使用 nextLine 方法是因为在输人行中有可能包含空格。要想读取一个单词（以空白符作为分隔符，) 就调用next方法:

```java
String firstName = in.next();
```

​		读取一个整数就调用nextInt方法:

```java
System.out.print("How old are you?");
int age = in.nextInt();
```

​		读取一个浮点数就用nextDouble方法。

Scanner 类定义在java.util 包中。 当使用的类不是定义在基本java.lang 包中时，一定要使用import 指示字将相应的包加载进来。

```java
import java.until.*;	//import java.util.Scanner;也行
```

*注: Scanner类的输入是可见的, 要想实现无回显的输入可以使用Console类*

### 格式化输出

​	Java中可以使用printf方法实现与C语言极为类似格式化打印(说起来C语言好像只有格式化打印吧)

```java
double x=3333.33333335
System.out.printf("%8.2f",x)
```

​	详细查表即可。

### 文件输入输出

​	暂且跳过



## 5.0	控制流程

​	Java 的控制流程结构与 C 和 C++ 的控制流程结构一样， 只有很少的例外情况: 

​		① 没有 goto 语句，但 **break 语句可以带标签**，可以利用它实现从内层循环跳出的目的(这种情况 C 语言采用 goto 语句实现。) 

​		② 还有一种变形的 for 循环，在 C 或 C++ 中没有这类循环。它有点类似于 C# 中的 foreach 循环, 可以用来依次处理数组中的每个元素, 格式为:

​			for(定义一个变量 : 集合名)

​				语句或语句块;

​		例如:

```java
String[] a = new String[100];
for(int element : a)
	System.out.println(element);
```

​		打印数组 a 的每一个元素，一个元素占一行。

### 块作用域

​	块（即复合语句）是指由一对大括号括起来的若干条简单的 Java 语句。块确定了变量的作用域。一个块可以嵌套在另一个块中。在C/C++中，可以在嵌套的块中重定义一个变量。在内层定义的变量会覆盖在外层定义的变量。这样，有可能会导致程序设计错误， 因此在 Java 中**不允许**这样做且无法通过编译。

### 判断、循环与多重选择

​	和C/C++相差无几。区别详见本节首。



## 6.0	大数值

​	如果基本的整数和浮点数精度不能够满足需求, 那么可以使用java.math包中的两个很有用的类:BigInteger(整数)和BigDecimal(浮点数)。这两个类可以处理包含任意长度数字序列的数值。

​	使用静态的valueOf方法可以将普通的数值转换为大数值：

```java
BigInteger a = Biglnteger.valueOf(100);
```

​	不能使用人们熟悉的算术运算符（如：+ 和 *) 处理大数值。 而需要使用大数值类中的 add 和 multiply 方法:

```java
BigInteger c = a.add(b); // c = a + b
BigInteger d = c.mutiply(b.add(Biglnteger.valueOf(2))); // d = c * (b + 2)
```

​	-和/也有对应的方法。



## 7.0	数组

​	数组是一种数据结构， 用来存储同一类型值的集合。在声明数组变量时， 需要指出数组类型 （ 数据元素类型紧跟 []) 和数组变量的名字。下面声明了整型数组a:

```java
int[] a
```

​	不过， 这条语句只声明了变量a， 并没有将a初始化为一个真正的数组。应该使用 **new** 运算符创建数组。

```java
int[] a = new int[100]
```

​	*注: ①创建一个数字数组时, 所有元素都初始化为0。boolean 数组的元素会初始化为 false 对象数组的元素则初始化为一个特殊值 null(如字符串的数组), 这表示这些元素目前未存放任何对象(与"空串不同")。*

​		  *②Java允许数组长度为0或变量。*

 		 *③Java 数组与C/C++数组在堆栈上有很大不同， 但基本上与分配在堆（heap) 上的数组指针一样。也就是说:*

```java
int[] a = new int[100]; // Java

//不同于

int a[100]; // C/C++

//而等同于

int* a = new int[100]; // C/C++
```

​	      *Java 中的 [ ] 运算符被预定义为检查数组边界, 而且没有指针运算, 即不能通过a加1得到数组的下一个元素。*

### 数组拷贝

​	在 Java 中，允许将一个数组变量拷贝给另一个数组变量。这时， 两个变量将引用同一个数组：

```java
int[] Prime = { 17, 88, 23, 29, 31, 12 };
int[] luckyNumbers = Prime;
1uckyNumbers[5] = 12; // now smallPrimes[5] is also 12
```

​	这里Java的数组名类似于C/C++的数组指针, 指向内存上的一个数组的指针。所以此例中内存上只有一个数组。

​	如果要实现内存上的"拷贝", 就要使用Arrays类的copyOf方法:	

```java
//码接上文
int[] copiedLuckyNumbers = Arrays.copyOf(luckyNumbers, luckyNumbers.length)
```

​	其中第二个参数是新数组的长度, 通常采用增大此参数的方法来增加数组的大小。多余的元素会按照本小节首的注①的规则进行填充, 缺少的元素则不会被拷贝。

​	*redundant:	adj.多余的, 累赘的*

​				   		*adj.被解雇的, 被裁员的*

### 命令行参数

​	和C有点区别, 先跳过

### 多重数组

​	大部分内容与C/C++相同。需要注意的是for each 循环语句不能自动处理二维数组的每一个元素。它是按照行， 也就是一维数组处理的要想访问二维数组a的所有元素， 需要使用两个嵌套的循环， 如下所示：

```java
for (double[] row : a)
	for (double value : row)
		//语句或语句块
```

​	若要想快速地打印一个二维数组的数据元素列表， 可以调用deepToString方法

```java
System.out.println(a.deepToString(a));
/*输出格式为:
[[16, 3, 2, 13], [5, 10, 11, 8], [9, 6, 7, 12], [4, 15, 14, 1]]*/
```

### 不规则数组

​	Java的多维数组不要求存在于高维(如第一维)的每个(子)数组长度都相等, Java可以创建长度"不规则"的多维数组。

```java
int[][] example = new int[13][];//要想创建一个不规则的数组， 首先需要分配一个具有所含行数的数组。
for (int n = 0; n <= 13 ; n++)
	example[n] = new int[n + 1];//接下来, 分配这些行。之后就可以在不超出边界的条件下访问其中元素了。
```

## 8.0	内存

​	JVM(虚拟机)占用的内存大概分为: **本地方法栈**、**寄存器**、**方法区**、**栈**、**堆**五块（Java SE 8)

​	代码读取到一个新类时会把它所有的方法和域加载到**方法区**暂存。

​	读取到一个方法时会把它加载到**栈内存**中，方法中的基本变量和引用变量的占用的"小"空间都在**栈内存**中。方法执行完毕后，方法的内存就出栈，内存被释放。

​	当使用new新建一个对象时，会在**堆内存**开辟一块空间存储这个对象。但当**栈内存**中无这个对象的引用时，这块内存也会被释放。

​	Java有回收垃圾内存的机制，会自动释放。

## 9.0	数据类型

​	分为两种: 基本数据类型和引用数据类型

### 基本数据类型

​	数据值是存储在自己的空间中(栈空间)

​	特点: 赋值给其它变量时，赋的是真实的值。

​	具体类型:boolean、byte、short、int、long、char、float、double

### 引用数据类型

​	数据值是存储在其他空间中，自己空间中存储的是地址值。

​	特点： 赋值给其他变量，赋的是地址值。其类似C/C++中的指针变量。

​	具体类型:数组、类对象以及除了基本数据类型外的所有类型。
