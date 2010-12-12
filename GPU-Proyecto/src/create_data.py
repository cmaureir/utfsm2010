from random import randint
import sys

if sys.argv[1] != "":
	for i in range(int(sys.argv[1])):
		print randint(-100,100),
