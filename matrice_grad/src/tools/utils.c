#include "utils.h"

#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <bsd/stdlib.h>

char * toUpperCase(char * str, const int size) {
	char * res = malloc(size * sizeof(char));
	for ( int i = 0 ; i < size ; ++i ) {
		res[i] = toupper(str[i]);
	}
	return res;
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

/**
 * http://man.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man3/arc4random.3?query=arc4random%26sec=3
 * @param randState
 */
void getRandstate(gmp_randstate_t randState) {
	gmp_randinit_default(randState);
	uint32_t val = arc4random();
	//uint32_t arc4random(void)
	gmp_randseed_ui (randState, val);
}

void printLine() {
	printf("\n-----------\n");
}
