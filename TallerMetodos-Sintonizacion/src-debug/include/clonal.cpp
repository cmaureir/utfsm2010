#include "clonal.h"

// Inicializacion de la problacion
// Random.
void initPopulation(bool type){
	int i=0,j=0,k=0,counter=0;
	int p[VARS];
	// Inicializacion de la semilla para generar numeros
	//  pseudo-aleatorios
	srand(time(0));
	
//	cout << "--Población inicial--" << endl;
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
	
//	printPop(population);
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
void evaluation(struct cell evalPop[POP+1], bool type){
	int mem=0, i=0, j=0, m=0, tmp=0, badness=0 ;

for (i = 0; i < typeNumber; i++) {
	cout << "types[j][1]: " << types[i][1] << endl;
}
getchar();

//	printPop(evalPop);
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

for (i = 0; i < typeNumber; i++) {
	cout << "types[j][1]: " << types[i][1] << endl;
}
getchar();

	printPop(evalPop);
}

//Seleccion de un individuo
//	Ruleta para una FO que minimiza
void selection(int n, struct cell popToSel[POP+1]){
	int mem, i, best, worst, den=0, selected = 0;
	double sum = 0;
	double p;
	// weird...
	int tp = typeNumber;
	int tps[tp];

	for (int j = 0; j < typeNumber; j++){
		tps[j] = types[j][1];
	}

//	cout << "ini selection typeNumber: " << typeNumber << endl;
//	getchar();
	best = popToSel[0].fitness;
	worst = popToSel[0].fitness;
	
	// Buscamos el peor y mejor valor en nuestra poblacion
	for (mem = 0; mem < POP; mem++){
		if(popToSel[mem].fitness > best && !isNull(popToSel[mem]))
			worst = popToSel[mem].fitness;
		
		if(popToSel[mem].fitness < worst && !isNull(popToSel[mem]))
			best = popToSel[mem].fitness;
	}
	cout << "Best: " << best << "  " << "Worst: " << worst << endl;
	getchar();
	// Calculamos nuestra probabilidad por cada individuo,
	//  a =  (Fitness_min + Fitness_max - Fitness_i)
	// 	Prob_i = a / Sum(a)
	
	// Denominador de la Prob_i
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem]))
			den += (worst + best -popToSel[mem].fitness);
	}
	cout << "Denom: " << den << endl;	
	getchar();
	// Fitness relativo a cada individuo
	for (mem = 0; mem < POP; mem++){
		if (!isNull(popToSel[mem])){
			popToSel[mem].rfitness = (double)(worst+best-popToSel[mem].fitness)/den;
			cout << "rfitness["<<mem<<"]: " << popToSel[mem].rfitness << endl;
		}
	}
	getchar();

	// Fitness acumulativo considerando todos los individuos
	popToSel[0].cfitness = popToSel[0].rfitness;
    for (mem = 1; mem < POP; mem++){
		if (!isNull(popToSel[mem])){
        	popToSel[mem].cfitness = popToSel[mem-1].cfitness + popToSel[mem].rfitness;
			cout << "cfitness["<<mem<<"]: " << popToSel[mem].cfitness << endl;
		}
    }
	getchar();

//	cout << "1 selection typeNumber: " << typeNumber << endl;
//	getchar();
	// Seleccionamos un numero random para elegir a nuestro individuo
	while (selected < n){
			cout << "selected: " << selected << endl;
			cout << "n: " << n << endl;
			p = rand()%1000/1000.0;
			for (i = 0; i < POP; i++) {
				if ( i == 0){

					cout << "if ("<<p<<" < "<<popToSel[0].cfitness<<" && "<<!isNull(popToSel[0])<<endl;
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
	for (int j = 0; j < tp; j++){
	    cout << "types[j][1]: " << types[j][1] << endl;
	}
	getchar();



	typeNumber = tp;
//	cout << "fin selection typeNumber: " << typeNumber << endl;
//	getchar();
}

void sortPop(struct cell p[POP+1]){
	int i,j;
	struct cell tmp;
	//Bubble Sort
//	cout << "--Sort Pop--" << endl;
	for (i = 0; i < POP; i++) {
		for (j = i+1; j < POP; j++) {
			if (p[i].fitness > p[j].fitness && !isNull(p[i]) &&  !isNull(p[j])){
				tmp = p[i];
		 	 	p[i] = p[j];
		 	 	p[j] = tmp;
			}
		}
	}
//	printPop(p);
}

//void clonation(){
void clonation(struct cell clone[POP+1], bool type){
	int i=0,j=0,n=0, counter[POP], k=0,var=0;
	double m[POP+1], intPart, decPart;
	//cout << "--Clonacion--" << endl;
	if (type){
	//	cout << "Clonamos..." << endl;
		sortPop(clone);
		//printPop(clone);
		
		for (i=0;i<POP;i++){
			if(isNull(clone[i]))
				break;
			n++;
		}
	//	cout << "El n:" << n << endl;
	//	getchar();

		for (i=0;i<n;i++){
				m[i] = (float)(clonationFactor*n)/(float)(i+1);
	//			cout << "m["<<i<<"]: "<< m[i] << endl;
				decPart = modf(m[i],&intPart);
	//			cout << "decPart:" << decPart << "\t intPart: "<<intPart << endl;
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
	//			cout <<"n: "<<n<<"  k: "<< k << "  counter["<<i<<"]: " << counter[i] << endl;
	//			getchar();
				clone[k] = clone[i];
				k++;
				if (k >= POP){
					k = 0;
				}
			}
		}
	}
	else{
		sortPop(clone);

		for (i=0;i<POP;i++){
			if(isNull(clone[i]))
				break;
			n++;
		}
		k=n;
		var = (int)((POP-n)*0.5);
        for(i=0;i<n;i++){
            for (j=0; j<var; j++){
                clone[k] = clone[i];
                k++;
            }
			var = var - (int)(POP*0.1);
			
        }
		
	}
	
	for (i = 0; i < POP; i++) {
		clonePop[i] = clone[i];
	}
//	printPop(clone);
}

// HyperMutacion
void hypermutation(){
	int i, j, random_1, random_2, tmp;
	sortPop(clonePop);
	//printPop(clonePop);
	for(i=0;i<POP;i++){
		if(!isNull(clonePop[i])){

			// Cambiar a mutar solo por el indice
			//for(j=0;j<round(mutRate * clonePop[i].fitness);j++){
			//for(j=0;j<(i+1)*VARS*0.2;j++){
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

void cloneSelection(int n, struct cell popToSel[POP+1], bool type){
	int i,j;
//	cout << "--Clone Selection--" << endl;
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
	else{
		selection(n,popToSel);
	}

//	printPop(tmpPop);

}

// Insertar los mejores entre population y clonePop
void cloneInsertion(){
//	cout << "--Clone Insertion--" << endl;
	int i;
	for (i = 0; i < POP; i++) {
		population[i] = tmpPop[i];
	}
//	printPop(population);

}

void newGeneration(int counter, bool type){
//	cout << "New generation..." << endl;
    int i=0,j=0,k=0,c=0,temp=0,r=0;
    int p[VARS];
    srand(time(0));
	// Inicializamos en p[] la cantidad requerida por cada tipo
	//  de autos, satisfaciendo asi las restricciones duras
//	cout << "typeNumber: " << typeNumber << endl;
//	getchar();

	
//	for (j = 0; j < typeNumber; j++){
//	    cout << "types[j][1]: " << types[j][1] << endl;
//	}
//	getchar();






	for (j = 0; j < typeNumber; j++){
//		cout << "while ("<<k<<" < " << types[j][1] << endl;
	    while(k < types[j][1]){
	        p[i] = j;
//			cout << " 1 p["<<i<<"]: "<< p[i] << endl;
	        k++;i++;
	    }
	    k = 0;
	}
//	cout << "i = "<< i << endl;
	getchar();
	i = 0;
	temp=0;
	r=0;

	for (j = 0; j < counter; j++) {
	        for (i=0; i<VARS; i++) {
	            r = i + (rand() % (VARS-i));
//				cout << "r: " << r << endl;
	            temp = p[i];
//				cout << "p[i] " << p[i]<< endl;
	            p[i] = p[r];
	            p[r] = temp;
//				cout << "p["<<r<<"]: " << p[r] << endl;
	        }
	//		getchar();
//				cout << "temp: " << temp << endl;
//				getchar();
	        // Guardamos nuestros valores en la estructura de   la poblacion
			// Mas malos reemplazados
			for (c=0; c<VARS; c++) {
//				cout << "p[c] = " << p[c] << endl;
//				getchar();
//				cout << "POP-1-j : " << POP-1-j << endl;
//				cout << "p["<<c<<"]: "<< p[c] << endl;
	           	population[POP-1-j].gene[c] = p[c];
				cout << "population["<<POP-1-j<<"].gene["<<c<<"]: " << population[POP-1-j].gene[c] << endl;
			}
	}
	getchar();
//	cout << "--New generation--" << endl;
//	printPop(population);
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
