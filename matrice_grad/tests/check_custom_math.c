/*
 * check_custom_math.c
 *
 *  Created on: 1 déc. 2017
 *      Author: root
 */

// make && make test || cat ./check_custom_math_test.log

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>
#include <check.h>

//#include "../src/tools/arrayUtils.h"
#include "../src/tools/customMath.h"
#include "../src/tools/utils.h"
#include "../src/tools/inputOutput.h"

#define TEST_DEFAULT_PRECISION 13

#define NB_ITER 100000

#define NB_VALUES 500

#define VAL_MAX 1000000.0

#define ERROR_MARGIN 5.0/100.0

#define LOG_FILE_NAME "check_custom_math.manual.log"

//#define RM m_getRoundingMode()

FILE * logFile;

/**
 * Test de l'utilitaire "customMath.c"
 * Exécuter avec `make test`
 */

void setup(void) {
	//logFile = openLog(LOG_FILE_NAME);
}

void teardown(void) {
	//closeLog(logFile);
}

START_TEST(test_m_init2)
	{
		mpfr_t mpfrValue;
		long int precision;

		m_init2(mpfrValue, TEST_DEFAULT_PRECISION);

		precision = mpfr_get_prec(mpfrValue);
		ck_assert(precision == TEST_DEFAULT_PRECISION);

		m_clear(mpfrValue);
	}END_TEST

START_TEST(test_stochastic_rounding)
	{
		logFile = openLog(LOG_FILE_NAME);
		char logBuffer[1000];
		int res = 0;
		long int initialPrecision = _i;
		mpfr_t valToRound;
		long int precisionToeRoundTo;

		// testing all the precisions
		// for ( long int initialPrecision = MPFR_PREC_MIN ; initialPrecision <= MPFR_PREC_MAX ; ++initialPrecision ) {
		mpfr_t mInitPrec;
		m_init2(mInitPrec, mpfr_get_default_prec());
		mpfr_set_si(mInitPrec, initialPrecision, MPFR_RNDN);

		sprintf(logBuffer, "\n[%ld] - Start of stochastic rounding test for precision `%ld` ...\n",
				initialPrecision, initialPrecision);
		m_log(logFile, logBuffer);
		sprintf(logBuffer, "[%ld] - Begin of changing the target precision...\n", initialPrecision);
		m_log(logFile, logBuffer);

		for (long int precisionToRoundTo = MPFR_PREC_MIN ; precisionToRoundTo <= MPFR_PREC_MAX ;
				++precisionToRoundTo) {
			sprintf(logBuffer, "[%ld]\t[%ld] - Target precision is now `%ld`\n", initialPrecision,
					precisionToRoundTo, precisionToRoundTo);
			m_log(logFile, logBuffer);
			int flagSign = 0;
			m_init2(valToRound, initialPrecision);

			sprintf(logBuffer, "[%ld]\t[%ld] - Begin of changing the values...\n", initialPrecision,
					precisionToRoundTo);
			m_log(logFile, logBuffer);
			// on va tester plusieurs valeurs
			for (int j = 0 ; j < NB_VALUES ; ++j) {
				char logCurrentVal[12];
				// mpfr_min_prec (mpfr_t x)

				// on pick une value aléatoire (entre 0 et 1)
				mpfr_t tmpRnd;
				m_init2(tmpRnd, initialPrecision);
				setRandomValue(tmpRnd);

				// on la multiplie par le maximum représentable à la précision initialPrecision //`min(initialPrecision,precisionToRoundTo)`
				mpfr_t maxValue;
				m_init2(maxValue, initialPrecision);
				mpfr_exp2(maxValue, mInitPrec, MPFR_RNDN);
				m_mul(valToRound, tmpRnd, maxValue, MPFR_RNDN);

				// on lui donne un signe alternativement positif et négatif
				mpfr_setsign(valToRound, valToRound, flagSign, MPFR_RNDN);
				flagSign = !flagSign;

				// now, valToRound is a value in the needed range
				mpfr_sprintf(logCurrentVal, "%.8f", valToRound);
				sprintf(logBuffer, "[%ld]\t[%ld]\tStarting to test the value `%s`\n",
						initialPrecision, precisionToRoundTo, logCurrentVal);
				m_log(logFile, logBuffer);

				mpfr_t actualResult;
				m_init2(actualResult, initialPrecision);
				mpfr_set(actualResult, valToRound, MPFR_RNDN);

				// une fois qu'on a la valeur...
				if (initialPrecision < precisionToRoundTo) {
					sprintf(logBuffer,
							"-----[%ld]\t[%ld]\t{%s} - Target precision (%ld) is greater than initialPrecision (%ld). Simple rounding.\n",
							initialPrecision, precisionToRoundTo, logCurrentVal, precisionToRoundTo,
							initialPrecision);
					m_log(logFile, logBuffer);
					stochasticRounding(&actualResult, precisionToRoundTo);
					// simple rounding (filling with zeros actually)
					mpfr_prec_round(valToRound, precisionToRoundTo, MPFR_RNDN); // no problem in using RNDN ;
					//no rounding will be made (new allocated space for significand filled with zero)
					ck_assert(mpfr_equal_p(actualResult, valToRound));
				} else {

					// on détermine la valeur attendue (pourcentage d'arrondis vers le haut, pourcentage d'arrondis vers le bas)

					/* --------------------------------------- */
					mpfr_t lastDigits;
					m_init2(lastDigits, (initialPrecision - precisionToRoundTo));
					mpfr_t tempRound;
					m_init2(tempRound, precisionToRoundTo);

					mpfr_set(tempRound, valToRound, MPFR_RNDZ); // tempRound = <0.03>
					// /!\ Important : need to round toward zero in order to have an exact rounded value close to zero for last digits

					mpfr_sub(lastDigits, valToRound, tempRound, MPFR_RNDN); // lastDigits = <0.0345> - <0.03>

					// last digit is the part we won't keep in the resulting rounded value
					// so it will be our base for testing the expected rounding direction

					mpfr_set_exp(lastDigits, 0);
					/* --------------------------------------- */

					int nbRoundUp = 0;

					sprintf(logBuffer,
							"[%ld]\t[%ld]\t{%s} - Begin of loop over multiple stochastic roundings...\n",
							initialPrecision, precisionToRoundTo, logCurrentVal);
					m_log(logFile, logBuffer);
					for (int k = 0 ; k < NB_ITER ; ++k) {
						int roundingDirection;
						m_init2(actualResult, initialPrecision);
						mpfr_set(actualResult, valToRound, MPFR_RNDN);
						// on lui applique l'arrondi
						roundingDirection = stochasticRounding(&actualResult, precisionToRoundTo);
						// on compte si c'est vers le haut ou vers le bas
						if (roundingDirection > 0) {
							nbRoundUp++;
						}
						m_clear(actualResult);
					}
					// et à la fin de la boucle on détermine combien ya de haut et de bas
					// et on le compare à la valeur attendue, avec une marge d'erreur à définir (mettons 5% pour commencer)
					mpfr_t expectedPctRoundUp;
					m_init2(expectedPctRoundUp, mpfr_get_default_prec());
					m_div(expectedPctRoundUp, lastDigits, maxValue, MPFR_RNDN);

					mpfr_t lowerBound;
					mpfr_init2(lowerBound, mpfr_get_default_prec());
					mpfr_sub_d(lowerBound, expectedPctRoundUp, ERROR_MARGIN, MPFR_RNDN);
					mpfr_t upperBound;
					mpfr_init2(upperBound, mpfr_get_default_prec());
					mpfr_add_d(upperBound, expectedPctRoundUp, ERROR_MARGIN, MPFR_RNDN);

					mpfr_t actualPctRoundUp;
					mpfr_init2(actualPctRoundUp, mpfr_get_default_prec());
					mpfr_set_d(actualPctRoundUp, (nbRoundUp / NB_ITER), MPFR_RNDN);

					sprintf(logBuffer,
							"---------[%ld]\t[%ld]\t{%s} - `%d` rounding upwards, upon `%d` roundings (%4f%s)\nShould be %4f%s\n",
							initialPrecision, precisionToRoundTo, logCurrentVal, nbRoundUp, NB_ITER,
							mpfr_get_d(actualPctRoundUp, MPFR_RNDN) * 100, "%",
							mpfr_get_d(expectedPctRoundUp, MPFR_RNDN) * 100, "%");
					m_log(logFile, logBuffer);
					ck_assert(
							mpfr_greaterequal_p(actualPctRoundUp, lowerBound)
									|| mpfr_lessequal_p(actualPctRoundUp, upperBound));

					m_clear(lastDigits);
					m_clear(tempRound);
				}
				m_clear(tmpRnd);
				m_clear(maxValue);
			}
			// on refait ça pour la précision cible suivante
			m_clear(valToRound);
		}
		m_clear(mInitPrec);
		//}

		closeLog(logFile);
		// on refait ça pour la précision initiale suivante
	}END_TEST

// --------------------------------------------------------

Suite * custom_math_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Custom Math");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, test_m_init2);
	tcase_add_loop_test(tc_core, test_stochastic_rounding, (int)MPFR_PREC_MIN, (int)MPFR_PREC_MAX);

	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = custom_math_suite();
	sr = srunner_create(s);

	srunner_set_log(sr, "check_custom_math_test.log");

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
