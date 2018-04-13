#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

	int pid,i,estado;
	char cadena[20] = "/bin/";
 
	pid = fork(); 
	if(pid < 0)
	{
		perror("No se ha podido crear el proceso hijo\n");
		exit(0);
	}
	else if{ // Es el proceso hijo
			
    	strcat(cadena, argv[1]);
   		char *argumentos[20];

    	argumentos[0]= cadena;
    	printf("\nCantidad argc: %i\n",argc);
		for (int i = 1; i < argc; ++i)
		{
			//printf("%s\n",argv[i+1]);
			argumentos[i] = argv[i+1];	
		}
			/*
			argumentos[argc-1]= NULL;
			printf("Ruta: %s\n",cadena);
			printf("Argumentos: \n");
			for (int i = 0; i < argc; ++i)
			{
				printf("%s\n ",argumentos[i]);
				
			}
			*/
		execv(cadena, argumentos);

		return -1;

	}else{
		wait(&estado);
	}
		
	return 0;
}

//int system(const char * string)

   // char *argumentos[] = {"/bin/ls", "-l", NULL}; 

   // execv("/bin/ls", argumentos);