#include "include/clonal.cpp"

int main(int argc, const char *argv[])
{
	// 'true' satisfaccion restricciones duras
	// 'false' completamente aleatorias
	bool type = false;	


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
		selection(clonationRate);
		clonation();
		hypermutation();
		evaluation(mutPop, type);
		getchar();
		cloneSelection(VARS*0.1);
		cloneInsertion();
		newGeneration();
		replace();
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

	printFile(argv[1],population[best_mem].gene,population[best_mem].fail,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));

	return 0;
}
