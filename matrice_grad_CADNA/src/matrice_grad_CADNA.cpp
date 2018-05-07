//============================================================================
// Name        : matrice_grad_CADNA.cpp
// Author      : Kito
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "SAM.h"
#include <assert.h>
using namespace std;

#define PREC_MIN 2
#define PREC_MAX 200

//#define NUMBER_OF_ITERATIONS 100000
#define NUMBER_OF_ITERATIONS 10000

std::string buildFileName(const unsigned int precision) {
	// output/lorenz_prec=2_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat
	std::string folder = "output";
	std::string prefix = "lorenz_prec=";
	std::string suffix = "_mp=200_ni=100000_rm=CADNA_si=10.000000_ro=28.000000_be=2.666700.dat";

	return folder + "/" + prefix + std::to_string(precision) + suffix;
}

void writeMpstMatrixInFile(const unsigned int precision, mp_st results[NUMBER_OF_ITERATIONS][3]) {
	size_t size = NUMBER_OF_ITERATIONS;
	std::string fileName = "";

	fileName = buildFileName(precision);

	ofstream outfile;
	outfile.open(fileName);
	outfile << "x\ty\tz" << endl;

	for ( size_t i = 0 ; i < size ; ++i ) {
		for ( short int j = 0 ; j < 3 ; ++j ) {
			outfile << results[i][j] << "\t";
		}
		outfile << endl;
	}

	outfile.close();
}

void lorenz(/*mp_st out[NUMBER_OF_ITERATIONS][3], */unsigned int precision) {
	mp_st results[NUMBER_OF_ITERATIONS+1][3];

//	const unsigned int nbPacks = 4; // dividing the treatment


	const int ktMax = NUMBER_OF_ITERATIONS;
	//	mp_st x = 77617;
	//	mp_st y = 33096;
	//	mp_st res,t;
	//
	//	res=sam_set_str(t, "333.75")
	mp_st x0 = -10;
	mp_st y0 = 20;
	mp_st z0 = -5;
	mp_st x1 = x0;
	mp_st y1 = y0;
	mp_st z1 = z0;
	mp_st xm1 = x0;
	mp_st ym1 = y0;
	mp_st zm1 = z0;

	mp_st xcoef = 0;
	mp_st sigma = 10 * (1 + xcoef);
	mp_st ro = 28 * (1 + xcoef);
	mp_st beta = 2.6667 * (1 + xcoef);
	mp_st xnu = -2.e-4;
	mp_st irkMax = 4;
	mp_st dt = 1.e-3;
	mp_st two = 2;

	mp_st alp, xtt, ytt, ztt;

	// writing x1, y1, z1
	results[0][0] = x1;
	results[0][1] = y1;
	results[0][2] = z1;

	// lorenz attractor main loop
	for (int kt = 1 ; kt <= ktMax ; ++kt) {
		// inner loop
		for (int irk = 1 ; irk <= irkMax ; ++irk) {
			alp = 1. / (irkMax + 1 - irk);

			xtt = (x1 - 2 * x0 + xm1) / (dt*dt) * xnu;
			ytt = (y1 - 2 * y0 + ym1) / (dt*dt) * xnu;
			ztt = (z1 - 2 * z0 + zm1) / (dt*dt) * xnu;

			x1 = x0 + dt * alp * (sigma * (y1 - x1) + xtt);
			y1 = y0 + dt * alp * (ro * x1 - y1 - x1 * z1 + ytt);
			z1 = z0 + dt * alp * (x1 * y1 - beta * z1 + ztt);
		}
		xm1 = x0;
		ym1 = y0;
		zm1 = z0;
		x0 = x1;
		y0 = y1;
		z0 = z1;
		// write x1,y1,z1
		results[kt][0] = x1;
		results[kt][1] = y1;
		results[kt][2] = z1;
	}

	printf("Success. Writing output.\n");
	writeMpstMatrixInFile(precision, results);
}

int main() {
	 ofstream myfile;
	  myfile.open ("ceci est un fichier de test.txt");
	  myfile << "Writing this to a file.\n";
	  myfile.close();
	printf("------------------------------------------\n");
	printf("|  Lorenz attractor runs for multiple 	 |\n");
	printf("|  precisions with SAM                   |\n");
	printf("------------------------------------------\n");

	printf("\nPrecision range: [ %d , %d ]\n", PREC_MIN, PREC_MAX);

	// boucle sur les précisions
	for (unsigned int precision = PREC_MIN ; precision <= PREC_MAX ; ++precision) {
		printf("\n%u : PRECISION %u\n",precision,precision);
		SAM_init(-1, precision); // -1 stands for "all numb_instability detected"

//		mp_st (*results)[NUMBER_OF_ITERATIONS][3];
//		results = (mp_st(*)[NUMBER_OF_ITERATIONS][3])malloc(sizeof(mp_st[NUMBER_OF_ITERATIONS][3]));
//		assert(results != NULL);

		printf("begin Lorenz...\n");
		lorenz(/**results,*/ precision);

//		printf("Success. Writing output.\n");
//		writeMpstMatrixInFile(precision, *results);

//		printf("Freeing array...\n");
//		free(results);
		SAM_end();
	}
//	SAM_init(-1,122);
//	printf("------------------------------------------\n");
//	printf("|  Polynomial function of two variables  |\n");
//	printf("|  with SAM                              |\n");
//	printf("------------------------------------------\n");
//
//	mp_st x = 77617;
//	mp_st y = 33096;
//	mp_st res,t;
//
//	res=sam_set_str(t, "333.75")*y*y*y*y*y*y+x*x*(11*x*x*y*y-y*y*y*y*y*y-121*y*y*y*y-2)
//	+sam_set_str(t, "5.5")*y*y*y*y*y*y*y*y+x/(2*y);
//	printf("res=%s\n",strp(res));
//
//	SAM_end();

	return EXIT_SUCCESS;
}
