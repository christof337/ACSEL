#include "arrayUtils.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Testé exhaustivement dans check_array_utils.c (lancer `make test` pour voir la sortie)
 */


/**
* Précondition : size <= size(array)
*/
void fillArrayWithZeros(double array[], int size) {
	fillArrayWith(array, size, 0);
}

/**
* Précondition : size <= size(array)
*/
void fillArrayWith(double array[], int size, double fillWith) {   
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = fillWith ;
	}
}

void fillArrayLinearly(double array[], int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = i ;
	}
}

double * vectorMult(const int size, double array1[size], double array2[size]) {
	static double * multipliedMatrix;

	multipliedMatrix = malloc(size * sizeof(double));

	for ( int i = 0 ; i < size ; i++ ) {
		multipliedMatrix[i] = array1[i] * array2[i];
	}

	return multipliedMatrix;
}

/**
* Précondition : size <= size(array)
*/
void printArray(double array[], int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		printf("[%d] : %f\n",i,array[i]);
	}
}
