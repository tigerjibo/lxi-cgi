#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	char command[30]="MEASUREMENT:TMMED:TYPE";
	const char get_value[]="MEASUREMENT:TMMED:VALUE?";
	int fd;
	int ret;
	char buf[1000];
	fd = open("/dev/usbtmc1",O_RDWR);
	if(fd < 0){
		perror("open usbtmc error");
		exit(1);
	}
	struct usbtmc_attribute attr;
	attr.attribute = USBTMC_ATTRIB_READ_MODE;
	attr.value = USBTMC_ATTRIB_VAL_READ;
	iocal(fd,USBTMC_IOCTL_SET_ATTRIBUTE,&attr);
	printf("begin\n");
	ret = send_command("CRMS");
	if(ret <0 ){
		perror("read usbtmc error");
	}
	ret = read(fd,buf,)

}
