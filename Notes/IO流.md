# IO流

​	IO流失存储和读取数据的方案。IO流中是以程序为参照物在读写(文件、网络数据.......)。

## 1.0	分类

​	IO流按流的方向来分可分为: 

- 输入流
- 输出流

​	按操作文件类型来分可分为: 

- 字节流(所有类型文件): 

  - 字节输入流(InputStream):
    - FileInput:操作本地文件的字节输入流
  - 字节输出流(OutputStream):

  - - FileOutput:操作本地文件的字节输出流



- 字符流(纯文本文件.txt .md .xdm .lrc等):
  - 字符输入流(Reader)
    - FileReader:操作本地文件的字符输入流
  - 字符输出流(Writer)
    - FileWriter:操作本地文件的字符输出流



## 2.0	操作

### 2.1	创建字节输出流对象

​	细节1:参数是字符串表示的路径或者是File对象都是可以的

​	细节2:如果文件不存在会创建一个新的文件，但是要保证父级路径是存在的。

​	细节3:如果文件已经存在，方法会清空文件。

​	细节4:使用构造器时，第一个参数是文件的相对/绝对路径，第二个选填参数是文件的续写开关，默认是false。

### 2.2	写数据

​	细节1: write方法的参数是整数，但是实际上写到本地文件中的是整数在ASCII上对应的字符

​	写入数据的三种方式:

```java
void write(int b)//一次写一个字节数据
void write(byte[] b)//一次写一个字节数组数据,每次write都会覆盖之前上一次存入数组的数据,如果最后一次读取长度小于最大长度，则有一部分不会被覆盖。解决方案见下
void write(byte[] b, int off， int len)//一次写一个字节数组的部分数据,off是起始索引,len是读入个数
```

​	细节2:Sting类里的getBytes方法可以将字符串转换为字节数组，可以利用此特性去write字符串

​	细节3:Windows中的换行符是'\r\n'，但Java会自动补全，所以写'\n'或'\r'都可以，最好还是写全。

#### 2.21	小知识

​	若想实现简单的数据加密效果，可以在用字节输入流读入数据的时候进行异或^一个数字n并写出。解密时再把加密文件异或^一个数字n即可解密。

### 2.3	读数据

 1. 如果文件不存在，就直接报错

 2. 一次读一个字节，读出来的是数据再ASCII上对应的数字

 3. 读到文件末尾了，read方法返回-1

 4. ```java
    /////////////循环读取
    FileInputStream fis = new FileInputStream(路径);
    FileOutputStream fos = new FileOutputStream(路径);
    int b;
    while((b = fis.read()) != -1){
        sout.(char)b;//循环读取
        fos.write(b);//边读边写
    }
    ////////////正确的多块读取
    int len;
    byte[] bytes = new byte[1024*1024*5];
    for((len = fis.read(bytes) != -1){
        sout.new String(bytes,0,len);
        fos.write(bytes,0,len);
    }
    
    ```





### 2.4	正确用trycatchfinally处理异常

​	!!只有实现了AutoCloseable的接口的类的流对象才能使用优化方案

```java
FileInputstream fis = null;
FileOutputStream fos = null;
try {
	fis = new FileInputstream( name: "D: \litheima\ [movie.mp4" );//不能在这里新建变量
	fos = new Fileoutputstream( name: "myiollcopy.mp4");//局部变量仅在本代码块内有效
//2.拷贝
	int len;
	byte[] bytes = new byte[1024 *1024*5];
	while((len = fis.read( bytes)) != -1){
		fos.write(bytes, off: e,len);
    }
		catch (IOException e) {
			e.printStackTrace();
        }finally {
// 3.释放资源
			if(fos != null){
				try {
					fos.close();
				}catch ( IOException e) {
					e.printstackTrace();
				}
			}
			if(fis != nu1l){
				try {
					fis.close();
				}catch ( IOException e) {
					e.printStackTrace();
				}
            }
        }
///////////////以下是JKD7的优化方案。!!只有实现了AutoCloseable的接口的类的流对象才能使用此方案
    try (创建流对象1;创建流对象2){
	int len;
	byte[] bytes = new byte[1024 *1024*5];
        while((len = fis.read( bytes)) != -1){
		fos.write(bytes, off: e,len);
        }
		catch (IOException e) {
			e.printStackTrace();
        }//!!只有实现了AutoCloseable的接口的类的流对象才能使用此方案
        ////资源用完会自动释放
////////////////JDK9里有新的特性，创建流对象可在外部完成,try中仅需输入引用变量。在此先不做展示
```

​	

### 2.4	释放资源

​	细节:每次使用完流之后都要释放资源 .close();

​	细节: 

- 先打开的后关闭，后打开的先关闭。这是为了保证在关闭一个流之前，所有依赖它的流都已经关闭了。
- 如果一个流依赖另一个流，例如处理流依赖节点流，应该先关闭处理流，再关闭节点流。这是因为处理流在关闭时会调用节点流的close方法，所以不需要再单独关闭节点流。



## 3.0	编码规则

### 3.1	ASCII

​	编码规则:7位存数据，8位补0.

​	解码规则:直接转成十进制,查表

### 3.2	GBK(国标扩展)

​	英文编解码同ASCII

​	中文编码:一个汉字两个字节(16位存储) 为了区分，高位字节二进制一定以1开头

​	中文解码:直接转成十进制，查表

### 3.3	Unicode(万国码)

​	有多种不同的编码规则,以UTF-8(不是字符集)为例

​	UTF-8用1~4个字节保存文字，简单来说,英文一个字节，中文三个字节

​	英文完全兼容ASCII

​	中文编码遵循格式:1110xxxx	10xxxxxx 10xxxxxx

### 3.4	乱码原因

​	原因1:读取数据时未读完整个汉字

​	原因2:编码和解码时的方式不统一

#### 3.41	如何不产生乱码?

​	1，不要用字节流读取文本文件
​	2，编码解码时使用同一个码表，同一个编码方式



### 3.5	Java中编解码的方法

| string类中的方法                           | 说明                 |
| ------------------------------------------ | -------------------- |
| public byte[] getBytes()                   | 使用默认方式进行编码 |
| public byte[] getBytes(string charsetName) | 使用指定方式进行编码 |
| string(byte[] bytes)                       | 使用默认方式进行解码 |
| string(byte[ ] bytes,string charsetName)   | 使用指定方式进行解码 |

## 4.0	字符流

​	字符流的底层其实就是字节流+字符集。	

​	特点:

​	输入流FileReader:一次读一个字节，遇到中文时，一次读多个字节

​	输出流FileWriter:底层会把数据按照指定的编码方式进行编码，变成字节再写到文件中

​	仅适用于纯文本文件

### 4.2	读数据

| 成员方法                       | 说明                         |
| ------------------------------ | ---------------------------- |
| public int read()              | 读取数据，读到末尾返回-1     |
| public int read(char[] buffer) | 读取多个数据，读到末尾返回-1 |

​	细节1:按字节进行读取，遇到中文，一次读多个字节，读取后解码，返回一个整数
​	细节2:读到文件末尾了,read方法返回-1。

​	**细节3**:new字符输入流时实际上会在底层创建一个长度为8192的字节数组作为缓冲区(初始化为0),第一次read会尝试填满缓冲区，此后就在缓冲区里读，读到尽头再重新填缓冲区。

​	read()细节:

​	1. read():默认也是一个字节一个字节的读取的,如果遇到中文就会一次读取多个

2. 在读取之后，方法的底层还会进行解码并转成十进制。最终把这个十进制作为返回值这个十进制的数据也表示在字符集上的数字。下例:

	- 英文:文件里面二进制数据0110 0001

​		read方法进行读取，解码并转成十进制97

 - 中文:文件里面的二进制数据11100110 10110001 10001001

   read方法进行读取，解码并转成十进制27721

 - 想要输出正确的字符，**强转(char)**即可

​	read(char[] buffer)细节:

1. 这个方法将读取数据，解码，强转三步合并了，把强转后的字符放到了数组当中
1. 同样需要留意文本末尾读取内容无法填充满导致<u>无法完全覆盖</u>上次读取内容的问题



### 4.3	写数据

​	append参数若留空则默认为false

| 构造方法                                          | 说明                                     |
| ------------------------------------------------- | ---------------------------------------- |
| public Filewriter(File file, boolean append)      | 创建字符输出流关联本地文件，默认续写关闭 |
| public Filewriter(String pathname,boolean append) | 创建字符输出流关联本地文件，续写同上     |



| 成员方法                                  | 说明                   |
| ----------------------------------------- | ---------------------- |
| void write(int c)                         | 写出一个字符           |
| void write(string str)                    | 写出一个字符串         |
| void write(string str, int off， int len) | 写出一个字符串的一部分 |
| void write(char[] cbuf)                   | 写出一个字符数组       |
| void write(char[] cbuf, int off, int len) | 写出字符数组的一部分   |

​	细节1:字符输入流其实也有长度为8192的缓冲区(此时大小不是8192bytes了是8192个char的大小)的机制。满足以下三种情况之一才会将缓冲区的内容刷新进目的地。

1. 装满了
2. flush()
3. close()

​	所以有时候会明明write了却没在文件里看到。

## 5.0	缓冲流

​	Buffered前缀+四个基本流名字=缓冲流名。字节缓冲流可以明显提升读写性能，但基本字符流本身就自带缓冲区，所以字符缓冲流对读写效率提升较小。

​	缓冲流的工作原理是，在创建缓冲流对象时，会创建一个内置的默认大小的缓冲区数组。当读取数据时，缓冲输入流会一次性从源流中读取多个字节或字符到缓冲区中，然后再从缓冲区中逐个返回给程序。当写入数据时，缓冲输出流会先将数据写入到缓冲区中，直到缓冲区满了或者调用了flush方法或者关闭了流，才会将缓冲区中的数据一次性写出到目标流中。

### 5.1	构造方法

​	

| 字节/字符缓冲流方法名称                       | 说明                 |
| --------------------------------------------- | -------------------- |
| public BufferedReader(Reader r)               | 把基本流包装成高级流 |
| public BufferedReader(Writer r)               | 把基本流包装成高级流 |
| public BufferedInputStream(InputStream ips)   | 把基本流包装成高级流 |
| public BufferedOutputStream(OutputStream ops) | 把基本流包装成高级流 |

​	其构造需要一个基本字节/字符流对象。



### 5.2	特殊方法

​	**字符缓冲流**有两个独有的、非常有用的方法:

```java
////	字符输入缓冲流:
public String readLine();			//读取一行数据，如果没有数据可读，返回null
////	字符输出缓冲流:
public void newLine();				//跨平台的通用的换行功能方法
```





## 6.0	转换流

​	转换流是字符流和字节流之间的桥梁。它们是**字符流**体系下的高级流,继承了Reader和Writer。主要作用为:

	1. 指定字符集读写
	1. 字节流想要使用字符流中的方法

### 6.1	构造方法

```java
public InputStreamReader(InputStream ips,String charsetName);
public OutputStreamWriter(OutputStream ops,String charsetName);    
```





## 7.0	序列化流和反序列化流

​	它们是**字节流**体系下的高级流，继承了InputStream和OutputStream。主要是对Java中的对象进行写入写出操作。

| 序列化流的构造方法和成员方法                | 说明                 |
| ------------------------------------------- | -------------------- |
| public ObjectOutputStream(OutputStream out) | 把基本流包装成高级流 |
| public final void writeObject(Object obj)   | 写出序列化流中的对象 |

| 反序列化流的构造方法和成员方法            | 说明                                               |
| ----------------------------------------- | -------------------------------------------------- |
| public ObjectInputStream(InputStream out) | 把基本流包装成高级流                               |
| public Object readObject()                | 把序列化到本地文件中的对象，读到程序中来，需要强转 |

​	序列化流可以把Java中的对象写到本地文件中。但若想让对象可以写出，需要让Javabean类实现Serializable接口，否则会报NotSerializableException异常。

​	Serializable接口是**标记型接口**，实现此接口说明此类可以被序列化。

​	序列化流写到文件中的数据不可更改，否则会破坏文件完整性。

### 7.1	版本号

​	如果实现了一个类实现了Serializable接口，那么Java底层就会根据的所有的内容(变量、方法)计算出一个long类型的变量——序列号(版本号)。创建对象时对象也会携带此序列号。这个类的对象被序列化写入文件时，版本号也会写入。

​	但若此时我们修改原本的Javabean类，序列号也会重新生成。此时若反序列化，就会抛出异常。

#### 7.12	解决方法

​	自己定义序列号，将序列号固定下来，就不会再出现此类问题:

```java
private static final long serivalVerionUID =1L;//名字固定不可修改
```

​	



### 7.3	如果有我不想序列化的变量?

​	使用**transient**瞬态关键字修饰变量，即可让此变量不被序列化到本地文件中。此时反序列化transient的变量值为默认。





## 8.0	打印流

​	打印流是**字节输出流**和**字符输出流**下的高级流，只有**写**，没有读。其主要指PrintStream,PrintWriter两个类。

​	特点1:打印流只操作文件目的地，不操作数据源

​	特点2:其特有的方法可以实现数据的**原样写出**。

​				其特有的方法可以实现**自动刷新**，**自动换行**。

### 8.1	字节打印流

​	构造方法:字节流底层没有缓冲区，开不开自动刷新都一样。

| 构造方法                                                     | 说明                                 |
| ------------------------------------------------------------ | ------------------------------------ |
| public Printstream(outputstream/File/String)                 | 构造方法关联字节输出流/文件/文件路径 |
| public PrintStream(String fileName，Charset charset)         | 指定字符编码                         |
| public Printstream(OutputStream out, boolean autoFlush)      | 自动刷新                             |
| public PrintStream(OutputStream out, boolean autoFlush,String encoding) | 指定字符编码且自动刷新               |

​	成员方法:

| 成员方法                                           | 说明                                            |
| -------------------------------------------------- | ----------------------------------------------- |
| public void write(int b)                           | 常规方法:规则跟之前一样，将指定的字节写出       |
| public void println(Xxx xx)                        | **特有方法**:打印任意数据，自动刷新，自动换行   |
| public void print(Xxx xx)                          | **特有方法**:打印任意数据，不换行               |
| public void printf(String format, object.. . args) | **特有方法**:带有占位符的格式化打印语句，不换行 |

### 8.2	字符打印流

​	构造方法:字符流底层有缓冲区，想要**自动刷新**可以手动开启。

| 构造方法                                                     | 说明                         |
| ------------------------------------------------------------ | ---------------------------- |
| public Printwriter(write/File /String)                       | 关联字节输出流/文件/文件路径 |
| public Printwriter( String fileName,Charset charset)         | 指定字符编码                 |
| public Printwriter(Write w, boolean autoFlush)               | 更多操作自动刷新             |
| public Printwriter(OutputStream out，boolean autoFlush，Charset charset) | 指定字符编码且自动刷新       |

​	成员方法同字节打印流。



### 8.3	System.out打印流

​	System.out是一种特殊的打印流，它是系统中的**标准输入流**。此打印流在虚拟机启动的时候由虚拟机创建，默认指向控制台。它会自动刷新。

```java
PrintStream ps =System.out;//获取标准输入流对象
//平常我们都使用链式编程
System.out.println("123");
```

​	此流在程序中是唯一的，关闭后就无法再开启。



## 9.0	压缩流

​	压缩流是字节输入流和字节输出流下的高级流。压缩流是一种可以将输入的数据变为压缩格式后进行输出，或者读取压缩格式的数据后，解压为正常数据的流。例如ZipOutputStream、ZipInputStream、GZIPOutputStream、GZIPInputStream等，它们都位于java.util.zip包下。

​	使用这些压缩流时，需要注意以下几点：

- 压缩流需要包装在其他基本流上，例如FileOutputStream、FileInputStream等。
- 压缩流需要关闭才能完成写入或读取操作。
- ZipOutputStream和ZipInputStream需要使用ZipEntry类来表示每一个被压缩或解压的子文件。
- ZipEntry类有一些方法可以设置或获取子文件的属性，例如名称、大小、时间等。
- GZIPOutputStream和GZIPInputStream不需要使用ZipEntry类，因为它们只处理单个文件。

### 9.1	代码示例

```java
//压缩文件或文件夹
public static void zipFile(String srcPath,String destPath) throws IOException {
    //创建一个输出流
    FileOutputStream fos = new FileOutputStream(destPath);
    //创建一个压缩流
    ZipOutputStream zos = new ZipOutputStream(fos);
    //创建一个文件对象，表示要压缩的源路径
    File srcFile = new File(srcPath);
    //调用一个方法，递归压缩文件或文件夹
    zipFile(srcFile,zos,"");
    //关闭流
    zos.close();
}

//递归压缩文件或文件夹
public static void zipFile(File srcFile,ZipOutputStream zos,String baseDir) throws IOException {
    //判断是否是文件夹
    if(srcFile.isDirectory()) {
        //获取该文件夹下的所有子文件或子文件夹
        File[] files = srcFile.listFiles();
        //遍历数组，对每个子文件或子文件夹进行处理
        for(File file:files) {
            //递归调用本方法，注意修改最后一个参数，表示在zip中的路径
            zipFile(file,zos,baseDir+srcFile.getName()+"/");
        }
    }else {
        //如果是单个文件，就直接压缩
        //创建一个输入流，读取该文件的内容
        FileInputStream fis = new FileInputStream(srcFile);
        //创建一个压缩实体，表示在zip中的一个子项（可以是单个文件或者空目录）
        ZipEntry entry = new ZipEntry(baseDir+srcFile.getName());
        //将该实体放入zip中
        zos.putNextEntry(entry);
        //定义一个字节数组，用来读写数据
        byte[] buffer = new byte[1024];
        int len;
        while((len=fis.read(buffer))!=-1) {
            zos.write(buffer,0,len);
            zos.flush();
        }
        fis.close();
    }
}

//解压zip格式的文件到指定目录下（目录不存在则自动创建）
public static void unzip(String zipPath,String destDir) throws IOException {
    //创建一个输入流，读取zip格式的数据源（可以是本地路径也可以是网络路径）
    File zipfile = new File(zipPath);
    //创建一个解压流，包装输入流（注意编码格式）
    FileInputStream src = new FileInputStream(zipfile);
    ZipInputStream zip = new ZipInputStream(src);
    //定义一个压缩实体，用来表示zip中的每个子项
    ZipEntry entry;
    //循环读取每个子项
    while((entry=zis.getNextEntry())!=null) {
        //获取子项的名称
        String name = entry.getName();
        //判断是否是空目录
        if(entry.isDirectory()) {
            //如果是空目录，就在指定目录下创建对应的文件夹
            new File(destDir+name).mkdirs();
        }else {
            //如果是单个文件，就在指定目录下创建对应的文件，并写入数据
            FileOutputStream fos = new FileOutputStream(destDir+name);
            byte[] buffer = new byte[1024];
            int len;
            while((len=zis.read(buffer))!=-1) {
                fos.write(buffer,0,len);
                fos.flush();
            }
            fos.close();
        }
    }
    zis.close();
}
```



## 10.0	Apache Commons-io工具包

​	Commons-io是apache开源基金组织提供的一组有关IO操作的开源工具包

​	作用:提高IO流的开发效率。

### 10.1	常见方法

#### 10.11	FileUtils类

| FileUtils类(文件/文件夹相关)                                 | 说明                         |
| ------------------------------------------------------------ | ---------------------------- |
| static void copyFile(File srcFile，File destFile)            | 复制文件                     |
| static void copyDirectory(File srcDir， File destDir)        | 复制文件夹                   |
| static void copyDirectoryToDirectory(File srcDir， File destDir) | 复制文件夹                   |
| static void deleteDirectory(File directory)                  | 删除文件夹                   |
| static void cleanDirectory(File directory)                   | 清空文件夹                   |
| static string readFileToString(File file，Charset encoding)  | 读取文件中的数据变成成字符串 |
| static void write(File file， CharSequence data，String encoding) | 写出数据                     |

- copyDirectory方法将指定的目录及其所有子目录和文件复制到指定的目标位置,也就是说，<u>源目录和目标目录会合并</u>。目标位置是目录的新位置和名称。如果目标位置不存在，它会被创建。如果该位置已经存在一个同名的目录，它会抛出一个IOException异常。
- copyDirectoryToDirectory方法将指定的目录及其所有子目录和文件复制到指定的父目录下,也就是说，源<u>目录会成为目标目录的一个子目录</u>。父目录必须已经存在。如果目标目录不存在，它会创建它。如果它存在，它会将源目录和目标目录合并同时覆盖同名文件。

#### 10.12	IOUtils类

| IOUtils类（流相关相关)                                       | 说明       |
| ------------------------------------------------------------ | ---------- |
| public static int copy(InputStream input，outputStream output) | 复制文件   |
| public static int copyLarge(Reader input, writer output)     | 复制大文件 |
| public static string readLines(Reader input)                 | 读取数据   |
| public static void write(String data，outputstream output)   | 写出数据   |

