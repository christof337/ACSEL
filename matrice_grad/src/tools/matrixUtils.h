#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

double ** createMatrix(const int m, const int n);

void freeMatrix(double ** matrix, const int m, const int n);

double ** matrixMult(double ** array1, const int m1, const int n1, 
	double ** array2, const int m2, const int n2);

double * matrixMultVector(double ** matrix, const int m, const int n, 
	double * vector, const int sizeVector);

double ** fillMatrixRandomly(double ** array, const int m, const int n);

double ** fillMatrixExponentially(double ** array, const int m, const int n);

void printMatrix(double ** matrix, const int m, const int n);

#endif /* MATRIX_UTILS_H */