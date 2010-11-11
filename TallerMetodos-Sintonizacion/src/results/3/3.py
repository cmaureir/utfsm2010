import matplotlib.pyplot as p
from pylab import *

rr_1 , rr_2, rr_3 = [], [], [];
fit_1 , fit_2, fit_3 = [], [], [];
time_1 , time_2, time_3 = [], [], [];

total_time_1 = 0
total_time_2 = 0
total_time_3 = 0

f1, f2, f3  = open("pb_200_01.res.3.1","r"),  open("pb_200_09.res.3.1","r"),  open("pb_200_10.res.3.1","r")

while 1:
	line = f1.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		rr_1.append(int(tmp[0]))
		fit_1.append(int(tmp[1]))
		time_1.append(float(tmp[2]))
		total_time_1 = total_time_1 + float(tmp[2])

while 1:
	line = f2.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		rr_2.append(int(tmp[0]))
		fit_2.append(int(tmp[1]))
		time_2.append(float(tmp[2]))
		total_time_2 = total_time_2 + float(tmp[2])


while 1:
	line = f3.readline()
	if not line:
		break
	else:
		tmp = line.replace("\n","").split(" ")
		rr_3.append(int(tmp[0]))
		fit_3.append(int(tmp[1]))
		time_3.append(float(tmp[2]))
		total_time_3 = total_time_3 + float(tmp[2])

f1.close()
f2.close()
f3.close()

plot1 = p.plot(rr_1,fit_1,label='pb_200_01')
plot2 = p.plot(rr_1,fit_2,label='pb_200_09')
plot3 = p.plot(rr_1,fit_3,label='pb_200_10')

title('replaceRate vs fitness')
legend((plot1,plot2,plot3),('pb_200_01','pb_200_09','pb_200_10'),loc='upper left')
grid(True)
p.axis([0,18,160,250],0.01)
xlabel('POP(20) * replaceDate')
ylabel('Fitness')
p.show()


fit_1.sort()
fit_2.sort()
fit_3.sort()

print "Mejor fitness: "+str(fit_1[0])
print "Peor fitness: "+str(fit_1[len(fit_1)-1])
print "Tiempo Total: "+str(total_time_1)
print
print "Mejor fitness: "+str(fit_2[0])
print "Peor fitness: "+str(fit_2[len(fit_2)-1])
print "Tiempo Total: "+str(total_time_2)
print
print "Mejor fitness: "+str(fit_3[0])
print "Peor fitness: "+str(fit_3[len(fit_3)-1])
print "Tiempo Total: "+str(total_time_3)

