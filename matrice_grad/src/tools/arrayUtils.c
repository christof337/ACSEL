#include "arrayUtils.h"

#include <stdio.h>
#include <stdlib.h>

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
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = fillWith ;
	}
	return array;
}

double * fillArrayLinearly(double * array, const int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = i ;
	}
	return array;
}

/**
 * size1 and size2 must be equals.
 */
double * vectorMult(double * array1, const int size1, double * array2, const int size2) {
	double * multipliedVector = createArray(size1);

	for ( int i = 0 ; i < size1 ; i++ ) {
		multipliedVector[i] = array1[i] * array2[i];
	}

	return multipliedVector;
}

/**
* Précondition : size <= size(array)
*/
void printArray(double * array, const int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		printf("[%d] : %f\n",i,array[i]);
	}
}
