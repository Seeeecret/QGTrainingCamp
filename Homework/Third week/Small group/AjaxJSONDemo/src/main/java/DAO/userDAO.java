package DAO;

import Service.User;
import Utils.JDBCUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class userDAO {
    public static User query(Connection connection, String username) {
        User user = null;
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM user_merit WHERE username = ?")) {
            statement.setString(1, username);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    user = new User();
                    user.setUsername(resultSet.getString("username"));
                    user.setPassword(resultSet.getString("password"));
                    user.setMerit(resultSet.getInt("merit"));
                    JDBCUtil.close(resultSet);
                }
            }
            finally {
                JDBCUtil.close(statement);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return user;
    }


    public static int insert(Connection connection, User user) {
        int i = 0;
        try (PreparedStatement statement = connection.prepareStatement("INSERT INTO user_merit (username, password) VALUES (?, ?)")) {
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            i = statement.executeUpdate();
            JDBCUtil.close(statement);
            return i;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static int update(Connection connection, User user) {
        try (PreparedStatement statement = connection.prepareStatement("UPDATE user_merit SET password = ? WHERE username = ?")) {
            statement.setString(1, user.getPassword());
            statement.setString(2, user.getUsername());
            int i = statement.executeUpdate();
            JDBCUtil.close(statement);
            return i;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static int delete(Connection connection, String username) {
        try (PreparedStatement statement = connection.prepareStatement("DELETE FROM user_merit WHERE username = ?")) {
            statement.setString(1, username);
            int i = statement.executeUpdate();
            JDBCUtil.close(statement);
            return i;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }


    public static int addMerit(String username) throws SQLException {
        Connection connection = JDBCUtil.getConnection();
        PreparedStatement preparedStatement = connection.prepareStatement("UPDATE user_merit SET merit = merit + 1 WHERE username = ?");
        preparedStatement.setString(1, username);
        int i = preparedStatement.executeUpdate();
        JDBCUtil.close(preparedStatement);
        JDBCUtil.close(connection);
        return i;
    }

    public userDAO() {
    }
}
