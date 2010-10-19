from os import system


for i in range(32,512,32):
	print "time ./integral "+str(i)
	system("time ./integral "+str(i))
