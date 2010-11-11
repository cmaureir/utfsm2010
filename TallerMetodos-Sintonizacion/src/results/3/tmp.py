from os import system

a = [0,2,4,6,8,10,12,14,16,18]


rr_1 , rr_2, rr_3 = [], [], [];
fit_1 , fit_2, fit_3 = [], [], [];
time_1 , time_2, time_3 = [], [], [];

total_time_1 = 0
total_time_2 = 0
total_time_3 = 0

f1, f2, f3  = open("pb_200_01.res.3","r"),  open("pb_200_09.res.3","r"),  open("pb_200_10.res.3","r")
t = False
i = 0
j = 0
for line in f1:
	tmp = line.replace("\n","").split(" ")
	total_time_1 = total_time_1 + float(tmp[2])
	if t == False:
		rr_1.append(int(tmp[0]))
		fit_1.append(int(tmp[1]))
		time_1.append(float(tmp[2]))
	elif int(tmp[1]) < fit_1[0] and t == True:
		rr_1[j] = int(tmp[0])
		fit_1[j] = int(tmp[1])
		time_1[j] = float(tmp[2])
	i = i + 1
	t = True
	if i == 10:
		i = 0
		t = False
		system("echo \""+str(rr_1[j])+" "+str(fit_1[j])+" "+str(time_1[j])+"\" >> pb_200_01.res.3.1")
		j = j + 1


t = False
i = 0
j = 0
for line in f2:
	tmp = line.replace("\n","").split(" ")
	total_time_2 = total_time_2 + float(tmp[2])
	if t == False:
		rr_2.append(int(tmp[0]))
		fit_2.append(int(tmp[1]))
		time_2.append(float(tmp[2]))
	elif int(tmp[1]) < fit_2[0] and t == True:
		rr_2[j] = int(tmp[0])
		fit_2[j] = int(tmp[1])
		time_2[j] = float(tmp[2])
	i = i + 1
	t = True
	if i == 10:
		i = 0
		t = False
		system("echo \""+str(rr_2[j])+" "+str(fit_2[j])+" "+str(time_2[j])+"\" >> pb_200_09.res.3.1")
		j = j + 1


t = False
i = 0
j = 0
for line in f3:
	tmp = line.replace("\n","").split(" ")
	total_time_3 = total_time_3 + float(tmp[2])
	if t == False:
		rr_3.append(int(tmp[0]))
		fit_3.append(int(tmp[1]))
		time_3.append(float(tmp[2]))
	elif int(tmp[1]) < fit_3[0] and t == True:
		rr_3[j] = int(tmp[0])
		fit_3[j] = int(tmp[1])
		time_3[j] = float(tmp[2])
	i = i + 1
	t = True
	if i == 10:
		i = 0
		t = False
		system("echo \""+str(rr_3[j])+" "+str(fit_3[j])+" "+str(time_3[j])+"\" >> pb_200_10.res.3.1")
		j = j + 1
