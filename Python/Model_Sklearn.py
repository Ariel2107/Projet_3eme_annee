import pickle
import numpy as np
from PIL import Image, ImageOps

loaded_model = pickle.load(open("C:/Users/ariel/OneDrive/Bureau/ESGI/Bachelor/Projet Annuel/Python/MODEL SKL/saved_model.pkl", 'rb'))

def prediction_skl(image):
    prediction = loaded_model.predict(image).item()

    return prediction
