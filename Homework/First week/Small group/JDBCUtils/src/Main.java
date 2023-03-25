import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * @author Secret
 */
public class Main {
    public static void main(String[] args) throws SQLException {
//        JDBCUtil.showTable("emp");
//        JDBCUtil.executeCommonUpdate("Update emp set age = ? where ID = ?",
//                28,1);
//        JDBCUtil.executeSpecialUpdate("emp","where ID = 3 or workNo = 00004","age = 26","workaddress = \' 广州\' ");
//        JDBCUtil.executeCommonQuery("select * from emp where id = ?",2);
//        JDBCUtil.executeCommonQuery("select dept.* ,a.人数 from dept left outer join (select count(dept_id) as 人数,dept_id\n" +
//                "from emp group by dept_id)as a on dept.ID = a.dept_id");
//        JDBCUtil.executeSpecialQuery("*","emp","where ID < 6 && salary<=8000 ");
//        JDBCUtil.executeCommonInsert("insert into dept (ID,name) values (7,'公关部')");
//        JDBCUtil.executeSpecialInsert("dept","(ID,name)", "(6,'广告部')");
//        JDBCUtil.executeSpecialDelete("dept","where ID = 7");
//        JDBCUtil.executeSpecialDelete("dept","where ID = 6");
//        Connection connection = JDBCUtil.getConnection();
//        PreparedStatement preparedStatement = connection.prepareStatement("insert into account (ID, name, money) VALUES (4,'赵六',5000)");
//        JDBCUtil.beginTransaction(connection);
//        ResultSet resultSet = preparedStatement.executeQuery();
//        int i = preparedStatement.executeUpdate();
//        System.out.println(i);
//        JDBCUtil.showResultSet(resultSet);
//        JDBCUtil.commitTransaction(connection);
//        JDBCUtil.rollbackTransaction(connection);
//        JDBCUtil.close(preparedStatement);
//        JDBCUtil.close(connection);
//        JDBCUtil.createNewTable("create table account2\n" +
//                "(\n" +
//                "    ID    int auto_increment comment '账户ID',\n" +
//                "    name  varchar(20)        not null comment '姓名',\n" +
//                "    money double default 0.0 null comment '存款',\n" +
//                "    constraint account_pk\n" +
//                "        primary key (ID)\n" +
//                ")\n" +
//                "    comment '银行账户例子';");

    }
}