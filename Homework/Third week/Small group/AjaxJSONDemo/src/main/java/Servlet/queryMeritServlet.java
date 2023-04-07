package Servlet;

import DAO.userDAO;
import Service.userService;
import Utils.mapper;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.HashMap;
@WebServlet("/queryMerit")
public class queryMeritServlet extends HttpServlet {
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
        i = userService.query(username).getMerit();
        jsonMap.put("code", 200);
        jsonMap.put("msg", "功德查询成功");
        jsonMap.put("data", i);
        mapper.writeValue(response.getWriter(), jsonMap);
    }


    @Override
    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws IOException {
        doGet(request, response);
    }
}

