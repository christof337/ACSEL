#include <stdio.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"

#define MATRIX_FILE_NAME "output/matrix"
#define DATA_FILE_NAME "output/solggc"
#define GK_FILE_NAME "output/gkgk2"
#define GK_LABEL "gkgk2"

#define MATRIX_EXTENSION ".dat" // TODO : séparer le nom du fichier et l'extension (implique de faire un utilitaire de concaténation)
#define DATA_EXTENSION ".dat" 
#define GK_EXTENSION ".dat"

/**
 * @file arrayUtils.c
 * @author     Christophe Pont
 * @date       9 Oct 2017
 * @brief      File containing various functions used for our specific usage in this very program.
 *
 *             Utilise les types de mpfr. 
 *
 * @see        http://www.mpfr.org/mpfr-current/mpfr.html
 */

/**
 * @brief      Ask for the matrix size up until a positive value is input
 *
 * @return     The input int value
 */
int askTailleMatrice() {
	int tailleMatrice = 0;
	do {
		printf("\nTaille Matrice ?\n");
		tailleMatrice = askForInt();
	} while (tailleMatrice <= 0);
}

/**
 * Custom function used to bypass the fact that in our program we only have one
 * shared size for the matrix and vectors : SIZE_M
 *
 * @param      result  The resulting vector
 * @param      matrix  The matrix to multiply
 * @param      vector  The vector to multiply
 * @param[in]  size    The size of all of the dimensions
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int customMatrixMultVector(mpfr_t * result, mpfr_t ** matrix, mpfr_t * vector, const int size) {
	return matrixMultVector(result, matrix, size, size, vector, size);
}

/**
 * @brief      Writes a matrix in file of name `MATRIX_FILE_NAME`.
 *
 * @param      matrix  The matrix to write
 * @param[in]  n       Number of columns of the matrix
 * @param[in]  m       Number of rows of the matrix
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeMatrixInFile(mpfr_t ** matrix, const int n, const int m, const mpfr_prec_t precision) {
	char fileName[20];
	sprintf(fileName, "%s%ld%s", MATRIX_FILE_NAME, precision, MATRIX_EXTENSION);
	return writeMatrix(matrix, n, m, fileName);
}

/**
 * @brief      Writes data in a file named `DATA_FILE_NAME`.
 *
 * @param      x          first array to write
 * @param      solgc      second array to write
 * @param[in]  size       The size of the arrays
 * @param[in]  precision  The precision
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeDataInFile(mpfr_t * x, mpfr_t * solgc, const int size, mpfr_prec_t precision) {
	char fileName[20];

	const char * labels[] = { "i", "x", "solgc" };
	const int n_array = (sizeof(labels) / sizeof(const char *));

	// i 
	mpfr_t * iArray;
	createArray(&iArray, size, precision);
	fillArrayLinearly(iArray, size);

	mpfr_t * data[] = { iArray, x, solgc };

	sprintf(fileName, "%s%ld%s", DATA_FILE_NAME, precision, DATA_EXTENSION);

	return writeData(data, size, fileName, labels, n_array);
}

/**
 * @brief      Writes a gk array in file named `GK_FILE_NAME`.
 *
 * @param      array  The array
 * @param[in]  size   The size
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeGkArrayInFile(mpfr_t * array, const int size, mpfr_prec_t precision) {
	char fileName[19];
	//sprintf(fileName,"%s%ld%s",GK_FILE_NAME,precision,GK_EXTENSION);
	//TODO : spécifier les paramètres actuels de l'application dans le nom du fichier
	sprintf(fileName, "%s%s", GK_FILE_NAME, GK_EXTENSION);

	if (precision == 2) {
		// réinitialisation du fichier et écriture des en têtes
		FILE * pf;
		pf = fopen(fileName, "w+");
		fprintf(pf, "i\t%12s\tprec\n", GK_LABEL);
		fclose(pf);
	}

	return writeArray(array, size, fileName, GK_LABEL);
}

/**
 * @brief      Print a final error message
 */
void printFinalErrorStatement() {
	fprintf(stderr, "\nUne erreur est survenue.\nFin du programme...\n");
}
