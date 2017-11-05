#include "customMath.h"

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

mpfr_rnd_t m_getRoundingMode() {
	return MPFR_RNDN; // FIXME : round to nearest pour l'instant, passer à mon custom stochastic rounding
}