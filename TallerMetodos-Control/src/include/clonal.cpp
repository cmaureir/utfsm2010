#include "clonal.h"

void saveBest(bool option){


	if(option){
		bestCellFitness = population[0].fitness;
	}
	else{
		bestNewCellFitness = clonePop[0].fitness;		
	}

}

void averageFitness(bool option){
	// True: Cells
	// Faslse: NewCells
	double av = 0.0;
	int i = 0;
	if(option){
	    for (i=0;i<POP;i++){
			av += population[i].fitness;
		}
		cellAverage = av/POP;	
//		cout << "cellAverage: " << cellAverage << endl;
	}
	else{
	    for (i=0;i<POP;i++){
			//av += clonePop[i].fitness;
			av += tmpPop[i].fitness;
		}
		newCellAverage = av/POP;	
//		cout << "newCellAverage: " << newCellAverage << endl;
	}
}


// Inicializacion de la problacion
void initPopulation(){
	int i=0,j=0,k=0,counter=0;
	int p[VARS];
	
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

bool isNull(struct cell p){
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
void evaluation(struct cell evalPop[POP+1]){
	int mem=0, i=0, j=0, m=0, tmp=0, badness=0 ;

	for (mem = 0; mem < POP; mem++){
		if(!isNull(evalPop[mem])){
		for(i = 0; i < optNumber; i++){
			while(m<carNumber){
				if(m+sizeMaxCarOptSeq[i] <= carNumber){
					// Sumamos los booleanos de si tiene o no una determinada opcion
					//  por cada tipo de auto en la secuencia de nuestra poblacion
					j = 0;
					for (j = m; j < sizeMaxCarOptSeq[i]+m; j++) {
						tmp += types[evalPop[mem].gene[j]][i+2];
					}
					// Si nuestra suma es mayor que la cantidad permitida,
					//  nuestro fitness sera las unidades excedentes por cada restriccion
					if(tmp > numMaxCarOptSeq[i]){
						badness += tmp-numMaxCarOptSeq[i];
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
		badness = 0;

	}

// printPop(evalPop);
}

//Seleccion de un individuo
//	Ruleta para una FO que minimiza
void selection(int n, struct cell popToSel[POP+1]){
	int mem, i, best, worst, den=0, selected = 0;
	double p;
	// weird...
	int tp = typeNumber;
	int tps[tp];

	for (int j = 0; j < typeNumber; j++){
		tps[j] = types[j][1];
	}

	best = popToSel[0].fitness;
	worst = popToSel[0].fitness;
	
	// Buscamos el peor y mejor valor en nuestra poblacion
	for (mem = 0; mem < POP; mem++){
		if(popToSel[mem].fitness > best && !isNull(popToSel[mem]))
			worst = popToSel[mem].fitness;
		
		if(popToSel[mem].fitness < worst && !isNull(popToSel[mem]))
			best = popToSel[mem].fitness;
	}
	// Denominador de la Prob_i
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem]))
			den += (worst + best -popToSel[mem].fitness);
	}
	// Fitness relativo a cada individuo
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem])){
			popToSel[mem].rfitness = (double)(worst+best-popToSel[mem].fitness)/den;
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

	for (int j = 0; j < tp; j++){
		types[j][1] = tps[j];
	}
	typeNumber = tp;
}

void sortPop(struct cell p[POP+1]){
	int i,j;
	struct cell tmp;
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

void clonation(struct cell clone[POP+1]){
	int i=0,j=0,n=0, counter[POP], k=0, clones;
	double m[POP+1], intPart, decPart;
	sortPop(clone);
	
	for (i=0;i<POP;i++){
		if(isNull(clone[i]))
			break;
		n++;
	}
	for (i=0;i<n;i++){
			clones = (float)(clonationFactor*n)/(float)(i+1);
			if((int)clones + clone_control  > 2){
				m[i] = clones + clone_control;
			}
			else{
				m[i] = clones;
			}
			decPart = modf(m[i],&intPart);
			if(decPart >= 0.5){
				counter[i] = (int)(intPart + 1);
			}
			else{
				counter[i] = (int)intPart;
			}
	}
	
	k=n;
	for(i=0;i<n;i++){
		for (j=0; j<counter[i]; j++){
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
	sortPop(clonePop);
	for(i=0;i<POP;i++){
		if(!isNull(clonePop[i])){

			// se intercambian por su orden, el primero 2 veces, el segundo 3 veces...
			for(j=0;j<(i+1);j++){
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
	}
}

void cloneSelection(struct cell popToSel[POP+1]){
	int i,j;
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
	struct cell tmp;
	    //Bubble Sort
	    for (i = 0; i < 2*(POP+1); i++) {
	        for (j = i+1; j < 2*(POP+1); j++) {
	            if (tmpPop[i].fitness > tmpPop[j].fitness && !isNull(tmpPop[i]) &&  !isNull(tmpPop[j])){
	                tmp = tmpPop[i];
	                tmpPop[i] = tmpPop[j];
	                tmpPop[j] = tmp;
	            }
	        }
	    }

}

// Insertar los mejores entre population y clonePop
void cloneInsertion(){
	int i;
	for (i = 0; i < POP; i++) {
		population[i] = tmpPop[i];
	}

}

void newGeneration(int counter){
    int i=0,j=0,k=0,c=0,temp=0,r=0;
    int p[VARS];
	// Inicializamos en p[] la cantidad requerida por cada tipo
	//  de autos, satisfaciendo asi las restricciones duras
	for (j = 0; j < typeNumber; j++){
	    while(k < types[j][1]){
	        p[i] = j;
	        k++;i++;
	    }
	    k = 0;
	}
	i = 0;
	temp=0;
	r=0;

	for (j = 0; j < counter; j++) {
	        for (i=0; i<VARS; i++) {
	            r = i + (rand() % (VARS-i));
	            temp = p[i];
	            p[i] = p[r];
	            p[r] = temp;
	        }
	        // Guardamos nuestros valores en la estructura de   la poblacion
			// Mas malos reemplazados
			for (c=0; c<VARS; c++) {
	           	population[POP-1-j].gene[c] = p[c];
			}
	}
}

void printPop(struct cell tmp[POP+1]){
	int i,j;
	for (i=0;i<POP;i++){
		for (j=0;j<VARS;j++){
			cout << tmp[i].gene[j] << " ";
		}
		cout << "| " <<tmp[i].fitness << " ";
		cout << endl;
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
		tmpPop[i].rfitness = 0;
		tmpPop[i].cfitness = 0;
		if(i < POP){
			for (j = 0; j < VARS; j++) {
				clonePop[i].gene[j] = 0;
			}
			clonePop[i].fitness = 0;
			clonePop[i].rfitness = 0;
			clonePop[i].cfitness = 0;
		}
	}
}
