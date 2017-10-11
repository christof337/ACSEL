#include <stdio.h>
#include <stdlib.h>

#include "matrice_grad.h"

#include "tools/arrayUtils.h"
#include "tools/matrixUtils.h"

// compilation : ../make
// ce code est inspiré du programme "matrice_grad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 

int main() {

	// DECLARATIONS
   const int NB_GRAD = 30; // nombre d'itérations du gradient

   const int TAILLE_MATRICE = askTailleMatrice();

   // DECLARATIONS DES TABLEAUX
   double ** a = createMatrix(TAILLE_MATRICE, TAILLE_MATRICE);    // a

   double * x = createArray(TAILLE_MATRICE);                    // x
   
   // ALLOCATIONS
   double * b = createArray(TAILLE_MATRICE);    // b
   // int xx[TAILLE_MATRICE];                   // xx : /!\ nom non explicite
   // int gk[TAILLE_MATRICE];                   // gk : gradient conjugué?
   // int agk[TAILLE_MATRICE];                  // agk : ?
   // int dk[TAILLE_MATRICE];                   // dk : ? 
   // int adk[TAILLE_MATRICE];                  // adk : ? 
   // int solgc[TAILLE_MATRICE]; 


	// INITIALISATIONS
   // initialisation de b à 0
	b = fillArrayWithZeros(b, TAILLE_MATRICE);

   // initialisation de a
   a = fillMatrixExponentially(a, TAILLE_MATRICE, TAILLE_MATRICE);

   // initialisation de x linéairement
   x = fillArrayLinearly(x, TAILLE_MATRICE);

   // on multiplie a et x ( B = AX )
   b = matrixMultVector(a, TAILLE_MATRICE, TAILLE_MATRICE, x, TAILLE_MATRICE);

   printArray(b, TAILLE_MATRICE);

   // on se propose de réaliser une inversion par minimisation d'énergie (descente de gradient)



   // écriture de la matrice a dans un fichier matrix.dat

   // désallocation des tableaux
   free(x);
   free(b);
   freeMatrix(a, TAILLE_MATRICE, TAILLE_MATRICE);

   return 0;
}

