#include <stdio.h>

#include <mpfr.h> // after stdio.h only
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "tools/customMath.h"
#include "tools/errorHandling.h"
#include "tools/timer.h"
#include "tools/utils.h"
#include "matrice_grad.h"
#include "parameters.h"
#include "log.h"

#define PRECISION_MIN MPFR_PREC_MIN // 2 TODO : enable the user to choose the minimum precision

#define DEBUG 1

#define PARALLEL 0

#define LORENTZ 1

#if defined (Linux)
#  include <unistd.h>
#  define psleep(sec) sleep ((sec))
#endif

// compilation : ../make
// ce code est inspiré du programme "matrice_grad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 
// quick run : src/main ms=100 ni=30 pre=16 rm=STOCHASTIC
// long run : src/main ms=3000 ni=100 rm=STOCHASTIC

int main(int argc, char *argv[]) {
	if ( LORENTZ) {
		/*
		 int llorenzAttractor(const mpfr_prec_t precision, const long int nbIterations,
		 const enum roundingModeEnum rme, const char * sigmaStr, const char * roStr,
		 const char * betaStr) {*/
		//		llorenzAttractor(128, 100000L, RNDN, "9", "26", "2.6");
		llorenzAttractor(128, 100000L, RNDN, NULL, NULL, NULL);

		return 0;
	}
	NB_STOCH_ROUND = 0;
	int state = EXIT_SUCCESS;
	if (DEBUG == 3) {
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
	} else {

		char * appName = argv[0];
		int hasInitializeParams = initParams(appName);
		if (hasInitializeParams != 0) {
			printErrorMessage("Error while initializing application parameters.\n");
			state = -1;
		} else {
			printf("\nHandling parameters...");
			fflush(stdout);
			state = handleParams(argc, argv);
			if (state != 0 && state != 1) {
				printErrorMessage("\nInput error. Abort execution.\n");
			} else if (state != 1) {
				// printParam(getParamFromParamEnum(MATRIX_SIZE));

				// DECLARATIONS
				// getting the params from param enum :
				const int NB_GRAD = getParamFromParamEnum(NB_ITER)->currentValue.li; // nombre d'itérations du gradient
				const size_t M_SIZE = getParamFromParamEnum(MATRIX_SIZE)->currentValue.s;
				const int RANGE_PRECISION = getParamFromParamEnum(MAX_PREC)->currentValue.li; // précision maximum utilisée
				const enum roundingModeEnum RME = getParamFromParamEnum(ROUNDING_MODE)->currentValue.rme;
				const enum matrixTypeEnum M_TYPE = getParamFromParamEnum(MATRIX_TYPE)->currentValue.mte;

				printf("\nDébut programme...");
				printf("\nParamètres :");
				printf("\n\tNombre d'itérations : %d", NB_GRAD);
				printf("\n\tTaille de la matrice : %zu", M_SIZE);
				printf("\n\tPlage de précisions traitée : [%d,%d]\n", PRECISION_MIN,
						RANGE_PRECISION);
				printf("\nAppuyez sur une touche pour lancer le programme...");
				getchar();

				initLogFiles();

				StartTimer();

				printf("\nDébut boucle principale itérant sur les précisions\n");

//				mpfr_t * metaGkgk2save[NB_GRAD];
				pthread_t threads[RANGE_PRECISION - PRECISION_MIN];
				int threadState;
				int nbThreads = 0;

				initGkgk2_global(RANGE_PRECISION - PRECISION_MIN + 1, NB_ITER);

				if ( PARALLEL) {
					// parallelize
					printf("\nLancement des threads");
					printProgressBarLine(RANGE_PRECISION - PRECISION_MIN);
					printf("|");

					// DEBUT BOUCLE ( entièrement parralélisée )
//#pragma acc parallel loop
					for (long int pre = PRECISION_MIN ; pre <= RANGE_PRECISION ; ++pre) {
						// CONJUGUATE GRADIENT DESCENT METHOD
						threadState = pthread_create(&threads[nbThreads], NULL,
								customConjuguateGradientDescentThreadWrapper, &pre);
						if (threadState) {
							fprintf(stderr, "\n[%ld]Thread error : %s", pre, strerror(threadState));
							exit(EXIT_FAILURE);
						} else {
							printf(".");
							fflush(stdout);
							nbThreads++;
						}
					}
					printf("|\n");
					// fin boucle principale (pre)
					printf("\nRécupération des threads...");
					printProgressBarLine(nbThreads);
					printf("|");
					fflush(stdout);
					for (int i = 0 ; i < nbThreads ; i++) {
						// in order to wait for everyone to finish
						pthread_join(threads[i], NULL);
						printf(".");
						fflush(stdout);
					}
					printf("|\n");
					fflush(stdout);
				} else {
					// not parallelized
					// sequential loop over the precisions
					for (mpfr_prec_t pre = PRECISION_MIN ; pre <= RANGE_PRECISION ; ++pre) {
						conjuguateGradientDescent(pre, M_SIZE, NB_GRAD, M_TYPE, RME);
						printf("Fin de la descente de gradient de précision `%ld`.\n", pre);
					}
				}
				printLine();
				printf("--------End of iterations--------");
				printLine();

				// when everything's good, writing gkgk2_global to a file
				printf("Writing gkgk2 to a file...\n");
				writeGkgk2_global(RANGE_PRECISION - MPFR_PREC_MIN, NB_GRAD);

				int closeSuccess;
				closeSuccess = closeLogFiles(); // shouldn't work now but doesn't matter
				if (closeSuccess != 0) {
					printErrorMessage("Error while closing log files");
				}
//				state += closeSuccess;

				double runtime = GetTimer();

				printf(" \n\nTotal time ellapsed: %f s\n", runtime / 1000);

				printf("\nParameters reminder:");
				printf("\n\tNombre d'itérations : %d", NB_GRAD);
				printf("\n\tTaille de la matrice : %zu", M_SIZE);
				printf("\n\tPlage de précisions traitée : [%d,%d]\n", PRECISION_MIN,
						RANGE_PRECISION);
				printf("\nFin programme.");
				fflush(stdout);
			}
		}

//		printf("\n\n--Stochastic rounding has been called %ld times.\n",NB_STOCH_ROUND);

		if (state == 0) {
			printf("\nFIN PROGRAMME NORMAL\n");
		} else if (state == 1) {
			printf("\nClosing help...");
			printLine();
		} else {
			printFinalErrorStatement();
		}
	}

	mpfr_free_cache();
	clearRandState();

	return state;
}
