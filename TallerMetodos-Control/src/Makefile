all:
	g++ -c include/extra.cpp 
	g++ -c include/clonal.cpp 
	g++ csp.cpp -o csp2 -lrt -Wall

clean:
	rm -rf csp
	rm -rf *.o
	rm -rf *.out

run:
	./csp pb_200_01.txt 0.4 0.2
