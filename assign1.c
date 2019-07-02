#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


#define DIR_BUF_SIZE 256
#define READ_BUF_SIZE 1024
#define TOKEN_BUF_SIZE 128
#define TOKEN_DELIM "\t\r\n\a"


bool on_flag=0;
bool log_flag=0;
char *dir = malloc(sizeof(char)*DIR_BUF_SIZE);


char *sh_read(){
	int bufsize=READ_BUF_SIZE;//buffer size for reading line
	int position=0;//current position in buffer
	char *buffer=malloc(sizeof(char)*bufsize);//allocating memory to buffer
	char c;//temporary var to hold char while reading
	if(!buffer){	//error handling while allocating memory
		printf("sh_read allocation error\n");
	}
	while(1){//loop that reads line
		c=getchar();

		if(c==EOF||c=='\n'){//checking for end of line
			buffer[position]='\0';
			return buffer;
		}
		else{
			buffer[position]=c;//adding char to line buffer
		}
		position++;
	}
}



char **sh_parse(char *line){


	int bufsize=TOKEN_BUF_SIZE;
	char **token_arr=malloc(bufsize*sizeof(char*));
	char *token;
	int position=0;
	if(token_arr){
		printf("Error allocating token_arr\n");
	}
	token=strtok(line,TOKEN_DELIM);
	while(token!=NULL){
		token_arr[position]=token;
		position++;
		token=strtok(NULL,TOKEN_DELIM);
	}
	token_arr[position]=NULL;
	return token_arr;

}


int main(int argc,char **argv){
	char *line;
	char **args;
	int status;
	line=sh_read();
	args=sh_parse(line);
	status=sh_execute();
}