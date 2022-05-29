import sys

import requests
import os
import urllib
from urllib.error import HTTPError
from colorama import Fore, init
import time
init(autoreset=True)
url = "https://api.thecatapi.com/v1/images/search"
apikey = "d78fae9d-ac6f-40ac-9df4-e3213bea2ed6"

def main(nbIt):
    os.system("cls")
    repository = "imageChat"
    if not os.path.exists(repository):
        os.mkdir(repository)
    try:
        for i in range(0, nbIt):
            response = requests.get(url, headers={"x-api-key": apikey})
            data = response.json()[0]['url']
            print(response.json())
            data = str(data)
            image_name = data.lstrip("https://cdn2.thecatapi.com/images/")
            print(Fore.RED + data)
            print(Fore.RED + image_name)
            try:
                open("imageChat/" + image_name)
                print("Le fichier existe deja !")
            except FileNotFoundError:
                print(Fore.GREEN + "1 image enregitré  : " + image_name)
                urllib.request.urlretrieve(data, "imagesChat/" + image_name)
    except KeyboardInterrupt:
        print("au revoir")
        sys.exit(1)



if __name__ == "__main__":
    entry = input("Combien de lien souhaiter : ")
    nbIt = int(entry)
    main(nbIt)
    exit(0)