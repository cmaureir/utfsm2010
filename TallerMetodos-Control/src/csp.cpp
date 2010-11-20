#include "include/clonal.cpp"

int main(int argc, const char *argv[])
{
	// 'true' satisfaccion restricciones duras
	bool type = true;
	// 'true' selecciona mejores
	bool cloneSelType = true;
	// 'true' remplaza los mas malos
	bool replaceType = true;
	// 'true' Se clonan mediante formula
	bool cloneType = true;

	timespec ts, te;

	clock_gettime(CLOCK_REALTIME, &ts);
	population[POP].fitness = 10000;	
	if(!checkFile(argc,argv))
		return 0;
	
	inputReading(argv[1]);
	generation = 0;

	srand(1925);
	initPopulation(type);
	evaluation(population, type);

	while(generation<GENS){
		srand(generation);
		cout << generation << endl;
		cleanPops();
		// calcular promedio de los fitness de la pop
		averageFitness(true);
		// obtener mejor fitness
		saveBest(true);
		selection(clonationRate, population);
		clonation(tmpPop, cloneType);
		// OJO calcular C, numero de clones
		hypermutation();
		evaluation(clonePop, type);
		// fitness del mejor anticuerpo de clones
		cloneSelection(clonePop, cloneSelType);
		saveBest(false);
		// calcular promedio de los fitness de la tmpPop
		averageFitness(false);
		// Calcular success measure
		// Calcular stuck measure
		// CONDICIONES 
		cloneInsertion();
		newGeneration(replaceRate, replaceType);
		evaluation(population, type);
		
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
//	printFile(population[0].fitness);
	cout  << population[0].fitness << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<abs(te.tv_nsec-ts.tv_nsec) << endl;

	return 0;
}
