package Servlet;
import DAO.userDAO;
import Service.User;
import Service.userService;
import Utils.mapper;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.HashMap;
@WebServlet("/addMerit")
public class addMeritServlet extends HttpServlet{
    @Override
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws IOException {
        // 设置响应内容类型
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        HashMap<String, Object> jsonMap = new HashMap<>();
        String username = request.getParameter("username");
        int i = 0;
        try {
            i = userDAO.addMerit(username);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            int merit = userService.query(username).getMerit();
            if (i == 0) {
                jsonMap.put("data", i);
                jsonMap.put("code", 400);
                jsonMap.put("msg", "功德增加失败");
            } else {
                jsonMap.put("code", 200);
                jsonMap.put("data", merit);
                jsonMap.put("msg", "功德增加成功");
            }
        }
        mapper.writeValue(response.getWriter(), jsonMap);

    }
    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws IOException {
        doGet(request, response);
    }
}
