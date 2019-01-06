#include <stdio.h>
#include <stdlib.h>

void free_train(float **train)
{
    for (int i = 0; i < 60000; i++)
    {
        free(train[i]);
    }
    free(train);
}
void free_test(float **test)
{
    for (int i = 0; i < 10000; i++)
    {
        free(test[i]);
    }
    free(test);
}

int put_train_value_in_array(float **train, int *label_train)
{
    FILE *src_train;
    //train
    src_train = fopen("source/train.txt", "r");
    if (!src_train)
    {
        printf("Erreur d'ouverture de train.txt\n");
        return 1;
    }
    else
    {
        float value;
        for (int i = 0; i < 60000; i++)
        {
            for (int j = 0; j < 784; j++)
            {
                value = 0;
                fscanf(src_train, "%f", &value);
                train[i][j] = value;
            }
        }
    }
    fclose(src_train);
    //label train
    src_train = fopen("source/ltrain.txt", "r");
    if (!src_train)
    {
        printf("Error open file ltrain.txt\n");
        return 1;
    }
    else
    {
        int value;
        for (int i = 0; i < 60000; i++)
        {
            value = 0;
            fscanf(src_train, "%d", &value);
            label_train[i] = value;
        }
    }
    fclose(src_train);
    return 0;
}

int put_test_value_in_array(float **test, int *label_test)
{
    FILE *src_test;
    //test
    src_test = fopen("source/test.txt", "r");
    if (!src_test)
    {
        printf("Error open file test.txt\n");
        return 1;
    }
    else
    {
        float value;
        for (int i = 0; i < 10000; i++)
        {
            for (int j = 0; j < 784; j++)
            {
                value = 0;
                fscanf(src_test, "%f", &value);
                test[i][j] = value;
            }
        }
    }
    fclose(src_test);
    //test label
    src_test = fopen("source/ltest.txt", "r");
    if (!src_test)
    {
        printf("Error open file ltest.txt\n");
        return 1;
    }
    else
    {
        int value;
        for (int i = 0; i < 10000; i++)
        {
            value = 0;
            fscanf(src_test, "%d", &value);
            label_test[i] = value;
        }
    }
    fclose(src_test);
    return 0;
}

