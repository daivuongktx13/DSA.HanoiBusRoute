
import ast
import time

import crawlingUtils as cU

f =open("Data/Main/bus_stop_location.txt","r")
f2 =open("Data/route_main.txt","r")

routes=f2.read()
routesLocation=f.read()

routes=ast.literal_eval(routes)
routesLocation=ast.literal_eval(routesLocation)
distanceDict=dict()
for key in routes.keys():
    route=routes[key]
    routeLocation=routesLocation[key]
    distanceMatrix=cU.getDistanceDrivingCar(str(routeLocation))
    time.sleep(2.5)
    for i in range(len(route)-1):
        dictTemp=(route[i],route[i+1])
        distanceDict[dictTemp]=distanceMatrix[i][i+1]

f3=open("Distance/distanceInLine.txt","w")

print(distanceDict,file=f3)
f3.close()
