/*
 * readOutputFile.h
 *
 *  Created on: 4 janv. 2018
 *      Author: root
 */

#ifndef READOUTPUTFILE_H_
#define READOUTPUTFILE_H_

enum parameterOrderEnum {
	param_min = 0,
	VALUE_TREATED = param_min,
	MATRIX_SIZE,
	NB_ITER,
	MAX_PREC,
	ROUNDING_MODE, // add params before this comment
	MATRIX_TYPE,
	param_max = MATRIX_TYPE,
	PARAM_ENUM_ERROR
};

enum matrixTypeEnum {
	RANDOM,
	EXPONENTIAL,
	HILBERT
};

enum roundingModeEnum {
	RNDN, // round to nearest (roundTiesToEven in IEEE 754-2008),
	STOCHASTIC, // custom ;)
	RNDZ, // round toward zero (roundTowardZero in IEEE 754-2008),
	RNDU, // round toward plus infinity (roundTowardPositive in IEEE 754-2008),
	RNDD, // round toward minus infinity (roundTowardNegative in IEEE 754-2008),
	RNDA  // round away from zero.
};

enum valueTreatedEnum {
	GKGK2
};

int extractParamsFromFileName(const char * fileName, enum valueTreatedEnum * valueTreated,
		long int * matrixSize, long int * numberOfIterations, long int * precisionMaxTreated,
		enum roundingModeEnum * roundingMode, enum matrixTypeEnum * matrixType);

void parametersPrint(enum roundingModeEnum roundingMode, enum matrixTypeEnum matrixType,
		enum valueTreatedEnum valueTreated, long int matrixSize, long int numberOfIterations,
		long int precisionMaxTreated);

char * getStringFromRoundingModeEnum(const enum roundingModeEnum rme);

char * getStringFromMatrixTypeEnum(const enum matrixTypeEnum mte) ;

char * getStringFromValueTreatedEnum(const enum valueTreatedEnum vte);

#endif /* READOUTPUTFILE_H_ */
