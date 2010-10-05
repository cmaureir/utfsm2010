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

	initPopulation();
	evaluation(population);

	while(generation<GENS){
		selection(VARS*0.2);
		clonation();
		hypermutation();
		evaluation(mutPop);
		getchar();
		cloneSelection(VARS*0.1);
		cloneInsertion();
		newGeneration();
		replace();
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

	printFile(argv[1],population[best_mem].gene,population[best_mem].fail,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));

	return 0;
}
