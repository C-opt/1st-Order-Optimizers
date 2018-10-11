#include "__CommonFunctions.h"
#include "__MatrixFunctions.h"

double LogRegressionR1R2Obj(double* array_solution, double **X, double* Y, double lambda1, double lambda2, int data_dim, int data_num) {
	double objective_value;
	double tmp_sum = 0;
	double tmp_L1_sum = 0;
	double tmp_inner_product;

	int i, j;

	for (i = 0; i < data_num; i++) {
		tmp_inner_product = 0;
		for (j = 0; j < data_dim; j++)
			tmp_inner_product = tmp_inner_product + X[j][i] * array_solution[j];
		tmp_sum = tmp_sum + log(1 + exp(-Y[i] * tmp_inner_product));
	}

	for(j = 0; j < data_dim; j++)
		tmp_L1_sum = tmp_L1_sum + absolute(array_solution[j]);

	tmp_inner_product = inner_product(array_solution, array_solution, data_dim);
	objective_value = 1.0*tmp_sum / data_num + 0.5*lambda2*tmp_inner_product + 1.0*lambda1*tmp_L1_sum;

	return objective_value;
}

void OneInstanceLogR1R2Gradient(double* instance_gradient, int data_idx, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int j;
	double tmp_inner_product, sigma_value;
	tmp_inner_product = 0;

	for (j = 0; j < data_dim; j++)
		tmp_inner_product = tmp_inner_product + X[j][data_idx] * array_solution[j];
	sigma_value = Sigmoid(-Y[data_idx] * tmp_inner_product);

	for (j = 0; j < data_dim; j++)
		instance_gradient[j] = -Y[data_idx] * X[j][data_idx] * sigma_value + lambda * array_solution[j];
}

void FullLogR1R2Gradient(double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int i, j;
	ZeroArray(full_gradient, data_dim);

	for (i = 0; i < data_num; i++) {
		OneInstanceLogR1R2Gradient(tmp_grad, i, array_solution, X, Y, lambda, data_dim, data_num);
		for (j = 0; j < data_dim; j++)
			full_gradient[j] = full_gradient[j] + tmp_grad[j];
	}

	for (j = 0; j < data_dim; j++)
		full_gradient[j] = 1.0*full_gradient[j] / data_num;
}

void AllFullLogR1R2Gradient(double** all_grad, double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num) {
	int i, j;
	ZeroArray(full_gradient, data_dim);

	for (i = 0; i < data_num; i++) {

		OneInstanceLogR1R2Gradient(tmp_grad, i, array_solution, X, Y, lambda, data_dim, data_num);
		for (j = 0; j < data_dim; j++) {
			full_gradient[j] = full_gradient[j] + tmp_grad[j];
			all_grad[j][i] = 1.0*tmp_grad[j];
		}
	}

	for (j = 0; j < data_dim; j++)
		full_gradient[j] = 1.0*full_gradient[j] / data_num;
}