import ast
import crawlingUtils as cU
import time

f=open("Distance/walking-s3_nd.txt",'r')
distanceMatrix=ast.literal_eval(f.read())

f1=open("Data/bus_stop_location_bus.txt",'r')
busStopLocation=ast.literal_eval(f1.read())


distanceMatrixNew=dict()
count=0
listNode=[]
listLocation=[]
total=0
for key in distanceMatrix.keys():
    if total==200:
        break
    if count==25:
        distanceM=cU.getDistanceWalking(str(listLocation))
        time.sleep(2)
        for i in range(count*2):
            if i%2==0:
                distanceMatrixNew[(listNode[i],listNode[i+1])]=distanceM[i][i+1]
        count=0
        listNode=[]
        listLocation=[]
        total+=1
    listNode.append(key[0])
    listNode.append(key[1])
    listLocation.append(busStopLocation[key[0]])
    listLocation.append(busStopLocation[key[1]])
    count+=1
else:
    distanceM=cU.getDistanceWalking(str(listLocation))
    time.sleep(2)
    for i in range(count*2):
        if i%2==0:
            distanceMatrixNew[(listNode[i],listNode[i+1])]=distanceM[i][i+1]
    count=0
    listNode=[]
    listLocation=[]
    total+=1
for key in distanceMatrixNew.keys():
    distanceMatrix.pop(key)
f2=open("Distance/walking-s4.txt",'w')
print(distanceMatrixNew,file=f2)
f2.close()
f3=open("Distance/walking-s4_nd.txt",'w')
print(distanceMatrix,file=f3)
f3.close()






