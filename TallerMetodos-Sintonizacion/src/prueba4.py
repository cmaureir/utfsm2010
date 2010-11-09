from os import system

instancias = ["pb_200_01.txt","pb_200_09.txt","pb_200_10.txt"]

for j in instancias:
	for i in range(0,11):
		if i == 10:
			tmp1 = "1"
		else:
			tmp1 = "0."+str(i)
		for w in range(0,11):
			if w == 10:
				tmp2 = "1"
			else:
				tmp2 = "0."+str(w)
			system("clear")
			print j+" "+str(i)+"/"+"1"
			print "./csp "+j+" "+tmp1+" "+tmp2+" 0.6 >> "+j.replace("txt","")+"res.4"
			system("./csp "+j+" "+tmp1+" "+tmp2+" 0.6 >> "+j.replace("txt","")+"res.4")
