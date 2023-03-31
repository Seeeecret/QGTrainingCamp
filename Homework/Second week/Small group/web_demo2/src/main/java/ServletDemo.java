import com.alibaba.druid.sql.ast.statement.SQLIfStatement;
import org.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.Enumeration;

/**
 * @author Secret
 */
@WebServlet("/ServletDemo")
public class ServletDemo extends HttpServlet {

    @Override
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        // 设置响应内容类型
        response.setContentType("text/html");
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username == null || username.isEmpty()|| password == null || password.isEmpty()) {
            // 如果没有请求主体，返回400 Bad Request状态码，并返回错误信息
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            PrintWriter out = response.getWriter();
            out.println("<h1>" + "Bad request" + "</h1>");
            out.println("<p>" + "Request body is missing or empty" + "</p>");
        }
        else {
            // 如果有请求主体，返回200 OK状态码，并返回请求主体
            response.setStatus(HttpServletResponse.SC_OK);
            PrintWriter out = response.getWriter();
            try {
                Connection connection = JDBCUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);
                preparedStatement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            out.println("<h1>" + "Successfuly Register" + "</h1>");
            out.println("<p>" + "username: " + username + "</p>");
            out.println("<p>" + "password: " + password + "</p>");
        }
    }
    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {// 使用Post请求方式登陆
        response.setContentType("text/html");
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username == null || username.isEmpty()|| password == null || password.isEmpty()) {
            // 如果没有请求主体，返回400 Bad Request状态码，并返回错误信息
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            PrintWriter out = response.getWriter();
            out.println("<h1>" + "Bad request" + "</h1>");
            out.println("<p>" + "Request body is missing or empty" + "</p>");
        }
        else {
            // 如果有请求主体，返回200 OK状态码，并返回请求主体
            PrintWriter out = response.getWriter();
            try {
                Connection connection = JDBCUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);
                if (preparedStatement.executeQuery().next()) {
                    response.setStatus(HttpServletResponse.SC_OK);
                    out.println("<h1>" + "Successfuly Login" + "</h1>");
                    out.println("<p>" + "username: " + username + "</p>");
                    out.println("<p>" + "password: " + password + "</p>");
                }
                else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    out.println("<h1>" + "Login Failed" + "</h1>");
                    out.println("<p>" + "username or password is incorrect" + "</p>");
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }
    @Override
    public void doHead(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {// 使用Head获取最后修改时间
        // 设置响应内容类型
        response.setContentType("text/html");
        // 设置响应头，Last-Modified为当前时间
        response.setHeader("Last-Modified", LocalDateTime.now().toString());
        // 不返回响应内容
    }
@Override
    public void doDelete(HttpServletRequest request,
                         HttpServletResponse response)
            throws ServletException, IOException {// 使用Delete请求方式删除用户
        // 设置响应内容类型
    response.setContentType("text/html");
    // 读取请求参数
    BufferedReader reader = request.getReader();
    StringBuilder stringBuilder = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
        stringBuilder.append(line);
    }
    reader.close();
    String requestBody = stringBuilder.toString();

    // 将请求体解析成 JSON 对象
    JSONObject jsonObject = new JSONObject(requestBody);
    String username = jsonObject.getString("username");
        int rows;
        try {
            rows = JDBCUtil.executeCommonUpdate("DELETE FROM users WHERE username = " + "'" + username+ "'");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        PrintWriter out = response.getWriter();
        if(rows == 0) {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            out.println("<h1>" + "No user with username: " + username + "</h1>");
        }
        else{
            response.setStatus(HttpServletResponse.SC_OK);
            out.println("<h1>" + "Deleted " + rows + " user with username: " + username + "</h1>");
        }
    }
@Override
    public void doPut(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {// 使用Put请求方式修改密码
        // 设置响应内容类型
        response.setContentType("text/html");
        // 读取请求参数
    BufferedReader reader = request.getReader();
    StringBuilder stringBuilder = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
        stringBuilder.append(line);
    }
    reader.close();
    String requestBody = stringBuilder.toString();

    // 将请求体解析成 JSON 对象
    JSONObject jsonObject = new JSONObject(requestBody);
    String username = jsonObject.getString("username");
    String password = jsonObject.getString("password");

        int rows;
        try {
            rows = JDBCUtil.executeCommonUpdate("UPDATE users SET password = " + "'" + password + "'" + " WHERE username = " + "'" + username + "'");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        PrintWriter out = response.getWriter();
        if(rows == 0) {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            out.println("<h1>" + "No user with username: " + username + "</h1>");
        }
        else{
            response.setStatus(HttpServletResponse.SC_OK);
            out.println("<h1>" + "Updated " + rows + " user with username: " + username + "</h1>");
        }
    }

//@Override
//    public void doTrace(HttpServletRequest request,
//                        HttpServletResponse response)
//            throws ServletException, IOException {// 使用Trace请求方式
//        response.setContentType("message/http");
//        // 获取请求头的枚举对象，用于遍历所有的请求头
//        Enumeration<String> headerNames = request.getHeaderNames();
//        StringBuilder message = new StringBuilder();
//        // 追加请求行，即请求方法、请求URI和协议版本，中间用空格分隔，最后用回车换行符结束
//        message.append(request.getMethod()).append(" ").
//                append(request.getRequestURI()).append(" ").
//                append(request.getProtocol()).append("\r\n");
//        // 追加请求头，即请求头的名称和值，中间用冒号和空格分隔，最后用回车换行符结束
//        while (headerNames.hasMoreElements()) {
//            String headerName = headerNames.nextElement();
//            String headerValue = request.getHeader(headerName);
//            message.append(headerName).append(": ").append(headerValue).append("\r\n");
//        }
//        // 追加空行，表示请求头结束
//        message.append("\r\n");
//        // 返回响应内容，即请求头的字符串表示
//        PrintWriter out = response.getWriter();
//        out.println(message.toString());
//    }
@Override
    public void doOptions(HttpServletRequest request,
                          HttpServletResponse response)
            throws ServletException, IOException {// 使用Options请求方式获取支持的请求方式
        // 设置响应内容类型
        response.setContentType("text/html");
        // 设置允许访问的方法
        response.setHeader("Allow Method", "GET, POST, HEAD, DELETE, PUT, OPTIONS");
        // 不返回响应内容
    }
}
