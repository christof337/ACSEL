#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

enum ERRORS { ERROR_NO_EQUAL_SIGN_IN_PARAMETER, ERROR_WHILE_HANDLING_INPUT_PARAMETERS};

int errorHandling () ;

void printError(int errnum);

void printErrorMessage(char * message);

void printCustomError(enum ERRORS err, char * param);


#endif // ERROR_HANDLING_H