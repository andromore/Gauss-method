#include "Matrix.h"

// Однопроходный метод Гаусса
void GaussMethod1(Matrix *x)
{
    double tmp1, tmp2;
    for (int a = 0; a < x->rows; a++)
    {
        for (int b = 0; b < x->columns - 1; b++)
        {
            tmp1 = Get(x, a, b);
            if (!equal(tmp1, 0))
            {
                for (int c = 0; c < x->rows; c++)
                {
                    if (c == a)
                    {
                        continue;
                    }
                    tmp2 = Get(x, c, b);
                    if (!equal(tmp2, 0))
                    {
                        AddRow1MultipliedByNumberToRow2(x, a, c, -tmp2 / tmp1);
                    }
                }
                break;
            }
        }
    }
}

// Двухпроходный метод Гаусса
void GaussMethod2(Matrix *x)
{
    double tmp1, tmp2;
    int last = 0;

    // Треугольный вид
    for (int a = 0; a < x->rows - 1; a++)
    {
        for (int b = last; b < x->columns - 1; b++)
        {
            last = b;
            tmp1 = Get(x, a, b);
            if (!equal(tmp1, 0))
            {
                for (int c = a + 1; c < x->rows; c++)
                {
                    tmp2 = Get(x, c, b);
                    if (!equal(tmp2, 0))
                    {
                        AddRow1MultipliedByNumberToRow2(x, a, c, -tmp2 / tmp1);
                    }
                }
                break;
            }
        }
    }

    // Диагональный вид
    for (int a = x->rows - 1; a > 0; a--)
    {
        for (int b = 0; b < x->columns - 1; b++)
        {
            tmp1 = Get(x, a, b);
            if (!equal(tmp1, 0))
            {
                for (int c = a - 1; c >= 0; c--)
                {
                    AddRow1MultipliedByNumberToRow2(x, a, c, -Get(x, c, b) / tmp1);
                }
                break;
            }
        }
    }
}