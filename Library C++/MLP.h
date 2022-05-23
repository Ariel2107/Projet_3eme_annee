//
// Created by ariel on 18/05/2022.
//

#ifndef PROJET_ANNUEL_MLP_H
#define PROJET_ANNUEL_MLP_H

float* predict_mlp_model(struct MLP * model, float* inputs, int32_t is_classification);

MLP* train_MLP(struct MLP* model, float* all_samples_inputs, float* all_samples_expected_inputs, float learning_rate,
               int32_t is_classification, int32_t nb_iter);

#endif //PROJET_ANNUEL_MLP_H
