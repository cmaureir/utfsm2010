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

	srand(1925);
	initPopulation();
	evaluation(population);

	int psBajos = 0, psCeros = 0 , psAltos = 0;
	int smBajos = 0, smCeros = 0 , smAltos = 0;
	while(generation<GENS){
		srand(generation);
		cout << "-----" << endl;
		cout << "Iteracion: " << generation << endl;
		cleanPops();
//		averageFitness(true);
//		sortPop(population);
		saveBest(true);

		selection(clonationRate, population);
		clonation(tmpPop);
		hypermutation();
		evaluation(clonePop);
		cloneSelection(clonePop);
	
//		sortPop(clonePop);
//		saveBest(false);
//		averageFitness(false);

		pS[generation] = bestNewCellFitness - bestCellFitness; 
		sM[generation] = newCellAverage - cellAverage;

		// CONDICIONES

//Inicial

//		if( pS[generation] > 0 ){
//			psAltos++;
//		}
//		else if( pS[generation] == 0 ){
//			psCeros++;
//		}
//		else if( pS[generation] < 0 ){
//			psBajos++;
//		}
//		if( sM[generation] > 0 )
//			smAltos++;
//		else if( sM[generation] == 0 )
//			smCeros++;
//		else if( sM[generation] < 0 )
//			smBajos++;


//// Forma 1		
//		if( pS[generation] < 0 ){
//			psAltos++;
//			if (psAltos == (int)(GENS*0.002)){
//				replaceRate -= (int)(POP*0.1);
//				//replaceRate = (int)(POP*0.3);
//				psAltos = 0;
//			}
//		}
//		else if( pS[generation] == 0 ){
//			psCeros++;
//			replaceRate = (int)(POP*0.5);
//			psAltos = 0;
//			psBajos = 0;
//		}
//		else if( pS[generation] > 0 ){
//			psBajos++;
//
//			if (psBajos == (int)(GENS*0.002) && replaceRate < (int)(POP*0.9)){
//				replaceRate += (int)(POP*0.1);
//				//replaceRate = (int)(POP*0.9);
//				psBajos = 0;
//			}
//		}

////Forma 2
//		if ( pS[generation] < 0 && clone_control < (int)(POP*0.1)){
//			clone_control += 1;
//		}
//		else if (pS[generation] > 0 && clone_control > -(int)(POP*0.1)){
//			clone_control -= 1;
//		}
////		else if (pS[generation] == 0){
////			clone_control = 0;
////		}
//
//		if (pS[generation] < 0 && sM[generation] > 0 && clonationRate > 2){
//			clonationRate -= 1;
//		}
//		else if (clonationRate < (int)(POP*0.9) ){
//			clonationRate += 1;
//		}

		cloneInsertion();
		newGeneration(replaceRate);
		evaluation(population);
//		
		cout << "Fitness: " << bestCellFitness << endl;
//		cout << "clone_control: " << clone_control << endl;
//		cout << "clonationRate: " << clonationRate << endl;
		cout << "replaceRate: " << replaceRate << endl;
		if ( generation != 0 && generation%2000 == 0 && replaceRate >= (int)(POP*0.5))
			replaceRate -= (int)(POP*0.1);
		if (bestCellFitness == 0)
			generation = GENS;
		generation++;
	}

//	cout << "PS" << endl;
//	cout << "Altos: " << psAltos << endl;
//	cout << "Ceros: " << psCeros << endl;
//	cout << "Bajos: " << psBajos << endl;
//
//	cout << "SM" << endl;
//	cout << "Altos: " << smAltos << endl;
//	cout << "Ceros: " << smCeros << endl;
//	cout << "Bajos: " << smBajos << endl;

	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
//	printFile(population[0].fitness);
//	cout  << replaceRate << " " << (float)((float)replaceRate/(float)POP) << " "<<population[0].fitness << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<abs(te.tv_nsec-ts.tv_nsec) << endl;
	cout  << population[0].fitness << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<abs(te.tv_nsec-ts.tv_nsec) << endl;
	for (int cars = 0 ; cars < VARS ; cars ++ ){
		cout << population[0].gene[cars] << " ";
	}
	cout << endl;

	return 0;
}
