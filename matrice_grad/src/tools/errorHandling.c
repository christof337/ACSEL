#include "errorHandling.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <gsl/gsl_errno.h>

int errorHandling () {

   	int errnum;
	
      errnum = errno;
      perror("Error : ");
      fprintf(stderr, "Error : %s\n", strerror( errnum ));

   return 0;
}

void printGslError (int status) {
	printf ("error: %s\n", gsl_strerror(status));
}