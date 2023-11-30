#include "Type.h"

void Print(Matrix *a)
{
    for (int i = 0; i < a->rows; i++)
    {
        printf("%d: ", i + 1);
        double tmp = Get(a, i, 0);
        if (tmp >= 0)
        {
            printf(" \033[94m%lf\033[39m * \033[95mx[1]\033[39m ", tmp);
        }
        else
        {
            printf("-\033[94m%lf\033[39m * \033[95mx[1]\033[39m ", -tmp);
        }
        for (int j = 1; j < a->columns - 1; j++)
        {
            tmp = Get(a, i, j);
            if (tmp >= 0)
            {
                printf("+ \033[94m%lf\033[39m * \033[95mx[%d]\033[39m ", tmp, j + 1);
            }
            else
            {
                printf("- \033[94m%lf\033[39m * \033[95mx[%d]\033[39m ", -tmp, j + 1);
            }
        }
        tmp = Get(a, i, a->columns - 1);
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