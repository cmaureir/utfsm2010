#!/usr/bin/env python
import os
from numpy import *
import matplotlib.pyplot as p
from pylab import *
l=[];
v=['200','300','400'];
n=['01','02','03','04','05','06','07','08','09','10'];
opt=[0,2,4,7,6,6,0,8,10,19,0,12,13,7,29,2,0,8,7,21,1,16,9,19,0,0,4,4,5,0]
m=[];
for a in v:
	for b in n:
		out1 = os.popen("cat pb_"+a+"_"+b+".out  | grep Restric | awk '{print $4}' | sort -n")
		while 1:
			line1 = out1.readline()
			if not line1: break
			l.append(int(line1))
		m.append(l[0])
		l=[];


e=[];
for i in range(1,31):
	e.append(i)


plot1 = p.plot(e,opt,label='Optimo')
plot2 = p.plot(e,m,label='Min')
title('Mejor Resultado Conocido vs Algoritmo Implementado')
legend((plot1,plot2),('Optimo Conocido','Implementacion'),loc='upper left')
grid(True)
p.axis([0,30,0,100],1)
xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
ylabel('Restricciones insatisfechas')
p.show()
		
