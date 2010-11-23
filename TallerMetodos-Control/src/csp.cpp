#include "include/clonal.cpp"

int main(int argc, const char *argv[])
{
	timespec ts, te;

	clock_gettime(CLOCK_REALTIME, &ts);
	population[POP].fitness = 10000;	
	if(!checkFile(argc,argv))
		return 0;
	
	inputReading(argv[1]);
	generation = 0;

//	srand(1925);
	srand(time(0));
	initPopulation();
	evaluation(population);

	int bajos = 0, ceros = 0 , altos = 0;


	while(generation<GENS){
		srand(generation);
//		cout << "---------------" << endl;
//		cout << "Iteracion: " << generation << endl;
		//cout << "replaceRate: " << replaceRate << endl;
		cleanPops();
		// calcular promedio de los fitness de la pop
//		averageFitness(true);
		// obtener mejor fitness
//		sortPop(population);
//		saveBest(true);
		selection(clonationRate, population);
		clonation(tmpPop);
		// OJO calcular C, numero de clones
		hypermutation();
		evaluation(clonePop);
		// fitness del mejor anticuerpo de clones
		cloneSelection(clonePop);
//		sortPop(clonePop);
//		saveBest(false);
//		// calcular promedio de los fitness de la tmpPop
//		averageFitness(false);
//		// Calcular success measure
//		pS[generation] = bestNewCellFitness - bestCellFitness; 
//		// Calcular stuck measure
//		sM[generation] = newCellAverage - cellAverage;
//		// CONDICIONES
//
//		if( pS[generation] > 0 )
//			altos++;
//		else if( pS[generation] == 0 )
//			ceros++;
//		else if( pS[generation] < 0 )
//			bajos++;
//
//		cout << "ps[]: " << pS[generation] << endl;
//		cout << "sM[]: " << sM[generation] << endl;
//		if ( pS[generation] > 0 && clone_control < POP/2){
//			clone_control += 1;
//		}
//		else if (pS[generation] < 0 ){
//			clone_control -= 5;
//		}
//		else if (pS[generation] == 0){
//			clone_control = 0;
//		}
//
//		if (sM[generation] < 0 && clonationRate < POP){
//			clonationRate += 1;
//		}
//		else if (clonationRate > 2){
//			cout << "entro" << endl;
//			getchar();
//			clonationRate -= 1;
//		}
//		if (sM[generation] < 0 && replaceRate > 0){
//			replaceRate -= 1;
//		}
//		else if (sM[generation] >= 0 && replaceRate < POP) {
//			replaceRate += 1;
//		}
//		if (replaceRate == 0 && generation%((int)(POP*0.2)) == 0){
//			replaceRate =  (int)POP - clonationRate;
//		}
		//replaceRate =  (int)POP - clonationRate;
//		if (generation != 0 && generation%600 == 0){
//			replaceRate = (int)(replaceRate/2);
////			clonationRate += (int)(clonationRate/2);
//		}
		cloneInsertion();
		newGeneration(replaceRate);
		evaluation(population);
//		
//		cout << "clone_control: " << clone_control << endl;
//		cout << "Fitness: " << bestCellFitness << endl;
//		cout << "clonationRate: " << clonationRate << endl;
//		cout << "replaceRate: " << replaceRate << endl;

//	cout << "Altos: " << altos << endl;
//	cout << "Ceros: " << ceros << endl;
//	cout << "Bajos: " << bajos << endl;
		generation++;
	}


	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
//	printFile(population[0].fitness);
	cout  << population[0].fitness << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<abs(te.tv_nsec-ts.tv_nsec) << endl;

	return 0;
}
