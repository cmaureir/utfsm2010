#!/bin/env python

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

print "M="+str(M)
print "CPU time="+str(m_cpu_time)
print "GPU time="+str(m_gpu_time)
print "Diff="+str(m_diff)
