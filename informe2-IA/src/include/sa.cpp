#include "sa.h"

// Movimiento
// Swap
void saMovement(){
	int i, random_1, random_2, tmp, c;

	for(c=0;c<VARS*0.1;c++){
		// Generamos dos numeros para intercambiar los valores
		//  de nuestra solucion
		random_1 = (1+(int)((rand()/(RAND_MAX + 1.0))*(VARS+1)))%VARS;
		random_2 = (1+(int)((rand()/(RAND_MAX + 1.0))*(VARS+1)))%VARS;
		for (i = 0; i < VARS; i++) {
			tmpSol[i] = saBestSol[i];
		}
		// Intercambiamos los valores del swap
		tmp = tmpSol[random_1];
		tmpSol[random_1] = tmpSol[random_2];
		tmpSol[random_2] = tmp;
	}

}

// Aceptacion
// Si X(t+1) mejora el objetivo o si P(exp(Dobjetivo/temp) >= random(0,1)
//  modificamos X(t+1) = X(t) + Dx(t+1), sino volvemos al Movimiento
bool saAcceptance(){
	int diff = 0;

	diff = getFitness(tmpSol) - getFitness(saBestSol);
	p = exp(-((double)diff/temp));
	p_new = rand()%1000/1000.0;
	
	// Si nuestra nueva solucion es mejor a la que ya teniamos
	//  retornamos verdadero
	if(diff < 0)
		return true;
	// Si no es mejor, probamos con un numero random y nuestra
	//  probabilidad generada en p
	else if(p < p_new)
		return true;
	// En caso contrario, no aceptamos
	else
		return false;
}

// Reduccion de la temperatura
// Si han pasado 3 iteraciones desde el ultimo cambio de temperatura
//  la disminuimos a un 90%
void saTDecrease(){
	if(iteration+1 % 4 == 0){
		temp = temp * 0.9;
	}
}

// Funcion para obtener el fitness de cada solucion
// Se consideran todas las unidades en las cuales sobrepase
//  a la cantidad requerida por cada opcion.
int getFitness(int individual[VARS]){
	int i, m=0, j=0, tmp = 0, fitness = 0;

	for(i = 0; i < optNumber; i++){
		while(m<carNumber){
			if(m+sizeMaxCarOptSeq[i] <= carNumber){
				// Sumamos la cantidad de automoviles que necesitamos por cada opcion.
				for (j = m; j < sizeMaxCarOptSeq[i]+m; j++) {
					tmp += types[individual[j]][i+2];
				}
				// Si sumamos mas que el maximo requerido, 
				//  penalizamos con una unidad por cada excedente.
				if(tmp > numMaxCarOptSeq[i]){
					fitness += tmp-numMaxCarOptSeq[i];
					tmp = 0;
				}
				else{
					tmp = 0;
				}
			}
			m++;
		}
		m = 0;
	}
	return fitness;
}

// Algoritmo central del SA + AM
void simulatedAnnealing(){
	int i;
	double random;
	
	// Generamos un numero aleatorio entre 0 y 1
	//  para ver si mutamos el individuo
	random = rand()%1000/1000.0;
	if(random < PMUT){
		// Establecemos como mejor solucion al primer
		//  individuo de nuestra poblacion
		for (i = 0; i < VARS; i++) {
			saBestSol[i] = newPop[0].gene[i];
		}
		
		// Iteramos mientras no sobrepasemos el numero maximo
		//  de iteraciones y la temperatura sea positiva
		while(iteration < IMAX && temp > 0){
			saMovement();
			if(saAcceptance()){
				// Si tmpSol es mejor que la que ya teniamos
				//  cambiamos la solucion
				for(i=0;i<VARS;i++){
					saBestSol[i] = tmpSol[i];
				}
				break;
			}
			saTDecrease();
			iteration++;
		}
		// Volvemos el numero de iteraciones y la temperatura
		//  a sus valores iniciales
		iteration = 0;
		temp = (double)TMAX;

		// Copiamos nuestra mejor solucion encontrada a una nueva
		//  poblacion
		for (i = 0; i < VARS; i++) {
			tmpPop[itePop].gene[i] = saBestSol[i];
		}
		// Aumentamos el contador de la poblacion
		itePop++;
	}
}	
