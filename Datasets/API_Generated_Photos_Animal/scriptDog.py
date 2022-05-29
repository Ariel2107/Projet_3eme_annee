import sys

import requests
import os
import urllib
from urllib.error import HTTPError
from colorama import Fore, init
import time
init(autoreset=True)
url = "https://random.dog/doggos"
url2 = "https://random.dog/"
def main():
    os.system("cls")
    repository = "imagesChien"
    if not os.path.exists(repository):
        os.mkdir(repository)
    response = requests.get(url)
    for i in response.json():
        try:
            open("imagesChien/" + i)
            print("Le fichier existe deja !")
        except FileNotFoundError:
            if ".mp4" in i:
                print(i + " : est un fichier mp4 je ne le prend pas en charge !")
                pass
            elif ".gif" in i:
                print(i + " : est un fichier gif je ne le prend pas en charge !")
            else:
                response = url2 + str(i)
                urllib.request.urlretrieve(response, "imagesChien/" + i)
                print(Fore.GREEN + "1 image enregitré  : " + i)
        except KeyboardInterrupt:
            print("bye")
            sys.exit(1)

if __name__ == '__main__':
    main()