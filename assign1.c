#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define DIR_BUF_SIZE 256
#define READ_BUF_SIZE 1024
bool on_flag=0;
bool log_flag=0;
char *dir = malloc(sizeof(char)*DIR_BUF_SIZE);

char *sh_read(){
	int bufsize=READ_BUF_SIZE;
	int position=0;
	char *buffer=malloc(sizeof(char)*bufsize);
	char c;
	if(!buffer){
		printf("sh_read allocation error\n");
	}
	while(1){
		c=getchar();

		if(c==EOF||c=='\n'){
			buffer[position]='\0';
			return buffer;
		}
		else{
			buffer[position]=c;
		}
		position++;
	}
}

int main(int argc,char **argv){
	char *line;
	char **args;
	int status;
	line=sh_read();
	agrs=sh_parse(line);
	status=sh_execute();
}