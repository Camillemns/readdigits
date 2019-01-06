#include <stdio.h>
#include <stdlib.h>

void free_train(float **train);
void free_test(float **test);
int put_train_value_in_array(float **train, int *label_train);
int put_test_value_in_array(float **test, int *label_test);
