/**
 * @file      commandes_h.h
 * @author    Raphael Bauvin
 * @version   1.0
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */

#ifndef COMMANDES_H
#define COMMANDES_H

/**
 * Affiche l'aide à l'utilisation du programme
 *
 * @author Raphael Bauvin
 **/
void print_help(void);

/**
 * Execute la ligne de commande
 *
 * @author Raphael Bauvin
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 **/
int exe_cmd(int argc, char **argv);

/**
 * Execute la ligne de commande depuis le chemin spécifié
 *
 * @author Raphael Bauvin
 *
 * @param argc : nombre d'argument de la ligne de commande
 * @param argv : arguments de la ligne de commande
 * @param path : chemin de la commande à éxécuter
 **/
int exe_cmd_path(int argc, char **argv, char *path);

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
int exe_cmd_ntimes(int nbr, int timewait, int argc, char **argv, char *path);

#endif
