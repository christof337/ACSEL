#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <mpfr.h>

int askForInt() ;

int writeMatrix(mpfr_t ** matrix, const int n, const int m, const char * fileName) ;

int writeData(mpfr_t * data[], const int size, const char * fileName, const char * labels[], const int n_array) ;

int writeArray(mpfr_t * array, const int size,const char * fileName, const char * label) ;

#endif /* INPUT_OUTPUT_H */