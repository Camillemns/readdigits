#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nn_tools.h"

struct neural_network
{
    int nbr_input;
    int nbr_hidden;
    int nbr_output;
    float *input;
    float **w_input_to_hidden;
    float *bias_input_to_hidden;
    float **dwIH;
    float *dbIH;
    float *hidden;
    float **w_hidden_to_output;
    float *bias_hidden_to_output;
    float **dwHO;
    float *dbHO;
    float *output;
    float *goal;
    float *error_rate_out;
    float *error_rate_hid;
};
typedef struct neural_network net;

net* init_neural_network (int in, int hid, int out)
{
    net *nn = malloc(sizeof(net));;
    nn -> nbr_input = in;
    nn -> nbr_hidden = hid;
    nn -> nbr_output = out;
    nn -> input = malloc(sizeof(float) * (nn -> nbr_input));
    nn -> w_input_to_hidden = calloc(nn -> nbr_input, sizeof(float*));
    for (int i = 0; i < nn -> nbr_input; i++)
    {
        nn -> w_input_to_hidden[i] = calloc(nn -> nbr_hidden, sizeof(float));
    }
    nn -> bias_input_to_hidden = malloc(sizeof(float) * (nn -> nbr_hidden));
    nn -> dwIH = calloc(nn -> nbr_input, sizeof(float *));
    for (int i = 0; i < nn -> nbr_input; i++)
    {
        nn -> dwIH[i] = calloc(nn -> nbr_hidden, sizeof(float));
    }
    nn -> dbIH = malloc(sizeof(float) * (nn -> nbr_hidden));
    nn -> hidden = malloc(sizeof(float) * (nn -> nbr_hidden));
    nn -> w_hidden_to_output = calloc(nn -> nbr_hidden, sizeof(float *));
    for (int i = 0; i < nn -> nbr_hidden; i++)
    {
        nn -> w_hidden_to_output[i] = calloc(nn -> nbr_output, sizeof(float));
    }
    nn -> bias_hidden_to_output = malloc(sizeof(float) * (nn -> nbr_output));
    nn -> dwHO = calloc(nn -> nbr_hidden, sizeof(float *));
    for (int i = 0; i < nn -> nbr_hidden; i++)
    {
        nn -> dwHO[i] = calloc(nn -> nbr_output, sizeof(float));
    }
    nn -> dbHO = malloc(sizeof(float) * (nn -> nbr_output));
    nn -> output = malloc(sizeof(float) * (nn -> nbr_output));
    nn -> goal = malloc(sizeof(float) * (nn -> nbr_output));
    nn -> error_rate_out = malloc(sizeof(float) * (nn -> nbr_output));
    nn -> error_rate_hid = malloc(sizeof(float) * (nn -> nbr_hidden));

    for (int i = 0; i < nn -> nbr_hidden; i++)
    {
        for (int j = 0; j < nn -> nbr_input; j++)
        {
            nn -> w_input_to_hidden[j][i] = random();
        }
        nn -> bias_input_to_hidden[i] = random();
    }

    for (int i = 0; i < nn -> nbr_output; i++)
    {
        for (int j = 0; j < nn -> nbr_hidden; j++)
        {
            nn -> w_hidden_to_output[j][i] = random();
        }
        nn -> bias_hidden_to_output[i] = random();
    }
    return nn;
}

void feedforward(net* a)
{
    for (int i = 0; i < a -> nbr_output; i++)
    {
        a -> output[i] = 0;
    }
    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        a -> hidden[i] = 0;
    }
    float sum;
    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        sum = 0.0;
        for (int k = 0; k < a -> nbr_input ; k++)
        {
            sum += a -> w_input_to_hidden[k][i] * a -> input[k];
        }
        a -> hidden[i] = sigmoid(sum + (a -> bias_input_to_hidden[i]));
    }

    for (int i = 0; i < a -> nbr_output; i++)
    {
        sum = 0.0;
        for (int k = 0; k < a -> nbr_hidden; k++)
        {
            sum += a -> w_hidden_to_output[k][i] * a -> hidden[k];
        }
        a -> output[i] = sigmoid(sum + (a -> bias_hidden_to_output[i]));
    }
}

void backpropagation(net* a)
{
    float sum;
    for (int i = 0; i < a -> nbr_output; i++)
    {
        a -> error_rate_out[i] = (a -> goal[i]) - ( a-> output[i]);
    }

    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        sum = 0;
        for (int j = 0; j < a -> nbr_output; j++)
        {
            sum += (a -> w_hidden_to_output[i][j]) * (a -> error_rate_out[j]);
        }
        a -> error_rate_hid[i] = sum;
    }

    float der,lr,error;
    lr = 0.1;
    for (int i = 0; i < a -> nbr_output; i++)
    {
        der = derivate_sigmoid(a -> output[i]);
        error = a -> error_rate_out[i];
        a -> dbHO[i] = lr * error * der;
        der = 0;
        error = 0;
    }

    for (int i = 0; i < a -> nbr_output; i++)
    {
        for (int j = 0; j < a -> nbr_hidden; j++)
        {
            a -> dwHO[j][i] = (a -> dbHO[i]) * (a -> hidden[j]);
        }
    }

    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        der = derivate_sigmoid(a -> hidden[i]);
        error = a -> error_rate_hid[i];
        a -> dbIH[i] = lr * error * der;
        der = 0;
        error = 0;
    }

    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        for (int j = 0; j < a -> nbr_input; j++)
        {
            a -> dwIH[j][i] = a -> dbIH[i] * a -> input[j];
        }
    }
}

void new_weights_bias(net *a)
{
    float value;
    //update of the input to hidden weights & bias
    for (int i = 0; i < a -> nbr_hidden; i++)
    {
        for (int j = 0; j < a -> nbr_input; j++)
        {
            value = a -> w_input_to_hidden[j][i];
            a -> w_input_to_hidden[j][i] = 0;
            a -> w_input_to_hidden[j][i] = value + (a -> dwIH[j][i]);
        }
        value = a -> bias_input_to_hidden[i];
        a -> bias_input_to_hidden[i] = 0;
        a -> bias_input_to_hidden[i] = value + (a -> dbIH[i]);
    }

    //update of the hidden to output weights & bias
    for (int i = 0; i < a -> nbr_output; i++)
    {
        for (int j = 0; j < a -> nbr_hidden; j++)
        {
            value = a -> w_hidden_to_output[j][i];
            a -> w_hidden_to_output[j][i] = 0;
            a -> w_hidden_to_output[j][i] = value + (a -> dwHO[j][i]);
        }
        value = a -> bias_hidden_to_output[i];
        a -> bias_hidden_to_output[i] = 0;
        a -> bias_hidden_to_output[i] = value + (a -> dbHO[i]);
    }
}

void run_neural_network(net *a, float **train, int *label, int epoch)
{
    for (int b = 0; b < epoch; b++)
    {
        int *c = calloc(10000, sizeof(int));
        for (int w = 0; w < 10000; w++)
        {
            int t = rand() % 10000;
            if( c[t] == 0)
            {
                int r = label[t];
                for (int i = 0; i < a -> nbr_output; i++)
                {
                    a -> goal[i] = 0;
                    if (i == r)
                    {
                        a -> goal[i] = 1;
                    }
                    a -> output[i] = 0;
                }
                for (int i = 0; i < a -> nbr_hidden; i++)
                {
                    a -> hidden[i] = 0;
                }
                for (int i = 0; i < a-> nbr_input; i++)
                {
                    a -> input[i] = train[t][i];
                }
                feedforward(a);
                backpropagation(a);
                new_weights_bias(a);
                for (int i = 0; i < a -> nbr_hidden; i++)
                {
                    for (int j = 0; j < a -> nbr_input; j++)
                    {
                        a -> dwIH[j][i] = 0;
                    }
                    a -> dbIH[i] = 0;
                }
                for (int i = 0; i < a -> nbr_output; i++)
                {
                    for (int j = 0; j < a -> nbr_hidden; j++)
                    {
                        a -> dwHO[j][i] = 0;
                    }
                    a -> dbHO[i] = 0;
                }
                c[t] = 1;
            }
            if ( w == 1000 - 1)
            {
                for (int i = 0; i < 1000; i++)
                {
                    c[i] = 0;
                }
            }
        }
    }
}
