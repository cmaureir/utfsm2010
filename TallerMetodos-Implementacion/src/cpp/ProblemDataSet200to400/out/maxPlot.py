#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
from numpy import *
import matplotlib.pyplot as p
from pylab import *
l=[];
v=['0','1','2','3','4'];
opt=[0,2,4,7,6,6,0,8,10,19,0,12,13,7,29,2,0,8,7,21,1,16,9,19,0,0,4,4,5,0]
m=[];
for a in v:
	out1 = os.popen("cat "+a+" | grep -v \"#\" | awk '{print $4}'")
	while 1:
		line1 = out1.readline()
		if not line1: break
		l.append(float(line1.replace("\n","")))
	m.append(l)
	l=[];
e=[];
for i in range(1,31):
	e.append(i)

#plot1 = p.plot(e,m[0],label='Normal')
#plot2 = p.plot(e,m[1],label='Pop aleatorias')
#plot3 = p.plot(e,m[2],label='Seleccion ruleta')
#plot4 = p.plot(e,m[3],label='Reemplazo aleatorio')
#plot5 = p.plot(e,m[4],label='Clonacion fija')
#
#title(u'Máximo')
#legend((plot1,plot2, plot3, plot4, plot5),('Normal','Pop aleatorias','Seleccion ruleta','Reemplazo aleatorio','Clonacion fija'),loc='upper left')
#grid(True)
#p.axis([0,30,150,550],1)
#xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
#ylabel('Restricciones insatisfechas')
#p.show()

plot1 = p.plot(e,m[0],label='Normal')
plot2 = p.plot(e,m[1],label='Pop aleatorias')
title(u'Máximo')
legend((plot1,plot2),('Normal','Pop aleatorias'),loc='upper left')
grid(True)
p.axis([0,30,150,550],1)
xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
ylabel('Restricciones insatisfechas')
p.show()

plot1 = p.plot(e,m[0],label='Normal')
plot3 = p.plot(e,m[2],label='Seleccion ruleta')
title(u'Máximo')
legend((plot1,plot3),('Normal','Seleccion ruleta'),loc='upper left')
grid(True)
p.axis([0,30,150,550],1)
xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
ylabel('Restricciones insatisfechas')
p.show()


plot1 = p.plot(e,m[0],label='Normal')
plot4 = p.plot(e,m[3],label='Reemplazo aleatorio')
title(u'Máximo')
legend((plot1, plot4),('Normal','Reemplazo aleatorio'),loc='upper left')
grid(True)
p.axis([0,30,150,550],1)
xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
ylabel('Restricciones insatisfechas')
p.show()


plot1 = p.plot(e,m[0],label='Normal')
plot5 = p.plot(e,m[4],label='Clonacion fija')

title(u'Máximo')
legend((plot1, plot5),('Normal','Clonacion fija'),loc='upper left')
grid(True)
p.axis([0,30,150,550],1)
xlabel('Instancias (1: pb_200_01 ... 30: pb_400_10)')
ylabel('Restricciones insatisfechas')
p.show()
