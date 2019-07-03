#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define DIR_BUF_SIZE 256
#define READ_BUF_SIZE 1024
#define TOKEN_BUF_SIZE 20
#define TOKEN_DELIM " \t\r\n\a"


int on_flag=0;
int log_flag=0;
//char *dir = malloc(sizeof(char)*DIR_BUF_SIZE);


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
	char **token_arr = malloc(bufsize * sizeof(char*));
	char *token;
	int position=0;
	token=strtok(line,TOKEN_DELIM);
	while(token != NULL){
		token_arr[position]=token;
		position++;
		
		token = strtok(NULL,TOKEN_DELIM);
	}
	token_arr[position]=NULL;
	return token_arr;


}
int sh_execute(char **args){
	pid_t pid,wpid;
	int status;
	
	
	pid=fork();
	if(pid==0){
		
		if(execvp(args[0], args) == -1){
			
			perror("lsh");
		}

	}
	else if(pid<0){
		printf("error while forking\n");
	}
	else{
		do{
			wpid=waitpid(pid,&status,WUNTRACED);

		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return status;
}

int sh_start_output_log(FILE *output_log){
	char buffer[1024];
	int nbytes;

	int out_pipe[2];
	pipe(out_pipe);

	int backup=dup(fileno(stdout));

	
	

	dup2(fileno(output_log),fileno(stdout));
	return backup;
}


int main(int argc,char **argv){
	char *line;
	char **args;
	int status;
	FILE *output_log;
	output_log=fopen("output.log","a+");

	int backup;
	while(1){//main loop

		if(on_flag==0){//check for entry
			line=sh_read();
			if(strcmp(line,"entry")==0){
				on_flag=1;
			}
			else{
				printf("Command line intepretor not started\n");
			}
			free(line);
		}
		
		if(on_flag==1){//entry command triggered

			do{
			line=sh_read();
			if(strcmp(line,"exit")==0){
				on_flag=0;//exit command entered
				printf("Command line exited\n");
				break;
			}
			if(strcmp(line,"log")==0 && log_flag==0){
				log_flag=1;
				 backup=sh_start_output_log(output_log);
				continue;
			}

			if(strcmp(line,"unlog")==0 && log_flag ==1){
				log_flag=0;
				dup2(backup,fileno(stdout));
				continue;
			}
			args=sh_parse(line);
			status=sh_execute(args);

			free(line);
			free(args);
			}while(on_flag==1);

		}

	}
}