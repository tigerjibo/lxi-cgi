/**
**name 	  :main.c
**author  :tiger-john
**data    :2011-05-20
**/
#include "cgi_code.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
/*
typedef struct {
	char value[400];
}tk;
*/
void cgi_page();
int info_handle();
nv_set nv[200];

char name[50];
char type[50];
char serial[50];
char buffer[40000];
unsigned  char info_sta[]={
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
			"<head>\r\n"
	//		"<meta http-equiv=\"Content-type\" content=\"text/html\" charset=\"gb2312\">\r\n"
		        "</head>\r\n"
			"<body text=\"black\">\r\n"
			"<form action=\"http://192.168.1.6/cgi-bin/info.cgi\" method=\"GET\">\r\n"
			"<h1 align=\"center\"> 设备信息</h1>\r\n"
			"<p align =\"center\"><img src=\"http://192.168.1.6/images/2014b1.jpg\">\r\n"
			"<p align=\"center\">\r\n"
			"<input type=\"submit\" name=\"Submit\" value=\"提交\">\r\n"
			"</p>\r\n"
			"</form>\r\n"
			
};
int main()
{
	int i,count;
	int flg = -1;

//	tk value [3];
        /*count 为窗体译码后实际的字段数*/
	count = get_input();

	/*输出HTTP报头*/
	printf("Content-type: text/html\r\n");
	printf("\r\n");
	cgi_page();
	return 0;
}

void cgi_page()
{
   	int flg=0;
	char *msg=NULL;
	flg =info_handle();
	msg = cgi_status(flg);
	if(30 ==flg)
	{
		printf("%s",info_sta);
		printf("<li>Manutacturer:%s</li>\r\n",name);
		printf("<li>Instrument Type:%s</li>\r\n",type);
		printf("<li>Serial Number:%s</li>\r\n",serial);
		printf("<li>IP Address:%s</li>\r\n",getenv("REMODE_NAME"));
		printf("<li>Sever Name:%s</li>\r\n",getenv("SERVER_NAME"));
		printf("<li>LXI Class :C</li>\r\n");
		printf("<li>LXI Version 1.3</li>\r\n");
	
	}
	else
	{
		printf("%s",info_sta);
		printf("<p align=center><font size=\"+2\"color=\"red\">%s,请重新操做</font></p>\r\n",msg);
	}
	printf("</body>\r\n</html>");
    
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

int info_handle()
{
	int i;

	int fd;
	int ret;
//	char buffer[4000];
	char *tmp;
	fd = open("/dev/usbtmc1",O_RDWR);
	if (fd < 0){
		return  37;
	}
	ret = write(fd,"*IDN?\n",6);
	if(0==ret)
		return 32;
	//sleep(1);
	ret = read(fd,buffer,4000);
	if(ret ==0)
		return 33;
	buffer[ret] ='\0';
	tmp = split(buffer,',');
	strcpy(name,tmp);
	tmp = split(buffer,',');
	strcpy(type,tmp);
	tmp = split(buffer,',');
	strcpy(serial,tmp);
	
	return 30;
}

