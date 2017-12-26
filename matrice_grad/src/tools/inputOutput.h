#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <mpfr.h>

int askForInt();

int writeMatrix(const size_t n, const size_t m, mpfr_t matrix[m][n], const char * fileName);

int writeData(mpfr_t * data[], const int size, const char * fileName, const char * labels[],
		const int n_array);

int writeArray(mpfr_t * array, const int size, const char * fileName, const char * label);

void eraseFile(const char * fileName);

char * getFileNameFromPrecision(const char * prefix, const char * suffix, const long int precision);

char * buildSuffix();

#endif /* INPUT_OUTPUT_H */
