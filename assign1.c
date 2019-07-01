#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define DIR_BUF_SIZE 256
bool on_flag=0;
bool log_flag=0;
char *dir = malloc(sizeof(char)*DIR_BUF_SIZE);

int main(int argc,char **argv){
	char *line;
	char **args;
	int status;
	line=sh_read();
	agrs=sh_parse(line);
	status=sh_execute();
}