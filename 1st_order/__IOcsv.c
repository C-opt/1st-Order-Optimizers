#include <stdio.h>
#include <stdlib.h>

void CreateMatrixCsv(char* filename, double** matrix, int matrix_row, int matrix_column) {
	printf("Creating %s file\n", filename);
	FILE *fp;
	int i, j;

	if ((fp = fopen(filename, "w+")) != NULL) {
		for (i = 0; i < matrix_row; i++)
			for (j = 0; j < matrix_column; j++)
				if (j == matrix_column - 1) {
					if (i == matrix_row - 1)
						fprintf(fp, "%.18lf", matrix[i][j]);
					else
						fprintf(fp, "%.18lf\n", matrix[i][j]);
				}
				else
					fprintf(fp, "%.18lf,", matrix[i][j]);
		fclose(fp);
	}
	else
		printf("Error trying to create %s\n", filename);
}

void CreateArrayCsv(char* filename, double* array, int array_size) {
	printf("Creating %s file\n", filename);
	FILE *fp;
	int i;

	if ((fp = fopen(filename, "w+")) != NULL) {
		for (i = 0; i < array_size; i++)
			if (i == array_size - 1)
				fprintf(fp, "%.18lf", array[i]);
			else
				fprintf(fp, "%.18lf,", array[i]);
		fclose(fp);
	}
	else
		printf("Error trying to create %s\n", filename);
}

void ReadMatrixCsv(char* filename, double** matrix, int matrix_row, int matrix_column) {
	printf("Reading %s file\n", filename);
	FILE *fp;
	int i, j;

	if ((fp = fopen(filename, "r+")) != NULL) {
		for (i = 0; i < matrix_row; i++)
			for (j = 0; j < matrix_column; j++)
				if (j == matrix_column - 1) {
					if (i == matrix_row - 1)
						fscanf(fp, "%lf", &(matrix[i][j]));
					else
						fscanf(fp, "%lf\n", &(matrix[i][j]));
				}
				else
					fscanf(fp, "%lf,", &(matrix[i][j]));
		fclose(fp);
	}
	else
		printf("Error trying to read %s\n", filename);
}

void ReadArrayCsv(char* filename, double* array, int array_size) {
	printf("Reading %s file\n", filename);
	FILE *fp;
	int i;

	if ((fp = fopen(filename, "r+")) != NULL) {
		for (i = 0; i < array_size; i++)
			if (i == array_size - 1)
				fscanf(fp, "%lf", &(array[i]));
			else
				fscanf(fp, "%lf,", &(array[i]));
		fclose(fp);
	}
	else
		printf("Error trying to create %s\n", filename);
}