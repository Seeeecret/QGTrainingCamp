package Service;

import DAO.userDAO;
import Utils.JDBCUtil;

import java.sql.Connection;
import java.sql.SQLException;

public class userService {

    public static User login(String username, String password) {
        User user = null;
        try (Connection connection = JDBCUtil.getConnection()) {
            user = userDAO.query(connection, username);
            if (user != null && user.getPassword().equals(password)) {
                return user;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return user;
    }

    // 注册账号
    public static boolean register(String username, String password) {
        User user = null;
        try (Connection connection = JDBCUtil.getConnection()) {
            user = userDAO.query(connection, username);
            if (user == null) {
                user = new User(username, password);
                userDAO.insert(connection, user);
                return true;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return false;
    }

    public static boolean changePassword(String username, String password) {
        User user = null;
        try (Connection connection = JDBCUtil.getConnection()) {
            user = userDAO.query(connection, username);
            if (user != null) {
                user.setPassword(password);
                userDAO.update(connection, user);
                return true;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return false;
    }

    public static boolean deleteUser(String username) {
        User user = null;
        try (Connection connection = JDBCUtil.getConnection()) {
            user = userDAO.query(connection, username);
            if (user != null) {
                userDAO.delete(connection, username);
                return true;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return false;
    }

    public userService() {

    }
}
