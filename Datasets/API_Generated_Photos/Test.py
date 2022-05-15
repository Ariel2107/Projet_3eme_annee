import requests

url = "https://selfie2id.p.rapidapi.com/run"

payload = {
	"touchup_val": 0.5,
	"tidyup_val": 0.5,
	"makeup_val": 0,
	"bg_color": "gray",
	"id_size": "2.56x2.56",
	"image": "https://images.generated.photos/KrGwydGvFOgxYU3kzkwKzWpuXa8V99Z8zCzw3DP-rwg/rs:fit:256:256/czM6Ly9pY29uczgu/Z3Bob3Rvcy1wcm9k/LnBob3Rvcy92M18w/MjQwMzAzLmpwZw.jpg"
}
headers = {
	"content-type": "application/json",
	"X-RapidAPI-Host": "selfie2id.p.rapidapi.com",
	"X-RapidAPI-Key": "dac970184fmsha8a673dd9ed073ep141226jsn40edc4ac73b0"
}

response = requests.request("POST", url, json=payload, headers=headers)

print(response.text)