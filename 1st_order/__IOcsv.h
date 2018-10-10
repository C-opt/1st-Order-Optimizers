#pragma once
void CreateMatrixCsv(char* filename, double** matrix, int matrix_row, int matrix_column);
void CreateArrayCsv(char* filename, double* array, int array_size);
void ReadMatrixCsv(char* filename, double** matrix, int matrix_row, int matrix_column);
void ReadArrayCsv(char* filename, double* array, int array_size);