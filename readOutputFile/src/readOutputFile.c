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

#include "utils.h"

#define EXTENSION ".dat"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr,
				"\nNo input file. Please give one of the output file you need to analyse as a parameter when you call %s",
				argv[0]);
		return EXIT_FAILURE;
	} else {
		// find the output file
		FILE * file;
		int errnum;

		// try to open the file in read mode
		file = fopen(argv[1], "r");
		errnum = errno;
		if (file == NULL) {
			// error while opening the file
			fprintf(stderr, "Error while opening the file %s : %s", argv[1], strerror(errnum));
		} else {
			// successfully opened the file
			// declaring the parameters
			enum valueTreatedEnum valueTreated;
			long int matrixSize, numberOfIterations, precisionMaxTreated;
			enum roundingModeEnum roundingMode;
			enum matrixTypeEnum matrixType;
			// extracting the params from the filename
			// gkgk2_ms=5000_ni=60_pre=200_rm=STOCHASTIC_mt=EXPONENTIAL.dat
			errnum = extractParamsFromFileName(argv[1], &valueTreated, &matrixSize,
					&numberOfIterations, &precisionMaxTreated, &roundingMode, &matrixType);
			if (errnum == EXIT_FAILURE) {
				fprintf(stderr, "Exiting...\n");
				return EXIT_FAILURE;
			} else {
				// we have everything

				// final print
				parametersPrint(roundingMode, matrixType, valueTreated, matrixSize,
						numberOfIterations, precisionMaxTreated);
			}

			fclose(file);
		}
	}
	return EXIT_SUCCESS;
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
		// the string does not contain an "=" : error
		fprintf(stderr, "\nThe given filename `%s` does not contain any `=` sign. Cannot read.\n",
				fileName);
		return EXIT_FAILURE;
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
			fileNameWithoutExtension = strrchr(fileNameWithoutExtension, '/');
			fileNameWithoutExtension++; // removing the /
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
