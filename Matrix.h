#include "Base.h"
double Get(Matrix *, int, int);
Matrix New(int, int);
Matrix Copy(Matrix *);
void Print(Matrix *);
void Set(Matrix *, int, int, double);
Matrix Sum(Matrix *, Matrix *);
Matrix Transporent(Matrix *);
void ComposeRowToNumber(Matrix *, int, double);
void AddRowToRowByNumber(Matrix *, int, int, double);
Matrix ComposeToNumber(Matrix *, double);
Matrix Composition(Matrix *, Matrix *);
void Free(Matrix *);
void SwapTwoRows(Matrix *, int, int);
void SwapTwoCulumns(Matrix *, int, int);