#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
 int res;
 res=open("fifo1",O_RDONLY);
 char buf[100];
 int n=read(res,buf,100);
 printf("Message receibved: \t%s",buf);
 
 int i,characters=0,words=0,lines=0;
 
 for(i=0;buf[i]!='\0';i++)
	{
		if(buf[i]==' ' || buf[i]=='\n' || buf[i]=='#')
			words++;
		if(buf[i]=='\n' || buf[i]=='#')
			lines++;
		if(buf[i]!=' ' && buf[i]!='\n' && buf[i]!='#')
			characters++;
	}
	
 printf("\nCounts are :\nCharacters: %d \nWords: %d \nLines: %d\n",characters,words,lines);
 return 0;
}
