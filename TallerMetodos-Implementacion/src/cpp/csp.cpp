#include "include/clonal.cpp"

int main(int argc, const char *argv[])
{
	// 'true' satisfaccion restricciones duras
	// 'false' completamente aleatorias
//	bool type = true;
	bool type = argv[2];	

	// 'true' selecciona mejores
	// 'false' selecciona mediante ruleta
//	bool cloneSelType = true;
	bool cloneSelType = argv[3];

	// 'true' remplaza los mas malos
	// 'false' reemplaza aleatoriamente
//	bool replaceType = true;
	bool replaceType = argv[4];

	// 'true' Se clonan mediante formula
	// 'false' Se clonal numero fijo de veces
//	bool cloneType = true;
	bool cloneType = argv[5];

	timespec ts, te;

	clock_gettime(CLOCK_REALTIME, &ts);
	population[POP].fitness = 10000;	
	if(!checkFile(argc,argv))
		return 0;
	inputReading(argv[1]);
	generation = 0;

	initPopulation(type);
	evaluation(population, type);

	while(generation<GENS){
		cleanPops();
		selection(clonationRate, population);
		clonation(tmpPop, cloneType);
		hypermutation();
		evaluation(clonePop, type);
		cloneSelection(selRate, clonePop, cloneSelType);
		cloneInsertion();
		newGeneration(replaceRate, replaceType);
		evaluation(population, type);
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
	cout << "FITNESS: " << population[0].fitness << endl;

	return 0;
}
