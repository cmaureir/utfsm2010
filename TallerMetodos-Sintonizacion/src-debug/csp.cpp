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

	cout << "ClonationFactor: "<<clonationFactor << "\t" << "ClonationRate: " << clonationRate << endl;
	
	inputReading(argv[1]);
	generation = 0;

	initPopulation(type);
	evaluation(population, type);

	while(generation<GENS){
		cout << "ini while" << endl;
		cleanPops();
		cout << "fin cleanpop" << endl;
		selection(clonationRate, population);
		cout << "fin selection" << endl;
		clonation(tmpPop, cloneType);
		cout << "fin clonation" << endl;
		hypermutation();
		cout << "fin hyp" << endl;
		evaluation(clonePop, type);
		cout << "fin eval 1" << endl;
		cloneSelection(selRate, clonePop, cloneSelType);
		cout << "fin clone sel" << endl;
		cloneInsertion();
		cout << "fin clone inse" << endl;
		newGeneration(replaceRate, replaceType);
		cout << "fin new gen" << endl;
		evaluation(population, type);
		cout << "fin eval 2" << endl;
		generation++;
	}
	
	clock_gettime(CLOCK_REALTIME, &te);

//	printFile(argv[1],population[0].gene,population[0].fitness,(te.tv_sec-ts.tv_sec), (te.tv_nsec-ts.tv_nsec));
	cout << population[0].fitness << endl;

	return 0;
}
