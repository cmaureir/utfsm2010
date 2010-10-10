#include "clonal.h"

// Inicializacion de la problacion
// Random.
void initPopulation(bool type){
	int i=0,j=0,k=0,counter=0;
	int p[VARS];
	// Inicializacion de la semilla para generar numeros
	//  pseudo-aleatorios
	srand(time(0));
	
	if(type){
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
	else{
		for (counter = 0; counter < POP; counter++) {
			for (i=0; i<VARS; i++) {
				int r = i + (rand() % typeNumber);
				r = r % typeNumber;
				p[i] = r;
			}

			// Guardamos nuestros valores en la estructura de
			//  la poblacion
	    	for (int c=0; c<VARS; c++) {
	    	    population[counter].gene[c] = p[c];
	    	}
		}
	}
	
	cout << "Población inicial..." << endl;
}

// Evaluacion
// Verificar las restricciones Blandas.
void evaluation(struct genotype evalPop[POP+1], bool type){
	int mem, i=0, j=0, m=0, tmp=0, badness=0, failCon = 0;

	for (mem = 0; mem < POP; mem++){
		for(i = 0; i < optNumber; i++){
			while(m<carNumber){
				if(m+sizeMaxCarOptSeq[i] <= carNumber){
					// Sumamos los booleanos de si tiene o no una determinada opcion
					//  por cada tipo de auto en la secuencia de nuestra poblacion
					for (j = m; j < sizeMaxCarOptSeq[i]+m; j++) {
						tmp += types[evalPop[mem].gene[j]][i+2];
					}
					// Si nuestra suma es mayor que la cantidad permitida,
					//  nuestro fitness sera las unidades excedentes por cada restriccion
					if(tmp > numMaxCarOptSeq[i]){
						//badness += tmp-numMaxCarOptSeq[i];
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
		evalPop[mem].fitness = badness;
		evalPop[mem].fail = failCon;
		badness = 0;
		failCon = 0;
	}
	
	if(!type){
		int tmpGen[VARS];
		for (i = 0; i < VARS; i++)
			tmpGen[i] = 0;

		for (i = 0; i < POP; i++) {
				for (j = 0; j < VARS; j++) {
					tmpGen[evalPop[i].gene[j]] += 1;

				}
				for (j = 0; j < typeNumber; j++){
					if (types[j][1] != tmpGen[j])
						evalPop[i].fitness += 10*(abs(types[j][1] -tmpGen[j]));
					tmpGen[j] = 0;
				}
		}
	}

	// PRINT
	cout << "Evaluamos..." << endl;
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
			cout << evalPop[i].gene[j] << " ";
		}
		cout << "| " <<evalPop[i].fitness << " ";
		cout << endl;
	}

	cout << endl;
	
}

//Seleccion de un individuo
//	Ruleta para una FO que minimiza
void selection(int n){
	int mem, i, j, best, worst, den=0, selected = 0;
	double sum = 0;
	double p;
	// Inicializamos la mejor y peor solucion como la primera
	//  de nuestra poblacion
	best = population[0].fitness;
	worst = population[0].fitness;
	
	// Buscamos el peor y mejor valor en nuestra poblacion
	for (mem = 0; mem < POP; mem++){
		if(population[mem].fitness > best)
			worst = population[mem].fitness;
		
		if(population[mem].fitness < worst)
			best = population[mem].fitness;
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
	while (selected < n){
			p = rand()%1000/1000.0;
			for (i = 0; i < POP; i++) {
				if ( i == 0){
					if (p < population[0].cfitness){
						clonePop[selected] = population[0];
						selected++;
					}
				}
				else{
					if (p >= population[i].cfitness && p < population[i+1].cfitness){
						clonePop[selected] = population[i+1];
						selected++;
					}
				}
			}
	}

	cout << "Seleccionamos..." << endl;
	// PRINT
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
			cout << clonePop[i].gene[j] << " ";
		}
		cout << "| " <<clonePop[i].fitness << " ";
		cout << endl;
	}

	cout << endl;
}


void clonation(){
	int i,j=0;
	for (i=0; i < POP; i++){
		if (clonePop[i].fitness == 0){
			clonePop[i] = clonePop[j];
			j++;
		}
	}

	// PRINT
	cout << "Clonamos..." << endl;
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
			cout << clonePop[i].gene[j] << " ";
		}
		cout << "| " <<clonePop[i].fitness << " ";
		cout << endl;
	}
}

// HyperMutacion
void hypermutation(){
	int i,j,sum=0,prom, v = VARS;
	// TO DO 
	// mutacion aleatoria
//	int tmp[VARS];
//
//	for (i=0; i < POP; i++){
//		sum += clonePop[i].fitness;
//	}
//	prom = sum/POP;
//	cout << "Prom: " << prom << endl;
	
	for (i=0; i < POP; i++){
//		if(clonePop[i].fitness > prom){
//			for (j=0;j<VARS;j++){
//				tmp[v] = clonePop[i].gene[j];
//				v--;
//			}
//			for (j=0;j<VARS;j++)
//				clonePop[i].gene[j] = tmp[j];
//		}
		mutPop[i] = clonePop[i];
	}
cout << "MUTO" << endl;

	// PRINT
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
			cout << clonePop[i].gene[j] << " ";
		}
		cout << "| " <<clonePop[i].fitness << " ";
		cout << endl;
	}
	getchar();
}

void cloneSelection(int n){
	int i;

	// hacer sort a mutPop
	// TO DO

	// Pasarlos a tmpPop
	for (i = 0; i < n; i++){
		tmpPop[i] = mutPop[i];	
	}
}

// Insertar en los primeros size(tmpPop) elementos
void cloneInsertion(){
	int i;
	int n=0;
	// size de tmpPop n

	for(i=0;i<n;i++){
		population[i] = tmpPop[i];
	}
}

void newGeneration(){
// TO DO
}

void replace(){
}
