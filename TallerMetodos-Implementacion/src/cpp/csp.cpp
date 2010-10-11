#include "include/clonal.cpp"

int main(int argc, const char *argv[])
{
	// 'true' satisfaccion restricciones duras
	// 'false' completamente aleatorias
	bool type = true;	

	// 'true' mejores
	// 'false' ruleta
	bool cloneSelType = true;

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
	//	cout << "Generación: " << generation << endl;
	//	printPop(population);
		cleanPops();
		selection(clonationRate, population);
		clonation(tmpPop);
		hypermutation();
		evaluation(clonePop, type);
		cloneSelection(selRate, clonePop, cloneSelType);
		cloneInsertion();
		newGeneration(replaceRate);
		evaluation(population, type);
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

	printFile(argv[1],population[0].gene,population[0].fail,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));

	return 0;
}
