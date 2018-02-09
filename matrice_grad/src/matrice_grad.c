#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <mpfr.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"
#include "tools/errorHandling.h"
#include "tools/customMath.h"
#include "tools/utils.h"
#include "parameters.h"
#include "log.h"

#define MATRIX_FILE_NAME "output/matrix"
#define DATA_FILE_NAME "output/solggc"
#define GK_FILE_NAME "output/gkgk2"
#define GK_LABEL "gkgk2"
#define LORENZ_PREFIX "output/lorenz"

#define MATRIX_EXTENSION ".dat"
#define DATA_EXTENSION ".dat" 
#define GK_EXTENSION ".dat"

#define RM mpfr_get_default_rounding_mode()

#define OUTPUT 0

void initGkgk2_global(const size_t nbPrecisions, const size_t nbIterations) {
	_arr_alloc_2d(nbPrecisions, nbIterations, &gkgk2_global);
}

void * customConjuguateGradientDescentThreadWrapper(void * precision) {
	const size_t M_SIZE = getParamFromParamEnum(MATRIX_SIZE)->currentValue.s;
	const int NB_GRAD = getParamFromParamEnum(NB_ITER)->currentValue.li; // nombre d'itérations du gradient
	const enum matrixTypeEnum M_TYPE = getParamFromParamEnum(MATRIX_TYPE)->currentValue.mte;
	const enum roundingModeEnum RME = getParamFromParamEnum(ROUNDING_MODE)->currentValue.rme;

	long int *prec = precision;
	conjuguateGradientDescent(*prec, M_SIZE, NB_GRAD, M_TYPE,
			RME/*, metaGkgk2save[nbGradientIterations]*/);

	return NULL;
}

void allocateMpfrVars(const mpfr_prec_t precision, mpfr_t gkGkTmp1, mpfr_t adkDkTmp, mpfr_t alphak,
		mpfr_t gkgk2, mpfr_t gkGkTmp2, mpfr_t betak) {
	m_init2(gkGkTmp1, precision);
	m_init2(adkDkTmp, precision);
	m_init2(alphak, precision);
	m_init2(gkgk2, precision);
	m_init2(gkGkTmp2, precision);
	m_init2(betak, precision);
}

void allocateArrays(const size_t matrixSize, const mpfr_prec_t precision,
		const int nbGradientIterations, mpfr_t** adk, mpfr_t** gkgk2save, mpfr_t** dkTmp) {
	// ALLOCATIONS
	createArray(adk, matrixSize, precision);
	createArray(gkgk2save, nbGradientIterations, precision);
	createArray(dkTmp, matrixSize, precision);
}

enum ERRORS fillA(const enum matrixTypeEnum matrixType, const size_t m, const size_t n,
		mpfr_t a[m][n], const enum roundingModeEnum roundingModeEnum) {
	enum ERRORS res = ERROR_OK;
	// initialisation de a
	switch (matrixType) {
	case RANDOM:
		fillMatrixRandomly(m, n, a);
		break;
	case EXPONENTIAL:
		fillMatrixExponentially(m, n, a, roundingModeEnum);
		break;
	case HILBERT:
	default:
		res = ERROR_MATRIX_TYPE_NOT_IMPLEMENTED;
	}
	return res;
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

int conjuguateGradientDescent(const mpfr_prec_t precision, const size_t matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum) {
	int res = 0;
	char logBuffer[500];
	const mpfr_rnd_t roundingMode = roundingModeEnumToMpfrRndT(roundingModeEnum);
	// DECLARATIONS DES TABLEAUX
	mpfr_t (*a)[matrixSize][matrixSize];
	// mpfr_t** a;	// a
	mpfr_t* x /* x ( vecteur linéaire )*/, *solgc, *gkgk2save, *b /* b */,
			*gk /* gk : gradient conjugué */, *gkTmp /* gk temporaire */, *dk /*dk : ? */, *adk
			/*adk : ?*/;
	mpfr_t gkGkTmp1, adkDkTmp, alphak, gkgk2, gkGkTmp2, betak;
	mpfr_t* dkTmp;

	/****************************************************************/
	sprintf(logBuffer, "\n------\tBoucle precision [%ld]\t------\n", precision);
	m_log(precision, logBuffer);
	sprintf(logBuffer, "[%ld]\n", precision);
	m_log(precision, logBuffer);

	/****************************************************************/
	sprintf(logBuffer, "\tInitialisation et remplissage des tableaux\n");
	m_log(precision, logBuffer);

	// initialisation de x linéairement
	createArray(&x, matrixSize, precision);
	fillArrayLinearly(x, matrixSize);

	sprintf(logBuffer, "\tDébut des calculs\n");
	m_log(precision, logBuffer);

	createArray(&b, matrixSize, precision);
	// initialisation de a
	createMatrix(matrixSize, matrixSize, &a, precision);
	res = fillA(matrixType, matrixSize, matrixSize, *a, roundingModeEnum);
	if (res != ERROR_OK) {
		printCustomError(res, 0);
	}
	assert(res == ERROR_OK);

	// on multiplie a et x ( B = AX )
	customMatrixMultVector(b, matrixSize, *a, x, roundingModeEnum);
	freeArray(x, matrixSize);
	createArray(&solgc, matrixSize, precision);
	fillArrayWithZeros(solgc, matrixSize);
	// on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
	// gradient conjuguétInitialisation
	createArray(&gkTmp, matrixSize, precision);
	// GK = A * XX - B
	customMatrixMultVector(gkTmp, matrixSize, *a, solgc, roundingModeEnum);
	createArray(&gk, matrixSize, precision);
	vectorMinusVector(gk, gkTmp, matrixSize, b, matrixSize, roundingModeEnum);
	freeArray(b, matrixSize);
	freeArray(gkTmp, matrixSize); // use gkTmp later?
	// DK = GK
	createArray(&dk, matrixSize, precision);
	vectorCopy(dk, gk, matrixSize);

	/****************************************************************/
	sprintf(logBuffer, "\tAllocation des variables MPFR\n");
	m_log(precision, logBuffer);
	allocateMpfrVars(precision, gkGkTmp1, adkDkTmp, alphak, gkgk2, gkGkTmp2, betak);

	sprintf(logBuffer, "\tInitialisation des tableaux temporaires\n");
	m_log(precision, logBuffer);
	allocateArrays(matrixSize, precision, nbGradientIterations, &adk, &gkgk2save, &dkTmp);

	sprintf(logBuffer, "\t-- Itérations du gradient... --\n");
	m_log(precision, logBuffer);

	// on itère sur le nombre d'itérations déterminé par NB_GRAD
	for (int iter = 0 ; iter < nbGradientIterations ; ++iter) {
		// ADK = A * DK
		customMatrixMultVector(adk, matrixSize, *a, dk, roundingModeEnum);
		// GKGK = GK * GK
		innerDotProduct(gkGkTmp1, gk, matrixSize, roundingModeEnum); // gkgk
		// ADKDK = ADK * DKdkAlphakTmp
		dotProduct(adkDkTmp, adk, matrixSize, dk, matrixSize, roundingModeEnum); // adkdk
		// AlphaK = GKGK / ADKDK ==> AlphaK = (GK*GK)/(ADK*DK)
		m_div(alphak, gkGkTmp1, adkDkTmp, roundingModeEnum);
		// XX = XX - AlphaK * DK
		vectorMultValue(dkTmp, dk, matrixSize, alphak, roundingModeEnum);
		vectorMinusVector(solgc, solgc, matrixSize, dkTmp, matrixSize, roundingModeEnum);
		// GK = GK - AlphaK * ADK
		vectorMultValue(dkTmp, adk, matrixSize, alphak, roundingModeEnum);
		vectorMinusVector(gk, gk, matrixSize, dkTmp, matrixSize, roundingModeEnum);
		// gkgk2 = sqrt of (square sum of gk elements)
		sumSquare(gkgk2, gk, matrixSize, roundingModeEnum);
		mpfr_sqrt(gkgk2, gkgk2, roundingMode);
		// GKGK = GK*GK
		innerDotProduct(gkGkTmp2, gk, matrixSize, roundingModeEnum); // pertinent car changements réalisés sur gk depuis gkgkTmp1
		m_div(betak, gkGkTmp2, gkGkTmp1, roundingModeEnum);
		// DK = GK + BetaK*DK
		vectorMultValue(dkTmp, dk, matrixSize, betak, roundingModeEnum);
		vectorPlusVector(dk, gk, matrixSize, dkTmp, matrixSize, roundingModeEnum);
		// sauvegarde
		mpfr_set(gkgk2save[iter], gkgk2, RM);
	}
	/****************************************************************/
	if ( OUTPUT) {
		sprintf(logBuffer, "\tEcriture de la matrice a dans un fichier (output/matrix.dat)\n");
		m_log(precision, logBuffer);
		// écriture de la matrice a dans un fichier
		int error = writeMatrixInFile(matrixSize, matrixSize, *a, precision);
		if (error != 0) {
			// error
			res = error;
		}
//		sprintf(logBuffer,
//				"\tEcriture de i, x(i) et solgc(i) dans un fichier (output/solggc.dat)\n");
//		m_log(precision, logBuffer);
		// écriture de i, x(i) et solgc(i) dans un fichier solggc.dat
//		error = writeDataInFile(x, solgc, matrixSize, precision);
//		if (error != 0) {
//			// error
//			res = error;
//		}
//		sprintf(logBuffer, "\tEcriture de gkgk2 dans un fichier (output/gkgk.dat)\n");
//		m_log(precision, logBuffer);
		// écriture de gkgk2 dans un fichier gkgk.dat (une seule ligne)
//		error = writeGkArrayInFile(gkgk2save, nbGradientIterations, precision);
//		if (error != 0) {
//			// error
//			res = error;
//		}
	}

	sprintf(logBuffer, "Gkgk2 : %F", mpfr_get_d(gkgk2, MPFR_RNDN));
	m_log(precision, logBuffer);
	sprintf(logBuffer, "\tLibérations des tableaux\n");
	m_log(precision, logBuffer);
//	freeArray(x, matrixSize); // has been freed earlier
	freeMatrix(matrixSize, matrixSize, a);
	freeArray(solgc, matrixSize);
	freeArray(gk, matrixSize);
	freeArray(dk, matrixSize);
	freeArray(adk, matrixSize);
	freeArray(dkTmp, matrixSize);
	sprintf(logBuffer, "\tLibérations des variables\n");
	m_log(precision, logBuffer);
	m_clear(gkGkTmp1);
	m_clear(adkDkTmp);
	m_clear(alphak);
	m_clear(gkgk2);
	m_clear(gkGkTmp2);
	m_clear(betak);

	// saving gkgk2
	createArray(&(gkgk2_global[precision - MPFR_PREC_MIN]), nbGradientIterations, precision);
	vectorCopy(gkgk2_global[precision - MPFR_PREC_MIN], gkgk2save, nbGradientIterations);

	freeArray(gkgk2save, nbGradientIterations);

	closeLogFromPrecision(precision);

//	printf("\nStochastic rounding has been called %ld times.\n", NB_STOCH_ROUND);
	return res;
}

void * customLorenzAttractorThreadWrapper(void * precision) {
	const size_t M_SIZE = getParamFromParamEnum(MATRIX_SIZE)->currentValue.s;
	const enum roundingModeEnum RME = getParamFromParamEnum(ROUNDING_MODE)->currentValue.rme;
	const long int NB_ITERATIONS = getParamFromParamEnum(NB_ITER)->currentValue.li;

	const double V_SIGMA = getParamFromParamEnum(SIGMA)->currentValue.d;
	const double V_RO = getParamFromParamEnum(RO)->currentValue.d;
	const double V_BETA = getParamFromParamEnum(BETA)->currentValue.d;

	long int *prec = precision;
	lorenzAttractor(*prec, NB_ITERATIONS, RME, V_SIGMA, V_RO, V_BETA);

	return NULL;
}

int isnan(mpfr_t number) {
	return mpfr_nan_p(number);
}

int lorenzAttractor(const mpfr_prec_t precision, const long int nbIterations,
		const enum roundingModeEnum rme, const double sigmaD, const double roD, const double betaD) {
	int err = EXIT_SUCCESS;
	/*
	 * FORTRAN CODE :
	 */
	// declarations
	mpfr_t x0, y0, z0;
	mpfr_t x1, y1, z1;
	mpfr_t xm1, ym1, zm1;
	mpfr_t xtt, ytt, ztt;
	mpfr_t xnu, tmpVal, tmpVal2, dt, one;
	mpfr_t sigma, ro, beta;
	mpfr_t alp;

	const int irkMax = 4;

	const size_t arraySize = nbIterations + 1;
	mpfr_t (*x1Array)[arraySize], (*y1Array)[arraySize], (*z1Array)[arraySize];

	// allocations
	mpfr_inits2(precision, x0, y0, z0, (mpfr_ptr) NULL);
	mpfr_inits2(precision, x1, y1, z1, (mpfr_ptr) NULL);
	mpfr_inits2(precision, xm1, ym1, zm1, (mpfr_ptr) NULL);
	mpfr_inits2(precision, xtt, ytt, ztt, (mpfr_ptr) NULL);
	mpfr_inits2(precision, tmpVal, tmpVal2, xnu, dt, one, (mpfr_ptr) NULL);
	mpfr_inits2(precision, sigma, ro, beta, (mpfr_ptr) NULL);
	mpfr_inits2(precision, alp, (mpfr_ptr) NULL);

	_createArray(arraySize, &x1Array, precision);
	_createArray(arraySize, &y1Array, precision);
	_createArray(arraySize, &z1Array, precision);

	// initializations
	mpfr_set_str(x0, "-10", 10, MPFR_RNDN);
	mpfr_set_str(y0, "20", 10, MPFR_RNDN);
	mpfr_set_str(z0, "-5", 10, MPFR_RNDN);
	mpfr_set(x1, x0, MPFR_RNDN);
	mpfr_set(y1, y0, MPFR_RNDN);
	mpfr_set(z1, z0, MPFR_RNDN);
	mpfr_set(xm1, x0, MPFR_RNDN);
	mpfr_set(ym1, y0, MPFR_RNDN);
	mpfr_set(zm1, z0, MPFR_RNDN);
	mpfr_set_str(xnu, "2e-4", 10, MPFR_RNDN);
	mpfr_set_str(dt, "1e-3", 10, MPFR_RNDN);
	mpfr_set_str(one, "1", 10, MPFR_RNDN);

	mpfr_set_d(sigma, sigmaD, MPFR_RNDN);
	mpfr_set_d(ro, roD, MPFR_RNDN);
	mpfr_set_d(beta, betaD, MPFR_RNDN);

	// writing x1, y1 and z1 to a file "lorentz.dat"
	assert(nbIterations > 0);
	mpfr_set((*x1Array)[0], x1, MPFR_RNDN);
	mpfr_set((*y1Array)[0], y1, MPFR_RNDN);
	mpfr_set((*z1Array)[0], z1, MPFR_RNDN);

	// COMPUTATIONS
	// 10000 iterations (minimum)
	for (long int kt = 1L ; kt <= nbIterations ; ++kt) {
		for (int irk = 1L ; irk <= irkMax ; ++irk) {
			// alp = 1/(irkmax+1-irk)
			mpfr_add_si(tmpVal, one, irkMax, MPFR_RNDN);
			mpfr_sub_si(tmpVal, tmpVal, irk, MPFR_RNDN);
			m_div(alp, one, tmpVal, rme);

			// tmpVal = dt**2*xnu
			mpfr_pow_si(tmpVal, dt, 2L, MPFR_RNDN);

			//      xtt=(x1-2*x0+xm1)/dt**2*xnu
			m_mul_si(tmpVal2, x0, 2L, rme);
			m_sub(tmpVal2, x1, tmpVal2, rme);
			m_add(tmpVal2, tmpVal2, xm1, rme);
			m_div(xtt, tmpVal2, tmpVal, rme);
			m_mul(xtt, xtt, xnu, rme);
			//      ytt=(y1-2*y0+ym1)/dt**2*xnu
			m_mul_si(tmpVal2, y0, 2L, rme);
			m_sub(tmpVal2, y1, tmpVal2, rme);
			m_add(tmpVal2, tmpVal2, ym1, rme);
			m_div(ytt, tmpVal2, tmpVal, rme);
			m_mul(ytt, ytt, xnu, rme);
			//      ztt=(z1-2*z0+zm1)/dt**2*xnu
			m_mul_si(tmpVal2, z0, 2L, rme);
			m_sub(tmpVal2, z1, tmpVal2, rme);
			m_add(tmpVal2, tmpVal2, zm1, rme);
			m_div(ztt, tmpVal2, tmpVal, rme);
			m_mul(ztt, ztt, xnu, rme);

			//      x1=x0+dt*alp*(sigma*(y1-x1)+xtt)
			m_sub(tmpVal, y1, x1, rme);
			m_mul(tmpVal, sigma, tmpVal, rme);
			m_add(tmpVal, tmpVal, xtt, rme);
			m_mul(tmpVal, tmpVal, alp, rme);
			m_mul(tmpVal, tmpVal, dt, rme);
			m_add(x1, x0, tmpVal, rme);

			//      y1=y0+dt*alp*(ro*x1-y1-x1*z1+ytt)
			m_mul(tmpVal, ro, x1, rme);
			m_sub(tmpVal, tmpVal, y1, rme);
			m_mul(tmpVal2, x1, z1, rme);
			m_sub(tmpVal, tmpVal, tmpVal2, rme);
			m_add(tmpVal, tmpVal, ytt, rme);
			m_mul(tmpVal, alp, tmpVal, rme);
			m_mul(tmpVal, dt, tmpVal, rme);
			m_add(y1, y0, tmpVal, rme);

			//      z1=z0+dt*alp*(x1*y1-beta*z1+ztt)
			m_mul(tmpVal, x1, y1, rme);
			m_mul(tmpVal2, beta, z1, rme);
			m_sub(tmpVal, tmpVal, tmpVal2, rme);
			m_add(tmpVal, tmpVal, ztt, rme);
			m_mul(tmpVal, alp, tmpVal, rme);
			m_mul(tmpVal, dt, tmpVal, rme);
			m_add(z1, z0, tmpVal, rme);
		}
		mpfr_set(xm1, x0, MPFR_RNDN);
		mpfr_set(ym1, y0, MPFR_RNDN);
		mpfr_set(zm1, z0, MPFR_RNDN);
		mpfr_set(x0, x1, MPFR_RNDN);
		mpfr_set(y0, y1, MPFR_RNDN);
		mpfr_set(z0, z1, MPFR_RNDN);
		// write x1,y1 and z1
		mpfr_set((*x1Array)[kt], x1, MPFR_RNDN);
		mpfr_set((*y1Array)[kt], y1, MPFR_RNDN);
		mpfr_set((*z1Array)[kt], z1, MPFR_RNDN);
	}

	for (size_t i = 0 ; i < arraySize ; ++i) {
//		mpfr_set((*xyz_global)[precision][0][i], (*x1Array)[i], MPFR_RNDN);
//		mpfr_set((*xyz_global)[precision][1][i], (*y1Array)[i], MPFR_RNDN);
//		mpfr_set((*xyz_global)[precision][2][i], (*z1Array)[i], MPFR_RNDN);
//		mpfr_printf("%30.8RF\t%30.8RF\t%30.8RF\n", (*x1Array)[i], (*y1Array)[i], (*z1Array)[i]);
	}

	const mpfr_t * xyzLorenz[3] = { *x1Array, *y1Array, *z1Array };
	writeLorenzMatrixInFile(arraySize, xyzLorenz, precision);

	mpfr_clears(x0, y0, z0, (mpfr_ptr) NULL);
	mpfr_clears(x1, y1, z1, (mpfr_ptr) NULL);
	mpfr_clears(xm1, ym1, zm1, (mpfr_ptr) NULL);
	mpfr_clears(xtt, ytt, ztt, (mpfr_ptr) NULL);
	mpfr_clears(tmpVal, tmpVal2, xnu, dt, one, (mpfr_ptr) NULL);
	mpfr_clears(sigma, ro, beta, (mpfr_ptr) NULL);
	mpfr_clears(alp, (mpfr_ptr) NULL);

	freeArray(*x1Array, arraySize);
	freeArray(*y1Array, arraySize);
	freeArray(*z1Array, arraySize);

	return 0;
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

	const char * labels[3] = { "i", "x", "solgc" };
	const int n_array = (sizeof(labels) / sizeof(const char *));

	// i 
	mpfr_t * iArray;
	createArray(&iArray, size, precision);
	fillArrayLinearly(iArray, size);

	const mpfr_t * data[3] = { iArray, x, solgc };

	sprintf(fileName, "%s%ld%s", DATA_FILE_NAME, precision, DATA_EXTENSION);

//	if (precision == MPFR_PREC_MIN) {
	eraseFile(fileName);
//	}

	res = writeData(size, fileName, n_array, labels, data);

	freeArray(iArray, size);

	return res;
}

int writeLorenzMatrixInFile(const size_t n, const mpfr_t * matrix[3], const mpfr_prec_t precision) {
	int err = EXIT_SUCCESS;

	const char * labels[3] = { "x", "y", "z" };

	char * fileName = buildLorenzFileName(precision);

//	printf("\twriting matrix in file `%s` ...\n", fileName);

	eraseFile(fileName);
	writeData(n, fileName, 3, labels, matrix);

	cfree(fileName);

	return err;
}

char * buildLorenzFileName(const mpfr_prec_t precision) {

	char tmp[4];
	sprintf(tmp, "%ld", precision);

	char * prefix = buildPrefixFromParams(LORENZ);

	char * fileName = malloc(
			sizeof(char)
					* (strlen(LORENZ_PREFIX) + strlen("_prec=") + strlen(tmp)
							+ strlen(prefix) + strlen(DATA_EXTENSION)+1));

	strcpy(fileName, LORENZ_PREFIX);
	strcat(fileName, "_prec=");
	strcat(fileName, tmp);
	strcat(fileName, prefix);
	strcat(fileName, DATA_EXTENSION);

	cfree(prefix);

	return fileName;
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
int writeGkgk2_global(const size_t nbPrecisionsTreated, const size_t nbIterations,
		const enum modelEnum me) {
	int res = 0;

	char fileName[100];
	char * prefix = buildPrefixFromParams(me);
	char * suffix = buildSuffix();

	sprintf(fileName, "%s%s%s", GK_FILE_NAME, prefix, suffix);

	eraseFile(fileName);

	for (size_t i = 0 ; i <= nbPrecisionsTreated ; ++i) {
		writeArray(gkgk2_global[i], nbIterations, fileName, "Gkgk2");
	}

	//res = writeGkGlobalArrayInFile(nbPrecisionsTreated,nbIterations,gkgk2_global,fileName);

	cfree(prefix);
	cfree(suffix);

	return res;
}

/**
 * @brief      Print a final error message
 */
void printFinalErrorStatement() {
	fprintf(stderr, "\nUne erreur est survenue.\nFin du programme...\n");
}

/* DEPRECATED */

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

int changeLorenzFileName(const mpfr_prec_t precision, const long int it) {
	int err = 0;
	char ext[] = ".dat";
	char toAdd[7];
	sprintf(toAdd, "(%ld)", it);
	char * oldName = buildLorenzFileName(precision);
	size_t namelen = strlen(oldName);
	char * newName = malloc(sizeof(char) * (strlen(toAdd) + namelen + strlen(DATA_EXTENSION)+1));

	strncpy(newName, oldName, namelen - strlen(ext));
	newName[namelen-strlen(ext)]=0;
	strcat(newName, toAdd);
	strcat(newName, DATA_EXTENSION);
//	strcat(newName, "\0");

	err = rename(oldName, newName);
	char * command = malloc(
			(strlen("mv \"%s\" \"stochFiles/%s\"") + strlen(newName) * 2) * sizeof(char));
	sprintf(command, "mv \"%s\" \"stochFiles/%s\"", newName, newName);
	system(command);

//	cfree(toAdd);
	cfree(command);
	cfree(oldName);
	cfree(newName);

	return err;
}

