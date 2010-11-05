# -*- coding: utf-8 -*-
from os import system

bases = ["A","C","T","G"]

def parse_file(file_name):
	f = open(file_name,"r")
	file_bases = []
	while 1:
		line = f.readline()
		if not line:
			break
		else:
			for i in line:
				if i in ["a","t","c","g"]:
					file_bases.append(i)
	f.close()
	return file_bases

def is_palindrome(sec):
	'''
	Verifica si una secuencia dada es un palindromo o no
	'''
	tmp_set = set()
	result = True
	for i in range(len(sec)/2):
		tmp_set.add(sec[i])
		tmp_set.add(sec[::-1][i])
		if not set(["a","t"]).issubset(tmp_set) and \
			not set(["c","g"]).issubset(tmp_set):
			result = False
		tmp_set.clear()	
	return result

def generate_subsequences_and_verify(sequence):
	top_ten = []
	for i in range(2,len(sequence)-1):
		system("clear")
		print str(i)+"/"+str(len(sequence)-2)
		for j in range(len(sequence)-1):
			if len(sequence[j:j+i]) == i:
				if is_palindrome(sequence[j:j+i]):
					top_ten.append(sequence[j:j+i])
	print "Ten bigger palindromes:"
	return top_ten[::-1][:10]


#tmp_l = parse_file("secuencia.txt")
tmp_l = parse_file("sec.txt")
raw_input("Press any key to start the palindrome search...")
print generate_subsequences_and_verify(tmp_l)

