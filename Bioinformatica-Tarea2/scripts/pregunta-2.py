# -*- coding: utf-8 -*-

from random import randint
from numpy import mean, std, array, zeros
import nwalign as nw
import matplotlib.pyplot as p
from pylab import *
import matplotlib.mlab as mlab

if len(sys.argv) != 2:
	print "Error"
	print "Ejecutar:      python pregunta-2.py [opcion]"
	print "Opciones:\n"
	print "\t 1\t\t Parte 1"
	print "\t 2\t\t Parte 2"
	print "\t 3\t\t Parte 3"


bases = ["A","C","G","T","B","D"]
sec_size =20#0
m = 30#0
m_list = []
for i in range(m+1):
	m_list.append(i)

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
if sys.argv[1] == "1":
	print "Pregunta 1..."
	sec_ini = generar_secuencia()
	d, d_matrix, sec_mut  = [], [], []
	sec_mut = sec_ini
	tmp1 = "".join(sec_ini)
	for i in range(m+1):
		sec_mut = mutacion(sec_mut,i)
		tmp2 = "".join(sec_mut)
		align = nw.global_align(tmp1,tmp2)
		matrix,distance =distancia(align[0],align[1])
		d.append(distance)
		d_matrix.append(matrix)
		tmp2 = ""

	p.show()
	plot1 = p.plot(m_list,d)
	title(u'Distancia vs Número de mutaciones')
	grid(True)
	p.axis([0,m,0,max(d)+1],0.01)
	xlabel(u'Número de mutaciones')
	ylabel('Distancia')
	p.show()

# 2
elif sys.argv[1] == "2":
	print "Pregunta 2..."
	sec_1 = generar_secuencia()
	sec_2 = []
	sec_2 = sec_1
	d2 , d2_matrix = [], []
	tmp1 = "".join(sec_1)
	
	for i in range(m+1):
		sec_2 = mutacion(sec_2,i)
		tmp2 = "".join(sec_2)
		align = nw.global_align(tmp1,tmp2)
		matrix,distance =distancia(align[0],align[1])
		d2.append(distance)
		d2_matrix.append(matrix)
		tmp2 = ""
	
	plot2 = p.plot(m_list,d2)
	title(u'Distancia entre secuencias vs Número de mutaciones')
	grid(True)
	p.axis([0,m,0,max(d2)+1],0.01)
	xlabel(u'Número de mutaciones')
	ylabel('Distancia entre secuencias')
	p.show()


# 3
elif sys.argv[1] == "3":
	print "Pregunta 3..."
	s1, s2, d3, d3_matrix = [], [], [], []
	for i in range(10000):
		s1 = generar_secuencia()
		s2 = generar_secuencia()
		tmp1 = "".join(s1)
		tmp2 = "".join(s2)
		align = nw.global_align(tmp1,tmp2)
		matrix,distance =distancia(align[0],align[1])
		d3.append(distance)
		d3_matrix.append(matrix)
	distance_mean = array(d3).mean()
	distance_standard_deviation = array(d3).std()
	print "Mean:" + str(distance_mean)
	print "Std:" + str(distance_standard_deviation)
	
	# the histogram of the data
	n, bins, patches = p.hist(d3, 50, normed=1, facecolor='green', alpha=0.75)
	
	p.xlabel('Distancia entre secuencias')
	p.ylabel('Probabilidad')
	p.title('Histograma')
	p.axis([min(d3),max(d3),0,0.16])
	p.grid(True) 
	p.show()
