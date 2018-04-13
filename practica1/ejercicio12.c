#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void controlador (int a){
  printf("Quieres terminar el proceso? %d\n", a);
  exit(-1);
}


void main(int argc, char const *argv[])
{
  while(1) {
     signal(SIGINT, controlador); 
  }
}
// Usar CTRL-C