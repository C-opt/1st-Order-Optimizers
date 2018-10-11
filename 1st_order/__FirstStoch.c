#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "__CommonFunctions.h"
#include "__LogisticRegL2.h"
#include "__MatrixFunctions.h"

double SVRG(double* array_solution, double** experiment_matrix, double **X, double* Y, double lambda1, double lambda2, int data_dim, int data_num, int stage_num, int m) {

	int t, j, k, rand_idx, tmp;
	int count = 0;

	double **all_grad = NULL;
	double *x_tilde = NULL;
	double *x_zero = NULL;
	double *x_previous = NULL;
	double *full_gradient = NULL;
	double *upsilon_k = NULL;
	double abs_grad, obj_value;

	all_grad = Allocate2dMatrix(all_grad, data_dim, data_num);
	x_tilde = AllocateArray(x_tilde, data_dim);
	x_zero = AllocateArray(x_zero, data_dim);
	x_previous = AllocateArray(x_previous, data_dim);
	full_gradient = AllocateArray(full_gradient, data_dim);
	upsilon_k = AllocateArray(upsilon_k, data_dim);

	ZeroArray(x_tilde, data_dim);
	ZeroArray(full_gradient, data_dim);
	if (experiment_matrix != NULL) {
		experiment_matrix[count][0] = 0;
		experiment_matrix[count][1] = LogRegressionR1R2Obj(array_solution, X, Y, lambda1, lambda2, data_dim, data_num);
	}

	double* tmp_grad = NULL;
	double* tmp_grad2 = NULL;
	double* tmp_sum = NULL;
	tmp_grad = AllocateArray(tmp_grad, data_dim);
	tmp_grad2 = AllocateArray(tmp_grad2, data_dim);
	tmp_sum = AllocateArray(tmp_sum, data_dim);
	tmp = floor(1.0*m / 100);

	for (t = 0; t < stage_num; t++) {

		for (j = 0; j < data_dim; j++) {
			x_tilde[j] = array_solution[j];
			x_zero[j] = x_tilde[j];
			x_previous[j] = x_zero[j];
		}
		AllFullLogR1R2Gradient(all_grad, full_gradient, tmp_grad, x_tilde, X, Y, lambda2, data_dim, data_num);
		abs_grad = L2Norm(full_gradient, data_dim);

		if (experiment_matrix != NULL) {
			count = count + 1;
			experiment_matrix[count][0] = experiment_matrix[count - 1][0] + 1;
			experiment_matrix[count][1] = LogRegressionR1R2Obj(array_solution, X, Y, lambda1, lambda2, data_dim, data_num);
		}

		if (t % 1 == 0)
			printf("SVRG: #stage = %5d, grad_abs = E%4.8lf, m = %1.1lf\n", t + 1, log(abs_grad) / log(10), 1.0*m / data_num);

		ZeroArray(tmp_sum, data_dim);
		ZeroArray(tmp_grad2, data_dim);

		for (k = 0; k < m; k++) {
			rand_idx = RandomFrom(0, data_num - 1);
			OneInstanceLogR1R2Gradient(tmp_grad2, rand_idx, x_previous, X, Y, lambda2, data_dim, data_num);

			for (j = 0; j < data_dim; j++) {
				upsilon_k[j] = tmp_grad2[j] - all_grad[j][rand_idx] + full_gradient[j];
				x_previous[j] = x_previous[j] - 0.25 * upsilon_k[j];
				tmp_sum[j] = tmp_sum[j] + x_previous[j];
			}

			if (experiment_matrix != NULL && (k % tmp == 0) && k != 0) {
				//printf("t = %d\n", k);
				count = count + 1;
				experiment_matrix[count][0] = experiment_matrix[count - 1][0] + 1.0*tmp / data_num;
				experiment_matrix[count][1] = LogRegressionR1R2Obj(x_previous, X, Y, lambda1, lambda2, data_dim, data_num);
			}

		}

		for (j = 0; j < data_dim; j++)
			array_solution[j] = 1.0*x_previous[j];
		//array_solution[j] = 1.0*tmp_sum[j] / m;

		if (experiment_matrix != NULL) {
			count = count + 1;
			experiment_matrix[count][0] = experiment_matrix[count - 1][0] + 1.0*(m % tmp) / data_num;
			experiment_matrix[count][1] = LogRegressionR1R2Obj(array_solution, X, Y, lambda1, lambda2, data_dim, data_num);
		}


	}

	FreeArray(x_tilde);
	FreeArray(x_zero);
	FreeArray(x_previous);
	FreeArray(full_gradient);
	FreeArray(tmp_grad);
	FreeArray(tmp_grad2);
	FreeArray(tmp_sum);
	FreeArray(upsilon_k);
	Free2dMatrix(all_grad);

	obj_value = LogRegressionR1R2Obj(array_solution, X, Y, lambda1, lambda2, data_dim, data_num);
	return obj_value;
}

double FISTA(double* array_solution, double **X, double* Y, double lambda1, double lambda2, int data_dim, int data_num, int max_iter, double epsilon) {

	int t, j;
	double t_prev, t_curr;
	t_prev = t_curr = 1.0;

	double *w_prev = NULL;
	double *y = NULL;
	double *gradient = NULL;
	double *tmp_array = NULL;
	double abs_grad, obj_value;

	w_prev = AllocateArray(w_prev, data_dim);
	y = AllocateArray(y, data_dim);
	gradient = AllocateArray(gradient, data_dim);
	tmp_array = AllocateArray(tmp_array, data_dim);

	ZeroArray(w_prev, data_dim);
	ZeroArray(gradient, data_dim);
	for (j = 0; j < data_dim; j++)
		y[j] = array_solution[j];

	double* tmp_grad = NULL;
	tmp_grad = AllocateArray(tmp_grad, data_dim);
	FullLogR1R2Gradient(gradient, tmp_grad, array_solution, X, Y, 0, data_dim, data_num);
	prox_map(gradient, data_dim, lambda1, lambda2);
	abs_grad = L2Norm(gradient, data_dim);
	abs_grad = 1;
	printf("abs_grad = %3.2f\n", abs_grad);

	t = 1;
	while ((t <= max_iter) && (abs_grad > epsilon)) {
		if (t % 5000 == 0)
			printf("FISTA: #iteration = %5d, grad_abs = E%4.8lf\n", t, log(abs_grad) / log(10));

		FullLogR1R2Gradient(gradient, tmp_grad, y, X, Y, 0, data_dim, data_num);
		for (j = 0; j < data_dim; j++) 
			array_solution[j] = y[j] - 4.0*gradient[j];
		
		prox_map(array_solution, data_dim, 4.0*lambda1, 4.0*lambda2);

		//Calculating the abs_grad
		for (j = 0; j < data_dim; j++) 
			tmp_array[j] = array_solution[j] - w_prev[j];
		abs_grad = L2Norm(tmp_array, data_dim);
		//

		t_curr = 0.5*(1.0 + sqrt(1.0 + 4.0 * t_prev*t_prev));
		for (j = 0; j < data_dim; j++) {
			y[j] = array_solution[j] + 1.0 * (t_prev - 1.0) / t_curr * (array_solution[j] - w_prev[j]);
			w_prev[j] = array_solution[j];
		}

		t_prev = t_curr;
		t = t + 1;
	}

	FreeArray(tmp_array);
	FreeArray(w_prev);
	FreeArray(y);
	FreeArray(gradient);
	FreeArray(tmp_grad);

	obj_value = LogRegressionR1R2Obj(array_solution, X, Y, lambda1, lambda2, data_dim, data_num);
	return obj_value;
}

double __optimizer(double* array_solution, double **X, double* Y, double lambda1, double lambda2, int data_dim, int data_num, int stage_num, int m, int max_iter, double epsilon) {
	double obj_value = 0;
	double ** tmp_experiment_matrix = NULL;

	//SVRG(array_solution, tmp_experiment_matrix, X, Y, lambda1, lambda2, data_dim, data_num, stage_num, m);
	//SVRG(array_solution, tmp_experiment_matrix, X, Y, lambda1, lambda2, data_dim, data_num, stage_num, data_num);
	obj_value = FISTA(array_solution, X, Y, lambda1, lambda2, data_dim, data_num, max_iter, epsilon);
	return obj_value;
}
