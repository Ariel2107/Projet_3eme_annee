//
// Created by ariel on 18/05/2022.
//

#include "MLP.h"
#include "utils_ariel.h"
#include "utilis_mourad.h"
#include "tools_mamadou.h"

struct MLP {
    double*** W;
    double** X;
    double** deltas;
    int32_t L;
    int32_t* d;
};


MLP* create_mlp_model(int* npl){
    //TODO
    MLP model; //crée un MLP à partir de sa structure
    model.d = npl;
    model.L = sizeof(model.d) - 1;
    for (int i = 0; i < sizeof(model.d); i++) {
        int* voidtab = [];
        Append2(model.W, voidtab);
        if (i == 0){
            continue;
        }
        for (int j = 0; j < model.d[i - 1] + 1; i++) {
            Append2(model.W[i], int* newtab);
            for (int k = 0; k < model.d[i]; i++) {
                if (j==0){
                    Append2(model.W[i][j],0);
                }else{
                    Append2(model.W[i][j], random_uniform(-1.0, 1.0));
                }
            }
        }
    }
    int *newtab = [1.0];
    int *newtab2 = [0.0];
    for (int i = 0; i < sizeof(model.d); i++) {
        int* tabvoid = [];
        Append2(model.X, tabvoid);
        Append2(model.deltas, tabvoid);
        for (int j = 0; j < model.d[i] + 1; j++) {
            if (j == 0){
                Append2(model.X[i], newtab);
            }else {
                Append2(model.X[i], newtab2);
            }
            Append2(model.deltas[i], 0.0);
        }
    }
    return model;
}

float* predict_mlp_model(struct MLP * model, float* inputs, int32_t is_classification) {
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

MLP* train_MLP(struct MLP* model, float* all_samples_inputs, float* all_samples_expected_inputs, float learning_rate,
        int32_t is_classification, int32_t nb_iter){
    for (0:nb_iter) {
        float k; // Ajouter le random entre 0 et len sample inputs
        float* sample_inputs = all_samples_inputs[k];
        float* sample_expected_output = all_samples_expected_inputs[k];
        float* _ = predict_mlp_model(MLP, sample_inputs, 1);

        for (int j = 1; j < model->d[model->L] + 1; ++j) {
            float semi_gradient = model->X[model->L][j] - sample_expected_output[j - 1];
            if(is_classification == 1){
                semi_gradient = semi_gradient * (1 - model->X[model->L][j]**2);
            }
            model->deltas[model->L][j] = semi_gradient;
        }

        for (int l = model->L; l > 1 ; --l) {
            for (int i = 1; i < model->d[l - 1] + 1; ++i) {
                float total = 0.0;
                for (int j = 1; j < model->d[l] + 1; ++j) {
                    total = total + model->W[l][i][j] * model->deltas[l][j];
                }
                total = (1 - model->X[l - 1][i]**2) * total;
                model->deltas[l - 1][i] = total;
            }
        }

        for (int l = 0; l < model->L + 1; ++l) {
            for (int i = 0; i < model->d[l - 1] + 1; ++i) {
                for (int j = 0; j < model->d[l] + 1; ++j) {
                    model->W[l][i][j] = model->W[l][i][j] - (learning_rate * model->X[l - 1][i] * model->deltas[l][j]);
                }
            }
        }

        return model;

    }
}


