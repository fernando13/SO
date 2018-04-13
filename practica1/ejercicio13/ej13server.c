#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>




int main(int argc,char *argv[]){
  char buffer[255];
  printf("SERVER\n");
  int server_to_client;
  int client_to_server;

  char * fifo_c_s="./client_to_server";
  char * fifo_s_c="./server_to_client";

  mkfifo(fifo_c_s,0666);
  mkfifo(fifo_s_c,0666);

/*
  int fd;
  printf("crea el fifo\n");


  //S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
  if(mkfifo("./myfifo",0666)){//man 3 ------------------------------mkfifo               S_IRUSR | S_IWUSR
    printf("ERROR en creacion fifo\n");
  }
//0666 permisos en octal
*/
  printf("cre{o} el fifo y return:\n");

  server_to_client = open(fifo_s_c, O_WRONLY);//O_RDONLY S_IWRITE      |O_RDONLY
  client_to_server = open(fifo_c_s, O_RDONLY);

  char msj[]="amazona te estoy tragando";

  write(server_to_client, msj, sizeof(msj)+1);
  //close(fd);

  printf("volio de clientes y esta en serve por leer la respuesta\n" );
  int eread=read(client_to_server, buffer, (sizeof(char)*255)+1);//read(fd, buffer, (sizeof(char)*255)+1)
  if ( eread > 0)
        {
            printf("%s \n", buffer);

        }
        printf("paso el if read de leer en server conm eread %i\n",eread);
    /* remove the FIFO */
    //unlink(myfifo);

    close(client_to_server);
    close(server_to_client);

    unlink(fifo_c_s);
    unlink(fifo_s_c);


    return 0;
}
