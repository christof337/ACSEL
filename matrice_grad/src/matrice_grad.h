#ifndef MATRICE_GRAD_H
#define MATRICE_GRAD_H

int askTailleMatrice();

double * customMatrixMultVector(double ** matrix, double * vector, const int size);

int writeMatrixInFile(double ** matrix, const int n, const int m);

int writeDataInFile(double * x, double * solgc, const int size);

int writeArrayInFile(double * array, const int size);

void printFinalStatement();

#endif /* MATRICE_GRAD_H */