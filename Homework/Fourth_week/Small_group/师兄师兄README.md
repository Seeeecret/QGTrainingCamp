# 师兄师兄看这里

​	MVCDemoMySQLScript.sql是网页系统需要的mysql脚本,师兄导入表后也可以在表内查看测试用的账号密码，或者自己创建亦可。

​	druid.properties配置文件中有JDBCUtil类的配置:

- test02是我本地的数据库名，师兄记得修改成自己导入sql脚本的数据库名，不然会报错
- username和password也得修改成自己的数据库用户名和密码

​	本系统代码设置了绝对路径，所以只能在Tomcat的服务器上跑

​	在IDEA里用Tomcat运行后，系统的默认地址为http://localhost:8080/MVCDemo_war/loginMenu.html

​	我本次作业除了完成基础要求之外，还实现了提升1的自制CRUDUtil，提升2的全部:crying_cat_face:然后自己加了个记住密码的功能和防用户手动改url强行访问登录后页面的功能。
