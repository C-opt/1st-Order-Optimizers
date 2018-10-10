#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "__FirstStoch.h"
#include "__CommonFunctions.h"
#include "__IOcsv.h"
#include "__LogisticRegL2.h"
#include "__MatrixFunctions.h"

int main() {
	time_t start, end;
	double time_lapse;

	int i, j, k;
	//581012
	//54

	//4601
	//57

	int data_num = 4601;
	int data_dim = 57;
	char X_filename[50] = "X_spambase.csv";
	char Y_filename[50] = "Y_spambase.csv";
	char output_filename[50] = "result_spambase.csv";
	char table_output_filename[50] = "table_spambase.csv";

	double lambda = pow(10, -6);
	double epsilon = 1.0*pow(10, -13);
	double obj_value;

	int max_iter = pow(10,7);
	int no_exp = 1;
	int m = floor(2 * data_num);
	int stage_num = 10;
	int inner_points = 100;
	
	double** X_matrix = NULL;
	double* Y_array = NULL;
	double* w = NULL;
	double* grad = NULL;
	double** result = NULL;
	double** experiment_table = NULL;

	X_matrix = Allocate2dMatrix(X_matrix, data_dim, data_num);
	Y_array = AllocateArray(Y_array, data_num);
	w = AllocateArray(w, data_dim);
	grad = AllocateArray(grad, data_dim);
	result = Allocate2dMatrix(result, no_exp, 2);
	experiment_table = Allocate2dMatrix(experiment_table, stage_num*(1 + inner_points + 1) + 1, 2);

	ReadMatrixCsv(X_filename, X_matrix, data_dim, data_num);
	ReadArrayCsv(Y_filename, Y_array, data_num);
	ZeroArray(w, data_dim);

	for (i = no_exp; i > 0; i--) {

		start = clock(); 
		ZeroArray(w, data_dim);
		//obj_value = SVRG(w, experiment_table, X_matrix, Y_array, lambda, data_dim, data_num, stage_num, m);
		obj_value = __optimizer(w, X_matrix, Y_array, 1.0*i*lambda, data_dim, data_num, 30, 4*data_num, max_iter, epsilon);
		end = clock();

		time_lapse = 1.0*(end - start) / CLOCKS_PER_SEC;
		printf("SVRG (lambda = %d/data_num) obj = %3.10lf in %3.3lf sec\n", i, obj_value, time_lapse);
		printf("--------------------------------------\n");

		result[i-1][0] = obj_value;
		result[i-1][1] = time_lapse;

	}

	//CreateMatrixCsv(table_output_filename, experiment_table, stage_num*(1 + inner_points + 1) + 1, 2);
	CreateMatrixCsv(output_filename, result, no_exp, 2);

	Free2dMatrix(X_matrix);
	FreeArray(Y_array);
	FreeArray(w);
	FreeArray(grad);
	Free2dMatrix(result);
	Free2dMatrix(experiment_table);

	printf("Type something for exiting the program\n");
	scanf("%d", &i);
}