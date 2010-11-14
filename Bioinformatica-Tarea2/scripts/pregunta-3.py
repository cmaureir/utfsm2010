# -*- coding: utf-8 -*-
from os import system
import time
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

def palin1(sequence):
	top_ten = []
	for i in range(2,len(sequence)-1):
		for j in range(len(sequence)-1):
			if len(sequence[j:j+i]) == i and i%2 == 0:
				if is_palindrome(sequence[j:j+i]):
					top_ten.append(sequence[j:j+i])
	return top_ten[::-1][:10]

def palin2(a):
	pals = []
	l = len(a)
	c = 0
	is_pal = False
	while c < len(a)-1:
	    for j in range(len(a)/2):
	        if c -j >= 0 and c+1 +j <= l-1:
	            tmp1 = set(["a","t"]).issubset(set([a[c-j],a[c+1+j]]))
	            tmp2 = set(["c","g"]).issubset(set([a[c-j],a[c+1+j]]))
	            if not tmp1 and not tmp2:
	                break
	            else:
	                ini = c-j
	                end = c+1+j
	                is_pal = True
	    if is_pal:
	        pals.append(a[ini:end+1])
	    is_pal = False
	    c = c + 1
		return sorted(pals,lambda a,b: cmp(len(a),len(b)))[::-1][:10]


tmp_l = parse_file("secuencia.txt")
#tmp_l = parse_file("sec.txt")
#s_time = time.time()

#print palin1(tmp_l)
#print time.time() - s_time, "sec"

s_time = time.time()
print palin2(tmp_l)
print time.time() - s_time, "sec"
