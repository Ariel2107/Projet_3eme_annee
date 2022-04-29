import requests
from bs4 import BeautifulSoup
import os


# ---------------------------- IMAGES URL ----------------------------
url_men = "https://www.gettyimages.fr/photos/portrait-homme"
url_men_google_img = "https://www.google.com/search?q=portrait+homme&client=safari&sxsrf=APq-WBugyNZ4vIpvLQoGgFnGtev7jik0OQ:1648645304993&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjv246u8u32AhUDyoUKHTufCj0Q_AUoAXoECAEQAw&biw=1440&bih=820&dpr=2"
url_men_pinterest = "https://www.pinterest.fr/search/pins/?q=portrait%20homme&rs=typed&term_meta[]=portrait%7Ctyped&term_meta[]=homme%7Ctyped"
url_men_istockphoto  = "https://www.istockphoto.com/fr/photos/portrait-homme"
url_men_pinterest_black_men = "https://www.pinterest.fr/genevievepichot/portrait-homme/black-men/"
url_men_intagram1 = "https://www.instagram.com/explore/tags/portraithomme/"



req = requests.get(url_men_pinterest_black_men)
soup = BeautifulSoup(req.text, 'html.parser')
print(req.status_code)

images = soup.find_all('img')
print(len(images))

for image in images:
    print(image['src'])