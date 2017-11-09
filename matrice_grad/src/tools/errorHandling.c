#include "errorHandling.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

int errorHandling () {
	int errnum;

	errnum = errno;
	perror("Error : ");
	fprintf(stderr, "Error : %s\n", strerror( errnum ));

	return 0;
}

void printError(int errnum) {
	perror("\nError : ");
	fprintf(stderr, "\nError : %s\n", strerror( errnum ));
}

void printCustomError(enum ERRORS err, char * param) {
	fprintf(stderr,"\nError : ");
	switch(err) {
		case ERROR_NO_EQUAL_SIGN_IN_PARAMETER:
			fprintf(stderr,"The parameter `%s` does not contain `=`.",param);
			break;
		case ERROR_WHILE_HANDLING_INPUT_PARAMETERS:
			fprintf(stderr,"Wrong parameter given. Type `%s help` in order to know which parameter use.",param);
			break;
		default:
			fprintf(stderr,"Something bad happened.");
			break;
	}
	fprintf(stderr,"\n");
}

void printErrorMessage(char * message) {
	fprintf(stderr,"%s",message);
}