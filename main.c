#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "polynom.h"
#include "int_algebra.h"
#include "complex_algebra.h"

typedef struct Complex Complex ;

const char *MSGS[] = {"What do you want to do?",
                      "0. Quit",
                      "1. Sum of polynomials",
                      "2. Difference of polynomials",
                      "3. Scalar Mul",
                      "4. Mul of polynomials",
                      "5. Value of polynomial at point",
                      "6. Composition of polynomials",
                      "7. Derivative",
                      "8. Value of derivative at point",
                      "9. Derivative of n order",
                      "10. Value of derivative of n order at point",
                     };
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

const char *MSGS_TYPE[] = {"Which type of polynomial do you need?",
                           "0. Quit",
                           "1. To previous step",
                           "2. Integer numbers",
                           "3. Complex numbers",
                          };
const int MSGS_TYPE_SIZE = sizeof(MSGS_TYPE) / sizeof(MSGS_TYPE[0]);

const char *MSGS_INPUT[] = {"Do you want to generate coefficients for polynomial or using keyboard input?",
                            "0. Quit",
                            "1. To previous step",
                            "2. Generate",
                            "3. Keyboard input",
                           };
const int MSGS_INPUT_SIZE = sizeof(MSGS_INPUT) / sizeof(MSGS_INPUT[0]);

int dialog(const char *msgs[], int n, int mode) {
    if (mode) return mode;
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "Incorrect input. Please, enter one positive integer number.\n";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        choice = getchar() - '0';
        char c = getchar();
        while (c != '\n') {
            if (0 <= (int)c - '0' && (int)c - '0' <= 9)
                choice = choice * 10 + (c - '0');
            c = getchar();
        }
    } while (choice < 0 || choice >= n);
    return choice;
}

int read_degree(size_t* degree) {
    int mode = 0;
    printf("Enter max degree of the polynomial:\n");
    if (scanf("%llu", degree) != 1 || *degree < 0) {
        while (getchar() != '\n') {};
        printf("Incorrect input. Please, enter one positive integer number.\n");
        mode = -1;
    }
    if (mode == 0) while (getchar() != '\n') {};
    return mode;
}

void* read_polynom_int(size_t degree_1) {
    int* coefficients = (int*)malloc(sizeof(int) * (degree_1 + 1));
    for (size_t i = 0; i <= degree_1; ++i) {
        printf("coefficient at x^%llu = ", i);
        if (scanf("%d", coefficients + i) != 1) {
            while (getchar() != '\n') {};
            printf("Incorrect input. Please, enter one integer number.\n");
            free(coefficients);
            return NULL;
        }
        while (getchar() != '\n') {};
    }
    return (void*)coefficients;
}

void* read_polynom_complex(size_t degree_1) {
    void* coefficients = malloc(SizeOfComplex() * (degree_1 + 1));
    for (size_t i = 0; i <= degree_1; ++i) {
        float Re = 0.0, Im = 0.0;
        printf("coefficient at x^%llu Re = ", i);
        if (scanf("%f", &Re) != 1) {
            while (getchar() != '\n') {};
            printf("Incorrect input. Please, enter one positive integer number.\n");
            free(coefficients);
            return NULL;
        }
        while (getchar() != '\n') {};

        printf("coefficient at x^%llu Im = ", i);
        if (scanf("%f", &Im) != 1) {
            while (getchar() != '\n') {};
            printf("Incorrect input. Please, enter one positive integer number.\n");
            free(coefficients);
            return NULL;
        }
        while (getchar() != '\n') {};

        Complex* z = MakeComplex(&Re, &Im);
        memcpy((int8_t*)coefficients + SizeOfComplex() * i, z, SizeOfComplex());
        free(z);
    }
    return coefficients;
}

int* read_int(char msg[250]) {
    int *a = malloc(sizeof (int));
    printf("%s", msg);
    if (scanf("%d", a) != 1) {
        while (getchar() != '\n') {};
        printf("Incorrect input. Please, enter one integer number.\n");
        free(a);
        return NULL;
    }
    return a;
}

int* read_unsigned_int(char msg[250]) {
    int *a = malloc(sizeof (int));
    printf("%s", msg);
    if (scanf("%d", a) != 1 || a < 0) {
        while (getchar() != '\n') {};
        printf("Incorrect input. Please, enter one integer number.\n");
        free(a);
        return NULL;
    }
    return a;
}

Complex* read_complex(char msg[250]) {
    Complex *a = malloc(SizeOfComplex());
    printf("%s", msg);
    float Re = 0.0, Im = 0.0;
    printf("Re = ");
    if (scanf("%f", &Re) != 1) {
        while (getchar() != '\n') {};
        printf("Incorrect input. Please, enter one positive integer number.\n");
        free(a);
        return NULL;
    }
    while (getchar() != '\n') {};

    printf("Im = ");
    if (scanf("%f", &Im) != 1) {
        while (getchar() != '\n') {};
        printf("Incorrect input. Please, enter one positive integer number.\n");
        free(a);
        return NULL;
    }
    while (getchar() != '\n') {};

    Complex* z = MakeComplex(&Re, &Im);
    memcpy((int8_t*)a, z, SizeOfComplex());
    free(z);
    return a;
}

int main() {
    srand(time(NULL));
    test_polynom();
    int cmd = 0;
    int cmd_type = 0;
    int cmd_input = 0;
    int mode = 0;
    int* order;
    void* a_int;
    void* a_complex;
    void* a_res;
    size_t degree_1, degree_2;
    Polynom* p1;
    Polynom* p2;
    Polynom* p_res;
    void* coefficients_1;
    void* coefficients_2;


    printf("Hello! I've made a little program for working with polynomials. You are welcome :)");
    do {
        cmd = dialog(MSGS, MSGS_SIZE, mode);
        mode = 0;
        switch(cmd) {
        case 0:
            printf("Goodbye! :)");
            break;
        case 1:
            printf("\nOption 1 - Sum\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 1;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }


                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);
                    p2 = CreateRandomInt(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Sum(p1, p2);
                    printf("Sum of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    int* coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 1;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    int* coefficients_2 = read_polynom_int(degree_2);
                    if (!coefficients_1) {
                        mode = 1;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);
                    p2 = CreateFromValuesInt(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Sum(p1, p2);
                    printf("Sum of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 1;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);
                    p2 = CreateRandomComplex(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Sum(p1, p2);
                    printf("Sum of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    Complex* coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 1;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 1;
                        break;
                    }

                    Complex* coefficients_2 = read_polynom_complex(degree_2);
                    if (!coefficients_1) {
                        mode = 1;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);
                    p2 = CreateFromValuesComplex(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Sum(p1, p2);
                    printf("Sum of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);


                    break;
                }
                break;

            }

            break;
        case 2:
            printf("\nOption 2 - Difference\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 2;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);
                    p2 = CreateRandomInt(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Diff(p1, p2);
                    printf("Diff of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 2;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    coefficients_2 = read_polynom_int(degree_2);
                    if (!coefficients_2) {
                        mode = 2;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);
                    p2 = CreateFromValuesInt(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Diff(p1, p2);
                    printf("Diff of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 2;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);
                    p2 = CreateRandomComplex(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Diff(p1, p2);
                    printf("Diff of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 2;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 2;
                        break;
                    }

                    coefficients_2 = read_polynom_complex(degree_2);
                    if (!coefficients_2) {
                        mode = 2;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);
                    p2 = CreateFromValuesComplex(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Diff(p1, p2);
                    printf("Diff of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);


                    break;
                }
                break;

            }

            break;
        case 3:
            printf("\nOption 3 - Scalar Mul\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 3;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 3;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 3;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = ScalarMul(p1, a_int);
                    printf("Scalar of polynomial ans %d: \n", *(int*)a_int);
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(a_int);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 3;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 3;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 3;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = ScalarMul(p1, a_int);
                    printf("Scalar of polynomial ans %d: \n", *(int*)a_int);
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(a_int);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 3;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 3;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 3;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = ScalarMul(p1, a_complex);
                    printf("Scalar mul of polynomial and ");
                    show_complex(a_complex);
                    printf(": \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(a_complex);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 3;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 3;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 3;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = ScalarMul(p1, a_complex);
                    printf("Scalar mul of polynomial and ");
                    show_complex(a_complex);
                    printf(": \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);

                    free(a_complex);
                    break;
                }
                break;

            }

            break;
        case 4:
            printf("\nOption 4 - Mul\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 4;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);
                    p2 = CreateRandomInt(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Mul(p1, p2);
                    printf("Mul of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 4;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    coefficients_2 = read_polynom_int(degree_2);
                    if (!coefficients_2) {
                        mode = 4;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);
                    p2 = CreateFromValuesInt(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Mul(p1, p2);
                    printf("Mul of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 4;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);
                    p2 = CreateRandomComplex(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Mul(p1, p2);
                    printf("Mul of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 4;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 4;
                        break;
                    }

                    coefficients_2 = read_polynom_complex(degree_2);
                    if (!coefficients_2) {
                        mode = 4;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);
                    p2 = CreateFromValuesComplex(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Mul(p1, p2);
                    printf("Mul of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);


                    break;
                }
                break;

            }

            break;
        case 5:
            printf("\nOption 5 - Value at point\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 5;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 5;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 5;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    a_res = PolynomValue(p1, a_int);
                    printf("Value of polynomial at %d: \n", *(int*)a_int);
                    printf("%d\n", *(int*)a_res);

                    Destructor(p1);

                    free(a_int);
                    free(a_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 5;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 5;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 5;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    a_res = PolynomValue(p1, a_int);
                    printf("Value of polynomial at %d: \n", *(int*)a_int);
                    printf("%d\n", *(int*)a_res);

                    Destructor(p1);

                    free(coefficients_1);
                    free(a_int);
                    free(a_res);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 5;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 5;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 5;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    a_res = PolynomValue(p1, a_complex);
                    printf("Scalar mul of polynomial at ");
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);

                    free(a_complex);
                    free(a_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 5;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 5;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 5;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    a_res = PolynomValue(p1, a_complex);
                    printf("Scalar mul of polynomial at ");
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);

                    free(coefficients_1);

                    free(a_complex);
                    free(a_res);
                    break;
                }
                break;

            }


            break;
        case 6:
            printf("\nOption 6 - Composition\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 6;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);
                    p2 = CreateRandomInt(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Composition(p1, p2);
                    printf("Composition of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 6;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    coefficients_2 = read_polynom_int(degree_2);
                    if (!coefficients_2) {
                        mode = 6;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);
                    p2 = CreateFromValuesInt(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Composition(p1, p2);
                    printf("Composition of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 6;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);
                    p2 = CreateRandomComplex(degree_2);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Composition(p1, p2);
                    printf("Composition of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 6;
                        break;
                    }

                    printf("The second polynomial: \n");
                    mode = read_degree(&degree_2);
                    if (mode != 0) {
                        mode = 6;
                        break;
                    }

                    coefficients_2 = read_polynom_complex(degree_2);
                    if (!coefficients_2) {
                        mode = 6;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);
                    p2 = CreateFromValuesComplex(degree_2, coefficients_2);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    ShowPolynom(p2);
                    printf("\n");

                    p_res = Composition(p1, p2);
                    printf("Composition of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p2);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(coefficients_2);


                    break;
                }
                break;

            }

            break;
        case 7:
            printf("\nOption 7 - Derivative\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 7;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 7;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative of polynomial: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 7;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 7;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 7;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 7;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 7;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 7;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative of polynomials: \n");
                    ShowPolynom(p_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);


                    break;
                }
                break;

            }
            break;
        case 8:
            printf("\nOption 8 - Value of derivative at point\n");
            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 8;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 8;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 8;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");


                    p_res = Derivative(p1);
                    printf("Derivative: \n");
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_int);
                    printf("Value of defivative at %d: \n", *(int*)a_int);
                    printf("%d\n", *(int*)a_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(a_int);
                    free(a_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 8;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 8;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 8;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative: \n");
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_int);
                    printf("Value of derivative at %d: \n", *(int*)a_int);
                    printf("%d\n", *(int*)a_res);

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(a_int);
                    free(a_res);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 8;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 8;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 8;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = Derivative(p1);
                    printf("Derivative: \n");
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_complex);
                    printf("Value of derivative at ");
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(a_complex);
                    free(a_res);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("The first polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 8;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 8;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 8;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    a_res = PolynomValue(p1, a_complex);
                    printf("Scalar mul of polynomial at ");
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);

                    free(a_complex);
                    free(a_res);
                    break;
                }
                break;

            }

            break;
        case 9:
            printf("\nOption 9 - N-order derivative\n");

            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 9;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");


                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(order);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(order);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 9;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(order);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(coefficients_1);
                    free(order);

                    break;
                }
                break;

            }
            break;
        case 10:
            printf("\nOption 10 - Value of n-order derivative at point\n");
            cmd_type = dialog(MSGS_TYPE, MSGS_TYPE_SIZE, mode);
            switch (cmd_type) {
            case 0:
                printf("Goodbye! :)");
                cmd = 0;
                break;
            case 1:
                break;
            case 2:
                printf("\nOption 2 - Integer\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 9;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateRandomInt(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");


                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_int);
                    printf("Value of Ndefivative (%d) at %d: \n", *order, *(int*)a_int);
                    printf("%d\n", *(int*)a_res);


                    Destructor(p1);
                    Destructor(p_res);

                    free(order);
                    free(a_res);
                    free(a_int);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    coefficients_1 = read_polynom_int(degree_1);
                    if (!coefficients_1) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    a_int = read_int("Enter one integer number: ");
                    if (!a_int) {
                        mode = 8;
                        break;
                    }

                    p1 = CreateFromValuesInt(degree_1, coefficients_1);

                    printf("Polynomials: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_int);
                    printf("Value of Ndefivative (%d) at %d: \n", *order, *(int*)a_int);
                    printf("%d\n", *(int*)a_res);


                    Destructor(p1);
                    Destructor(p_res);


                    free(coefficients_1);
                    free(order);
                    free(a_res);
                    free(a_int);

                    break;
                }
                break;
            case 3:
                printf("\nOption 3 - Complex\n");
                cmd_input = dialog(MSGS_INPUT, MSGS_INPUT_SIZE, mode);
                switch (cmd_input) {
                case 0:
                    printf("Goodbye! :)");
                    cmd = 0;
                    break;

                case 1:
                    mode = 9;
                    break;

                case 2:
                    printf("\nOption 2 - Generation\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateRandomComplex(degree_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_complex);
                    printf("Value of Ndefivative (%d) at ", *order);
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(order);
                    free(a_res);
                    free(a_complex);

                    break;

                case 3:
                    printf("\nOption 3 - Keyboard input\n");

                    printf("Polynomial: \n");
                    mode = read_degree(&degree_1);
                    if (mode != 0) {
                        mode = 9;
                        break;
                    }

                    coefficients_1 = read_polynom_complex(degree_1);
                    if (!coefficients_1) {
                        mode = 9;
                        break;
                    }

                    order = read_unsigned_int("Enter order of dreivative: ");
                    if (!order) {
                        mode = 9;
                        break;
                    }

                    a_complex = read_complex("Enter complex number: \n");
                    if (!a_complex) {
                        mode = 9;
                        break;
                    }

                    p1 = CreateFromValuesComplex(degree_1, coefficients_1);

                    printf("Generated: \n");
                    ShowPolynom(p1);
                    printf("\n");

                    p_res = NDerivative(p1, *order);
                    printf("NDerivative (%d) of polynomial: \n", *order);
                    ShowPolynom(p_res);
                    printf("\n");

                    a_res = PolynomValue(p_res, a_complex);
                    printf("Value of Ndefivative (%d) at ", *order);
                    show_complex(a_complex);
                    printf(": \n");
                    show_complex(a_res);
                    printf("\n");

                    Destructor(p1);
                    Destructor(p_res);

                    free(order);
                    free(a_res);
                    free(a_complex);
                    free(coefficients_1);

                    break;
                }
                break;

            }
            break;
        }
    } while (cmd != 0);
    return 0;
}
