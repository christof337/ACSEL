#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

enum ERRORS {
	ERROR_OK = 0,
	ERROR_NO_EQUAL_SIGN_IN_PARAMETER = -1,
	ERROR_WHILE_HANDLING_INPUT_PARAMETERS = -2,
	ERROR_WRONG_PARAMETER_GIVEN = -3,
	ERROR_WRONG_VALUE_GIVEN = -4
};

int errorHandling();

void printError(int errnum);

void printErrorMessage(char * message);

void printCustomError(enum ERRORS err, int nbParams, ...);

#endif // ERROR_HANDLING_H
