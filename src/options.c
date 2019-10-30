#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;

int j = 1;

int main(int argc, char** argv){
	for (j; j< argc; j++) {
		if (argv[j][0]=='-'){
			int idx = 1;
			while (argv[j][idx]!='\0'){
				if (argv[j][idx]=='A')A=j;
				if (argv[j][idx]=='B')B=j;
				if (argv[j][idx]=='C')C=j;
				if (argv[j][idx]=='D')D=j;
				if (argv[j][idx]=='E')E=j;
				idx++;
			}
		}
	}
	
	char chaine[100];
		if (A != 0) {
			if (argv[A +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("A: %s\n", argv[A +1]);
			}
		}
		if (B != 0) {
			if (argv[B +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("B: %s\n", argv[B +1]);
			}
		}
		if (C != 0) {
			if (argv[C +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("C: %s\n", argv[C +1]);
			}
		}
		if (D != 0) {
			if (argv[D +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("D: %s\n", argv[D +1]);
			}
		}
		if (E != 0) {
			if (argv[E +1][0]=='-') {
				printf("Le chemin n'a pas été spécifié");
			}
			else
			{
				printf("E: %s\n", argv[E +1]);
			}
		}	
	

return 0;
}
