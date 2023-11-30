#include "Base.h"
#include "Type.h"

void Print(Matrix *);
void Set(Matrix *, int, int, double);
void ComposeRowToNumber(Matrix *, int, double);
void AddRow1MultipliedByNumberToRow2(Matrix *, int, int, double);
void Free(Matrix *);
void SwapTwoRows(Matrix *, int, int);
double Get(Matrix *, int, int);
Matrix New(int, int);
Matrix Copy(Matrix *);
Matrix Sum(Matrix *, Matrix *);
Matrix Transparent(Matrix *);
Matrix ComposeToNumber(Matrix *, double);
Matrix Composition(Matrix *, Matrix *);