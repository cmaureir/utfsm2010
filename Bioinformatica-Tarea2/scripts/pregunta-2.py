# -*- coding: utf-8 -*-

from random import randint
from numpy import mean, std, array, zeros
import nwalign as nw
import matplotlib.pyplot as p
from pylab import *

bases = ["A","C","G","T","B","D"]
sec_size =20#0
m = 30#0

def generar_secuencia():
	'''
	Genera una secuencia aleatoria de 200 bases
	equiprobables e independientes (ACGTBD)	
	'''
	sec = []
	for i in range(sec_size):
		sec.append(bases[randint(0,5)])
	return sec

def mutacion(sec,m):
	''' 
	Muta m veces una secuencia determinada con distintas formas:
		0: insercion
		1: borrado
		2: reemplazo
	'''
	for i in range(m):
		r = randint(0,2)
		if len(sec) > 0:
			if r == 0:
				sec.insert(randint(0,len(sec)),bases[randint(0,5)])
			elif r == 1:
				sec.pop(randint(0,len(sec)))
			elif r == 2:
				sec[randint(0,len(sec)-1)] = bases[randint(0,5)]
		elif len(sec) == 0 and r == 0:
			sec.append(bases[randint(0,5)])
	return sec

def distancia(s1,s2):
	'''
	Distancia de Levenshtein entre la secuencia inicial y la actual
	(implementando Needleman-Wunsch)
	'''
	if len(s1) > len(s2):
		s1, s2 = s2, s1
	if len(s2) == 0:
		return len(s1)
	m = len(s1) + 1
	n = len(s2) + 1
	d = zeros((m,n))
	for i in range(m):
		d[i][0] = i
	for j in range(n):
		d[0][j]=j
	for i in xrange(1, m):
		for j in range(1, n):
			deletion = d[i-1][j] + 1
			insertion = d[i][j-1] + 1
			substitution = d[i-1][j-1]
			if s1[i-1] != s2[j-1]:
				substitution += 1
			d[i][j] = min(insertion, deletion, substitution)

	return d,d[i-1][j-1]

# 1

sec_ini = generar_secuencia()
d, d_matrix, sec_mut  = [], [], []
sec_mut = sec_ini
tmp1 = "".join(sec_ini)
for i in range(m):
	sec_mut = mutacion(sec_mut,i)
	tmp2 = "".join(sec_mut)
	align = nw.global_align(tmp1,tmp2)
	matrix,distance =distancia(align[0],align[1])
	d.append(distance)
	d_matrix.append(matrix)
	tmp2 = ""

m_list = []
for i in range(m):
	m_list.append(i)

print "m: "+str(len(m_list))
print "d: "+str(len(d))
print m_list
print d
raw_input()
plot1 = p.plot(m_list,d,label='lala')
#
title('Distancia vs Numero de mutaciones')
legend((plot1),('lala'),loc='upper right')
grid(True)
p.axis([0,m,0,max(d)],0.01)
xlabel('Numero de mutaciones')
ylabel('Distancia')
p.show()



# 2
#s = generar_secuencia()
#ini = s
#m = 300 # Duda: sera 300 o un numero entre 0 y 300?
#s = mutacion(s,m)
#d = distancia(ini,s)


# 3
#
#sec1 = []
#sec2 = []
#d = []
#for i in range(100):
#	sec1.append(generar_secuencia())
#	sec2.append(generar_secuencia())
#	d.append(distancia(sec1[i],sec2[i]))
#
#distance_mean = array(d).mean()
#distance_standard_deviation = array(d).std()
#
# 4

