#ifndef MATRICE_GRAD_H
#define MATRICE_GRAD_H

#include <mpfr.h>

#include "parameters.h"
#include "tools/customMath.h"

void * customConjuguateGradientDescentThreadWrapper(void * precision) ;

int conjuguateGradientDescent(const int precision, const size_t matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum/*,mpfr_t *metaGkgk2save[nbGradientIterations]*/);

int askTailleMatrice();

int customMatrixMultVector(mpfr_t * result, const size_t size,
		mpfr_t matrix[size][size], mpfr_t * vector, const enum roundingModeEnum rme);

int writeMatrixInFile(const size_t n, const size_t m, mpfr_t matrix[m][n], mpfr_prec_t precision);

int writeDataInFile(mpfr_t * x, mpfr_t * solgc, const size_t size, mpfr_prec_t precision);

int writeGkArrayInFile(mpfr_t * array, const size_t size, mpfr_prec_t precision);

void printFinalErrorStatement();

#endif /* MATRICE_GRAD_H */
