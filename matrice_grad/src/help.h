/*
 * help.h
 *
 *  Created on: 27 déc. 2017
 *      Author: root
 */

#ifndef HELP_H_
#define HELP_H_

#include "parameters.h"

// HELP
int isHelp(const char * option);

void printHelp();

int printNeededHelp(const char * helpForParam);

void printParamHelp(enum ParamEnum param);

void printRoundingModeHelp(const struct Param pRoundingMode);

#endif /* HELP_H_ */
