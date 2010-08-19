#include "include/ea.cpp"

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
	evaluation();

	while(generation<GENS){
		while ( itePop < POP-1 ){
		    individualSelection();
		    mutation();
		}
		elitism();
		changePop();
	    evaluation();
	    generation++;
		itePop = 0;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

	printFile(argv[1],population[best_mem].gene,population[best_mem].fail,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));

	return 0;
}
