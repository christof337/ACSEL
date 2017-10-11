#include <stdio.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"

int askTailleMatrice() {
	int tailleMatrice = 0;
	do {
		printf("Taille Matrice ?\n");
		tailleMatrice = askForInt();
	}while ( tailleMatrice <= 0 );
}


/**
 * Custom function used to bypass the fact that in our program we only have one shared size for the matrix and vectors : TAILLE_MATRICE
 */
double * customMatrixMultVector(double ** matrix, double * vector, const int size) {
   return matrixMultVector(matrix,size,size,vector,size);
}