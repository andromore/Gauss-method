#include "MethodGauss.h"
#include <time.h>

// Режим сборки: INPUT = 0 (Ручной ввод) | RANDOM = 1 (Генерация коэффициентов) | GENERATION 2 (Генерация неизвестных)
#define MODE 0

// Получение случайного значения
#define RANDOM (double) (rand() / RAND_MAX) + 1 // + 1 Чтобы точно не было 0

int main()
{
    int i, j, n, m;
    double tmp;
#if (MODE == 0) || (MODE == 1)
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
#elif MODE == 2 // В режиме 2 нет параметров
    printf("\033[92mEnter rank of expanded matrix:\033[39m ");
    if (scanf("%d", &n) == 0)
    {
        printf("%s", "\033[91mI'm sorry, but I don't understand you. (Your input is incorrect)\n\033[39m");
        return 0;
    }
    m = n;
#else
#error
#endif
    if ((1 < n) && (n < 255) && (1 < m) && (m < 256))
    {
        Matrix a = New(m, n + 1);
        
        // Заполнение системы
#if MODE == 0 // INPUT
        printf("\033[92mGeneral view of the system of equations:\033[39m\n\033[94m1\033[39m: a[1][1] * \033[95mx[1]\033[39m + a[1][2] * \033[95mx[2]\033[39m + ... + a[1][n] * \033[95mx[n]\033[39m + b[1] = 0\n\033[94m2\033[39m: a[2][1] * \033[95mx[1]\033[39m + a[2][2] * \033[95mx[2]\033[39m + ... + a[2][n] * \033[95mx[n]\033[39m + b[2] = 0\n   ...\n\033[94mm\033[39m: a[m][1] * \033[95mx[1]\033[39m + a[m][2] * \033[95mx[2]\033[39m + ... + a[m][n] * \033[95mx[n]\033[39m + b[m] = 0\n\033[92mEnter the elements of augmented matrix:\033[39m\n");
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
#elif MODE == 1 // RANDOM
        srand(time(NULL));
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n + 1; j++)
            {
                a.pointer[i * (n + 1) + j] = RANDOM;
            }
        }
        printf("\033[92mGenerated system of equations:\033[39m\n");
        Print(&a);
#elif MODE == 2 // GENERATION
        srand(time(NULL));
        double z[n]; // Сгенерированные значения неизвестных
        printf("\033[92mGenerated solution:\033[39m\n");
        for (i = 0; i < n; i++) // Генерация значений неизвестных
        {
            tmp = RANDOM;
            z[i] = tmp;
            printf("x[%d] = %lf\n", i + 1, tmp);
        }
        for (i = 0; i < m; i++) // Генерация коэффициентов и свободных членов
        {
            double b = 0;
            for (j = 0; j < n; j++)
            {
                a.pointer[i * (n + 1) + j] = RANDOM;
                b += a.pointer[i * (n + 1) + j] * z[j];
            }
            Set(&a, i, n, -b);
        }
        printf("\033[92mGenerated system of equations:\033[39m\n");
        Print(&a);
        double q[n]; // Вычисленные значения неизвестных
#else
#error
#endif
        Matrix x = GaussMethod(&a); // Решение системы
        Free(&a); // Система больше не нужна

        // Вывод результата
        int y[x.columns - 1]; // Список распечатанных элементов: -1 - нет, 0 - главная, 1 - параметр.
        for (i = 0; i < x.columns; i++)
        {
            y[i] = -1;
        }
        
        // Приведение диагонали к единичному виду
        for (i = 0; i < x.rows; i++)
        {
            int a = -1;
            for (j = 0; j < x.columns; j++)
            {
                if (!equali(Get(&x, i, j), 0))
                {
                    a = j;
                    break;
                }
            }
            ComposeRowToNumber(&x, i, 1 / Get(&x, i, a));
        }
        
        // Проверка на наличие решений
        for (i = x.rows - 1; i >= 0; i--)
        {
            int a = -1;
            for (j = 0; j < x.columns - 1; j++)
            {
                if (!equali(Get(&x, i, j), 0))
                {
                    a = j;
                    break;
                }
            }
            if ((a == -1) && (!equali(Get(&x, i, x.columns - 1), 0))) // 0 * (x[1] + x[2] + ...) = b
            {
                printf("This system has no solution\n");
                return 0;
            }
        }
        
        // Главные переменные
        printf("\033[92mSolution is:\033[39m\n");
        for (i = 0; i < x.rows; i++)
        {
            int a = -1;
            for (j = 0; j < x.columns - 1; j++) // Поиск главной переменной в строке
            {
                if (!equali(Get(&x, i, j), 0)) // Главная переменная обнаружена
                {
                    a = j;
                    y[j] = 0;
                    break;
                }
            }
            if (a != -1) // Значения главных переменных
            {
                printf("\033[95mx[%d]\033[39m = ", a + 1);
                printf("(%lf)", - Get(&x, i, x.columns - 1));
#if (MODE == 0) || (MODE == 1) // В режиме 2 не может быть параметров
                for (j = a + 1; j < x.columns - 1; j++)
                {
                    if (!equali(Get(&x, i, j), 0)) // Параметр обнаружен
                    {
                        printf(" + (%lf) * \033[95mx[%d]\033[39m", - Get(&x, i, j), j + 1);
                        y[j] = 1;
                    }
                }
#elif MODE == 2
                q[i] = - Get(&x, i, x.columns - 1) - z[i];
#else
#error
#endif
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
            printf("no variables");
        }
        printf("\n");
#if MODE == 2 // Подсчёт среднего квадратичного отклонения
        double r = 0;
        for (i = 0; i < n; i++)
        {
            r += pow(q[i], 2);
        }
        printf("\033[92mThe average quadratic error of calculations:\033[39m %le\n", pow(r, 0.5));
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