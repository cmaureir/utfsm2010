#include "ea.h"

// Inicializacion de la problacion
// Random.
void initPopulation(){
	int i=0,j=0,k=0,counter=0;
	int p[VARS];
	// Inicializacion de la semilla para generar numeros
	//  pseudo-aleatorios
	srand(time(0));
	
	// Inicializamos en p[] la cantidad requerida por cada tipo
	//  de autos, satisfaciendo asi las restricciones duras
	for (j = 0; j < typeNumber; j++){
		while(k < types[j][1]){
	        p[i] = j;
			k++;i++;
		}
		k = 0;
	}

	// Generamos la poblacion inicial, tomando p[] y comenzando
	//  a desordenarlos aleatoriamente para generar los individuos
	for (counter = 0; counter < POP; counter++) {
			for (i=0; i<(VARS-1); i++) {
	            int r = i + (rand() % (VARS-i));
	            int temp = p[i];
				p[i] = p[r];
				p[r] = temp;
	        }
		// Guardamos nuestros valores en la estructura de
		//  la poblacion
	    for (int c=0; c<VARS; c++) {
	        population[counter].gene[c] = p[c];
	    }
		
	}
}

// Evaluacion
// Verificar las restricciones Blandas.
void evaluation(){
	int mem, i=0, j=0, m=0, tmp=0, badness=0, failCon = 0;

	for (mem = 0; mem < POP; mem++){
		for(i = 0; i < optNumber; i++){
			while(m<carNumber){
				if(m+sizeMaxCarOptSeq[i] <= carNumber){
					// Sumamos los booleanos de si tiene o no una determinada opcion
					//  por cada tipo de auto en la secuencia de nuestra poblacion
					for (j = m; j < sizeMaxCarOptSeq[i]+m; j++) {
						tmp += types[population[mem].gene[j]][i+2];
					}
					// Si nuestra suma es mayor que la cantidad permitida,
					//  nuestro fitness sera las unidades excedentes por cada restriccion
					if(tmp > numMaxCarOptSeq[i]){
						badness += tmp-numMaxCarOptSeq[i];
						failCon += 1;
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
		population[mem].fitness = badness;
		population[mem].fail = failCon;
		// Si encontramos una solucion factible que no viole ninguna
		//  restriccion blanda, de inmediatos nos quedamos con dicha
		//  solucion.
		if (population[mem].fitness == 0) {
			for (i = 0; i < POP; i++) {
				for (j = 0; j < VARS; j++) {
					newPop[i].gene[j] = population[mem].gene[j];
					newPop[i].fitness = 0;	
				}
			}

			for (i = 0; i < POP; i++) {
				for (j = 0; j < VARS; j++) {
					population[i].gene[j] = newPop[i].gene[j];
					population[i].fitness = newPop[i].fitness;
				}
			}
			generation = GENS;
		}
		
		badness = 0;
		failCon = 0;
	}
}

//Seleccion de un individuo
//	Ruleta para una FO que minimiza
void individualSelection(){
	int mem, i, j, best, worst, den=0;
	double sum = 0;
	double p;

	// Inicializamos la mejor y peor solucion como la primera
	//  de nuestra poblacion
	best = population[0].fitness;
	worst = population[0].fitness;
	
	// Buscamos el peor y mejor valor en nuestra poblacion
	for (mem = 0; mem < POP; mem++){
		if(population[mem].fitness > best)
			best = population[mem].fitness;
		
		if(population[mem].fitness < worst)
			worst = population[mem].fitness;
	}

	// Calculamos nuestra probabilidad por cada individuo,
	//  a =  (Fitness_min + Fitness_max - Fitness_i)
	// 	Prob_i = a / Sum(a)
	
	// Denominador de la Prob_i
	for (mem = 0; mem < POP; mem++){
		den += (worst + best -population[mem].fitness);
	}
	
	// Fitness relativo a cada individuo
	for (mem = 0; mem < POP; mem++){
		population[mem].rfitness = (double)(worst+best-population[mem].fitness)/den;
		sum += population[mem].rfitness;
	}
	// Fitness acumulativo considerando todos los individuos
	population[0].cfitness = population[0].rfitness;
    for (mem = 1; mem < POP; mem++){
        population[mem].cfitness = population[mem-1].cfitness + population[mem].rfitness;
    }

	// Seleccionamos un numero random para elegir a nuestro individuo
	p = rand()%1000/1000.0;
	for (i = 0; i < POP; i++) {
		if (p < population[0].cfitness)
			// Almacenamos al individuo elegido en newPop[]
            newPop[i] = population[0];
        else{
            for (j = 0; j < POP;j++){
	            if (p >= population[j].cfitness && p<population[j+1].cfitness){
					// Almacenamos al individuo elegido en newPop[]
	                newPop[i] = population[j+1];
				}
			}
		}
	}	
}

// Elitismo
// Pasamos siempre el mejor individuo de cada poblacion
//  a la siguiente poblacion y se reemplaza al peor individuo
//  por el mejor individuo.
void elitism(){
	int i; double best, worst;

	// Inicializamos la mejor y peor solucion como la primera
	//  de nuestra poblacion
	best = population[0].fitness;
	worst = population[0].fitness;

	// Buscamos el indice del mejor y peor individuo de nuestra
	//  poblacion
	for (i = 0; i < POP - 1; ++i){
		// Eleccion del peor
	    if(population[i].fitness > population[i+1].fitness) {
	        if (population[i].fitness >= worst){
	            worst = population[i].fitness;
	            worst_mem = i;
			}
	        if (population[i+1].fitness <= best){
	            best = population[i+1].fitness;
	            best_mem = i + 1;
			}
		}
		// Eleccion del mejor
	    else {
	        if (population[i].fitness <= best) {
	            best = population[i].fitness;
	            best_mem = i;
			}
	        if (population[i+1].fitness >= worst) {
	            worst = population[i+1].fitness;
	            worst_mem = i + 1;
			}
		}
	}
	// Cambia el peor por el mejor
	for (i = 0; i < VARS; i++) {
		population[worst_mem].gene[i] = population[best_mem].gene[i];
	}
	population[worst_mem].fitness  = population[best_mem].fitness;

	// Guardamos el mejor
	for (i = 0; i < VARS; i++) {
		tmpPop[POP-1].gene[i] = population[best_mem].gene[i];
	}
}

// Mutacion
// Simulated Annealing + Alguna Mejora
void mutation(){
	simulatedAnnealing();
}

// Cambiar poblacion
// Cambiamos los elementos de la poblacion que hemos creado,
//  a la solucion actual.
void changePop(){
	int i,j;
	for (i = 0; i < POP; i++) {
		for (j = 0; j < VARS; j++) {
			population[i].gene[j] = tmpPop[i].gene[j];
		}
	}
}
