#include "Base.h"

double Get(Matrix *a, int row, int column)
{
    return a->pointer[a->columns * row + column];
}

void Set(Matrix *a, int row, int column, double value)
{
    a->pointer[a->columns * row + column] = value;
}

Matrix New(int rows, int columns)
{
    Matrix result;
    result.pointer = (double *) malloc(rows * columns * sizeof(double));
    if (result.pointer != NULL)
    {
        result.rows = rows;
        result.columns = columns;
    }
    return result;
}

Matrix Copy(Matrix *a)
{
    Matrix result = New(a->rows, a->columns);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->columns; j++)
        {
            Set(&result, i, j, Get(a, i, j));
        }
    }
    return result;
}

void Print(Matrix *a)
{
    for (int i = 0; i < a->rows; i++)
    {
        printf("%d: ", i + 1);
        for (int j = 0; j < a->columns - 1; j++)
        {
            printf("(%lf) * x[%d] + ", Get(a, i, j), j + 1);
        }
        printf("(%lf) = 0\n", Get(a, i, a -> columns - 1));
    }
}

Matrix Sum(Matrix *a, Matrix *b)
{
    assert((a->rows == b->rows) || (a->columns == b->columns));
    Matrix result = New(a->rows, a->columns);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->columns; j++)
        {
            Set(&result, i, j, Get(a, i, j) + Get(b, i, j));
        }
    }
    return result;
}

Matrix Transporent(Matrix *a)
{
    Matrix result = New(a->columns, a->rows);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->columns; j++)
        {
            Set(&result, j, i, Get(a, i, j));
        }
    }
    return result;
}

void ComposeRowToNumber(Matrix *a, int index, double number)
{
    for (int i = 0; i < a->columns; i++)
    {
        Set(a, index, i, Get(a, index, i) * number);
    }
}

void AddRowToRowByNumber(Matrix *a, int index1, int index2, double number)
{
    for (int i = 0; i < a->columns; i++)
    {
        Set(a, index2, i, Get(a, index2, i) + Get(a, index1, i) * number);
    }
}

Matrix ComposeToNumber(Matrix *a, double number)
{
    Matrix result = New(a->rows, a->columns);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->columns; j++)
        {
            Set(&result, i, j, Get(&result, i, j) * number);
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

void SwapTwoColumns(Matrix *a, int column1, int column2)
{
    assert((column1 >= 0) && (column2 >= 0) && (column1 < a->columns) && (column2 < a->columns));
    double tmp;
    for (int i = 0; i < a->rows; i++)
    {
        tmp = Get(a, i, column1);
        Set(a, i, column1, Get(a, i, column2));
        Set(a, i, column2, tmp);
    }
}