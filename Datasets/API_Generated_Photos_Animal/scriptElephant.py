import sys

import requests
import os
import urllib
from urllib.error import HTTPError
from colorama import Fore, init
import time
init(autoreset=True)
url = "https://elephant-api.herokuapp.com/elephants"
def main():
    os.system("cls")
    repository = "imagesElephant"
    if not os.path.exists(repository):
        os.mkdir(repository)
    response = requests.get(url)
    try:
        for i in response.json():
            if 'missing.jpg' in i['image']:
                pass
            else:
                urllib.request.urlretrieve(i["image"], "imagesElephant/" + i["image"].lstrip("https://elephant-api.herokuapp.com/pictures/"))
                print(i['image'])
    except KeyError:
        print("il n'y a pas d'image..")

if __name__ == '__main__':
    main()
