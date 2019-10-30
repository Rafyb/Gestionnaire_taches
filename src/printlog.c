#include <stdio.h>
#include <stdlib.h>

FILE* fichier = NULL;

int init_log(void){
    fichier = fopen("../log/test.log", "w+");    
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier de log");
        return 1;
    }
    return 0;
}

int close_log(void){
    return fclose(fichier);
}

void ecris_log(int log){
	switch(log){
		case -1:
			fprintf(fichier, "==========================\n");
			fprintf(fichier, "    DEBUT DU TRAITEMENT   \n");
			fprintf(fichier, "==========================\n");
			break;
		case 0:
			fprintf(fichier, "==========================\n");
			fprintf(fichier, "FIN NORMALE DU TRAITEMENT\n");
			fprintf(fichier, "==========================\n");
			break;
		case 1:
			fprintf(fichier, "==========================\n");
			fprintf(fichier, "FIN ANORMALE DU TRAITEMENT\n");
			fprintf(fichier, "==========================\n");
			break;
		case 2:
			fprintf(fichier, "Le chemin n'a pas été spécifié\n");
			break;
	}
}
