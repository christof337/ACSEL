#include "parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpfr.h>

#include "tools/utils.h"
#include "tools/errorHandling.h"

#define DEFAULT_MATRIX_SIZE 100
#define DEFAULT_NB_ITER 50
#define DEFAULT_MAX_PREC 75

#define DEFAULT_ROUNDING_MODE RNDN
#define DEFAULT_MATRIX_TYPE EXPONENTIAL

#define HELP_CAPTION "HELP"

struct Param * P_MATRIX_SIZE, *P_NB_ITER, *P_MAX_PREC, *P_ROUNDING_MODE, *P_MATRIX_TYPE;

struct Param _p_m_s, _p_n_i, _p_m_p, _p_r_m, _p_m_t;

char * globalAppName;

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
	P_MATRIX_SIZE->typ_defaultValue = LONGINT;
	P_MATRIX_SIZE->defaultValue.li = DEFAULT_MATRIX_SIZE;
	strcpy(P_MATRIX_SIZE->description, "Define the size of the processed matrix.");
	P_MATRIX_SIZE->error = 0;
	P_MATRIX_SIZE->isDefault = 1;
	P_MATRIX_SIZE->currentValue.li = DEFAULT_MATRIX_SIZE;

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
	strcpy(P_MAX_PREC->shortName, "pre");
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
	int err = 0;
	if (argc > 1) {
		globalAppName = argv[0];
		// one or more argument passed
		char * firstArgTmp = toUpperCase(argv[1], strlen(argv[1]) + 1);
		if (strcmp(firstArgTmp, HELP_CAPTION) == 0) {
			// HELP
			err = 1;
			if (argc == 2) {
				// casual help
				printHelp();
			} else if (argc == 3) {
				// parameter help
				char * paramName = argv[2];
				// on essaie de récupérer le paramètre correspondant à la chaine écrite
				enum ParamEnum pe = getParamEnumFromString(paramName);
				if (pe != PARAM_ENUM_ERROR) {
					printParamHelp(pe);
				} else {
					err = ERROR_WHILE_HANDLING_INPUT_PARAMETERS;
					printCustomError(err, 1, globalAppName);
				}
			} else {
				// typo while asking for help
				err = ERROR_WHILE_HANDLING_INPUT_PARAMETERS;
				printCustomError(err, 1, globalAppName);
			}
		} else {
			int i = 1;
			while (err == 0 && i < argc) {
				char * currentStr = argv[i];
				if (strchr(currentStr, '=') == NULL) {
					// the string does not contain an "=" : error
					err = ERROR_NO_EQUAL_SIGN_IN_PARAMETER;
					printCustomError(err, 2, globalAppName, currentStr);
				} else {
					// test if the string contains =
					char ** tmp = str_split(currentStr, '=');
					char * parameterStr = tmp[0];
					char * value = tmp[1];
					enum ParamEnum pe = getParamEnumFromString(parameterStr);
					if (pe == PARAM_ENUM_ERROR) {
						// error
						err = ERROR_WRONG_PARAMETER_GIVEN;
						printCustomError(err, 2, globalAppName, parameterStr);
					} else {
						struct Param * param = getParamFromParamEnum(pe);
						int hasAssigned = assignValueToParam(param, value);
						if (hasAssigned == -1) {
							// wrong value
							err = ERROR_WRONG_VALUE_GIVEN;
							printCustomError(err, 3, globalAppName, param->name, value);
						} else {
							// value assigned : everything's fine
							printf("\n\t Parameter %s has been assigned with the value `%s`.",
									param->name, value);
							param->isDefault = 0;
						}
					}

					free(tmp);
				}

				++i;
			}
		}
		free(firstArgTmp);
	} else {
		// no argument given
		// default values will be used
		err = 0;
	}

	return err;
}

int assignValueToParam(struct Param * param, char * strValue) {
	int err = 0;
	int res;
	double dou;
	long int li;
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
		} else {
			// error
			err = -1;
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
		if (strcmp(valueUp, "RNDN") == 0) {
			param->currentValue.rme = RNDN;
		} else if (strcmp(valueUp, "STOCHASTIC") == 0) {
			param->currentValue.rme = STOCHASTIC;
		} else if (strcmp(valueUp, "RNDZ") == 0) {
			param->currentValue.rme = RNDZ;
		} else if (strcmp(valueUp, "RNDU") == 0) {
			param->currentValue.rme = RNDU;
		} else if (strcmp(valueUp, "RNDD") == 0) {
			param->currentValue.rme = RNDD;
		} else if (strcmp(valueUp, "RNDA") == 0) {
			param->currentValue.rme = RNDA;
		} else {
			// error
			err = -1;
		}
		break;
	default:
		//erreur
		err = -1;
		break;
	}
	free(valueUp);
	return err;
}

/* MAPPERS */
enum ParamEnum getParamEnumFromString(char * paramName) {
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
enum roundingModeEnum stringToRoundingModeEnum(char * string, const int size) {
	enum roundingModeEnum res = -1;

	char * str = toUpperCase(string, size);

	if (strcmp(str, "RNDN") == 0) {
		res = RNDN;
	} else if (strcmp(str, "STOCHASTIC") == 0) {
		res = -1; // NOT IMPLEMENTED YET
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

mpfr_rnd_t roundingModeEnumToMpfrRndT(enum roundingModeEnum e) {
	mpfr_rnd_t mpfr_rnd;
	switch (e) {
	case RNDN:
		mpfr_rnd = MPFR_RNDN; // round to nearest (roundTiesToEven in IEEE 754-2008)
		break;
		// case STOCHASTIC:
		// mpfr_rnd = pasCodé; // round randomly to toward plus infinity or toward minus infinity,
		// the more close it is from the rounded value, the more probability
		// to round to this value.
		// break;
	case RNDZ:
		mpfr_rnd = MPFR_RNDZ; // round toward zero (roundTowardZero in IEEE 754-2008)
		break;
	case RNDU:
		mpfr_rnd = MPFR_RNDU; // round toward plus infinity (roundTowardPositive in IEEE 754-2008)
		break;
	case RNDD:
		mpfr_rnd = MPFR_RNDD; //round toward minus infinity (roundTowardNegative in IEEE 754-2008)
		break;
	case RNDA:
		mpfr_rnd = MPFR_RNDA; // round toward minus infinity (roundTowardNegative in IEEE 754-2008)
		break;
	default:
		mpfr_rnd = roundingModeEnumToMpfrRndT(DEFAULT_ROUNDING_MODE);
		break;
	}
	return mpfr_rnd;
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
		askedParam->error = -1;
		break;
	}
	return askedParam;
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
		printf("\n\t`%s`(`%s`)", param.name, param.shortName);
	}
	printf("\n");
}

// ------------------------------------------------------------------
// ------------------------------ HELP ------------------------------
// ------------------------------------------------------------------
// TODO : externalize "help.c" as a independent file

void printHelp() {
	printLine();
	printf("\tHELP");
	printf(
			"\n\t - Please use `%s [<parameter>=<value>][<parameter>=<value>]...` to run the program. ",
			globalAppName);
	printf("If a parameter is omitted, the default value will be used.");
	printf("\n\t - Type `%s help` to print this message", globalAppName);
	printf(
			"\n\t - Type `%s help <parameter>` to print a help message on how to use this parameter and its values.\n",
			globalAppName);
	printParametersShort();
}

void printParamHelp(enum ParamEnum param) {
	printf("Parameter help:");
	printParamEnum(param);
	switch (param) {
	case MATRIX_SIZE:
		// TODO
		break;
	case NB_ITER:
		// TODO
		break;
	case MAX_PREC:
		// TODO
		break;
	case ROUNDING_MODE:
		printRoundingModeHelp();
		break;
	case MATRIX_TYPE:
		// TODO
		break;
	case PARAM_ENUM_ERROR:
		//error
		break;
	default:
		break;
	}
}

void printRoundingModeHelp() {
	printLine();
	printf("The following six rounding modes are supported:\n");
	printf(
			"\t- `STOCHASTIC`: round randomly to toward plus infinity or toward minus infinity, the more close it is from the rounded value, the more probability to round to this value.\n");
	printf("\t- `RNDN`: ound to nearest (roundTiesToEven in IEEE 754-2008),\n");
	printf("\t- `RNDZ`: round toward zero (roundTowardZero in IEEE 754-2008),\n");
	printf("\t- `RNDU`: round toward plus infinity (roundTowardPositive in IEEE 754-2008),\n");
	printf("\t- `RNDD`: round toward minus infinity (roundTowardNegative in IEEE 754-2008),\n");
	printf("\t- `RNDA`: round away from zero.\n");
	printf("\nUsage example :");
	printf("\n\t`%s %s=RNDN`", globalAppName, P_ROUNDING_MODE->name);
	printf("\n\t`%s %s=STOCHASTIC`\n", globalAppName, P_ROUNDING_MODE->shortName);
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
