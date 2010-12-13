from numpy import average

f = open("results","r")
ave = []
tmp = []
while 1:
	line = f.readline()
	if not line: break
	if len(tmp) == 10:
		print average(tmp)
		tmp = []
	tmp.append(float(line.split(" ")[1].replace("\n","")))
	print  line.split(" ")[0].replace("\n","")
