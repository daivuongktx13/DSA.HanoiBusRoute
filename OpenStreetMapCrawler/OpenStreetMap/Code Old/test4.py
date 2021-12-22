import ast

f=open("Distance/distanceInLine.txt",'r')
f1=open("Data/route_main.txt",'r')
f2=open("Distance/distanceInLine2.txt",'w')

lineDistance=ast.literal_eval(f.read())
lineRoutes=ast.literal_eval(f1.read())



for key in lineDistance.keys():
    alist=list()
    alist.append(lineDistance[key])
    alist.append(0)
    alist.append([])
    lineDistance[key]=alist

for key in lineRoutes.keys():
    routes=lineRoutes[key]
    for i in range(len(routes)-1):
        busStop1=routes[i]
        busStop2=routes[i+1]
        lineDistance[(busStop1,busStop2)][1]+=1
        lineDistance[(busStop1,busStop2)][2].append(key)
print(lineDistance,file=f2)
f2.close()
f1.close()
f.close()