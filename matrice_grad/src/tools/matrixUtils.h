#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <mpfr.h>

#include "customMath.h"

void createMatrix(mpfr_t *** matrix, const int m, const int n, mpfr_prec_t precision);

void freeMatrix(mpfr_t ** matrix, const int m, const int n);

int matrixMult(mpfr_t ** res, mpfr_t ** array1, const int m1, const int n1, mpfr_t ** array2,
		const int m2, const int n2, const enum roundingModeEnum rme);

int matrixMultVector(mpfr_t * res, mpfr_t ** matrix, const int m, const int n, mpfr_t * vector,
		const int sizeVector, const enum roundingModeEnum rme);

int fillMatrixRandomly(mpfr_t ** array, const int m, const int n);

int fillMatrixExponentially(mpfr_t ** array, const int m, const int n, const enum roundingModeEnum rme);

void printMatrix(mpfr_t ** matrix, const int m, const int n);

#endif /* MATRIX_UTILS_H */
