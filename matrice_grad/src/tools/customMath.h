#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>


void m_init2(mpfr_t value, mpfr_prec_t precision);

int m_mul(mpfr_t product, mpfr_t factor1, mpfr_t factor2, mpfr_rnd_t roundingMode) ;

int m_div(mpfr_t quotient, mpfr_t dividend, mpfr_t divisor, mpfr_rnd_t roundingMode) ;

void m_clear(mpfr_t value);

int stochasticRounding(mpfr_t * v, mpfr_prec_t pre);

void m_print(mpfr_t v);

void m_print_wm(mpfr_t v, char * msg);

mpfr_rnd_t m_getRoundingMode();

int getLastDigits(mpfr_t * lastDigits, long int initialPrecision, long int precisionToRoundTo, mpfr_t valToRound);

int generateRandomValueInPrecisionRange(mpfr_t * valToRound,
		long int precision, mpfr_t maxValueInRange, int flagSign);

int m_setPrecision(mpfr_t * v, mpfr_prec_t pre);

void getMaxValue(mpfr_t * maxValue, mpfr_prec_t precision);

#endif // CUSTOM_MATH_H
