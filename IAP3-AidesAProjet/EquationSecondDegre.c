/* @file Cours1a-EquationSecondDegre.c */

#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	float b=0., c=0., delta=0.;
	unsigned int i, nbTests;
	printf("Resolution de l'equation x^2+bx+c = 0\n"); 
	printf("Nombre de tests ? ");
	scanf("%u", &nbTests);
	for (i=0; i<nbTests; ++i) {
		printf("Entrez les valeurs de b et c : ");
		scanf("%f %f", &b, &c);
		delta = (b*b)-(4*c); 
		if (delta<0.) // 2 racines imaginaires
			printf("Pas de racine reelle\n");
		else 
			if (delta==0.) // 1 racine double
				printf("Une racine reelle : %f\n", -b/2);
			else // 2 racines reelles
				printf("Deux racines reelles : %f et %f\n", 
				       (-b-sqrt(delta))/2., (-b+sqrt(delta))/2.);
	}
	system("pause"); return 0;
}
