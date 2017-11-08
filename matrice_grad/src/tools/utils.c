#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char * toUpperCase(char * str, const int size) {
	char * res = malloc(size * sizeof(char));
	for ( int i = 0 ; i < size ; ++i ) {
		res[i] = toupper(str[i]);
	}
	return res;
}