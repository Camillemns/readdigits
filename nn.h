#include <stdio.h>
#include <stdlib.h>
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
    float **dbHO;
    float *output;
    float *goal;
    float *error_rate_out;
    float *error_rate_hid;
};
typedef struct neural_network net;

net* init_neural_network(int in, int hid, int out);
void feedforward(net* a);
void backpropagation(net* a);
void new_weights_bias(net* a);
void run_neural_network(net *a, float **train, int *label, int epoch);

