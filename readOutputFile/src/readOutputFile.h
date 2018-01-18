/*
 * readOutputFile.h
 *
 *  Created on: 4 janv. 2018
 *      Author: root
 */

#ifndef READOUTPUTFILE_H_
#define READOUTPUTFILE_H_

#include "customMath.h"

/**
 * @brief      List the different parameters used by this program.
 * param_min and param_max are used to loop through the enum
 */
enum parameterOrderEnum {
	param_min,
	VALUE_TREATED = param_min,
	MATRIX_SIZE,
	MATRIX_TYPE,
	MAX_PREC,
	NB_ITER,
	ROUNDING_MODE, // add params before this comment
	SIGMA,
	RO,
	BETA,
	param_max = BETA,
	PARAM_ENUM_ERROR,
	param_min_cgd = MATRIX_SIZE,
	param_max_cgd = ROUNDING_MODE,
	param_min_lorenz = MAX_PREC,
	param_max_lorenz = BETA
};

enum matrixTypeEnum {
	RANDOM,
	EXPONENTIAL,
	HILBERT
};

//enum roundingModeEnum {
//	RNDN, // round to nearest (roundTiesToEven in IEEE 754-2008),
//	STOCHASTIC, // custom ;)
//	RNDZ, // round toward zero (roundTowardZero in IEEE 754-2008),
//	RNDU, // round toward plus infinity (roundTowardPositive in IEEE 754-2008),
//	RNDD, // round toward minus infinity (roundTowardNegative in IEEE 754-2008),
//	RNDA  // round away from zero.
//};

enum valueTreatedEnum {
	vte_GKGK2,
	vte_SIMPLE_GKGK2,
	vte_LORENZ
};

int extractParamsFromFileName(const char * fileName, enum valueTreatedEnum * valueTreated,
		long int * matrixSize, long int * numberOfIterations, long int * precisionMaxTreated,
		enum roundingModeEnum * roundingMode, enum matrixTypeEnum * matrixType, double * sigma,
		double * ro, double * beta);

void parametersPrint(enum roundingModeEnum roundingMode, enum matrixTypeEnum matrixType,
		enum valueTreatedEnum valueTreated, long int matrixSize, long int numberOfIterations,
		long int precisionMaxTreated);

int fillProgressivePrecisionArrayFromFile(const char * fileName, const size_t m, const size_t n,
		mpfr_t (**arrayToFill)[m][n], const mpfr_prec_t precisionMax);

int fillProgressivePrecisionArrayFromSimpleFile(const char * fileName, const size_t n,
		mpfr_t (**arrayToFill)[n]);

int getLastElements(size_t m, mpfr_t (**lastElements)[m], size_t n, mpfr_t (*array)[m][n]);

void printMinimums(int nbMin, size_t minIndexes[nbMin]);

char* removePath(const char* fileName);

char * getRNDNFileNameFromStochasticFileName(const char * stochasticFileName);

int writeDifferenceStochasticToRndnInFile(const size_t numberOfPrecisionTreated,
		const size_t numberOfIterations,
		const mpfr_t (*stochasticArray)[numberOfPrecisionTreated][numberOfIterations],
		const mpfr_t (*RNDNArray)[numberOfPrecisionTreated][numberOfIterations],
		const char * stochasticFileName, const mpfr_prec_t precisionMax);

int writeDifferenceStochasticToSimpleRndnInFile(const size_t numberOfPrecisionTreated,
		const mpfr_t (*stochasticArray)[numberOfPrecisionTreated],
		const mpfr_t (*RNDNArray)[numberOfPrecisionTreated], const char * stochasticFileName,
		const mpfr_prec_t precisionMax);

char * getStringFromRoundingModeEnum(const enum roundingModeEnum rme);

char * getStringFromMatrixTypeEnum(const enum matrixTypeEnum mte);

char * getStringFromValueTreatedEnum(const enum valueTreatedEnum vte);

#endif /* READOUTPUTFILE_H_ */
