#include "MethodGauss.h"

// #define Debug

int main()
{
    int i, j, n, m;
    double tmp;
    printf("\033[92mEnter number of variables (n):\033[39m ");
    if (scanf("%d", &n) == 0)
    {
        printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
        return 0;
    }
    printf("\033[92mEnter number of equations (m):\033[39m ");
    if (scanf("%d", &m) == 0)
    {
        printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
        return 0;
    }
    if ((1 < n) && (n < 255) && (1 < m) && (m < 256))
    {
        Matrix a = New(m, n + 1);
        
        // Заполнение системы
        printf("\033[92mGeneral view of the system of equations:\033[39m\n");
        printf("1: \033[93ma[1][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[1][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[1][n]\033[39m * \033[95mx[n]\033[39m + \033[93mb[1]\033[39m = \033[94m0\033[39m\n");
        printf("2: \033[93ma[2][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[2][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[2][n]\033[39m * \033[95mx[n]\033[39m + \033[93mb[2]\033[39m = \033[94m0\033[39m\n");
        printf("   ...\n");
        printf("m: \033[93ma[m][1]\033[39m * \033[95mx[1]\033[39m + \033[93ma[m][2]\033[39m * \033[95mx[2]\033[39m + ... + \033[93ma[m][n]\033[39m * \033[95mx[n]\033[39m + \033[93mb[m]\033[39m = \033[94m0\033[39m\n");
        printf("\033[92mEnter the elements of augmented matrix:\033[39m\n");
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n + 1; j++)
            {
                if (j != n)
                {
                    printf("\033[93ma[%d][%d]:\033[39m ", i + 1, j + 1);
                }
                else
                {
                    printf("\033[93mb[%d]:\033[39m ", i + 1);
                }
                if (scanf("%lf", &a.pointer[i * (n + 1) + j]) == 0)
                {
                    printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
                    return 0;
                }
            }
        }
        printf("\033[92mThe entered system of equations:\033[39m\n");
        Print(&a);
        Matrix x = GaussMethod(&a); // Решение системы
        Free(&a); // Система больше не нужна

        printf("\033[92mThe simplified system:\033[39m\n");
        Print(&x);

        #ifndef Debug

        // Вывод результата
        int y[x.columns - 1]; // Список распечатанных элементов: -1 - нет, 0 - главная, 1 - параметр.
        for (i = 0; i < x.columns; i++)
        {
            y[i] = -1;
        }
        
        // Приведение диагонали к единичному виду
        for (i = 0; i < x.rows; i++)
        {
            tmp = -1;
            for (j = 0; j < x.columns; j++)
            {
                if (!equal(Get(&x, i, j), 0))
                {
                    tmp = j;
                    break;
                }
            }
            ComposeRowToNumber(&x, i, 1 / Get(&x, i, tmp));
        }

        // Поиск решений
        printf("\033[92mSolution is:\033[39m\n");
        
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
                printf("\033[91mThis system has no solution\033[39m\n");
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
                printf("\033[95mx[%d]\033[39m = ", a + 1);
                tmp = - Get(&x, i, x.columns - 1);
                if (tmp > 0)
                {
                    printf(" \033[94m%lf\033[39m", tmp);
                }
                else
                {
                    printf("-\033[94m%lf\033[39m", -tmp);
                }
                for (j = a + 1; j < x.columns - 1; j++)
                {
                    tmp = Get(&x, i, j);
                    if (!equal(tmp, 0)) // Параметр обнаружен
                    {
                        if (tmp > 0)
                        {
                            printf(" + \033[94m%lf\033[39m * \033[95mx[%d]\033[39m", -tmp, j + 1);
                        }
                        else
                        {
                            printf(" - \033[94m%lf\033[39m * \033[95mx[%d]\033[39m", tmp, j + 1);
                        }
                        y[j] = 1;
                    }
                }
                printf("\n");
            }
        }
        
        // Переменные, от значения которых ничего не зависит
        j = 0;
        printf("\033[92mThis variables can have any values:\033[39m ");
        for (i = 0; i < x.columns - 1; i++)
        {
            if ((y[i] == -1) && (j == 0))
            {
                printf("\033[95mx[%d]\033[39m", i + 1);
                j++;
            }
            elif (y[i] == -1)
            {
                printf(", \033[95mx[%d]\033[39m", i + 1);
            }
        }
        if (j == 0)
        {
            printf("\033[95mno variables\033[39m");
        }
        
        // Параметры
        j = 0;
        printf("\n\033[92mThis variables are parameters:\033[39m ");
        for (i = 0; i < x.columns - 1; i++)
        {
            if ((y[i] == 1) && (j == 0))
            {
                printf("\033[95mx[%d]\033[39m", i + 1);
                j++;
            }
            elif (y[i] == 1)
            {
                printf(", \033[95mx[%d]\033[39m", i + 1);
            }
        }
        if (j == 0)
        {
            printf("\033[95mno variables\033[39m");
        }
        printf("\n");

        #endif

        Free(&x); // Матрица решений больше не нужна
    }
    elif ((n > 255) || (m > 255))
    {
        printf("%s", "\033[91mO, I'm sorry, but it's too long for me...\033[39m\n");
    }
    elif ((n == 1) || (m == 1))
    {
        printf("%s", "\033[91mDo I really have to decide this?\033[39m\n");
    }
    else
    {
        printf("%s", "\033[91mIt's a good joke, but no...\033[39m\n");
    }
    return 0;
}