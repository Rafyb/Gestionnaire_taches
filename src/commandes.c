#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int executerCommande(int argc, char** argv){
    char* arg[10];
    for(int i = 0; i < argc; i++) {
        arg[i] = argv[i];
        if(i == argc-1){
            arg[i+1] = NULL;
        }
    }
    execvp(argv[0],arg);
    return 1;
}

int executerCommandeBoucle(int nbr,int timewait,int argc, char** argv){
    pid_t pid_fils;;
    int status;
    int timeToWait;
    while(nbr != 0){
        timeToWait = timewait;
        pid_fils = fork();
        if(pid_fils == 0){
            srand(time(NULL));
            int timeStart = (int)time(NULL);
            if(executerCommande(argc,argv)==1) {
                perror("Probleme execution commande");
                return 1;
            }
            exit((int)time(NULL) - timeStart);
        }
        //wait(&status);
        timeToWait -= WEXITSTATUS(status);
            printf("temps avant prochaine execution : %d\n", timeToWait);
        sleep(timeToWait);
        nbr--;
    }
    return 0;
}