#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int executerCommande(int argc, char** argv){
    char* arg[20];
    for(int i = 0; i < argc; i++) {
        if(i > 0) { 
            arg[i-1] = argv[i];
        }
        if(i == argc-1){
            arg[i] = NULL;
        }
    }
    execvp(argv[1],arg);
    return 1;
}

int main(int argc, char** argv)
{
  if(argc<1) {
    perror("Nombre d'argument invalide");
    return 1;
  }

  pid_t pid_fils = fork();

  if(pid_fils == 0){
    if(executerCommande(argc,argv)==1) perror("Probleme execution commande");
  }

  return 0;
}
