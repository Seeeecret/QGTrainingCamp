package Servlet;

import Service.userService;
import Utils.mapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
@WebServlet("/register")
public class registerServlet extends HttpServlet{
    @Override
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        // 设置响应内容类型
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean register = userService.register(username, password);
        HashMap<String, Object> jsonMap = new HashMap<>();
        if (register) {
            jsonMap.put("code", 200);
            jsonMap.put("msg", "注册成功");
        } else {
            jsonMap.put("code", 400);
            jsonMap.put("msg", "用户名重复, 注册失败");
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
