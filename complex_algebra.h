#ifndef COMPLEX_ALGEBRA_H
#define COMPLEX_ALGEBRA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"

struct Complex;
typedef struct Complex Complex;

void* zero_complex();

void* one_complex();

void* minus_complex(void* number);

void* sum_complex(void* a, void* b);

void* mul_complex(void* a, void* b);

void* random_complex();

void show_complex(void* a);

Polynom* Create0Complex(size_t maxDegree);
Polynom* CreateFromValuesComplex(size_t maxDegree, void* coefficients);
Polynom* CreateRandomComplex(size_t maxDegree);

Complex* MakeComplex(float* Re, float* Im);
size_t SizeOfComplex();
int IsEqual(Complex* a, Complex* b);

#endif // COMPLEX_ALGEBRA_H
