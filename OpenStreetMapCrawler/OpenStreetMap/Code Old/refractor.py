import ast

f=open("Data/Main/bus_stop_location","w")
f2 =open("Data/route_main.txt","r")
f3=open("Data/bus_stop_location_bus.txt","r")
routes=f2.read()
busLocation=f3.read()

routes=ast.literal_eval(routes)
busLocation=ast.literal_eval(busLocation)

for key in routes.keys():
    listBusStop=routes[key]
    for i in range(len(listBusStop)):
        listBusStop[i]=busLocation[listBusStop[i]]
    routes[key]=listBusStop
print(routes,file=f)
f3.close()
f.close()
f2.close()