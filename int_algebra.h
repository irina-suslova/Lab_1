#ifndef INT_ALGEBRA_H
#define INT_ALGEBRA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"

void* zero_int();

void* one_int();

void* minus_int(void* number);

void* sum_int(void* a, void* b);

void* mul_int(void* a, void* b);

void* random_int();

void show_int(int* a);

Polynom* Create0Int(size_t maxDegree);
Polynom* CreateFromValuesInt(size_t maxDegree, void* coefficients);
Polynom* CreateRandomInt(size_t maxDegree);

#endif // INT_ALGEBRA_H
