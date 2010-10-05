import lib.extra as lib
import random


def population_init():
	p = []

	for i in range(lib.typeNumber):
		for j in range(lib.types[i][1]):
			p.append(i)

	for i in range(lib.pop):
		random.shuffle(p)
		lib.population.append(lib.genotype(p))
		print i
		print lib.population[i].gene

	print "\n"
	for i in lib.population:
		print i.gene

def selection():
	pass

def clonation():
	pass

def hypermutation():
	pass

def evaluation():
	pass

def clonal_selection():
	pass

def clonal_insertion():
	pass

def generation():
	pass

def replacement():
	pass
	
