#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Matrix.hpp"
#include <cstring>

/* Matrix */

Matrix::Matrix(int rows, int columns)
{
    assert((0 < rows < 256) and (0 < columns < 256));
    this->pointer = (double *)malloc(rows * columns * sizeof(double));
    this->rows = rows;
    this->columns = columns;
}

Matrix::Matrix(const Matrix &matrix)
{
    this->rows = matrix.rows;
    this->columns = matrix.columns;
    this->pointer = (double *)malloc(matrix.rows * matrix.columns * sizeof(double));
    memcpy(this->pointer, matrix.pointer, matrix.rows * matrix.columns * sizeof(double));
}

Matrix::~Matrix(void)
{
    free(this->pointer);
    this->pointer = nullptr;
    this->rows = 0;
    this->columns = 0;
}

int Matrix::get_rows(void) const
{
    return this->rows;
}

int Matrix::get_columns(void) const
{
    return this->columns;
}

double Matrix::get_element(int row, int column) const
{
    return this->pointer[this->columns * row + column];
}

void Matrix::set_element(int row, int column, double value)
{
    this->pointer[this->columns * row + column] = value;
}

void Matrix::set_row(int row, double value)
{
    for (int column = 0; column < this->columns; column++)
    {
        this->set_element(row, column, value);
    }
}

void Matrix::set_column(int column, double value)
{
    for (int row = 0; row < this->rows; row++)
    {
        this->set_element(row, column, value);
    }
}

void Matrix::set_all(double value)
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int column = 0; column < this->columns; column++)
        {
            this->set_element(row, column, value);
        }
    }
}

void Matrix::print_matrix(void) const
{
    double tmp;
    for (int row = 0; row < this->rows; row++)
    {
        tmp = this->get_element(row, 0);
        if (tmp >= 0)
        {
            printf(" %lf, ", tmp);
        }
        else
        {
            printf("-%lf, ", -tmp);
        }
        for (int column = 1; column < this->columns - 1; column++)
        {
            tmp = this->get_element(row, column);
            if (tmp >= 0)
            {
                printf(" %lf, ", tmp);
            }
            else
            {
                printf("-%lf, ", -tmp);
            }
        }
        tmp = this->get_element(row, this->columns - 1);
        if (tmp >= 0)
        {
            printf(" %lf\n", tmp);
        }
        else
        {
            printf("-%lf\n", -tmp);
        }
    }
}

void Matrix::transparent_matrix(void)
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int column = row + 1; column < this->columns; column++)
        {
            this->swap_elements(row, column, column, row);
        }
    }
}

void Matrix::swap_elements(int row1, int column1, int row2, int column2)
{
    double tmp = this->get_element(row1, column1);
    this->set_element(row1, column1, this->get_element(row2, column2));
    this->set_element(row2, column2, tmp);
}

void Matrix::swap_rows(int row1, int row2)
{
    double tmp;
    for (int column = 0; column < this->columns; column++)
    {
        tmp = this->get_element(row1, column);
        this->set_element(row1, column, this->get_element(row2, column));
        this->set_element(row2, column, tmp);
    }
}

void Matrix::swap_columns(int column1, int column2)
{
    double tmp;
    for (int row = 0; row < this->rows; row++)
    {
        tmp = this->get_element(row, column1);
        this->set_element(row, column1, this->get_element(row, column2));
        this->set_element(row, column2, tmp);
    }
}

void Matrix::multiply_row(int row, double multiplier)
{
    for (int column = 0; column < this->columns; column++)
    {
        this->set_element(row, column, this->get_element(row, column) * multiplier);
    }
}

void Matrix::multiply_column(int column, double multiplier)
{
    for (int row = 0; row < this->rows; row++)
    {
        this->set_element(row, column, this->get_element(row, column) * multiplier);
    }
}

void Matrix::multiply_matrix(double multiplier)
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int column = 0; column < this->columns; column++)
        {
            this->set_element(row, column, this->get_element(row, column) * multiplier);
        }
    }
}

void Matrix::add_row_to_row(int row1, int row2)
{
    this->add_row_to_row(row1, row2, 1.0);
}

void Matrix::add_row_to_row(int row1, int row2, double multiplier)
{
    for (int column = 0; column < this->columns; column++)
    {
        this->set_element(row2, column, this->get_element(row2, column) + this->get_element(row1, column) * multiplier);
    }
}

void Matrix::add_column_to_column(int column1, int column2)
{
    this->add_column_to_column(column1, column2, 1.0);
}

void Matrix::add_column_to_column(int column1, int column2, double multiplier)
{
    for (int row = 0; row < this->rows; row++)
    {
        this->set_element(row, column2, this->get_element(row, column2) + this->get_element(row, column1) * multiplier);
    }
}

void Matrix::add_matrix(const Matrix &summand)
{
    assert((this->rows == summand.rows) and (this->columns == summand.columns));
    for (int row = 0; row < this->rows; row++)
    {
        for (int column = 0; column < this->columns; column++)
        {
            this->set_element(row, column, this->get_element(row, column) + summand.get_element(row, column));
        }
    }
}

int main()
{
    Matrix a = Matrix(2, 2);
    a.set_element(0, 0, 1);
    a.set_element(1, 1, 1);
    a.set_element(1, 0, 0);
    a.set_element(0, 1, 0);
    a.add_row_to_row(0, 1);
    // a.print_matrix();
    /* Matrix b = Matrix(2, 2);
    b.set_element(0, 0, 2);
    b.set_element(1, 1, 3);
    b.set_element(1, 0, -2);
    b.set_element(0, 1, -1); */
    // b.print_matrix();
    // b.transparent_matrix();
    // b.print_matrix();
    a.print_matrix();
    return 0;
}