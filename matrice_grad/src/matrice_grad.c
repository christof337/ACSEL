#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"
#include "tools/errorHandling.h"
#include "parameters.h"
#include "log.h"

#define MATRIX_FILE_NAME "output/matrix"
#define DATA_FILE_NAME "output/solggc"
#define GK_FILE_NAME "output/gkgk2"
#define GK_LABEL "gkgk2"

#define MATRIX_EXTENSION ".dat"
#define DATA_EXTENSION ".dat" 
#define GK_EXTENSION ".dat"

#define PRECISION_MIN MPFR_PREC_MIN // 2 TODO : enable the user to choose the minimum precision

#define RM mpfr_get_default_rounding_mode()

#define OUTPUT 0


void initGkgk2_global(const size_t nbPrecisions, const size_t nbIterations) {
	arr_alloc(nbPrecisions,nbIterations,&gkgk2_global);
}

void * customConjuguateGradientDescentThreadWrapper(void * precision) {
	const size_t M_SIZE = getParamFromParamEnum(MATRIX_SIZE)->currentValue.s;
	const int NB_GRAD = getParamFromParamEnum(NB_ITER)->currentValue.li; // nombre d'itérations du gradient
	const enum matrixTypeEnum M_TYPE = getParamFromParamEnum(MATRIX_TYPE)->currentValue.mte;
	const enum roundingModeEnum RME = getParamFromParamEnum(ROUNDING_MODE)->currentValue.rme;

	conjuguateGradientDescent((mpfr_prec_t) precision, M_SIZE, NB_GRAD, M_TYPE,
			RME/*, metaGkgk2save[nbGradientIterations]*/);

	return NULL;
}

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

int conjuguateGradientDescent(const int precision, const size_t matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum/*, mpfr_t *metaGkgk2save[nbGradientIterations]*/) {
	int res = 0;
	char logBuffer[500];
	const mpfr_rnd_t roundingMode = roundingModeEnumToMpfrRndT(roundingModeEnum);
	// DECLARATIONS DES TABLEAUX
	mpfr_t (*a)[matrixSize][matrixSize];
	// mpfr_t** a;	// a
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

	sprintf(logBuffer, "\n------\tBoucle precision [%d]\t------\n", precision);
	m_log(precision, logBuffer);
	sprintf(logBuffer, "[%d]\n", precision);
	m_log(precision, logBuffer);
	// INITIALISATIONS
	sprintf(logBuffer, "\tInitialisation des tableaux\n");
	m_log(precision, logBuffer);
	// ALLOCATIONS
	createArray(&x, matrixSize, precision);
	createMatrix(matrixSize, matrixSize, &a, precision);
	createArray(&solgc, matrixSize, precision);
	createArray(&b, matrixSize, precision);
	createArray(&gkTmp, matrixSize, precision);
	createArray(&gk, matrixSize, precision);
	createArray(&dk, matrixSize, precision);
	createArray(&adk, matrixSize, precision);
	createArray(&gkgk2save, nbGradientIterations, precision);
	sprintf(logBuffer, "\tAllocation des variables MPFR\n");
	m_log(precision, logBuffer);
	m_init2(gkGkTmp1, precision);
	m_init2(adkDkTmp, precision);
	m_init2(alphak, precision);
	m_init2(gkgk2, precision);
	m_init2(gkGkTmp2, precision);
	m_init2(betak, precision);
	sprintf(logBuffer, "\tInitialisation des tableaux temporaires\n");
	m_log(precision, logBuffer);
	createArray(&dkAlphakTmp, matrixSize, precision);
	createArray(&adkAlphakTmp, matrixSize, precision);
	createArray(&dkBetaKTmp, matrixSize, precision);
	sprintf(logBuffer, "\tRemplissage des tableaux\n");
	m_log(precision, logBuffer);
	// initialisation de a
	switch (matrixType) {
	case RANDOM:
		fillMatrixRandomly(matrixSize, matrixSize, *a);
		break;
	case EXPONENTIAL:
		fillMatrixExponentially(matrixSize, matrixSize, *a, roundingModeEnum);
		break;
	case HILBERT:
	default:
		printErrorMessage("\nError : Matrix type not implemented.\n");
		return -1;
	}
	// initialisation de x linéairement
	fillArrayLinearly(x, matrixSize);
	sprintf(logBuffer, "\tDébut des calculs\n");
	m_log(precision, logBuffer);
	// on multiplie a et x ( B = AX )
	customMatrixMultVector(b, matrixSize, *a, x, roundingModeEnum);
	fillArrayWithZeros(solgc, matrixSize);
	// on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
	// gradient conjugué
	// GK = A * XX - B
	customMatrixMultVector(gkTmp, matrixSize, *a, solgc, roundingModeEnum);
	vectorMinusVector(gk, gkTmp, matrixSize, b, matrixSize, roundingModeEnum);
	// DK = GK
	vectorCopy(dk, gk, matrixSize);
	sprintf(logBuffer, "\t-- Itérations du gradient... --\n");
	m_log(precision, logBuffer);
	// on itère sur le nombre d'itérations déterminé par NB_GRAD
	for (int iter = 0 ; iter < nbGradientIterations ; ++iter) {
		// ADK = A * DK
		customMatrixMultVector(adk, matrixSize, *a, dk, roundingModeEnum);
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
	if ( OUTPUT) {
		sprintf(logBuffer, "\tEcriture de la matrice a dans un fichier (output/matrix.dat)\n");
		m_log(precision, logBuffer);
		// écriture de la matrice a dans un fichier
		int error = writeMatrixInFile(matrixSize, matrixSize, *a, precision);
		if (error != 0) {
			// error
			res = error;
		}
		sprintf(logBuffer,
				"\tEcriture de i, x(i) et solgc(i) dans un fichier (output/solggc.dat)\n");
		m_log(precision, logBuffer);
		// écriture de i, x(i) et solgc(i) dans un fichier solggc.dat
		error = writeDataInFile(x, solgc, matrixSize, precision);
		if (error != 0) {
			// error
			res = error;
		}
		sprintf(logBuffer, "\tEcriture de gkgk2 dans un fichier (output/gkgk.dat)\n");
		m_log(precision, logBuffer);
		// écriture de gkgk2 dans un fichier gkgk.dat (une seule ligne)
//		error = writeGkArrayInFile(gkgk2save, nbGradientIterations, precision);
//		if (error != 0) {
//			// error
//			res = error;
//		}
	}
	// saving gkgk2
	createArray(&(gkgk2_global[precision-MPFR_PREC_MIN]),nbGradientIterations,precision);
	vectorCopy(gkgk2_global[precision-MPFR_PREC_MIN],gkgk2save,nbGradientIterations);

	sprintf(logBuffer,"Gkgk2 : %F",mpfr_get_d(gkgk2,MPFR_RNDN));
	m_log(precision, logBuffer);
	sprintf(logBuffer, "\tLibérations des variables\n");
	m_log(precision, logBuffer);
	m_clear(gkGkTmp1);
	m_clear(adkDkTmp);
	m_clear(alphak);
	m_clear(gkgk2);
	m_clear(gkGkTmp2);
	m_clear(betak);
	sprintf(logBuffer, "\tLibérations des tableaux\n");
	m_log(precision, logBuffer);
	freeArray(x, matrixSize);
	freeMatrix(matrixSize, matrixSize, a);
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

//	printf("\nStochastic rounding has been called %ld times.\n", NB_STOCH_ROUND);
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

int customMatrixMultVector(mpfr_t * result, const size_t size, mpfr_t matrix[size][size],
		mpfr_t * vector, const enum roundingModeEnum rme) {
	return matrixMultVector(result, size, size, matrix, vector, size, rme);
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
int writeMatrixInFile(const size_t n, const size_t m, mpfr_t matrix[m][n],
		const mpfr_prec_t precision) {
	char fileName[20];
	sprintf(fileName, "%s%ld%s", MATRIX_FILE_NAME, precision, MATRIX_EXTENSION);
//	if (precision == MPFR_PREC_MIN) {
	eraseFile(fileName);
//	}
	return writeMatrix(n, m, matrix, fileName);
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
int writeDataInFile(mpfr_t * x, mpfr_t * solgc, const size_t size, mpfr_prec_t precision) {
	int res = 0;

	char fileName[20];

	const char * labels[] = { "i", "x", "solgc" };
	const int n_array = (sizeof(labels) / sizeof(const char *));

	// i 
	mpfr_t * iArray;
	createArray(&iArray, size, precision);
	fillArrayLinearly(iArray, size);

	mpfr_t * data[] = { iArray, x, solgc };

	sprintf(fileName, "%s%ld%s", DATA_FILE_NAME, precision, DATA_EXTENSION);

//	if (precision == MPFR_PREC_MIN) {
	eraseFile(fileName);
//	}

	res = writeData(data, size, fileName, labels, n_array);

	freeArray(iArray, size);

	return res;
}

/**
 * @brief      Writes a gk array in file named `GK_FILE_NAME`.
 *
 * @param      array  The array
 * @param[in]  size   The size
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
//int writeGkGlobalArrayInFile(mpfr_t ** array, const size_t size, mpfr_prec_t precision) {
//	char fileName[19];
//	//sprintf(fileName,"%s%ld%s",GK_FILE_NAME,precision,GK_EXTENSION);
//	//TODO : spécifier les paramètres actuels de l'application dans le nom du fichier
//	sprintf(fileName, "%s%s", GK_FILE_NAME, GK_EXTENSION);
//
//	if (precision == MPFR_PREC_MIN) {
//		// réinitialisation du fichier et écriture des en têtes
//		FILE * pf;
//		pf = fopen(fileName, "w+");
//		fprintf(pf, "i\t%12s\tprec\n", GK_LABEL);
//		fclose(pf);
//	}
//
//	return writeArray(array, size, fileName, GK_LABEL);
//}


int writeGkgk2_global(const size_t nbPrecisionsTreated, const size_t nbIterations) {
	int res = 0;

	char fileName[100];
	char * prefix = buildPrefixFromParams();
	char * suffix = buildSuffix();

	sprintf(fileName,"%s%s%s",GK_FILE_NAME,prefix,suffix);

	eraseFile(fileName);

	for ( size_t i = 0 ; i < nbPrecisionsTreated ; ++i ) {
		writeArray(gkgk2_global[i],nbIterations,fileName,"Gkgk2");
	}

	//res = writeGkGlobalArrayInFile(nbPrecisionsTreated,nbIterations,gkgk2_global,fileName);

	free(prefix);
	free(suffix);

	return res;
}

/**
 * @brief      Print a final error message
 */
void printFinalErrorStatement() {
	fprintf(stderr, "\nUne erreur est survenue.\nFin du programme...\n");
}

