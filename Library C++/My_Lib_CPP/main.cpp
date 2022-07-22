#if WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif

#include <iostream>

float random_choice(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

extern "C" {
    DLLEXPORT double* create_linear_model(int inputCountPerSample){

        double* W = new double[inputCountPerSample + 1];
        const int POINT = 100;

        for (int i = 0; i < inputCountPerSample + 1; i++) {

            double randVal = std::rand() % POINT;
            int powerCount = std::rand() % POINT;

            while (powerCount > 0) {
                randVal *= -1;
                powerCount -= 1;
            }

            W[i] = randVal / POINT;
        }
        return W;
    }

    DLLEXPORT float predict_linear_model_(float **inputs, float *model_weights) {

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

    DLLEXPORT float predict_linear_model(float *inputs, float *model_weights) {

        int rows_inputs = sizeof(inputs) / sizeof(inputs[0]);

        float total_sum = 0;
        float bias = model_weights[0];

        for (int j = 0; j < rows_inputs; j += 1) {
            for (int k = 1; k < rows_inputs; k += 1) {

                total_sum += (inputs[j] * model_weights[k] + inputs[j + 1] * model_weights[k + 1]);
            }
        }

        total_sum += bias;


        if (total_sum >= 0) {
            return 1;

        } else {
            return -1;
        }

    }

    DLLEXPORT void train_linear_model_classification(int max_iteration, float **inputs, float *model_weights, float *output, float learning_step, int size_model_weights, int input_size){

        int k;
        float g_x_k;
        float y_k;
        float diff;

        double* new_W = create_linear_model(input_size/2);

        for (int i = 1; i < max_iteration; i += 1) {

            k = random_choice(0, input_size);
            g_x_k = predict_linear_model_(inputs, model_weights);
            y_k = output[k];

            diff = y_k - g_x_k;
            model_weights[0] = model_weights[0] + learning_step * diff * 1;

            for (int j = 1; j < size_model_weights; ++j) {
                for (int l = 0; l < input_size; ++l) {
                    model_weights[j] = model_weights[j] + learning_step * diff * inputs[k][l];
                }
            }

        }
    }
}

