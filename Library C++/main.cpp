//
// Created by ariel on 16/05/2022.
//

#include <iostream>
#include <cstdint>
#include "utilis_mourad.h"
#include "MLP.h"

using namespace std;

int main()
{
    float old_X[4][2] = {{1,0}, {0,1}, {0,0}, {1, 1}};
    float * *X = new float *;
    for (int32_t i = 0; i < 4; ++i) {
        X[i] = new float;
        for (int32_t j = 0; j < 2; ++j) {
            X[i][j] = old_X[i][j];
        }
    }

    float old_Y[4][1] = {{1}, {1}, {-1}, {-1}};
    float * *Y = new float *;
    for (int32_t i = 0; i < 4; ++i) {
        Y[i] = new float;
        for (int32_t j = 0; j < 1; ++j) {
            Y[i][j] = old_Y[i][j];
        }
    }

    int32_t * npl = new int32_t;
    npl[0] = 2;
    npl[1] = 5;
    npl[2] = 1;
    MLP * model = create_mlp_model(npl, 3);
    cout << "Before Training :" << endl;
    for (int32_t i = 0; i < 4; ++i) {
        float * prediction = predict_mlp_model(model, X[i], 2, 1);
        for (int32_t j = 1; j < 2; ++j) {
            cout << j << " : " << prediction[j] << endl;
        }
    }
    MLP * trained_model = train_MLP(model, X, 4, Y, 0.01, 1, 10000);
    cout << "After Training :" << endl;
    for (int32_t i = 0; i < 4; ++i) {
        float * prediction = predict_mlp_model(trained_model, X[i], 2, 1);
        for (int32_t j = 1; j < 2; ++j) {
            cout << j << " : " << prediction[j] << endl;
        }
    }

    return 0;
}

