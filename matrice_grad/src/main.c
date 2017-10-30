#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrice_grad.h"

#include "tools/arrayUtils.h"
#include "tools/matrixUtils.h"

// compilation : ../make
// ce code est inspiré du programme "matrice_grad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 

int main() {
   int state = 0;

	// DECLARATIONS
   const int NB_GRAD = 30; // nombre d'itérations du gradient

   const int M_SIZE = askTailleMatrice();

   // DECLARATIONS DES TABLEAUX
   double * b;          // b
   double * gk;         // gk : gradient conjugué?
   double * gkTmp;      // gk temporaire
   double ** a;         // a
   double * x;          // x
   double * dk;         // dk : ? 
   double * adk;        // adk : ? 
   double * solgc;
   double * gkgk2save;
   
   // ALLOCATIONS
   x = createArray(M_SIZE); 
   a = createMatrix(M_SIZE, M_SIZE);
   solgc = createArray(M_SIZE);
   gkgk2save = createArray(NB_GRAD);

	// INITIALISATIONS
   // initialisation de a
   a = fillMatrixExponentially(a, M_SIZE, M_SIZE);

   // initialisation de x linéairement
   x = fillArrayLinearly(x, M_SIZE);

   // on multiplie a et x ( B = AX )
   b = customMatrixMultVector(a, x, M_SIZE);


   solgc = fillArrayWithZeros(solgc, M_SIZE);

   // on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
   // gradient conjugué
   // GK = A * XX - B
   gkTmp = customMatrixMultVector(a,solgc,M_SIZE);
   gk = vectorMinusVector(gkTmp, M_SIZE, b, M_SIZE);


   // DK = GK
   dk = vectorCopy(gk, M_SIZE);

   // on itère sur le nombre d'itérations déterminé par NB_GRAD
   for ( int iter = 0 ; iter < NB_GRAD ; ++iter ) {
      // ADK = A * DK
      adk = customMatrixMultVector(a, dk, M_SIZE);
      // GKGK = GK * GK
      double gkGkTmp1 = innerDotProduct(gk, M_SIZE); // gkgk

      // ADKDK = ADK * DK
      double adkDkTmp = dotProduct(adk, M_SIZE, dk, M_SIZE); // adkdk
      // AlphaK = GKGK / ADKDK ==> AlphaK = (GK*GK)/(ADK*DK)
      double alphak = gkGkTmp1 / adkDkTmp;

      // XX = XX - AlphaK * DK
      double * dkAlphakTmp = vectorMultDouble(dk, M_SIZE, alphak);
      double * solgcTmp = solgc;
      solgc = vectorMinusVector(solgcTmp, M_SIZE, dkAlphakTmp, M_SIZE);

      // GK = GK - AlphaK * ADK
      double * adkAlphakTmp = vectorMultDouble(adk, M_SIZE, alphak);
      double * gkTmp = gk;
      gk = vectorMinusVector(gkTmp, M_SIZE, adkAlphakTmp, M_SIZE);

      // gkgk2 = sqrt of (square sum of gk elements)
      double gkgk2 = sumSquare(gk,M_SIZE);
      gkgk2 = sqrt(gkgk2);
      // GKGK = GK*GK
      double gkGkTmp2 = innerDotProduct(gk, M_SIZE); // pertinent car changements réalisés sur gk depuis gkgkTmp1
      double betak = gkGkTmp2 / gkGkTmp1;
      // DK = GK + BetaK*DK
      double * dkBetaKTmp = vectorMultDouble(dk, M_SIZE, betak);
      double * dkTmp = dk;
      dk = vectorPlusVector(gk, M_SIZE, dkBetaKTmp, M_SIZE);

      // sauvegarde
      gkgk2save[iter] = gkgk2;

      // libérations mémoire
      free(dkAlphakTmp);
      free(solgcTmp);
      free(adkAlphakTmp);
      free(gkTmp);
      free(dkBetaKTmp);
      free(dkTmp);
   }

   // écriture de la matrice a dans un fichier
   int error = writeMatrixInFile(a, M_SIZE, M_SIZE);
   if ( error != 0 ) {
      // error
      state = error;
   }

   // écriture de i, x(i) et solgc(i) dans un fichier solggc.dat
   error = writeDataInFile(x,solgc,M_SIZE);
   if ( error != 0 ) {
      // error
      state = error;
   }

   // écriture de gkgk2 dans un fichier gkgk.dat
   error = writeArrayInFile(gkgk2save,NB_GRAD);
   if ( error != 0 ) {
      // error
      state = error;
   }

   // désallocation des tableaux
   free(x);
   free(b);
   free(gk);
   free(dk);
   free(adk);
   free(solgc);
   free(gkTmp);
   freeMatrix(a, M_SIZE, M_SIZE);

   if ( state == 0 ) {
      printf("\nFIN PROGRAMME NORMAL\n");
   } else {
      printFinalStatement();
   }

   return state;
}