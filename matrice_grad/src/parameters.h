#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <mpfr.h>

/**
 * @brief      List the different matrix types handled by the program
 */
enum matrixTypeEnum {
	EXPONENTIAL,
	HILBERT
};

/**
 * @brief      List the different rounding mode types handled by the program
 */
enum roundingModeEnum {
	RNDN, // round to nearest (roundTiesToEven in IEEE 754-2008),
	STOCHASTIC, // custom ;)
	RNDZ, // round toward zero (roundTowardZero in IEEE 754-2008),
	RNDU, // round toward plus infinity (roundTowardPositive in IEEE 754-2008),
	RNDD, // round toward minus infinity (roundTowardNegative in IEEE 754-2008),
	RNDA  // round away from zero.
};

/**
 * @brief      Union used to access the default value, which can have different type depending on the parameter used
 */
union defaultValueUnion {
	double d;
	enum matrixTypeEnum mte;
	long int li;
	enum roundingModeEnum rme;
};

/**
 * @brief      Enum listing the different types of the default value of the params
 */
enum type {
	DOUBLE,
	MATRIXTYPEENUM,
	LONGINT,
	ROUNDINGMODEENUM
};

/**
 * @brief      Main structure of this file. Contains all of the fields used to
 *             write and access the command line parameters of the program.
 *             Handle the default values.
 */
struct Param {
	char name[50];
	char shortName[10];
	enum type typ_defaultValue;
	union defaultValueUnion defaultValue;
	char description[200];
	int error;
	unsigned int isDefault :1;
	union defaultValueUnion currentValue;
};

/**
 * @brief      List the different parameters used by this program.
 * param_min and param_max are used to loop through the enum
 */
enum ParamEnum {
	param_min,
	MATRIX_SIZE = param_min,
	NB_ITER,
	MAX_PREC,
	ROUNDING_MODE, // add params before this comment
	MATRIX_TYPE,
	param_max = MATRIX_TYPE,
	PARAM_ENUM_ERROR
};

int initParams(char * appName);

int handleParams(int argc, char *argv[]);

int assignValueToParam(struct Param * param, char * strValue);

struct Param * getParamFromParamEnum(enum ParamEnum pe);

enum ParamEnum getParamEnumFromString(char * paramName);

void paramAdressInit();

// ROUNDING MODE
enum roundingModeEnum stringToRoundingModeEnum(char * string, const int size);

mpfr_rnd_t roundingModeEnumToMpfrRndT(enum roundingModeEnum e);

// mpfr_rnd_t m_getRoundingMode();

// DISPLAY
void printParam(struct Param param);

void printParametersFull();

void printParametersShort();

void printParamEnum(enum ParamEnum pe);

void printDefaultValue(enum type dvtype, union defaultValueUnion dv);

// HELP

void printHelp();

void printParamHelp(enum ParamEnum param);

void printRoundingModeHelp();

#endif /* PARAMETERS_H */
