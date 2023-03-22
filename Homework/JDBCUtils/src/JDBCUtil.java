import com.alibaba.druid.pool.DruidDataSourceFactory;
import javax.sql.DataSource;
import java.io.FileInputStream;
import java.util.Properties;
import java.sql.*;
/**
 * @author Secret
 */
public class JDBCUtil {

    private static DataSource dataSource;

    static {
        Properties druidProperties = new Properties();
        try {
            druidProperties.load(new FileInputStream("src/druid.properties"));
            dataSource = DruidDataSourceFactory.createDataSource(druidProperties);

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
    private JDBCUtil() {
    }

    /**
     * 获取数据源
     *
     * @return {@link DataSource}
     */
    public static DataSource getDataSource(){
        return dataSource;
    }


    /**
     * 获得连接
     *
     * @return {@link Connection}
     * @throws SQLException sqlexception异常
     */
    public static Connection getConnection() throws SQLException {
        return dataSource.getConnection();
    }


    /**
     * 获得语句
     *
     * @return {@link Statement}
     * @throws SQLException sqlexception异常
     */
    public static Statement getStatement() throws SQLException {
        return dataSource.getConnection().createStatement();
    }

    /**
     * 获取预编译语句
     *
     * @param sql sql
     * @return {@link PreparedStatement}
     * @throws SQLException sqlexception异常
     */
    public static PreparedStatement getPreparedStatement(String sql) throws SQLException {
            return dataSource.getConnection().prepareStatement(sql);
    }

    /**
     * 将连接交还数据源
     *
     * @param connection 连接
     * @throws SQLException sqlexception异常
     */
    public static void close(Connection connection) throws SQLException {
        if (connection!=null){
            connection.close();
        }
    }

    public static void close(Statement statement) throws SQLException {
        if (statement!=null){
            statement.close();
        }
    }
    public static void close(PreparedStatement preparedStatement) throws SQLException {
        if (preparedStatement!=null){
            preparedStatement.close();
        }
    }

    public static void close(ResultSet resultSet) throws SQLException {
        if (resultSet!=null){
            resultSet.close();
        }
    }

    public static void close(Connection connection,Statement statement,
                             PreparedStatement preparedStatement,
                             ResultSet resultSet) throws SQLException {
        if (connection!=null){
            connection.close();
        }
        if (statement!=null){
            statement.close();
        }
        if (preparedStatement!=null){
            preparedStatement.close();
        }
        if (resultSet!=null){
            resultSet.close();
        }
    }
    /**
     * 执行查询
     *
     * @param sql    sql
     * @param params 参数
     * @throws SQLException sqlexception异常
     */
    public static void executeQuery(String sql,Object... params) throws SQLException {
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            pstmt = JDBCUtil.getPreparedStatement(sql);
            for (int i = 0; i < params.length; i++) {
                pstmt.setObject(i + 1, params[i]);
            }
            rs = pstmt.executeQuery();
            showResultSet(rs);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            if(rs!=null){
                rs.close();
            }
            if (pstmt != null) {
                pstmt.close();
            }
        }
    }

    /**
     * 执行更新语句
     *
     * @param sql    sql
     * @param params 参数
     * @return int
     * @throws SQLException sqlexception异常
     */
    public static int executeUpdate(String sql,Boolean autoCommit,Object... params) throws SQLException {
    PreparedStatement pstmt = null;
    Connection connection = dataSource.getConnection();
    int result;
        connection.setAutoCommit(autoCommit);
    try {
        pstmt = connection.prepareStatement(sql);
        for (int i = 0; i < params.length; i++) {
            pstmt.setObject(i + 1, params[i]);
        }
        result = pstmt.executeUpdate();
    } catch (SQLException e) {
        connection.rollback();
        throw new RuntimeException(e);
    } finally {
        connection.commit();
        if (pstmt != null) {
            pstmt.close();
        }
        if (connection != null) {
            connection.close();
        }
    }
    return result;
}



    /**
     * 展示结果集
     *
     * @param rs 结果集
     * @throws SQLException sqlexception异常
     */
    public static void showResultSet(ResultSet rs) throws SQLException {
        ResultSetMetaData rsmd = rs.getMetaData();
        int columnCount = rsmd.getColumnCount();
        for(int i =1;i<=columnCount;i++){
            String columnName = rsmd.getColumnName(i);
            System.out.printf("%-16s",columnName);
            if(i<columnCount){
                System.out.print("\t");
            }else{
                System.out.println();
            }
        }
        while ((rs.next())){
            for (int i = 1; i <= columnCount; i++) {
                Object value = rs.getObject(i);
                System.out.printf("%-16s",value);

                if(i<columnCount){
                    System.out.print("\t");
                }else{
                    System.out.println();
                }
            }
        }
        rs.close();
    }


    /**
     * 打印全表
     *
     * @param tableName 表名
     * @throws SQLException sqlexception异常
     */
    public static void showTable(String tableName) throws SQLException {
        Connection connection = dataSource.getConnection();
        PreparedStatement ps = connection.prepareStatement("select * from " + tableName);
        ResultSet rs = ps.executeQuery();
        JDBCUtil.showResultSet(rs);
        ps.close();
    }

}



