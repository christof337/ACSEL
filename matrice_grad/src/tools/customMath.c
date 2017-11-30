
#include <stdio.h>
#include <mpfr.h>

#include "customMath.h"


#include "utils.h"

/* --------------------- MPFR notes --------------------- 
mode d'arrondi : MPFR_RNDN : round to nearest : notre préféré jusque là
 ==> TODO : voir si je peux créer le mien?

 mpfr_t t,u; // déclaration
 const int precision = 200;
 mpfr_init2(t, precision); // initialisation à une précision de `precision` (200) bits
 mpfr_init2 (u, precision);
 unsigned int i = 1;
 mpfr_mul_ui(t,t,i,MPFR_RNDU); // multiplication de t par i (1) avec arrondi vers +infini
 mpfr_div(u,u,t,MPFR_RNDD); // divise u par t, et arrondi le résultat vers -infini (et stocke le résultat dans u)
 mpfr_out_str(stdout,10,0,s,MPFR_RNDD); /* affiche la valeur de s en base 10, arrondi vers moins l'infini, 
 // le troisième argument 0 indiquant que le nombre de digit affichés est choisi automatiquement 
 // par rapport à la précision de s /
mpfr_clear(t) // libère l'espace pris par les variables mpfr

*/

void m_init2(mpfr_t value, mpfr_prec_t precision) {
	mpfr_init2(value,precision);
}

/**
 * @brief      Multiply factor1 and factor2 and put the product in product.
 *
 * @param[in]  product       The product
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

int m_div(mpfr_t quotient, mpfr_t dividend, mpfr_t divisor, mpfr_rnd_t roundingMode) {
	return mpfr_div(quotient, dividend, divisor, roundingMode);
}

void m_clear(mpfr_t value) {
	mpfr_clear(value);
}

/**
 *
 * @param v
 * @param pre
 * @return
 */
int stochasticRounding(mpfr_t * v, mpfr_prec_t pre)
{
	printLine();
	printLine();
	printf("\nStart of rounding :\n");
	m_print_wm((*v),"\tRounding  `v`=");
	printf(" at precision %ld",pre);

	int error;
	mpfr_t res;
	m_init2(res, pre);

	mpfr_prec_t currentPrecision = mpfr_get_prec(*v);
	printf("\n Current precision is %ld",currentPrecision);

	// v is a number of `currentPrecision` bits.
	// res must be the value of `v` with precision `pre` ; rounded with stochastic rounding
	if( currentPrecision < pre ) {
		printf("\n\tCurrent precision (%ld) is lower than asked precision (%ld) ; exiting without rouding...",currentPrecision,pre);
		error += mpfr_prec_round(*v,pre, MPFR_RNDN); // no problem in using RNDN ; because no rounding will be made
		m_print_wm(*v,"\n\tResult is :");
		m_clear(res);
	} else {
		// v is longer than the asked precision
		mpfr_t lastDigits;
		m_init2(lastDigits, (currentPrecision - pre ) ); // TODO check the +1
		//m_init2(lastDigits, (currentPrecision) ); // TODO check the +1
		mpfr_t tempRound;
		m_init2(tempRound, pre);

		mpfr_set(tempRound, *v, MPFR_RNDZ); // tempRound = <0.03>
		m_print_wm(tempRound,"Rounded (tmp) value : ");
		// /!\ Important : need to round toward zero in order to have an exact rounded value close to zero for last digits

		mpfr_sub(lastDigits,*v, tempRound, MPFR_RNDN); // lastDigits = <0.0345> - <0.03>
		m_print_wm(lastDigits,"Last digits : ");

		// last digit is the part we won't keep in the resulting rounded value
		// so it will be our base for the rounding choice

		// right now we just have to :
		// multiply lastDigits by its exponent
		// generate a random value between -0.5 and 0.5
		// add this value to lastDigits
		// round to nearest lastDigits
	}

	return error;
}

mpfr_rnd_t m_getRoundingMode() {
	return MPFR_RNDN;
}

void m_print(mpfr_t v) {
	mpfr_out_str (stdout, 2, 0, v, MPFR_RNDN);
}

/**
 * print with message
 * @param v
 */
void m_print_wm(mpfr_t v, char * msg) {
	printf("\n%s ",msg);
	mpfr_out_str (stdout, 2, 0, v, MPFR_RNDN);
}
