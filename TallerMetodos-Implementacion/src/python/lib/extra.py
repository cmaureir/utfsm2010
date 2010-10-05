#!/bin/env python
# -*- coding: utf-8 -*-

# Global Variables
carNumber = optNumber = typeNumber = 0
types = []

# Tamaño poblacion
pop = 10
# Número de generaciones
gens = 20


class genotype():
	def __init__(self,gene):
		self.gene = gene # Automoviles

	def set_fitness(self,fitness):
		self.fitness = fitness # Valor evaluacion de la FO

	def set_fail(self,fail):
		self.fail = fail # Cantidad de restricciones blandas insatisfechas

	def set_rfitness(self,rfitness):
		self.rfitness = rfitness # fitness relativo

	def set_cfitness(self,cfitness):
		self.cfitness = cfitness # fitness acumulado

population = []  #genotype() # poblacion actual
newPop = [] #genotype() # nueva poblacion en formacion
tmpPop = [] #genotype() # poblacion temporal


# Read File

def read_file(filename):
	global carNumber, optNumber, typeNumber, types
	i,j,tmp = 0, 0, 0
	f = open(filename,"r")

    # Primera linea
    # Numero de Autos - Numero de Opciones - Numero de Tipos de Autos.
	line = f.readline().replace("\n","").split(" ")
	carNumber, optNumber, typeNumber = int(line[0]), int(line[1]), int(line[2])

	# Segunda linea
    # cantidad de autos permitidos en la subsecuencia con la opción i
	tmp = f.readline().replace("\n","").split(" ")
	numMaxCarOptSeq =  list(int(a) for a in tmp if a.isdigit())

    # Tercera linea
    # tamaño de la subsecuencia i
	tmp = f.readline().replace("\n","").split(" ")	
	sizeMaxCarOptSeq = list(int(a) for a in tmp if a.isdigit())

    # Resto de lineas
    # Tipo de auto - Cantidad de autos que la tienen - Tiene la opcion i (1 o 0)
	for i in range(0,typeNumber):
		line = f.readline().replace("\n","").split(" ")
		types.append(list(int(a) for a in line if a.isdigit()))

	# Cerrar archivo
	f.close()

def print_file():
	pass

def check_file():
	pass
