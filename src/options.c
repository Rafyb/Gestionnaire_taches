#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int option1 = 0;
int option2 = 0;
int option3 = 0;
int option4 = 0;
int option5 = 0;

int j = 1;

int main(int argc, char** argv){
	while (argv[j][0]=='-'){
		int idx = 1;
		while (argv[j][idx]!=0){
			if (argv[j][idx]=='option1')option1=j;
			if (argv[j][idx]=='option2')option2=j;
			if (argv[j][idx]=='option3')option3=j;
			if (argv[j][idx]=='option4')option4=j;
			if (argv[j][idx]=='option5')option5=j;
			idx++;
		}
		j++;
	}
	
	char chaine[100];
		if (option1 != 0) {
			if (argv[option1 +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("option1: %s\n", argv[option1 +1]);
			}
		}
		if (option2 != 0) {
			if (argv[option2 +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("option2: %s\n", argv[option2 +1]);
			}
		}
		if (option3 != 0) {
			if (argv[option3 +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("option3: %s\n", argv[option3 +1]);
			}
		}
		if (option4 != 0) {
			if (argv[option4 +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("option4: %s\n", argv[option4 +1]);
			}
		}
		if (option5 != 0) {
			if (argv[option5 +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("option5: %s\n", argv[option5 +1]);
			}
		}	
	

return 0;
}
