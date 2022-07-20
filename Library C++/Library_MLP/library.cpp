#if WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif

#include <cstdint>
#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <fstream>

using namespace std;

struct MLP {
    float*** W;
    float** X;
    float** deltas;
    int32_t L;
    int32_t* d;
};

unsigned int seed;


float random_choice(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

struct MLP * copy_MLP_model(struct MLP * old_model){
    MLP * model = new MLP;
    model->d = new int32_t;
    model->L = old_model->L;
    for (int32_t i = 0; i < old_model->L + 1; ++i) {
        model->d[i] = old_model->d[i];
    }

    model->W = new float**;
    for (int32_t l = 0; l < old_model->L + 1; l++) {
        model->W[l] = new float *;
        if (l == 0){
            continue;
        }
        for (int32_t i = 0; i < model->d[l - 1] + 1; ++i) {
            model->W[l][i] = new float ;
            for (int32_t j = 0; j < model->d[l] + 1; ++j) {
                if(j == 0){
                    model->W[l][i][j] = 0.0;
                }else{
                    model->W[l][i][j] = random_choice(-1.0, 1.0);
                }
            }
        }

    }
    model->X = new float *;
    model->deltas = new float *;
    for (int32_t l = 0; l < old_model->L + 1; ++l) {
        model->X[l] = new float;
        model->deltas[l] = new float;
        for (int32_t j = 0; j < model->d[l] + 1; ++j) {
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

std::ostream& write_model(std::ostream& os, struct MLP* model, int32_t* npl, int32_t npl_size){
    for (int32_t l = 0; l < npl_size; l++) {
        for (int32_t i = 0; i < npl[l - 1] + 1; ++i) {
            os << "/";
            for (int32_t j = 0; j < npl[l] + 1; ++j) {
                os << model->W[l][i][j]<<" ";
            }
        }
        os<<";";
    }

    return os;
}

extern "C" {
    DLLEXPORT struct MLP * create_mlp_model(int32_t* npl, int32_t npl_size) {
        srand(10);
        MLP * model = new MLP;
        model->d = new int32_t[npl_size];
        model->L = npl_size - 1;
        for (int32_t i = 0; i < npl_size; ++i) {
            model->d[i] = npl[i];
        }

        model->W = new float**[npl_size];
        for (int32_t l = 0; l < npl_size; l++) {
            model->W[l] = new float *[npl[l - 1]];
            if (l == 0){
                continue;
            }
            for (int32_t i = 0; i < npl[l - 1] + 1; ++i) {
                model->W[l][i] = new float[npl[l]] ;
                for (int32_t j = 0; j < npl[l] + 1; ++j) {
                    if(j == 0){
                        model->W[l][i][j] = 0.0;
                    }else{
                        model->W[l][i][j] = random_choice(-1.0, 1.0);
                    }
                }
            }

        }
        model->X = new float *[npl_size];
        model->deltas = new float *[npl_size];
        for (int32_t l = 0; l < npl_size; ++l) {
            model->X[l] = new float[npl[l]];
            model->deltas[l] = new float[npl[l]];
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

    DLLEXPORT float* predict_mlp_model(struct MLP * model, float* inputs, int32_t inputs_size, int32_t is_classification) {
        for (int i = 0; i < model->d[0]; ++i) {
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
        float *tab = new float[model->L];
        for (int32_t i = 1; i < model->L; ++i) {
            tab[i] = model->X[model->L][i];
        }
        return tab;
    }

    DLLEXPORT void destroy_mlp_model(struct MLP * model) {
        delete(model);
    }

    DLLEXPORT void insert_saved_model(struct MLP* model, float input, int index_l, int index_i, int index_j){
        model->W[index_l][index_i][index_j] = input;
    }

    DLLEXPORT void alternate_train_MLP(struct MLP* model, float* sample_inputs, float* sample_expected_output,
            float learning_rate, int32_t is_classification){
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

    DLLEXPORT struct MLP* train_MLP(struct MLP* model, float** all_samples_inputs, int32_t len_sample_inputs, float** all_samples_expected_inputs, float learning_rate, int32_t is_classification, int32_t nb_iter){
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

    DLLEXPORT void save_MLP(struct MLP* model, int32_t* npl, int32_t npl_size){
        std::fstream of("Map.txt", std::ios::out | std::ios::app);

        if (of.is_open())
        {
            write_model(of, model, npl, npl_size);
            of.close();
        }

    }

    DLLEXPORT void destroy_float_array(float* array) {
        delete[] array;
    }

    DLLEXPORT int32_t return_42() {
        return 42;
    }

    DLLEXPORT int32_t my_add(int32_t a, int32_t b) {
        return a + b;
    }
}

