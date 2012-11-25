#!/usr/bin/env python
# Tarea Genoma y Ensamblado
# Objetivo: Dado una secuencia de ADN pasada como parametro (archivo texto plano)
# encontrar los 10 trozos que mas se repitan, de largo minimo 3 y maximo n, siendo
# n el largo total del ADN

import sys
from operator import itemgetter


def sateliteSearch(secuencia):
    """Busca secuencias repetidas"""
    n = len(secuencia)
    d = dict()
    # Crearemos trozos de largo 3 hasta n, buscando trozos repetidos
    for i in range(3, n+1):
    	for j in range(0, n-i):
    		# Utilizando los trozos encontrados como llaves de diccionario d (contador)
    		if secuencia[j:j+i] in d.keys():
    			d[secuencia[j:j+i]] += 1
    		else:
    			d[secuencia[j:j+i]] = 1
    # Ordenando diccionario por valores en su contenido (se hace una traduccion desde un 
    # diccinario d a una lista de tuplas, donde cada tupla es (llave, valor) correspondiente 
    # al diccionario original
    resultado = sorted(d.items(), key=itemgetter(0))
    resultado = sorted(resultado, key=itemgetter(1))
    return resultado


if __name__ == '__main__':
    # Comprobando argumentos
    if len(sys.argv) != 2:
    	print "Uso: " + sys.argv[0] + " <archivo>"
        sys.exit()
    
    # Leyendo archivo
    archivo = open(sys.argv[1], "r")
    secuencia = archivo.read()
    archivo.close()

    resultado = sateliteSearch(secuencia)
    
    resultado = resultado[::-1][:10]
    # Salida (10 trozos mas largos y repetidos de largo maximo n, hasta un minimo de 3
    for i in resultado:
    	print i
