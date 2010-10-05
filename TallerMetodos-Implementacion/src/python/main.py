#!/bin/env python
# -*- coding: utf-8 -*-

#from lib.extra import read_file
#from lib.extra import *
import lib.clonal as clonal

clonal.lib.read_file("input")

print clonal.lib.carNumber
print clonal.lib.optNumber
print clonal.lib.typeNumber
print clonal.lib.types


clonal.population_init()
#    Generar repertorio inicial R
#    Bucle generaciones
#      R* = Seleccionar(n,R) //prop. fitness
#      C  = Clonacion(B, R*) //prop. fitness
#      C* = Hipermutacion(C) //inv prop. fitness
#      C* = Evaluacion(C*)
#      R* = Seleccion(n,C*) // prop. fitness
#      R  = Insercion(R*)
#      D  = Generacion(d)
#      R  = Reemplazo(fitness, D)

#input   : S = set of patterns to be recognised, n the number of worst elements to select for removal
#output  : M = set of memory detectors capable of classifying unseen patterns
#
#begin
#    
#   Create an initial random set of antibodies, A 
#    
#   forall  patterns in S   do         
#      Determine the affinity with each antibody in A 
#      Generate clones of a subset of the antibodies in A  with the highest affinity. 
#         The number of clones for an antibody is proportional to its affinity             
#      Mutate attributes of these clones to the set A , and place a copy of the highest 
#         affinity antibodies in A  into the memory set, M
#      Replace the n lowest affinity antibodies in A with new randomly generated antibodies
#   end 
#  
#end 

