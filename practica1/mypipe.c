#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char const *op = argv[2];
	char const *cmd1 = argv[1];
	char const *cmd2 = argv[3];
	//char *argumentos[3];// {path,cmd,NULL};
	int pid,status; 
	char path[20] = "/bin/";

	printf("\n");

	//*****************************************************************
	if(strcmp(op,"|")==0){ 
		int p[2];
		pipe(p);
		if(fork()==0){
			close(0);
			dup(p[0]);
			close(p[1]);
			execlp(cmd1,cmd1,NULL);
		}else{		
			if(fork()==0){
				close(1);
				dup(p[1]);
				close(p[0]);
				execlp(cmd2,cmd2,NULL);
			}
			wait(0);
			wait(0);
		}
	}	


	//*****************************************************************
	if(strcmp(op,">")==0){ //cmd > output_file
		pid = fork(); 
		if(pid == 0){// Es el proceso hijo
			close(1); // cierro la salida estandar		
			int fd = open(cmd2, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWRITE); //S_IRUSR|S_WUSR
			dup(fd);
			execlp(cmd1,cmd1,NULL);
		}else{
			wait(0);
		}	
	}	


	//*****************************************************************
	if(strcmp(op,"<")==0){
    	printf("entro al <, con cmd1 %s y cmd2 %s\n",cmd1,cmd2 );
    	int fd;
    	if(fork()==0){
    		close(0);
    		fd=open(cmd2,O_RDONLY); //man 2 open       SINO EN VEZ DE S_IWRITE PONER S_IWVSR
     		dup(fd);
     		execlp(cmd1,cmd1,NULL);
   		}else{
   	    int w;
   	    wait(&w);
   	}
  }


	//*****************************************************************
	if(strcmp(op,">>")==0){ //cmd >> output_file
		pid = fork(); 
		if(pid == 0){// Es el proceso hijo
			close(1); // cierro la salida estandar		
			int fd = open(cmd2, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWRITE); //S_IRUSR|S_WUSR
			dup(fd);
			execlp(cmd1,cmd1,NULL);
		}else{
			wait(0);
		}
	}	


	//*****************************************************************
	if(strcmp(op,";")==0){

		pid = fork(); 
		if(pid == 0){// Es el proceso hijo1
						
			execlp(cmd1,cmd1,NULL);

		}else{ // Proceso padre

			wait(0);
			printf("\n");

			pid = fork(); 
			if(pid == 0){// Es el proceso hijo2
						
				execlp(cmd2,cmd2,NULL);

			}else{
				wait(0);
			}	
		}
	}


	//*****************************************************************
	if(strcmp(op,"||")==0){

		pid = fork(); 
		if(pid == 0){// Es el proceso hijo1

			/*			
			strcat(path, cmd1);
			argumentos[0] == path;
			argumentos[2] == cmd1;
			argumentos[3] == NULL;
			execv(path, argumentos);
			*/
			execlp(cmd1,cmd1,NULL);
			exit(3);

		}else{ // Proceso padre

			wait(&status);

			if(WIFEXITED(status) && WEXITSTATUS(status)==3){ // Hijo1 termino incorrectamente
				pid = fork(); 
				if(pid == 0){// Es el proceso hijo2
					/*
					strcat(path, cmd2);
					argumentos[0] == path;
					argumentos[2] == cmd2;
					argumentos[3] == NULL;
					execv(path, argumentos);
					*/
					execlp(cmd2,cmd2,NULL);

				}else{
					wait(0);
				}
			}	
		}
	}


	//*****************************************************************
	if(strcmp(op,"&&")==0){

		pid = fork(); 
		if(pid == 0){// Es el proceso hijo1
						
			execlp(cmd1,cmd1,NULL);
			exit(3);

		}else{ // Proceso padre

			wait(&status);

			if(WIFEXITED(status) && WEXITSTATUS(status)!=3){

				pid = fork(); 
				if(pid == 0){// Es el proceso hijo2

					execlp(cmd2,cmd2,NULL);

				}else{
					wait(0);
				}
			}	
		}
	}	
	printf("\n");
}
             