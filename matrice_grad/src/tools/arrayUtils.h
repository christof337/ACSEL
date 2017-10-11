#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

double * createArray(const int n);

double * fillArrayWithZeros(double * array, const int size) ;

double * fillArrayWith(double * array, const int size, double fillWith);

double * fillArrayLinearly(double * array, const int size);

double * vectorMult(double * array1, const int size1, double * array2, const int size2);

void printArray(double * array, const int size);

#endif /* ARRAY_UTILS_H */