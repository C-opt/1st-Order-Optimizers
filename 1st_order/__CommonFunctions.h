#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int RandomFrom(int min, int max);
void *malloc_e(size_t size);
double Sigmoid(double z);
double L2Norm(double *array, int array_size);
double inner_product(double *array1, double *array2, int data_dim);
double absolute(double num);
double maximum(double num1, double num2);
void prox_map(double *array, int array_size, double lambda1, double lambda2);