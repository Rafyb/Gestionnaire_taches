/**
 * @file      commandes_c.c
 * @author    Raphael Bauvin
 * @version   2.3
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */

#include "../logs/printlog_h.h"
#include "commandes_h.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/**
 * Affiche l'aide à l'utilisation du programme
 *
 * @author Raphael Bauvin
 **/
void print_help() {
  printf(
      "Veuillez à ce que la synthaxe "
      "corresponde à : progCommande {options} [nombre repetition] [delai] "
      "[ligne de commande a executer]\n/!\\ Attention le délai et le nombre "
      "de répétition ne peuvent pas être inférieur à 1\nOptions disponibles : "
      "\n "
      "	-l ( ou -L ) pour activer les logs\n"
      "	-h ( ou -H ) pour spécifier que le temps fourni est en heures\n"
      "	-m ( ou -M ) pour spécifier que le temps fourni est en "
      "minutes\n"
      "	-p ( ou -P ) pour spécifier l'emplacement de la commande à éxécuter "
      "avec une syntaxe spécifique\n");
}

/**
 * Execute la ligne de commande
 *
 * @author Raphael Bauvin
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 **/
int exe_cmd(int argc, char **argv) {
  char *arg[10];
  char* ligne;
  for (int i = 0; i < argc; i++) {
    arg[i] = argv[i];
    if (i == argc - 1) {
      arg[i + 1] = NULL;
    }
  }
  if (is_init()) {
    ligne = concatLigne("Execution de la commande : ",argv[0]);
    ecris_log(ligne);
  }
  execvp(argv[0], arg);
  return 1;
}

/**
 * Execute la ligne de commande depuis le chemin spécifié
 *
 * @author Raphael Bauvin
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 * @param path : chemin de la commande à éxécuter
 **/
int exe_cmd_path(int argc, char **argv, char *path) {
  char *arg[10];
  char* ligne;
  for (int i = 0; i < argc; i++) {
    arg[i] = argv[i];
    if (i == argc - 1) {
      arg[i + 1] = NULL;
    }
  }
  if (is_init()) {
    ligne = concatLigne("Execution de la commande : ",path);
    ecris_log(ligne);
  }
  execv(path, arg);
  return 1;
}

int wait_before_next_exec(int timeStart, int timewait) {
  int status;
  int timeToWait;
  char* ligne;
  // on attend la fin de la commande
  wait(&status);
  ecris_log("-- fin du processus");
  int timeStop = (int)time(NULL);
  // On retire le temps d'éxécution au temps à attendre
  timeToWait = timewait - (timeStop - timeStart);
  // Si le temps d'éxécution a duré plus longtemps que le temps d'attentes
  if (timeToWait < 0)
    timeToWait = 0; // on éxécute direct sans attendre
  if (is_init()) {
    char timed[20];
    sprintf(timed, "%d secondes", timeToWait);
    ligne = concatLigne("Temps avant prochaine execution : ",timed);
    ecris_log(ligne);
  }
  // On attend
  sleep(timeToWait);
  return timeToWait;
}

/**
 * Gére la boucle de répétition et du délai d'attente de chaque éxécution
 *
 * @author Raphael Bauvin
 *
 * @param nbr : nombre d'éxécution
 * @param timewait : délai entre chaque éxécution
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 * @param path : chemin de la commande à éxécuter
 **/
int exe_cmd_ntimes(int nbr, int timewait, int argc, char **argv, char *path) {
  pid_t pid_fils;
  // Répétition de la commande
  while (nbr != 0) {
    // Création du processus fils
    pid_fils = fork();
    if (pid_fils == -1) {
      erreur_traitement("Erreur fork");
    }
    // Execution dans le fils
    int timeStart = (int)time(NULL);
    if (pid_fils == 0) {
      // Si il y a un chemin spécifié on execute depuis le chemin spécifié
      if (strlen(path) > 0) {
        if (exe_cmd_path(argc, argv, path) == 1)
          erreur_traitement("Probleme execution commande");

      } else {
        if (exe_cmd(argc, argv) == 1)
          erreur_traitement("Probleme execution commande");
      }
    }
    nbr--;

    // Tant qu'il reste une execution on attends avant la suivante
    if (nbr != 0) {
      wait_before_next_exec(timeStart, timewait);
    }
  }

  // Fin normal du programme
  if (is_init()) {
    wait(NULL);
    ecris_log("-- fin du processus");
    ecris_log_ES(0);
    close_log();
  }
  return 0;
}
