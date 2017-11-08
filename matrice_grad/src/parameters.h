#ifndef PARAMETERS_H
#define PARAMETERS_H

enum matrixTypeEnum {
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

union defaultValueUnion {
	double d;
	enum matrixTypeEnum mte;
	long int li;
	enum roundingModeEnum rme;
};

enum type {DOUBLE, MATRIXTYPEENUM, LONGINT, ROUNDINGMODEENUM};

struct Param {
   char  name[50];
   char shortName[10];
   enum type typ_defaultValue;
   union defaultValueUnion defaultValue;
   char description[200];
   int error;
};

enum paramsEnum { MATRIX_SIZE, NB_ITER, MAX_PREC, ROUNDING_MODE, MATRIX_TYPE};

int initParams(char * appName) ;

void printParam(struct Param param);

void printLine(); 

void printRoundingModeHelp();

struct Param getParamFromParamEnum(enum paramsEnum pe);

#endif /* PARAMETERS_H */