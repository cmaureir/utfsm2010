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

	changeParam(argv);
//	cout << "ClonationFactor: "<<clonationFactor << endl;
//	cout << "ClonationRate: " << clonationRate << endl;
//	cout << "ReplaceRate: " << replaceRate << endl;
	
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
		cloneSelection(clonePop, cloneSelType);
		cloneInsertion();
		newGeneration(replaceRate, replaceType);
		evaluation(population, type);
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
//	printFile(population[0].fitness);
	cout << replaceRate << " " << population[0].fitness << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<(te.tv_nsec-ts.tv_nsec) << endl;

	return 0;
}
