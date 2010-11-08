flags = -Wno-deprecated -O3 -g
prog  = REVAC
comp = g++
semilla = 2
archivo_configuracion = configuracionGE.config
directorio = instancias
ejecutable=sh-gtsp-Version1.sh


exe:$(prog)
	./$(prog) $(ejecutable) $(archivo_configuracion) $(directorio) $(semilla) 

$(prog): main.o
	$(comp) main.o -o $(prog) $(flags)

main.o: main.cpp includes.h globales.h 
	$(comp) -c main.cpp $(flags)

clean:
	rm -f *~
	rm -f *.o
	rm -rf $(prog)

