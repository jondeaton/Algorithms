#include <iostream>
#include <cassert>
#include <cmath> 

float my_function(float x) {
	float f = x * std::exp(x) - 5;
	return f;
}

float diff_func(float (*func)(float), float x, float h=0.0001) {
	return (func(x + h) - func(x - h)) / (2 * h);
}

float newton(float (*func)(float), float x0, float tol=0.0001) {
	float f = func(x0);
	float df = diff_func(func, x0);
	assert(df != 0);
	float x1 = x0 - (f / df);
	float error = std::fabs(x1 - x0);
	while (error > tol) {
		x0 = x1;
		f = func(x0);
		df = diff_func(func, x0);
		assert(df != 0);
		x1 = x0 - f / df;
		error = std::fabs(x1 - x0);
	}
	return x1;
}

int main(int argc, char* argv[]) {
	float root = newton(my_function, 1);
	printf("f(%f) ~= 0\n",root);
}