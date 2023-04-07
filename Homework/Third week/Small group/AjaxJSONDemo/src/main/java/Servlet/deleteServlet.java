package Servlet;

import Service.userService;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
@WebServlet("/delete")
public class deleteServlet extends HttpServlet{
    @Override
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        // 设置响应内容类型
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        String username = request.getParameter("username");
        boolean delete = userService.deleteUser(username);
        HashMap<String, Object> jsonMap = new HashMap<>();
        if (delete) {
            jsonMap.put("code", 200);
            jsonMap.put("msg", "删除成功");
        } else {
            jsonMap.put("code", 400);
            jsonMap.put("msg", "用户不存在, 删除失败");
        }
    }
    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
