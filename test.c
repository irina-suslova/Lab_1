#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"
#include "int_algebra.h"
#include "complex_algebra.h"

int test_sum_int() {
    int a[] = {1, 2};
    Polynom* p1 = CreateFromValuesInt(1, a);
    int b[] = {7, 4, 16, 3, 0, 5};
    Polynom* p2 = CreateFromValuesInt(5, b);

    int res[] = {8, 6, 16, 3, 0, 5};
    Polynom* p_res = Sum(p1, p2);
    int checker = 0;
    for (int i = 0; i <= 5; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p_res);
    Destructor(p1);
    Destructor(p2);
    return checker;
}

int test_diff_int() {
    int a[] = {1, 2, 3, 8};
    Polynom* p1 = CreateFromValuesInt(3, a);
    int b[] = {7, 4, 16, 3, 0, 5};
    Polynom* p2 = CreateFromValuesInt(5, b);

    int res[] = {-6, -2, -13, 5, 0, -5};
    Polynom* p_res = Diff(p1, p2);
    int checker = 0;
    for (int i = 0; i <= 5; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);
    return checker;
}

int test_scalarmul_int() {
    int a[] = {1, 2, 0, -2};
    Polynom* p1 = CreateFromValuesInt(3, a);
    int b = 5;

    int res[] = {5, 10, 0, -10};
    Polynom* p_res = ScalarMul(p1, &b);
    int checker = 0;
    for (int i = 0; i <= 3; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p_res);
    return checker;
}

int test_mul_int() {
    int a[] = {1, 2};
    Polynom* p1 = CreateFromValuesInt(1, a);
    int b[] = {0, 0, 2};
    Polynom* p2 = CreateFromValuesInt(2, b);

    int res[] = {0, 0, 2, 4};
    Polynom* p_res = Mul(p1, p2);
    int checker = 0;
    for (int i = 0; i <= 3; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);
    return checker;
}

int test_polynomvalue_int() {
    int a[] = {1, 2, 0, -2};
    Polynom* p1 = CreateFromValuesInt(3, a);
    int b = 5;

    int res = 1 + 2*5 - 2*5*5*5;
    void* p_res = PolynomValue(p1, &b);
    int checker = 0;
    if (!p_res || *(int*)p_res != res) {
        checker = 1;
    }
    Destructor(p1);
    return checker;
}

int test_composition_int() {
    int a[] = {1, 2};
    Polynom* p1 = CreateFromValuesInt(1, a);
    int b[] = {3, 0, 2};
    Polynom* p2 = CreateFromValuesInt(2, b);

    int res[] = {7, 0, 4};
    Polynom* p_res = Composition(p1, p2);
    int checker = 0;
    for (int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);
    return checker;
}

int test_derivative_int() {
    int a[] = {1, 2, 0, -2};
    Polynom* p1 = CreateFromValuesInt(3, a);

    int res[] = {2, 0, -6};
    Polynom* p_res = Derivative(p1);
    int checker = 0;
    for (int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p_res);
    return checker;
}

int test_Nderivative_int() {
    int a[] = {1, 2, 0, -2};
    Polynom* p1 = CreateFromValuesInt(3, a);
    size_t b = 2;

    int res[] = {0, -12};
    Polynom* p_res = NDerivative(p1, b);
    int checker = 0;
    for (int i = 0; i <= 1; ++i) {
        if (!Get(i, p_res) || *(int*)Get(i, p_res) != res[i]) {
            checker = 1;
            break;
        }
    }
    Destructor(p1);
    Destructor(p_res);
    return checker;
}

int test_sum_complex() {
    void* a = malloc(SizeOfComplex() * 3);
    void* b = malloc(SizeOfComplex() * 2);

    float re = 5.0;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 0.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy(b, z, SizeOfComplex());
    free(z);

    re = 8.0;
    im = 1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)b + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 3);

    re = 5.0;
    im = 1.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = 10.0;
    im = 1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);
    Polynom* p2 = CreateFromValuesComplex(1, b);
    Polynom* p_res = Sum(p1, p2);

    int checker = 0;
    for(int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);

    free(a);
    free(b);
    free(res);
    return checker;
}

int test_diff_complex() {
    void* a = malloc(SizeOfComplex() * 3);
    void* b = malloc(SizeOfComplex() * 2);

    float re = 5.0;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 0.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy(b, z, SizeOfComplex());
    free(z);

    re = 8.0;
    im = 1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)b + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 3);

    re = 5.0;
    im = 1.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = -6.0;
    im = -1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);
    Polynom* p2 = CreateFromValuesComplex(1, b);

    Polynom* p_res = Diff(p1, p2);

    int checker = 0;
    for(int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);

    free(a);
    free(b);
    free(res);
    return checker;
}

int test_scalarmul_complex() {
    void* a = malloc(SizeOfComplex() * 3);

    float re = 5.0;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);


    void* res = malloc(SizeOfComplex() * 3);

    re = 9.0;
    im = 7.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = 4.0;
    im = 2.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -5.0;
    im = 5.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 1.0;
    Complex* b = MakeComplex(&re, &im);


    Polynom* p1 = CreateFromValuesComplex(2, a);

    Polynom* p_res = ScalarMul(p1, b);

    int checker = 0;
    for(int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p_res);

    free(a);
    free(b);
    free(res);
    return checker;
}

int test_mul_complex() {
    void* a = malloc(SizeOfComplex() * 3);
    void* b = malloc(SizeOfComplex() * 2);

    float re = 5.0;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 0.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy(b, z, SizeOfComplex());
    free(z);

    re = 8.0;
    im = 1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)b + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 4);

    re = 0.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = 38.5;
    im = 15.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 16.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -12.5;
    im = 22.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 3*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);
    Polynom* p2 = CreateFromValuesComplex(1, b);

    Polynom* p_res = Mul(p1, p2);

    int checker = 0;
    for(int i = 0; i <= 3; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);

    free(a);
    free(b);
    free(res);
    return checker;
}

int test_polynomvalue_complex() {
    void* b = malloc(SizeOfComplex() * 2);

    float re = 0.0;
    float im = 0.5;
    Complex* z = MakeComplex(&re, &im);
    memcpy(b, z, SizeOfComplex());
    free(z);

    re = 8.0;
    im = 1.5;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)b + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 1.0;
    im = 0.0;
    Complex* a = MakeComplex(&re, &im);

    re = 8.0;
    im = 2.0;
    Complex* res = MakeComplex(&re, &im);

    Polynom* p2 = CreateFromValuesComplex(1, b);
    Complex* p_res = PolynomValue(p2, a);

    int checker = 0;
    if (IsEqual(res, p_res) != 1) checker = 1;

    Destructor(p2);

    free(p_res);
    free(a);
    free(b);
    free(res);
    return checker;
}

int test_composition_complex() {
    void* a = malloc(SizeOfComplex() * 3);
    void* b = malloc(SizeOfComplex() * 2);

    float re = 5.4;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.1;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = 0.0;
    im = 0.0;
    z = MakeComplex(&re, &im);
    memcpy(b, z, SizeOfComplex());
    free(z);

    re = 8.0;
    im = 1.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)b + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 3);

    re = 5.4;
    im = 1.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = 15.9;
    im = 2.8;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -111.0;
    im = 173.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);
    Polynom* p2 = CreateFromValuesComplex(1, b);

    Polynom* p_res = Composition(p1, p2);

    int checker = 0;
    for(int i = 0; i <= 2; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p2);
    Destructor(p_res);

    free(a);
    free(b);
    free(res);
    return checker;
}

int test_derivative_complex() {
    void* a = malloc(SizeOfComplex() * 3);

    float re = 5.4;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.1;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 2);

    re = 2.0;
    im = 0.1;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    re = -2.0;
    im = 6.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)res + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);

    Polynom* p_res = Derivative(p1);

    int checker = 0;
    for(int i = 0; i <= 1; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p_res);

    free(a);
    free(res);
    return checker;
}

int test_Nderivative_complex() {
    void* a = malloc(SizeOfComplex() * 3);

    float re = 5.4;
    float im = 1.0;
    void* z = MakeComplex(&re, &im);
    memcpy(a, z, SizeOfComplex());
    free(z);

    re = 2.0;
    im = 0.1;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + SizeOfComplex(), z, SizeOfComplex());
    free(z);

    re = -1.0;
    im = 3.0;
    z = MakeComplex(&re, &im);
    memcpy((int8_t*)a + 2*SizeOfComplex(), z, SizeOfComplex());
    free(z);

    void* res = malloc(SizeOfComplex() * 1);

    re = -2.0;
    im = 6.0;
    z = MakeComplex(&re, &im);
    memcpy(res, z, SizeOfComplex());
    free(z);

    Polynom* p1 = CreateFromValuesComplex(2, a);

    Polynom* p_res = NDerivative(p1, 2);

    int checker = 0;
    for(int i = 0; i <= 0; ++i) {
        if (!Get(i, p_res) || IsEqual(Get(i, p_res), (Complex*)((int8_t*)res + i * SizeOfComplex())) != 1) {
            checker = 1;
            break;
        }
    }

    Destructor(p1);
    Destructor(p_res);

    free(a);
    free(res);
    return checker;
}

void test_polynom() {
    printf("test sum int: ");
    if (test_sum_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test diff int: ");
    if (test_diff_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test scalarmul int: ");
    if (test_scalarmul_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test mul int: ");
    if (test_mul_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test polynomvalue int: ");
    if (test_polynomvalue_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test composition int: ");
    if (test_composition_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test derivative int: ");
    if (test_derivative_int() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test Nderivative int: ");
    if (test_Nderivative_int() == 0) printf("passed \n");

    printf("test sum complex: ");
    if (test_sum_complex() == 0) printf("passed \n");

    printf("test diff complex: ");
    if (test_diff_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test scalarmul complex: ");
    if (test_scalarmul_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test mul complex: ");
    if (test_mul_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test polynomvalue complex: ");
    if (test_polynomvalue_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test composition complex: ");
    if (test_composition_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test derivative complex: ");
    if (test_derivative_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("test Nderivative complex: ");
    if (test_Nderivative_complex() == 0) printf("passed \n");
    else printf("failed \n");

    printf("\n");
}
