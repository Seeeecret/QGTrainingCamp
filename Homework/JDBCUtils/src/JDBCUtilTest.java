import org.junit.Test;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

class JDBCUtilTest {

    @org.junit.jupiter.api.Test
    void createNewTable() throws SQLException {
        JDBCUtil.createNewTable("create table account_2\n" +
                "(\n" +
                "    ID    int auto_increment comment '账户ID',\n" +
                "    name  varchar(20)        not null comment '姓名',\n" +
                "    money double default 0.0 null comment '存款',\n" +
                "    constraint account_pk\n" +
                "        primary key (ID)\n" +
                ")\n" +
                "    comment '银行账户例子';");
    }

    @org.junit.jupiter.api.Test
    void executeCommonQuery() {
        JDBCUtil.executeCommonQuery("select * from emp where id = ? or workaddress = ?", 2, "成都");
    }

    @org.junit.jupiter.api.Test
    void executeSpecialQuery() {
        JDBCUtil.executeSpecialQuery("name,gender", "emp", "where age<= 26");
    }


    @org.junit.jupiter.api.Test
    void showTable() throws SQLException {
        JDBCUtil.showTable("emp");
        JDBCUtil.showTable("account");
    }

    @org.junit.jupiter.api.Test
    void executeCommonInsert() throws SQLException {
        System.out.println("影响语句数:" +
                JDBCUtil.executeCommonInsert("insert into account (ID, name, money) VALUES (5,'吴七',5000)"));
    }

    @org.junit.jupiter.api.Test
    void executeSpecialInsert() throws SQLException {
        System.out.println("影响语句数:" +
                JDBCUtil.executeSpecialInsert("account", "(ID,name,money)", "(6,'孙八',10000),(7,'钱九',9000)"));
    }

    @org.junit.jupiter.api.Test
    void executeCommonUpdate() throws SQLException {
        JDBCUtil.showTable("emp");
        System.out.println("影响语句数:" +
                JDBCUtil.executeCommonUpdate("Update emp set age = ? where ID = ?", 8, 1));
        JDBCUtil.showTable("emp");

    }

    @org.junit.jupiter.api.Test
    void executeSpecialUpdate() throws SQLException {
        JDBCUtil.showTable("emp");
        System.out.println("影响语句数:" +
                JDBCUtil.executeSpecialUpdate("emp", "where ID = 3 or workNo = 00004", "age = 12", "workaddress = ' 广州' "));
        JDBCUtil.showTable("emp");
    }

    @org.junit.jupiter.api.Test
    void executeSpecialDelete() throws SQLException {
        JDBCUtil.showTable("account");
        System.out.println("影响语句数:" + JDBCUtil.executeSpecialDelete("account", "where ID > 4"));
        JDBCUtil.showTable("account");
    }

    @org.junit.jupiter.api.Test
    void showResultSet() throws SQLException {
        Connection connection = JDBCUtil.getConnection();
        String sql = "select * from emp";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        ResultSet resultSet = preparedStatement.executeQuery();
        JDBCUtil.showResultSet(resultSet);
        connection.close();
    }

    @org.junit.jupiter.api.Test
    void beginTransaction() throws SQLException {
        Connection connection = JDBCUtil.getConnection();
        String sql = "update account set money = 100000";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        JDBCUtil.beginTransaction(connection);
        JDBCUtil.showTable("account");
        System.out.println("影响语句数量:"+ preparedStatement.executeUpdate());
        JDBCUtil.rollbackTransaction(connection);
        JDBCUtil.showTable("account");
        connection.close();
    }

    @org.junit.jupiter.api.Test
    void commitTransaction() throws SQLException {
        Connection connection = JDBCUtil.getConnection();
        String sql = "update account set money = 100000 where name = '张三'";
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        JDBCUtil.beginTransaction(connection);
        JDBCUtil.showTable("account");
        System.out.println("影响语句数量:"+ preparedStatement.executeUpdate());
        JDBCUtil.commitTransaction(connection);
        JDBCUtil.showTable("account");
        connection.close();
    }

    @org.junit.jupiter.api.Test
    void rollbackTransaction() throws SQLException, InterruptedException {
        beginTransaction();
    }
}