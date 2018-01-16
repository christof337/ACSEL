#include "parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpfr.h>
#include <unistd.h>
#include <getopt.h>

#include "tools/utils.h"
#include "tools/errorHandling.h"

#include "help.h"

#define DEFAULT_MATRIX_SIZE 100
#define DEFAULT_NB_ITER 50
#define DEFAULT_MAX_PREC 75

#define DEFAULT_ROUNDING_MODE RNDN
#define DEFAULT_MATRIX_TYPE EXPONENTIAL

#define HELP_CAPTION "HELP"

struct Param *P_MATRIX_SIZE, *P_NB_ITER, *P_MAX_PREC, *P_ROUNDING_MODE, *P_MATRIX_TYPE, *P_ERROR;

struct Param _p_m_s, _p_n_i, _p_m_p, _p_r_m, _p_m_t, _p_e;

/* TODO : tout remplacer par `getopt` */

/**
 * @brief      Init the parameters
 *
 * @param      appName  The application name
 *
 * @return     { description_of_the_return_value }
 */
int initParams(char * appName) {
	paramAdressInit();

	char tmp[200];

	// MATRIX_SIZE
	strcpy(P_MATRIX_SIZE->name, "matrixSize");
	strcpy(P_MATRIX_SIZE->shortName, "ms");
	P_MATRIX_SIZE->typ_defaultValue = SIZE_T;
	P_MATRIX_SIZE->defaultValue.s = DEFAULT_MATRIX_SIZE;
	strcpy(P_MATRIX_SIZE->description, "Define the size of the processed matrix.");
	P_MATRIX_SIZE->error = 0;
	P_MATRIX_SIZE->isDefault = 1;
	P_MATRIX_SIZE->currentValue.s = DEFAULT_MATRIX_SIZE;

	// NB_ITER
	strcpy(P_NB_ITER->name, "nbIter");
	strcpy(P_NB_ITER->shortName, "ni");
	P_NB_ITER->typ_defaultValue = LONGINT;
	P_NB_ITER->defaultValue.li = DEFAULT_NB_ITER;
	strcpy(P_NB_ITER->description, "Define the number of iterations made to minimize the matrix.");
	P_NB_ITER->error = 0;
	P_NB_ITER->isDefault = 1;
	P_NB_ITER->currentValue.li = DEFAULT_NB_ITER;

	// MAX_PREC
	strcpy(P_MAX_PREC->name, "maxPrecision");
	strcpy(P_MAX_PREC->shortName, "mp");
	P_MAX_PREC->typ_defaultValue = LONGINT;
	P_MAX_PREC->defaultValue.li = DEFAULT_MAX_PREC;
	strcpy(P_MAX_PREC->description,
			"Define the maximum precision up until the program will process (from 2 to maxPrecision).");
	P_MAX_PREC->error = 0;
	P_MAX_PREC->isDefault = 1;
	P_MAX_PREC->currentValue.li = DEFAULT_MAX_PREC;

	// ROUNDING_MODE
	strcpy(P_ROUNDING_MODE->name, "roundingMode");
	strcpy(P_ROUNDING_MODE->shortName, "rm");
	P_ROUNDING_MODE->typ_defaultValue = ROUNDINGMODEENUM;
	P_ROUNDING_MODE->defaultValue.rme = DEFAULT_ROUNDING_MODE;
	sprintf(tmp, "Define the rounding mode used for the computations of the program.");
	strcpy(P_ROUNDING_MODE->description, tmp);
	P_ROUNDING_MODE->error = 0;
	P_ROUNDING_MODE->isDefault = 1;
	P_ROUNDING_MODE->currentValue.rme = DEFAULT_ROUNDING_MODE;

	// MATRIX_TYPE
	strcpy(P_MATRIX_TYPE->name, "matrixType");
	strcpy(P_MATRIX_TYPE->shortName, "mt");
	P_MATRIX_TYPE->typ_defaultValue = MATRIXTYPEENUM;
	P_MATRIX_TYPE->defaultValue.mte = DEFAULT_MATRIX_TYPE;
	sprintf(tmp, "Define the way the processed matrix is filled.");
	strcpy(P_MATRIX_TYPE->description, tmp);
	P_MATRIX_TYPE->error = 0;
	P_MATRIX_TYPE->isDefault = 1;
	P_MATRIX_TYPE->currentValue.mte = DEFAULT_MATRIX_TYPE;

	// ERROR
	strcpy(P_ERROR->name, "Error");
	P_ERROR->error = -1;

	return 0;
}

/**
 * @brief      Set the application parameters accordingly to the given input values
 *
 * @param[in]  argc  The number of passed arguments
 * @param      argv  The commandline arguments
 *
 * @return     0 if the arguments were correctly handled, 1 if only the help caption was asked, and a value < 0 if a problem has occured
 */
int handleParams(int argc, char *argv[]) {
	int err = EXIT_SUCCESS;
	if (argc > 1) {
		globalAppName = argv[0];
		// one or more argument passed
		char c;
		int option_index = 0;
		static struct option long_options[] = {
				{ "model", 1, 0, 0 },
				{ "matrixSize", 1, 0, 0 },
				{ "nbIter", 1, 0, 0 },
				{ "maxPrecision", 1, 0, 0 },
				{ "roundingMode", 1, 0, 0},
				{ "matrixType", 1, 0, 0 },
				{ "mo", 1, 0, 0 },
				{ "ms", 1, 0, 0 },
				{ "ni", 1, 0, 0 },
				{ "mp", 1, 0, 0 },
				{ "rm", 1, 0, 0},
				{ "mt", 1, 0, 0 },
				{ "help", 2, 0, 'h' },
				{ 0, 0, 0, 0 } };

		while ((c = getopt_long(argc, argv, "+h", long_options, &option_index)) != -1) {

			switch (c) {
			case 0:
				// long option
				if (isHelp(long_options[option_index].name)) {
					if(optarg) {
						printNeededHelp(optarg);
					} else {
						printHelp();
					}
					return 1;
				} else {
					if (optarg) {
						err = setParam(long_options[option_index].name, optarg);
						if (err == EXIT_FAILURE) {
							// error
							return err;
						}
					} else {
						fprintf(stderr, "Please give a value after the option %s.\n",
								long_options[option_index].name);
						return EXIT_FAILURE;
					}
				}
				break;
			case 'h':
				if (optarg) {
					printNeededHelp(optarg);
				} else {
					printHelp();
				}
				return 1;
			case '?':
				printHelp();
				if(optarg) {
					printNeededHelp(optarg);
				}
				break;
			default:
				fprintf(stderr, "Unknow option %c.\n", c);
				return EXIT_FAILURE;
				break;
			}
			option_index = 0;
		}
	} else {
		// no argument given
		// default values will be used
		err = 0;
	}

	// arguments without options :
    if (optind < argc) {
    	fprintf(stderr,"Error : too many arguments given. ");
        while (optind < argc) {
            fprintf(stderr, "`%s` ", argv[optind++]);
        }
    	fprintf(stderr," are unrecognized.\n");
    	printHelp();
    	err = EXIT_FAILURE;
    }

	return err;
}

int setParam(const char * paramName, const char * paramValue) {
	int err = EXIT_SUCCESS;

	err = assignValueToParam(getParamFromParamEnum(getParamEnumFromString(paramName)),
			paramValue);

	return err;
}

int assignValueToParam(struct Param * param, const char * strValue) {
	int err = EXIT_SUCCESS;
	int res;
	double dou;
	long int li;
	enum roundingModeEnum roundingMode;
	size_t s;
	char * valueUp = toUpperCase(strValue, strlen(strValue) + 1);
	switch (param->typ_defaultValue) {
	case DOUBLE:
		res = sscanf(strValue, "%lf", &dou);
		if (res == EOF) {
			// error
			err = -1;
		} else {
			param->currentValue.d = dou;
		}
		break;
	case MATRIXTYPEENUM:
		if (strcmp(valueUp, "EXPONENTIAL") == 0) {
			param->currentValue.mte = EXPONENTIAL;
		} else if (strcmp(valueUp, "HILBERT") == 0) {
			param->currentValue.mte = HILBERT;
		} else if (strcmp(valueUp, "RANDOM") == 0) {
			param->currentValue.mte = RANDOM;
		} else {
			// error
			err = -1;
		}
		break;
	case SIZE_T:
		res = sscanf(strValue, "%zu", &s);
		if (res == EOF) {
			// error
			err = -1;
		} else {
			param->currentValue.s = s;
		}
		break;
	case LONGINT:
		res = sscanf(strValue, "%ld", &li);
		if (res == EOF) {
			// error
			err = -1;
		} else {
			param->currentValue.li = li;
		}
		break;
	case ROUNDINGMODEENUM:
		res = stringToRoundingModeEnum(valueUp, strlen(valueUp) + 1);
		if (res != -1) {
			param->currentValue.rme = res;
		} else {
			err = res;
		}
		break;
	default:
		//erreur
		err = EXIT_FAILURE;
		break;
	}
	if (err == EXIT_SUCCESS) {
		param->isDefault = 0;
	}
	free(valueUp);
	return err;
}

/* MAPPERS */
enum ParamEnum getParamEnumFromString(const char * paramName) {
	enum ParamEnum res = PARAM_ENUM_ERROR;
	char * paramNameUpper = toUpperCase(paramName, strlen(paramName) + 1);
	enum ParamEnum pe = param_min;
	while (pe <= param_max && res == PARAM_ENUM_ERROR) {
		struct Param param = *getParamFromParamEnum(pe);
		char * longNameUp = toUpperCase(param.name, strlen(param.name) + 1);
		char * shortNameUp = toUpperCase(param.shortName, strlen(param.shortName) + 1);

		if (strcmp(longNameUp, paramNameUpper) == 0 || strcmp(shortNameUp, paramNameUpper) == 0) {
			res = pe;
		}

		free(longNameUp);
		free(shortNameUp);

		++pe;
	}
	free(paramNameUpper);
	return res;
}

/* --------------*/
/* ROUNDING MODE */
/* --------------*/

/**
 * @brief      { function_description }
 *
 * @param      string  The string
 *
 * @return     `-1` if the rounding mode asked is not handled
 */
enum roundingModeEnum stringToRoundingModeEnum(char * string, const size_t size) {
	enum roundingModeEnum res = -1;

	char * str = toUpperCase(string, size);

	if (strcmp(str, "RNDN") == 0) {
		res = RNDN;
	} else if (strcmp(str, "STOCHASTIC") == 0) {
		res = STOCHASTIC;
	} else if (strcmp(str, "RNDZ") == 0) {
		res = RNDZ;
	} else if (strcmp(str, "RNDU") == 0) {
		res = RNDU;
	} else if (strcmp(str, "RNDD") == 0) {
		res = RNDD;
	} else if (strcmp(str, "RNDA") == 0) {
		res = RNDA;
	} else {
		res = -1;
	}

	free(str);

	return res;
}

//mpfr_rnd_t m_getRoundingMode() {
//	enum roundingModeEnum currentRoundingMode = P_ROUNDING_MODE->currentValue.rme;
//	return roundingModeEnumToMpfrRndT(currentRoundingMode);
//}

/**
 * @brief      Gets the parameter from parameter enum.
 *
 * @param[in]  pe    { parameter_description }
 *
 * @return     The parameter corresponding of the given parameter enum. An empty parameter with error at -1 if none was found
 */
struct Param * getParamFromParamEnum(enum ParamEnum pe) {
	struct Param * askedParam;
	switch (pe) {
	case MATRIX_SIZE:
		askedParam = P_MATRIX_SIZE;
		break;
	case NB_ITER:
		askedParam = P_NB_ITER;
		break;
	case MAX_PREC:
		askedParam = P_MAX_PREC;
		break;
	case ROUNDING_MODE:
		askedParam = P_ROUNDING_MODE;
		break;
	case MATRIX_TYPE:
		askedParam = P_MATRIX_TYPE;
		break;
	case PARAM_ENUM_ERROR:
	default:
		askedParam = P_ERROR;
		askedParam->error = -1;
		break;
	}
	return askedParam;
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

char * getParamValueString(const struct Param * param) {
	char * value = malloc(sizeof(char) * 20);
	char * tmpStr;
	switch (param->typ_defaultValue) {
	case DOUBLE:
		sprintf(value, "%f", param->currentValue.d);
		break;
	case MATRIXTYPEENUM:
		tmpStr = getStringFromMatrixTypeEnum(param->currentValue.mte);
		strcpy(value, tmpStr);
		if (value == NULL) {
			printErrorMessage("Unknow matrix type.");
			return NULL;
		}
		free(tmpStr);
		break;
	case LONGINT:
		sprintf(value, "%ld", param->currentValue.li);
		break;
	case SIZE_T:
		sprintf(value, "%zu", param->currentValue.s);
		break;
	case ROUNDINGMODEENUM:
		tmpStr = getStringFromRoundingModeEnum(param->currentValue.rme);
		strcpy(value, tmpStr);
		if (value == NULL) {
			printErrorMessage("Unknow rounding mode.");
			return NULL;
		}
		free(tmpStr);
		break;
	default:
		printErrorMessage("Unknow param type.");
		return NULL;
	}
	return value;
}

/**
 * @brief      schhht
 */
void paramAdressInit() {
	P_MATRIX_SIZE = &_p_m_s;
	P_NB_ITER = &_p_n_i;
	P_MAX_PREC = &_p_m_p;
	P_ROUNDING_MODE = &_p_r_m;
	P_MATRIX_TYPE = &_p_m_t;
	P_ERROR = &_p_e;
}

// ---------------- PRINT ----------------

void printParam(struct Param param) {
	printLine();
	printf("Parameter `%s` (short name `%s`) - ", param.name, param.shortName);
	printf("Default value: ");
	printDefaultValue(param.typ_defaultValue, param.defaultValue);
	printf("\n\t%s", param.description);
}

void printParamEnum(enum ParamEnum pe) {
	printParam(*getParamFromParamEnum(pe));
}

void printParametersFull() {
	printf("\nParameters list : ");
	for (int p = param_min ; p <= param_max ; ++p) {
		printParamEnum(p);
	}
}

void printParametersShort() {
	printf("\nParameters list : ");
	for (int p = param_min ; p <= param_max ; ++p) {
		struct Param param = *getParamFromParamEnum(p);
		printf("\n\t`--%s`(`--%s`)", param.name, param.shortName);
	}
	printf("\n");
}

void printDefaultValue(enum type dvtype, union defaultValueUnion dv) {
	printf("`");
	switch (dvtype) {
	case DOUBLE:
		printf("%F", dv.d);
		break;
	case MATRIXTYPEENUM:
		switch (dv.mte) {
		case EXPONENTIAL:
			printf("EXPONENTIAL");
			break;
		case HILBERT:
			printf("HILBERT");
			break;
		case RANDOM:
			printf("RANDOM");
			break;
		}
		break;
	case LONGINT:
		printf("%li", dv.li);
		break;
	case ROUNDINGMODEENUM:
		switch (dv.rme) {
		case RNDN:
			printf("RNDN");
			break;
		case STOCHASTIC:
			printf("STOCHASTIC");
			break;
		case RNDZ:
			printf("RNDN");
			break;
		case RNDU:
			printf("RNDU");
			break;
		case RNDD:
			printf("RNDD");
			break;
		case RNDA:
			printf("RNDA");
			break;
		default:
			printErrorMessage("\nDefault rounding mode not yet implemented (!?).");
			break;
		}
		break;
	default:
		printErrorMessage("\nUnknow param default value type.");
		break;
	}
	printf("`");
}
