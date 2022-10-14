#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <errno.h>
#include "solver.h"

#define TEST true

struct test_data
{
    float data[3];
    float data_check[4];
    int error;
    float* x1;
    float* x2;
};

/*!
\brief тестирующая функция
\detail тестирующая функция прогоняет значения из data через kvadratka,
сравнивает с эталонными из data_check и пишет результаты тестов в консоль
*/
void test()
{
    float x1 = NAN, x2 = NAN;
    test_data test_data_array[] =
    {
        {{    1,                  4,                   -3},    {     TWO_ROOTS,    -4.6458,    0.6458},         NO_ERRORS,    &x1,    &x2},
        {{    1,                  0,                   -4},    {     TWO_ROOTS,    -2.0000,    2.0000},         NO_ERRORS,    &x1,    &x2},
        {{    0,                  0,                    0},    {INFINITE_ROOTS,          0,         0},         NO_ERRORS,    &x1,    &x2},
        {{    0,                  4,                    5},    {      ONE_ROOT,    -1.2500,         0},         NO_ERRORS,    &x1,    &x2},
        {{    0,                  0,                    5},    {       NO_ROOT,          0,         0},         NO_ERRORS,    &x1,    &x2},
        {{    2,                  3,                    7},    {       NO_ROOT,          0,         0},         NO_ERRORS,    &x1,    &x2},
        {{15246,             120536,              -645721},    {     TWO_ROOTS,   -11.5675,    3.6614},         NO_ERRORS,    &x1,    &x2},
        {{    0,            1154526,             -1125452},    {      ONE_ROOT,     0.9748,         0},         NO_ERRORS,    &x1,    &x2},
        {{    1,              -2068,              1069156},    {      ONE_ROOT,  1034.0000, 1034.0000},         NO_ERRORS,    &x1,    &x2},
        {{    1,  3.4*pow(10.0, 20),              1231031},    {   ERROR_OCCUR,          0,         0}, VARIABLE_OVERFLOW,    &x1,    &x2},
        {{    1,                 10,   -3.4*pow(10.0, 38)},    {   ERROR_OCCUR,          0,         0}, VARIABLE_OVERFLOW,    &x1,    &x2},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0},      NULL_POINTER,   NULL,    &x2},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0},      NULL_POINTER,    &x1,   NULL},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0},    EQUAL_POINTERS,    &x1,    &x1},
        {{  NAN,                  0,                    0},    {   ERROR_OCCUR,          0,         0},         NAN_INPUT,    &x1,    &x2},
        {{    0,                  0,                  NAN},    {   ERROR_OCCUR,          0,         0},         NAN_INPUT,    &x1,    &x2},
        {{    1,      pow(10.0, 19),   -0.7*pow(10.0, 38)},    {   ERROR_OCCUR,          0,         0}, VARIABLE_OVERFLOW,    &x1,    &x2}
    };

    for(int i = 0; i < (sizeof(test_data_array) / sizeof(test_data_array[0])); i++)
    {
        int number_of_roots = kvadratka(test_data_array[i].data[0],
                                        test_data_array[i].data[1],
                                        test_data_array[i].data[2],
                                        test_data_array[i].x1,
                                        test_data_array[i].x2);
        if(number_of_roots == int(test_data_array[i].data_check[0])
        && number_of_roots == ERROR_OCCUR
        && errno == test_data_array[i].error)
        {
            printf("test %i OK\n", i + 1);
            printf("ERROR %d\n", errno);
        }

        else
        {
            if(number_of_roots == int(test_data_array[i].data_check[0])
            && !floatcmp(x1, test_data_array[i].data_check[1])
            && !floatcmp(x2, test_data_array[i].data_check[2])
            && !floatcmp(float(errno), test_data_array[i].data_check[3]))
                printf("test %i OK\n", i + 1);
            else
            {
                printf("test %i FAILED\n", i + 1);
                printf("right output: %i %.4f %.4f\n", int(test_data_array[i].data_check[0]),
                       test_data_array[i].data_check[1],
                       test_data_array[i].data_check[2]);
                printf("program output: %i %.4f %.4f\n", number_of_roots, x1, x2);
            }
        }
    }
}

/*!
\detail в режиме теста запускает тестирующую функцию,
в обычном считывает коэффициенты из консоли и запускает kvadratka,
а затем печатает полученные значения
*/
int main()
{
    float a = NAN, b = NAN, c = NAN;
#if TEST
    test();
    return 0;

#else
    puts("type a b c");
    if(scanf("%f %f %f", &a, &b, &c) != 3)
    {
        puts("invalid input");
        return 0;
    }
    errno = 0;
    output(a, b, c);
#endif // TEST
}
