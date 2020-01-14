/**
 * @file      commandes_h.h
 * @author    Raphael Bauvin, Johann De Almeida
 * @version   14012020
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */
#ifndef COMMANDES_H
#define COMMANDES_H

typedef struct S_Otpions {
  char *path; // - path
  int h;      // - heure
  int m;      // - minute
  int l;      // - log
  int d;      // - différé
} T_Options;

/**
 * @brief La fonction parcourt les arguments et enregistre les options dans la
 * structure fournit en paramètre
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 * @param options : structure contenant les options possibles
 * @return opt : nombre d'options lues
 **/
int gerer_options(int argc, char **argv, T_Options *options);

/**
 * @brief Affiche l'aide à l'utilisation du programme
 *
 **/
void print_help(void);

/**
 * @brief Execute la ligne de commande à l'aide de "execv" ou "execvp" en
 *fonction de si le chemin est spécifié ou non
 *
 * @param argc : nombre d'arguments de la ligne de commande
 * @param argv : les arguments de la ligne de commande
 **/
int exe_cmd(int argc, char **argv, char *path);

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
int exe_cmd_ntimes(int nbr, int timewait, int argc, char **argv, char *path);

#endif
