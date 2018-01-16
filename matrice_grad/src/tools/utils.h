#ifndef UTILS_H
#define UTILS_H

#include <gmp.h>
#include <mpfr.h>

char * toUpperCase(const char * str, const size_t size);

char** str_split(char* a_str, const char a_delim);

void getRandstate(gmp_randstate_t randState);

void setRandomValue(mpfr_t * val);

void clearRandState();

void printLine();

void printProgressBarLine(const int nbThreads) ;

void strreplace(char string[], char search[], char replace[]);

void cfree(void * ptr);

#endif /* UTILS_H */

