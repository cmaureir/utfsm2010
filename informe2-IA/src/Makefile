all:
	g++ -c include/extra.cpp
	g++ -c include/ea.cpp
	g++ -c include/sa.cpp -lm
	g++ csp.cpp -o csp -lrt -Wall


200:
	@echo "Cambiando VARS a 200"
	@sed 's/#define VARS 300/#define VARS 200/g' -i include/extra.h
	@sed 's/#define VARS 400/#define VARS 200/g' -i include/extra.h

300:
	@echo "Cambiando VARS a 300"
	@sed 's/#define VARS 200/#define VARS 300/g' -i include/extra.h
	@sed 's/#define VARS 400/#define VARS 300/g' -i include/extra.h

400:
	@echo "Cambiando VARS a 400"
	@sed 's/#define VARS 200/#define VARS 400/g' -i include/extra.h
	@sed 's/#define VARS 300/#define VARS 400/g' -i include/extra.h
	@echo "Compilando con VARS : 400 ..."

clean:
	@echo "Volviendo VARS a 200"
	@sed 's/#define VARS 300/#define VARS 200/g' -i include/extra.h
	@sed 's/#define VARS 400/#define VARS 200/g' -i include/extra.h
	@echo "Limpiando..."
	rm -rf csp
	rm -rf *.o
	rm -rf *.out

test: 
	@echo "Compilando los binarios para cada test..."
	@echo "Compilando con 200 variables..."
	@make 200
	@make
	@echo "Moviendo binario csp a ProblemDataSet200to400/csp200.."
	@mv csp ProblemDataSet200to400/csp200
	@echo "Compilando con 300 variables..."
	@make 300 all
	@echo "Moviendo binario csp a ProblemDataSet200to400/csp300.."
	@mv csp ProblemDataSet200to400/csp300
	@echo "Compilando con 400 variables..."
	@make 400 all
	@echo "Moviendo binario csp a ProblemDataSet200to400/csp400.."
	@mv csp ProblemDataSet200to400/csp400
