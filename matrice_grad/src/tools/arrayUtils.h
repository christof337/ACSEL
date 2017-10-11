#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

double * createArray(const int n);

double * fillArrayWithZeros(double * array, const int size) ;

double * fillArrayWith(double * array, const int size, double fillWith);

double * fillArrayLinearly(double * array, const int size);

double * vectorMult(double * array1, const int size1, double * array2, const int size2);

double * vectorLessVector(double * vector1, const int size1, double * vector2, const int size2);

double * vectorCopy(double * vector, const int size);

double innerDotProduct(double * vector, const int size);

double dotProduct(double * vector1, const int size1, double * vector2, const int size2);

double * vectorMultDouble(double * vector, const int size, double value);

double sumSquare(double * vector, const int size);

void printArray(double * array, const int size);

#endif /* ARRAY_UTILS_H */