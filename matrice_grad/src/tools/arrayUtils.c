#include "arrayUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Testé exhaustivement dans check_array_utils.c (lancer `make test` pour voir la sortie)
 */

double * createArray(const int n) {
    double * values = malloc(n * sizeof(double));
    if(values == NULL) {
  		fprintf(stderr, "Error - unable to allocate required memory\n");
  	}
    return values;
}

/**
* Précondition : size <= size(array)
*/
double * fillArrayWithZeros(double * array, const int size) {
	return fillArrayWith(array, size, 0);
}

/**
* Précondition : size <= size(array)
*/
double * fillArrayWith(double * array, const int size, double fillWith) {   
	for ( int i = 0 ; i < size ; ++i ) {
		array[i] = fillWith ;
	}
	return array;
}

double * fillArrayLinearly(double * array, const int size) {
	for ( int i = 0 ; i < size ; ++i ) {
		array[i] = i+1 ;
	}
	return array;
}

/**
 * size1 and size2 must be equals.
 */
double * vectorMult(double * array1, const int size1, double * array2, const int size2) {
	double * multipliedVector = createArray(size1);

	for ( int i = 0 ; i < size1 ; ++i ) {
		multipliedVector[i] = array1[i] * array2[i];
	}

	return multipliedVector;
}

/**
 * size1 and size2 must be equal.
 * the output of this function must be freed afterwards.
 */
double * vectorPlusVector(double * vector1, const int size1, double * vector2, const int size2) {
	double * result = createArray(size1);
	for ( int i = 0 ; i < size1 ; ++i ) {
		result[i] = vector1[i] + vector2[i];
	}
	return result;
}

/**
 * size1 and size2 must be equal.
 * the output of this function must be freed afterwards.
 */
double * vectorMinusVector(double * vector1, const int size1, double * vector2, const int size2) {
	double * result = createArray(size1);
	for ( int i = 0 ; i < size1 ; ++i ) {
		result[i] = vector1[i] - vector2[i];
	}
	return result;
}

/**
 * the return value of this function must be freed afterwards.
 */ 
double * vectorCopy(double * vector, const int size) {
	double * copy = createArray(size);
	memcpy(copy,vector,size*sizeof(double));
	return copy;
}

double innerDotProduct(double * vector, const int size) {
	return dotProduct(vector,size,vector,size);
}

/**
 * size1 and size2 must be equals.
 */
double dotProduct(double * vector1, const int size1, double * vector2, const int size2) {
	double product = 0;
	for ( int i = 0 ; i < size1 ; ++i ) {
		product += vector1[i]*vector2[i];
	}
	return product;
}

/**
 * the output of this function must be freed afterwards.
 */
double * vectorMultDouble(double * vector, const int size, double value) {
	double * result = createArray(size);
	for ( int i = 0 ; i < size ; ++i ) {
		result[i] = vector[i] * value;
	}
	return result;
}

double sumSquare(double * vector, const int size) {
	double res = 0;
	for ( int i = 0 ; i < size ; ++i ) {
        res += pow(vector[i],2);
    }
    return res;
}

/**
* Précondition : size <= size(array)
*/
void printArray(double * array, const int size) {
	for ( int i = 0 ; i < size ; ++i ) {
		printf("[%d] : %G \n",i,array[i]);
	}
}
