
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#include "parameters.h"

/*
 * log.h
 *
 *  Created on: 26 déc. 2017
 *      Author: root
 */

char * buildPrefixFromParams(const enum modelEnum me);

char * buildLogPrefixFromParams(const enum modelEnum me);

char * buildLogSuffix();

int initLogFiles(const enum modelEnum me);

int closeLogFiles();

FILE * openLog(const char * fileName);

void m_log(const long int currentPrecision, const char * str);

void m_log_err(const long int currentPrecision, const char * str);

int closeLog(FILE * fileToClose);

int allocateLogFilesArray(const long int nbPrecisionTreated);

size_t getLogFileIndexFromCurrentPrecision(long int precision);

int closeLogFromPrecision(long int precision);

#endif /* LOG_H_ */
