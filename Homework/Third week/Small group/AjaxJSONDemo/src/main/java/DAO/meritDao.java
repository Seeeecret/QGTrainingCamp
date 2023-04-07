package DAO;

import Utils.JDBCUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;


public class meritDao {

    public meritDao() {

    }

    public static int addMerit(String username) throws SQLException {
        Connection connection = JDBCUtil.getConnection();
        PreparedStatement preparedStatement = connection.prepareStatement("UPDATE user_merit SET merit = merit + 1 WHERE username = ?");
        preparedStatement.setString(1, username);
        return preparedStatement.executeUpdate();
    }

}
