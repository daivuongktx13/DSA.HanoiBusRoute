import ast

f1=open("Distance/walking-s1.txt",'r')
f2=open("Distance/walking-s2.txt",'r')
f3=open("Distance/walking-s3.txt",'r')
f4=open("Distance/walking-s4.txt",'r')

d1=ast.literal_eval(f1.read())
d2=ast.literal_eval(f2.read())
d3=ast.literal_eval(f3.read())
d4=ast.literal_eval(f4.read())

print(1,'-',len(d1.keys()))
print(2,'-',len(d2.keys()))
print(3,'-',len(d3.keys()))
print(4,'-',len(d4.keys()))

d={**d1,**d2,**d3,**d4}
print("Total: ",len(d.keys()))

f5=open("Distance/walkingFinal.txt",'w')
print(d,file=f5)
f5.close()

