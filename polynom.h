#ifndef POLYNOM_H
#define POLYNOM_H

#include <stdio.h>
#include "typeInfo.h"

struct Polynom;
typedef struct Polynom Polynom;
typedef struct TypeInfo TypeInfo;

// Создание
Polynom* Create0(size_t maxDegree, TypeInfo* type);
Polynom* CreateFromValues(size_t maxDegree, TypeInfo* type, void* coefficients);
Polynom* CreateRandom(size_t maxDegree, TypeInfo* type);

// Дополнительно
Polynom* Copy(Polynom *p);
void Destructor(Polynom *p);

// Декомпозиция
void* Get(size_t coord, Polynom *p);
void Set(size_t coord, void *value, Polynom *p);

// Функции
Polynom* Sum(Polynom *p1, Polynom *p2);
Polynom* Diff(Polynom *p1, Polynom *p2);
Polynom* ScalarMul(Polynom *p, void *a);
Polynom* Mul(Polynom *p1, Polynom *p2);
void* PolynomValue(Polynom *p, void *a);

// Дополнительные функции
Polynom* Composition(Polynom *p1_where, Polynom *p2_what);
Polynom* Derivative(Polynom *p);
Polynom* NDerivative(Polynom *p, size_t n);

void ShowPolynom(Polynom *p);

#endif // POLYNOM_H
