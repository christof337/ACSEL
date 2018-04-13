#include <stdio.h>

#include <mpfr.h> // after stdio.h only
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "tools/customMath.h"
#include "tools/errorHandling.h"
#include "tools/timer.h"
#include "tools/utils.h"
#include "tools/matrixUtils.h"
#include "tools/arrayUtils.h"
#include "matrice_grad.h"
#include "parameters.h"
#include "log.h"

#define PRECISION_MIN MPFR_PREC_MIN // 2 TODO : enable the user to choose the minimum precision

#ifndef DEBUG
#	define DEBUG 0
#endif

#if defined (Linux)
#  include <unistd.h>
#  define psleep(sec) sleep ((sec))
#endif

// comment when you want a normal usage
// #define NB_STOCH_RUNS 50

// compilation : ../make
// ce code est inspiré du programme "matrice_grad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 
// quick run : src/main ms=100 ni=30 pre=16 rm=STOCHASTIC
// long run : src/main ms=3000 ni=100 rm=STOCHASTIC

int main(int argc, char *argv[]) {
	int state = EXIT_SUCCESS;
#if (DEBUG==3)
	// test
	quickTestStochasticRounding();
#else
	char * appName = argv[0];
	int hasInitializeParams = initParams(appName);
	if (hasInitializeParams != 0) {
		printErrorMessage("Error while initializing application parameters.\n");
		state = -1;
	} else {
		printf("\nHandling parameters...\n");
		fflush(stdout);
		state = handleParams(argc, argv);
		if (state != 0 && state != 1) {
			printErrorMessage("\nInput error. Abort execution.\n");
		} else if (state != 1) {
			const int RANGE_PRECISION = getParamFromParamEnum(MAX_PREC)->currentValue.li; // précision maximum utilisée
			const enum roundingModeEnum RME = getParamFromParamEnum(ROUNDING_MODE)->currentValue.rme;
			const int IS_PARALLEL = getParamFromParamEnum(PARALLEL)->currentValue.li;
			// Get to know which program the user wants to run
			const enum modelEnum MODEL_SELECTED = getParamFromParamEnum(MODEL)->currentValue.me;
			StartTimer();
			if (MODEL_SELECTED == CGD) {
				/* Conjuguate gradient method */

				// DECLARATIONS
				// getting the params from param enum :
				const int NB_GRAD = getParamFromParamEnum(NB_ITER)->currentValue.li; // nombre d'itérations du gradient
				const size_t M_SIZE = getParamFromParamEnum(MATRIX_SIZE)->currentValue.s;
				const enum matrixTypeEnum M_TYPE = getParamFromParamEnum(MATRIX_TYPE)->currentValue.mte;

				printf("\nDébut programme...");
				printf("\nParamètres :");
				printf("\n\tNombre d'itérations : %d", NB_GRAD);
				printf("\n\tTaille de la matrice : %zu", M_SIZE);
				printf("\n\tPlage de précisions traitée : [%d,%d]\n", PRECISION_MIN,
						RANGE_PRECISION);
				printf("\nAppuyez sur une touche pour lancer le programme...");
				getchar();

				initLogFiles(MODEL_SELECTED);

				printf("\nDébut boucle principale itérant sur les précisions\n");

				initGkgk2_global(RANGE_PRECISION - PRECISION_MIN + 1, NB_GRAD);

				if (IS_PARALLEL) {
					//				mpfr_t * metaGkgk2save[NB_GRAD];
					pthread_t threads[RANGE_PRECISION - PRECISION_MIN];
					int threadState;
					int nbThreads = 0;

					// parallelize
					printf("\nLancement des threads");
					printProgressBarLine(RANGE_PRECISION - PRECISION_MIN);
					printf("|");

					// DEBUT BOUCLE ( entièrement parallélisée )
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
				writeGkgk2_global(RANGE_PRECISION - MPFR_PREC_MIN, NB_GRAD, MODEL_SELECTED);

				int closeSuccess;
				closeSuccess = closeLogFiles(); // shouldn't work now but doesn't matter
				if (closeSuccess != 0) {
					printErrorMessage("Error while closing log files");
				}
				//				state += closeSuccess;

				printf("\nParameters reminder:");
				printf("\n\tNombre d'itérations : %d", NB_GRAD);
				printf("\n\tTaille de la matrice : %zu", M_SIZE);
				printf("\n\tPlage de précisions traitée : [%d,%d]\n", PRECISION_MIN,
						RANGE_PRECISION);
				printf("\nFin programme.");
				fflush(stdout);
			} else if (MODEL_SELECTED == LORENZ) {
				/* LORENZ ATTRACTOR */

				long int NB_ITERATIONS; // nombre d'itérations de lorenz
				if (getParamFromParamEnum(NB_ITER)->isDefault) {
					getParamFromParamEnum(NB_ITER)->currentValue.li = getDefaultNbIterValue();
				}
				NB_ITERATIONS = getParamFromParamEnum(NB_ITER)->currentValue.li;

				if (IS_PARALLEL) {
#ifdef NB_STOCH_RUNS
					for (long int it = 0; it < NB_STOCH_RUNS; ++it) {
						printf("run %ld...\n", it);
#endif
					// parallelize runs
					pthread_t threads[RANGE_PRECISION - PRECISION_MIN];
					int threadState;
					int nbThreads = 0;

					// parallelize
//							printf("\nLancement des threads");
//							printProgressBarLine(RANGE_PRECISION - PRECISION_MIN);
//							printf("|");

					// DEBUT BOUCLE ( entièrement parallélisée )
					//#pragma acc parallel loop
					for (long int pre = PRECISION_MIN ; pre <= RANGE_PRECISION ; ++pre) {
						// CONJUGUATE GRADIENT DESCENT METHOD
						threadState = pthread_create(&threads[nbThreads], NULL,
								customLorenzAttractorThreadWrapper, &pre);
						if (threadState) {
							fprintf(stderr, "\n[%ld]Thread error : %s", pre, strerror(threadState));
							exit(EXIT_FAILURE);
						} else {
//									printf(".");
//									fflush(stdout);
							nbThreads++;
						}
					}
//							printf("|\n");
					// fin boucle principale (pre)
//							printf("\nRécupération des threads...");
//							printProgressBarLine(nbThreads);
//							printf("|");
//							fflush(stdout);
					for (int i = 0 ; i < nbThreads ; i++) {
						// in order to wait for everyone to finish
						pthread_join(threads[i], NULL);
#ifdef NB_STOCH_RUNS
						changeLorenzFileName(i + MPFR_PREC_MIN, it);
					}
#endif
//								printf(".");
//								fflush(stdout);
					}
//							printf("|\n");
//							fflush(stdout);
				} else {
					const double V_SIGMA = getParamFromParamEnum(SIGMA)->currentValue.d;
					const double V_RO = getParamFromParamEnum(RO)->currentValue.d;
					const double V_BETA = getParamFromParamEnum(BETA)->currentValue.d;
					// not parallelized
#ifdef NB_STOCH_RUNS
					for (long int it = 0; it < NB_STOCH_RUNS; ++it) {
						printf("run %ld...\n", it);
#endif
					for (long int pre = PRECISION_MIN ; pre <= RANGE_PRECISION ; ++pre) {
//							printf("Lorenz [%ld] :\n", pre);

						state = lorenzAttractor(pre, NB_ITERATIONS, RME, V_SIGMA, V_RO, V_BETA);

						if (state == EXIT_FAILURE) {
							// error
							fprintf(stderr,
									"Error while handling Lorenz Attractor for precision `%ld`.\n",
									pre);
							return state;
						}

#ifdef NB_STOCH_RUNS
						changeLorenzFileName(pre, it);
					}
					clearRandState();
#endif
					}
				}
			}
			double runtime = GetTimer();
			printf(" \n\nTotal time ellapsed: %f s\n", runtime / 1000);
		}

		freeParams();
	}

	if (state == 0) {
		printf("\nFIN PROGRAMME NORMAL\n");
	} else if (state == 1) {
		printf("\nClosing help...");
		printLine();
	} else {
		printFinalErrorStatement();
	}
#endif

	mpfr_free_cache();
	clearRandState();

	return state;
}
