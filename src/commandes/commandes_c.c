/**
 * @file      commandes_c.c
 * @author    Raphael Bauvin
 * @version   1.0
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */

#include "../logs/printlog_h.h"
#include "commandes_h.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int exe_cmd(int argc, char **argv) {
  char *arg[10];
  for (int i = 0; i < argc; i++) {
    arg[i] = argv[i];
    if (i == argc - 1) {
      arg[i + 1] = NULL;
    }
  }
  execvp(argv[0], arg);
  return 1;
}

int exe_cmd_ntimes(int nbr, int timewait, int argc, char **argv) {
  pid_t pid_fils;
  int status;
  int timeToWait;

  while (nbr != 0) {
    timeToWait = timewait;
    pid_fils = fork();
    if (pid_fils == -1) {
      perror("Erreur fork\n");
      exit(errno);
    }
    if (pid_fils == 0) {
      int timeStart = (int)time(NULL);
      if (exe_cmd(argc, argv) == 1) {
        perror("Probleme execution commande");
        if (is_init()) {
          ecris_log(1);
          close_log();
        }
        return 1;
      }
      int timeStop = (int)time(NULL);
      exit(timeStop - timeStart);
    }
    nbr--;

    if (nbr != 0) {
      timeToWait -= WEXITSTATUS(status);
      printf("temps avant prochaine execution : %d\n", timeToWait);
      sleep(timeToWait);
    }
  }
  if (is_init()) {
    ecris_log(0);
    close_log();
  }
  return 0;
}
