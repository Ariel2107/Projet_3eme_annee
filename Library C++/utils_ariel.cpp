//
// Created by ariel on 16/05/2022.
//

#include "utils_ariel.h"
#include <cmath>

template <typename T>

double tanh_me(double z){
    double result;
    result = (1 - exp(-2*z))/(1 + exp(-2*z));
    return result;
}

int sum(double* W, float* inputs){
    int total = 0;
    int size_W = sizeof(W)/sizeof(W[0]);
    int size_inputs = sizeof(inputs)/sizeof(inputs[0]);
    for (int i = 0; i < size_inputs; ++i) {
        for (int j = 0; j < size_W; ++j) {
            total = total + (inputs[i] * W[j]);
        }
    }
    return total;
}


