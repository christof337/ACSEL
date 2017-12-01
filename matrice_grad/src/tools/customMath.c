
#include <stdio.h>
#include <mpfr.h>

#include "customMath.h"


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
 *	Apply a randomized stochastic rounding to the value `v` at the precision `pre`
 * @param v		The value to round
 * @param pre	The precision to round to
 * @return		0 if rounded exactly, > 0 if globally rounded upward the exact
 *             	value, < 0 if globally rounded downward the exact value
 */
int stochasticRounding(mpfr_t * v, mpfr_prec_t pre)
{
	m_print_wm((*v),"\t\tRounding  `v`=");
	printf(" at precision %ld",pre);

	int error;

	mpfr_prec_t currentPrecision = mpfr_get_prec(*v);
	printf("\t Current precision is %ld",currentPrecision);

	// v is a number of `currentPrecision` bits.
	// res must be the value of `v` with precision `pre` ; rounded with stochastic rounding
	if( currentPrecision < pre ) {
		printf("\n\tCurrent precision (%ld) is lower than asked precision (%ld) ; exiting without rouding...",currentPrecision,pre);
		error += mpfr_prec_round(*v,pre, MPFR_RNDN); // no problem in using RNDN ; because no rounding will be made
		m_print_wm(*v,"\n\tResult is :");
	} else {
		// v is longer than the asked precision
		mpfr_t lastDigits;
		m_init2(lastDigits, (currentPrecision - pre ) ); // TODO check the +1
		//m_init2(lastDigits, (currentPrecision) ); // TODO check the +1
		mpfr_t tempRound;
		m_init2(tempRound, pre);

		mpfr_set(tempRound, *v, MPFR_RNDZ); // tempRound = <0.03>
		m_print_wm(tempRound,"\t\tRounded (tmp) value : ");
		// /!\ Important : need to round toward zero in order to have an exact rounded value close to zero for last digits

		mpfr_sub(lastDigits,*v, tempRound, MPFR_RNDN); // lastDigits = <0.0345> - <0.03>
		m_print_wm(lastDigits,"\t\tLast digits : ");

		// last digit is the part we won't keep in the resulting rounded value
		// so it will be our base for the rounding choice

		// right now we just have to :
		// multiply lastDigits by its exponent
		// -------------------------
		// on n'aurait pas besoin du code qui suit en mettant simplement l'exposant de lastDigits à 0
		/* mpz_t mantissa;
		mpfr_get_z_2exp (mantissa, lastDigits);

		mpfr_t mpfr_lastDigits;
		m_init2(mpfr_lastDigits,(currentPrecision - pre));
		mpfr_set_z (mpfr_lastDigits, mantissa, MPFR_RNDN);
		mpfr_set_exp (mpfr_lastDigits, 0); // TODO A VERIFIER QUADRUPLE CHECKER

		m_print_wm(mpfr_lastDigits,"Last digits after exp: ");*/
		// -------------------------

		mpfr_set_exp (lastDigits, 0); // TODO A VERIFIER QUADRUPLE CHECKER
		//m_print_wm(lastDigits,"\nJuste pour la blague, lastDigits à l'exposant 0 ça donne quoi?");

		// generate a random value between -0.5 and 0.5
		// add this value to lastDigits
		// round to nearest lastDigits

		// --- OR ---

		// equivalent to generate a random value between 0 and 1
		mpfr_t randomValue;
		m_init2(randomValue,(currentPrecision - pre));
		gmp_randstate_t randState;
		getRandstate(randState);
		mpfr_urandomb(randomValue,randState);
		// and see if it is greater than lastDigits or not
		// if it is, round down, if it is not, round up
		if ( mpfr_cmp ( lastDigits , randomValue ) > 0 ) {
			// rounding up
			printf("\n\t\t\tROUND UP");
			error += mpfr_prec_round( *v , pre, MPFR_RNDU );
		} else {
			// rounding down
			printf("\n\t\t\tROUND DOWN");
			error += mpfr_prec_round( *v , pre, MPFR_RNDD );
		}

		m_clear(lastDigits);
		m_clear(randomValue);
		//m_clear(mpfr_lastDigits);
	}

	return error;
}

/**
 * // FIXME m_getRoundingMode
 * @return
 */
mpfr_rnd_t m_getRoundingMode() {
	return MPFR_RNDN;
}

/**
 * Print to the standard output the value of v in base 2
 * @param v	The value to print to the standard output
 */
void m_print(mpfr_t v) {
	mpfr_out_str (stdout, 2, 0, v, MPFR_RNDN);
}

/**
 * Same than m_print with a message above the value
 * @param v
 */
void m_print_wm(mpfr_t v, char * msg) {
	printf("\n%s ",msg);
	m_print(v);
}
