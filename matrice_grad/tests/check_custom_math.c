/*
 * check_custom_math.c
 *
 *  Created on: 1 déc. 2017
 *      Author: root
 */

// make && make test || cat ./check_custom_math_test.log


#include <stdlib.h>
#include <check.h>
#include <mpfr.h>

//#include "../src/tools/arrayUtils.h"
#include "../src/tools/customMath.h"

#define TEST_DEFAULT_PRECISION 13

#define NB_ITER 100000

#define NB_VALUES 500

#define VAL_MAX 1000000.0

//#define RM m_getRoundingMode()


/**
 * Test de l'utilitaire "customMath.c"
 * Exécuter avec `make test`
 */

void setup(void)
{

}

void teardown(void)
{

}

START_TEST(test_m_init2) {
	mpfr_t mpfrValue;
	long int precision;

	m_init2(mpfrValue, TEST_DEFAULT_PRECISION);

	precision = mpfr_get_prec(mpfrValue);
	ck_assert( precision == TEST_DEFAULT_PRECISION );

	m_clear(mpfrValue);
}
END_TEST

START_TEST(test_stochastic_rounding) {
	mpfr_t valToRound;
	long int precisionToeRoundTo;

	// testing all the precisions
	for ( long int initialPrecision = MPFR_PREC_MIN ; initialPrecision <= MPFR_PREC_MAX ; ++initialPrecision ) {
		for ( long int precisionToRoundTo = MPFR_PREC_MIN ; precisionToRoundTo <= MPFR_PREC_MAX ; ++initialPrecision ) {
			m_init2(valToRound, initialPrecision /* 13 */);

			// on va tester plusieurs valeurs
			for ( int i = 0 ; i < NB_VALUES; ++i ) {
				// mpfr_min_prec (mpfr_t x)

				// on pick une value entre 0 et 1
				// on la multiplie par le maximum représentable à la précision `min(initialPrecision,precisionToRoundTo)`

				// une fois qu'on a la valeur...
				// on détermine la valeur attendue (pourcentage d'arrondis vers le haut, pourcentage d'arrondis vers le bas)
				for ( int j = 0 ; i < NB_ITER ; ++j ) {
					// on lui applique l'arrondi
					// on compte si c'est vers le haut ou vers le bas
				}
				// et à la fin de la boucle on détermine combien ya de haut et de bas
				// et on le compare à la valeur attendue, avec une marge d'erreur à définir (mettons 5% pour commencer)
			}
			// on refait ça pour la précision cible suivante

		}
		// on refait ça pour la précision initiale suivante
		m_clear(valToRound);
	}

	m_clear(valToRound);
}
END_TEST

// --------------------------------------------------------

Suite * custom_math_suite(void) {
	Suite *s;
	TCase *tc_core;
	TCase *tc_lmits;

	s = suite_create("Custom Math");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);


	tcase_add_test(tc_core, test_m_init2);
	tcase_add_test(tc_core, test_stochastic_rounding);

	suite_add_tcase(s, tc_core);

	return s;
}

int main ( void ) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = custom_math_suite();
	sr = srunner_create(s);

	srunner_set_log (sr, "check_custom_math_test.log");

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
