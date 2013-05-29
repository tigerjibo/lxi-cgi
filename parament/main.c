/**
**name 	  :main.c
**author  :tiger-john
**data    :2011-05-20
**/
#include "cgi_code.h"
#include "usbtmc.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

void cgi_page(int flg,int num);
int para_handle(int value_count);
int para(int para_num);
int send_command(char *type);
nv_set nv[200];

#define LENGTH 300
#define RMS 1
#define DEL 2
#define FAL 3
#define FRQ 4
#define MAX 5
#define MIN 6
#define MEA 7
#define NWI 8
#define PDU 9
#define PER 10
#define PK2 11
#define PWI 12
#define RIS 13
#define ALL 14
/*
struct {

	char command[500];
	int  flg;
}COMMAND_TABLE;
*/
int fd;
char *command[13];
		char rms[LENGTH];
		char del[LENGTH];
		char fal[LENGTH];
		char frq[LENGTH];
		char max[LENGTH];
		char min[LENGTH];
		char mea[LENGTH];
		char nwi[LENGTH];
		char pdu[LENGTH];
		char per[LENGTH];
		char pk2[LENGTH];
		char pwi[LENGTH];
		char ris[LENGTH];
															

unsigned  char para_sta[]={
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n"
			"<head>\r\n"
	//		"<meta http-equiv=\"Content-type\" content=\"text/html\" charset=\"gb2312\">\r\n"
		        "</head>\r\n"
			"<body text=\"black\">\r\n"
			"<h1 align=\"center\">获取设备数据</h1>\r\n"
			"<p align =\"center\"><img src=\"http://192.168.1.6/images/vol.png\">\r\n"
			"<form action=\"http://192.168.1.6/cgi-bin/parament.cgi\" method=\"GET\">\r\n"
			"<h3 align=\"left\">选择参数</h3>\r\n"
			"<p align=\"left\">\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"1\" chrcked>\r\n"
			"均方根\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"2\" chrcked>\r\n"
			"上升延迟\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"3\" chrcked>\r\n"
			"下降时间\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"4\" chrcked>\r\n"
			"频率\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"5\" chrcked>\r\n"
			"最高值\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"6\" chrcked>\r\n"
			"最低值\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"7\" chrcked>\r\n"
			"平均值\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"8\" chrcked>\r\n"
			"负脉宽\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"9\" chrcked>\r\n"
			"占空比\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"10\" chrcked>\r\n"
			"周期\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"11\" chrcked>\r\n"
			"峰峰值\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"12\" chrcked>\r\n"
			"正脉宽\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"13\" chrcked>\r\n"
			"上升时间\r\n"
			"<input type=\"checkbox\" name=\"parament\" value=\"14\" chrcked>\r\n"
			"全部参数\r\n"
			"</p>\r\n"
			"<p align=\"center\">\r\n"
			"<input type=\"submit\" name=\"Submit\" value=\"提交\">\r\n"
			"<input name=\"Reset\" type=\"reset\" value=\"取消\">\r\n"
			"</p>\r\n"
			"</form>\r\n"
			
};
int main()
{
	int i,count;
	int flg = -1;
        /*count 为窗体译码后实际的字段数*/
	count = get_input();

	/*输出HTTP报头*/
	printf("Content-type: text/html\r\n");
	printf("\r\n");
	flg = para_handle(count);
	
	return 0;
}

void cgi_page(int flg,int num)
{
   	
	char *msg=NULL;
	msg = cgi_status(flg);
	switch(num){
			case RMS:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>RMS : %s</li>\r\n",rms);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">RMS :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case DEL:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>DLE : %s</li>\r\n",del);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">DEL :  %s 请重新操做</font></p>\r\n",msg);
				}
 				break;
			case FAL:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>FAL : %s</li>\r\n",fal);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">FAL :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case FRQ:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>FRQ : %s</li>\r\n",frq);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">FRQ :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case MAX:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>MAX : %s</li>\r\n",max);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">MAX :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case MIN:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>MIN : %s</li>\r\n",min);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">MIN :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case MEA:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>MEA : %s</li>\r\n",mea);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">MEA :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case NWI:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>NWI : %s</li>\r\n",nwi);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">nwi :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case PDU:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>PDU : %s</li>\r\n",pdu);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">PDU :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case PER:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>PER : %s</li>\r\n",per);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">PER :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case PK2:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>PK2 : %s</li>\r\n",pk2);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">PK2 :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case PWI:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>pwi : %s</li>\r\n",pwi);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">PWI :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			case RIS:	
				if(30 ==flg){
				printf("%s",para_sta);
				printf("<li>RIS : %s</li>\r\n",ris);
				} else {
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\">RIS :  %s 请重新操做</font></p>\r\n",msg);
				}
				break;
			
			default :
				printf("%s",para_sta);
				printf("<p align=center><font size=\"+2\"color=\"red\"> %s 请重新操做</font></p>\r\n",msg);
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
int para_handle(int value_count)
{
	int i;
	int para_num;
	int flg;
	if(value_count -1 !=1)
		return 35;
	if(strcmp(nv[0].name,"parament") != 0)
		return 43;
	para_num = atoi(nv[0].value);
	flg = para(para_num);
	cgi_page(flg,para_num);
	return flg;
}

int send_command(char *type)
{
	int ret;
	char command[30]="MEASUREMENT:IMMED:TYPE ";
	const char get_value[]="MEASUREMENT:IMMED:VALUE?";
	
	strcat(command,type);

	ret=write(fd,command,strlen(command));
	if(ret<0){
		return 32;
	}
	ret=write(fd,get_value,strlen(get_value));
	if(ret<0){
		return 32;
	}
	return 30;
}
int para(int para_num)
{
	
	char command[30]="MEASUREMENT:IMMED:TYPE ";
	const char get_value[] ="MEKSUREMENT:IMMED:VALUE?";
	int ret;
	int cmd;

	fd = open("/dev/usbtmc1",O_RDWR);
	if (fd < 0){
		return 37;
	}
	struct usbtmc_attribute attr;
	attr.attribute = USBTMC_ATTRIB_READ_MODE;
	attr.value=USBTMC_ATTRIB_VAL_READ;
	ioctl(fd,USBTMC_IOCTL_SET_ATTRIBUTE,&attr);
	switch(para_num){
		case RMS:
				ret = send_command("CRMS");
				if(ret != 30){
					return ret;	
				}
				ret=read(fd,rms,LENGTH);
				if(ret<0){
                                      return 33;
                                }
				
			
				break;
		case DEL:	
				ret = send_command("DELAY");
                     		if(ret != 30){
					return ret;	
                     		}
                     		ret=read(fd,del,LENGTH);
                     		if(ret<0){
                                	return 33;
                     		}
				break;
		case FAL:
				ret = send_command("FALL");
                     		if(ret != 30){
					return ret;
                     		}
                     		ret=read(fd,fal,LENGTH);
                     		if(ret<0){
                                	return 33;
                     		}
				break;
		case FRQ:
		   		ret = send_command("FREQ");
                     		if(ret != 30){
					  return ret;
                    		 }	
                     		ret=read(fd,frq,LENGTH);
                     		if(ret<0){
					return 33;
                     		}
				break;
		case MAX:
		   		ret = send_command("MAXIMUM");
                     		if(ret != 30){
					return ret;   
                     		}
                     		ret=read(fd,max,LENGTH);
                     		if(ret<0){
                                	return 33;
                     		}
				break;
 		case MIN:
		   		ret = send_command("MINIMUM");
                     		if(ret != 30){
					return ret; 
                     		}
                     		ret = read(fd,min,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		}
				break;
		case MEA:
		   		ret = send_command("MEAN");
                     		if(ret != 30){
					return ret; 
                     		}
                     		ret = read(fd,mea,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		} 
				break;
		case NWI:
		   		ret = send_command("NWIDTH");
                     		if(ret != 30){
					return ret;
                     		}
                     		ret = read(fd,nwi,LENGTH);
                     		if(ret<0){
                                	return 33;
                    		}
				break;
		case PDU:
		   		ret = send_command("PDUTY");
                     		if(ret != 30){
					return ret;   
                     		}
                     		ret = read(fd,pdu,LENGTH);
                    		if(ret<0){
                                	return 33;
                     		}
				break;
		case PER:
		   		ret = send_command("PERIOD");
                     		if(ret != 30){
					return ret;  
                     		}
                     		ret = read(fd,per,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		}
				break;
		case PK2:
		   		ret = send_command("PK2PK");
                     		if(ret != 30){
					return ret; 
                     		}
                     		ret = read(fd,pk2,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		}
				break;
		case PWI:
		   		ret = send_command("PWIDTH");
                     		if(ret != 30){
					return ret;   
                     		}
                     		ret = read(fd,pwi,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		}
				break;
		case RIS:
		   		ret = send_command("RISE");
                     		if(ret !=30){
					return ret;   
                     		}
                     		ret = read(fd,ris,LENGTH);
                     		if(ret < 0){
                                	return 33;
                     		}
				break;

		default : 
				return 53;
	
	}
	return 30;
}


