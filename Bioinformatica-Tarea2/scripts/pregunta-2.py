# -*- coding: utf-8 -*-

from random import randint
from numpy import mean, std, array
bases = ["A","C","G","T","B","D"]
sec_size = 200

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
		if len(sec)-1 >= 0:
			if r == 0:
				sec.insert(randint(0,len(sec)-1),bases[randint(0,5)])
			elif r == 1:
				sec.pop(randint(0,len(sec)-1))
			elif r == 2:
				sec[randint(0,len(sec)-1)] = bases[randint(0,5)]
		elif len(sec)-1 == 0 and r == 0:
			sec.append(bases[randint(0,5)])
			
	return sec

def distancia(ini,sec):
	'''
	Distancia de Levenshtein entre la secuencia inicial y la actual
	(implementando Needleman-Wunsch)
	'''
	# Duda: La distancia de LEvenshtein vendría siendo la misma cantidad de  mutaciones.
	# Duda: Needleman-Wunch me entrega las secuencias para ver que tan iguales son
	#		Por lo tanto no afectaria en el valor de la distancia
	#		El algoritmo está como un modulo en  python
	#			http://pypi.python.org/pypi/nwalign/0.1.3
	a = 1
	return a

#Generar una secuencia, y aplicar M mutaciones; para M entre 0 y 300, graﬁque la relacion
#entre M y D, donde D es la distancia de Levenshtein entre la secuencia ﬁnal y la secuencia
#inicial.

s = generar_secuencia()
ini = s
d = []
for i in range(300):
	s = mutacion(s,i)
	d.append(distancia(ini,s))
	

#Genere una secuencia, clonela, y a cada copia apliquele M mutaciones (de modo que
#tendra dos secuencias crecientemente distintas). Graﬁque la relacion entre M y D’, donde
#D’ es la distancia entre las dos secuencias que estan mutando.

s = generar_secuencia()
ini = s
m = 300 # Duda: será 300 o un numero entre 0 y 300?
s = mutacion(s,m)
d = distancia(ini,s)


#Genere 10.000 pares de secuencias (largo 200 c/u) y evalue su distancia de Levenshtein;
#haga un histograma de la distribucion de estos valores, y calcule media y desviacion estandar.

sec1 = []
sec2 = []
d = []
for i in range(100):
	sec1.append(generar_secuencia())
	sec2.append(generar_secuencia())
	d.append(distancia(sec1[i],sec2[i]))

distance_mean = array(d).mean()
distance_standard_deviation = array(d).std()

#Considerando (b) y (c), ¿por sobre que valor de M diria usted que el parentesco entre las
#secuencias es indetectable?

