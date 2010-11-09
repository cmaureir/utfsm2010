from os import system

cr_1 , cr_2, cr_3 = [], [], [];
cf_1 , cf_2, cf_3 = [], [], [];
fit_1 , fit_2, fit_3 = [], [], [];
time_1 , time_2, time_3 = [], [], [];

total_time_1 = 0
total_time_2 = 0
total_time_3 = 0

f1, f2, f3  = open("pb_200_01.res.4","r"),  open("pb_200_09.res.4","r"),  open("pb_200_10.res.4","r")

while 1:
	line = f1.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		cr_1.append(float(tmp[0]))
		cf_1.append(float(tmp[1]))
		fit_1.append(int(tmp[2]))
		time_1.append(float(tmp[3]))
		total_time_1 = total_time_1 + float(tmp[3])

while 1:
	line = f2.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		cr_2.append(float(tmp[0]))
		cf_2.append(float(tmp[1]))
		fit_2.append(int(tmp[2]))
		time_2.append(float(tmp[3]))
		total_time_2 = total_time_2 + float(tmp[3])


while 1:
	line = f3.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		cr_3.append(float(tmp[0]))
		cf_3.append(float(tmp[1]))
		fit_3.append(int(tmp[2]))
		time_3.append(float(tmp[3]))
		total_time_3 = total_time_3 + float(tmp[3])

f1.close()
f2.close()
f3.close()

fit_1.sort()
fit_2.sort()
fit_3.sort()

system("cat pb_200_01.res.4 | grep \"\ "+str(fit_1[0])+"\ \"")
print "Tiempo Total: "+str(total_time_1)
print
system("cat pb_200_09.res.4 | grep \"\ "+str(fit_2[0])+"\ \"")
print "Tiempo Total: "+str(total_time_2)
print
system("cat pb_200_10.res.4 | grep \"\ "+str(fit_3[0])+"\ \"")
print "Tiempo Total: "+str(total_time_3)

