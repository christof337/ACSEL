#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <mpfr.h>

#include "customMath.h"

void createArray(mpfr_t ** result, const size_t n, mpfr_prec_t precision);

int fillArrayWithZeros(mpfr_t * array, const size_t size);

int fillArrayWith(mpfr_t * array, const size_t size, mpfr_t fillWith);

int fillArrayLinearly(mpfr_t * array, const size_t size);

int vectorMult(mpfr_t * result, const mpfr_t * array1, const size_t size1, const mpfr_t * array2,
		const size_t size2, const enum roundingModeEnum rme);

int vectorPlusVector(mpfr_t * res, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme);

int vectorMinusVector(mpfr_t * res, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme);

int vectorCopy(mpfr_t * res, mpfr_t * vector, const size_t size);

int innerDotProduct(mpfr_t res, mpfr_t * vector, const size_t size, const enum roundingModeEnum rme);

int dotProduct(mpfr_t res, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme);

int vectorMultValue(mpfr_t * res, mpfr_t * vector, const size_t size, mpfr_t value,
		const enum roundingModeEnum rme);

int sumSquare(mpfr_t res, mpfr_t * vector, const size_t size, const enum roundingModeEnum rme);

void printArray(mpfr_t * array, const size_t size);

void freeArray(mpfr_t * array, const size_t size);

#endif /* ARRAY_UTILS_H */
