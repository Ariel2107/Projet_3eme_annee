//
// Created by ariel on 18/05/2022.
//

#include "MLP.h"
#include "utils_ariel.h"

struct MLP {
    double*** W;
    double** X;
    double** deltas;
    int32_t L;
    int32_t* d;
};

float* predict_mlp_model(struct MLP * model, float* inputs, int32_t inputs_size, int32_t is_classification) {
    for (auto i = 0; i < model->d[0]; ++i) {
        model.X[0][i + 1] = inputs[i];
    }

    for (int l = 1; l < model->L + 1; ++l) {
        for (int j = 0; j < (model->d[l] + 1); ++j) {
            float total = 0.0;
            for (int i = 0; i < (model->d[l - 1] + 1); ++i) {
                total = total + model->W[l][i][j] * model->X[l - 1][i]
            }
            if (l < model->L || is_classification == 1){
                total = tanh_me(total);
            }
            model->X[l][j] = total;
        }
    }
    int tab_size = sizeof(model->X[model->L])/sizeof(model->X[model->L][0]);
    float tab[tab_size - 1];
    for (int i = 1; i < tab_size; ++i) {
        tab[i] = model->X[model->L][i];
    }
    return tab;
}
