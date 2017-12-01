#ifndef UTILS_H
#define UTILS_H

#include <gmp.h>

char * toUpperCase(char * str, const int size);

char** str_split(char* a_str, const char a_delim);

void getRandstate(gmp_randstate_t randState);

void printLine(); 

#endif /* UTILS_H */
