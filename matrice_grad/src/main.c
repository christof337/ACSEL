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

				mpfr_t * metaGkgk2save[NB_GRAD];
				pthread_t threads[RANGE_PRECISION - PRECISION_MIN];
				int threadState;
				int nbThreads=0;

				// DEBUT BOUCLE ( entièrement parralélisable )
//#pragma acc parallel loop
				for (int pre = PRECISION_MIN ; pre < RANGE_PRECISION ; ++pre) {
					threadState = pthread_create(&threads[nbThreads], NULL,
							customConjuguateGradientDescentThreadWrapper, (void*) pre);
					if (threadState) {
						fprintf(stderr, "\n[%d]Thread error : %s", pre, strerror(threadState));
						exit(EXIT_FAILURE);
					} else {
						nbThreads++;
					}
					// CONJUGUATE GRADIENT DESCENT METHOD
//					/*state += */conjuguateGradientDescent(pre, M_SIZE, NB_GRAD, M_TYPE,
//							RME/*, metaGkgk2save*/);
				}
				// fin boucle principale (pre)

				for(int i = 0; i < nbThreads;i++) {
					// in order to wait for everyone to finish
					pthread_join(threads[i],NULL);
				}

				int closeSuccess;
				closeSuccess = closeLogFiles();
				if(closeSuccess != 0 ) {
					printErrorMessage("Error while closing log files");
				}
				state += closeSuccess;

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

	return state;
}
