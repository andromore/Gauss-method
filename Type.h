#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define elif else if
typedef struct
{
    double *pointer;
    unsigned char rows;
    unsigned char columns;
} Matrix;