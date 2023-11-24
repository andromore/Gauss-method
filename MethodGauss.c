#include "Matrix.h"

Matrix GaussMethod(Matrix *y)
{
    Matrix x = Copy(y);

    // Треугольный вид
    int k = 0; // Количество отсортированных неизвестных
    for (int a = 0; a < x.rows; a++)
    {
        int swaps = 0;
        for (int b = a; b < x.rows; b++) // Локальная сортировка - отсеивание рядов с одной и той же первой неизвестной
        {
            if (!equali(Get(&x, b, k), 0))
            {
                SwapTwoRows(&x, a + swaps, b);
                swaps++;
            }
        }
        if (swaps > 1) // Требуется создать локальный треугольный вид
        {
            for (int b = a + 1; b < a + swaps; b++)
            {
                AddRowToRowByNumber(&x, a, b,  - Get(&x, b, k) / Get(&x, a, k));
            }
        }
        if (swaps == 0) // Ступенька съехала вправо - сортируемая неизвестная принимает любое значение
        {
            a--;
        }
        k++;
    }

    // Диагональный вид
    for (int a = x.rows - 1; a > 0; a--)
    {
        int b = -1; // Есть ли ненулевые элементы
        for (int c = 0; c < x.columns - 1; c++)
        {
            if (!equali(Get(&x, a, c), 0))
            {
                b = c;
                break;
            }
        }
        if (b != -1) // Вычитаем ряды с ненулевыми неизвестными
        {
            for (int c = a - 1; c >= 0; c--)
            {
                AddRowToRowByNumber(&x, a, c, - Get(&x, c, b) / Get(&x, a, b));
            }
        }
    }

    printf("\033[92mThe simpled system:\033[39m\n");
    Print(&x);
    return x;
}