#include "utils.h"

#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <bsd/stdlib.h>

/**
 * Return the uppercase string of the given `str`.
 * Result must be freed afterwards.
 * @param str	The string to up
 * @param size	The size of `str`
 * @return		A new string uppercase of `str`
 */
char * toUpperCase(const char * str, const size_t size) {
	char * res = malloc(size * sizeof(char));
	for (size_t i = 0 ; i < size ; ++i) {
		res[i] = toupper(str[i]);
	}
	return res;
}

/**
 * Split the string `a_str` with the given delimiter
 * @param a_str		The string to split
 * @param a_delim	The delimiter around which split
 * @return			An array of strings, splitted from a_str with a_delim
 */
char** str_split(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
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

	if (result) {
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

gmp_randstate_t randState;
int isRandstateInitialized = 0;

/**
 * Init and seed the given randState a specific randstate.
 * http://man.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man3/arc4random.3?query=arc4random%26sec=3
 * @param randState	The randstate to init and seed
 */
void getRandstate(gmp_randstate_t randState) {
	gmp_randinit_default(randState);
	uint32_t val = arc4random();
	//uint32_t arc4random(void)
	gmp_randseed_ui(randState, val);
	isRandstateInitialized = 1;
}

/**
 *	Put a random value between 0 and 1 in `val` using gmp_randstate and mpfr_urandomb.
 *	TODO : enable multiple random seeding.
 * @param val 	The value to randomize
 */
void setRandomValue(mpfr_t * val) {
	/*
	 * Envisager chaine de Markov ?
	 */
	if (!isRandstateInitialized) {
		getRandstate(randState);
	}
	mpfr_urandomb(*val, randState);
}

// TEST setRandomValue :
/*
 * 	StartTimer();
	mpfr_t val;
	m_init2(val,mpfr_get_default_prec());
	for(int i = 0 ; i < 100 ; ++i ) {
		setRandomValue(val);
		mpfr_printf("[%d] - %RF\n",i,val);
	}
	clearRandState();
	double runtime = GetTimer();

	printf(" \n\nTotal time ellapsed: %f s\n", runtime / 1000);
	return 0;
 */

void clearRandState() {
	if (isRandstateInitialized) {
		gmp_randclear(randState);
	}
}

/**
 * Simply print a line with one charriot return before and one after on the standard output.
 */
void printLine() {
	printf("\n---------------------------------\n");
}

void printProgressBarLine(const int nbThreads) {
	printf("\n| Début");
	int nbSpaces = (nbThreads - strlen(" Début") - strlen("Fin ") + 1);
	for (int i = 0 ; i <= nbSpaces ; ++i) {
		printf(" ");
	}
	printf("Fin |\n");
}

void strreplace(char string[], char search[], char replace[]){
    char buffer[100];
    char*p = string;
    while((p=strstr(p, search))){
        strncpy(buffer, string, p-string);
        buffer[p-string] = '\0';
        strcat(buffer, replace);
        strcat(buffer, p+strlen(search));
        strcpy(string, buffer);
        p++;
    }
}

void cfree(void * ptr) {
	if(ptr) {
		free(ptr);
	}
}
