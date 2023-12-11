#include <math.h>

#define INACCURACY pow(10, -10) // Ошибка

// Сравнение double с учётом ошибки
int equal(double a, double b)
{
    if ((a - INACCURACY < b) && (b < a + INACCURACY))
    {
        return 1;
    }
    return 0;
}