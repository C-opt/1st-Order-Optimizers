#include "__CommonFunctions.h"
#include "__MatrixFunctions.h"

double LogRegressionR2Obj(double* array_solution, double **X, double* Y, double lambda, int data_dim, int data_num) {
	double objective_value;
	double tmp_sum = 0;
	double tmp_inner_product;

	int i, j;

	for (i = 0; i < data_num; i++) {
		tmp_inner_product = 0;
		for (j = 0; j < data_dim; j++)
			tmp_inner_product = tmp_inner_product + X[j][i] * array_solution[j];
		tmp_sum = tmp_sum + log(1 + exp(-Y[i] * tmp_inner_product));
	}

	tmp_inner_product = 0;
	for (j = 0; j < data_dim; j++)
		tmp_inner_product = tmp_inner_product + array_solution[j] * array_solution[j];

	objective_value = 1.0*tmp_sum / data_num + 0.5*lambda*tmp_inner_product;

	return objective_value;
}

void OneInstanceLogR2Gradient(double* instance_gradient, int data_idx, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int j;
	double tmp_inner_product, sigma_value;
	tmp_inner_product = 0;

	for (j = 0; j < data_dim; j++)
		tmp_inner_product = tmp_inner_product + X[j][data_idx] * array_solution[j];
	sigma_value = Sigmoid(-Y[data_idx] * tmp_inner_product);

	for (j = 0; j < data_dim; j++)
		instance_gradient[j] = -Y[data_idx] * X[j][data_idx] * sigma_value + lambda * array_solution[j];
}

void FullLogR2Gradient(double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int i, j;
	ZeroArray(full_gradient, data_dim);

	for (i = 0; i < data_num; i++) {

		OneInstanceLogR2Gradient(tmp_grad, i, array_solution, X, Y, lambda, data_dim, data_num);
		for (j = 0; j < data_dim; j++)
			full_gradient[j] = full_gradient[j] + tmp_grad[j];

	}

	for (j = 0; j < data_dim; j++)
		full_gradient[j] = 1.0*full_gradient[j] / data_num;
}

void AllFullLogR2Gradient(double** all_grad, double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int i, j;
	ZeroArray(full_gradient, data_dim);

	for (i = 0; i < data_num; i++) {

		OneInstanceLogR2Gradient(tmp_grad, i, array_solution, X, Y, lambda, data_dim, data_num);
		for (j = 0; j < data_dim; j++) {
			full_gradient[j] = full_gradient[j] + tmp_grad[j];
			all_grad[j][i] = 1.0*tmp_grad[j];
		}
	}

	for (j = 0; j < data_dim; j++)
		full_gradient[j] = 1.0*full_gradient[j] / data_num;
}