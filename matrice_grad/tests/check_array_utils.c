#include <stdlib.h>
#include <check.h>
#include <mpfr.h>

#include "../src/tools/arrayUtils.h"
#include "../src/tools/customMath.h"

#define RM m_getRoundingMode()

#define RME RNDN

#define SIZE 10

#define DEFAULT_PRECISION 32

/**
 * Test de l'utilitaire "arrayUtils.c"
 * Exécuter avec `make test` 
 */

mpfr_t * arrayTest;

int initArray(mpfr_t ** array) {
	int err = 0;
	createArray(array, SIZE, DEFAULT_PRECISION);
	for (int i = 0 ; i < SIZE ; ++i) {
		// on initialise à i par défaut
		// array[i] = i
		err += mpfr_set_si((*array)[i], i, RM);
	}
	return err;
}

int initArrayDesc(mpfr_t ** array) {
	int err = 0;
	createArray(array, SIZE, DEFAULT_PRECISION);
	for (int i = 0 ; i < SIZE ; ++i) {
		// on initialise à SIZE - i par défaut
		// array[i] = SIZE - i
		err += mpfr_set_si((*array)[i], SIZE-i, RM);
	}
	return err;
}

void setup(void) {
	initArray(&arrayTest);
}

void teardown(void) {
	freeArray(arrayTest, SIZE);
}

START_TEST(test_fill_array_with_zeros)
	{
		mpfr_t zero;
		m_init2(zero, DEFAULT_PRECISION);
		mpfr_set_d(zero, 0.0, RM);

		fillArrayWithZeros(arrayTest, SIZE);

		for (int i = 0 ; i < SIZE ; ++i) {
			ck_assert(mpfr_cmp(arrayTest[i],zero) == 0);
		}

		m_clear(zero);
	}END_TEST

START_TEST(test_fill_array_with)
	{
		mpfr_t someNumber;
		m_init2(someNumber, DEFAULT_PRECISION);
		mpfr_set_d(someNumber, 5.0, RM);

		fillArrayWith(arrayTest, SIZE, someNumber);

		for (int i = 0 ; i < SIZE ; ++i) {
			ck_assert(mpfr_cmp(arrayTest[i],someNumber) == 0);
		}

		m_clear(someNumber);
	}END_TEST

START_TEST(test_fill_array_linearly)
	{
		mpfr_t cmp;
		m_init2(cmp, DEFAULT_PRECISION);

		fillArrayLinearly(arrayTest, SIZE);

		for (long int i = 0 ; i < SIZE ; ++i) {
			mpfr_set_si(cmp, i + 1, RM);

			ck_assert(mpfr_cmp(arrayTest[i],cmp) == 0);
		}

		m_clear(cmp);
	}END_TEST

START_TEST(test_vector_mult)
	{
		// declarations
		mpfr_t * secondArrayTest;
		mpfr_t * multipliedMatrix;
		createArray(&multipliedMatrix, SIZE, DEFAULT_PRECISION);

		mpfr_t t;
		m_init2(t, DEFAULT_PRECISION);

		// initializations
		initArrayDesc(&secondArrayTest);

		vectorMult(multipliedMatrix, arrayTest, SIZE, secondArrayTest, SIZE, RME);

		for (int i = 0 ; i < SIZE ; ++i) {
			m_mul(t, arrayTest[i], secondArrayTest[i], RME);
			ck_assert(mpfr_cmp(multipliedMatrix[i],t)==0);
		}

		freeArray(secondArrayTest, SIZE);
		freeArray(multipliedMatrix, SIZE);
		m_clear(t);
	}END_TEST

Suite * array_utils_suite(void) {
	Suite *s;
	TCase *tc_core;
//	TCase *tc_lmits;

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

int main(void) {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = array_utils_suite();
	sr = srunner_create(s);

	srunner_set_log(sr, "check_array_utils_test.log");

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
