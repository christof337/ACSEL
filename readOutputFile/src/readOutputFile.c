/*
 ============================================================================
 Name        : readOutputFile.c
 Author      : Kito
 Version     :
 Copyright   : 
 Description : Read the output file of matrice_grad, given one of the output file
 ============================================================================
 */
#include "readOutputFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <mpfr.h>

#include "utils.h"
#include "matrixUtils.h"
#include "arrayUtils.h"
#include "inputOutput.h"

#define EXTENSION ".dat"

#define SIMPLIFIED_OUTPUT_FILE_NAME_PREFIX "simple_"

#define GKGK2_TRESHOLD "10.0"

int main(int argc, char *argv[]) {
	printf("\nProgram start...\n");
	fflush(stdout);
	int errnum = EXIT_SUCCESS;
	if (argc == 1) {
		fprintf(stderr,
				"\nNo input file. Please give one of the output file you need to analyse as a parameter when you call %s",
				argv[0]);
		errnum = EXIT_FAILURE;
	} else {
		// declaring the parameters
		enum valueTreatedEnum valueTreated;
		long int matrixSize, numberOfIterations, precisionMaxTreated;
		enum roundingModeEnum roundingMode;
		enum matrixTypeEnum matrixType;
		// extracting the params from the filename
		char * fileName = argv[1];
		// gkgk2_ms=5000_ni=60_pre=200_rm=STOCHASTIC_mt=EXPONENTIAL.dat
		errnum = extractParamsFromFileName(fileName, &valueTreated, &matrixSize,
				&numberOfIterations, &precisionMaxTreated, &roundingMode, &matrixType);
		if (errnum == EXIT_FAILURE) {
			fprintf(stderr, "Exiting...\n");
			return EXIT_FAILURE;
		} else {
			// we have everything
			// now we can actually read the file
			long int numberOfPrecisionTreated = precisionMaxTreated - MPFR_PREC_MIN + 1;
			mpfr_t (*valueTreatedArray)[numberOfPrecisionTreated][numberOfIterations];

			// initialization
			arr_alloc_2d(numberOfPrecisionTreated, numberOfIterations, &valueTreatedArray);
			// we don't call createMatrix because we want different precisions for each subarray
			for (int precision = MPFR_PREC_MIN ; precision <= precisionMaxTreated ; ++precision) {
				// looping to call _createArray instead
				mpfr_t (*ptr)[numberOfIterations];
				ptr = &((*valueTreatedArray) [ precision - MPFR_PREC_MIN ]);
				_createArray(numberOfIterations, &ptr,
						precision);
			}

			// reading from file...

			// find the output file, opening it, reading it, and putting its content in valueTreatedArray if everything's fine
			errnum = readFromFormattedOutputFile(fileName, precisionMaxTreated, numberOfIterations,
					*valueTreatedArray);

			if (errnum != EXIT_FAILURE) {
				// sucessfull read
				// get the last valueTreated value for each precision
				mpfr_t (*lastElements)[numberOfPrecisionTreated];
				getLastElements(numberOfPrecisionTreated, &lastElements, numberOfIterations,
						valueTreatedArray);
				assert(lastElements != NULL);

				// max
				size_t maxIndex;
				maxIndex = getMaxIndex(numberOfPrecisionTreated, *lastElements);
				mpfr_t maxValue;
				m_init2(maxValue, precisionMaxTreated);
				mpfr_set(maxValue, (*lastElements)[maxIndex], MPFR_RNDN);

				mpfr_printf(
						"\nThe maximum value for %s is %RF. It has been found at precision %zu\n",
						getStringFromValueTreatedEnum(valueTreated), maxValue,
						maxIndex + MPFR_PREC_MIN);

				// min
				size_t minIndex;
				minIndex = getMinIndex(numberOfPrecisionTreated, *lastElements);
				mpfr_t minValue;
				m_init2(minValue, precisionMaxTreated);
				mpfr_set(minValue, (*lastElements)[minIndex], MPFR_RNDN);

				mpfr_printf("\nThe minimum value for %s is %RF. ",
						getStringFromValueTreatedEnum(valueTreated), minValue);

				size_t * minIndexes;
				int nbMin = getAllMinIndexes(&minIndexes, numberOfPrecisionTreated, *lastElements);
				assert(nbMin != 0);
				if (nbMin > 1) {
					printMinimums(nbMin, minIndexes);
				} else if (nbMin == 1) {
					printf("It has been found at precision %zu\n", minIndex + MPFR_PREC_MIN);
				}
				int step = 0;
				char * simplifiedOutputFileName;
				char * fileNameWithoutPath = removePath(fileName);
				simplifiedOutputFileName = malloc(
						sizeof(char)
								* (strlen(fileNameWithoutPath)
										+ strlen(SIMPLIFIED_OUTPUT_FILE_NAME_PREFIX)));
				strcpy(simplifiedOutputFileName, SIMPLIFIED_OUTPUT_FILE_NAME_PREFIX);
				strcat(simplifiedOutputFileName, fileNameWithoutPath);

				mpfr_t (*precisions)[numberOfPrecisionTreated];
				_createArray(numberOfPrecisionTreated, &precisions, 18);
				for (long int i = MPFR_PREC_MIN ; i <= precisionMaxTreated ; ++i) {
					mpfr_set_si((*precisions)[i-MPFR_PREC_MIN], i, MPFR_RNDN);
				}
				mpfr_t (*data)[2][numberOfPrecisionTreated];

//				writeData
				writeArray(*lastElements, numberOfPrecisionTreated, simplifiedOutputFileName,
						"Simplified Gkgk2");

				// ------------------------------------------------------------------
				// just for the lulz, trying to write it again for comparison
				eraseFile("test.dat");
				for (size_t i = 0 ; i < numberOfPrecisionTreated ; ++i) {
					writeArray((*valueTreatedArray)[i], numberOfIterations, "test.dat",
							"Gkgk2 Test");
				}
				// ------------------------------------------------------------------

				freeArray(*lastElements, numberOfPrecisionTreated);
				free(minIndexes);
				free(simplifiedOutputFileName);
			}

			// final print
			parametersPrint(roundingMode, matrixType, valueTreated, matrixSize, numberOfIterations,
					precisionMaxTreated);
		}
	}

	if (errnum == EXIT_SUCCESS) {
		printf("\nProgram completed.\n");
	} else {
		printf("\nAn error occured. End of program...\n");
	}
	return errnum;
}

/* -------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------- */

int getLastElements(size_t m, mpfr_t (**lastElements)[m], size_t n, mpfr_t (*array)[m][n]) {
	int res = EXIT_SUCCESS;

	(*lastElements) = malloc(sizeof(mpfr_t[m]));

	assert((*lastElements) != NULL /* Error while allocating last elements array */);
	for (size_t i = 0 ; i < m ; ++i) {
		m_init2((**lastElements)[i], mpfr_get_prec((*array)[i][n - 1]));
		mpfr_set((**lastElements)[i], (*array)[i][n - 1], MPFR_RNDN);
	}

	return res;
}

/**
 * Put in valueTreated, matrixSize, numberOfIterations; precisionMaxTreated, roundingMode and matrixType,
 * the corresponding value from the fileName given as input.
 */
int extractParamsFromFileName(const char * fileName, enum valueTreatedEnum * valueTreated,
		long int * matrixSize, long int * numberOfIterations, long int * precisionMaxTreated,
		enum roundingModeEnum * roundingMode, enum matrixTypeEnum * matrixType) {
	int res = EXIT_SUCCESS;

	// test if the string contains `=` sign
	if (strchr(fileName, '=') == NULL) {
		// the string does not contain an "=" : errorprecisionMaxTreated
		fprintf(stderr, "\nThe given filename `%s` does not contain any `=` sign. Cannot read.\n",
				fileName);
		res = EXIT_FAILURE;
	} else {
		assert(
				strlen(strrchr(fileName,'.'))==strlen(EXTENSION) && "Wrong format. The file does not end with `.dat`");
		// removing the extension
		char * fileNameWithoutExtension = malloc(
				sizeof(char) * (strlen(fileName) - strlen(EXTENSION)));
		strncpy(fileNameWithoutExtension, fileName, strlen(fileName) - strlen(".dat"));
		char * toFree = fileNameWithoutExtension;
		if (strchr(fileName, '/') != NULL) {
			// removing the early path
			fileNameWithoutExtension = removePath(fileNameWithoutExtension);
		}
		// splitting with `_`
		char ** splittedString = str_split(fileNameWithoutExtension, '_');
		for (enum parameterOrderEnum poe = param_min ; poe <= param_max ; ++poe) {
			if (splittedString[poe] == NULL) {
				return EXIT_FAILURE;
			} else {
				if (poe == VALUE_TREATED) {
					// value treated
					if (strcasecmp(splittedString[poe], "gkgk2") == 0) {
						(*valueTreated) = GKGK2;
					} else {
						assert(0 && "Unknow treated value prefix.");
						res = EXIT_FAILURE;
					}
				} else {
					char ** currentParamCouple = str_split(splittedString[poe], '=');
					char * parameterStr = currentParamCouple[0];
					char * value = currentParamCouple[1];
					int nbSuccess = -1;
					switch (poe) {
					case VALUE_TREATED:
						// not a chance
						assert(0 && "Unknow error");
						res = EXIT_FAILURE;
						break;
					case MATRIX_SIZE:
						assert(
								strcasecmp(parameterStr, "ms") == 0
										&& "First parameter isn't matrix size");
						long int ms;
						nbSuccess = sscanf(value, "%ld", &ms);
						assert(
								nbSuccess > 0
										&& "Error while reading matrix size value in file name");
						(*matrixSize) = ms;
						break;
					case NB_ITER:
						assert(
								strcasecmp(parameterStr, "ni") == 0
										&& "Second parameter isn't number of iterations");
						long int ni;
						nbSuccess = sscanf(value, "%ld", &ni);
						assert(
								nbSuccess > 0
										&& "Error while reading number of iterations value in file name");
						(*numberOfIterations) = ni;
						break;
					case MAX_PREC:
						assert(
								strcasecmp(parameterStr, "pre") == 0
										&& "Third parameter isn't max precision");
						long int mp;
						nbSuccess = sscanf(value, "%ld", &mp);
						assert(
								nbSuccess > 0
										&& "Error while reading number of iterations value in file name");
						(*precisionMaxTreated) = mp;
						break;
					case ROUNDING_MODE:
						assert(
								strcasecmp(parameterStr, "rm") == 0
										&& "Fourth parameter isn't rounding mode");
						enum roundingModeEnum rme;
						if (strcasecmp(value, "STOCHASTIC") == 0) {
							rme = STOCHASTIC;
						} else if (strcasecmp(value, "RNDN") == 0) {
							rme = RNDN;
						} else if (strcasecmp(value, "RNDZ") == 0) {
							rme = RNDZ;
						} else if (strcasecmp(value, "RNDU") == 0) {
							rme = RNDU;
						} else if (strcasecmp(value, "RNDD") == 0) {
							rme = RNDD;
						} else if (strcasecmp(value, "RNDA") == 0) {
							rme = RNDA;
						} else {
							// error
							assert(0 && "Unknow rounding mode type");
							res = EXIT_FAILURE;
						}
						(*roundingMode) = rme;
						break;
					case MATRIX_TYPE:
						assert(
								strcasecmp(parameterStr, "mt") == 0
										&& "Fifth parameter isn't matrix type");
						enum matrixTypeEnum mte;
						if (strcasecmp(value, "RANDOM") == 0) {
							mte = RANDOM;
						} else if (strcasecmp(value, "EXPONENTIAL") == 0) {
							mte = EXPONENTIAL;
						} else if (strcasecmp(value, "HILBERT") == 0) {
							mte = HILBERT;
						} else {
							// error
							assert(0 && "Unknow matrix type");
							res = EXIT_FAILURE;
						}
						(*matrixType) = mte;
						break;
					case PARAM_ENUM_ERROR:
					default:
						assert(0 && "Too many parameters in filename");
						res = EXIT_FAILURE;
						break;
					}
					free(currentParamCouple);
				}
			}
		}
		free(splittedString);
		free(toFree);
	}
	return res;
}

void printMinimums(int nbMin, size_t minIndexes[nbMin]) {
	printf("This minimum has been found at precisions ");
	printf(" %zu", minIndexes[0]);
	for (int i = 1 ; i < nbMin - 1 ; ++i) {
		printf(", %zu", minIndexes[i] + MPFR_PREC_MIN);
	}
	printf(" and %zu.\n", minIndexes[nbMin - 1] + MPFR_PREC_MIN);
}

char* removePath(char* fileName) {
	// removing the early path
	fileName = strrchr(fileName, '/');
	fileName++; // removing the /
	return fileName;
}

void parametersPrint(enum roundingModeEnum roundingMode, enum matrixTypeEnum matrixType,
		enum valueTreatedEnum valueTreated, long int matrixSize, long int numberOfIterations,
		long int precisionMaxTreated) {
	// we have everything
	// final print
	char* roundingModeString = getStringFromRoundingModeEnum(roundingMode);
	assert(roundingModeString!=NULL && "Incorrect rounding mode?");
	char* matrixTypeString = getStringFromMatrixTypeEnum(matrixType);
	assert(matrixTypeString!=NULL && "Incorrect matrix type?");
	char* valueTreatedString = getStringFromValueTreatedEnum(valueTreated);
	assert(valueTreatedString!=NULL && "Incorrect treated value?");

	printf("\nThe values are :\n");
	printf("\t- Value treated : %s\n", valueTreatedString);
	printf("\t- Matrix size : %ld\n", matrixSize);
	printf("\t- Number of iterations : %ld\n", numberOfIterations);
	printf("\t- Precision max treated : %ld\n", precisionMaxTreated);
	printf("\t- Rounding mode : %s\n", roundingModeString);
	printf("\t- Matrix type : %s\n", matrixTypeString);

	free(roundingModeString);
	free(matrixTypeString);
	free(valueTreatedString);
}

/**
 * Give the string value from a roundingModeEnum
 */
char * getStringFromRoundingModeEnum(const enum roundingModeEnum rme) {
	char * res = malloc(sizeof(char) * strlen("STOCHASTIC"));
	switch (rme) {
	case RNDN:
		strcpy(res, "RNDN");
		break;
	case STOCHASTIC:
		strcpy(res, "STOCHASTIC");
		break;
	case RNDZ:
		strcpy(res, "RNDZ");
		break;
	case RNDU:
		strcpy(res, "RNDU");
		break;
	case RNDD:
		strcpy(res, "RNDD");
		break;
	case RNDA:
		strcpy(res, "RNDA");
		break;
	default:
		res = NULL;
	}
	return res;
}

char * getStringFromMatrixTypeEnum(const enum matrixTypeEnum mte) {
	char * res = malloc(sizeof(char) * strlen("EXPONENTIAL"));
	switch (mte) {
	case HILBERT:
		strcpy(res, "HILBERT");
		break;
	case RANDOM:
		strcpy(res, "RANDOM");
		break;
	case EXPONENTIAL:
		strcpy(res, "EXPONENTIAL");
		break;
	default:
		return NULL;
	}
	return res;
}

char * getStringFromValueTreatedEnum(const enum valueTreatedEnum vte) {
	char * res = malloc(sizeof(char) * strlen("GKGK2"));
	switch (vte) {
	case GKGK2:
		strcpy(res, "Gkgk2");
		break;
	default:
		return NULL;
	}
	return res;
}
