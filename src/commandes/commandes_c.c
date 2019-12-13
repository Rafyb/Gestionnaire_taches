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

void print_help() {
  printf("Veuillez à ce que la synthaxe "
         "corresponde à : progCommande {options} [nombre repetition] [delai] "
         "[ligne de commande a executer] \nOptions disponibles : \n "
         "	-l ( ou -L ) pour activer les logs\n"
         "	-h ( ou -H ) pour spécifier que le temps fournis est en heure\n"
         "	-m ( ou -M ) pour spécifier que le temps fournis est en "
         "minute\n"
         "	-r ( ou -R ) si les commandes sont spécifiés dans un fichier "
         "avec une synthaxe spécifique\n");
}

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
