#include "read_weights_biases.h"

int put_weights_in_arrays(float **t, int n, int m, char *str)
{
    //n input et m hidden; n hidden et m output
    FILE *src;
    src = fopen(str, "r");
    if (!src)
    {
        printf("ERROR when opening %s", str);
        return 1;
    }
    else
    {
        float value;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                value = 0;
                fscanf(src, "%f", &value);
                t[j][i] = value;
            }
        }
    }
    fclose(src);
    return 0;
}

int put_biases_in_arrays(float *t, int n, char *str)
{
    //n hidden; n output;
    FILE *src;
    src = fopen(str,"r");
    if (!src)
    {
        printf("ERROR when opening %s", str);
        return 1;
    }
    else
    {
        float value;
        for (int i = 0; i < n; i++)
        {
            value = 0;
            fscanf(src, "%f", &value);
            t[i] = value;
        }
    }
    fclose(src);
    return 0;
}
