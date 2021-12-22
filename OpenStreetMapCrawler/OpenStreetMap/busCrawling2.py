import overpy
api = overpy.Overpass()
import crawlingUtils as cU
import time

queryRelation="""<osm-script timeout="600">
  <query type="relation">
    <bbox-query s="20.5590" n="21.5495" w="104.9533" e="106.4548"/>
    <id-query ref="***" type="relation"/>
  </query>
  <recurse type="relation-node"/>
  <print order="quadtile"/>
</osm-script>
"""

f=open("Data/route.txt","w")
f0=open("Data/line.txt","r") ##
f1=open("Data/bus_stop_route.txt","w")
f3=open("Data/bus_stop_name.txt","w",encoding='utf-8')
f4=open("Data/bus_stop_location.txt","w")
f5=open("Data/bus_stop_location_bus.txt","w")
listLine=[]

n=int(f0.readline())
for i in range(n):
  listLine.append([s.strip() for s in f0.readline().split(sep="-")])


dictionary=dict()
lonLatDictOfLine=dict()
lonLatDictOfBus=dict()
route=dict()
#
bus_stop_name=dict()
for pair in listLine:
  pair[0]=int(pair[0])
  if pair[1] not in cU.listAccepted:
    continue
  result=api.query(queryRelation.replace("***",str(pair[0])))
  route[pair[0]]=[]
  print(pair[0])
  lonLatDictOfLine[pair[0]]=[]
  nodes=result.nodes
  for node in nodes:
    name=node.tags
    if 'name' in str(name):
      bus_stop_name[node.id]=name['name']
    else:
      bus_stop_name[node.id]=" "
    #
    if node.id not in dictionary.keys():
      dictionary[node.id]=[pair[1]]
    else:
      dictionary[node.id].append(pair[1])
    #
    lonLatDictOfLine[pair[0]].append([float(node.lon),float(node.lat)])
    lonLatDictOfBus[node.id]=[float(node.lon),float(node.lat)]
    route[pair[0]].append(node.id)
#
print("Creating route.txt")
print(route,file=f)
#
print("Creating bus_stop_routes.txt")
print(dictionary,file=f1)
#
print("Creating bus_stop_name.txt")
print(bus_stop_name,file=f3)
#
print("Creating bus_stop_location.txt")
print(lonLatDictOfLine,file=f4)
#
print("Creating bus_stop_location_bus.txt")
print(lonLatDictOfBus,file=f5)

  
f5.close()
f0.close()
f1.close()
f4.close()
f3.close()
f.close()



