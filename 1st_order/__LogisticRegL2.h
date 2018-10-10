#pragma once
double LogRegressionR2Obj(double* array_solution, double **X, double* Y, double lambda, int data_dim, int data_num);
void OneInstanceLogR2Gradient(double* instance_gradient, int data_idx, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);
void FullLogR2Gradient(double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);
void AllFullLogR2Gradient(double** all_grad, double* full_gradient, double* tmp_grad, double* array_solution, double** X, double* Y, double lambda, int data_dim, int data_num);
