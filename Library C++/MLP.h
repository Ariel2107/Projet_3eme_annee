//
// Created by ariel on 18/05/2022.
//

#ifndef PROJET_ANNUEL_MLP_H
#define PROJET_ANNUEL_MLP_H

#include <cstdint>

struct MLP {
    double*** W;
    double** X;
    double** deltas;
    int32_t L;
    int32_t* d;
};

MLP* create_mlp_model(int32_t* npl, int32_t npl_size);

float* predict_mlp_model(struct MLP * model, float* inputs, int32_t inputs_size, int32_t is_classification);

MLP* train_MLP(struct MLP* model, float** all_samples_inputs, int32_t len_sample_inputs,
        float** all_samples_expected_inputs, float learning_rate, int32_t is_classification, int32_t nb_iter);

#endif //PROJET_ANNUEL_MLP_H
