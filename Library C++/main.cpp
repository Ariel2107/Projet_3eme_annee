//
// Created by ariel on 16/05/2022.
//

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "utils_ariel.h"
#include "tools_mamadou.h"
#include <iomanip>

using namespace std;

int main()
{
    std::cout <<"Hello, World!"<<std::endl;

    float W[2] = {0.7, -0.8};

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
    cout << res << endl;

    return 0;
}

