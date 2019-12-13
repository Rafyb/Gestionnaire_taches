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

void print_help(void);

int exe_cmd(int argc, char **argv);

int exe_cmd_ntimes(int nbr, int timewait, int argc, char **argv);

#endif
