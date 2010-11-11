from os import system

instancias = ["pb_200_01.txt","pb_200_09.txt","pb_200_10.txt"]

for j in instancias:
	for i in range(0,10):
		for w in range(0,10):
			tmp = "0."+str(i)
			system("clear")
			print j+" "+str(i)+"/"+"1"
			system("./csp "+j+" 0.5 0.4 "+str(tmp)+" >> "+j.replace("txt","")+"res.3")
