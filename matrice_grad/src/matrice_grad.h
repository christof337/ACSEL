#ifndef MATRICE_GRAD_H
#define MATRICE_GRAD_H

#include <mpfr.h>

#include "parameters.h"
#include "tools/customMath.h"

int conjuguateGradientDescent(const int precision, const int matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum);

int askTailleMatrice();

int customMatrixMultVector(mpfr_t * result, mpfr_t ** matrix, mpfr_t * vector, const int size, const enum roundingModeEnum rme);

int writeMatrixInFile(mpfr_t ** matrix, const int n, const int m, mpfr_prec_t precision);

int writeDataInFile(mpfr_t * x, mpfr_t * solgc, const int size, mpfr_prec_t precision);

int writeGkArrayInFile(mpfr_t * array, const int size, mpfr_prec_t precision);

void printFinalErrorStatement();

#endif /* MATRICE_GRAD_H */
