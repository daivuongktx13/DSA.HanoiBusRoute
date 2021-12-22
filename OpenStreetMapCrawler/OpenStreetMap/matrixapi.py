

url1='https://api.distancematrix.ai/maps/api/distancematrix/json?origins=51.4822656,-0.1933769&destinations=51.4994794,-0.1269979&key=HBF1IRcxDadIgsujBlX5vqZojjcXF'

import requests



result=requests.get(url=url1)
print(result)
result.json()['rows'][0]['elements'][0]['distance']['value']