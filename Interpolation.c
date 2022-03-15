#include <stdio.h>
#define RFACTOR (1.24733)

// 4 1 1 1 2 1.4142 3 1.7321 4 2 2.56

void comb_sort(double* x, double* y, int size)
{
    int gap = size;
    int swaps = 1;
    int i, j;

    while (gap > 1 || swaps)
    {
        gap = (int)(gap / RFACTOR);
        if (gap < 1)
            gap = 1;
        swaps = 0;
        for (i = 0; i < size - gap; ++i)
        {
            j = i + gap;
            if (x[i] > x[j])
            {
                double tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
                tmp = y[i];
                y[i] = y[j];
                y[j] = tmp;
                swaps = 1;
            }
        }
    }
}

void lagrange(int numOfKnownPoints, double* x, double* y, int i)
{
    for (int j = 0; j < numOfKnownPoints; j++)
    {
        double p = 1;
        for (int k = 0; k < numOfKnownPoints; k++)
        {
            if (k != j)
            {
                p *= (x[i] - x[k]) / (x[j] - x[k]);
            }
        }
        y[i] += y[j] * p;
    }
}

int main()
{
    FILE* out;
    out = fopen("output.txt", "w");

    int numOfKnownPoints, numOfUnknownPoints, numOfPoints;
    printf("Введите количество узлов интерполяции:\n");
    scanf("%d", &numOfKnownPoints);

    printf("Введите количество неизвестных точек:\n");
    scanf("%d", &numOfUnknownPoints);

    numOfPoints = numOfKnownPoints + numOfUnknownPoints;

    double x[numOfPoints], y[numOfPoints];
    for (int i = 0; i < numOfKnownPoints; i++)
    {
        printf("Введите значения узла (x%d y%d):\n", i + 1, i + 1);
        scanf("%lf %lf", &x[i], &y[i]);
    }
    for (int i = numOfKnownPoints; i < numOfPoints; i++)
    {
        printf("Введите неизвестный x:\n");
        scanf("%lf", &x[i]);
        y[i] = 0;
    }

    for (int i = numOfKnownPoints; i < numOfPoints; i++) //кол-во неизвестных y
    {
        lagrange(numOfKnownPoints, x, y, i);
    }

    comb_sort(x, y, numOfPoints);

    for (int i = 0; i < numOfPoints; i++)
    {
        fprintf(out, "%.6lf %.6lf\n", x[i], y[i]);
    }
}