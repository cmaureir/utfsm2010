#!/bin/env python

# 
vector = [1,5,10,15,20]
vector_cpu_time = [];
vector_gpu_time = [];
vector_diff = [];

cpu_time, gpu_time, diff  = 0, 0, 0

for i in vector:
	vector_file = open("vector"+str(i),"r")
	for line in vector_file:
		parts = line.replace("\n","").split(" ")
		cpu_time = cpu_time + float(parts[0])
		gpu_time = gpu_time + float(parts[1])
		diff = diff + float(parts[2])
	vector_file.close()

	vector_cpu_time.append(cpu_time / 20)
	vector_gpu_time.append(gpu_time / 20)
	vector_diff.append(diff / 20)
		
	cpu_time, gpu_time, diff  = 0, 0, 0

print "vector="+str(vector)
print "CPU time="+str(vector_cpu_time)
print "GPU time="+str(vector_gpu_time)
print "Diff="+str(vector_diff)
