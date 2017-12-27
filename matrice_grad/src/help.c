#include "help.h"
#include "parameters.h"

#include <stdio.h>

/*
 * help.c
 *
 *  Created on: 27 déc. 2017
 *      Author: root
 */

// ------------------------------------------------------------------
// ------------------------------ HELP ------------------------------
// ------------------------------------------------------------------

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
		// TODO matrix size param help caption
		break;
	case NB_ITER:
		// TODO nb iterations param help caption
		break;
	case MAX_PREC:
		// TODO max precision param help caption
		break;
	case ROUNDING_MODE:
		printRoundingModeHelp(*getParamFromParamEnum(param));
		break;
	case MATRIX_TYPE:
		// TODO matrix type param help caption
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
	printf("\n\t`%s %s=RNDN`", globalAppName, pRoundingMode.name);
	printf("\n\t`%s %s=STOCHASTIC`\n", globalAppName, pRoundingMode.shortName);
}
