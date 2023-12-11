#include "elif.h"
#include "Base.h"
#include "Type.h"

double Get(Matrix *matrix, int row, int column)
{
    return matrix->pointer[matrix->columns * row + column];
}

void Set(Matrix *matrix, int row, int column, double value)
{
    matrix->pointer[matrix->columns * row + column] = value;
}

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
            printf("+ \033[94m%lf\033[39m = \033[94m0\033[39m\n", tmp);
        }
        else
        {
            printf("- \033[94m%lf\033[39m = \033[94m0\033[39m\n", -tmp);
        }
    }
}

void ComposeRowToNumber(Matrix *matrix, int row, double multiplier)
{
    for (int column = 0; column < matrix->columns; column++)
    {
        Set(matrix, row, column, Get(matrix, row, column) * multiplier);
    }
}

void AddRow1MultipliedByNumberToRow2(Matrix *a, int row1, int row2, double multiplier)
{
    for (int column = 0; column < a->columns; column++)
    {
        Set(a, row2, column, Get(a, row2, column) + Get(a, row1, column) * multiplier);
    }
}

Matrix ComposeToNumber(Matrix *a, double multiplier)
{
    Matrix result = New(a->rows, a->columns);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->columns; j++)
        {
            Set(&result, i, j, Get(&result, i, j) * multiplier);
        }
    }
    return result;
}

Matrix Composition(Matrix *a, Matrix *b)
{
    assert(a->columns == b->rows);
    Matrix result = New(a->rows, b->columns);
    double sum;
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->columns; j++)
        {
            sum = 0;
            for (int k = 0; k < a->columns; k++)
            {
                sum += Get(a, i, k) * Get(b, k, j);
            }
            Set(&result, i, j, sum);
        }
    }
    return result;
}

void Free(Matrix *a)
{
    free(a->pointer);
    a->pointer = NULL;
    a->rows = 0;
    a->columns = 0;
}

void SwapTwoRows(Matrix *a, int row1, int row2)
{
    assert((row1 >= 0) && (row2 >= 0) && (row1 < a->rows) && (row2 < a->rows));
    double tmp;
    for (int i = 0; i < a->columns; i++)
    {
        tmp = Get(a, row1, i);
        Set(a, row1, i, Get(a, row2, i));
        Set(a, row2, i, tmp);
    }
}