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

	// DECLARATIONS
   const int NB_GRAD = 30; // nombre d'itérations du gradient

   const int M_SIZE = askTailleMatrice();

   // DECLARATIONS DES TABLEAUX
   double * b;          // b
   double * gk;         // gk : gradient conjugué?
   double * gkTmp;      // gk temporaire
   double ** a;         // a
   double * x;          // x
   double * xx;
   double * dk;         // dk : ? 
   double * adk;        // adk : ? 
   
   // ALLOCATIONS
   x = createArray(M_SIZE); 
   xx = createArray(M_SIZE);   // xx : /!\ nom non explicite
   a = createMatrix(M_SIZE, M_SIZE);
   // int agk[M_SIZE];                  // agk : ?
   // int dk[M_SIZE];                   // dk : ? 
   // int adk[M_SIZE];                  
   // int solgc[M_SIZE]; 


	// INITIALISATIONS
   // initialisation de a
   a = fillMatrixExponentially(a, M_SIZE, M_SIZE);

   // initialisation de x linéairement
   x = fillArrayLinearly(x, M_SIZE);

   // on multiplie a et x ( B = AX )
   b = customMatrixMultVector(a, x, M_SIZE);

   xx = fillArrayWithZeros(xx, M_SIZE);

   // on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)
   // gradient conjugué
   // GK = A * XX - B
   gkTmp = customMatrixMultVector(a,xx,M_SIZE);
   gk = vectorLessVector(gkTmp, M_SIZE, b, M_SIZE);
   free(gkTmp);

   // DK = GK
   dk = vectorCopy(gk, M_SIZE);

   // on itère sur le nombre d'itérations déterminé par NB_GRAD
   for ( int iter = 0 ; iter < NB_GRAD ; ++iter ) {
      // ADK = A * DK
      adk = customMatrixMultVector(a, dk, M_SIZE);
      // GKGK = GK * GK
      double gkGkTmp = innerDotProduct(gk, M_SIZE); // gkgk
      // ADKDK = ADK * DK
      double adkDkTmp = dotProduct(adk, M_SIZE, dk, M_SIZE); // adkdk
      // AlphaK = GKGK / ADKDK ==> AlphaK = (GK*GK)/(ADK*DK)
      double alphak = gkGkTmp / adkDkTmp;

      // XX = XX - AlphaK * DK
      double * dkAlphakTmp = vectorMultDouble(dk, M_SIZE, alphak);
      double * xxTmp = xx;
      xx = vectorLessVector(xxTmp, M_SIZE, dkAlphakTmp, M_SIZE);
      free(dkAlphakTmp);
      free(xxTmp);

      // GK = GK - AlphaK * ADK
      double * adkAlphakTmp = vectorMultDouble(adk, M_SIZE, alphak);
      double * gkTmp = gk;
      gk = vectorLessVector(gkTmp, M_SIZE, adkAlphakTmp, M_SIZE);
      free(adkAlphakTmp);
      free(gkTmp);

      // gkgk2 = square sum of elements
      double gkgk2 = sumSquare(gk,M_SIZE);

   }

   // écriture de la matrice a dans un fichier matrix.dat

   printf("\nx :\n");
   printArray(x, M_SIZE);
   printf("\nxx :\n");
   printArray(xx, M_SIZE);
   printf("\nb :\n");
   printArray(b, M_SIZE);
   printf("\nGK :\n");
   printArray(gk, M_SIZE);
   printf("\nDK :\n");
   printArray(dk, M_SIZE);
   printf("\nADK :\n");
   printArray(adk, M_SIZE);
   // désallocation des tableaux
   free(x);
   free(xx);
   free(b);
   free(gk);
   free(dk);
   free(adk);
   freeMatrix(a, M_SIZE, M_SIZE);

   return 0;
}