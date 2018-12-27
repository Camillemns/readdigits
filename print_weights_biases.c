#include <stdio.h>
#include <stdlib.h>

void print_weights(float **wIH, float **wHO,int in, int hid, int out)
{
    FILE *src;
    src = fopen("wIH.txt","w");
    if (!src)
    {
        printf("Error loading .txt\n");
    }
    for (int i = 0; i < hid; i++)
    {
        for (int j = 0; j < in; j++)
        {
            fprintf(src, "%f\n", wIH[j][i]);
        }
    }
    fclose(src);

    src = fopen("wHO.txt", "w");
    if (!src)
    {
        printf("Eroor loading .txt\n");
    }
    for (int i = 0; i < out; i++)
    {
        for (int j = 0; j < hid; j++)
        {
             fprintf(src, "%f\n", wHO[j][i]);
        }
    }
    fclose(src);
}

void print_biases(float *bIH, float *bHO, int hid, int out)
{
    FILE *src;
    src = fopen("bIH.txt", "w");
    if (!src)
    {
        printf("Error loading .txt\n");
    }
    for (int i = 0; i < hid; i++)
    {
        fprintf(src, "%f\n", bIH[i]);
    }
    fclose(src);

    src = fopen("bHO.txt", "w");
    if (!src)
    {
        printf("Error loading .txt\n");
    }
    for (int i = 0; i < out; i++)
    {
        fprintf(src, "%f\n", bHO[i]);
    }
    fclose(src);
}

