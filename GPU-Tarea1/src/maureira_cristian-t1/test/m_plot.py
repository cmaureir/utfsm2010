#!/bin/env python

import matplotlib.pyplot as p
from pylab import *


# M
M = [10,100,1000,10000,100000,1000000]
m_cpu_time = [];
m_gpu_time = [];
m_diff = [];

cpu_time, gpu_time, diff  = 0, 0, 0

for i in M:
	m_file = open("m"+str(i),"r")
	for line in m_file:
		parts = line.replace("\n","").split(" ")
		cpu_time = cpu_time + float(parts[0])
		gpu_time = gpu_time + float(parts[1])
		diff = diff + float(parts[2])
	m_file.close()

	m_cpu_time.append(cpu_time / 20)
	m_gpu_time.append(gpu_time / 20)
	m_diff.append(diff / 20)
		
	cpu_time, gpu_time, diff  = 0, 0, 0


#plot1 = p.plot(M,m_cpu_time,label='CPU time', 'o-')
plot1 = p.plot(M, m_cpu_time, 'o')

#plot2 = p.plot(M,m_gpu_time,label='GPU time')
plot2 = p.plot(M,m_gpu_time,'o',label='GPU time')
#plot3 = p.plot(M,m_diff,label='Diference')

title('M variation')
#legend((plot1,plot2,plot3),('CPU time','GPU time','Diference'),loc='center right')
legend((plot1,plot2),('CPU time','GPU time'),loc='center right')
grid(True)
p.axis([10,10000,0,10])
xlabel('M values')
ylabel('Time [s]')
p.show()
