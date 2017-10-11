#include "matrixUtils.h"

#include "arrayUtils.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * m : number of rows
 * n : number of columns
 */
double ** createMatrix(const int m, const int n) {
    double* values = calloc(n*m, sizeof(double));
    double** rows = malloc(m*sizeof(double*));

    if(values == NULL || rows == NULL) {
  		fprintf(stderr, "Error - unable to allocate required memory\n");
  	}

    for (int i=0; i<m; ++i) {
        rows[i] = values + i*n;
    }
    return rows;
}

/**
 * m : number of rows
 * n : number of columns
 */
void freeMatrix(double ** matrix, const int m, const int n) {
	for ( int i = 0 ; i < m ; ++i) {
		// free(matrix[i]); // QUICKFIX
	}
	free(matrix);
}

/** 
 * array1 : matrix of dimensions (m1, n1)
 * array2 : matrix of dimensions (m2, n2)
 * n1 and m2 must be equal.
 * the output of this function must be freed after use.
 */
double ** matrixMult(double ** array1, const int m1, const int n1, 
	double ** array2, const int m2, const int n2) {

	double ** multipliedMatrix = createMatrix(m1, n2);
	double sum = 0;

	for (int i = 0; i < m1; ++i) {
		// lignes de la première matrice
      	for (int j = 0; j < n2; ++j) {
	      	// colonnes de la seconde matrice
	        for (int k = 0; k < m2; ++k) {
	        	// lignes de la seconde matrice m2 // colonnes de la première n1
	         	sum = sum + array1[i][k]*array2[k][j];
	        }
	        multipliedMatrix[i][j] = sum;
	        sum = 0;
      	}
    }

    return multipliedMatrix;
}

/**
 * matrix : matrix of dimensions (m,n)
 * n and sizeVector must be equal.
 * array returned by this function must be freed afterwards.
 * the output of this function must be freed afterwards.
 */
double * matrixMultVector(double ** matrix, const int m, const int n, 
	double * vector, const int sizeVector) {

	double * result = createArray(m);
	double ** resultTmp;

	// on change le vecteur en matrice dont le nombre de ligne serait sizeVector et le nombre de colonne serait 1 (ce afin d'utiliser la multiplication matricielle)
	double ** matrixTemp = createMatrix(sizeVector, 1);
	// on recopie la première colonne ... 
	for ( int i = 0 ; i < sizeVector ; ++i ) {
		matrixTemp[i][0] = vector[i];
	}

	// multiplication matrice / vecteur
	resultTmp = matrixMult(matrix, m, n,
		matrixTemp, sizeVector, 1);

	for ( int i = 0 ; i < m ; ++i ) {
		result[i] = resultTmp[i][0];
	}

	freeMatrix(resultTmp, m, 1);

	return result;
}

/* function to generate and return a matrix of (m*n) random numbers */
double ** fillMatrixRandomly(double ** array, const int m, const int n) {
   /* set the seed */
   srand( (unsigned)time( NULL ) );
  
   for ( int i = 0; i < m ; ++i) {
   		for ( int j = 0 ; j < n ; ++j) {
      		array[i][j] = rand();
      	}
   }
   return array;
}

/**
 * m : nombre de lignes de la matrice
 * n : nombre de colonnes de la matrice
 */
double ** fillMatrixExponentially(double ** array, const int m, const int n) {
	for ( int i = 0 ; i < m ; ++i ) {
		for ( int j = 0 ; j < n ; ++j ) {
			array[i][j] = exp(-0.05*pow((i-j),2.0));
		}
	}
	return array;
}

/**
 * m : nombre de lignes de la matrice
 * n : nombre de colonnes de la matrice
 */
void printMatrix(double ** array, const int m, const int n) {
	printf("\t");
	for (int j = 0; j < n ; ++j) {
		printf("j=%d\t",j);
	}
	for (int i = 0; i < m; ++i) {
		printf("i=%d\t",i);
		for (int j = 0; j < n; ++j) {
			printf("%f\t", array[i][j]);
    	}
		printf("\n");
  	}
}