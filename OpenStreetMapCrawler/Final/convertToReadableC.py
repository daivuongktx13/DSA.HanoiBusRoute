import ast
#
f1=open("lineName.txt",'r')
lineName=ast.literal_eval(f1.read())
f1_c=open("C/lineName.txt",'w')
print(len(lineName.keys()),file=f1_c)
for key in lineName.keys():
    print(key,lineName[key],sep=' ',file=f1_c)
f1_c.close()
f1.close()
#
f2=open("busStopName.txt",'r',encoding='utf-8')
busStopName=ast.literal_eval(f2.read())
f2_c=open("C/busStopName.txt",'w',encoding='utf-8')
print(len(busStopName.keys()),file=f2_c)
for key in busStopName.keys():
    print(key,busStopName[key],sep=' ',file=f2_c)
f2_c.close()
f2.close()
#
f3=open("route.txt",'r')
route=ast.literal_eval(f3.read())
f3_c=open("C/route.txt",'w')
print(len(route.keys()),file=f3_c)
for key in route.keys():
    print(key,len(route[key]),file=f3_c)
    for busStop in route[key]:
        print(busStop,end=' ',file=f3_c)
    print('',file=f3_c)
f3_c.close()
f3.close()
#
f4=open("routeDistance.txt",'r')
routeDistance=ast.literal_eval(f4.read())
f4_c=open("C/routeDistance.txt",'w')
print(len(routeDistance.keys()),file=f4_c)
for key in routeDistance.keys():
    print(key[0],key[1],routeDistance[key][0],sep=' ',file=f4_c)
    print(routeDistance[key][1],end=' ',file=f4_c)
    for line in routeDistance[key][2]:
        print(line,end=' ',file=f4_c)
    print('',file=f4_c)
f4.close()
f4_c.close()
#
f5=open("busStop_Routes.txt",'r')
busStop_Routes=ast.literal_eval(f5.read())
f5_c=open("C/busStop_Routes.txt",'w')
print(len(busStop_Routes.keys()),file=f5_c)
for key in busStop_Routes.keys():
    print(key,file=f5_c)
    print(len(busStop_Routes[key]),end=' ',file=f5_c)
    for route in busStop_Routes[key]:
        print(route,end=' ',file=f5_c)
    print('',file=f5_c)
f5.close()
f5_c.close()
#
f6=open("walkingDistance.txt",'r')
walkDistance=ast.literal_eval(f6.read())
f6_c=open("C/walkingDistance.txt",'w')
print(len(walkDistance.keys()),file=f6_c)
for key in walkDistance.keys():
    print(key[0],key[1],walkDistance[key],sep=' ',file=f6_c)
f6.close()
f6_c.close()









