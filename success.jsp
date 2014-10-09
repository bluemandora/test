<%@ page language="java" import="java.util.*" pageEncoding="gbk"%>
<%@ taglib prefix="s" uri="/struts-tags" %> 

<html>

  <body>
  	
    <s:iterator value="#request.ls" var="mylist">
    		<td> <s:property value="#mylist.ISBN"/> </td>
    		<a href="Information.action?id=<s:property value="#mylist.ISBN" />"><s:property value="#mylist.Title"/></a> 
    		<td> <s:property value="#mylist.Author"/> </td>
    		<td> <s:property value="#mylist.Publisher"/> </td>
    		<a href="Delete.action?id=<s:property value="#mylist.ISBN" />">删除</a> <br/>
	</s:iterator>
	<a href="login.jsp">返回搜索页面</a>
  </body>
</html> 
World
