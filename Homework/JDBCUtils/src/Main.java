import java.sql.ResultSet;
import java.sql.SQLException;

public class Main {
    public static void main(String[] args) throws SQLException {

//        JDBCUtil.showTable("emp");
//        JDBCUtil.beginTransaction();
//        JDBCUtil.executeUpdateCommon("Update emp set age = ? where ID = ?",
//                false,28,1);
//        JDBCUtil.showTable("emp");
//        JDBCUtil.executeQueryCommon("select * from emp where id = ?",2);
//        JDBCUtil.showTable("emp");
//        JDBCUtil.endTransaction(false);
        JDBCUtil.executeQuerySpecial("*","emp","where ID < 6 && salary<=8000 ");

    }
}