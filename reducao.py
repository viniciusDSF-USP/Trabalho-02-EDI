import numpy as np

M = np.array([
[-4,-4,-2,-2],
[-4,-4,-2,-2],
[2,2,-2,4],
[2,2,4,-2]
])

print(M,'\n')

def mult(M, i, a):
	M[i-1] = M[i-1]*a

def soma(M, i1, i2, a=None):
	if a == None:
		M[i1-1] += M[i2-1]
	else:
		M[i1-1] += M[i2-1]*a

def swap(M, i1, i2, det=False):
	if det:
		M[i1-1], M[i2-1] = M[i2-1], -M[i1-1]
	else:
		M[i1-1], M[i2-1] = M[i2-1], M[i1-1]

M = M/2
soma(M, 2, 1,-1)
mult(M,3,2); soma(M, 3, 1); mult(M,3,1/3)
mult(M,4,2); soma(M, 4, 1); mult(M,4,1/3)

soma(M, 1, 4); mult(M, 1, -1/2)
soma(M, 3, 4); mult(M, 4, -1)

print(M,'\n')