#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"
#include "int_algebra.h"
#include "typeInfo.h"

typedef struct TypeInfo TypeInfo;

void* zero_int() {
    int* zero = malloc(sizeof(int));
    *(int*)zero = 0;
    return zero;
}

void* one_int() {
    int* one = malloc(sizeof(int));
    *(int*)one = 1;
    return one;
}

void* minus_int(void* number) {
    int* negative = malloc(sizeof(int));
    *(int*)negative = -(*(int*)number);
    return negative;
}

void* sum_int(void* a, void* b) {
    int* c = malloc(sizeof(int));
    *(int*)c = *(int*)a + *(int*)b;
    return c;
}

void* mul_int(void* a, void* b) {
    int* c = malloc(sizeof(int));
    *(int*)c = *(int*)a * *(int*)b;
    return c;
}

void* random_int() {
    int a[2] = {-1, 1};
    int *res = malloc(sizeof(int));
    *res = a[rand() % 2] * (rand() % 7);
    return res;
}

void show_int(int* a) {
    printf("%d", *(int*)a);
}

TypeInfo* MakeIntType() {
    TypeInfo* type_int = malloc(sizeof(TypeInfo));
    type_int->elementSize = sizeof (int);
    type_int->zero = zero_int();
    type_int->one = one_int();
    type_int->minus = (void*)minus_int;
    type_int->sum = (void*)sum_int;
    type_int->mul = (void*)mul_int;
    type_int->random = (void*)random_int;
    type_int->show = (void*)show_int;
    return type_int;
}

Polynom *Create0Int(size_t maxDegree) {
    TypeInfo* type_int = MakeIntType();
    return Create0(maxDegree, type_int);
}

Polynom *CreateFromValuesInt(size_t maxDegree, void *coefficients) {
    TypeInfo* type_int = MakeIntType();
    return CreateFromValues(maxDegree, type_int, coefficients);
}

Polynom *CreateRandomInt(size_t maxDegree) {
    TypeInfo* type_int = MakeIntType();
    return CreateRandom(maxDegree, type_int);
}
