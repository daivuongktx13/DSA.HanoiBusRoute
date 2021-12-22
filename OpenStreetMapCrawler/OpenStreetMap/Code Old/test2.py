import crawlingUtils as cU
f0=open("Data/line.txt","r") ##
listLine=[]

n=int(f0.readline())
for i in range(n):
  listLine.append([s.strip() for s in f0.readline().split(sep="-")])

f0.close()