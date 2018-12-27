#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

float random()
{
    float b = (float)rand()/ (float) RAND_MAX;
    /*int a = rand();
    if (a % 2 == 0)
    {
        b = -b;
    }*/
    return b;
}

float sigmoid(float a)
{
    return (1 / (1 + expf(-a)));
}

float derivate_sigmoid(float a)
{
    return a * (1 - a);
}

int max_array(float *a, int n)
{
    int m = 0;
    float c = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > c)
        {
            c = a[i];
            m = i;
        }
    }
    return m;
}

/*//nulle comme solution au niveau de la memoire avec le return mais si void ok? à verifier...
void  mult(float **a, float **b, float **c, int n, int m, int p)
{
    int sum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum = 0;
            for (int k = 0; k < p; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

void trans(float **a, float **b, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = a[j][i];
        }
    }
}*/
