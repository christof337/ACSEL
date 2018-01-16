#include <stdio.h>

#include "inputOutput.h"
#include "errorHandling.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "customMath.h"
#include "utils.h"

#ifndef RM
#define RM mpfr_get_default_rounding_mode()
#endif // RM

#define DATA_SUFFIX ".dat"

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
int writeMatrix(const size_t n, const size_t m, mpfr_t matrix[m][n], const char * fileName) {
	FILE * pf;
	int errnum;
	pf = fopen(fileName, "w+");

	if (pf == NULL) {
		// fail to open file
		errnum = errno;
		printError(errnum);
		return errnum;
	} else {
		fprintf(pf, "\t");
		for (int j = 0 ; j < n ; ++j) {
			fprintf(pf, "%8s[%d]\t", "", j + 1);
		}
		fprintf(pf, "\n");
		for (int i = 0 ; i < m ; ++i) {
			fprintf(pf, "[%d]\t", i + 1);
			for (int j = 0 ; j < n ; ++j) {
				//fprintf(pf,"%12G\t",matrix[i][j]);
				mpfr_out_str(pf, 10, 12, matrix[i][j], RM);
				fprintf(pf, "\t");
			}
			fprintf(pf, "\n");
		}

		fclose(pf);
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
int writeData(const size_t size, const char * fileName, const size_t n_array,
		const char * labels[n_array], mpfr_t * data[n_array]) {
	FILE * pf;
	int errnum;
	pf = fopen(fileName, "a");

	if (pf == NULL) {
		// failed to open file
		errnum = errno;
		printError(errnum);
		return errnum;
	} else {
		// libellés
		for (int i = 0 ; i < n_array ; ++i) {
			fprintf(pf, "%12s\t", labels[i]);
		}
		fprintf(pf, "\n");
		for (size_t j = 0 ; j < size ; ++j) {
			for (size_t i = 0 ; i < n_array ; ++i) {
				//fprintf(pf,"%12G\t",data[i][j]);
				mpfr_out_str(pf, 10, 0, data[i][j], RM);
				fprintf(pf, "\t");
			}
			fprintf(pf, "\n");
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
int writeArray(mpfr_t * array, const int size, const char * fileName, const char * label) {
	FILE * pf;
	int errnum;
	pf = fopen(fileName, "a");

	mpfr_prec_t prec = mpfr_get_prec(array[0]);

	if (pf == NULL) {
		// failed to open file
		errnum = errno;
		printError(errnum);
		return errnum;
	} else {
		// fprintf(pf,"i\t%12s\tprec\n",label);
		for (size_t i = 0 ; i < size ; ++i) {
			//fprintf(pf,"%d\t%G\n",i,array[i]);
			fprintf(pf, "%zu\t", i);
			mpfr_out_str(pf, 10, 0, array[i], RM);
			fprintf(pf, "\t%ld\n", prec);
		}
		fprintf(pf, "\n"); // adding a chariot in order to have a nice view in gnuplot :) <3

		fclose(pf);
	}

	return 0;
}

void eraseFile(const char * fileName) {
	// réinitialisation du fichier
	FILE * pf;
	pf = fopen(fileName, "w+");
	// fprintf(pf, " "); // TODO : check if necessary
	fclose(pf);
}

char * getFileNameFromPrecision(const char * prefix, const char * suffix, const long int precision) {
	char * fileName = malloc(sizeof(char) * (strlen(prefix) + strlen(suffix) + 5));

	sprintf(fileName, "%s(%ld)%s", prefix, precision, suffix);

	return fileName;
}

char * buildSuffix() {
	char * suffix;
	suffix = malloc(sizeof(char) * strlen(DATA_SUFFIX));
	strcpy(suffix, DATA_SUFFIX);
	return suffix;
}

/**
 * Read from a given formatted output file and put the read lines in arrayToFill.
 * @param fileName
 * @param precisionMaxTreated
 * @param nbIterations
 * @param arrayToFill
 * @return
 */
int readFromFormattedOutputFile(const char* fileName, long int precisionMaxTreated,
		long int nbIterations, mpfr_t (*arrayToFill)[precisionMaxTreated][nbIterations]) {
	// reading from file...
	// find the output file
	FILE* file;
	int errnum = EXIT_SUCCESS;
	// try to open the file in read mode
	file = fopen(fileName, "r");
	//			errnum = errno;
	if (file == NULL) {
		// error while opening the file
		fprintf(stderr, "Error while opening the file %s : %s", fileName, strerror(errnum));
		errnum = EXIT_FAILURE;
	} else {
		// successfully opened the file
		char* line = NULL;
		size_t len = 0;
		ssize_t read;
		char** splittedLine = NULL;
		long int it;
		mpfr_t secondColumn;
		for (long int precision = MPFR_PREC_MIN ; precision <= precisionMaxTreated ; ++precision) {
			it = 0;
			// reading all the lines for this precision until meeting an empty line
			while ((read = getline(&line, &len, file)) != -1 && strcmp(line, "\n") != 0) {
				// non empty line
				splittedLine = str_split(line, '\t');
				if (splittedLine == NULL) {
					// impossible to split : error?
					fprintf(stderr, "\nImpossible to split the line %s [%ld].\n", line, precision);
					/* Split fail */
					assert(0 /* Split fail */);
					errnum = EXIT_FAILURE;
				} else {
					assert(splittedLine[2]!=NULL && "Wrong file format");
					long int thirdColumn;
					sscanf(splittedLine[2], "%ld", &thirdColumn);
					if (thirdColumn != precision) {
						fprintf(stderr,
								"\nError while reading line %s (for precision %ld).\nThe input file does not have a correct format.\nCheck that the precision is the third column and that a line has been jumped between each precision block.",
								line, precision);
						assert(0 /* Read fail */);
						errnum = EXIT_FAILURE;
					} else {
						// the third column actually is the right precision
						// is the first one the number of iterations?
						long int firstColumn;
						sscanf(splittedLine[0], "%ld", &firstColumn);
						if (firstColumn != it) {
							fprintf(stderr,
									"\nError while reading line %s (for precision %ld).\nThe input file does not have a correct format.\nCheck that the first column is in the right order",
									line, precision);
							assert(0 /* Read fail */);
							errnum = EXIT_FAILURE;
						} else {
							// all seem nice, we are actually at the line corresponding to the precision `precision`
							// and to the iteration number `it`
							m_init2(secondColumn, precision);
							size_t prec = precision - MPFR_PREC_MIN;
							m_init2((*arrayToFill)[prec][it], precision);
							int tmp = mpfr_set_str(secondColumn, splittedLine[1], 10 /* base 10 */,
									MPFR_RNDN);
							assert(tmp == 0 /* mpfr_set_str fail*/);
							mpfr_set((*arrayToFill)[prec][it], secondColumn, MPFR_RNDN);
							m_clear(secondColumn);
						} // endif firstColumn = it
					} // endif third column != precision
				} // endif splitted line == NULL
				free(splittedLine);
				++it;
				// going to the next iteration
			}
			// going to the next precision
		}
		fclose(file);
		cfree(line);
	}
	return errnum;
}

/**
 * Read from a given formatted simple output file and put the read lines in arrayToFill.
 * @param fileName
 * @param precisionMaxTreated
 * @param nbIterations
 * @param arrayToFill
 * @return
 */
int readFromSimpleFormattedOutputFile(const char* fileName, const long int precisionMaxTreated,
		const long int nbIterations, mpfr_t (*arrayToFill)[precisionMaxTreated]) {
	// reading from file...
	// find the output file
	FILE* file;
	int errnum = EXIT_SUCCESS;
	// try to open the file in read mode
	file = fopen(fileName, "r");
	errnum = errno;
	if (file == NULL) {
		// error while opening the file
		fprintf(stderr, "Error while opening the file %s : %s", fileName, strerror(errnum));
		errnum = EXIT_FAILURE;
	} else {
		// successfully opened the file
		char* line = NULL;
		size_t len = 0;
		ssize_t read;
		char** splittedLine = NULL;
		mpfr_t secondColumn;
		mpfr_prec_t precision = MPFR_PREC_MIN;
		// reading all the lines for this precision until meeting an empty line
		// header line
		getline(&line, &len, file);
		while ((read = getline(&line, &len, file)) != -1 && strcmp(line, "\n") != 0) {
			// non empty line
			splittedLine = str_split(line, '\t');
			if (splittedLine == NULL) {
				// impossible to split : error?
				fprintf(stderr, "\nImpossible to split the line %s [%ld].\n", line, precision);
				/* Split fail */
				assert(0 /* Split fail */);
				errnum = EXIT_FAILURE;
			} else {
				assert(splittedLine[0]!=NULL && "Wrong file format");
				float firstColumn;
				sscanf(splittedLine[0], "%f", &firstColumn);
				if ((long)firstColumn != precision) {
					fprintf(stderr,
							"\nError while reading line %s (for precision %ld).\nThe input file does not have a correct format.\nCheck that the precision is the third column and that a line has been jumped between each precision block.",
							line, precision);
					assert(0 /* Read fail */);
					errnum = EXIT_FAILURE;
				} else {
					// all seem nice, we are actually at the line corresponding to the precision `precision`
					m_init2(secondColumn, precision);
					size_t index = precision - MPFR_PREC_MIN;
					m_init2((*arrayToFill)[index], precision);
					int tmp = mpfr_set_str(secondColumn, splittedLine[1], 10 /* base 10 */,
							MPFR_RNDN);
					assert(tmp == 0 /* mpfr_set_str fail*/);
					mpfr_set((*arrayToFill)[index], secondColumn, MPFR_RNDN);
					m_clear(secondColumn);
				}
			}
			cfree(splittedLine);
			++precision;
			// going to the next precision
		}
		fclose(file);
		cfree(line);
	}
	return errnum;
}
