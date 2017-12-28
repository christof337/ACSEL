#include "log.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <mpfr.h>

#include "tools/errorHandling.h"
#include "tools/inputOutput.h"
#include "parameters.h"

/*
 * log.c
 *
 *  Created on: 26 déc. 2017
 *      Author: root
 */

#define LOG_FOLDER "log"
#define LOG_PREFIX "log"
#define LOG_SUFFIX ".log"

#ifndef DEBUG
#define DEBUG 0
#endif /* DEBUG */

FILE ** logFiles = NULL;

char * buildLogPrefixFromParams() {
	char * logFileNamePrefix = buildPrefixFromParams();
	if (logFileNamePrefix != NULL) {
		char * tmp = malloc(sizeof(char)*100);
		sprintf(tmp, "%s/%s%s", LOG_FOLDER, LOG_PREFIX, logFileNamePrefix);
		strcpy(logFileNamePrefix,tmp);
		free(tmp);
	} else {
		printErrorMessage("Error while building log file prefix.");
	}
	return logFileNamePrefix;
}

char * buildPrefixFromParams() {
	char * fileNamePrefix;

	fileNamePrefix = malloc(sizeof(char)*100);
	strcpy(fileNamePrefix,"");
	if(fileNamePrefix != NULL) {
		for (int p = param_min ; p <= param_max ; ++p) {
			struct Param * param = getParamFromParamEnum(p);
			sprintf(fileNamePrefix, "%s_%s=%s", fileNamePrefix, param->shortName,
					getParamValueString(param));
		}
	}
	return fileNamePrefix;
}

char * buildLogSuffix() {
	char * suffix = malloc(sizeof(char)*strlen(LOG_SUFFIX));
	strcpy(suffix,LOG_SUFFIX);
	return suffix;
}

/**
 * Init log files from parameters value.
 * @return
 */
int initLogFiles() {
	int res = 0;

	// getting the number of files
	long int nbPrec = getParamFromParamEnum(MAX_PREC)->currentValue.li - MPFR_PREC_MIN+1;

	// getting the address of the log files array
	if (allocateLogFilesArray(nbPrec) != 0) {
		printErrorMessage("Error while allocating the log files");
		res = -1;
	} else {
		if (logFiles == NULL) {
			// error when initializing the log file array
			res = errno;
		} else {
			// building prefix and suffix
			char * prefix;
			prefix = buildLogPrefixFromParams();
			char * suffix;
			suffix = buildLogSuffix();

			// opening all the logFiles
			for (long int i = 0 ; i < nbPrec ; ++i) {
				char * logFileName;
				logFileName = getFileNameFromPrecision(prefix, suffix, i+MPFR_PREC_MIN);
				logFiles[i] = openLog(logFileName);
				if (logFiles[i] == NULL) {
					res = -1;
				}
				free(logFileName);
			}
			free(prefix);
			free(suffix);
		}
	}

	return res;
}

int closeLogFiles() {
	int res = 0;

	long int nbPrec = getParamFromParamEnum(MAX_PREC)->currentValue.li - MPFR_PREC_MIN;

	for (long int i = 0 ; i < nbPrec ; ++i) {
		res += closeLog(logFiles[i]);
	}

	return res;
}

FILE * openLog(const char * fileName) {
	FILE * file;
	int errnum;
	file = fopen(fileName, "w+");

	if (file == NULL) {
		// failed to open file
		errnum = errno;
		printError(errnum);
	}

	return file;
}

void m_log(const long int currentPrecision, const char * str) {
	size_t index;
	index = getLogFileIndexFromCurrentPrecision(currentPrecision);
	if (logFiles[index] != NULL) {
		fprintf(logFiles[index], "[INFO] - %s\n", str);
	}
}

void m_log_err(const long int currentPrecision, const char * str) {
	size_t index;
	index = getLogFileIndexFromCurrentPrecision(currentPrecision);
	if (logFiles[index] != NULL) {
		fprintf(logFiles[index], "[ERROR] - %s\n", str);
	}
	if ( DEBUG > 0) {
		char logMsg[1000];
		sprintf(logMsg,"(%ld)[ERROR] - %s",currentPrecision,str);
		printErrorMessage(logMsg);
		printf("\n4- log msg\n");
		free(logMsg);
	}
}

int closeLog(FILE * fileToClose) {
	if (fileToClose != NULL) {
		fclose(fileToClose);
		return 0;
	} else {
		errorHandling();
		return -1;
	}
}

int allocateLogFilesArray(const long int nbPrecisionTreated) {
	int res = 0;
	if (logFiles == NULL) {
		logFiles = malloc(sizeof(FILE*) * nbPrecisionTreated);
		if (logFiles == NULL) {
			int errnum = errno;
			printError(errnum);
			res = -1;
		}
	}
	return res;
}

size_t getLogFileIndexFromCurrentPrecision(long int precision) {
	return precision - MPFR_PREC_MIN;
}
