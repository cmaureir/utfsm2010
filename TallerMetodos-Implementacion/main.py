#!/bin/env python
# -*- coding: utf-8 -*-

carNumber, optNumber, typeNumber = 0, 0, 0
types = array([],[])

def read_file(filename):
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

    #// Resto de lineas
    #// Tipo de auto - Cantidad de autos que la tienen - Tiene la opcion i (1 o 0)
	for i in range(0,typeNumber):
		line = f.readline().replace("\n","").split(" ")
		types[i][0] = line[0]
		types[i][1] = line[1]
		for j in range(0,optNumber):
			types[i][j+2] = line[j+2]
	f.close()
	print types

read_file("input")
