package Servlet;

import Service.User;
import Service.userService;
import DAO.userDAO;
import Utils.mapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;

@WebServlet("/delete")
public class deleteServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        // 设置响应内容类型

        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        User login = userService.login(username, password);
        HashMap<String, Object> jsonMap = new HashMap<>();

        if (login != null) {
            boolean delete = userService.deleteUser(username);
            jsonMap.put("username", login.getUsername());
            jsonMap.put("password", login.getPassword());
            jsonMap.put("code", 200);
            jsonMap.put("msg", "删除成功");
        } else {
            jsonMap.put("code", 400);
            jsonMap.put("msg", "账号或密码错误, 删除失败");
        }
        mapper.writeValue(response.getWriter(), jsonMap);

    }

    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
