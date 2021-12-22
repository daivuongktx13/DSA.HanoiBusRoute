import ast

f = open("Data/bus_stop_location_bus.txt",'r')
f1= open("Data/route_main.txt",'r')

busStopLocations=ast.literal_eval(f.read())
f.close()
routes=ast.literal_eval(f1.read())
f1.close()

nearestDistance=dict()

from geopy import distance

# coords_1 = (21.0028706,105.7999062)
# coords_2 = (21.0066991,105.7967832)

# print(distance.distance(coords_1,coords_2).m)
keys=list(routes.keys())
for i in range(len(keys)-1):
    listBusStop1=routes[keys[i]]
    for j in range(i+1,len(keys)):
        print(i,j)
        listBusStop2=routes[keys[j]]
        #Consider i j
        distanceMatrix=dict()
        for bStop1 in listBusStop1:
            for bStop2 in listBusStop2:
                if bStop1 == bStop2:
                    continue
                coords_1=(busStopLocations[bStop1][1],busStopLocations[bStop1][0])
                coords_2=(busStopLocations[bStop2][1],busStopLocations[bStop2][0])
                ds=distance.distance(coords_1,coords_2).m
                distanceMatrix[(bStop1,bStop2)]=ds
                distanceMatrix[(bStop2,bStop1)]=ds
        for bStop1 in listBusStop1:
            minNumber=10000000
            minIndex=-1
            for bStop2 in listBusStop2:
                if bStop1 == bStop2:
                    continue
                if distanceMatrix[(bStop1,bStop2)]<minNumber:
                    minNumber=distanceMatrix[(bStop1,bStop2)]
                    minIndex=bStop2
            nearestDistance[(bStop1,minIndex)]=minNumber
        for bStop2 in listBusStop2:
            minNumber=10000000
            minIndex=-1
            for bStop1 in listBusStop1:
                if bStop2 == bStop1:
                    continue
                if distanceMatrix[(bStop2,bStop1)]<minNumber:
                    minNumber=distanceMatrix[(bStop2,bStop1)]
                    minIndex=bStop1
            nearestDistance[(bStop2,minIndex)]=minNumber
f2= open("Distance/distaceByWalk.txt","w")
print(nearestDistance,file=f2)
f2.close()  




