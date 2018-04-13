#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FIFONAME "myFifo"


int main(int argc,char *argv[]){
  char buffer[255];
  char auxiliar[255];

  int server_to_client;
  int client_to_server;

  char * fifo_c_s="./client_to_server";
  char * fifo_s_c="./server_to_client";

  mkfifo(fifo_c_s,0666);
  mkfifo(fifo_s_c,0666);



  printf("antes de abir el archivo en CLIENT\n");
//  int fd = open("./myfifo",O_RDONLY);// O_WRONLY|S_IWRITE       O_RDONLY

  server_to_client = open(fifo_s_c, O_RDONLY);//O_RDONLY S_IWRITE      |O_RDONLY
  client_to_server = open(fifo_c_s, O_WRONLY);

  if(server_to_client<0 || client_to_server<0){
    printf("error en open\n");
  }
  printf("anted dek if del read en client\n");
  if (read(server_to_client, buffer, (sizeof(char)*255)+1) > 0)
        {
            printf("%s \n", buffer);

        }
        printf("tendria que haber leido y escrito\n");
        int c_long = strlen(buffer);
        for (int i=0; i<= c_long; i++){
          auxiliar[i]=  buffer[c_long-i-1];
        }

        printf("antes de ecribir %s\n",auxiliar );
        write(client_to_server,auxiliar,(strlen(auxiliar))+1);
        printf("depues de ecribir en pipe\n" );


        close(client_to_server);
        close(server_to_client);

        return 0;
}
