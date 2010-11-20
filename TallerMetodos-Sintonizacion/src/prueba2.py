from os import system

instancias = ["pb_200_01.txt","pb_200_09.txt","pb_200_10.txt"]

for j in instancias:
	for i in range(10,2001,30):
		system("clear")
		print j+" "+str(i)+"/"+"1990"
		if i == 10:
			system("sed 's/#define GENS 200/#define GENS "+str(i)+"/g' -i include/extra.h")
			system("make clean all &> /dev/null ")
			system("./csp "+j+" 0.5 0.4 0.6 >> "+j.replace("txt","")+"res")
		else:
			system("sed 's/#define GENS "+str(i-30)+"/#define GENS "+str(i)+"/g' -i include/extra.h")
			system("make clean all &> /dev/null ")
			system("./csp "+j+" 0.5 0.4 0.6 >> "+j.replace("txt","")+"res")

	system("sed 's/#define GENS 1990/#define GENS 200/g' -i include/extra.h")
