//
// Created by ariel on 16/05/2022.
//

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "utils_ariel.h"
#include <iomanip>

using namespace std;

int main()
{
    std::cout <<"Hello, World!"<<std::endl;
    double x = 1.30584843, result, second_result, varr1;
    result = (1 - exp(-2*x))/(1 + exp(-2*x));
    varr1 = tanh(1.30584843);
    second_result = tanh_me(1.30584843);
    cout << "tanh from script = " << setprecision(16) << result << endl;
    cout << "tanh from cmath = " << setprecision(16) << varr1 << endl;
    cout << "tanh from my method = " << setprecision(16) << second_result << endl;



    return 0;
}

