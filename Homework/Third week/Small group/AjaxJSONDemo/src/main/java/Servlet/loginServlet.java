package Servlet;

import Service.User;
import Service.userService;
import Utils.mapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;

@WebServlet("/login")
public class loginServlet extends HttpServlet {
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
            jsonMap.put("code", 200);
            jsonMap.put("msg", "登陆成功");
            jsonMap.put("data", login);
        } else {
            jsonMap.put("code", 400);
            jsonMap.put("msg", "登陆失败");
        }
        mapper.writeValue(response.getWriter(), jsonMap);
    }


    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }

    @Override
    public void doPut(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean changePassword = userService.changePassword(username, password);
        HashMap<String, Object> jsonMap = new HashMap<>();
        if (changePassword) {
            jsonMap.put("code", 200);
            jsonMap.put("msg", "修改成功");
        } else {
            jsonMap.put("code", 400);
            jsonMap.put("msg", "用户不存在, 修改失败");
        }
    }
}
