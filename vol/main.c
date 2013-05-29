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

void cgi_page();
int vol_handle();
nv_set nv[200];

char buffer[40000];
unsigned  char vol_sta[]={
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
			"<head>\r\n"
	//		"<meta http-equiv=\"Content-type\" content=\"text/html\" charset=\"gb2312\">\r\n"
		        "</head>\r\n"
			"<body text=\"black\">\r\n"
			"<form action=\"http://192.168.1.6/cgi-bin/vol.cgi\" method=\"GET\">\r\n"
			"<h1 align=\"center\">获得峰峰值</h1>\r\n"
			"<p align =\"center\"><img src=\"http://192.168.1.6/images/vol.png\">\r\n"
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
	flg =vol_handle();
	msg = cgi_status(flg);
	if(30 ==flg)
	{
		printf("%s",vol_sta);
		printf("<li>峰峰值:%s</li>\r\n",buffer);

	}
	else
	{
		printf("%s",vol_sta);
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

int vol_handle()
{
	int i;
	char set_pk2pktype_buf[]="MEASUrement:IMMed:TYPE PK2PK";
	char get_pk2pkvalue_buf[]="MEASUrement:IMMed:VALue?";
	char get_pk2pkstatus_buf[]="MEASUrement:IMMed:TYPE?";
	char get_allvalue_buf[]="WAVFrm?";
	int fd;
	int ret;
	fd = open("/dev/usbtmc1",O_RDWR);
	if (fd < 0){
		perror("open usbtmc1 fail");
		return  37;
	}
	ret=write(fd,set_pk2pktype_buf,strlen(set_pk2pktype_buf));
	if(ret < 0)
		return 32;
	ret=write(fd,get_pk2pkvalue_buf,strlen(get_pk2pkvalue_buf));
	if(ret < 0)
		return 32;
	ret = read(fd,buffer,4000);
	if(ret ==0)
		return 33;
	buffer[ret] ='\0';
	
	return 30;
}

