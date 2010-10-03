#!/bin/env python
# Generate dotPlot of two sequences
#
# Use:
#  python dp.py seq1 seq2
#
# where seq{1,2} are files with the sequence inside
import sys

l1=[];
l2=[];

def read_seqs(file1,file2):
	f1 = open(file1)
	f2 = open(file2)
	l1.append(f1.readline().replace("\n",""))
	l2.append(f2.readline().replace("\n",""))
	f1.close()
	f2.close()

def print_tex(x,y):
	print "\\begin{tabular}{|"+"p{0.0025cm}|"*(len(x)-1)+"}"
	print "\\hline"
	for i in x[0:len(x)-2]:
		print i+" &",
	print x[len(x)-1]+"\\\\\\hline"

	for j in y:
		print j,
		for k in x[1:len(x)]:
			if j == k:
				print "& *",
			else:
				print "&  ",
		print "\\\\\\hline"
	print "\\end{tabular}"	


try:
	arg1 = sys.argv[1]
	arg2 = sys.argv[2]

except IndexError:
	print "error"

read_seqs(arg1, arg2)
l1 = " "+l1[0]
l2 = l2[0]
print_tex(l1,l2)
