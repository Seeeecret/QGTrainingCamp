import java.sql.SQLException;

public class Main {
    public static void main(String[] args) throws SQLException {

//        JDBCUtil.showTable("emp");
//        JDBCUtil.beginTransaction();
//        JDBCUtil.executeUpdate("Update emp set age = ? where ID = ?",
//                false,18,3);
//        JDBCUtil.showTable("emp");
        JDBCUtil.executeQuery("select * from emp where id = ?",2);
        JDBCUtil.showTable("dept");
//        JDBCUtil.endTransaction(false);


    }
}