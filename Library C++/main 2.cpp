//
// Created by ariel on 16/05/2022.
//

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "utils_ariel.h"
#include "tools_mamadou.h"
#include <iomanip>

#define M 5
#define N 5


using namespace std;

void func(int **arr, int row, int col)        //function prototype
{
    for (int i=0; i<row; i++)
    {
        for(int j=0 ; j<col; j++)
        {
            cout<<arr[i][j]<<" ";   //printing each element of array
        }
        cout<<"\n";
    }
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

float predict_linear_model(float inputs[][], float model_weights[]) {

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

int main()
{
    std::cout <<"Hello, World!"<<std::endl;

<<<<<<< Updated upstream
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
=======
    float test_input[3][2] = {{1,1}, {2,3}, {3,3}};
    float test_w[3] = {1, 4.5, 5.8};

    int** arr2 = new int*[3];
    arr2[3] = new int[4]
    float test_resultat = predict_linear_model(test_input, test_w);



    int row, colm;
    cin >> row >> colm;
    int** arr = new int*[row];

    func(arr, row, colm);
>>>>>>> Stashed changes

    return 0;
}

