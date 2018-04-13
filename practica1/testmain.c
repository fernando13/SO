#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i =1;
	printf("Cantidad argc: %i\n",argc);
	printf("%s\n","Argumentos: ");
	for (int i = 0; i < argc; ++i)
	{
		printf("%s\n",argv[i]);
	}
	printf("%s\n",argv[argc-1]);
/*
	i=0;
	printf("%sAmbiente: \n");
	while(envp[i])
	{
		printf("%s\n",envp[i++] );
	}	
*/
	return 0;
}

