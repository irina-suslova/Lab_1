#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"
#include "typeInfo.h"

typedef struct TypeInfo TypeInfo;

struct Polynom {
    size_t maxDegree;
    void* coefficients;

    TypeInfo* type;
};
typedef struct Polynom Polynom;

Polynom* Create0(size_t maxDegree, TypeInfo* type) {
    Polynom *p = malloc(sizeof(Polynom));
    p->maxDegree = maxDegree;
    p->type = type;
    p->coefficients = malloc(p->type->elementSize * (p->maxDegree + 1));
    for (size_t i = 0; i < maxDegree + 1; ++i) {
        int8_t* position = (int8_t*)p->coefficients + i * p->type->elementSize;
        memcpy(position, p->type->zero, p->type->elementSize);
    }

    return p;
}

Polynom* CreateFromValues(size_t maxDegree, TypeInfo* type, void *coefficients) {
    Polynom *p = Create0(maxDegree, type);
    for (size_t i = 0; i < maxDegree + 1; ++i) {
        int8_t* position = (int8_t*)p->coefficients + i * p->type->elementSize;
        int8_t* coeff = coefficients + i * p->type->elementSize;
        memcpy(position, coeff, p->type->elementSize);
    }
    return p;
}

Polynom* CreateRandom(size_t maxDegree, TypeInfo* type) {
    Polynom *p = Create0(maxDegree, type);
    for (size_t i = 0; i <= maxDegree; ++i) {
        int8_t* position = (int8_t*)p->coefficients + i * p->type->elementSize;
        int8_t* value = p->type->random();
        memcpy(position, value, p->type->elementSize);
        free(value);
    }
    return p;
}

Polynom* Copy(Polynom *p) {
    TypeInfo* type = malloc(sizeof(TypeInfo));
    memcpy(type, p->type, sizeof(TypeInfo));
    int8_t* zero = malloc(p->type->elementSize);
    memcpy(zero, p->type->zero, p->type->elementSize);
    type->zero = zero;
    int8_t* one = malloc(p->type->elementSize);
    memcpy(one, p->type->one, p->type->elementSize);
    type->one = one;
    return CreateFromValues(p->maxDegree, type, p->coefficients);
}

Polynom* Copy0(Polynom *p, size_t maxDegree) {
    TypeInfo* type = malloc(sizeof(TypeInfo));
    memcpy(type, p->type, sizeof(TypeInfo));
    int8_t* zero = malloc(p->type->elementSize);
    memcpy(zero, p->type->zero, p->type->elementSize);
    type->zero = zero;
    int8_t* one = malloc(p->type->elementSize);
    memcpy(one, p->type->one, p->type->elementSize);
    type->one = one;

    return Create0(maxDegree, type);
}

void Destructor(Polynom *p) {
    free(p->coefficients);
    free(p->type->zero);
    free(p->type->one);
    free(p->type);
    free(p);
}

void* Get(size_t coord, Polynom *p) {
    return p->coefficients + coord * p->type->elementSize;
}

void Set(size_t coord, void *value, Polynom *p) {
    int8_t* position = (int8_t*)p->coefficients + coord * p->type->elementSize;
    memcpy(position, value, p->type->elementSize);
}

size_t max(size_t a, size_t b) {
    return a >= b ? a : b;
}

size_t min(size_t a, size_t b) {
    return a <= b ? a : b;
}

Polynom* Sum(Polynom *p1, Polynom *p2) {
    if (!p1 || !p2) return NULL;
    if (p1->type->elementSize != p2->type->elementSize) return NULL;
    size_t p_res_maxDegree = max(p1->maxDegree, p2->maxDegree);
    Polynom *p_res = Copy0(p1, p_res_maxDegree);
    for (size_t i = 0; i < p_res->maxDegree + 1; ++i) {
        if(i <= p1->maxDegree  && i <= p2->maxDegree ) {

            int8_t* s = p_res->type->sum(Get(i, p1), Get(i, p2));

            Set(i, s, p_res);

            free(s);
            continue;
        }
        if(i > p1->maxDegree) {
            Set(i, Get(i, p2), p_res);
            continue;
        }
        if(i > p2->maxDegree) {
            Set(i, Get(i, p1), p_res);
            continue;
        }
    }
    return p_res;
}

Polynom* Diff(Polynom *p1, Polynom *p2) {
    if (!p1 || !p2) return NULL;
    if (p1->type->elementSize != p2->type->elementSize) return NULL;
    size_t p_res_maxDegree = max(p1->maxDegree, p2->maxDegree);
    Polynom *p_res = Copy0(p1, p_res_maxDegree);
    for (size_t i = 0; i < p_res->maxDegree + 1; ++i) {
        if(i <= p1->maxDegree && i <= p2->maxDegree) {

            int8_t* m = p_res->type->minus(Get(i, p2));
            int8_t* s = p_res->type->sum(Get(i, p1), m);
            Set(i, s, p_res);
            free(m);
            free(s);
            continue;
        }
        if(i > p1->maxDegree) {
            int8_t* m = p_res->type->minus(Get(i, p2));
            Set(i, m, p_res);
            free(m);
            continue;
        }
        if(i > p2->maxDegree) {
            Set(i, Get(i, p1), p_res);
            continue;
        }
    }
    return p_res;
}

Polynom* ScalarMul(Polynom *p, void *a) {
    if (!p || !a) return NULL;
    Polynom *p_res = Copy0(p, p->maxDegree);
    for (size_t i = 0; i <= p_res->maxDegree; ++i) {
        int8_t* m = p_res->type->mul(Get(i, p), a);
        Set(i, m, p_res);
        free(m);
    }
    return p_res;
}

Polynom* Mul(Polynom *p1, Polynom *p2) {
    if (!p1 || !p2) return NULL;
    if (p1->type->elementSize != p2->type->elementSize) return NULL;
    size_t p_res_maxDegree = p1->maxDegree + p2->maxDegree;
    Polynom *p_res = Copy0(p1, p_res_maxDegree);
    for (size_t i = 0; i <= p1->maxDegree; ++i)
        for (size_t j = 0; j <= p2->maxDegree; ++j) {
            int8_t* m = p_res->type->mul(Get(i, p1), Get(j, p2));
            int8_t* s = p_res->type->sum(m, Get(i + j, p_res));
            Set(i + j, s, p_res);
            free(m);
            free(s);

        }
    return p_res;
}

void* PolynomValue(Polynom *p, void *a) {
    void* a_degree = malloc(p->type->elementSize);
    memcpy(a_degree, p->type->one, p->type->elementSize);
    void* res = malloc(p->type->elementSize);
    memcpy(res, Get(0, p), p->type->elementSize);
    for (size_t i = 1; i <= p->maxDegree; ++i) {
        void* tmp = p->type->mul(a_degree, a);
        memcpy(a_degree, tmp, p->type->elementSize);
        free(tmp);

        int8_t* m = p->type->mul(Get(i, p), a_degree);
        int8_t* s = p->type->sum(res, m);
        memcpy(res, s, p->type->elementSize);
        free(m);
        free(s);
    }
    free(a_degree);
    return res;
}

Polynom* Composition(Polynom *p1, Polynom *p2) {
    // подстановка p2 в p1
    if (!p1 || !p2) return NULL;
    if (p1->type->elementSize != p2->type->elementSize) return NULL;
    Polynom* p_degree = Copy(p2);

    Polynom* p_res = Copy0(p1, 0);
    Set(0, p1->coefficients, p_res);

    for(size_t i = 1; i <= p1->maxDegree; ++i) {
        Polynom* sm = ScalarMul(p_degree, Get(i, p1));
        Polynom* tmp = Sum(p_res, sm);

        Destructor(p_res);
        p_res = Copy(tmp);
        Destructor(tmp);

        Destructor(sm);

        if (i != p1->maxDegree) {
            tmp = Mul(p_degree, p2);
            Destructor(p_degree);
            p_degree = Copy(tmp);
            Destructor(tmp);
        }
    }
    Destructor(p_degree);
    return p_res;
}

Polynom* Derivative(Polynom *p) {
    size_t p_res_maxDegree = p->maxDegree == 0 ? 0 : p->maxDegree - 1;
    Polynom *p_res = Copy0(p, p_res_maxDegree);

    Polynom* degree = Copy0(p, 0);
    Set(0, p->type->one, degree);

    Polynom* one = Copy0(p, 0);
    Set(0, p->type->one, one);

    for (size_t i = 1; i <= p->maxDegree; ++i) {

        Polynom* a = Copy0(p, 0);
        Set(0, p->coefficients + i * p->type->elementSize, a);

        Polynom* sm = Mul(a, degree);
        Set(i - 1, Get(0, sm), p_res);

        if (i != p->maxDegree) {
            Polynom* tmp = Sum(degree, one);
            Destructor(degree);
            degree = Copy(tmp);
            Destructor(tmp);
        }

        Destructor(sm);
        Destructor(a);
    }

    Destructor(degree);
    Destructor(one);
    return p_res;
}

void ShowPolynom(Polynom *p) {
    p->type->show(Get(0, p));
    for(size_t i = 1; i < p->maxDegree + 1; ++i) {
        printf(" + ");
        p->type->show(Get(i, p));
        printf(" x^%d", (int)i);
    }
    printf("\n");
}

Polynom* NDerivative(Polynom *p, size_t n) {
    Polynom* p_res = Copy(p);
    for (size_t i = 0; i < n; ++i) {
        Polynom* tmp = Derivative(p_res);
        Destructor(p_res);
        p_res = tmp;
    }
    return p_res;
}
