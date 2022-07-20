import requests
import bs4
import urllib
import PIL

"""faces_url = "https://api.generated.photos/api/v1/faces?api_key=mqPGl9uMtjW-w31NxUM3vQ&param={gender=male})"
response = requests.get(faces_url)
print(response.text)


for images in response.json()['faces']:
    image = images['urls'][-1]
    value = image['512']
    img_name = value.split('/')[-1]
    try:
        PIL.Image.open(img_name)
    except:
        print("Nouvelle image !!!")
        print(img_name)
        urllib.request.urlretrieve(value, img_name)"""

i = 0
params = {
    "q": "batman wallpaper",
    "tbm": "isch",
    "content-type": "image/png",
}
req = requests.get("https://www.bing.com/images/search?q=selfie&form=HDRSC3&first=1&tsc=ImageHoverTitle", params=params)
soup = bs4.BeautifulSoup(req.text, 'html.parser')
images = soup.findAll('img')


for image in images:
    value = "https://www.bing.com/images/search?q=selfie&form=HDRSC3&first=1&tsc=ImageHoverTitle" + image['src']
    print(value)
    img_name = value.split('/')[-1]
    urllib.request.urlretrieve(value, img_name)
    i+=1




