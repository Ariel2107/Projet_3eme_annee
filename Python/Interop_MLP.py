from ctypes import *
import random
from PIL import Image, ImageOps
import numpy as np
import os
from tqdm import tqdm
from sklearn.metrics import mean_squared_error, accuracy_score



def preprocess_dataset(path1, path2, img_size):
    list_X, list_Y = [], []
    images = [path1 + "/" + i for i in os.listdir(path1)] + [path2 + "/" + i for i in os.listdir(path2)]
    np.random.shuffle(images)
    for filename in tqdm(images):
        if "." in filename:
            img = ImageOps.grayscale(Image.open(filename).resize(img_size))
            array = np.asarray(img).flatten().tolist()

            list_X.append(array)

            if "Female" in filename:
                class_array = [-1.0]
            elif "Male" in filename:
                class_array = [1.0]

            list_Y.append(class_array)

    X, Y = np.array(list_X), np.array(list_Y)
    return X / 255. ** 2, Y


def create_mlp_model(my_lib, struct_model):
    struct_model_int = [int(i) for i in struct_model]
    struct_model_type = len(struct_model_int) * c_int

    my_lib.create_mlp_model.argtypes = [struct_model_type,
                                        c_int]
    my_lib.create_mlp_model.restype = POINTER(c_void_p)

    return my_lib.create_mlp_model(struct_model_type(*struct_model_int), len(struct_model_int))


def predict_mlp(model, input, len_input, is_classification):
    my_dll.predict_mlp_model.argtypes = [c_void_p, POINTER(c_float), c_int32,
                                         c_int32]
    my_dll.predict_mlp_model.restype = POINTER(c_float)
    ng = c_float * len(input)
    prediction = my_dll.predict_mlp_model(model, ng(*input), len_input, is_classification)
    return prediction


def train_mlp(model_to_train, X_to_train, y, learning_rate, nb_iter, is_classification):
    my_dll.alternate_train_MLP.argtypes = [c_void_p, POINTER(c_float),
                                           POINTER(c_float), c_float, c_int32]
    my_dll.alternate_train_MLP.restype = None

    for i in tqdm(range(0, nb_iter)):
        k = random.choice(list(range(0, len(X_to_train))))
        arr_types_X = c_float * len(X_to_train[k])
        arr_types_Y = c_float * len(y[k])
        my_dll.alternate_train_MLP(model_to_train, arr_types_X(*X_to_train[k]), arr_types_Y(*y[k]), learning_rate,
                                   is_classification)


def destroy_model(model_to_destroy):
    my_dll.destroy_mlp_model.argtypes = [c_void_p]
    my_dll.destroy_mlp_model.restype = None

    my_dll.destroy_mlp_model(model_to_destroy)

def save_model(model_to_save, struct_model):
    struct_model_type = len(struct_model) * c_int32

    my_dll.save_MLP.argtypes = [c_void_p, POINTER(c_int32), c_int32]
    my_dll.save_MLP.restype = None

    my_dll.save_MLP(model_to_save, struct_model_type(*struct_model), len(struct_model))

def insert_saved_model(model_where_insert, npl):
    my_dll.insert_saved_model.argtypes = [c_void_p, c_float, c_int32, c_int32, c_int32]
    my_dll.insert_saved_model.restype = None

    with open("Map.txt") as f:
        content = f.read()

    model_W = [[[j for j in i.split(" ")[:-1]] for i in l.split("/")[1:]] for l in content.split(";")]
    d = npl
    print(model_W)
    for l in range(len(d)):
        if l == 0:
            continue
        for i in range(d[l - 1] + 1):
            for j in range(d[l] + 1):
                print(model_W[l][i][j])
                my_dll.insert_saved_model(model_where_insert, float(model_W[l][i][j]), l, i, j)


if __name__ == "__main__":
    random.seed(10)
    my_dll = cdll.LoadLibrary(
        "C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Library C++/Library_MLP/cmake-build-debug/Library_MLP.dll")

    # Creating MLP
    npl = [3136, 2, 1]

    model = create_mlp_model(my_dll, npl)
    #save_model(model, npl)
    #insert_saved_model(model, npl)

    print("Importing the training dataset...")
    X, Y = preprocess_dataset("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Training/Female", "C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Training/Male", (56, 56))


    # Before Training
    for k, i in enumerate(X):
        prediction = predict_mlp(model, i, len(i), 1)

    print("\nTraining...")
    train_mlp(model, X, Y, 0.1, 100000, 1)

    y_pred = []
    y_true = []
    # After Training
    for k, i in enumerate(X):
        prediction = predict_mlp(model, i, len(i), 1)
        if prediction[1] > 0:
            y_pred.append(1.0)
        else:
            y_pred.append(-1.0)
        y_true.append(Y[k][0])

    print("\nOn Training Dataset:")
    print("Modele's mean squared error :", mean_squared_error(y_true=y_true, y_pred=y_pred))
    print("Modele's accuracy :", accuracy_score(y_true=y_true, y_pred=y_pred))

    # Test on the testing Dataset
    print("\nImporting the test dataset...")
    X, Y = preprocess_dataset("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Test/Female",
                              "C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Test/Male",
                              (56, 56))
    y_pred = []
    y_true = []
    for k, i in enumerate(X):
        prediction = predict_mlp(model, i, len(i), 1)
        if prediction[1] > 0:
            y_pred.append(1.0)
        else:
            y_pred.append(-1.0)
        y_true.append(Y[k][0])

    print("On Test Dataset:")
    print("Modele's mean squared error :", mean_squared_error(y_true=y_true, y_pred=y_pred))
    print("Modele's accuracy :", accuracy_score(y_true=y_true, y_pred=y_pred))

    # Test on the validation dataset
    print("\nImporting the validation dataset...")
    X, Y = preprocess_dataset("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Validation/Female",
                              "C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Datasets/Validation/Male",
                              (56, 56))
    y_pred = []
    y_true = []
    for k, i in enumerate(X):
        prediction = predict_mlp(model, i, len(i), 1)
        if prediction[1] > 0:
            y_pred.append(1.0)
        else:
            y_pred.append(-1.0)
        y_true.append(Y[k][0])

    print("On Validation Dataset:")
    print("Modele's mean squared error :", mean_squared_error(y_true=y_true, y_pred=y_pred))
    print("Modele's accuracy :", accuracy_score(y_true=y_true, y_pred=y_pred))

    save_model(model, npl)
    destroy_model(model)

