/**
 * @file      main.c
 * @author    Raphael Bauvin
 * @version   2.3
 * @date      30 Octobre 2019
 * @brief     Contient le main principale du programme ainsi que la gestion des
 * options
 *
 */

#include "../logs/printlog_h.h"
#include "commandes_h.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * La commande doit respecter le format suivant :
 *./progCommande [options] {nombre repetition} {delai} {ligne de commande a
 *executer}
 *
 * Les options suivantes sont disponibles :
 *    -l ( ou -L ) pour activer les logs
 * @todo :
 *    -h ( ou -H ) pour spécifier que le temps fournis est en heure
 *    -m ( ou -M ) pour spécifier que le temps fournis est en minute
 *    -r ( ou -R ) si les commandes sont spécifiés dans un fichier avec une
 *synthaxe spécifique
 *
 * @author Raphael Bauvin / Johann
 * @param argc nombre d'argument
 * @param argv liste des arguments
 */
int main(int argc, char **argv) {

  // ------ Test du nombre d'argument
  if (argc < 4) {
    perror("Nombre d'argument invalide");
    print_help();
    return 3;
  }

  // ------ Gerer les options
  // nombre d'argument pris par les options
  int opt = 0;

  // liste des differentes options possible
  int l = 0; // - log
  int p = 0; // - path

  for (int j = 1; j < argc; j++) {
    if (argv[j][0] == '-') {
      int idx = 1;
      while (argv[j][idx] != '\0') {
        if (argv[j][idx] == 'l' || argv[j][idx] == 'L')
          l = j;
        if (argv[j][idx] == 'p' || argv[j][idx] == 'P')
          p = j;
        idx++;
      }
    }
  }
  // Utilisation des logs
  if (l > 0) {
    // options[opt] = "l";
    opt++;
    init_log(argv[0]);
  }

  // Utilisation d'un chemin different pour l'execution du fichier
  if (p > 0) {
    opt += 2;
    if (argv[p + 1][0] == '-') {
      if (is_init()) {
        ecris_log(2);
        ecris_log(1);
      }
      perror("Le chemin n'a pas été spécifié\n");
      return 3;
    }
  }
  opt++;
  // ------ Passer la l'execution de la commande
  int nbr = atoi(argv[opt]);
  int timewait = atoi(argv[opt + 1]);
  int taille = argc - (opt + 2);
  if (nbr == 0 || timewait == 0) {
    perror("Nombre d'argument invalide");
    print_help();
    return 2;
  }

  char *ligne_de_commande[10];
  for (int i = 0; i < taille; i++) {
    ligne_de_commande[i] = argv[opt + 2 + i];
  }
  pid_t pid_fils = fork();
  if (pid_fils == -1) {
    perror("Erreur fork\n");
    exit(errno);
  }
  if (pid_fils == 0) {
    exe_cmd_ntimes(nbr, timewait, taille, ligne_de_commande);
  }

  return 0;
}
