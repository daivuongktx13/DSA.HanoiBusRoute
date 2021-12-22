import requests
import json


def getDistanceDrivingCar(lon1,lat1,lon2,lat2):
    bodyString= '{"locations":[[lon1,lat1],[lon2,lat2]],"metrics":["distance"]}'
    bodyString=bodyString.replace("lon1",lon1)
    bodyString=bodyString.replace("lat1",lat1)
    bodyString=bodyString.replace("lon2",lon2)
    bodyString=bodyString.replace("lat2",lat2)
    body=json.loads(bodyString)
    headers = {
        'Accept': 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8',
        'Authorization': '5b3ce3597851110001cf6248b50e9cc8efe54d6cbf9101f734dda74e',
        'Content-Type': 'application/json; charset=utf-8'
    }
    call = requests.post('https://api.openrouteservice.org/v2/matrix/driving-car', json=body, headers=headers)
    print(call.status_code, call.reason)
    return call.json()['distances'][0][1]


def getDistanceWalking(lon1,lat1,lon2,lat2):
    bodyString= '{"locations":[[lon1,lat1],[lon2,lat2]],"metrics":["distance"]}'
    bodyString=bodyString.replace("lon1",lon1)
    bodyString=bodyString.replace("lat1",lat1)
    bodyString=bodyString.replace("lon2",lon2)
    bodyString=bodyString.replace("lat2",lat2)
    body=json.loads(bodyString)
    headers = {
        'Accept': 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8',
        'Authorization': '5b3ce3597851110001cf6248b50e9cc8efe54d6cbf9101f734dda74e',
        'Content-Type': 'application/json; charset=utf-8'
    }
    call = requests.post('https://api.openrouteservice.org/v2/matrix/foot-walking', json=body, headers=headers)
    print(call.status_code, call.reason)
    return call.json()['distances'][0][1]


