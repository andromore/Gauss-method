#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INACCURACY pow(10, -10)

int equal(double a, double b)
{
    if ((a - INACCURACY < b) && (b < a + INACCURACY))
    {
        return 1;
    }
    return 0;
}