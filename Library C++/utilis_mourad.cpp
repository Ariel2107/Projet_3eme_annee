//
// Created by Noureddine SKB on 22/05/2022.
//

#include "utilis_mourad.h"

std::vector<int> Append(std::vector<int> tab1, std::vector<int> tab2){
    std::vector<int> results;
    results.reserve(tab1.size() + tab2.size());
    results.insert(results.end(), tab1.begin(), tab1.end());
    results.insert(results.end(), tab2.begin(), tab2.end());
    return results;
}
std::vector<float> Append(std::vector<float> tab1, std::vector<float> tab2){
    std::vector<float> results;
    results.reserve(tab1.size() + tab2.size());
    results.insert(results.end(), tab1.begin(), tab1.end());
    results.insert(results.end(), tab2.begin(), tab2.begin());
}

std::vector<double> Append(std::vector<double> tab1, std::vector<double> tab2){
    std::vector<double> results;
    results.reserve(tab1.size() + tab2.size());
    results.insert(results.end(), tab1.begin(), tab1.end());
    results.insert(results.end(), tab2.begin(), tab2.end());
}

float* Append2(float *tab1, float *tab2){
    float *results;
    int len1 = sizeof(tab1);
    int len2 = sizeof(tab2);
    int i;
    int j = 0;
    for (int i = 0; i < len1; i++) {
        results[j] = tab1[i];
        j++;
    }
    for (int k = 0; k < len2; ++k) {
        results[j] = tab2[i];
        j++;
    }
    return results;
}

double* Append2(double *tab1, double tab2){
    double *results;
    int len1 = sizeof(tab1);
    int len2 = sizeof(tab2);
    int i;
    int j = 0;
    for (int i = 0; i < len1; i++) {
        results[j] = tab1[i];
        j++;
    }
    for (int k = 0; k < len2; ++k) {
        results[j] = tab2[i];
        j++;
    }
    return results;
}

int* Append2(int *tab1, int* tab2){
    int *results;
    int len1 = sizeof(tab1);
    int len2 = sizeof(tab2);
    int i;
    int j = 0;
    for (int i = 0; i < len1; ++i) {
        results[j] = tab1[i];
        j++;
    }
    for (int k = 0; k < len2; ++k) {
        results[j] = tab2[i];
        j++;
    }
    return results;
}
