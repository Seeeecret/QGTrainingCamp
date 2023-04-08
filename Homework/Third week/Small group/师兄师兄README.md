# 师兄师兄看这里

​	AjaxDemoMySQLScript.sql是网页系统需要的mysql脚本,师兄导入表后也可以在表内查看测试用的账号密码，或者自己创建亦可。

​	druid.properties配置文件中有JDBCUtil类的配置:

- test02是我本地的数据库名，师兄记得修改成自己导入sql脚本的数据库名，不然会报错
- username和password也得修改成自己的数据库用户名和密码

​	本系统代码设置了绝对路径，所以只能在Tomcat的服务器上跑

​	在IDEA里用Tomcat运行后，系统的默认地址为http://localhost:8080/AjaxJSONDemo_war/loginMenu.html

​	我这个电子功德系统实现了**JSON数据响应为统一的结果集**处理，同时登陆后的界面实现了 **JQuery 和 Ajax 结合 Jdbc**实现前端对后端持久层的数据交互(虽然很简陋:crying_cat_face:

​	这次我的项目分包结构有所优化，师兄请欣赏~:rose:
