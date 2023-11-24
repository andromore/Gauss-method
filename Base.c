#include "Type.h"

int equal(double a, double b, double c)
{
    if ((a - c < b) && (b < a + c))
    {
        return 1;
    }
    return 0;
}