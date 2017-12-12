#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <mpfr.h>

void createMatrix(mpfr_t *** matrix, const int m, const int n, mpfr_prec_t precision);

void freeMatrix(mpfr_t ** matrix, const int m, const int n);

int matrixMult(mpfr_t ** res, mpfr_t ** array1, const int m1, const int n1, mpfr_t ** array2,
		const int m2, const int n2);

int matrixMultVector(mpfr_t * res, mpfr_t ** matrix, const int m, const int n, mpfr_t * vector,
		const int sizeVector);

int fillMatrixRandomly(mpfr_t ** array, const int m, const int n);

int fillMatrixExponentially(mpfr_t ** array, const int m, const int n);

void printMatrix(mpfr_t ** matrix, const int m, const int n);

#endif /* MATRIX_UTILS_H */
