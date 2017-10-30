#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

int askForInt();

int writeMatrix(double ** matrix, const int n, const int m, const char * fileName);

int writeData(double * data[], const int size, const char * fileName, const char * labels[], const int n_array);

int writeArray(double * array, const int size,const char * fileName, const char * label);

#endif /* INPUT_OUTPUT_H */