#include <stdlib.h>
#include <check.h>
#include <math.h> 
#include "../src/tools/matrixUtils.h"
#include "../src/tools/arrayUtils.h"

#define DEFAULT_NB_ROWS 15
#define DEFAULT_NB_COLUMNS 10

/**
 * Test de l'utilitaire "matrixUtils.c"
 * Exécuter avec `make test` 
 */

// const int SIZE = 10;
double ** matrixTest;

void setup(void)
{
	matrixTest = createMatrix(DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS); // hope the function works
}

void teardown(void)
{
    freeMatrix(matrixTest, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
}

START_TEST(test_create_matrix) {
	// we basically want to know if we can acess read/write every memory slot reserved
	const int m = 4; // nb rows
	const int n = 7; // nb columns
	double ** matrix = createMatrix(m,n);

	// write
	for ( int i = 0 ; i < m ; i++ ) {
		for ( int j = 0 ; j < n ; j++ ) {
			matrix[i][j] = (i-1)/(j+1);
		}
	}

	// read
	for ( int i = 0 ; i < m ; i++ ) {
		for ( int j = 0 ; j < n ; j++ ) {			
			ck_assert(matrix[i][j] == (i-1)/(j+1));
		}
	}

	free(matrix);
}
END_TEST

START_TEST(test_fill_matrix_exponentially) {
	fillMatrixExponentially(matrixTest, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);

	for ( int i = 0 ; i < DEFAULT_NB_ROWS ; i++ ) {
		for ( int j = 0 ; j < DEFAULT_NB_COLUMNS ; j++ ) {
			ck_assert(matrixTest[i][j] == exp(-0.05 * pow((i-j), 2.0)));
		}
	}
}
END_TEST

START_TEST(test_matrix_mult) {
	const int p = 13;
	double ** matrix1 = createMatrix(DEFAULT_NB_ROWS, p);
	double ** matrix2 = createMatrix(p, DEFAULT_NB_COLUMNS);

	matrix1 = fillMatrixRandomly(matrix1, DEFAULT_NB_ROWS, p); // not pure test but still
	matrix2 = fillMatrixExponentially(matrix2, p, DEFAULT_NB_COLUMNS);
	
	double ** multipliedMatrix = matrixMult(matrix1,DEFAULT_NB_ROWS,p,
		matrix2,p,DEFAULT_NB_COLUMNS);

	double sum = 0;

	for ( int i = 0 ; i < DEFAULT_NB_ROWS ; i++ ) {
		for ( int j = 0 ; j < DEFAULT_NB_COLUMNS ; j++ ) {
	        for (int k = 0; k < p ; k++) {
	         	sum = sum + matrix1[i][k]*matrix2[k][j];
	        }
			ck_assert(multipliedMatrix[i][j] == sum);
	        sum = 0;
		}
	}

	freeMatrix(matrix1, DEFAULT_NB_ROWS, p);
	freeMatrix(matrix2, p, DEFAULT_NB_COLUMNS);
	freeMatrix(multipliedMatrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
}
END_TEST

START_TEST(test_matrix_mult_vector) {
	double ** matrix = createMatrix(DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
	double * vector = createArray(DEFAULT_NB_COLUMNS);

	matrix = fillMatrixExponentially(matrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
	vector = fillArrayLinearly(vector, DEFAULT_NB_COLUMNS);

	double * multipliedVector = matrixMultVector(matrix,DEFAULT_NB_ROWS,DEFAULT_NB_COLUMNS,vector,DEFAULT_NB_COLUMNS);

	double sum = 0;

	for ( int i = 0 ; i < DEFAULT_NB_ROWS ; i++ ) {
		for ( int j = 0 ; j < DEFAULT_NB_COLUMNS ; j++ ) {
	        sum = sum + matrix[i][j]*vector[j];
		}
		ck_assert(multipliedVector[i] == sum);
        sum = 0;
	}

	freeMatrix(matrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
	free(vector);
}
END_TEST

// freeMatrix and fillMatrixRandomly cannot be tested

Suite * matrix_utils_suite(void) {
	Suite *s;
	TCase *tc_memory;
	TCase *tc_fill;
	TCase *tc_mult;

	s = suite_create("Matrix_Utils_Test_Suite");

	/* Memory Management test case */
	tc_memory = tcase_create("Memory_Management_Test_Case");
	tcase_add_test(tc_memory, test_create_matrix);
	suite_add_tcase(s, tc_memory);


	/* Filling test case */
	tc_fill = tcase_create("Filling_Test_Case");
	tcase_add_checked_fixture(tc_fill, setup, teardown);
	tcase_add_test(tc_fill, test_fill_matrix_exponentially);
	suite_add_tcase(s, tc_fill);

	/* Multiplication test case */
	tc_mult = tcase_create("Multiplication_Test_Case");
	tcase_add_test(tc_mult, test_matrix_mult);
	tcase_add_test(tc_mult, test_matrix_mult_vector);
	suite_add_tcase(s, tc_mult);

	return s;
}

int main ( void ) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = matrix_utils_suite();
	sr = srunner_create(s);

	srunner_set_log (sr, "check_matrix_utils_test.log");

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
