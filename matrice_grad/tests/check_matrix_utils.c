#include <stdlib.h>
#include <check.h>
#include <math.h> 
#include "../src/tools/matrixUtils.h"

#define SIZE 10

/**
 * Test de l'utilitaire "matrixUtils.c"
 * Exécuter avec `make test` 
 */

// const int SIZE = 10;
double matrixTest[SIZE][SIZE];

START_TEST(test_fill_matrix_exponentially) {
	fillMatrixExponentially(SIZE, SIZE, matrixTest);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		for ( int j = 0 ; j < SIZE ; j++ ) {
			ck_assert(matrixTest[i][j] == exp(-0.05 * pow((i-j), 2.0)));
		}
	}
}
END_TEST

Suite * matrix_utils_suite(void) {
	Suite *s;
	TCase *tc_core;
	TCase *tc_lmits;

	s = suite_create("Matrix Utils");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_fill_matrix_exponentially);
	suite_add_tcase(s, tc_core);

	return s;
}

int main ( void ) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = matrix_utils_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
