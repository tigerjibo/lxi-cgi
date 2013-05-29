/**
**name	:cgi_decode.h
**author:tiger-john
**date  :2010-05-20
**
**/
#ifndef CGI_DECODE_H
#define CGI_DECHODE_H

#include<stdio.h>
#include<stdlib.h>//calloc malloc free realloc
#include<string.h>
#include<ctype.h>//isprint isupper isspace

typedef struct 
{
	char name[250];
	char value[250];
}nv_set;

typedef struct 
{
	char *name;
	char *password;
}User_Info;
/*
User_Info DATA[5]={
			{"tiger","123456"},{"admin","admin"}
		    };
*/		    
void makespace(char *s);
char *split(char *s,char stop);
char *convert(char *s);
int hexa(char c);
char *cgi_status(int flg);

#endif
