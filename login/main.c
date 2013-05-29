/**
**name 	  :main.c
**author  :tiger-john
**data    :2011-05-20
**/
#include "cgi_code.h"

User_Info DATA[5]={
		    {"tiger","123456"},
		    {"admin","admin"}
		 };

unsigned char log_sta1[]={
	        "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
		"<head>\r\n"
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n"
		"<script language=\"text/javascript\" type=\"text/javascript\">\r\n"
		"function ready(){\r\n"
		"if(document.form1.username.value.length==0){\r\n"
			"alert(\"用户名不能为空！\");\r\n"
			"return false;\r\n"
		 "}\r\n"
		 "if(document.form1.password.value.length==0){\r\n"
		 	"alert(\"密码不能为空！\");\r\n"
			"return false;\r\n"
		 "}\r\n"
		 "return true;\r\n"
		 "}\r\n"
		 "</script>\r\n"
		"<title>XMS实验室</title>\r\n"
		"<link rel=\"stylesheet\" type=\"text/css\" href=\"http://192.168.1.6/css/back_login.css\">\r\n"
		"<link rel=\"stylesheet\" type=\"text/css\" href=\"http://192.168.1.6/css/back_common.css\">\r\n"
		"</head>\r\n"
		"<body id=\"main\">\r\n"
		"<center>\r\n"
		"<div id=\"center\">\r\n"
		"<div style=\"height: 28px; text-align: center; width: 100%\">\r\n"
		"</div>\r\n"	
		"<div id=\"thestyle\">\r\n"	
		"<form name=\"form1\" action=\"http://192.168.1.6/cgi-bin/login.cgi\" method=\"post\" onSubmit=\"return ready();\">\r\n"	
		"<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\">\r\n"	
		"<tr>\r\n"	
		"<td>\r\n"	
		"用户名\r\n"	
		"</td>\r\n"	
		"<td>\r\n"	
		"<input class=\"inputFrameStyle\" type=\"text\" id=\"admin.username\" name=\"username\">\r\n"	
		"</td>\r\n"	
		"<td>\r\n"	
		"</td>\r\n"	
		"</tr>\r\n"	
		"<tr>\r\n"	
		"<td>\r\n"	
		"密码\r\n"	
		"</td>\r\n"	
		"<td>\r\n"	
		"<input style=\"width: 12em\" type=\"password\" id=\"admin.password\" name=\"password\"/>\r\n"	
		"</td>\r\n"							
		"</tr>\r\n"	
		"<tr>\r\n"	
		"<td></td>\r\n"	
		"<td>\r\n"	
		"<input type=\"submit\" name=\"login\" value=\"登录\"\r\n"	
		"style=\"cursor: pointer\">\r\n"	
		"<input type=\"checkbox\" style=\"\" />\r\n"	
		"记住密码\r\n"	
		"</td>\r\n"	
		"<td>\r\n"	
		"</td>\r\n"	
		"</tr>\r\n"	
		"</table>\r\n"	
		"</form>\r\n"	
		"</div>\r\n"	
		"</div>\r\n"	
		"</center>\r\n"	  
			
};
unsigned char home[]={
		"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
		"<head>\r\n"
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n"
		"<title>XNMS-实验室</title>\r\n"
		"</head>\r\n"
		"<frameset rows=\"100,*\" cols=\"*\" frameborder=\"no\" border=\"0\" framespacing=\"0\" >\r\n"
		"<frame src=\"http://192.168.1.6/top.html\"  name=\"topFrame\" scrolling=\"No\" noresize=\"noresize\"/>\r\n"
		"<frameset cols=\"377,*\" rameborder=\"no\" border=\"0\" framespacing=\"0\">\r\n"
		"<frame src=\"http://192.168.1.6/menu.html\" name=\"MenuFrame\" scrolling=\"No\" noresize=\"noresize\"/>\r\n"
		"<frame src=\"http://192.168.1.6/scope.html\" name=\"conFrame\" scrolling=\"yes\" noresize=\"noresize\">\r\n"
		"</frameset>\r\n"
		"<body>	\r\n"
		"</body>\r\n"
		"</html>\r\n"
		"</body>\r\n"
		"</html>\r\n"

};


int get_input();
int is_login(int count);
void cgi_page(int flg);

nv_set nv[200];

int main()
{
	int i,count;
	int flg = -1;
        /*count 为窗体译码后实际的字段数*/
	count = get_input();

	/*输出HTTP报头*/
	printf("Content-type: text/html\r\n");
	printf("\r\n");
	flg = is_login(count);
	cgi_page(flg);
	return 0;
}

void cgi_page(int flg)
{
     char *msg=NULL;
     msg = cgi_status(flg);
     if(flg !=30){
     	printf("%s",log_sta1);
	printf("<p align=center><font size=\"+2\"color=\"red\">%s,请重新登录</font></p>\r\n",msg); 
	printf("</body>\r\n</html>");
     }	else {
     	printf("%s",home);
     }
}
int get_input()
{
	char *method;
	char *my_data = 0;
	char *tmp_ptr,*tmp;
	int data_len;
	int i;
	method = getenv("REQUEST_METHOD");
	if(0 == strcmp(method,"GET")){
		tmp_ptr = getenv("QUERY_STRING");
		data_len = strlen(tmp_ptr);
		my_data = (char *)malloc(sizeof(char)*(data_len+1));
		/*数据存放在my_data中*/
		strcpy(my_data,getenv("QUERY_STRING"));
		my_data[data_len] = '\0';
	}
	if(0 == strcmp(method,"POST")){
		data_len =atoi(getenv("CONTENT_LENGTH"));
		my_data = (char *)malloc(sizeof(char)*(data_len+1));
		fread(my_data,1,data_len,stdin);
	}

	i = 0;
	while(my_data[0]!='\0'){
	
		tmp = split(my_data,'=');//分离数据对
		makespace(tmp);
		tmp = convert(tmp);
		strcpy(nv[i].name,tmp);
		tmp = split(my_data,'&');
		makespace(tmp);
		tmp = convert(tmp);
		strcpy(nv[i].value,tmp);
		i++;
	}
	return i--;
}
int is_login(int count)
{
	int i;
	int flg = -1;
	if(count-1 != 2)
		return 35;
	for(i = 0;i < 2;i++){
		if(0 == strcmp(nv[0].value,DATA[i].name)){
			if(0 == strcmp(nv[1].value,DATA[i].password)){
				flg = 30;
				break;
			} else {
				flg = 61;
				break;			
			}	
		}
	}

	if (2 == i)
		flg = 60;
	if (-1 == flg)
		flg = 61;
	
	return flg;
}
