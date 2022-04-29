import requests
import os
import urllib
from urllib.error import HTTPError
import colorama
from colorama import Fore, init
import time
init(autoreset=True)
url = "https://zoo-animal-api.herokuapp.com/animals/rand/"


def main():
    os.system("cls")
    entry = input("Combien de lien souhaiter : ")
    nbIt = int(entry)
    repository = "images"
    if not os.path.exists(repository):
        os.mkdir(repository)
    try:
        for i in range(0, nbIt):
            response = requests.get(url)
            images = response.json()['image_link']
    except HTTPError:
        print("Pause ... attend tu as envoyé trop de requêtes !")
        time.sleep(60)
        response = requests.get(url)
        images = response.json()['image_link']
        image = images.lstrip('htps:/upload.wikimedia.org/wikipedia/commons/.1234567890sbzooinstitutes.com/img/animals/86fineartamerica.com/images-medium-large-5/')
        print(Fore.RED + image)
    try:
        open("images/" + image)
        print("Le fichier existe deja !")
    except OSError:
        print(Fore.GREEN + "1 image enregitré  : " + image)
        urllib.request.urlretrieve(images, "images/" + image)
    except HTTPError:
        time.sleep(60)
        print(Fore.GREEN + "1 image enregitré !")
        urllib.request.urlretrieve(images, "images/" + image)
        urllib.request.urlretrieve(images, "images/" + image)

if __name__ == '__main__':
    main()