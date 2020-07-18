#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include<fcntl.h>




#define RD_VALUE _IOR('a','b',int32_t*)


int main()
{

int fd;
int buffer;
int select;
int value;
//int h;
int val;
int allign;
val = getpid();
fd=open("/dev/mydevice",O_RDWR);
printf("ADC\n");
printf("*********enter the channel for ADC:");
scanf("%d",&select);
printf("\n");
printf("*****1.right_aligned*****\n");
printf("*****2.left_aligned*****\n");
printf("*********enter the alighnment:");
scanf("%d",&allign);


switch(select)
{

case 1:
printf("channel no 1 is selected");


break;


case 2:
printf("channel no 2 is selected");

break;



case 3:
printf("channel  no 3 is selected");

break;



case 4:
printf("channel no 4 is selected");

break;



case 5:
printf("channel no 5 is selected");

break;




case 6:
printf("channel no 6 is selected");

break;



case 7:
printf("channel no 7 is selected");

break;



case 8:
printf("channel no 8 is selected");

break;

}

printf("\n");
ioctl(fd, RD_VALUE, (int32_t*) &value);
value=value/10;
printf("The ADC output is :%u\n",value);
close(fd);
return 0;

}
		


