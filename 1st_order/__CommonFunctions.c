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