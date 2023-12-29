#include "stdio.h"
#include "stdlib.h"
#include "math.h"

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

typedef struct
{
    double *pointer;
    int rows;
    int columns;
} Matrix;

// Создать новую матрицу
Matrix New(int rows, int columns)
{
    Matrix result;
    result.pointer = (double *)malloc(rows * columns * sizeof(double));
    if (result.pointer != NULL)
    {
        result.rows = rows;
        result.columns = columns;
    }
    return result;
}

// Получить элемент матрицы
double Get(Matrix *matrix, int row, int column)
{
    return matrix->pointer[matrix->columns * row + column];
}

// Установить элемент матрицы
void Set(Matrix *matrix, int row, int column, double value)
{
    matrix->pointer[matrix->columns * row + column] = value;
}

// Копировать матрицу
Matrix Copy(Matrix *matrix)
{
    Matrix result = New(matrix->rows, matrix->columns);
    for (int row = 0; row < matrix->rows; row++)
    {
        for (int column = 0; column < matrix->columns; column++)
        {
            Set(&result, row, column, Get(matrix, row, column));
        }
    }
    return result;
}

// Напечатать содержимое матрицы
void Print(Matrix *matrix)
{
    double tmp;
    for (int row = 0; row < matrix->rows; row++)
    {
        printf("%d: ", row + 1);
        tmp = Get(matrix, row, 0);
        if (tmp >= 0)
        {
            printf(" \033[94m%lf\033[39m * \033[95mx[1]\033[39m ", tmp);
        }
        else
        {
            printf("-\033[94m%lf\033[39m * \033[95mx[1]\033[39m ", -tmp);
        }
        for (int column = 1; column < matrix->columns - 1; column++)
        {
            tmp = Get(matrix, row, column);
            if (tmp >= 0)
            {
                printf("+ \033[94m%lf\033[39m * \033[95mx[%d]\033[39m ", tmp, column + 1);
            }
            else
            {
                printf("- \033[94m%lf\033[39m * \033[95mx[%d]\033[39m ", -tmp, column + 1);
            }
        }
        tmp = Get(matrix, row, matrix->columns - 1);
        if (tmp >= 0)
        {
            printf("=  \033[94m%lf\033[39m\n", tmp);
        }
        else
        {
            printf("= -\033[94m%lf\033[39m\n", -tmp);
        }
    }
}

// Умножить ряд на число
void ComposeRowToNumber(Matrix *matrix, int row, double multiplier)
{
    for (int column = 0; column < matrix->columns; column++)
    {
        Set(matrix, row, column, Get(matrix, row, column) * multiplier);
    }
}

// Прибавить к одном ряду другой,умноженный на некоторое число
void AddRow1MultipliedByNumberToRow2(Matrix *a, int row1, int row2, double multiplier)
{
    for (int column = 0; column < a->columns; column++)
    {
        Set(a, row2, column, Get(a, row2, column) + Get(a, row1, column) * multiplier);
    }
}

// Освободить память
void Free(Matrix *a)
{
    free(a->pointer); // Непосредственно освобождение памяти
    // Правила хорошего тона для людей без дыр в ногах
    a->pointer = NULL;
    a->rows = 0;
    a->columns = 0;
}

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

int main()
{
    int i, j, variables, equations;
    double tmp;
    
    // Общий вид матрицы системы
    printf("\033[92mGeneral view of the system of equations:\033[39m\n");
    printf("1: \033[93ma[1][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[1][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[1][n]\033[39m * \033[95mx[n]\033[39m = \033[93mb[1]\033[39m\n");
    printf("2: \033[93ma[2][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[2][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[2][n]\033[39m * \033[95mx[n]\033[39m = \033[93mb[2]\033[39m\n");
    printf("   ...\n");
    printf("m: \033[93ma[m][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[m][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[m][n]\033[39m * \033[95mx[n]\033[39m = \033[93mb[m]\033[39m\n");
    printf("\033[92mEnter the elements of augmented matrix:\033[39m\n");

    // Вводим количество уравнений и количество неизвестных
    printf("\033[92mEnter number of variables:\033[39m ");
    if (scanf("%d", &variables) == 0)
    {
        printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
        return 0;
    }
    printf("\033[92mEnter number of equations:\033[39m ");
    if (scanf("%d", &equations) == 0)
    {
        printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
        return 0;
    }
    if ((variables > 254) || (equations > 255))
    {
        printf("%s", "\033[91mO, I'm sorry, but it's too long for me...\033[39m\n");
        return 0;
    }
    else if ((variables == 1) || (equations == 1))
    {
        printf("%s", "\033[91mDo I really have to decide this?\033[39m\n");
        return 0;
    }
    else if ((variables < 1) || (equations < 1))
    {
        printf("%s", "\033[91mIt's a good joke, but no...\033[39m\n");
        return 0;
    }

    Matrix x = New(equations, variables + 1);

    // Вводим элементы матрицы
    for (i = 0; i < equations; i++)
    {
        for (j = 0; j < variables + 1; j++)
        {
            if (j != variables)
            {
                printf("\033[93ma[%d][%d]:\033[39m ", i + 1, j + 1);
            }
            else
            {
                printf("\033[93mb[%d]:\033[39m ", i + 1);
            }
            if (scanf("%lf", &x.pointer[i * (variables + 1) + j]) == 0)
            {
                printf("%sI'm sorry, but I don't understand you. (Your input is incorrect)%s\n", "\033[91m", "\033[39m");
                return 0;
            }
        }
    }

    // Печатаем вид введённой системы
    printf("%sThe entered system of equations:%s\n", "\033[92m", "\033[39m");
    Print(&x);

    // Решаем систему
    GaussMethod1(&x); // Применение метода Гаусса

    // Для типов переменных
    int* y = (int*) malloc((x.columns - 1) * sizeof(int));
    // Список распечатанных элементов:
    // -1 - переменная, от значения которой ничего не зависит
    // 0 - главная переменная
    // 1 - параметр

    // Поиск переменных, от которых ничего не зависит
    for (int column = 0; column < x.columns; column++)
    {
        tmp = 1;
        for (int row = 0;row < x.rows; row++)
        {
            if (!equal(Get(&x, row, column), 0))
            {
                tmp = 0;
            }
        }
        if (tmp == 1)
        {
            y[column] = -1;
        }
    }

    // Приведение диагонали к единичному виду
    for (i = 0; i < x.rows; i++)
    {
        for (j = 0; j < x.columns; j++)
        {
            if (!equal(Get(&x, i, j), 0))
            {
                ComposeRowToNumber(&x, i, 1 / Get(&x, i, j));
                break;
            }
        }
        
    }

    // Поиск решений
    printf("%sSolution is:%s\n", "\033[92m", "\033[39m");

    // Проверка на наличие решений
    for (i = x.rows - 1; i >= 0; i--)
    {
        tmp = -1;
        for (j = 0; j < x.columns - 1; j++)
        {
            if (!equal(Get(&x, i, j), 0))
            {
                tmp = j;
                break;
            }
        }
        if ((tmp == -1) && (!equal(Get(&x, i, x.columns - 1), 0))) // 0 * (x[1] + x[2] + ...) = b
        {
            printf("%sThis system has no solution%s\n", "\033[91m", "\033[39m");
            return 0;
        }
    }

    // Главные переменные
    for (i = 0; i < x.rows; i++)
    {
        int a = -1;
        for (j = 0; j < x.columns - 1; j++) // Поиск главной переменной в строке
        {
            if (!equal(Get(&x, i, j), 0)) // Главная переменная обнаружена
            {
                a = j;
                y[j] = 0;
                break;
            }
        }
        if (a != -1) // Значения главных переменных
        {
            printf("%sx[%d]%s = ", "\033[95m", a + 1, "\033[39m");

            // Число
            tmp = Get(&x, i, x.columns - 1);
            if (tmp > 0)
            {
                printf(" %s%lf%s", "\033[94m", tmp, "\033[39m");
            }
            else
            {
                printf("-%s%lf%s", "\033[94m", -tmp, "\033[39m");
            }

            // Параметры, если есть
            for (j = a + 1; j < x.columns - 1; j++)
            {
                tmp = Get(&x, i, j);
                if (!equal(tmp, 0)) // Параметр обнаружен
                {
                    if (tmp > 0)
                    {
                        printf(" - %s%lf%s * %sx[%d]%s", "\033[94m", tmp, "\033[39m", "\033[95m", j + 1, "\033[39m");
                    }
                    else
                    {
                        printf(" + %s%lf%s * %sx[%d]%s", "\033[94m", -tmp, "\033[39m", "\033[95m", j + 1, "\033[39m");
                    }
                    y[j] = 1;
                }
            }
            printf("\n");
        }
    }

    // Переменные, от значения которых ничего не зависит
    j = 0;
    printf("%sThis variables can have any values:%s ", "\033[92m", "\033[39m");
    for (i = 0; i < x.columns - 1; i++)
    {
        if ((y[i] == -1) && (j == 0))
        {
            printf("%sx[%d]%s", "\033[95m", i + 1, "\033[39m");
            j++;
        }
        else if (y[i] == -1)
        {
            printf(", %sx[%d]%s", "\033[95m", i + 1, "\033[39m");
        }
    }
    if (j == 0)
    {
        printf("%sno variables%s", "\033[95m", "\033[39m");
    }
    printf("\n");

    // Параметры
    j = 0;
    printf("%sThis variables are parameters:%s ", "\033[92m", "\033[39m");
    for (i = 0; i < x.columns - 1; i++)
    {
        if ((y[i] == 1) && (j == 0))
        {
            printf("%sx[%d]%s", "\033[95m", i + 1, "\033[39m");
            j++;
        }
        else if (y[i] == 1)
        {
            printf(", %sx[%d]%s", "\033[95m", i + 1, "\033[39m");
        }
    }
    if (j == 0)
    {
        printf("%sno variables%s", "\033[95m", "\033[39m");
    }
    printf("\n");

    Free(&x); // Матрица больше не нужна
    return 0;
}