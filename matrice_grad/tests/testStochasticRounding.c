/*
 * check_custom_math.c
 *
 *  Created on: 1 déc. 2017
 *      Author: root
 */

//gcc tests/testStochasticRounding.c src/tools/*.c -lmpfr -lgmp -lbsd -o customTestMath
#include <stdio.h>
#include <mpfr.h>

#include "../src/tools/customMath.h"
#include "../src/tools/inputOutput.h"
#include "../src/tools/utils.h"

#define TEST_DEFAULT_PRECISION 13

#define NB_ITER 2000L // 100000

#define NB_VALUES 30 // 500

#define VAL_MAX 1000000.0

#define ERROR_MARGIN 5.0/100.0

#define LOG_FILE_NAME "check_custom_math.manual.log"

#define MAX_TESTED_PRECISION 50 // 100

#ifndef max
#define max(A,B) A>B?A:B
#endif

//#define RM m_getRoundingMode()

FILE * logFile;
long int nbRnd;
long int nbCorrectRnd;

void testExtendedRounding(mpfr_t * valToRound, mpfr_t* actualResult, long int initialPrecision,
		long int precisionToRoundTo, int j, FILE* logBuffer) {
	// rounding to a greater precision ==> no need for actual rounding
	fprintf(logBuffer,
			"\n----[%ld]\t[%ld]\t(%d)\t{%f} - Target precision (%ld) is greater than initialPrecision (%ld). Simple rounding.",
			initialPrecision, precisionToRoundTo, j, mpfr_get_d(*valToRound, MPFR_RNDN),
			precisionToRoundTo, initialPrecision);
	m_init2(*actualResult, initialPrecision);
	mpfr_set(*actualResult, *valToRound, MPFR_RNDN);
	stochasticRounding(actualResult, precisionToRoundTo);
	++nbRnd;
	// simple rounding (filling with zeros actually)
	mpfr_t expectedResult;
	m_init2(expectedResult, precisionToRoundTo);
	mpfr_set(expectedResult, *valToRound, MPFR_RNDN);
	//m_setPrecision(valToRound, precisionToRoundTo); // no problem in using RNDN ;
	//no rounding will be made (new allocated space for significand filled with zero)
	if (mpfr_equal_p(*actualResult, expectedResult)) {
		//great, correct rounding
		++nbCorrectRnd;
	} else {
		// error, wrong rounding
		fprintf(stderr,
				"[%ld]\t[%ld]\t(%d)\t{%f} - Error during rounding of `%f`. Got `%f` instead of `%f`\n",
				initialPrecision, precisionToRoundTo, j, mpfr_get_d(*valToRound, MPFR_RNDN),
				mpfr_get_d(*valToRound, MPFR_RNDN), mpfr_get_d(*actualResult, MPFR_RNDN),
				mpfr_get_d(*valToRound, MPFR_RNDN));
	}
	m_clear(expectedResult);
}

/**
 * Set the value "bound" with the lower or upper bound of `valueToBoundAround` (depending on the parameter "isLowerBound"
 * @param bound
 * @param valueToBoundAround
 * @param isLowerBound 1 if the needed bound is the lower one, 0 if not
 */
void getBound(mpfr_t * bound, mpfr_t valueToBoundAround, int isLowerBound) {
	mpfr_init2(*bound, mpfr_get_default_prec());
	if (isLowerBound) {
		mpfr_sub_d(*bound, valueToBoundAround, ERROR_MARGIN, MPFR_RNDN);
	} else {
		mpfr_add_d(*bound, valueToBoundAround, ERROR_MARGIN, MPFR_RNDN);
	}
}

/**
 * Test de l'utilitaire "customMath.c"
 * Exécuter avec `gcc tests/check_custom_math2.c src/tools/*.c -lmpfr -lgmp -lbsd -o customTestMath`
 */
int test_stochastic_rounding() {
	int res = 0;
	nbRnd = 0;
	nbCorrectRnd = 0;

	FILE * logBuffer = stdout;

	/**
	 * The value to round.
	 */
	mpfr_t valToRound;

	mpfr_t mpfrNbIter;
	m_init2(mpfrNbIter, mpfr_get_default_prec());
	mpfr_set_si(mpfrNbIter, NB_ITER, MPFR_RNDN);

	// testing all the precisions
	for (long int initialPrecision = MPFR_PREC_MIN + 10 ;
			initialPrecision < MAX_TESTED_PRECISION /*100*/; ++initialPrecision) {

		mpfr_t maxValue;
		getMaxValue(&maxValue, initialPrecision);

		fprintf(logBuffer,
				"\n[%ld] - Start of stochastic rounding test for precision `%ld`. Changing target precision...\n",
				initialPrecision, initialPrecision);

		for (long int precisionToRoundTo = MPFR_PREC_MIN + 7 ;
				precisionToRoundTo < MAX_TESTED_PRECISION /*100*/; ++precisionToRoundTo) {
			fprintf(logBuffer, "[%ld]\t[%ld] - Target precision is now `%ld`. ", initialPrecision,
					precisionToRoundTo, precisionToRoundTo);
			int flagSign = 0;
			m_init2(valToRound, initialPrecision);

			fprintf(logBuffer, "Changing values...\n");
			// testing multiple values in the current range
			for (int j = 0 ; j < NB_VALUES ; ++j) {
				char logCurrentVal[12];
				// mpfr_min_prec (mpfr_t x)

				generateRandomValueInPrecisionRange(&valToRound, initialPrecision, maxValue,
						flagSign);

				// changing the sign alternatively (TODO is randomly a best choice for feeding?)
				// flagSign = !flagSign; // FIXME fix the negative rounding

				/* --------------------------------------- */
				/* ---- now, valToRound is a value in the needed range ---- */
				/* --------------------------------------- */
				// sprintf(logCurrentVal,"%f",mpfr_get_d(valToRound,MPFR_RNDN));
				fprintf(logBuffer, "[%ld]\t[%ld]\t(%d) - Starting to test the value `%f`. ",
						initialPrecision, precisionToRoundTo, j, mpfr_get_d(valToRound, MPFR_RNDN));

				mpfr_t actualResult;

				// once we have generated the needed value
				if (initialPrecision <= precisionToRoundTo) {
					// rounding to a greater precision ==> no need for actual rounding
					testExtendedRounding(&valToRound, &actualResult, initialPrecision,
							precisionToRoundTo, j, logBuffer);
					m_clear(actualResult);
				} else {

					// on détermine la valeur attendue (pourcentage d'arrondis vers le haut, pourcentage d'arrondis vers le bas)

					mpfr_t lastDigits;
					getLastDigits(&lastDigits, valToRound, initialPrecision, precisionToRoundTo);

					long int nbRoundUp = 0;

					fprintf(logBuffer, "Begin of loop over multiple stochastic roundings...\n");
					for (long int k = 0 ; k < NB_ITER ; ++k) {
						int roundingDirection;
						m_init2(actualResult, initialPrecision);
						mpfr_set(actualResult, valToRound, MPFR_RNDN); // no rounding shall be made since pre(actualResult)=pre(valToRound)
						// applying the stochastic rounding
						roundingDirection = stochasticRounding(&actualResult, precisionToRoundTo);
						// counting if it is upwards or downwards
						if (roundingDirection > 0) {
							nbRoundUp++;
						}
						m_clear(actualResult);
					}
					// et à la fin de la boucle on détermine combien ya de haut et de bas
					// et on le compare à la valeur attendue, avec une marge d'erreur à définir (mettons 5% pour commencer)
					mpfr_t maxLastDigitsValue;
					getMaxValue(&maxLastDigitsValue, (initialPrecision - precisionToRoundTo));
					mpfr_set_exp(maxLastDigitsValue, 1);
					mpfr_t expectedPctRoundUp;
					m_init2(expectedPctRoundUp, mpfr_get_default_prec() * 2);
					m_div(expectedPctRoundUp, lastDigits, maxLastDigitsValue, MPFR_RNDN);
					m_mul_si(expectedPctRoundUp, expectedPctRoundUp, 100L, RNDN);

					mpfr_t lowerBound;
					getBound(&lowerBound, expectedPctRoundUp, 0);
					mpfr_t upperBound;
					getBound(&upperBound, expectedPctRoundUp, 1);

					mpfr_t actualPctRoundUp;
					mpfr_init2(actualPctRoundUp, mpfr_get_default_prec());
					mpfr_t tmpNbRndUp;
					m_init2(tmpNbRndUp, mpfr_get_default_prec());
					mpfr_set_si(tmpNbRndUp, nbRoundUp, MPFR_RNDN);
					m_div(actualPctRoundUp, tmpNbRndUp, mpfrNbIter, MPFR_RNDN);
					m_mul_si(actualPctRoundUp, actualPctRoundUp, 100L, RNDN);

					fprintf(logBuffer, "------[%ld]\t[%ld]\t(%d)\t{%4f} - ", initialPrecision,
							precisionToRoundTo, j, mpfr_get_d(valToRound, MPFR_RNDN));
					fflush(logBuffer);
					mpfr_fprintf(logBuffer,
							"`%ld` rounding upwards, upon `%ld` roundings (%4.4Rf%1s)\n", nbRoundUp,
							NB_ITER, actualPctRoundUp, "%");
					fflush(logBuffer);
					/*mpfr_fprintf(logBuffer,
					 "\tShould be %Rb(%RF)/%Rb(%RF)=%4.4Rf%1s\n",
					 lastDigits, lastDigits, maxLastDigitsValue,
					 maxLastDigitsValue, expectedPctRoundUp, "%");*/
					mpfr_fprintf(logBuffer, "\tShould be %RF/%RF=%4.4Rf%1s\n", lastDigits,
							maxLastDigitsValue, expectedPctRoundUp, "%");
					++nbRnd;
					if (mpfr_greaterequal_p(actualPctRoundUp, lowerBound)
							|| mpfr_lessequal_p(actualPctRoundUp, upperBound)) {
						++nbCorrectRnd;
					}
					//getchar();

					m_clear(tmpNbRndUp);
					m_clear(actualPctRoundUp);
					m_clear(upperBound);
					m_clear(lowerBound);
					m_clear(expectedPctRoundUp);
					m_clear(maxLastDigitsValue);
					m_clear(lastDigits);
				}
			}
			// on refait ça pour la précision cible suivante
			m_clear(valToRound);
		}
		//m_clear(mInitPrec);
		m_clear(maxValue);
		//getchar();
	}

	m_clear(mpfrNbIter);

	printLine();
	printLine();
	printf(
			"\nLA VERITE : normalement on devrait avoir un pourcentage de correct rounding satisfaisant : %f%s\n",
			(double) nbCorrectRnd / (double) nbRnd * 100.0, "%");

	// on refait ça pour la précision initiale suivante
}

// --------------------------------------------------------

int main(void) {
	test_stochastic_rounding();
}

