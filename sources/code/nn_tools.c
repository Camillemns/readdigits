#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

float randomizer()
{
    float b = (float)rand()/ (float) RAND_MAX;
    int a = rand();
    if (a % 2 == 0)
    {
        b = -b;
    }
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

char* int_to_char(int m)
{
    char *str;
    switch(m)
    {
        case 0:
            str = "0";
            break;
        case 1:
            str = "1";
            break;
        case 2:
            str = "2";
            break;
        case 3:
            str = "3";
            break;
        case 4:
            str = "4";
            break;
        case 5:
            str = "5";
            break;
        case 6:
            str = "6";
            break;
        case 7:
            str = "7";
            break;
        case 8:
            str = "8";
            break;
        case 9:
            str = "9";
            break;
        default:
            break;
    }
    return str;
}
