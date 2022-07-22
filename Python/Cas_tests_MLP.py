from ctypes import *
import random
from PIL import Image, ImageOps
import numpy as np
import os
from tqdm import tqdm
import pandas as pd
from sklearn.metrics import mean_squared_error, accuracy_score

my_dll = CDLL("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Library C++/My_Lib_CPP/cmake-build-debug/My_Lib_CPP.dll")

list_W = []
import_W = pd.read_csv("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Library C++/My_Lib_CPP/TEST_MODEL_WEIGHT.csv")

list_W.append(import_W.columns)
list_W = np.asarray(list_W)[0]
list_W = [float(i) for i in list_W]


file_uploaded = "C:/Users/ariel/Downloads/OIP (2).jfif"

image = ImageOps.grayscale(Image.open(file_uploaded).resize((56, 56)))

my_image = np.asarray(image, dtype=np.float64).flatten()
print(my_image)

struct_model_type = len(my_image) * c_float

struct_model_weight = len(list_W) * c_float


my_dll.predict_linear_model.argtypes = [POINTER(c_float), POINTER(c_float)]
my_dll.predict_linear_model.restype = c_float

resultat = my_dll.predict_linear_model(struct_model_type(*my_image), struct_model_weight(*list_W))

print(resultat)
