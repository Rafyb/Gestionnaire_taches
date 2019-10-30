#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  if(argc<1) {
    perror("Nombre d'argument invalide");
    return 1;
  }

  executerCommandeBoucle(3,10,argc,argv);  

  return 0;
}
