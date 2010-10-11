#!/usr/bin/env python
import os
from numpy import *

l=[];
t=[];
v=['200','300','400'];
n=['01','02','03','04','05','06','07','08','09','10'];


for a in v:
	for b in n:
		out1 = os.popen("cat pb_"+a+"_"+b+".out  | grep Restric | awk '{print $4}' | sort -n")
		while 1:
			line1 = out1.readline()
			if not line1: break
			l.append(int(line1))
		out2 = os.popen("cat pb_"+a+"_"+b+".out  | grep Tie | awk '{print $6}' | sort -n")
		while 1:
			line2 = out2.readline()
			if not line2: break
			t.append(int(line2))

		print "===pb_"+a+"_"+b+"==="
		print "Prom: "+str(average(l))
		print "S: "+str(std(l))
		print "Min: "+str(l[0])
		print "Max: "+str(l[len(l)-1])
		print "t: "+str(average(t))
		l=[];
		t=[];
		
