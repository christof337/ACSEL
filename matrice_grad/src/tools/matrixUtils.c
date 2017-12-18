#include "matrixUtils.h"

#include "arrayUtils.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "customMath.h"

#define RM m_getRoundingMode()

/**
 * Create a matrix and allocate memory for it. DO NOT initialize the space
 * needed for mpfr
 *
 * @param      a          trust me about the ***. Pointer to a two dimensionnal array of mpfr_t (**)
 * @param[in]  m          number of rows
 * @param[in]  n          number of columns
 * @param[in]  precision  The precision
 * @param      matrix  The matrix
 */
void createMatrix(mpfr_t *** a, const int m, const int n, mpfr_prec_t precision) {
	mpfr_t tmp;
	m_init2(tmp, precision);
	mpfr_t * values = calloc(n * m, sizeof(tmp));
	(*a) = malloc(m * sizeof(mpfr_t*));

	if (values == NULL || *a == NULL) {
		fprintf(stderr, "Error - unable to allocate required memory\n");
	}

	for (int i = 0 ; i < m ; ++i) {
		(*a)[i] = values + i * n;
	}

	for (int i = 0 ; i < m ; ++i) {
		for (int j = 0 ; j < n ; ++j) {
			m_init2((*a)[i][j], precision);
		}
	}

	m_clear(tmp);
}

/**
 * Free the matrix `matrix`
 *
 * @param      matrix  The matrix to free
 * @param[in]  m       number of rows
 * @param[in]  n       number of columns
 */
void freeMatrix(mpfr_t ** matrix, const int m, const int n) {
	for (int i = 0 ; i < m ; ++i) {
		for (int j = 0 ; j < n ; ++j) {
			m_clear(matrix[i][j]);
		}
		// free(matrix[i]); // QUICKFIX
	}
	free(matrix);
}

/**
 * Multiply array1 and array2. n1 and m2 must be equal.
 *
 * @param      multipliedMatrix  The multiplied matrix. Must be of dimension
 *                               m1,n2
 * @param      array1            matrix of dimensions (m1, n1)
 * @param[in]  m1                First dimension of array1. Must be > 0
 * @param[in]  n1                Second dimension of array1. Must be > 0
 * @param      array2            matrix of dimensions (m2, n2)
 * @param[in]  m2                First dimension of array2
 * @param[in]  n2                Second dimension of array2
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int matrixMult(mpfr_t ** multipliedMatrix, mpfr_t ** array1, const int m1, const int n1,
		mpfr_t ** array2, const int m2, const int n2, const enum roundingModeEnum rme) {

	int res = 0;

	mpfr_prec_t prec = mpfr_get_prec(array1[0][0]);

	// mpfr_t ** multipliedMatrix = createMatrix(m1, n2);
	mpfr_t sum;
	m_init2(sum, prec);
	mpfr_set_d(sum, 0.0, RM);

	mpfr_t t;
	m_init2(t, prec);

	for (int i = 0 ; i < m1 ; ++i) {
		// lignes de la première matrice
		for (int j = 0 ; j < n2 ; ++j) {
			// colonnes de la seconde matrice
			for (int k = 0 ; k < m2 ; ++k) {
				// lignes de la seconde matrice m2 / colonnes de la première n1
				// sum = sum + array1[i][k]*array2[k][j];
				res += m_mul(t, array1[i][k], array2[k][j], rme);
				res += m_add(sum, sum, t, rme);
			}
			mpfr_set(multipliedMatrix[i][j], sum, RM);
			mpfr_set_d(sum, 0.0, RM); // sum = 0;
		}
	}

	return res;
}

/**
 * @brief      Multiply matrix and vector and set the product into result 
 * @pre        n and sizeVector must be equal.
 *
 * @param      result      The result
 * @param      matrix      matrix of dimensions (m,n)
 * @param[in]  m           number of rows of the matrix
 * @param[in]  n           number of columns of the matrix 
 * @param      vector      The vector to add to `matrix`
 * @param[in]  sizeVector  The size of the vector
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int matrixMultVector(mpfr_t * result, mpfr_t ** matrix, const int m, const int n, mpfr_t * vector,
		const int sizeVector, const enum roundingModeEnum rme) {

	int res = 0;
	mpfr_t ** resultTmp;

	mpfr_prec_t prec = mpfr_get_prec(matrix[0][0]); // FIXME

	createMatrix(&resultTmp, m, 1, prec);

	// on change le vecteur en matrice dont le nombre de ligne serait sizeVector
	// et le nombre de colonne serait 1 (ce afin d'utiliser la multiplication
	// matricielle)
	mpfr_t ** matrixTemp;
	createMatrix(&matrixTemp, sizeVector, 1, prec);

	// on recopie la première colonne ...
	for (int i = 0 ; i < sizeVector ; ++i) {
		mpfr_set(matrixTemp[i][0], vector[i], RM);
	}

	// multiplication matrice / vecteur
	res = matrixMult(resultTmp, matrix, m, n, matrixTemp, sizeVector, 1,rme);

	for (int i = 0 ; i < m ; ++i) {
		mpfr_set(result[i], resultTmp[i][0], RM);
	}

	freeMatrix(resultTmp, m, 1);

	return res;
}

/**
 * function to generate and return a matrix of (m*n) random numbers
 *
 * @param      array  The matrix to fill randomly
 * @param[in]  m      number of rows of the matrix
 * @param[in]  n      number of columns of the matrix
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int fillMatrixRandomly(mpfr_t ** array, const int m, const int n) {
	int res = 0;
	gmp_randstate_t randState;
	gmp_randinit_default(randState);
	for (int i = 0 ; i < m ; ++i) {
		for (int j = 0 ; j < n ; ++j) {
			res += mpfr_urandom(array[i][j], randState, RM);
		}
	}
	return res;
}

/**
 * Fill a matrix "exponentially"
 *
 * @param      array  The matrix to fill exponentially
 * @param[in]  m      number of rows of the matrix
 * @param[in]  n      number of columns of the matrix
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             value, < 0 if globally rounded downwards the exact value
 */
int fillMatrixExponentially(mpfr_t ** array, const int m, const int n, const enum roundingModeEnum rme) {
	int res = 0;
	mpfr_t s, t, u, exp; // intermediate temporary variables

	mpfr_prec_t prec = mpfr_get_prec(array[0][0]); // FIXME
	//mpfr_prec_t prec = 2; // FIXME

	mpfr_inits2(prec, s, t, u, exp, (mpfr_ptr) NULL);
	mpfr_set_d(exp, 2.0, RM);
	mpfr_set_d(t, -0.05, RM);

	for (long int i = 0 ; i < m ; ++i) {
		for (long int j = 0 ; j < n ; ++j) {
			// array[i][j] = exp(-0.05*pow((i-j),2.0))
			mpfr_prec_t prec = mpfr_get_prec(array[i][j]);
			mpfr_set_si(s, i - j, RM);
			m_pow(u, s, exp, rme);
			m_mul(u, u, t, rme);
			res += mpfr_exp(array[i][j], u, RM);
		}
	}
	mpfr_clears(s, t, u, exp, (mpfr_ptr) NULL);
	return res;
}

/**
 * @brief      Print the matrix on the standard output
 *
 * @param      array  The matrix to print
 * @param[in]  m      number of rows of the matrix
 * @param[in]  n      number of columns of the matrix
 */
void printMatrix(mpfr_t ** array, const int m, const int n) {
	printf("\t");
	for (int j = 0 ; j < n ; ++j) {
		mpfr_printf("j=%d%5s\t", j, "");
	}
	printf("\n");
	for (int i = 0 ; i < m ; ++i) {
		mpfr_printf("i=%d\t", i);
		for (int j = 0 ; j < n ; ++j) {
			mpfr_printf("%f\t", array[i][j]);
		}
		mpfr_printf("\n");
	}
}
