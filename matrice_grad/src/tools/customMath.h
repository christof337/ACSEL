#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>

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

long int NB_STOCH_ROUND;

int m_mul(mpfr_t product, const mpfr_t factor1, const mpfr_t factor2, const enum roundingModeEnum roundingMode);

int m_mul_si(mpfr_t product, const mpfr_t factor1, long int factor2, const enum roundingModeEnum roundingMode);

int m_div(mpfr_t quotient, const mpfr_t dividend, const mpfr_t divisor,
		const enum roundingModeEnum roundingMode);

int m_add(mpfr_t summation, const mpfr_t addend1, const mpfr_t addend2,
		const enum roundingModeEnum roundingMode);

int m_sub(mpfr_t difference, const mpfr_t minuend, const mpfr_t substrahend,
		const enum roundingModeEnum roundingMode);

int m_pow(mpfr_t res, const mpfr_t val, const mpfr_t exp, const enum roundingModeEnum roundingMode);

void handleExtendedRounding(mpfr_t longValue1, mpfr_t longValue2, mpfr_t longResult,
		const mpfr_t shortValue1, const mpfr_t shortValue2);

void m_init2(mpfr_t value, const mpfr_prec_t precision);

void m_clear(mpfr_t value);

int m_setPrecision(mpfr_t * value, const mpfr_prec_t pre);
int m_setPrecisionWithRoundingMode(mpfr_t * value, const mpfr_prec_t pre, const mpfr_rnd_t roundingMode);

int stochasticRounding(mpfr_t * v, const mpfr_prec_t pre);

mpfr_rnd_t m_getRoundingMode();

int getLastDigits(mpfr_t * lastDigits, const mpfr_t valToRound, const long int initialPrecision,
		const long int precisionToRoundTo);

int generateRandomValueInPrecisionRange(mpfr_t * valToRound, const long int precision,
		const mpfr_t maxValueInRange, const int flagSign);

void getMaxValue(mpfr_t * maxValue, const mpfr_prec_t precision);

mpfr_rnd_t roundingModeEnumToMpfrRndT(enum roundingModeEnum e);

void m_print(const mpfr_t v);

void m_print_wm(const mpfr_t v, const char * msg);

#endif // CUSTOM_MATH_H
