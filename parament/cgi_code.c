/**
**name   : cgi_deconde.c
**author : tiger-john
**data   : 2011-05-20
**/

#include "cgi_code.h"


void makespace(char *s)
{
	int i,len;
	len = strlen(s);
	for(i = 0;i < len ;i++){
		
		if('+' == s[i]) 
			s[i] =' ';
	}
}
char *split(char *s,char stop)
{
	char *data;
	char *tmp;
	int i,len,j;
	len = strlen(s);
	tmp = s;
	data = (char *)malloc(sizeof(char)*len+1);
	
	for(i = 0;i < len;i++){
		
		if(stop != s[i]){
		
			data[i] = s[i];
		} else {
			
			i +=1;
			break;
		}
	}
	if(len == i)
		data[i] = '\0';
	else
		data[i-1]='\0';
	for(j = i;j < len;j++)
		s[j-i] = tmp[j];
	s[len-i] = '\0';
	return data;
}

char *convert(char *s)
{
	int i,j,len;
	char *data;
	
	len = strlen(s);
	data = (char *)malloc(sizeof(char)*(len+1));
	j = 0;
	for(i = 0;i < len;i++){
		if(s[i] != '%'){
			data[j] = s[i];
			j++;
		} else {
		
			data[j] = (char)(16*hexa(s[i+1]) + hexa(s[i+2]));
			j++;
			i += 2;
		}
	}
	data[j] = '\0';
	return data;
}
int hexa(char c)
{
	switch(c){
		
		case '0' : return 0;
		case '1' : return 1;
	        case '2' : return 2;
	        case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
	        case '7' : return 7;
	  	case '8' : return 8;
		case '9' : return 9;
	 	case 'a' :
	        case 'A' : return 10;
	        case 'b' :
		case 'B' : return 11;
		case 'c' : 
		case 'C' : return 12;
		case 'd' : 
		case 'D' : return 13;
		case 'e' : 
	        case 'E' : return 14;
		case 'f' :
	        case 'F' : return 15;
	}
	return -1;
}
char *cgi_status(int code)
{
	static const struct {   
		   		  int code;
				  char *msg;

			      } translation[50] = {
							{30, "Sucess"},
							{31, "Open failed!"},
							{32,"Write failed"},
							{33,"Read  failed"},
							{34,"Implement Wrong"},
							{35,"Invailed data"},
							{36,"Value Too Lagage"},
							{37,"No Found Device"},
							{38,"No memory in system"},
							{40,"Init Error"},
							{41,"ajax Error"},
							{42,"TYPE Error"},
							{43,"Parament Error"},
							{51,"NO AJAX File"},
							{52,"NO FILE"},
							{53,"NO Implement"},
							{54,"NO Data"},
							{55,"NO This device"},
							{60,"NO User"},
							{61,"WRONG PASSWORD"},
							};

	   	int i;
		for(i = 0;i<50 ;i++)
			if(translation[i].code==code)
				return translation[i].msg;
		return "unknown error code";
}
