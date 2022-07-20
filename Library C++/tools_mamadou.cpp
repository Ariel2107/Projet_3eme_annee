//
// Created by Mamadou SARAMBOUNOU on 19/05/2022.
//
#include <iostream>
using namespace std;

#include "tools_mamadou.h"


float random_choice(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

int random_choice_int(int min, int max) {
    int random = ((int) rand()) / (int) RAND_MAX;
    int diff = max - min;
    int r = random * diff;
    return min + r;
}

float* random_uniform(float min, float max, int size) {
    float *tab;

    for (int i=0; i<size; i+=1){
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = max - min;
        float r = random * diff;

        tab[i] = min + r;
    }

    return tab;
}

float predict_linear_model(float **inputs, float *model_weights) {

    int rows_inputs = sizeof(inputs) / sizeof(inputs[0]);
    int cols_inputs = sizeof(inputs[0]) / sizeof(inputs[0][0]);

    float total_sum = 0;
    float bias = model_weights[0];

    for (int i = 0; i < rows_inputs; i += 1) {
        for (int j = 0; j < cols_inputs; j += 1) {
            for (int k = 1; k < cols_inputs; k += 1) {

                total_sum += (inputs[i][j] * model_weights[k] + inputs[i][j + 1] * model_weights[k + 1]);
            }

        }
    }

    total_sum += bias;


    if (total_sum >= 0) {
        return 1;

    } else {
        return -1;
    }

}

float* train_linear_model_classification(int max_iteration, float **inputs, float *model_weights, float **output, float learning_step){

    int cols_inputs = sizeof(inputs[0]) / sizeof(inputs[0][0]);
    int k = random_choice(0, cols_inputs);
    float g_x_k = predict_linear_model(inputs, model_weights);
    float y_k = output[1][k];

    float diff = y_k - g_x_k;
    model_weights[0] = model_weights[0] + learning_step * diff * 1;


    for (int i = 1; k < cols_inputs; k += 1) {

        model_weights[i] = model_weights[i] + learning_step * diff * 1;

    }

    return model_weights;
}
