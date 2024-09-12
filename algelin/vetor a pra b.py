import numpy as np 

d = int(input()) 
b1 = []
b2 = []

for i in range(d):
    linha = input() ; 
    linha = linha.strip().split(" ")
    novo = []
    for j in linha:
        novo.append(float(j))
    b1.append(novo) 

for i in range(d):
    linha = input() ; 
    linha = linha.strip().split(" ")
    novo = []
    for j in linha:
        novo.append(float(j))
    b2.append(novo) 

v = input()
v = v.strip().split(" ")
novo = []

for i in v:
    novo.append(float(i))

v = novo 

for j in v: 
    j = int(j)

v_b1 = np.array(b1).T 
v_b2 = np.array(b2).T
v = np.array(v) 

m_b1_b2 = np.dot(np.linalg.inv(v_b1), v_b2)
resp = np.dot(v, m_b1_b2)

for i in resp: 
    print("{:.4f}".format(i), end = " ")

print()
