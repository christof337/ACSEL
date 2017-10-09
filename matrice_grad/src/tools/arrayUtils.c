#include "arrayUtils.h"

#include <stdio.h>

/**
 * Testé exhaustivement dans check_array_utils.c (lancer `make test` pour voir la sortie)
 */


/**
* Précondition : size <= size(array)
*/
void fillArrayWithZeros(int array[], int size) {
	fillArrayWith(array, size, 0);
}

/**
* Précondition : size <= size(array)
*/
void fillArrayWith(int array[], int size, int fillWith) {   
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = fillWith ;
	}
}

void fillArrayLinearly(int array[], int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		array[i] = i ;
	}
}

/**
* Précondition : size <= size(array)
*/
void printArray(int array[], int size) {
	for ( int i = 0 ; i < size ; i++ ) {
		printf("[%d] : %d\n",i,array[i]);
	}
}