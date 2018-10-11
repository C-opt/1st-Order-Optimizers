#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int RandomFrom(int min, int max) {
	int x;
	x = rand() % (max - min + 1);
	return min + x;
}

/* malloc with error check */
void *malloc_e(size_t size) {
	void *s;
	if ((s = malloc(size)) == NULL) {
		fprintf(stderr, "malloc: not enough memory\n");
		exit(EXIT_FAILURE);
	}
	return s;
}

double Sigmoid(double z) {
	double func_value;
	func_value = 1.0 / (1 + exp(-z));
	return func_value;
}

double L2Norm(double *array, int array_size) {
	double tmp_sum = 0;
	double norm;
	int i;

	for (i = 0; i < array_size; i++)
		tmp_sum = tmp_sum + array[i] * array[i];
	norm = sqrt(tmp_sum);
	return norm;
}

double inner_product(double *array1, double *array2, int data_dim) {

	int tmp_inner_product = 0;
	int j;

	for (j = 0; j < data_dim; j++)
		tmp_inner_product = tmp_inner_product + array1[j] * array2[j];

	return tmp_inner_product;
}

double absolute(double num) {
	if (num < 0)
		num = -num;
	else
		num = num;
	return num;
}

double maximum(double num1, double num2){
	if (num1 >= num2)
		return num1;
	else
		return num2;
}

void prox_map(double *array, int array_size, double lambda1, double lambda2) {
	int i;
	int sign;
	for (i = 0; i < array_size; i++) {
		if (array[i] >= 0)
			sign = 1;
		else
			sign = -1;
		array[i] = (1.0 / (1 + lambda2))*sign*maximum(0, absolute(array[i]) - lambda1);
	}
}