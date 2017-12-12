#include <stdio.h>
#include <mpfr.h>

#include "arrayUtils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "customMath.h"

#define RM m_getRoundingMode()

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
 * 
 */

/**
 * @brief      Initialize an array with the given precision.
 *
 * @param      result     The resulting array
 * @param[in]  n          size of the array to create
 * @param[in]  precision  The precision
 */
void createArray(mpfr_t ** result, const int n, mpfr_prec_t precision) {
	mpfr_t tmp;
	m_init2(tmp, precision);
	(*result) = malloc(n * sizeof(tmp));
	if ((*result) == NULL) {
		fprintf(stderr, "Error - unable to allocate required memory\n");
	} else {
		for (int i = 0 ; i < n ; ++i) {
			m_init2((*result)[i], precision);
		}
	}
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
int fillArrayWithZeros(mpfr_t * array, const int size) {
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
int fillArrayWith(mpfr_t * array, const int size, mpfr_t fillWith) {
	int err = 0;
	for (int i = 0 ; i < size ; ++i) {
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
int fillArrayLinearly(mpfr_t * array, const int size) {
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
int vectorMult(mpfr_t * result, mpfr_t * array1, const int size1, mpfr_t * array2, const int size2) {
	int err = 0;
	for (int i = 0 ; i < size1 ; ++i) {
		err += m_mul(result[i], array1[i], array2[i], RM);
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
int vectorPlusVector(mpfr_t * result, mpfr_t * vector1, const int size1, mpfr_t * vector2,
		const int size2) {
	int err = 0;
	for (int i = 0 ; i < size1 ; ++i) {
		err += mpfr_add(result[i], vector1[i], vector2[i], RM);
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
int vectorMinusVector(mpfr_t * result, mpfr_t * vector1, const int size1, mpfr_t * vector2,
		const int size2) {
	int err = 0;
	for (int i = 0 ; i < size1 ; ++i) {
		err += mpfr_sub(result[i], vector1[i], vector2[i], RM);
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
int vectorCopy(mpfr_t * result, mpfr_t * vector, const int size) {
	int err = 0;
	for (int i = 0 ; i < size ; ++i) {
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
int innerDotProduct(mpfr_t result, mpfr_t * vector, const int size) {
	return dotProduct(result, vector, size, vector, size);
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
int dotProduct(mpfr_t product, mpfr_t * vector1, const int size1, mpfr_t * vector2, const int size2) {
	int err = 0;
	mpfr_prec_t prec = mpfr_get_prec(product);
	mpfr_t t;

	m_init2(t, prec);

	mpfr_set_d(product, 0.0, RM); // product = 0;

	for (int i = 0 ; i < size1 ; ++i) {
		//product += vector1[i]*vector2[i];
		err += m_mul(t, vector1[i], vector2[i], RM);
		err += mpfr_add(product, product, t, RM);
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
int vectorMultValue(mpfr_t * result, mpfr_t * vector, const int size, mpfr_t value) {
	int err = 0;

	for (int i = 0 ; i < size ; ++i) {
		// result[i] = vector[i] * value;
		err += m_mul(result[i], vector[i], value, RM);
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
int sumSquare(mpfr_t result, mpfr_t * vector, const int size) {
	int err = 0;
	mpfr_prec_t prec = mpfr_get_prec(result);
	mpfr_t t, exp;

	mpfr_inits2(prec, t, exp, (mpfr_ptr) NULL);

	mpfr_set_d(exp, 2.0, RM);

	mpfr_set_d(result, 0.0, RM); // result = 0

	for (int i = 0 ; i < size ; ++i) {
		// result += pow(vector[i],2);
		err += mpfr_pow(t, vector[i], exp, RM);
		err += mpfr_add(result, result, t, RM);
	}

	mpfr_clears(t, exp, (mpfr_ptr) NULL);

	return err;
}

/**
 * @brief      Print the array `array` up to the `size`th element
 * @pre        size <= size(array)
 *
 * @param      array  The array to print
 * @param[in]  size   The number of elements to print
 */
void printArray(mpfr_t * array, const int size) {
	for (int i = 0 ; i < size ; ++i) {
		printf("[%d] : ", i);
		mpfr_printf("%G \n", array[i]);
	}
}

/**
 * @brief      Free the array `array`
 *
 * @param      array  The array to free
 * @param[in]  size   The size of the array
 */
void freeArray(mpfr_t * array, const int size) {
	for (int i = 0 ; i < size ; ++i) {
		m_clear(array[i]);
	}
	free(array);
}
