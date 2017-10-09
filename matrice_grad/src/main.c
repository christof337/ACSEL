#include <stdio.h>

#include "matrice_grad.h"

#include "tools/arrayUtils.h"

// compilation : gcc src/*.c src/tools/*.c -o matrice_grad
// ce code est inspiré du programme "matricegrad".
// l'objectif est de faire varier la précision pour observer le comportement de réduction du gradient 

int main() {

	// DECLARATIONS

	const int TAILLE_MATRICE = askTailleMatrice();
   	
   	int a[TAILLE_MATRICE][TAILLE_MATRICE]; 	// a
   	int x[TAILLE_MATRICE]; 		 			// x
   	int b[TAILLE_MATRICE]; 					// b
   	int xx[TAILLE_MATRICE]; 				// xx : /!\ nom non explicite
   	int gk[TAILLE_MATRICE];					// gk : gradient conjugué?
   	int agk[TAILLE_MATRICE];				// agk : ?
   	int dk[TAILLE_MATRICE];					// dk : ? 
   	int adk[TAILLE_MATRICE];				// adk : ? 
   	int solgc[TAILLE_MATRICE];				// solgc : solution gradient conjugué ? 

   	const int NB_GRAD = 30; // nombre d'itérations du gradient

   	// INITIALISATIONS

   	fillArrayWithZeros(b,TAILLE_MATRICE);
  
   	return 0;
}

