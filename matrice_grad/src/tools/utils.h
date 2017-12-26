#ifndef UTILS_H
#define UTILS_H

#include <gmp.h>
#include <mpfr.h>

char * toUpperCase(char * str, const size_t size);

char** str_split(char* a_str, const char a_delim);

void getRandstate(gmp_randstate_t randState);

void setRandomValue(mpfr_t * val);

void printLine();

#endif /* UTILS_H */
