#include <stdio.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"

#define MATRIX_FILE_NAME "output/matrix.dat"
#define DATA_FILE_NAME "output/solggc.dat"
#define GK_FILE_NAME "output/gkgk2.dat"
#define GK_LABEL "gkgk2"

// #define MATRIX_EXTENSION = ".dat"; // TODO : séparer le nom du fichier et l'extension (implique de faire un utilitaire de concaténation)

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

int writeMatrixInFile(double ** matrix, const int n, const int m) {
	return writeMatrix(matrix,n,m,MATRIX_FILE_NAME);
}


int writeDataInFile(double * x, double * solgc, const int size) {
	const char * labels[] = {
		"i",
		"x",
		"solgc"
	} ;
	const int n_array = (sizeof(labels) / sizeof (const char *));

	// i 
	double * iArray = createArray(size);
	iArray = fillArrayLinearly(iArray,size);

	double * data[] = {
		iArray,
		x,
		solgc
	} ;

	return writeData(data, size, DATA_FILE_NAME, labels, n_array);
}


int writeArrayInFile(double * array, const int size) {
	return writeArray(array,size,GK_FILE_NAME,GK_LABEL);
}

void printFinalStatement() {
	fprintf(stderr, "\nUne erreur est survenue.\nFin du programme...\n");
}