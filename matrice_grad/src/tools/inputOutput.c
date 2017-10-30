#include "inputOutput.h"
#include "errorHandling.h"

#include <stdio.h>
#include <errno.h>
//#include <string.h>


int askForInt() {
   int askedInt;
   scanf("%d", &askedInt);
   return askedInt;
}

/**
 * écrit la matrice `matrix` dans un fichier.
 * `matrix` doit être de dimension (n,m)
 * renvoit 0 en cas de succès, une autre valeur sinon
 */
int writeMatrix(double ** matrix, const int n, const int m, const char * fileName) {
   FILE * pf;
   int errnum;
   pf = fopen (fileName, "w+");
   
   if ( pf == NULL ) {
      // fail to open file
      errnum = errno;
      printError(errnum);
      return errnum;
   } else {
      fprintf(pf,"\t");
      for ( int j = 0 ; j < n ; ++j ) {
         fprintf(pf,"%8s[%d]\t","",j+1);
      }
      fprintf(pf,"\n");
      for ( int i = 0 ; i < m ; ++i ) {
         fprintf(pf,"[%d]\t",i+1);
         for ( int j = 0 ; j < n ; ++j ) {
            fprintf(pf,"%12G\t",matrix[i][j]);
         }
         fprintf(pf,"\n");
      }

      fclose (pf);
   }
   
   return 0;
}

int writeData(double * data[], const int size, const char * fileName, const char * labels[], const int n_array) {
   FILE * pf;
   int errnum;
   pf = fopen(fileName,"w+");

   if ( pf == NULL ) {
      // failed to open file
      errnum = errno;
      printError(errnum);
      return errnum;
   } else {
      // libellés
      for ( int i = 0 ; i < n_array ; ++i ) {
         fprintf(pf,"%12s\t",labels[i]);
      }
      fprintf(pf,"\n");
      for ( int j = 0 ; j < size ; ++j ) {
         for ( int i = 0 ; i < n_array ; ++i ) {
            fprintf(pf,"%12G\t",data[i][j]);
         }
         fprintf(pf,"\n");
      }

      fclose(pf);
   }

   return 0;
}

int writeArray(double * array, const int size,const char * fileName, const char * label) {
   FILE * pf;
   int errnum;
   pf = fopen(fileName,"w+");

   if ( pf == NULL ) {
      // failed to open file
      errnum = errno;
      printError(errnum);
      return errnum;
   } else {
      fprintf(pf,"i\t%s\n",label);
      for ( int i = 0 ; i < size ; ++i ) {
         fprintf(pf,"%d\t%G\n",i,array[i]);
      }

      fclose(pf);
   }

   return 0;
}
