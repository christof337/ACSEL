#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <mpfr.h>

#include "customMath.h"

void createArray(mpfr_t ** result, const int n, mpfr_prec_t precision);

int fillArrayWithZeros(mpfr_t * array, const int size);

int fillArrayWith(mpfr_t * array, const int size, mpfr_t fillWith);

int fillArrayLinearly(mpfr_t * array, const int size);

int vectorMult(mpfr_t * res, mpfr_t * array1, const int size1, mpfr_t * array2, const int size2, const enum roundingModeEnum rme);

int vectorPlusVector(mpfr_t * res, mpfr_t * vector1, const int size1, mpfr_t * vector2,
		const int size2, const enum roundingModeEnum rme);

int vectorMinusVector(mpfr_t * res, mpfr_t * vector1, const int size1, mpfr_t * vector2,
		const int size2, const enum roundingModeEnum rme);

int vectorCopy(mpfr_t * res, mpfr_t * vector, const int size);

int innerDotProduct(mpfr_t res, mpfr_t * vector, const int size, const enum roundingModeEnum rme);

int dotProduct(mpfr_t res, mpfr_t * vector1, const int size1, mpfr_t * vector2, const int size2, const enum roundingModeEnum rme);

int vectorMultValue(mpfr_t * res, mpfr_t * vector, const int size, mpfr_t value, const enum roundingModeEnum rme);

int sumSquare(mpfr_t res, mpfr_t * vector, const int size, const enum roundingModeEnum rme);

void printArray(mpfr_t * array, const int size);

void freeArray(mpfr_t * array, const int size);

#endif /* ARRAY_UTILS_H */
