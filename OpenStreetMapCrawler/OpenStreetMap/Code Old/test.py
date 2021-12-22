import overpy
api = overpy.Overpass()
import test3 as dUtis
# result=api.query("""<query type="node">
#   <newer than="2021-01-01T00:00:00Z"/>
#   <has-kv k="highway" v="bus_stop"/>
#   <bbox-query s="21.00108" n="21.00239" w="105.84268" e="105.84518"/>
# </query>
# <print mode="meta"/>""")



result=api.query("""<query type="relation">
  <has-kv k="route" v="bus"/>
  <bbox-query s="20.5590" n="21.5495" w="104.9533" e="106.4548"/>
</query>
<print/>
""")
queryNode="""<osm-script>
  <id-query ref="***" type="node"/>
  <print/>
</osm-script>"""

f=open("route.txt","w")
f1=open("bus_stop.txt","w")
f2=open("distance.txt","w")

def getDistanceDrivingCar_1(node1, node2):
  result_temp1=api.query(queryNode.replace("***",str(node1)))
  result_temp2=api.query(queryNode.replace("***",str(node2)))
  lon1=str(result_temp1.nodes[0].lon)
  lat1=str(result_temp1.nodes[0].lat)
  lon2=str(result_temp2.nodes[0].lon)
  lat2=str(result_temp2.nodes[0].lat)
  distance=dUtis.getDistanceDrivingCar(lon1,lat1,lon2,lat2)
  return distance
def getDistanceWalking_1(node1, node2):
  result_temp1=api.query(queryNode.replace("***",str(node1)))
  result_temp2=api.query(queryNode.replace("***",str(node2)))
  lon1=str(result_temp1.nodes[0].lon)
  lat1=str(result_temp1.nodes[0].lat)
  lon2=str(result_temp2.nodes[0].lon)
  lat2=str(result_temp2.nodes[0].lat)
  distance=dUtis.getDistanceWalking(lon1,lat1,lon2,lat2)
  return distance

dictionary=dict()
dictionaryRoute=dict()
#
print("Creating route.txt")
for i,relation in enumerate(result.relations):
  print(relation.id,relation.tags['ref'],sep="|",file=f)
  nodes= list()
  for member in relation.members:
      if "platform" in str(member):
          nodes.append(member)
  dictionaryRoute[str(relation.id)]=nodes
  print(len(nodes),end=" ",file=f)
  for node in nodes:
    print(node.ref,end=" ",file=f)
    if node.ref not in dictionary.keys():
      dictionary[node.ref]=[relation.tags['ref']]
    else:
      dictionary[node.ref].append(relation.tags['ref'])
  print("",file=f)
#
print("Creating bus_stop.txt")
for key in dictionary.keys():
  print(key,end="|",file=f1)
  print(len(dictionary[key]),end='|',file=f1)
  for ref in dictionary[key]:
    print(ref,end=" ",file=f1)
  print("",file=f1)
#
print("Creating distance.txt")
#For each route
count=0
for key in dictionaryRoute.keys():
  routeList=dictionaryRoute[key]
  for i in range(len(routeList)-1):
    distance=getDistanceDrivingCar_1(routeList[i].ref,routeList[i+1].ref)
    count+=1
    print(routeList[i],routeList[i+1],distance,sep=" ",file=f2)
print("Complete 1st stage")
for i in range(len(dictionaryRoute.keys())-1):
  keys=dictionaryRoute.keys()
  for j in range(i+1,len(dictionaryRoute.keys())):
    #Consider 1 to 2
    for nodeId1 in dictionaryRoute[keys[i]]:
      nodeIndex=[]
      distanceVal=[]
      for nodeId2 in dictionaryRoute[keys[j]]:
        if nodeId2 not in dictionaryRoute[keys[i]]:
          distance=getDistanceWalking_1(nodeId1,nodeId2)
          nodeIndex.append(nodeId2)
          distanceVal.append(distance)
      minVal=min(distanceVal)
      selectedNode=nodeIndex[distanceVal.index(minVal)] 
      print(nodeId1,selectedNode,minVal,sep=" ",file=f2)
    #Consider 2 to 1
    for nodeId2 in dictionaryRoute[keys[j]]:
      nodeIndex=[]
      distanceVal=[]
      for nodeId1 in dictionaryRoute[keys[i]]:
        if nodeId1 not in dictionaryRoute[keys[j]]:
          distance=getDistanceWalking_1(nodeId2,nodeId1)
          nodeIndex.append(nodeId1)
          distanceVal.append(distance)
      minVal=min(distanceVal)
      selectedNode=nodeIndex[distanceVal.index(minVal)] 
      print(nodeId2,selectedNode,minVal,sep=" ",file=f2)
print("Complete 2nd stage")
    


f.close()
f1.close()
f2.close()