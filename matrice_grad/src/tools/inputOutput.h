#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <mpfr.h>

int askForInt();

int writeMatrix(const size_t n, const size_t m, mpfr_t matrix[m][n], const char * fileName);

int writeData(const size_t size, const char * fileName, const size_t n_array,
		const char * labels[n_array], const mpfr_t * data[n_array]);

int writeArray(mpfr_t * array, const int size, const char * fileName, const char * label);

void eraseFile(const char * fileName);

char * getFileNameFromPrecision(const char * prefix, const char * suffix, const long int precision);

char * buildSuffix();

int readFromFormattedOutputFile(const char* fileName, long int precisionMaxTreated,
		long int nbIterations, mpfr_t (*arrayToFill)[precisionMaxTreated][nbIterations]);

int readFromSimpleFormattedOutputFile(const char* fileName, const long int precisionMaxTreated,
		const long int nbIterations, mpfr_t (*arrayToFill)[precisionMaxTreated]);

#endif /* INPUT_OUTPUT_H */
