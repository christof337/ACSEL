#include <stdlib.h>
#include <check.h>
#include "../src/tools/arrayUtils.h"

/**
 * Test de l'utilitaire "arrayUtils.c"
 * Exécuter avec `make test` 
 */

const int SIZE = 10;
int * arrayTest;

void setup(void)
{
	arrayTest = malloc(SIZE * sizeof(int));
    for ( int i = 0 ; i < SIZE ; i++ ) {
    	// on initialise à i par défaut
    	arrayTest[i] = i ; 
    }
}

void teardown(void)
{
    free(arrayTest);
}

START_TEST(test_fill_array_with_zeros) {

	fillArrayWithZeros(arrayTest, SIZE);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_int_eq(arrayTest[i], 0);
	}
}
END_TEST

START_TEST(test_fill_array_with) {
	fillArrayWith(arrayTest, SIZE, 5);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_int_eq(arrayTest[i], 5);
	}
}
END_TEST

START_TEST(test_fill_array_linearly) {

	fillArrayLinearly(arrayTest, SIZE);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_int_eq(arrayTest[i], i);
	}
}
END_TEST

Suite * array_utils_suite(void) {
	Suite *s;
	TCase *tc_core;
	TCase *tc_lmits;

	s = suite_create("Array Utils");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);
    
	tcase_add_test(tc_core, test_fill_array_with_zeros);
	tcase_add_test(tc_core, test_fill_array_with);
	tcase_add_test(tc_core, test_fill_array_linearly);
	suite_add_tcase(s, tc_core);

	return s;
}

int main ( void ) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = array_utils_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
