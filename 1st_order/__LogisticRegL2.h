#pragma once
double LogRegressionR1R2Obj(double* array_solution, double **X, double* Y, double lambda1, double lambda2, int data_dim, int data_num);
void OneInstanceLogR1R2Gradient(double* instance_gradient, int data_idx, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);
void FullLogR1R2Gradient(double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);
void AllFullLogR1R2Gradient(double** all_grad, double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);