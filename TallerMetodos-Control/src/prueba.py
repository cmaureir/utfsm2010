from os import system

instancias = ["pb_200_01.txt","pb_200_09.txt","pb_200_10.txt"]

for i in instancias:
	for j in range(10):
		print "Instancia: "+i+"    Iteracion: "+str(j)
		system("./csp2 "+i+" >> "+i.replace("txt","")+"res.2")
