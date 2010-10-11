all:
	g++ -c include/extra.cpp
	g++ -c include/clonal.cpp
	g++ csp.cpp -o csp -lrt -Wall

clean:
	rm -rf csp
	rm -rf *.o
	rm -rf *.out

run:
	./csp input.txt true true true true
