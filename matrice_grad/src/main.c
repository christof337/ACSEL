#include <stdio.h>

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
   double a[TAILLE_MATRICE][TAILLE_MATRICE];    // a
   double x[TAILLE_MATRICE];                    // x
   double b[TAILLE_MATRICE];                    // b
   // int xx[TAILLE_MATRICE];                   // xx : /!\ nom non explicite
   // int gk[TAILLE_MATRICE];                   // gk : gradient conjugué?
   // int agk[TAILLE_MATRICE];                  // agk : ?
   // int dk[TAILLE_MATRICE];                   // dk : ? 
   // int adk[TAILLE_MATRICE];                  // adk : ? 
   // int solgc[TAILLE_MATRICE]; 

   // ALLOCATIONS


	// INITIALISATIONS

   // initialisation de b à 0
	fillArrayWithZeros(b,TAILLE_MATRICE);

   // initialisation de a
   fillMatrixExponentially(TAILLE_MATRICE, TAILLE_MATRICE, a);

   // initialisation de x linéairement
   fillArrayLinearly(x, TAILLE_MATRICE);

   //    b=matmul(a,x)  !cible



   // écriture de la matrice a dans un fichier matrix.dat

   // désallocation des tableaux
   // gsl_matrix_free(a);
   // free(x);
   // free(b);
   // gsl_vector_free(xx);
   // gsl_vector_free(gk);
   // gsl_vector_free(agk);
   // gsl_vector_free(dk);
   // gsl_vector_free(adk);
   // gsl_vector_free(solgc);

   return 0;
}

