#include "matrixUtils.h"

#include <math.h>

/**
 * size1 taille de la première dimension de la matrice
 * size2 taille de la seconde dimension de la matrice
 */
void remplissageExponentielMatrice(int size1, int size2, double array[size1][size2]) {
	for ( int i = 0 ; i < size1 ; i++ ) {
		for ( int j = 0 ; j < size2 ; j++ ) {
			array[i][j] = exp(pow(-0.05*(i-j),2.0));
		}
	}
}
