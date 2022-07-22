import streamlit as st
import matplotlib.pyplot as plt
from PIL import Image, ImageOps
import numpy as np
import ctypes
from ctypes import *
import Interop_MLP
import Model_Sklearn
import pandas as pd

my_dll = CDLL("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Library C++/My_Lib_CPP/cmake-build-debug/My_Lib_CPP.dll")
my_dll.predict_linear_model.argtypes = [POINTER(c_float), POINTER(c_float)]
my_dll.predict_linear_model.restype = c_float

list_W = []
import_W = pd.read_csv("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Library C++/My_Lib_CPP/TEST_MODEL_WEIGHT.csv")

list_W.append(import_W.columns)
list_W = np.asarray(list_W)[0]
list_W = [float(i) for i in list_W]


st.title("Projet annuel : MACHINE LEARNING")

def model_option():
    option = st.selectbox('Choisissez votre model', ("SKLEARN", 'LIBRARIE MODELE LINEAIRE', 'LIBRARIE MLP'))
    st.write('Option:', option)
    return option

model_choice = model_option()

file_uploaded = st.file_uploader("Upload Files",type=['png','jpg', 'jpeg', 'gif', 'jfif'])

def predict_class():
    image = ImageOps.grayscale(Image.open(file_uploaded).resize((56, 56)))

    if model_choice == "SKLEARN":
        array = np.asarray(image).flatten() / 255 ** 2
        array = np.array(array.flatten().tolist()).reshape((1, 56 ** 2))
        resultat = Model_Sklearn.prediction_skl(array)
    elif model_choice == "LIBRARIE MLP":
        array = np.asarray(image).flatten().tolist()
        resultat = Interop_MLP.predict_mlp_without_model(array, len(array), 1)
    elif model_choice == "LIBRARIE MODELE LINEAIRE":
        my_image = np.asarray(image, dtype=np.float64).flatten()
        struct_model_type = len(my_image) * c_float

        struct_model_weight = len(list_W) * c_float

        resultat = my_dll.predict_linear_model(struct_model_type(*my_image), struct_model_weight(*list_W))


    if resultat == -1:
        resultat = "It's a Woman !"
    else:
        resultat = "It's a Man !"
    return resultat


def main():
    if file_uploaded is not None:
        image = Image.open(file_uploaded)
        figure = plt.figure()
        plt.imshow(image)
        plt.axis("off")
        st.pyplot(figure)
        resultat = predict_class()
        st.write(resultat)

if __name__ == "__main__":
   main()