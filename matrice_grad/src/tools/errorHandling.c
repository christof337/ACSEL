#include "errorHandling.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

int errorHandling() {
	int errnum;

	errnum = errno;
	perror("\nError : ");
	fprintf(stderr, "\nError : %s\n", strerror(errnum));

	return 0;
}

void printError(int errnum) {
	perror("\nError : ");
	fprintf(stderr, "\nError : %s\n", strerror(errnum));
}

void printCustomError(enum ERRORS err, int nbParams, ...) {
	va_list valist;
	char ** params;
	/* initialize valist for nbParams number of arguments */
	va_start(valist, nbParams);
	params = malloc(nbParams * sizeof(char*));
	/* access all the arguments assigned to valist */
	for (int i = 0 ; i < nbParams ; ++i) {
		params[i] = va_arg(valist, char*);
	}

	fprintf(stderr, "\nError : ");
	switch (err) {
	case ERROR_NO_EQUAL_SIGN_IN_PARAMETER:
		fprintf(stderr, "The parameter `%s` does not contain `=`.\n", params[1]);
		fprintf(stderr, "Type `%s help` in order to know how to input parameters.", params[0]);
		break;
	case ERROR_WRONG_VALUE_GIVEN:
		fprintf(stderr, "Incorrect usage of `%s` as a value for parameter %s.\n", params[2],
				params[1]);
		fprintf(stderr, "Type `%s help %s` in order to know which value to use.", params[0],
				params[1]);
		break;
	case ERROR_WRONG_PARAMETER_GIVEN:
		fprintf(stderr, "Parameter `%s` is incorrect.\n", params[1]);
		fprintf(stderr, "Type `%s help` in order to know which parameter to use.", params[0]);
		break;
	case ERROR_WHILE_HANDLING_INPUT_PARAMETERS:
		fprintf(stderr, "Wrong parameter given. \n");
		fprintf(stderr, "Type `%s help` in order to know which parameter to use.", params[0]);
		break;
	default:
		fprintf(stderr, "Something bad happened.");
		break;
	}
	fprintf(stderr, "\n");

	free(params);
	/* clean memory reserved for valist */
	va_end(valist);
}

void printErrorMessage(char * message) {
	fprintf(stderr, "\n%s", message);
}
