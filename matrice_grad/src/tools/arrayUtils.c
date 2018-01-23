#include <stdio.h>
#include <mpfr.h>

#include "arrayUtils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "customMath.h"

#define RM mpfr_get_default_rounding_mode()

/**
 * @file arrayUtils.c
 * @author     Christophe Pont
 * @date       9 Oct 2017
 * @brief      File containing various utils for manipulating and adding arrays.
 *
 *             Utilise les types de mpfr. Testé exhaustivement dans
 *             check_array_utils.c (lancer `make test` pour voir la sortie).
 *
 * @see        http://www.mpfr.org/mpfr-current/mpfr.html
 */

/**
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param aptr
 */
void arr_alloc(const size_t x, mpfr_t (**aptr)[x]) {
	*aptr = malloc(sizeof(mpfr_t[x])); // allocate a true array
	assert(*aptr != NULL);
}

void arr_fill(const size_t x, mpfr_t array[x], mpfr_prec_t precision) {
	for (size_t i = 0 ; i < x ; i++) {
		m_init2(array[i], precision);
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
void _createArray(const size_t n, mpfr_t (**a)[n], mpfr_prec_t precision) {
	arr_alloc(n, a);
	arr_fill(n, **a, precision);
}

/**
 * @brief      Initialize an array with the given precision.
 * @deprecated
 * @param      result     The resulting array
 * @param[in]  n          size of the array to create
 * @param[in]  precision  The precision
 */
void createArray(mpfr_t ** result, const size_t n, mpfr_prec_t precision) {
	mpfr_t tmp;
	m_init2(tmp, precision);
	(*result) = malloc(n * sizeof(tmp));
	if ((*result) == NULL) {
		fprintf(stderr, "Error - unable to allocate required memory\n");
	} else {
		for (size_t i = 0 ; i < n ; ++i) {
			m_init2((*result)[i], precision);
		}
	}
	m_clear(tmp);
}

/**
 * @brief      Fill an array with zeros.
 * @pre        size <= size(array)
 *
 * @param      array  The array to fill. Must be of size `size`, and initialized
 * @param[in]  size   The size of `array`
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int fillArrayWithZeros(mpfr_t * array, const size_t size) {
	int err = 0;
	mpfr_t zero;
	m_init2(zero, mpfr_get_prec(array[0]));

	mpfr_set_d(zero, 0.0, RM);

	err = fillArrayWith(array, size, zero);

	m_clear(zero);

	return err;
}

/**
 * @brief      Fill an array with the given value
 * @pre        size <= size(array)
 *
 * @param      array     The array to fill. Must be of size `size`, and
 *                       initialized
 * @param[in]  size      The size of `array`
 * @param[in]  fillWith  The value to fill with
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int fillArrayWith(mpfr_t * array, const size_t size, mpfr_t fillWith) {
	int err = 0;
	for (size_t i = 0 ; i < size ; ++i) {
		err += mpfr_set(array[i], fillWith, RM);
	}
	return err;
}

/**
 * @brief      Fill an array linearly (1,2,3...size+1)
 *
 * @param      array  The array to fill
 * @param[in]  size   The size of the array
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int fillArrayLinearly(mpfr_t * array, const size_t size) {
	int err = 0;
	for (long int i = 0 ; i < size ; ++i) {
		err += mpfr_set_si(array[i], i + 1, RM);
	}
	return err;
}

/**
 * @brief 	   Vector multiplication. 
 * @pre        size1 and size2 must be equal.
 *
 * @param      result  The resulting vector. Must be of size `size`, and
 *                     initialized
 * @param      array1  The array 1
 * @param[in]  size1   The size 1
 * @param      array2  The array 2
 * @param[in]  size2   The size 2
 * @param      vector1  The vector 1
 * @param      vector2  The vector 2
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int vectorMult(mpfr_t * result, const mpfr_t * array1, const size_t size1, const mpfr_t * array2,
		const size_t size2, const enum roundingModeEnum rme) {
	int err = 0;
	for (size_t i = 0 ; i < size1 ; ++i) {
		err += m_mul(result[i], array1[i], array2[i], rme);
	}
	return err;
}

/**
 * @brief 	   Vector addition. 
 * @pre        size1 and size2 must be equal.
 *
 * @param      result   The resulting vector. Must be of size `size`, and
 *                      initialized
 * @param      vector1  The vector 1
 * @param[in]  size1    The size 1
 * @param      vector2  The vector 2
 * @param[in]  size2    The size 2
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int vectorPlusVector(mpfr_t * result, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme) {
	int err = 0;
	for (size_t i = 0 ; i < size1 ; ++i) {
		err += m_add(result[i], vector1[i], vector2[i], rme);
	}
	return err;
}

/**
 * @brief 	   Vector substraction. 
 * @pre        size1 and size2 must be equal.
 *
 * @param      result   The resulting vector. Must be of size `size`, and
 *                      initialized
 * @param      vector1  The vector 1
 * @param[in]  size1    The size 1
 * @param      vector2  The vector 2
 * @param[in]  size2    The size 2
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int vectorMinusVector(mpfr_t * result, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme) {
	int err = 0;
	for (size_t i = 0 ; i < size1 ; ++i) {
		err += m_sub(result[i], vector1[i], vector2[i], rme);
	}
	return err;
}

/**
 * @brief 	   Copy vector into result
 *
 * @param      result  The result. must be of size `size`, and initialized
 * @param      vector  The vector to copy
 * @param[in]  size    The size of `vector`. Must be > 0
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int vectorCopy(mpfr_t * result, mpfr_t * vector, const size_t size) {
	int err = 0;
	for (size_t i = 0 ; i < size ; ++i) {
		err += mpfr_set(result[i], vector[i], RM);
	}
	return err;
}

/**
 * @brief      Dot product of the vector with itself
 *
 * @param[in]  result  The result. Must have been initialized with the desired precision.
 * @param      vector  The vector
 * @param[in]  size    The size of the vector
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int innerDotProduct(mpfr_t result, mpfr_t * vector, const size_t size,
		const enum roundingModeEnum rme) {
	return dotProduct(result, vector, size, vector, size, rme);
}

/**
 * @brief      Dot product of two vectors
 * @pre        size1 and size2 must be equals.
 *
 * @param[in]  product  The product. Must have been initialized with the desired precision.
 * @param      vector1  The vector 1
 * @param[in]  size1    The size of `vector1`.
 * @param      vector2  The vector 2
 * @param[in]  size2    The size of `vector2`. 
 * @param[in]  result  The result
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int dotProduct(mpfr_t product, mpfr_t * vector1, const size_t size1, mpfr_t * vector2,
		const size_t size2, const enum roundingModeEnum rme) {
	int err = 0;
	mpfr_prec_t prec = mpfr_get_prec(product);
	mpfr_t t;

	m_init2(t, prec);

	mpfr_set_d(product, 0.0, RM); // product = 0;

	for (size_t i = 0 ; i < size1 ; ++i) {
		//product += vector1[i]*vector2[i];
		err += m_mul(t, vector1[i], vector2[i], rme);
		err += m_add(product, product, t, rme);
	}

	m_clear(t);

	return err;
}

/**
 * Multiply all of the elements of a vector by a value and put it in result
 *
 * @param  	   result  The resulting vector. Must be of size `size`
 * @param      vector  The vector to multiply
 * @param[in]  size    The size of `vector`
 * @param[in]  value   The value
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int vectorMultValue(mpfr_t * result, mpfr_t * vector, const size_t size, mpfr_t value,
		const enum roundingModeEnum rme) {
	int err = 0;

	for (size_t i = 0 ; i < size ; ++i) {
		// result[i] = vector[i] * value;
		err += m_mul(result[i], vector[i], value, rme);
	}

	return err;
}

/**
 * @brief      Add the square of all the elements of the vector and put the result in `result`
 *
 * @param[in]  result  The result. Must have been initialized with the desired precision.
 * @param      vector  The vector
 * @param[in]  size    The size. 
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int sumSquare(mpfr_t result, mpfr_t * vector, const size_t size, const enum roundingModeEnum rme) {
	int err = 0;
	mpfr_prec_t prec = mpfr_get_prec(result);
	mpfr_t t, exp;

	m_init2(t, prec);
	m_init2(exp, prec);

	mpfr_set_d(exp, 2.0, RM);

	mpfr_set_d(result, 0.0, RM); // result = 0

	for (size_t i = 0 ; i < size ; ++i) {
		// result += pow(vector[i],2);
		err += m_pow(t, vector[i], exp, rme);
		err += m_add(result, result, t, rme);
	}

	m_clear(t);
	m_clear(exp);

	return err;
}

/**
 * @brief      Print the array `array` up to the `size`th element
 * @pre        size <= size(array)
 *
 * @param      array  The array to print
 * @param[in]  size   The number of elements to print
 */
void printArray(mpfr_t * array, const size_t size) {
	for (size_t i = 0 ; i < size ; ++i) {
		printf("[%zu] : ", i);
		mpfr_printf("%G \n", array[i]);
	}
}

/**
 * @brief      Free the array `array`
 *
 * @param      array  The array to free
 * @param[in]  size   The size of the array
 */
void freeArray(mpfr_t * array, const size_t size) {
	for (size_t i = 0 ; i < size ; ++i) {
		m_clear(array[i]);
	}
	cfree(array);
}

size_t getMaxIndex(const size_t size, const mpfr_t array[size]) {
	size_t indexMax;
	mpfr_t max;
	assert(size > 0 /* Impossible to get max index from empty array */);
	indexMax = size - 1;
	m_init2(max, mpfr_get_prec(array[indexMax]));
	mpfr_set(max, array[0], MPFR_RNDN);
	for (size_t i = 0 ; i < size ; ++i) {
		if ( mpfr_cmp(array[i],max) > 0) {
			mpfr_set(max, array[i], MPFR_RNDN);
			indexMax = i;
		}
	}
	m_clear(max);
	return indexMax;
}

size_t getMinIndex(const size_t size, const mpfr_t array[size]) {
	size_t indexMin;
	mpfr_t min;
	assert(size > 0 /* Impossible to get max index from empty array */);
	indexMin = size - 1;
	m_init2(min, mpfr_get_prec(array[indexMin]));
	mpfr_set(min, array[0], MPFR_RNDN);
	for (size_t i = 0 ; i < size ; ++i) {
		if ( mpfr_cmp(array[i],min) < 0) {
			mpfr_set(min, array[i], MPFR_RNDN);
			indexMin = i;
		}
	}
	m_clear(min);
	return indexMin;
}

int getAllMinIndexes(size_t ** indexArray, const size_t size, const mpfr_t array[size]) {
	size_t indexMin;
	indexMin = getMinIndex(size, array);
	mpfr_t minValue;
	m_init2(minValue, mpfr_get_prec(array[size - 1]));
	mpfr_set(minValue, array[indexMin], MPFR_RNDN);
	// counting the number of concerned values
	long int nbMin = 0;
	for (size_t i = 0 ; i < size ; ++i) {
		if (mpfr_cmp(minValue,array[i]) == 0) {
			++nbMin;
		}
	}
	assert(nbMin!=0 /* impossible */);
	*indexArray = malloc(sizeof(size_t) * nbMin);
	size_t indexMinArray = 0;
	for (size_t i = 0 ; i < size ; ++i) {
		if (mpfr_cmp(minValue,array[i]) == 0) {
			(*indexArray)[indexMinArray] = i;
			++indexMinArray;
		}
	}
	m_clear(minValue);
	return nbMin;
}
