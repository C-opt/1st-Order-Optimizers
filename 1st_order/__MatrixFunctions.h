#pragma once
double*AllocateArray(double* dynamic_array, double dimension);
double** Allocate2dMatrix(double** matrix, int dimension1, int dimension2);
void FreeArray(double* dynamic_array);
void Free2dMatrix(double** matrix);
void PrintOut2dMatrix(double **matrix, int matrix_row, int matrix_column);
void PrintOutArray(double *array, int array_size);
void ZeroArray(double *array, int array_size);