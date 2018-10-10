#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int RandomFrom(int min, int max);
void *malloc_e(size_t size);
double Sigmoid(double z);
double L2Norm(double *array, int array_size);