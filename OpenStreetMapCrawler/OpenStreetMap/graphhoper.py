import requests
url="https://graphhopper.com/api/1/route?point=51.131,12.414&point=48.224,3.867&profile=foot&key=api_key"
url=url.replace("api_key","ab88ee2d-373c-4893-93ae-42267afbcd14")
result=requests.get(url=url)