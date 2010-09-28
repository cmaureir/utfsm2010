#!/bin/env python

block = [2,4,8,16,32,64,128,256]
block_cpu_time = [];
block_gpu_time = [];
block_diff = [];

cpu_time, gpu_time, diff  = 0, 0, 0

for i in block:
	block_file = open("block"+str(i),"r")
	for line in block_file:
		parts = line.replace("\n","").split(" ")
		cpu_time = cpu_time + float(parts[0])
		gpu_time = gpu_time + float(parts[1])
		diff = diff + float(parts[2])
	block_file.close()

	block_cpu_time.append(cpu_time / 20)
	block_gpu_time.append(gpu_time / 20)
	block_diff.append(diff / 20)
		
	cpu_time, gpu_time, diff  = 0, 0, 0

print "block="+str(block)
print "CPU time="+str(block_cpu_time)
print "GPU time="+str(block_gpu_time)
print "Diff="+str(block_diff)
