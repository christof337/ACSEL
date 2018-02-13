#include <stdio.h>
#include <mpfr.h>

#include "customMath.h"

#include "utils.h"

#ifndef DEBUG
 #define DEBUG 0
#endif

#ifndef max
#define max(A,B) A>B?A:B
#endif

/**
 * Initialize the value with the given precision.
 * Each variable initialized in this way must be freed afterwards.
 * @see mpfr/mpfr_init2
 * @param value 	The reference of the value to initialize according to MPFR standards
 * @param[in] precision The precision to initialize the value with
 */
void m_init2(mpfr_t value, const mpfr_prec_t precision) {
	mpfr_init2(value, precision);
}

/**
 * @brief      Multiply `factor1` and `factor2` and put the product in `product`.
 *
 * @param[out] product       The product
 * @param[in]  factor1       The first factor
 * @param[in]  factor2       The second factor
 * @param[in]  roundingMode  The rounding mode
 *
 * @return     0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int m_mul(mpfr_t product, const mpfr_t factor1, const mpfr_t factor2,
		const enum roundingModeEnum roundingMode) {
	if (roundingMode == STOCHASTIC) {
		int res = 0;
		mpfr_t longFactor1, longFactor2, longProduct;
		mpfr_prec_t targetPrecision = mpfr_get_prec(product);

		handleExtendedRounding(longFactor1, longFactor2, longProduct, factor1, factor2);
		mpfr_mul(longProduct, longFactor1, longFactor2, MPFR_RNDN);

		res = stochasticRounding(&longProduct, targetPrecision);

		mpfr_set(product, longProduct, MPFR_RNDN);

		m_clear(longFactor1);
		m_clear(longFactor2);
		m_clear(longProduct);
		return res;
	} else {
		// passer le enumRM à mpfr_rm_t
		return mpfr_mul(product, factor1, factor2, roundingModeEnumToMpfrRndT(roundingMode));
	}
}

int m_mul_si(mpfr_t product, const mpfr_t factor1, long int factor2,
		const enum roundingModeEnum roundingMode) {
	int res = 0;
	mpfr_t mFactor2;

	m_init2(mFactor2, max(mpfr_get_prec(factor1), mpfr_get_prec(product)));
	mpfr_set_si(mFactor2, factor2, roundingModeEnumToMpfrRndT(roundingMode));

	res = m_mul(product, factor1, mFactor2, roundingMode);

	m_clear(mFactor2);
	return res;
}

/**
 * @brief      Divide `dividend` by `divisor` and put the quotient in `quotient`.
 *
 * @param[out]	quotient		The quotient
 * @param[in]	dividend		The dividend
 * @param[in]	divisor			The divisor
 * @param[in]	roundingMode	The rounding mode
 * @return		0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int m_div(mpfr_t quotient, const mpfr_t dividend, const mpfr_t divisor,
		const enum roundingModeEnum roundingMode) {
	if (roundingMode == STOCHASTIC) {
		int res = 0;
		mpfr_t longDividend, longDivisor, longQuotient;

		mpfr_prec_t targetPrecision = mpfr_get_prec(quotient);

		handleExtendedRounding(longDividend, longDivisor, longQuotient, dividend, divisor);

		mpfr_div(longQuotient, longDividend, longDivisor, MPFR_RNDN);

		res = stochasticRounding(&longQuotient, targetPrecision);

		mpfr_set(quotient, longQuotient, MPFR_RNDN);

		m_clear(longDividend);
		m_clear(longDivisor);
		m_clear(longQuotient);

		return res;
	} else {
		// passer le enumRM à mpfr_rm_t
		return mpfr_div(quotient, dividend, divisor, roundingModeEnumToMpfrRndT(roundingMode));
	}
}

/**
 * @brief      Add `addends1` by `addends2` and put the sum in `summation`.
 *
 * @param[out]	summation		The sum
 * @param[in]	addend1			The first term
 * @param[in]	addend2			The second term
 * @param[in]	roundingMode	The rounding mode
 * @return		0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int m_add(mpfr_t summation, const mpfr_t addend1, const mpfr_t addend2,
		const enum roundingModeEnum roundingMode) {
	if (roundingMode == STOCHASTIC) {
		int res = 0;
		mpfr_t longAddend1, longAddend2, longSummation;

		mpfr_prec_t targetPrecision = mpfr_get_prec(summation);

		handleExtendedRounding(longAddend1, longAddend2, longSummation, addend1, addend2);

		mpfr_add(longSummation, longAddend1, longAddend2, MPFR_RNDN);

		res = stochasticRounding(&longSummation, targetPrecision);

		mpfr_set(summation, longSummation, MPFR_RNDN);

		m_clear(longAddend1);
		m_clear(longAddend2);
		m_clear(longSummation);

		return res;
	} else {
		// passer le enumRM à mpfr_rm_t
		return mpfr_add(summation, addend1, addend2, roundingModeEnumToMpfrRndT(roundingMode));
	}
}

/**
 * @brief      	Substract `substrahend` from `minuend` and put the difference in `difference`.
 *
 * @param[out]	difference		The difference
 * @param[in]	minuend			The number substrahend is substracted from
 * @param[in]	substrahend		The number being substracted
 * @param[in]	roundingMode	The rounding mode
 * @return		0 if rounded exactly, > 0 if globally rounded upwards the exact
 *             values, < 0 if globally rounded downwards the exact values
 */
int m_sub(mpfr_t difference, const mpfr_t minuend, const mpfr_t substrahend,
		const enum roundingModeEnum roundingMode) {
	if (roundingMode == STOCHASTIC) {
		int res = 0;
		mpfr_t longMinuend, longSubstrahend, longDifference;

		mpfr_prec_t targetPrecision = mpfr_get_prec(difference);

		handleExtendedRounding(longMinuend, longSubstrahend, longDifference, minuend, substrahend);

		mpfr_sub(longDifference, longMinuend, longSubstrahend, MPFR_RNDN);

		res = stochasticRounding(&longDifference, targetPrecision);

		mpfr_set(difference, longDifference, MPFR_RNDN);

		m_clear(longMinuend);
		m_clear(longSubstrahend);
		m_clear(longDifference);

		return res;
	} else {
		// passer le enumRM à mpfr_rm_t
		return mpfr_sub(difference, minuend, substrahend, roundingModeEnumToMpfrRndT(roundingMode));
	}
}

int m_pow(mpfr_t pow, const mpfr_t val, const mpfr_t exp, const enum roundingModeEnum roundingMode) {
	if (roundingMode == STOCHASTIC) {
		int res = 0;
		mpfr_t longVal, longExp, longPow;

		mpfr_prec_t targetPrecision = mpfr_get_prec(pow);

		// treating the numbers in 2n precision
		handleExtendedRounding(longVal, longExp, longPow, val, exp);

		mpfr_pow(longPow, longVal, longExp, MPFR_RNDN);

		res = stochasticRounding(&longPow, targetPrecision);

		mpfr_set(pow, longPow, MPFR_RNDN);

		m_clear(longVal);
		m_clear(longExp);
		m_clear(longPow);

		return res;
	} else {
		// passer le enumRM à mpfr_rm_t
		return mpfr_pow(pow, val, exp, roundingModeEnumToMpfrRndT(roundingMode));
	}
}

/**
 * @brief	Clear the value according to mpfr standards.
 * 			Cannot use the value after this point.
 * @param	value 	The value to clear.
 */
void m_clear(mpfr_t value) {
	mpfr_clear(value);
}

/**
 * @brief					Sum the precision of shortValue1 and shortValue2 and set longResult, longValue1 and longValue2 with the resulting precision (or MPFR_PREC_MAX if lower).
 * 							Also set the value of longValue1 and longValue2 to the value of shortValue1 and shortValue2 (respectively)
 * @param longValue1[out]	The value to set at a larger precision
 * @param longValue2[out]	The other value to set at a larger precision
 * @param longResult[out]	Just a value to initialize at a larger precision, without set
 * @param shortValue1[in]	The value to set longValue1 with
 * @param shortValue2[in]	The value to set longValue2 with
 */
void handleExtendedRounding(mpfr_t longValue1, mpfr_t longValue2, mpfr_t longResult,
		const mpfr_t shortValue1, const mpfr_t shortValue2) {
	mpfr_prec_t currentPrecision1 = mpfr_get_prec(shortValue1);
	mpfr_prec_t currentPrecision2 = mpfr_get_prec(shortValue2);
	mpfr_prec_t extendedPrecision = 0L;

	if (currentPrecision1 + currentPrecision2 < MPFR_PREC_MAX) {
		extendedPrecision = currentPrecision1 + currentPrecision2;
	} else {
		extendedPrecision = MPFR_PREC_MAX;
	}
	m_init2(longValue1, extendedPrecision);
	m_init2(longValue2, extendedPrecision);
	m_init2(longResult, extendedPrecision);
	mpfr_set(longValue1, shortValue1, MPFR_RNDN);
	mpfr_set(longValue2, shortValue2, MPFR_RNDN);
}

/**
 * @brief			Increase the precision of v, keeping the previous value.
 * @param value			The value to change precision of
 * @param[in] pre	The target precision
 * @return			The rounding direction of the rounding made during the precision change
 * 						(0 if rounded exactly, > 0 if globally rounded upwards the exact
 *       				value, < 0 if globally rounded downwards the exact value)
 */
int m_setPrecision(mpfr_t * value, const mpfr_prec_t pre) {
	int roundingDirection = 0;
	mpfr_t result;
	m_init2(result, pre);
	mpfr_set(result, *value, MPFR_RNDN);
	//roundingDirection = mpfr_prec_round(result, pre, MPFR_RNDN);
	mpfr_set_prec(*value, pre);
	mpfr_set(*value, result, MPFR_RNDN);
	m_clear(result);
	return roundingDirection;
}

/**
 * @brief			Increase the precision of v, keeping the previous value.
 * @param value			The value to change precision of
 * @param[in] pre	The target precision
 * @return			The rounding direction of the rounding made during the precision change
 * 						(0 if rounded exactly, > 0 if globally rounded upwards the exact
 *       				value, < 0 if globally rounded downwards the exact value)
 */
int m_setPrecisionWithRoundingMode(mpfr_t * value, const mpfr_prec_t pre,
		const mpfr_rnd_t roundingMode) {
	int roundingDirection = 0;
	mpfr_t result;
	m_init2(result, pre);
	mpfr_set(result, *value, roundingMode);
	//roundingDirection = mpfr_prec_round(result, pre, MPFR_RNDN);
	mpfr_set_prec(*value, pre);
	mpfr_set(*value, result, roundingMode);
	m_clear(result);
	return roundingDirection;
}

/**
 * @brief			Apply a randomized stochastic rounding to the value `v` at the precision `pre`.
 * 					The chances for `value` to be rounded in a direction depend on its distance to the next (resp) previous floating point value at the precision `pre`.
 * @param value		The value to round
 * @param[in] pre	The precision to round to
 * @return			0 if rounded exactly, > 0 if globally rounded upward the exact
 *             		value, < 0 if globally rounded downward the exact value
 */
int stochasticRounding(mpfr_t * value, const mpfr_prec_t pre) {
	// recording the rounding direction
	int roundingDirection = 0;

	// recording the current precision
	const mpfr_prec_t currentPrecision = mpfr_get_prec(*value);
#if (DEBUG>0)
	m_print_wm((*value), "\t\tRounding  `v`=");
	printf(" at precision %ld", pre);
	printf("\t Current precision is %ld", currentPrecision);
#endif

	// value is a number of `currentPrecision` bits.
	// value must be set with the value of `v` with precision `pre` ; rounded with stochastic rounding
	if (currentPrecision <= pre) {
		// value is already shorter than the expected precision : no rounding, simply adding zeros at the end
		// `mpfr_prec_round` seems to fail to increase the precision : using a custom function, m_setPrecision
		roundingDirection = m_setPrecision(value, pre);
#if (DEBUG>0)
		printf(
				"\n\tCurrent precision (%ld) is lower than asked precision (%ld) ; exiting without rouding...",
				currentPrecision, pre);
		m_print_wm(*value, "\n\tResult is :");
		printf("\n");
#endif
	} else {
		// value is longer than the asked precision
		// retrieving the exceeding digits
		const long int lastDigitPrecision = max((currentPrecision - pre), MPFR_PREC_MIN);
		mpfr_t lastDigits;
		getLastDigits(&lastDigits, *value, currentPrecision, pre);
		mpfr_abs(lastDigits, lastDigits, MPFR_RNDN);

		// generate a random value between -0.5 and 0.5
		// add this value to lastDigits
		// round to nearest lastDigits
		// --- OR ---
		// equivalent to generate a random value between 0 and 1
		mpfr_t randomValue;
		//m_init2(randomValue,lastDigitPrecision);
		m_init2(randomValue, mpfr_get_default_prec());
//		do {
		setRandomValue(&randomValue);
		// and see if it is greater than lastDigits or not
		// if it is, round down, if it is not, round up
		if (mpfr_greater_p(lastDigits, randomValue)) {
			// rounding up
#if (DEBUG>0)
			printf("\tROUND UP");
#endif
			// roundingDirection = mpfr_prec_round(*value, pre, MPFR_RNDU);
//			roundingDirection = 1;
			roundingDirection = m_setPrecisionWithRoundingMode(value, pre, MPFR_RNDU);
		} else if (mpfr_less_p(lastDigits, randomValue)) {
			// rounding down
#if (DEBUG>0)
			printf("\tROUND DOWN");
#endif
			// roundingDirection = mpfr_prec_round(*value, pre, MPFR_RNDD);
//			roundingDirection = -1;
			roundingDirection = m_setPrecisionWithRoundingMode(value, pre, MPFR_RNDD);
		}

//		++NB_STOCH_ROUND;
//		} while (mpfr_equal_p(randomValue, lastDigits)); // loop in order to not misinterpret the equal case (occurs likely at low precision)

		m_clear(lastDigits);
		m_clear(randomValue);
		//m_clear(mpfr_lastDigits);
	}

	return roundingDirection;
}

/**
 * @deprecated
 * @return The rounding mode to use through the whole application
 */
mpfr_rnd_t m_getRoundingMode() {
	return mpfr_get_default_rounding_mode();
}

/**
 * Return the digits after the "precisionToRoundTo"
 * @param[out] lastDigits 			The output value. Is initialized during function.
 * @param[in] valToRound			The value to extract the digits of
 * @param[in] initialPrecision		The precision of valToRound
 * @param[in] precisionToRoundTo	The precision from which we want the lastDigits to start
 * @return zero
 */
int getLastDigits(mpfr_t * lastDigits, const mpfr_t valToRound, const long int initialPrecision,
		const long int precisionToRoundTo) {
	mpfr_t tempRound;
	m_init2(tempRound, precisionToRoundTo);

	m_init2(*lastDigits, max((initialPrecision - precisionToRoundTo), MPFR_PREC_MIN));

	mpfr_set(tempRound, valToRound, MPFR_RNDZ); // round toward zero // tempRound = <0.03>
	/* /!\ Important : need to round toward zero in order to have an exact rounded value close to zero for last digits */
	m_sub(*lastDigits, valToRound, tempRound, RNDN); // lastDigits = <0.0345> - <0.03> = <0.0045>
	// last digit is the part we won't keep in the resulting rounded value
	// so it will be our base for testing the expected rounding direction
	mpfr_set_exp(*lastDigits, 0); // lastDigits = 0.45

	m_clear(tempRound);

	return 0;
}

/**
 *	Generates a random value with the given sign and ranging from the minimum representable value in the given precision and the maximum representable value in the given precision.
 * @param[out] randomValue
 * @param[in] precision
 * @param[in] maxValueInRange
 * @param[in] flagSign
 * @return	zero
 */
int generateRandomValueInPrecisionRange(mpfr_t * randomValue, const long int precision,
		const mpfr_t maxValueInRange, const int flagSign) {
	mpfr_t tmpRnd;
	if (precision * 2 < MPFR_PREC_MAX) {
		m_init2(tmpRnd, precision * 2); // TODO check this. `precision`*1 seems too low.
	} else {
		m_init2(tmpRnd, MPFR_PREC_MAX - 1); // overflow risk
	}
	// random value picking (between 0 and 1)
	setRandomValue(&tmpRnd);
	// multiplying the random value with the maximum value in order to have a value in the desired range ==> valToRound
	m_mul(*randomValue, tmpRnd, maxValueInRange, MPFR_RNDN);
	// set the asked sign
	mpfr_setsign(*randomValue, *randomValue, flagSign, MPFR_RNDN);

	m_clear(tmpRnd);

	return 0;
}

/**
 * @brief				Init and set maxValue to the maximum value representable at the precision `precision`
 * @param[out] maxValue	The value to set to the maximum. Must be freed afterwards.
 * @param[in] precision	The precision to wrap maxValue. Must be positive.
 */
void getMaxValue(mpfr_t * maxValue, const mpfr_prec_t precision) {
	mpfr_t mPrec;
	m_init2(mPrec, mpfr_get_default_prec());
	mpfr_set_si(mPrec, precision, MPFR_RNDN);
	m_init2(*maxValue, max(precision, MPFR_PREC_MIN)); // max needed in order not to throw an exception when initializing
	// getting the highest possible value for the initialPrecision range
	mpfr_exp2(*maxValue, mPrec, MPFR_RNDN);

	m_clear(mPrec);
}

mpfr_rnd_t roundingModeEnumToMpfrRndT(enum roundingModeEnum e) {
	mpfr_rnd_t mpfr_rnd;
	switch (e) {
	case RNDN:
		mpfr_rnd = MPFR_RNDN; // round to nearest (roundTiesToEven in IEEE 754-2008)
		break;
	case STOCHASTIC:
		mpfr_rnd = -1; // not implemented in mpfr yet. Call customMath/m_<operation>.
		// round randomly to toward plus infinity or toward minus infinity,
		// the more close it is from the rounded value, the more probability
		// to round to this value.
		break;
	case RNDZ:
		mpfr_rnd = MPFR_RNDZ; // round toward zero (roundTowardZero in IEEE 754-2008)
		break;
	case RNDU:
		mpfr_rnd = MPFR_RNDU; // round toward plus infinity (roundTowardPositive in IEEE 754-2008)
		break;
	case RNDD:
		mpfr_rnd = MPFR_RNDD; //round toward minus infinity (roundTowardNegative in IEEE 754-2008)
		break;
	case RNDA:
		mpfr_rnd = MPFR_RNDA; // round toward minus infinity (roundTowardNegative in IEEE 754-2008)
		break;
	default:
		mpfr_rnd = mpfr_get_default_rounding_mode();
		break;
	}
	return mpfr_rnd;
}

/**
 * @brief					Print to the standard output the value of valueToPrint in base 2 if DEBUG is enabled
 * @param[in] valueToPrint	The value to print to the standard output
 */
void m_print(const mpfr_t valueToPrint) {
#if (DEBUG>0)
	mpfr_out_str(stdout, 2, 0, valueToPrint, MPFR_RNDN);
#endif
}

/**
 * @brief					Print `valueToPrint` in base 2 preceded by `msg` to the standard output if DEBUG is enabled.
 * @param[in] valueToPrint	The value to print to the standard output
 * @param[in] msg			The message to introduce the given value (useful for debugging)
 */
void m_print_wm(const mpfr_t valueToPrint, const char * msg) {
#if (DEBUG>0)
	printf("\n%s ", msg);
	m_print(valueToPrint);
#endif
}

/**
 * Simple test of the stochastic rounding.
 */
void quickTestStochasticRounding() {
// test
	mpfr_t number;
	mpfr_prec_t numberPrecision = 8;
	double value = 1.234375;
//		double desiredValue1 = 1.234;
//		double desiredValue2 = 1.235;
	mpfr_prec_t desiredPrecision = 5;
	m_init2(number, numberPrecision);
//m_init2(*test,numberPrecision);
	mpfr_set_d(number, value, MPFR_RNDN);
	printf("\nAffichage du nombre avant opération :\n\t");
	m_print(number);
	stochasticRounding(&number, desiredPrecision);
	printf("\nAffichage du nombre APRES opération : \n\t");
	m_print(number);
	m_clear(number);
}
