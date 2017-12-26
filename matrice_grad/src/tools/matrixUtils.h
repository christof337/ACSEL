#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <mpfr.h>

#include "customMath.h"

void arr_alloc(const size_t x, const size_t y, mpfr_t (**aptr)[x][y]);

void arr_fill(const size_t x, const size_t y, mpfr_t array[x][y], mpfr_prec_t precision);

void createMatrix(const size_t m, const size_t n, mpfr_t (**a)[m][n], mpfr_prec_t precision);

void freeMatrix(const size_t m, const size_t n, mpfr_t (*matrix)[m][n]);

int matrixMult(const size_t m1, const size_t n1, mpfr_t array1[m1][n1], const size_t m2,
		const size_t n2, mpfr_t array2[m2][n2], mpfr_t res[m1][n2], const enum roundingModeEnum rme);

int matrixMultVector(mpfr_t * res, const size_t m, const size_t n, mpfr_t matrix[m][n],
		mpfr_t * vector, const size_t sizeVector, const enum roundingModeEnum rme);

int fillMatrixRandomly(const size_t m, const size_t n, mpfr_t array[m][n]);

int fillMatrixExponentially(const size_t m, const size_t n, mpfr_t array[m][n],
		const enum roundingModeEnum rme);

void printMatrix(const size_t m, const size_t n, mpfr_t matrix[m][n]);

#endif /* MATRIX_UTILS_H */
