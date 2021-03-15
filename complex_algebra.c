#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"
#include "complex_algebra.h"
#include "typeInfo.h"

typedef struct TypeInfo TypeInfo ;

typedef struct Complex {
    float Re;
    float Im;
} Complex;

void* zero_complex() {
    Complex* zero = malloc(sizeof(Complex));
    zero->Re = 0.0;
    zero->Im = 0.0;
    return (void*)zero;
}

void* one_complex() {
    Complex* one = malloc(sizeof(Complex));
    one->Re = 1.0;
    one->Im = 0.0;
    return (void*)one;
}

void* minus_complex(void* number) {
    Complex* negative = malloc(sizeof(Complex));
    negative->Re = -((Complex*)number)->Re;
    negative->Im = -((Complex*)number)->Im;
    return (void*)negative;
}

void* sum_complex(void* a, void* b) {
    Complex* c = malloc(sizeof(Complex));
    c->Re = ((Complex*)a)->Re + ((Complex*)b)->Re;
    c->Im = ((Complex*)a)->Im + ((Complex*)b)->Im;
    return (void*)c;
}

void* mul_complex(void* a, void* b) {
    Complex* c = malloc(sizeof(Complex));
    c->Re = ((Complex*)a)->Re * ((Complex*)b)->Re - ((Complex*)a)->Im * ((Complex*)b)->Im;
    c->Im = ((Complex*)a)->Im * ((Complex*)b)->Re + ((Complex*)a)->Re * ((Complex*)b)->Im;
    return c;
}

void* random_complex() {
    float a[2] = {-1.0, 1.0};
    Complex *res = malloc(sizeof(Complex));
    res->Re = a[rand() % 2] * (rand() % 7);
    res->Im = a[rand() % 2] * (rand() % 7);
    return res;
}

void show_complex(void* a) {
    if (((Complex*)a)->Im >= 0) printf("%.1lf+%.1lfi", ((Complex*)a)->Re, ((Complex*)a)->Im);
    else printf("%.1lf-%.1lfi", ((Complex*)a)->Re, -((Complex*)a)->Im);
}

TypeInfo* MakeComplexType() {
    TypeInfo* type_complex = malloc(sizeof(TypeInfo));
    type_complex->elementSize = sizeof (Complex);
    type_complex->zero = zero_complex();
    type_complex->one = one_complex();
    type_complex->minus = (void*)minus_complex;
    type_complex->sum = (void*)sum_complex;
    type_complex->mul = (void*)mul_complex;
    type_complex->random = (void*)random_complex;
    type_complex->show = (void*)show_complex;
    return type_complex;
}

Polynom* Create0Complex(size_t maxDegree) {
    TypeInfo* type_complex = MakeComplexType();
    return Create0(maxDegree, type_complex);
}

Polynom* CreateFromValuesComplex(size_t maxDegree, void* coefficients) {
    TypeInfo* type_complex = MakeComplexType();
    return CreateFromValues(maxDegree, type_complex, coefficients);
}

Polynom* CreateRandomComplex(size_t maxDegree) {
    TypeInfo* type_complex = MakeComplexType();
    return CreateRandom(maxDegree, type_complex);
}

Complex* MakeComplex(float* Re, float* Im) {
    Complex* a = (Complex*)malloc(sizeof(Complex));
    a->Re = *Re;
    a->Im = *Im;
    return a;
}

size_t SizeOfComplex() {
    return sizeof (Complex);
}

int IsEqual(Complex *a, Complex *b) {
    if (!a || !b) return -1;
    if (a->Re == b->Re && a->Im == b->Im) return 1;
    return 0;
}
