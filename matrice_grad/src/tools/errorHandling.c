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
