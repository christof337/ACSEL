#include <stdlib.h>
#include <check.h>
#include "../src/tools/arrayUtils.h"

#define SIZE 10

/**
 * Test de l'utilitaire "arrayUtils.c"
 * Exécuter avec `make test` 
 */

double * arrayTest;

double * initArray() {
	double * array = createArray(SIZE);
    for ( int i = 0 ; i < SIZE ; i++ ) {
    	// on initialise à i par défaut
    	array[i] = i ; 
    }
    return array;
}

double * initArrayDesc() {
	double * array = createArray(SIZE);
    for ( int i = 0 ; i < SIZE ; i++ ) {
    	// on initialise à i par défaut
    	array[i] = SIZE - i ; 
    }
    return array;
}

void setup(void)
{
	arrayTest = initArray();
}

void teardown(void)
{
    free(arrayTest);
}

START_TEST(test_fill_array_with_zeros) {

	arrayTest = fillArrayWithZeros(arrayTest, SIZE);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_double_eq(arrayTest[i], 0);
	}
}
END_TEST

START_TEST(test_fill_array_with) {
	arrayTest = fillArrayWith(arrayTest, SIZE, 5);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_double_eq(arrayTest[i], 5);
	}
}
END_TEST

START_TEST(test_fill_array_linearly) {

	arrayTest = fillArrayLinearly(arrayTest, SIZE);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_double_eq(arrayTest[i], i);
	}
}
END_TEST

START_TEST(test_vector_mult) {
	// declarations
	double * secondArrayTest;
	double * multipliedMatrix;

	// initializations
	secondArrayTest = initArrayDesc();
	multipliedMatrix = vectorMult(arrayTest, SIZE, secondArrayTest, SIZE);

	for ( int i = 0 ; i < SIZE ; i++ ) {
		ck_assert_double_eq(multipliedMatrix[i], arrayTest[i]*secondArrayTest[i]);
	}

	free(secondArrayTest);
	free(multipliedMatrix);
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
	tcase_add_test(tc_core, test_vector_mult);
	
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
