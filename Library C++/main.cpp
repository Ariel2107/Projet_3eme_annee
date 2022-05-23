//
// Created by ariel on 16/05/2022.
//

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "utils_ariel.h"
#include <iomanip>
#include "MLP.h"
#include "tools_mamadou.h"

using namespace std;

int main()
{
    std::cout <<"Hello, World!"<<std::endl;
    double x = 1.30584843, result, varr1;
    result = (1 - exp(-2*x))/(1 + exp(-2*x));
    varr1 = tanh(1.30584843);
    float second_result;
   //second_result = tanh_me(1.30584843);
    cout << "tanh from script = " << setprecision(16) << result << endl;
    cout << "tanh from cmath = " << setprecision(16) << varr1 << endl;
    cout << "tanh from my method = " << setprecision(16) << second_result << endl;

    float old_W[3] = {0.1, 0.2, 0.3};
    float* W = new float[3];
    for (int i = 0; i < 3; ++i) {
        W[i] = old_W[i];
    }

    float X_tab[2][2] = {{2.0, 3.4}, {2.0, 3.4}};
    float** X = new float*[2];
    for (int i = 0; i < 2; ++i) {
        X[i] = new float[2];
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            X[i][j] = X_tab[i][j];
        }
    }


    float res = predict_linear_model(X, W);

    cout << "Result predicted = " << setprecision(16) << res << endl;

    return 0;
}

