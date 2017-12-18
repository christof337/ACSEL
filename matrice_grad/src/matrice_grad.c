#include <stdio.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"
#include "tools/errorHandling.h"

#define MATRIX_FILE_NAME "output/matrix"
#define DATA_FILE_NAME "output/solggc"
#define GK_FILE_NAME "output/gkgk2"
#define GK_LABEL "gkgk2"

#define MATRIX_EXTENSION ".dat" // TODO : séparer le nom du fichier et l'extension (implique de faire un utilitaire de concaténation)
#define DATA_EXTENSION ".dat" 
#define GK_EXTENSION ".dat"

#define PRECISION_MIN MPFR_PREC_MIN // 2 TODO : enable the user to choose the minimum precision

#define RM mpfr_get_default_rounding_mode()

/**
 * @file matrice_grad.c
 * @author     Christophe Pont
 * @date       9 Oct 2017
 * @brief      File containing various functions used for our specific usage in this very program.
 *
 *             Utilise les types de mpfr. 
 *
 * @see        http://www.mpfr.org/mpfr-current/mpfr.html
 */

int conjuguateGradientDescent(const int maxPrecision, const int matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum, const mpfr_rnd_t roundingMode, int res) {
	// DECLARATIONS DES TABLEAUX
	mpfr_t** a;	// a
	mpfr_t* x;	// x
	mpfr_t* solgc;
	mpfr_t* gkgk2save;
	mpfr_t* b;	// b
	mpfr_t* gk;	// gk : gradient conjugué?
	mpfr_t* gkTmp;	// gk temporaire
	mpfr_t* dk;	// dk : ?
	mpfr_t* adk;	// adk : ?
	mpfr_t gkGkTmp1;
	mpfr_t adkDkTmp;
	mpfr_t alphak;
	mpfr_t gkgk2;
	mpfr_t gkGkTmp2;
	mpfr_t betak;
	mpfr_t* dkAlphakTmp;
	mpfr_t* adkAlphakTmp;
	mpfr_t* dkBetaKTmp;
	printf("\nDébut boucle principale itérant sur les précisions (non parrallélisée)");
	// DEBUT BOUCLE ( entièrement parralélisable )
	for (int pre = PRECISION_MIN ; pre < maxPrecision ; ++pre) {
		printf("\n------\tBoucle precision [%d]\t------", pre);
		printf("\n[%d]", pre);
		fflush(stdout);
		// INITIALISATIONS
		printf("\n\tInitialisation des tableaux");
		fflush(stdout);
		// ALLOCATIONS
		createArray(&x, matrixSize, pre);
		createMatrix(&a, matrixSize, matrixSize, pre);
		createArray(&solgc, matrixSize, pre);
		createArray(&b, matrixSize, pre);
		createArray(&gkTmp, matrixSize, pre);
		createArray(&gk, matrixSize, pre);
		createArray(&dk, matrixSize, pre);
		createArray(&adk, matrixSize, pre);
		createArray(&gkgk2save, nbGradientIterations, pre);
		printf("\n\tAllocation des variables MPFR");
		fflush(stdout);
		m_init2(gkGkTmp1, pre);
		m_init2(adkDkTmp, pre);
		m_init2(alphak, pre);
		m_init2(gkgk2, pre);
		m_init2(gkGkTmp2, pre);
		m_init2(betak, pre);
		printf("\n\tInitialisation des tableaux temporaires");
		fflush(stdout);
		createArray(&dkAlphakTmp, matrixSize, pre);
		createArray(&adkAlphakTmp, matrixSize, pre);
		createArray(&dkBetaKTmp, matrixSize, pre);
		printf("\n\tRemplissage des tableaux");
		fflush(stdout);
		// initialisation de a
		switch (matrixType) {
		case RANDOM:
			fillMatrixRandomly(a, matrixSize, matrixSize);
			break;
		case EXPONENTIAL:
			fillMatrixExponentially(a, matrixSize, matrixSize, roundingModeEnum);
			break;
		case HILBERT:
		default:
			printErrorMessage("\nError : Matrix type not implemented.\n");
			return -1;
		}
		// initialisation de x linéairement
		fillArrayLinearly(x, matrixSize);
		printf("\n\tDébut des calculs");
		fflush(stdout);
		// on multiplie a et x ( B = AX )
		customMatrixMultVector(b, a, x, matrixSize, roundingModeEnum);
		fillArrayWithZeros(solgc, matrixSize);
		// on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
		// gradient conjugué
		// GK = A * XX - B
		customMatrixMultVector(gkTmp, a, solgc, matrixSize, roundingModeEnum);
		vectorMinusVector(gk, gkTmp, matrixSize, b, matrixSize, roundingModeEnum);
		// DK = GK
		vectorCopy(dk, gk, matrixSize);
		printf("\n\t-- Itérations du gradient... --");
		fflush(stdout);
		// on itère sur le nombre d'itérations déterminé par NB_GRAD
		for (int iter = 0 ; iter < nbGradientIterations ; ++iter) {
			// ADK = A * DK
			customMatrixMultVector(adk, a, dk, matrixSize, roundingModeEnum);
			// GKGK = GK * GK
			innerDotProduct(gkGkTmp1, gk, matrixSize, roundingModeEnum); // gkgk
			// ADKDK = ADK * DK
			dotProduct(adkDkTmp, adk, matrixSize, dk, matrixSize, roundingModeEnum); // adkdk
			// AlphaK = GKGK / ADKDK ==> AlphaK = (GK*GK)/(ADK*DK)
			m_div(alphak, gkGkTmp1, adkDkTmp, roundingModeEnum);
			// XX = XX - AlphaK * DK
			vectorMultValue(dkAlphakTmp, dk, matrixSize, alphak, roundingModeEnum);
			vectorMinusVector(solgc, solgc, matrixSize, dkAlphakTmp, matrixSize, roundingModeEnum);
			// GK = GK - AlphaK * ADK
			vectorMultValue(adkAlphakTmp, adk, matrixSize, alphak, roundingModeEnum);
			vectorMinusVector(gk, gk, matrixSize, adkAlphakTmp, matrixSize, roundingModeEnum);
			// gkgk2 = sqrt of (square sum of gk elements)
			sumSquare(gkgk2, gk, matrixSize, roundingModeEnum);
			mpfr_sqrt(gkgk2, gkgk2, roundingMode);
			// GKGK = GK*GK
			innerDotProduct(gkGkTmp2, gk, matrixSize, roundingModeEnum); // pertinent car changements réalisés sur gk depuis gkgkTmp1
			m_div(betak, gkGkTmp2, gkGkTmp1, roundingModeEnum);
			// DK = GK + BetaK*DK
			vectorMultValue(dkBetaKTmp, dk, matrixSize, betak, roundingModeEnum);
			vectorPlusVector(dk, gk, matrixSize, dkBetaKTmp, matrixSize, roundingModeEnum);
			// sauvegarde
			mpfr_set(gkgk2save[iter], gkgk2, RM);
			// libérations mémoire
			//free(dkAlphakTmp);
			//free(solgcTmp);
			//free(adkAlphakTmp);
			//free(gkTmp);
			//free(dkBetaKTmp);
		}
		printf("\n\tEcriture de la matrice a dans un fichier (output/matrix.dat)");
		fflush(stdout);
		// écriture de la matrice a dans un fichier
		int error = writeMatrixInFile(a, matrixSize, matrixSize, pre);
		if (error != 0) {
			// error
			res = error;
		}
		printf("\n\tEcriture de i, x(i) et solgc(i) dans un fichier (output/solggc.dat)");
		fflush(stdout);
		// écriture de i, x(i) et solgc(i) dans un fichier solggc.dat
		error = writeDataInFile(x, solgc, matrixSize, pre);
		if (error != 0) {
			// error
			res = error;
		}
		printf("\n\tEcriture de gkgk2 dans un fichier (output/gkgk.dat)");
		fflush(stdout);
		// écriture de gkgk2 dans un fichier gkgk.dat
		error = writeGkArrayInFile(gkgk2save, nbGradientIterations, pre);
		if (error != 0) {
			// error
			res = error;
		}
		printf("\n\tLibérations des variables");
		fflush(stdout);
		m_clear(gkGkTmp1);
		m_clear(adkDkTmp);
		m_clear(alphak);
		m_clear(gkgk2);
		m_clear(gkGkTmp2);
		m_clear(betak);
		printf("\n\tLibérations des tableaux");
		fflush(stdout);
		freeArray(x, matrixSize);
		freeMatrix(a, matrixSize, matrixSize);
		freeArray(b, matrixSize);
		freeArray(solgc, matrixSize);
		freeArray(gkgk2save, nbGradientIterations);
		freeArray(gk, matrixSize);
		freeArray(dk, matrixSize);
		freeArray(adk, matrixSize);
		freeArray(gkTmp, matrixSize);
		freeArray(dkAlphakTmp, matrixSize);
		freeArray(adkAlphakTmp, matrixSize);
		freeArray(dkBetaKTmp, matrixSize);
	}
	// fin boucle principale (pre)
	return res;
}

/**
 * @brief      Ask for the matrix size up until a positive value is input
 * @deprecated
 * @return     The input int value
 */
int askTailleMatrice() {
	int tailleMatrice = 0;
	do {
		printf("\nTaille Matrice ?\n");
		tailleMatrice = askForInt();
	} while (tailleMatrice <= 0);
	return tailleMatrice;
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
int customMatrixMultVector(mpfr_t * result, mpfr_t ** matrix, mpfr_t * vector, const int size, const enum roundingModeEnum rme) {
	return matrixMultVector(result, matrix, size, size, vector, size, rme);
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
