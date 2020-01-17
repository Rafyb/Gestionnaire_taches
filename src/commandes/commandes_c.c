/**
 * @file      commandes_c.c
 * @author    Raphael Bauvin, Johann De Almeida
 * @version   14012020
 * @date      30 Octobre 2019
 *
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */
#include "../logs/printlog_h.h"
#include "commandes_h.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief La fonction parcourt les arguments et enregistre les options dans
 *la structure fournit en paramètre
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 * @param options : structure contenant les options possibles
 * @return opt : nombre d'options lues
 **/
int gerer_options(int argc, char **argv, T_Options *options) {
  int opt = 0;
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] == '-') {
      int idx = 1;

      while (argv[j][idx] != '\0') {
        // Converion du temps à attendre en heure
        if (argv[j][idx] == 'h' || argv[j][idx] == 'H') {
          if (options->m > 1) {
            erreur_traitement("Le temps ne peut pas être spécifié en minute et "
                              "en heure en même temps\n");
            return -1;
          }
          options->h = 3600;
          opt++;
        }
        // Converion du temps à attendre en minute
        if (argv[j][idx] == 'm' || argv[j][idx] == 'M') {
          if (options->h > 1) {
            erreur_traitement("Le temps ne peut pas être spécifié en minute et "
                              "en heure en même temps\n");
            return -1;
          }
          options->m = 60;
          opt++;
        }
        // Utilisation d'un chemin different pour l'execution du fichier
        if ((argv[j][idx] == 'p' || argv[j][idx] == 'P') &&
            (strlen(options->path) < 1)) {
          options->path = argv[++j];
          opt += 2;
          if (!(strlen(options->path) > 0)) {
            erreur_traitement("Le chemin n'a pas été spécifié\n");
            return -1;
          }
          idx += strlen(options->path) - 2;
        }
        // Utilisation d'un lancement différé
        if ((argv[j][idx] == 'd' || argv[j][idx] == 'D') && !options->d) {
          if (atoi(argv[j + 1]) > 0) {
            options->d = atoi(argv[++j]);
            opt += 2;
          } else {
            erreur_traitement("Le temps différé n'est pas spécifié\n");
            return -1;
          }
          idx += strlen(argv[j]) - 2;
        }
        // Utilisation des logs
        if ((argv[j][idx] == 'l' || argv[j][idx] == 'L') && !options->l) {
          options->l = 0;
          opt++;
          init_log(argv[0]);
        }
        idx++;
      }
    }
  }
  return opt;
}

/**
 * @brief Affiche l'aide à l'utilisation du programme
 *
 **/
void print_help() {
  printf(
      "Veuillez à ce que la synthaxe "
      "corresponde à : progCommande {options} [nombre repetition] [delai] "
      "[ligne de commande a executer]\n"
      "/!\\ Attention le délai et le nombre de répétition ne peuvent pas être "
      "inférieur à 1\nOptions disponibles :\n"
      "	-l ( ou -L ) pour activer les logs\n"
      "	-h ( ou -H ) pour spécifier que le temps fourni est en heures\n"
      "	-m ( ou -M ) pour spécifier que le temps fourni est en minutes\n"
      "	-p ( ou -P ) pour spécifier l'emplacement de la commande à éxécuter "
      "avec une syntaxe spécifique\n"
      "	-d ( ou -D ) pour que la première execution se fasse en différé\n");
}

/**
 * @brief Execute la ligne de commande à l'aide de "execv" ou "execvp" en
 *fonction de si le chemin est spécifié ou non
 *
 * @param argc : nombre d'arguments de la ligne de commande
 * @param argv : les arguments de la ligne de commande
 **/
int exe_cmd(int argc, char **argv, char *path) {
  char *arg[10];
  // Recupération de la ligne de commande exacte
  for (int i = 0; i < argc; i++) {
    arg[i] = argv[i];
    if (i == argc - 1) {
      arg[i + 1] = NULL;
    }
  }
  // Si il y a un chemin spécifié on execute depuis le chemin spécifié
  if (strlen(path) > 0) {
    if (is_init())
      ecris_log(concatLigne("Execution de la commande : ", path));
    // Execution via chemin spécifié
    execv(path, arg);
  } else {
    if (is_init())
      ecris_log(concatLigne("Execution de la commande : ", argv[0]));
    // Execution via les chemins spécifiés dans la variable d'environnement PATH
    // de l'utilisateur
    execvp(argv[0], arg);
  }
  return 1;
}

/**
 * @brief Gére la boucle de répétition et le délai d'attente entre chaque
 * éxécution
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
    if (pid_fils == 0) {
      if (exe_cmd(argc, argv, path) == 1)
        erreur_traitement("Probleme execution commande");
    }
    nbr--;
    // Tant qu'il reste une execution on attends avant la suivante
    if (nbr != 0) {
      ecris_temps(timewait);
      sleep(timewait);
    }
  }

  // Fin normal du preocessus
  if (is_init()) {
    waitpid(pid_fils, NULL, 0); // Attends la fin du dernier processus lancé
    ecris_log_ES(0);
    close_log();
  }
  return 0;
}
