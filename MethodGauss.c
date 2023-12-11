#include "Matrix.h"

void GaussMethod(Matrix *x)
{
    // Треугольный вид
    for (int i = 0; i < x->rows; i++)
    {
        for (int j = 0; j < x->columns - 1; j++)
        {
            if (!equal(Get(x, i, j), 0))
            {
                double tmp;
                double non_zero_element_of_start_row = Get(x, i, j);
                for (int row = i + 1; row < x->rows; row++)
                {
                    tmp = Get(x, row, j);
                    if (!equal(tmp, 0))
                    {
                        AddRow1MultipliedByNumberToRow2(x, i, row, -tmp / non_zero_element_of_start_row);
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