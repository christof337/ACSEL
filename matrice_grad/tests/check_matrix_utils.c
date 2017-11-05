#include <stdlib.h>
#include <check.h>
#include <math.h> 
#include "../src/tools/matrixUtils.h"
#include "../src/tools/arrayUtils.h"
#include "../src/tools/customMath.h"

#define DEFAULT_NB_ROWS 15
#define DEFAULT_NB_COLUMNS 10

#define RM m_getRoundingMode()

#define DEFAULT_PRECISION 32

/**
 * @brief      Test de l'utilitaire "matrixUtils.c" Exécuter avec `make test`
 */

// const int SIZE = 10;
mpfr_t ** matrixTest;

void setup(void)
{
	createMatrix(&matrixTest, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS, DEFAULT_PRECISION); // hope the function works
}

void teardown(void)
{
    freeMatrix(matrixTest, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
}

START_TEST(test_create_matrix) {
	// we basically want to know if we can acess read/write every memory slot reserved
	// TODO change precision and see if it still works
	const int m = 4; // nb rows
	const int n = 7; // nb columns
	mpfr_t t;
	m_init2(t,DEFAULT_PRECISION);

	mpfr_t ** matrix;
	createMatrix(&matrix,m,n,DEFAULT_PRECISION);

	// write
	for ( int i = 0 ; i < m ; ++i ) {
		for ( int j = 0 ; j < n ; ++j ) {
			mpfr_set_d(t,(i-1)/(j+1),RM);
			//matrix[i][j] = (i-1)/(j+1);
			mpfr_set(matrix[i][j],t,RM);
		}
	}

	// read
	for ( int i = 0 ; i < m ; ++i ) {
		for ( int j = 0 ; j < n ; ++j ) {	
			mpfr_set_d(t,(i-1)/(j+1),RM);		
			ck_assert(mpfr_cmp(matrix[i][j],t) == 0);
		}
	}

	m_clear(t);
	freeMatrix(matrix,m,n);
}
END_TEST

START_TEST(test_fill_matrix_exponentially) {
	mpfr_t s, t, u, exp; // intermediate temporary variables
	mpfr_inits2 (DEFAULT_PRECISION, s, t, u, exp, (mpfr_ptr)NULL);
	mpfr_set_d(t, -0.05, RM);
	mpfr_set_d(exp, 2.0, RM);

	fillMatrixExponentially(matrixTest, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);

	for ( long int i = 0 ; i < DEFAULT_NB_ROWS ; ++i ) {
		for ( long int j = 0 ; j < DEFAULT_NB_COLUMNS ; ++j ) {
			// ck_assert(matrixTest[i][j] == exp(-0.05 * pow((i-j), 2.0)));
  			mpfr_set_si (s, i-j, RM);
  			mpfr_pow(u,s,exp,RM);
  			m_mul(u,u,t,RM);
			mpfr_exp(s, u, RM);
			ck_assert(mpfr_cmp(matrixTest[i][j],s) == 0);
		}
	}
	mpfr_clears (s, t, u, exp, (mpfr_ptr) NULL);
}
END_TEST

START_TEST(test_matrix_mult) {
	const int p = 13;
	mpfr_t ** matrix1;
	mpfr_t ** matrix2;
	mpfr_t t;
	m_init2(t,DEFAULT_PRECISION);

	createMatrix(&matrix1, DEFAULT_NB_ROWS, p, DEFAULT_PRECISION);
	createMatrix(&matrix2, p, DEFAULT_NB_COLUMNS,DEFAULT_PRECISION);

	fillMatrixRandomly(matrix1, DEFAULT_NB_ROWS, p); // not pure test but still
	fillMatrixExponentially(matrix2, p, DEFAULT_NB_COLUMNS);
	
	mpfr_t ** multipliedMatrix;
	createMatrix(&multipliedMatrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS,DEFAULT_PRECISION);
	matrixMult(multipliedMatrix,matrix1,DEFAULT_NB_ROWS,p,
		matrix2,p,DEFAULT_NB_COLUMNS);

	mpfr_t sum;
	m_init2(sum,DEFAULT_PRECISION);
	mpfr_set_d(sum,0.0,RM); // sum = 0

	for ( int i = 0 ; i < DEFAULT_NB_ROWS ; ++i ) {
		for ( int j = 0 ; j < DEFAULT_NB_COLUMNS ; ++j ) {
	        for (int k = 0; k < p ; ++k) {
	         	// sum = sum + matrix1[i][k]*matrix2[k][j];
	        	m_mul(t,matrix1[i][k],matrix2[k][j],RM);
	        	mpfr_add(sum, sum, t, RM);
	        }
			ck_assert(mpfr_cmp(multipliedMatrix[i][j],sum) == 0 );
			mpfr_set_d(sum,0.0,RM); // sum = 0
		}
	}

	m_clear(t);
	m_clear(sum);
	freeMatrix(matrix1, DEFAULT_NB_ROWS, p);
	freeMatrix(matrix2, p, DEFAULT_NB_COLUMNS);
	freeMatrix(multipliedMatrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
}
END_TEST

START_TEST(test_matrix_mult_vector) {
	mpfr_t t;
	m_init2(t,DEFAULT_PRECISION);

	mpfr_t ** matrix;
	createMatrix(&matrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS,DEFAULT_PRECISION);
	mpfr_t * vector;
	createArray(&vector,DEFAULT_NB_COLUMNS,DEFAULT_PRECISION);

	fillMatrixExponentially(matrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
	fillArrayLinearly(vector, DEFAULT_NB_COLUMNS);

	mpfr_t * multipliedVector;
	createArray(&multipliedVector,DEFAULT_NB_ROWS,DEFAULT_PRECISION);

	matrixMultVector(multipliedVector, matrix,DEFAULT_NB_ROWS,DEFAULT_NB_COLUMNS,vector,DEFAULT_NB_COLUMNS);

	mpfr_t sum;
	m_init2(sum,DEFAULT_PRECISION);
	mpfr_set_d(sum,0.0,RM); // sum = 0

	for ( int i = 0 ; i < DEFAULT_NB_ROWS ; ++i ) {
		for ( int j = 0 ; j < DEFAULT_NB_COLUMNS ; ++j ) {
	        //sum = sum + matrix[i][j]*vector[j];
        	m_mul(t,matrix[i][j],vector[j],RM);
        	mpfr_add(sum, sum, t, RM);
		}
		ck_assert(mpfr_cmp(multipliedVector[i],sum)==0);
		mpfr_set_d(sum,0.0,RM); // sum = 0
	}

	m_clear(t);
	m_clear(sum);
	freeMatrix(matrix, DEFAULT_NB_ROWS, DEFAULT_NB_COLUMNS);
	freeArray(vector,DEFAULT_NB_COLUMNS);
	freeArray(multipliedVector,DEFAULT_NB_COLUMNS);
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
