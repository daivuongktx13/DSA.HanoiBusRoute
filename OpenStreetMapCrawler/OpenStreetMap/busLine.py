
import overpy
api = overpy.Overpass()
import crawlingUtils as cU
import time


result=api.query("""<query type="relation">
  <has-kv k="route" v="bus"/>
  <bbox-query s="20.5590" n="21.5495" w="104.9533" e="106.4548"/>
</query>
<print/>
""")


f=open("Data/line.txt","w")
print(len(result.relations),file=f)
for relation in result.relations:
    print(relation.id,relation.tags['ref'],sep="-",file=f)
f.close()

f1=open("Data/route_main.txt","w")
lineDict=dict()
for relation in result.relations:
  if relation.tags['ref'] not in cU.listAccepted:
    continue
  lineDict[relation.id]=[]
  mems=relation.members
  for mem in mems:
    if 'platform' in str(mem):
      lineDict[relation.id].append(mem.ref)
print(lineDict,file=f1)
f1.close()
