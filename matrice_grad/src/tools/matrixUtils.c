#include "matrixUtils.h"

#include "arrayUtils.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mpfr.h>
#include <assert.h>

#include "customMath.h"
#include "utils.h"

#define RM mpfr_get_default_rounding_mode()

/**
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param aptr
 */
void arr_alloc_2d(const size_t x, const size_t y, mpfr_t (**aptr)[x][y]) {
	*aptr = malloc(sizeof(mpfr_t[x][y])); // allocate a true 2D array
	assert(*aptr != NULL);
}

void _arr_alloc_2d(const size_t x, const size_t y, mpfr_t ***aptr) {
	*aptr = malloc(sizeof(mpfr_t[x][y])); // allocate a true 2D array
	assert(*aptr != NULL);
}

void arr_fill_2d(const size_t x, const size_t y, mpfr_t array[x][y], mpfr_prec_t precision) {
	for (size_t i = 0 ; i < x ; i++) {
		for (size_t j = 0 ; j < y ; j++) {
			m_init2(array[i][j], precision);
		}
	}
}

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
//void createMatrix(mpfr_t *** a, const int m, const int n, mpfr_prec_t precision) {
void createMatrix(const size_t m, const size_t n, mpfr_t (**a)[m][n], mpfr_prec_t precision) {

	arr_alloc_2d(m, n, a);
	arr_fill_2d(m, n, **a, precision);
//	mpfr_t tmp;
//	m_init2(tmp, precision);
//	mpfr_t * values = calloc(n * m, sizeof(tmp));
//	(*a) = malloc(m * sizeof(mpfr_t*));
//
//	if (values == NULL || *a == NULL) {
//		fprintf(stderr, "Error - unable to allocate required memory\n");
//	}
//
//	for (int i = 0 ; i < m ; ++i) {
//		(*a)[i] = values + i * n;
//	}
//
//	for (int i = 0 ; i < m ; ++i) {
//		for (int j = 0 ; j < n ; ++j) {
//			m_init2((*a)[i][j], precision);
//		}
//	}
//
//	cfree(values);
//
//	m_clear(tmp);
}

/**
 * Free the matrix `matrix`
 *
 * @param      matrix  The matrix to free
 * @param[in]  m       number of rows
 * @param[in]  n       number of columns
 */
void freeMatrix(const size_t m, const size_t n, mpfr_t (*matrix)[m][n]) {
	for (int i = 0 ; i < m ; ++i) {
		for (int j = 0 ; j < n ; ++j) {
			m_clear((*matrix)[i][j]);
		}
		// cfree(matrix[i]); // QUICKFIX
	}
	cfree(matrix);
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
int matrixMult(const size_t m1, const size_t n1, mpfr_t array1[m1][n1], const size_t m2,
		const size_t n2, mpfr_t array2[m2][n2], mpfr_t multipliedMatrix[m1][n2],
		const enum roundingModeEnum rme) {

	int res = 0;

	mpfr_prec_t prec = mpfr_get_prec(array1[0][0]);

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

	m_clear(sum);
	m_clear(t);

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
int matrixMultVector(mpfr_t * result, const size_t m, const size_t n, mpfr_t matrix[m][n],
		mpfr_t * vector, const size_t sizeVector, const enum roundingModeEnum rme) {

	int res = 0;

	mpfr_prec_t prec = mpfr_get_prec(matrix[0][0]); // ok to use a given precision

	mpfr_t (*resultTmp)[m][1];
	createMatrix(m, 1, &resultTmp, prec);

	// on change le vecteur en matrice dont le nombre de ligne serait sizeVector
	// et le nombre de colonne serait 1 (ce afin d'utiliser la multiplication
	// matricielle)
	mpfr_t (*matrixTemp)[sizeVector][1];
	createMatrix(sizeVector, 1, &matrixTemp, prec);

	// on recopie la première colonne ...
	for (size_t i = 0 ; i < sizeVector ; ++i) {
		mpfr_set((*matrixTemp)[i][0], vector[i], RM);
	}

	// multiplication matrice / vecteur
	// 	res = matrixMult(resultTmp, matrix, m, n, matrixTemp, sizeVector, 1,rme);

	res = matrixMult(m,n,matrix,sizeVector,1,*matrixTemp,*resultTmp,rme);
//	res = matrixMult(m,n,resultTmp,sizeVector,1,matrixTemp,matrix,rme);
//	res = matrixMult(m, n, resultTmp, matrix, matrixTemp, sizeVector, 1, rme);

	for (int i = 0 ; i < m ; ++i) {
		mpfr_set(result[i], (*resultTmp)[i][0], RM);
	}

	freeMatrix(m, 1,resultTmp);
	freeMatrix(sizeVector, 1,matrixTemp);

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
int fillMatrixRandomly(const size_t m, const size_t n, mpfr_t array[m][n]) {
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
int fillMatrixExponentially(const size_t m, const size_t n, mpfr_t array[m][n],
		const enum roundingModeEnum rme) {
	int res = 0;
	mpfr_t s, t, u, exp; // intermediate temporary variables

	mpfr_prec_t prec = mpfr_get_prec(array[0][0]); // ok to use a given precision

	m_init2(s, prec);
	m_init2(t, prec);
	m_init2(u, prec);
	m_init2(exp, prec);

	mpfr_set_str(exp, "2.0", 10, RM);
	mpfr_set_str(t, "-0.05", 10, RM);

	for (long int i = 0 ; i < m ; ++i) {
		for (long int j = 0 ; j < n ; ++j) {
			// array[i][j] = exp(-0.05*pow((i-j),2.0))
//			mpfr_prec_t prec = mpfr_get_prec(array[i][j]);
			mpfr_set_si(s, (i - j), RM);
			m_pow(u, s, exp, rme);
			m_mul(u, u, t, rme);
			res += mpfr_exp(array[i][j], u, RM);
		}
	}

	m_clear(s);
	m_clear(t);
	m_clear(u);
	m_clear(exp);

	return res;
}

/**
 * @brief      Print the matrix on the standard output
 *
 * @param      array  The matrix to print
 * @param[in]  m      number of rows of the matrix
 * @param[in]  n      number of columns of the matrix
 */
void printMatrix(const size_t m, const size_t n, mpfr_t array[m][n]) {
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
