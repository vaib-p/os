#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
 int res,file;
 res=mkfifo("fifo1",0777);
 printf("named pipe is created!!!");
 file=open("fifo1",O_WRONLY);
 write(file,"vaibhav ",8);
 printf("Message has sent!");
 return 0;
}
