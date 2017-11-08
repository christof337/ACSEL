#include "parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpfr.h>
#include <ctype.h>

#include "tools/utils.h"
#include "tools/errorHandling.h"

#define DEFAULT_MATRIX_SIZE 100.0
#define DEFAULT_NB_ITER 50.0
#define DEFAULT_MAX_PREC 50

#define DEFAULT_ROUNDING_MODE RNDN
#define DEFAULT_MATRIX_TYPE EXPONENTIAL


struct Param P_MATRIX_SIZE, P_NB_ITER, P_MAX_PREC, P_ROUNDING_MODE, P_MATRIX_TYPE;

int initParams(char * appName) {
	char tmp[200];

	// MATRIX_SIZE
	strcpy( P_MATRIX_SIZE.name, "matrixSize");
   	strcpy( P_MATRIX_SIZE.shortName, "ms");
   	P_MATRIX_SIZE.typ_defaultValue = DOUBLE;
   	P_MATRIX_SIZE.defaultValue.d = DEFAULT_MATRIX_SIZE;
   	strcpy( P_MATRIX_SIZE.description, "Define the size of the processed matrix.");
   	P_MATRIX_SIZE.error = 0;
   	
	// NB_ITER
	strcpy( P_NB_ITER.name, "nbIter");
   	strcpy( P_NB_ITER.shortName, "ni");
   	P_NB_ITER.typ_defaultValue = DOUBLE;
   	P_NB_ITER.defaultValue.d = DEFAULT_NB_ITER;
   	strcpy( P_NB_ITER.description, "Define the number of iterations made to minimize the matrix.");
   	P_NB_ITER.error = 0;

	// MAX_PREC
	strcpy( P_MAX_PREC.name, "maxPrecision");
   	strcpy( P_MAX_PREC.shortName, "pre");
   	P_MAX_PREC.typ_defaultValue = LONGINT;
   	P_MAX_PREC.defaultValue.li = DEFAULT_MAX_PREC;
   	strcpy( P_MAX_PREC.description, "Define the maximum precision up until the program will process (from 2 to maxPrecision)");
   	P_MAX_PREC.error = 0;

	// ROUNDING_MODE
	strcpy( P_ROUNDING_MODE.name, "roundingMode");
   	strcpy( P_ROUNDING_MODE.shortName, "rm");
   	P_ROUNDING_MODE.typ_defaultValue = ROUNDINGMODEENUM;
   	P_ROUNDING_MODE.defaultValue.rme = DEFAULT_ROUNDING_MODE;
	sprintf(tmp,"Define the rounding mode used for the computations of the program.\nFor more information about the different rounding mode handled, type `%s help roundingModes`",appName);
   	strcpy( P_ROUNDING_MODE.description, tmp);
   	P_ROUNDING_MODE.error = 0;


	// MATRIX_TYPE
	strcpy( P_MATRIX_TYPE.name, "matrixType");
   	strcpy( P_MATRIX_TYPE.shortName, "mt");
   	P_MATRIX_TYPE.typ_defaultValue = MATRIXTYPEENUM;
   	P_MATRIX_TYPE.defaultValue.mte = DEFAULT_MATRIX_TYPE;
   	sprintf(tmp,"Define the way the processed matrix is filled.\nFor more information about the different matrix types handled, type `%s help matrixTypes`",appName);
   	strcpy(P_MATRIX_TYPE.description, tmp);
   	P_MATRIX_TYPE.error = 0;

}

void printParam(struct Param param) {
	printLine();
	printf("Paramètre %s :\n",param.name);
	printf("\nShort name : %s",param.shortName);
	printf("\tValeur par défaut : ");
	switch(param.typ_defaultValue) {
		case DOUBLE:
 			printf("%F",param.defaultValue.d);
 			break;
		case MATRIXTYPEENUM:
			switch(param.defaultValue.mte) {
				case EXPONENTIAL:
 					printf("EXPONENTIAL");
 					break;
 				case HILBERT:
 					printf("HILBERT");
 					break;
			}
 			break;
		case LONGINT:
 			printf("%li",param.defaultValue.li);
		case ROUNDINGMODEENUM:
			switch(param.defaultValue.rme) {
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
	printf("\n");
 	printf("\tDecription : %s\n", param.description);
}

void printLine() {
	printf("\n-----------\n");
}

void printRoundingModeHelp() {
	printLine();
	printf("The following five rounding modes are supported:\n");
    printf("\t- STOCHASTIC\t:\tround randomly to toward plus infinity or toward minus infinity, the more close it is from the rounded value, the more probability to round to this value.\n");
    printf("\t- RNDN\t:\tround to nearest (roundTiesToEven in IEEE 754-2008),\n");
    printf("\t- RNDZ\t:\tround toward zero (roundTowardZero in IEEE 754-2008),\n");
    printf("\t- RNDU\t:\tround toward plus infinity (roundTowardPositive in IEEE 754-2008),\n");
    printf("\t- RNDD\t:\tround toward minus infinity (roundTowardNegative in IEEE 754-2008),\n");
    printf("\t- RNDA\t:\tround away from zero.\n");
}

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

	if(strcmp(str,"RNDN")==0) {
		res = RNDN;
	} else if (strcmp(str,"STOCHASTIC")==0) {
		res = -1; // NOT IMPLEMENTED YET
	} else if (strcmp(str,"RNDZ")==0) {
		res = RNDZ;
	} else if (strcmp(str,"RNDU")==0) {
		res = RNDU;
	} else if (strcmp(str,"RNDD")==0) {
		res = RNDD;
	} else if (strcmp(str,"RNDA")==0) {
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
}

/**
 * @brief      Gets the parameter from parameter enum.
 *
 * @param[in]  pe    { parameter_description }
 *
 * @return     The parameter corresponding of the given parameter enum. An empty parameter with error at -1 if none was found
 */
struct Param getParamFromParamEnum(enum paramsEnum pe) {
	struct Param askedParam;
	switch(pe) {
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
			askedParam = P_ROUNDING_MODE;
			break;
		default:
			askedParam.error = -1;
			break;
	}
	return askedParam;
}