#include "__CommonFunctions.h"
#include <stdio.h>

double*AllocateArray(double* dynamic_array, double dimension) {
	dynamic_array = (double*)malloc_e(dimension * sizeof(double));
	return dynamic_array;
}

double** Allocate2dMatrix(double** matrix, int dimension1, int dimension2) {
	int i;
	matrix = (double**)malloc_e(dimension1 * sizeof(double*));
	matrix[0] = (double*)malloc_e(dimension1 * dimension2 * sizeof(double));
	for (i = 1; i < dimension1; i++)
		matrix[i] = matrix[i - 1] + dimension2;
	return matrix;
}

void FreeArray(double* dynamic_array) {
	free((void *)dynamic_array);
}

void Free2dMatrix(double** matrix) {
	free((void *)matrix[0]);
	free((void *)matrix);
}

void PrintOut2dMatrix(double **matrix, int matrix_row, int matrix_column) {
	int i, j;
	for (i = 0; i < matrix_row; i++) {
		for (j = 0; j < matrix_column; j++)
			printf("%3.2f ", matrix[i][j]);
		printf("\n");
	}
}

void PrintOutArray(double *array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++)
		printf("%3.2lf\n", array[i]);
}

void ZeroArray(double *array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++)
		array[i] = 0;
}