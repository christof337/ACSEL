#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

void fillArrayWithZeros(double array[], int size) ;

void fillArrayWith(double array[], int size, double fillWith);

void fillArrayLinearly(double array[], int size);

double * vectorMult(const int size, double array1[size], double array2[size]);

void printArray(double array[], int size);

#endif /* ARRAY_UTILS_H */