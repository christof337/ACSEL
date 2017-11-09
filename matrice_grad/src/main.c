#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include <mpfr.h> // after stdio.h only

#include "matrice_grad.h"

#include "parameters.h"
#include "tools/arrayUtils.h"
#include "tools/matrixUtils.h"
#include "tools/customMath.h"
#include "tools/errorHandling.h"

#define PRECISION_MIN MPFR_PREC_MIN // 2

// compilation : ../make
// ce code est inspiré du programme "matrice_grad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 

int main( int argc, char *argv[] )  {
   int state = 0;

   char * appName = argv[0];
   int hasInitializeParams = initParams(appName);
   if( hasInitializeParams != 0 ) {
      printErrorMessage("Error while initializing application parameters.\n");
      state = -1;
   }else {
      state = handleParams(argc,argv);
      if ( state != 0 && state != 1 ) {
         printCustomError(ERROR_WHILE_HANDLING_INPUT_PARAMETERS, appName);
      } else if ( state != 1 ) {
         // printParam(getParamFromParamEnum(MATRIX_SIZE));

      	// DECLARATIONS
         // getting the params from param enum : 
            // enum paramsEnum { MATRIX_SIZE, NB_ITER, MAX_PREC, ROUNDING_MODE, MATRIX_TYPE}; 
         const int NB_GRAD = getParamFromParamEnum(NB_ITER).currentValue.li; // nombre d'itérations du gradient

         const int M_SIZE = getParamFromParamEnum(MATRIX_SIZE).currentValue.li;

         const int RANGE_PRECISION = getParamFromParamEnum(MAX_PREC).currentValue.li; // précision maximum utilisée TODO : la passer en paramètre du programme
         
         const mpfr_rnd_t RM = roundingModeEnumToMpfrRndT(getParamFromParamEnum(MAX_PREC).currentValue.rme);

         printf("\nDébut programme...");
         printf("\nParamètres :");
         printf("\n\tNombre d'itérations : %d",NB_GRAD);
         printf("\n\tTaille de la matrice : %d",M_SIZE);
         printf("\n\tPlage de précisions traitée : [%d,%d]\n",PRECISION_MIN, RANGE_PRECISION);

         printf("\nAppuyez sur une touche pour lancer le programme...");
         getchar();

         // DECLARATIONS DES TABLEAUX
         mpfr_t ** a;         // a
         mpfr_t * x;          // x
         mpfr_t * solgc;
         mpfr_t * gkgk2save;

         mpfr_t * b;          // b
         mpfr_t * gk;         // gk : gradient conjugué?
         mpfr_t * gkTmp;      // gk temporaire
         mpfr_t * dk;         // dk : ? 
         mpfr_t * adk;        // adk : ? 

         mpfr_t gkGkTmp1;
         mpfr_t adkDkTmp;
         mpfr_t alphak;
         mpfr_t gkgk2;
         mpfr_t gkGkTmp2;
         mpfr_t betak;

         mpfr_t * dkAlphakTmp;
         mpfr_t * adkAlphakTmp;
         mpfr_t * dkBetaKTmp;

         printf("\nDébut boucle principale itérant sur les précisions (non parrallélisée)");

         // DEBUT BOUCLE ( entièrement parralélisable )
         for (int pre = PRECISION_MIN ; pre < RANGE_PRECISION ; ++pre ) {
            printf("\n------\tBoucle precision [%d]\t------",pre);

         	// INITIALISATIONS
            printf("\n\tInitialisation des tableaux");
            // ALLOCATIONS
            createArray(&x,M_SIZE,pre); 
            createMatrix(&a,M_SIZE, M_SIZE,pre);

            createArray(&solgc,M_SIZE,pre);
            createArray(&b,M_SIZE,pre);
            createArray(&gkTmp,M_SIZE,pre);
            createArray(&gk,M_SIZE,pre);
            createArray(&dk,M_SIZE,pre);
            createArray(&adk,M_SIZE,pre);

            createArray(&gkgk2save,NB_GRAD,pre);

            printf("\n\tAllocation des variables MPFR");
            m_init2(gkGkTmp1,pre);
            m_init2(adkDkTmp,pre);
            m_init2(alphak,pre);
            m_init2(gkgk2,pre);
            m_init2(gkGkTmp2,pre);
            m_init2(betak,pre);

            printf("\n\tInitialisation des tableaux temporaires");
            createArray(&dkAlphakTmp,M_SIZE,pre);
            createArray(&adkAlphakTmp,M_SIZE,pre);
            createArray(&dkBetaKTmp,M_SIZE,pre);

            printf("\n\tRemplissage des tableaux");
            // initialisation de a
            fillMatrixExponentially(a, M_SIZE, M_SIZE);

            // initialisation de x linéairement
            fillArrayLinearly(x, M_SIZE);

            printf("\n\tDébut des calculs");

            // on multiplie a et x ( B = AX )
            customMatrixMultVector(b, a, x, M_SIZE);

            fillArrayWithZeros(solgc, M_SIZE);

            // on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
            // gradient conjugué
            // GK = A * XX - B
            customMatrixMultVector(gkTmp,a,solgc,M_SIZE);
            vectorMinusVector(gk, gkTmp, M_SIZE, b, M_SIZE);

            // DK = GK
            vectorCopy(dk, gk, M_SIZE);

            printf("\n\t-- Itérations du gradient... --");
            // on itère sur le nombre d'itérations déterminé par NB_GRAD
            for ( int iter = 0 ; iter < NB_GRAD ; ++iter ) {
               // ADK = A * DK
               customMatrixMultVector(adk, a, dk, M_SIZE);
               // GKGK = GK * GK
               innerDotProduct(gkGkTmp1, gk, M_SIZE); // gkgk

               // ADKDK = ADK * DK
               dotProduct(adkDkTmp, adk, M_SIZE, dk, M_SIZE); // adkdk
               // AlphaK = GKGK / ADKDK ==> AlphaK = (GK*GK)/(ADK*DK)
               m_div(alphak,gkGkTmp1,adkDkTmp,RM);

               // XX = XX - AlphaK * DK
               vectorMultValue(dkAlphakTmp, dk, M_SIZE, alphak);
               vectorMinusVector(solgc, solgc, M_SIZE, dkAlphakTmp, M_SIZE);

               // GK = GK - AlphaK * ADK
               vectorMultValue(adkAlphakTmp, adk, M_SIZE, alphak);
               vectorMinusVector(gk, gk, M_SIZE, adkAlphakTmp, M_SIZE);

               // gkgk2 = sqrt of (square sum of gk elements)
               sumSquare(gkgk2, gk,M_SIZE);
               mpfr_sqrt(gkgk2, gkgk2,RM);
               // GKGK = GK*GK
               innerDotProduct(gkGkTmp2, gk, M_SIZE); // pertinent car changements réalisés sur gk depuis gkgkTmp1
               m_div(betak, gkGkTmp2,gkGkTmp1,RM);
               // DK = GK + BetaK*DK
               vectorMultValue(dkBetaKTmp, dk, M_SIZE, betak);
               vectorPlusVector(dk, gk, M_SIZE, dkBetaKTmp, M_SIZE);

               // sauvegarde
               mpfr_set(gkgk2save[iter], gkgk2, RM);

               // libérations mémoire
               //free(dkAlphakTmp);
               //free(solgcTmp);
               //free(adkAlphakTmp);
               //free(gkTmp);
               //free(dkBetaKTmp);
            }

            printf("\n\tEcriture de la matrice a dans un fichier (output/matrix.dat)");
            // écriture de la matrice a dans un fichier
            int error = writeMatrixInFile(a, M_SIZE, M_SIZE, pre);
            if ( error != 0 ) {
               // error
               state = error;
            }

            printf("\n\tEcriture de i, x(i) et solgc(i) dans un fichier (output/solggc.dat)");
            // écriture de i, x(i) et solgc(i) dans un fichier solggc.dat
            error = writeDataInFile(x,solgc,M_SIZE, pre);
            if ( error != 0 ) {
               // error
               state = error;
            }

            printf("\n\tEcriture de gkgk2 dans un fichier (output/gkgk.dat)");
            // écriture de gkgk2 dans un fichier gkgk.dat
            error = writeGkArrayInFile(gkgk2save,NB_GRAD, pre);
            if ( error != 0 ) {
               // error
               state = error;
            }

            printf("\n\tLibérations des variables");
            m_clear(gkGkTmp1);
            m_clear(adkDkTmp);
            m_clear(alphak);
            m_clear(gkgk2);
            m_clear(gkGkTmp2);
            m_clear(betak);

            printf("\n\tLibérations des tableaux");
            freeArray(x,M_SIZE); 
            freeMatrix(a,M_SIZE, M_SIZE);
            freeArray(b,M_SIZE);
            freeArray(solgc,M_SIZE);
            freeArray(gkgk2save,NB_GRAD);
            freeArray(gk, M_SIZE);
            freeArray(dk, M_SIZE);
            freeArray(adk, M_SIZE);
            freeArray(gkTmp, M_SIZE);

            freeArray(dkAlphakTmp,M_SIZE);
            freeArray(adkAlphakTmp,M_SIZE);
            freeArray(dkBetaKTmp,M_SIZE);
            
         } // fin boucle principale (pre)

         // désallocation des tableaux
         //freeArray(x, M_SIZE);
         //freeArray(b, M_SIZE);
         //freeArray(gk, M_SIZE);
         //freeArray(dk, M_SIZE);
         //freeArray(adk, M_SIZE);
         //freeArray(solgc, M_SIZE);
         //freeArray(gkTmp, M_SIZE);
         //freeMatrix(a, M_SIZE, M_SIZE);
      }
   }
   if ( state == 0 ) {
      printf("\nFIN PROGRAMME NORMAL\n");
   } else if ( state == 1 ) {
      printf("\nClosing help...\n");
      printLine();
   } else {
      printFinalErrorStatement();
   }

   return state;
}