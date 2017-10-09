#include <stdio.h>

#include "matrice_grad.h"

#include "tools/inputOutput.h"

int askTailleMatrice() {
	int tailleMatrice = 0;
	do {
		printf("Taille Matrice ?\n");
		tailleMatrice = askForInt();
	}while ( tailleMatrice <= 0 );
}
