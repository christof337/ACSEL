#include "help.h"

#include <stdio.h>

#include "parameters.h"
#include "utils.c"

/*
 * help.c
 *
 *  Created on: 27 déc. 2017
 *      Author: root
 */

#define HELP_CAPTION "help"

// ------------------------------------------------------------------
// ------------------------------ HELP ------------------------------
// ------------------------------------------------------------------

/**
 * Return 1 is option is equal to HELP_CAPTION, 0 if not
 * @param option the option to test
 * @return 1 if HELP, 0 if not
 */
int isHelp(const char * option) {
	int isHelp = 0;

	char * optionUpper = toUpperCase(option,strlen(option)+1);
	char * helpUpper = toUpperCase(HELP_CAPTION,strlen(HELP_CAPTION)+1);

	if ( strcmp(optionUpper, helpUpper) == 0) {
		isHelp = 1;
	}
	free(optionUpper);
	free(helpUpper);
	return isHelp;
}

/**
 * Print a global help message.
 */
void printHelp() {
	printLine();
	printf("\tHELP");
	printf(
			"\n\t - Please use `%s [--<parameter>=<value>] [--<parameterShortName>=<value>] [...]` to run the program. ",
			globalAppName);
	printf("If a parameter is omitted, the default value will be used.");
	printf("\n\t - Type `%s --help` to print this message", globalAppName);
	printf(
			"\n\t - Type `%s --help <parameter>` to print a help message on how to use this parameter and its values.\n",
			globalAppName);
	printParametersShort();
}

/**
 * Print a help message according to a given string param.
 * @param helpForParam
 * @return
 */
int printNeededHelp(const char * helpForParam) {
	int err = EXIT_SUCCESS;
	// parameter help
	// on essaie de récupérer le paramètre correspondant à la chaine écrite
	enum ParamEnum pe = getParamEnumFromString(helpForParam);
	if (pe != PARAM_ENUM_ERROR) {
		printParamHelp(pe);
	} else {
		fprintf(stderr,"%s is not a valid option.\n",helpForParam);
		err = EXIT_FAILURE;
	}

	return err;
}
void printParamHelp(enum ParamEnum param) {
	printf("Parameter help:");
	printParamEnum(param);
	switch (param) {
	case MODEL:
		// TODO MODEL param help caption
		printf("Help hasn't been implemented for model yet.");
		break;
	case MATRIX_SIZE:
		// TODO matrix size param help caption
		printf("Help hasn't been implemented for matrix size yet.");
		break;
	case NB_ITER:
		// TODO nb iterations param help caption
		printf("Help hasn't been implemented for nb iterations yet.");
		break;
	case MAX_PREC:
		// TODO max precision param help caption
		printf("Help hasn't been implemented for max precision yet.");
		break;
	case ROUNDING_MODE:
		printRoundingModeHelp(*getParamFromParamEnum(param));
		break;
	case MATRIX_TYPE:
		// TODO matrix type param help caption
		printf("Help hasn't been implemented for matrix type yet.");
		break;
	case SIGMA:
		// TODO sigma param help caption
		printf("Help hasn't been implemented for sigma yet.");
		break;
	case RO:
		// TODO RO param help caption
		printf("Help hasn't been implemented for ro yet.");
		break;
	case BETA:
		// TODO BETA param help caption
		printf("Help hasn't been implemented for beta yet.");
		break;
	case PARAM_ENUM_ERROR:
		//error
		break;
	default:
		break;
	}
}

void printRoundingModeHelp(const struct Param pRoundingMode) {
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
	printf("\n\t`%s --%s RNDN`", globalAppName, pRoundingMode.name);
	printf("\n\t`%s --%s STOCHASTIC`\n", globalAppName, pRoundingMode.shortName);
}
