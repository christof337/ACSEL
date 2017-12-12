#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>

void m_init2(mpfr_t value, const mpfr_prec_t precision);

int m_mul(mpfr_t product, const mpfr_t factor1, const mpfr_t factor2, const mpfr_rnd_t roundingMode);

int m_div(mpfr_t quotient, const mpfr_t dividend, const mpfr_t divisor,
		const mpfr_rnd_t roundingMode);

void m_clear(mpfr_t value);

int m_setPrecision(mpfr_t * value, const mpfr_prec_t pre);

int stochasticRounding(mpfr_t * v, const mpfr_prec_t pre);

void m_print(const mpfr_t v);

void m_print_wm(const mpfr_t v, const char * msg);

mpfr_rnd_t m_getRoundingMode();

int getLastDigits(mpfr_t * lastDigits, const mpfr_t valToRound, const long int initialPrecision,
		const long int precisionToRoundTo);

int generateRandomValueInPrecisionRange(mpfr_t * valToRound, const long int precision,
		const mpfr_t maxValueInRange, const int flagSign);

void getMaxValue(mpfr_t * maxValue, const mpfr_prec_t precision);

#endif // CUSTOM_MATH_H
