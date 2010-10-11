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
	
//	cout << "Población inicial..." << endl;
}

bool isNull(struct genotype p){
	int i=0,j=0;
	for (i = 0; i < VARS; i++) {
		if(p.gene[i] == 0)
			j++;	
	}
	if(j==VARS)
		return true;
	else
		return false;
}



// Evaluacion
// Verificar las restricciones Blandas.
void evaluation(struct genotype evalPop[POP+1], bool type){
	int mem, i=0, j=0, m=0, tmp=0, badness=0, failCon = 0;

	for (mem = 0; mem < POP; mem++){
		if(!isNull(evalPop[mem])){
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
//	cout << "Evaluamos..." << endl;
//	for (i=0;i<POP;i++){
//		for (j=0;j<VARS;j++){
//			cout << evalPop[i].gene[j] << " ";
//		}
//		cout << "| " <<evalPop[i].fitness << " ";
//		cout << endl;
//	}
//
//	cout << endl;
	// Verificar si encuentro 1 con 0, para terminar el programa	
}

//Seleccion de un individuo
//	Ruleta para una FO que minimiza
void selection(int n, struct genotype popToSel[POP+1]){
	int mem, i, best, worst, den=0, selected = 0;
	double sum = 0;
	double p;
	// Inicializamos la mejor y peor solucion como la primera
	//  de nuestra poblacion
	best = popToSel[0].fitness;
	worst = popToSel[0].fitness;
	
	// Buscamos el peor y mejor valor en nuestra poblacion
	for (mem = 0; mem < POP; mem++){
		if(popToSel[mem].fitness > best && !isNull(popToSel[mem]))
			worst = popToSel[mem].fitness;
		
		if(popToSel[mem].fitness < worst && !isNull(popToSel[mem]))
			best = popToSel[mem].fitness;
	}
	// Calculamos nuestra probabilidad por cada individuo,
	//  a =  (Fitness_min + Fitness_max - Fitness_i)
	// 	Prob_i = a / Sum(a)
	
	// Denominador de la Prob_i
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem]))
			den += (worst + best -popToSel[mem].fitness);
	}
	
	// Fitness relativo a cada individuo
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem])){
			popToSel[mem].rfitness = (double)(worst+best-popToSel[mem].fitness)/den;
			sum += popToSel[mem].rfitness;
		}
	}
	// Fitness acumulativo considerando todos los individuos
	popToSel[0].cfitness = popToSel[0].rfitness;
    for (mem = 1; mem < POP; mem++){
		if (!isNull(popToSel[mem])){
        	popToSel[mem].cfitness = popToSel[mem-1].cfitness + popToSel[mem].rfitness;
		}
    }

	// Seleccionamos un numero random para elegir a nuestro individuo
	while (selected < n){
			p = rand()%1000/1000.0;
			for (i = 0; i < POP; i++) {
				if ( i == 0){
					if (p < popToSel[0].cfitness && !isNull(popToSel[0])){
						tmpPop[selected] = popToSel[0];
						selected++;
					}
				}
				else{
					if (p >= popToSel[i].cfitness && p < popToSel[i+1].cfitness && !isNull(popToSel[i]) && !isNull(popToSel[i+1])){
						tmpPop[selected] = popToSel[i+1];
						selected++;
					}
				}
			}
	}

//	cout << "Seleccionamos..." << endl;
	// PRINT
//	for (i=0;i<POP;i++){
//		for (j=0;j<VARS;j++){
//			cout << tmpPop[i].gene[j] << " ";
//		}
//		cout << "| " <<tmpPop[i].fitness << " ";
//		cout << endl;
//	}
//
//	cout << endl;
}

void sortPop(struct genotype p[2*(POP+1)]){
	int i,j;
	struct genotype tmp;
	//Bubble Sort
	for (i = 0; i < POP; i++) {
		for (j = i+1; j < POP; j++) {
			if (p[i].fitness > p[j].fitness && !isNull(p[i]) &&  !isNull(p[j])){
				tmp = p[i];
		 	 	p[i] = p[j];
		 	 	p[j] = tmp;
			}
		}
	}
}


//void clonation(){
void clonation(struct genotype clone[POP+1]){
	int i=0,j=0,n=0, counter[POP], k=0;
	double m[POP+1], intPart, decPart;

//	cout << "Clonamos..." << endl;
	sortPop(clone);
//	printPop(clone);
	
	for (i=0;i<POP;i++){
		if(isNull(clone[i]))
			break;
		n++;
	}
//	cout << "El n:" << n << endl;
//	getchar();
	for (i=0;i<n;i++){
			m[i] = (float)(clonationFactor*n*2)/(float)(i+1);
//			cout << "m["<<i<<"]: "<< m[i] << endl;
			decPart = modf(m[i],&intPart);
//			cout << "decPart:" << decPart << "\t intPart: "<<intPart << endl;
			if(decPart >= 0.5){
				counter[i] = (int)(intPart + 1);
			}
			else{
				counter[i] = (int)intPart;
			}
//		cout << "counter["<<i<<"]: "<< counter[i]<<endl;
	}
	
	k=n;
	for(i=0;i<n;i++){
		for (j=0; j<counter[i]; j++){
//			cout <<"n: "<<n<<"  k: "<< k << "  counter["<<i<<"]: " << counter[i] << endl;
//			getchar();
			clone[k] = clone[i];
			k++;
			if (k >= POP){
				k = 0;
			}
		}
	}

	for (i = 0; i < POP; i++) {
		clonePop[i] = clone[i];
	}


}

// HyperMutacion
void hypermutation(){
	int i, j, random_1, random_2, tmp;

	for(i=0;i<POP;i++){
	    for(j=0;j<clonationRate;j++){
	        // Generamos dos numeros para intercambiar los valores
	        //  de nuestra solucion
	        random_1 = (1+(int)((rand()/(RAND_MAX + 1.0))*(VARS+1)))%VARS;
	        random_2 = (1+(int)((rand()/(RAND_MAX + 1.0))*(VARS+1)))%VARS;
	        // Intercambiamos los valores del swap
	        tmp = clonePop[i].gene[random_1];
	        clonePop[i].gene[random_1] = clonePop[i].gene[random_2];
	        clonePop[i].gene[random_2] = tmp;
	    }
	}

//	cout << "MUTO" << endl;
}

void cloneSelection(int n, struct genotype popToSel[POP+1], bool type){
	int i;
	if(type){
		// Sort population y clonalPop, juntarlos y obtener los mejores
		bool change = false;

		for (i = 0; i < POP; i++) {
			if(!change)
				tmpPop[i] = population[i];
			else
				tmpPop[i+POP] = popToSel[i];

			if(i == POP-1 && !change){
				i=-1;
				change = true;
			}	
		}
		sortPop(tmpPop);
	}
	else{
		selection(n,popToSel);
	}

}

// Insertar los mejores entre population y clonePop
void cloneInsertion(){
//	cout << "Clone insertion..." << endl;
	int i;
	for (i = 0; i < POP; i++) {
		population[i] = tmpPop[i];
	}

}

void newGeneration(int counter){
//	cout << "New generation..." << endl;
    int i=0,j=0,k=0;
    int p[VARS];
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
	for (j = 0; j < counter; j++) {
	        for (i=0; i<(VARS-1); i++) {
	            int r = i + (rand() % (VARS-i));
	            int temp = p[i];
	            p[i] = p[r];
	            p[r] = temp;
	        }
	        // Guardamos nuestros valores en la estructura de
	        //  la poblacion
	       for (int c=0; c<VARS; c++) {
	            population[POP-1-j].gene[c] = p[c];
	        }
	}
}

void printPop(struct genotype tmp[POP+1]){
	int i,j;
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
//			cout << tmp[i].gene[j] << " ";
		}
//		cout << "| " <<tmp[i].fitness << " ";
//		cout << endl;
	}
	getchar();

}

void cleanPops(){
	int i,j;
	for (i = 0; i < 2*(POP+1); i++) {
		for (j = 0; j < VARS; j++) {
			tmpPop[i].gene[j] = 0;

		}
		tmpPop[i].fitness = 0;
		tmpPop[i].fail = 0;
		tmpPop[i].rfitness = 0;
		tmpPop[i].cfitness = 0;
		if(i < POP){
			for (j = 0; j < VARS; j++) {
				clonePop[i].gene[j] = 0;
			}
			clonePop[i].fitness = 0;
			clonePop[i].fail = 0;
			clonePop[i].rfitness = 0;
			clonePop[i].cfitness = 0;
		}
	}
}
