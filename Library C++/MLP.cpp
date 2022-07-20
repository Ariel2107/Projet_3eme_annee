//
// Created by ariel on 18/05/2022.
//

#include "utilis_mourad.h"
#include "tools_mamadou.h"
#include <cstdint>
#include <cmath>
#include <random>
#include "MLP.h"

MLP* create_mlp_model(int32_t* npl, int32_t npl_size){
    MLP * model = new MLP;
    model->d = new int32_t;
    model->L = npl_size - 1;
    for (int32_t i = 0; i < npl_size; ++i) {
        model->d[i] = npl[i];
    }

    model->W = new double**;
    for (int32_t l = 0; l < npl_size; l++) {
        model->W[l] = new double *;
        if (l == 0){
            continue;
        }
        for (int32_t i = 0; i < npl[l - 1] + 1; ++i) {
            model->W[l][i] = new double ;
            for (int32_t j = 0; j < npl[l] + 1; ++j) {
                if(j == 0){
                    model->W[l][i][j] = 0.0;
                }else{
                    model->W[l][i][j] = random_choice(-1.0, 1.0);
                }
            }
        }

    }
    model->X = new double *;
    model->deltas = new double *;
    for (int32_t l = 0; l < npl_size; ++l) {
        model->X[l] = new double;
        model->deltas[l] = new double;
        for (int32_t j = 0; j < npl[l] + 1; ++j) {
            if (j == 0){
                model->X[l][j] = 1.0;
            }else{
                model->X[l][j] = 0.0;
            }
            model->deltas[l][j] = 0.0;
        }
    }
    return model;
}

float* predict_mlp_model(struct MLP * model, float* inputs, int32_t inputs_size, int32_t is_classification) {
    for (auto i = 0; i < model->d[0]; ++i) {
        model->X[0][i + 1] = inputs[i];
    }

    float total;
    for (int32_t l = 1; l < model->L + 1; ++l) {
        for (int32_t j = 0; j < (model->d[l] + 1); ++j) {
            total = 0.0;
            for (int32_t i = 0; i < (model->d[l - 1] + 1); ++i) {
                total += model->W[l][i][j] * model->X[l - 1][i];
            }
            if (l < model->L | is_classification == 1){
                total = tanh(total);
            }
            model->X[l][j] = total;
        }
    }
    float *tab = new float;
    for (int32_t i = 1; i < inputs_size; ++i) {
        tab[i] = model->X[model->L][i];
    }
    return tab;
}

MLP* train_MLP(struct MLP* model, float** all_samples_inputs, int32_t len_sample_inputs, float** all_samples_expected_inputs, float learning_rate, int32_t is_classification, int32_t nb_iter) {
    for (int32_t po = 0; po < nb_iter + 1; po++) {
        int32_t k = rand()%len_sample_inputs;
        float *sample_inputs = all_samples_inputs[k];
        float *sample_expected_output = all_samples_expected_inputs[k];
        float *_ = predict_mlp_model(model, sample_inputs, 1, 1);

        for (int32_t j = 1; j < model->d[model->L] + 1; ++j) {
            float semi_gradient = model->X[model->L][j] - sample_expected_output[j - 1];
            if (is_classification == 1) {
                semi_gradient = semi_gradient * (1 - pow(model->X[model->L][j], 2));
            }
            model->deltas[model->L][j] = semi_gradient;
        }
        float total;
        for (int32_t l = model->L ; l > 0; --l) {
            for (int32_t i = 1; i < model->d[l - 1] + 1; ++i) {
                total = 0.0;
                for (int32_t j = 1; j < model->d[l] + 1; ++j) {
                    total += model->W[l][i][j] * model->deltas[l][j];
                }
                total = (1 - pow(model->X[l - 1][i], 2)) * total;
                model->deltas[l - 1][i] = total;
            }
        }

        for (int32_t l = 1; l < model->L + 1; ++l) {
            for (int32_t i = 0; i < model->d[l - 1] + 1; ++i) {
                for (int32_t j = 0; j < model->d[l] + 1; ++j) {
                    model->W[l][i][j] -= learning_rate * model->X[l - 1][i] * model->deltas[l][j];
                }
            }
        }

    }
    return model;
}


