/**
 * @file      printlog_h.h
 * @author    Johann
 * @version   1.0
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'ecritures des logs.
 *
 */

#ifndef PRINTLOG_H
#define PRINTLOG_H

/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_log(int log);
/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_date_heure(void);
/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_nom_prog(char *prog);
/**
 * La fonction ouvre le fichier des logs
 *
 * @author Raphael Bauvin et Johann
 * @return 0 si le fichier est ouvert avec succé
 * @return 1 si une erreur est survenu
 *
 */
int init_log(char *nom_prog);
/**
 * La fonction ferme le fichier
 *
 * @author Raphael Bauvin
 * @return 0 si fichier fermé avec succé
 */
int close_log(void);
/**
 * La fonction verifie si le fichier est initialise
 *
 * @author Raphael Bauvin
 * @return 1 si fichier ouvert
 * @return 0 si fichier fermé
 */
int is_init(void);

#endif // PRINTLOG_H
