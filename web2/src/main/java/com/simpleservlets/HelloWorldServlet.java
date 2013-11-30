package com.simpleservlets;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloWorldServlet extends HttpServlet {


    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        PrintWriter writer = response.getWriter();
        Process test = Runtime.getRuntime().exec("help");
        BufferedReader reader= new BufferedReader(new InputStreamReader(test.getInputStream()));


        BufferedReader readerBody= new BufferedReader(new InputStreamReader(request.getInputStream()));
        String s;
        while ((s = readerBody.readLine()) != null) {
            System.out.println(s);
            writer.println(s);
        }
        System.out.println(request.toString());
        //writer.println("\ncfhhfghfghfhfghghhhhhhhhhhhhhhhhhh________________\n");
        //writer.println(reader.readLine());
    }


}