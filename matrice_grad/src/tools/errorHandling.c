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

