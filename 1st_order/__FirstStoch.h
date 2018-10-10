#pragma once

double SVRG(double* array_solution, double** experiment_matrix, double **X, double* Y, double lambda, int data_dim, int data_num, int stage_num, int m);
double FISTA(double* array_solution, double **X, double* Y, double lambda, int data_dim, int data_num, int max_iter, double epsilon);
double __optimizer(double* array_solution, double **X, double* Y, double lambda, int data_dim, int data_num, int stage_num, int m, int max_iter, double epsilon);