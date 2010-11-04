# -*- coding: utf-8 -*-

bases = ["A","C","T","G"]

def is_palindrome(sec):
	'''
	Verifica si una secuencia dada es un palindromo o no
	'''
	tmp_set = set()
	result = True
	for i in range(len(sec)/2):
		tmp_set.add(sec[i])
		tmp_set.add(sec[::-1][i])
		if not set(["A","T"]).issubset(tmp_set) and not set(["C","G"]).issubset(tmp_set):
			result = False
		tmp_set.clear()	
	return result

tmp_sec = ["A","T","C","G","A","T"]

top_ten = []
print tmp_sec

for i in range(2,len(tmp_sec)-1):
	for j in range(len(tmp_sec)-1):
		if len(tmp_sec[j:j+i]) == i:
			if is_palindrome(tmp_sec[j:j+i]):
				top_ten.append(tmp_sec[j:j+i])	

print top_ten
print top_ten[::-1][:10]
