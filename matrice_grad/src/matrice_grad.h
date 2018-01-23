#ifndef MATRICE_GRAD_H
#define MATRICE_GRAD_H

#include <mpfr.h>

#include "parameters.h"
#include "tools/customMath.h"
#include "tools/errorHandling.h"

// conjuguate gradient
mpfr_t ** gkgk2_global;

void initGkgk2_global(const size_t nbPrecisions, const size_t nbIterations);

void * customConjuguateGradientDescentThreadWrapper(void * precision);

void allocateArrays(const size_t matrixSize, const mpfr_prec_t precision,
		const int nbGradientIterations, mpfr_t** adk, mpfr_t** gkgk2save, mpfr_t** dkTmp);

void allocateMpfrVars(const mpfr_prec_t precision, mpfr_t gkGkTmp1, mpfr_t adkDkTmp, mpfr_t alphak,
		mpfr_t gkgk2, mpfr_t gkGkTmp2, mpfr_t betak);

enum ERRORS fillA(const enum matrixTypeEnum matrixType, const size_t m, const size_t n,
		mpfr_t a[m][n], const enum roundingModeEnum roundingModeEnum);

int conjuguateGradientDescent(const mpfr_prec_t precision, const size_t matrixSize,
		const int nbGradientIterations, const enum matrixTypeEnum matrixType,
		const enum roundingModeEnum roundingModeEnum/*,mpfr_t *metaGkgk2save[nbGradientIterations]*/);

void * customLorenzAttractorThreadWrapper(void * precision);

int lorenzAttractor(const mpfr_prec_t precision, const long int nbIterations,
		const enum roundingModeEnum rme, const double sigmaD, const double roD, const double betaD);

int customMatrixMultVector(mpfr_t * result, const size_t size, mpfr_t matrix[size][size],
		mpfr_t * vector, const enum roundingModeEnum rme);

int writeMatrixInFile(const size_t n, const size_t m, mpfr_t matrix[m][n], mpfr_prec_t precision);

int writeLorenzMatrixInFile(const size_t n, const mpfr_t * matrix[3], const mpfr_prec_t precision);

char * buildLorenzFileName();

int writeDataInFile(mpfr_t * x, mpfr_t * solgc, const size_t size, mpfr_prec_t precision);

//int writeGkGlobalArrayInFile(mpfr_t ** array, const size_t size, mpfr_prec_t precision);

int writeGkgk2_global(const size_t nbPrecisionsTreated, const size_t nbIterations,
		const enum modelEnum me);

void printFinalErrorStatement();

int changeLorenzFileName(const mpfr_prec_t precision, const long int it);

/* DEPRECATED */
int askTailleMatrice();

#endif /* MATRICE_GRAD_H */
