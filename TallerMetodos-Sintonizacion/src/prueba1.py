from os import system

instancias = ["pb_200_01.txt","pb_200_09.txt","pb_200_10.txt"]

for j in instancias:
	for i in range(10,211):
		system("clear")
		print j+" "+str(i)+"/"+"211"
		if i == 10:
			system("sed 's/#define POP 20/#define POP "+str(i)+"/g' -i include/extra.h")
			system("make clean all &> /dev/null ")
			system("./csp "+j+" 0.5 0.4 0.6 >> "+j.replace("txt","")+"res")
		else:
			system("sed 's/#define POP "+str(i-1)+"/#define POP "+str(i)+"/g' -i include/extra.h")
			system("make clean all &> /dev/null ")
			system("./csp "+j+" 0.5 0.4 0.6 >> "+j.replace("txt","")+"res")

	system("sed 's/#define POP 210/#define POP 20/g' -i include/extra.h")

