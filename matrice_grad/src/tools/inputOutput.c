#include "inputOutput.h"

#include <stdio.h>
//#include <errno.h>
//#include <string.h>


int askForInt() {
   int askedInt;
   scanf("%d", &askedInt);
   return askedInt;
}

/*
int askForInt() {
   extern int errno ;
   int askedInt;
   scanf("%d", &askedInt);
   if ( errno != 0 ) {
         int errnum;
         errnum = errno;
         perror("Error : ");
         fprintf(stderr, "Input error : %s\n", strerror( errnum ));
   }
   return askedInt;
}*/

/*
int main () {

   FILE * pf;
   int errnum;
   pf = fopen ("unexist.txt", "rb");
	
   if (pf == NULL) {
   
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
   }
   else {
   
      fclose (pf);
   }
   
   return 0;
}*/