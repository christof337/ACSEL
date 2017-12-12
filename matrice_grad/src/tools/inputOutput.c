#include <stdio.h>

#include "inputOutput.h"
#include "errorHandling.h"

#include <errno.h>
//#include <string.h>

#include "customMath.h"

#define RM m_getRoundingMode()

/**
 * @brief      Ask for an int in the standard input and return it
 *
 * @return     The input int
 */
int askForInt() {
   int askedInt;
   scanf("%d", &askedInt);
   return askedInt;
}

/**
 * @brief      écrit la matrice `matrix` dans un fichier.
 * @pre        `matrix` doit être de dimension (n,m)
 *
 * @param      matrix    The matrix to write
 * @param[in]  n         Number of columns
 * @param[in]  m         Number of rows
 * @param[in]  fileName  The file name
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeMatrix(mpfr_t ** matrix, const int n, const int m, const char * fileName) {
   FILE * pf;
   int errnum;
   pf = fopen (fileName, "a");
   
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
            //fprintf(pf,"%12G\t",matrix[i][j]);
            mpfr_out_str(pf,10,12,matrix[i][j],RM);
            fprintf(pf,"\t");
         }
         fprintf(pf,"\n");
      }

      fclose (pf);
   }
   
   return 0;
}

/**
 * @brief      Writes various data in a file. The labels are given as an
 *             argument, and will be used for column headers.
 * @pre        data must have n_array lines and size columns          
 * 
 * @param      data      The data to write
 * @param[in]  size      The size of each of data lines
 * @param[in]  fileName  The file name
 * @param      labels    The labels of the columns
 * @param[in]  n_array   The number of columns
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeData(mpfr_t * data[], const int size, const char * fileName, const char * labels[], const int n_array) {
   FILE * pf;
   int errnum;
   pf = fopen(fileName,"a");

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
            //fprintf(pf,"%12G\t",data[i][j]);
            mpfr_out_str(pf,10,12,data[i][j],RM);
            fprintf(pf,"\t");
         }
         fprintf(pf,"\n");
      }

      fclose(pf);
   }

   return 0;
}

/**
 * @brief      Writes an array in a file.
 *
 * @param      array     The array
 * @param[in]  size      The size of the array
 * @param[in]  fileName  The file name
 * @param[in]  label     The label
 *
 * @return     0 en cas de succès, la valeur de l'erreur sinon
 */
int writeArray(mpfr_t * array, const int size,const char * fileName, const char * label) {
   FILE * pf;
   int errnum;
   pf = fopen(fileName,"a");

   mpfr_prec_t prec = mpfr_get_prec(array[0]);

   if ( pf == NULL ) {
      // failed to open file
      errnum = errno;
      printError(errnum);
      return errnum;
   } else {
      // fprintf(pf,"i\t%12s\tprec\n",label);
      for ( int i = 0 ; i < size ; ++i ) {
         //fprintf(pf,"%d\t%G\n",i,array[i]);
         fprintf(pf,"%d\t",i);
         mpfr_out_str(pf,10,12,array[i],RM);
         fprintf(pf,"\t%ld\n",prec);
      }
      fprintf(pf,"\n"); // adding a chariot in order to have a nice view in gnuplot :) <3

      fclose(pf);
   }

   return 0;
}

FILE * openLog(const char * fileName) {
	FILE * file;
	int errnum;
	file = fopen(fileName,"a");

	 if ( file == NULL ) {
	      // failed to open file
	      errnum = errno;
	      printError(errnum);
	 }

	 return file;
}

//void m_log(FILE * logFile, const char * str) {
void m_log(FILE * logFile, FILE * str) { /*
	if ( logFile != NULL ) {
		fprintf(logFile,"%s",str);
	}
*/}

int closeLog(FILE * fileToClose) {
	if(fileToClose != NULL ) {
		fclose(fileToClose);
		return 0;
	} else {
		errorHandling();
		return -1;
	}
}
