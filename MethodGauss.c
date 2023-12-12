#include "Matrix.h"

void AddRow1MultipliedByNumberToRow2FromStartToEnd(Matrix *a, int row1, int row2, double multiplier, int start, int end)
{
    for (int column = start; column < end; column++)
    {
        Set(a, row2, column, Get(a, row2, column) + Get(a, row1, column) * multiplier);
    }
}

void GaussMethod(Matrix *x)
{
    double tmp;
    int last = 0;
    // Треугольный вид
    for (int a = 0; a < x->rows - 1; a++)
    {
        for (int b = last; b < x->columns - 1; b++)
        {
            last = b;
            if (!equal(Get(x, a, b), 0))
            {
                double non_zero_element_of_start_row = Get(x, a, b);
                for (int c = a + 1; c < x->rows; c++)
                {
                    tmp = Get(x, c, b);
                    if (!equal(tmp, 0))
                    {
                        AddRow1MultipliedByNumberToRow2(x, a, c, -tmp / non_zero_element_of_start_row);
                    }
                }
                break;
            }
        }
    }

    // Диагональный вид
    for (int a = x->rows - 1; a > 0; a--)
    {
        int b = -1; // Есть ли ненулевые элементы
        for (int c = 0; c < x->columns - 1; c++)
        {
            if (!equal(Get(x, a, c), 0))
            {
                b = c;
                break;
            }
        }
        if (b != -1) // Вычитаем ряды с ненулевыми неизвестными
        {
            for (int c = a - 1; c >= 0; c--)
            {
                AddRow1MultipliedByNumberToRow2(x, a, c, - Get(x, c, b) / Get(x, a, b));
            }
        }
    }
}