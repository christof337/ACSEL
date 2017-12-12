
#include <stdio.h>
#include <mpfr.h>

#include "customMath.h"

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef max
#define max(A,B) A>B?A:B
#endif

#include "utils.h"

/* --------------------- MPFR notes --------------------- 
mode d'arrondi : MPFR_RNDN : round to nearest : mode par défaut.
Désormais, possibilité d'utiliser l'arrondi stochastique.
*/

/**
 * Initialize the value with the given precision
 * Each variable initialized in this way must be freed afterwards.
 * @param value the reference of the value to initialize according to MPFR standards
 * @param precision the precision to initialize the value with
 */
void m_init2(mpfr_t value, mpfr_prec_t precision) {
	mpfr_init2(value,precision);
}

/**
 * @brief      Multiply factor1 and factor2 and put the product in product.
 *
 * @param[out] product       The product
 * @param[in]  factor1       The factor 1
 * @param[in]  factor2       The factor 2
 * @param[in]  roundingMode  The rounding mode
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int m_mul(mpfr_t product, mpfr_t factor1, mpfr_t factor2, mpfr_rnd_t roundingMode) {
	return mpfr_mul(product, factor1, factor2, roundingMode);
}

 /**
  * @brief      Divide dividend by divisor and put the quotient in quotient.
  *
  * @param[out]	quotient		The quotient
  * @param[in]	dividend		The dividend
  * @param[in]	divisor			The divisor
  * @param[in]	roundingMode	The rounding mode
  * @return		0 if rounded exactly, > 0 if globally rounded upwards the exact
  *             values, < 0 if globally rounded downwards the exact values
  */
int m_div(mpfr_t quotient, mpfr_t dividend, mpfr_t divisor, mpfr_rnd_t roundingMode) {
	return mpfr_div(quotient, dividend, divisor, roundingMode);
}

/**
 * @brief	Clear the value according to mpfr standards.
 * 			Each variable must be freed afterwards.
 * 			Cannot use the value after this point.
 * @param	value 	the value to clear.
 */
void m_clear(mpfr_t value) {
	mpfr_clear(value);
}

/**
 * Increase the precision of v, keeping the previous value
 * @param v
 * @param pre
 * @return
 */
int m_setPrecision(mpfr_t * v, mpfr_prec_t pre) {
	int roundingDirection=0;
	mpfr_t result;
	m_init2(result, pre);
	mpfr_set(result, *v, MPFR_RNDN);
	//roundingDirection = mpfr_prec_round(result, pre, MPFR_RNDN);
	mpfr_set_prec(*v, pre);
	mpfr_set(*v, result, MPFR_RNDN);
	m_clear(result);
	return roundingDirection;
}

/**
 *	Apply a randomized stochastic rounding to the value `v` at the precision `pre`
 * @param v		The value to round
 * @param pre	The precision to round to
 * @return		0 if rounded exactly, > 0 if globally rounded upward the exact
 *             	value, < 0 if globally rounded downward the exact value
 */
int stochasticRounding(mpfr_t * v, mpfr_prec_t pre)
{
	if(DEBUG) m_print_wm((*v),"\t\tRounding  `v`=");
	if(DEBUG) printf(" at precision %ld",pre);

	int roundingDirection = 0;

	mpfr_prec_t currentPrecision = mpfr_get_prec(*v);
	if(DEBUG) printf("\t Current precision is %ld",currentPrecision);

	// v is a number of `currentPrecision` bits.
	// res must be the value of `v` with precision `pre` ; rounded with stochastic rounding
	if( currentPrecision <= pre ) {
		if(DEBUG) printf("\n\tCurrent precision (%ld) is lower than asked precision (%ld) ; exiting without rouding...",currentPrecision,pre);
		roundingDirection = m_setPrecision(v,pre);
		//roundingDirection = mpfr_prec_round(*v,pre, MPFR_RNDN); // no problem in using RNDN ; because no rounding will be made
		if(DEBUG) m_print_wm(*v,"\n\tResult is :");
		printf("\n");
	} else {
		long int lastDigitPrecision = max((currentPrecision - pre ),MPFR_PREC_MIN);
		// v is longer than the asked precision
		mpfr_t lastDigits;
		getLastDigits(&lastDigits,currentPrecision,pre,*v);

		// generate a random value between -0.5 and 0.5
		// add this value to lastDigits
		// round to nearest lastDigits

		// --- OR ---

		// equivalent to generate a random value between 0 and 1
		mpfr_t randomValue;
		m_init2(randomValue,lastDigitPrecision);
		do {
			setRandomValue(&randomValue);
			// and see if it is greater than lastDigits or not
			// if it is, round down, if it is not, round up
			if ( mpfr_greater_p ( lastDigits , randomValue ) ) {
				// rounding up
				if(DEBUG) printf("\tROUND UP");
				roundingDirection = mpfr_prec_round( *v , pre, MPFR_RNDU );
				roundingDirection = 1;
			} else {
				// rounding down
				if(DEBUG && !mpfr_equal_p(randomValue,lastDigits)) printf("\tROUND DOWN");
				roundingDirection = mpfr_prec_round( *v , pre, MPFR_RNDD );
				roundingDirection = -1;
			}
		} while ( mpfr_equal_p(randomValue,lastDigits) );

		m_clear(lastDigits);
		m_clear(randomValue);
		//m_clear(mpfr_lastDigits);
	}

	return roundingDirection;
}

/**
 * // FIXME m_getRoundingMode
 * @return
 */
mpfr_rnd_t m_getRoundingMode() {
	return MPFR_RNDN;
}

/**
 * Return the digits after the "precisionToRoundTo"
 * @param lastDigits 			The output value. Is initialized during function.
 * @param initialPrecision		The precision of valToRound
 * @param precisionToRoundTo	The precision from which we want the lastDigits to start
 * @param valToRound			The value to extract the digits of
 * @return
 */
int getLastDigits(mpfr_t * lastDigits, long int initialPrecision,
		long int precisionToRoundTo, mpfr_t valToRound) {
	m_init2(*lastDigits,
			max((initialPrecision - precisionToRoundTo), MPFR_PREC_MIN));
	mpfr_t tempRound;
	m_init2(tempRound, precisionToRoundTo);
	mpfr_set(tempRound, valToRound, MPFR_RNDZ); // tempRound = <0.03>
	// /!\ Important : need to round toward zero in order to have an exact rounded value close to zero for last digits
	mpfr_sub(*lastDigits, valToRound, tempRound, MPFR_RNDN); // lastDigits = <0.0345> - <0.03>
	// last digit is the part we won't keep in the resulting rounded value
	// so it will be our base for testing the expected rounding direction
	mpfr_set_exp(*lastDigits, 0);

	m_clear(tempRound);

	return 0;
}

int generateRandomValueInPrecisionRange(mpfr_t * randomValue,
		long int precision, mpfr_t maxValueInRange, int flagSign) {
	// mpfr_min_prec (mpfr_t x)
	mpfr_t tmpRnd;
	if(precision*2<MPFR_PREC_MAX) {
		m_init2(tmpRnd, precision*2); // TODO check this. `precision` seems too low.
	} else {
		m_init2(tmpRnd, MPFR_PREC_MAX-1); // overflow risk
	}
	// random value picking (between 0 and 1)
	setRandomValue(&tmpRnd);
	// multiplying the random value with the maximum value in order to have a value in the desired range ==> valToRound
	m_mul(*randomValue, tmpRnd, maxValueInRange, MPFR_RNDN);
	//mpfr_printf("tmpRnd : %R\tmaxValue : %R\tvalToRound : %R\n",tmpRnd,maxValue,valToRound);
	/* printf("[%ld]\t[%ld]\t(%d) - tmpRnd : %f\tmaxValue : %f\tvalToRound : %f\n",
	 precision, precisionToRoundTo, j, mpfr_get_d(tmpRnd, MPFR_RNDN),
	 mpfr_get_d(maxValueInRange, MPFR_RNDN),
	 mpfr_get_d(valToRound, MPFR_RNDN)); */
	mpfr_setsign(*randomValue, *randomValue, flagSign, MPFR_RNDN);

	m_clear(tmpRnd);

	return 0;
}

void getMaxValue(mpfr_t * maxValue, mpfr_prec_t precision) {
	mpfr_t mPrec;
	m_init2(mPrec, mpfr_get_default_prec());
	mpfr_set_si(mPrec, precision, MPFR_RNDN);
	m_init2(*maxValue, max(precision,MPFR_PREC_MIN));
	// getting the highest possible value for the initialPrecision range
	mpfr_exp2(*maxValue, mPrec, MPFR_RNDN);
	//mpfr_sub_si(*maxValue,*maxValue,1L,MPFR_RNDN);
	m_clear(mPrec);
}


/**
 * Print to the standard output the value of v in base 2
 * @param v	The value to print to the standard output
 */
void m_print(mpfr_t v) {
	if(DEBUG||1) mpfr_out_str (stdout, 2, 0, v, MPFR_RNDN);
}

/**
 * Same than m_print with a message above the value
 * @param v
 */
void m_print_wm(mpfr_t v, char * msg) {
	if(DEBUG||1) {
		printf("\n%s ",msg);
		m_print(v);
	}
}
