//
// Created by Mamadou SARAMBOUNOU on 19/05/2022.
//

#include "tools_mamadou.h"
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