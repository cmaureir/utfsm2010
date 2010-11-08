#include "extra.h"


void inputReading(const char name[50]){
	int i,j,tmp;
	FILE *in;
	in = fopen(name,"r");
	// Primera linea
	// Numero de Autos - Numero de Opciones - Numero de Tipos de Autos.
	fscanf(in,"%d %d %d\n",&carNumber, &optNumber, &typeNumber);
	// Segunda linea
	// cantidad de autos permitidos en la subsecuencia con la opción i
	for (i = 0; i < optNumber; i++) {
		fscanf(in,"%d",&tmp);
		numMaxCarOptSeq[i] = tmp;
	}
	// Tercera linea
	// tamaño de la subsecuencia i
	for (i = 0; i < optNumber; i++) {
		fscanf(in,"%d",&tmp);
		sizeMaxCarOptSeq[i] = tmp;
	}

	// Resto de lineas
	// Tipo de auto - Cantidad de autos que la tienen - Tiene la opcion i (1 o 0)
	for (i = 0; i < typeNumber; i++) {
		fscanf(in,"%d %d",&types[i][0],&types[i][1]);
		for (j = 0; j < optNumber; j++){ 
			fscanf(in,"%d",&types[i][j+2]);
		}

	}
	fclose(in);
}

void showFile(){
	int i,j;
	cout << carNumber << " " << optNumber << " " << typeNumber << endl;

	for (i = 0; i < optNumber; i++) {
		cout << numMaxCarOptSeq[i] << " ";
	}
	cout << endl;

	for (i = 0; i < optNumber; i++) {
		cout << sizeMaxCarOptSeq[i] << " ";
	}
	cout << endl;

	for (i = 0; i < typeNumber; i++) {
		for (j = 0; j < optNumber + 2; j++){ 
			cout << types[i][j] << " ";
		}
		cout << endl;
	}
}

//void printFile(const char c_name[50], int sol[VARS], int failCon, int sec, int nsec){
void printFile(int failCon){
	FILE *out;
//	int i=0;

	// Transformacion del nombre en const char a char
	//char *_name = const_cast<char*>(c_name);
	//char name[50];
	//strncpy(name,_name,strlen(_name)-4);	
	//name[strlen(_name)-4] = '\0';

	//strcat(name,".out");
	//out = fopen(name,"a+");

	//fprintf(out,"Secuencia de vehiculos : ");
	//for(i=0;i<carNumber;i++)
	//	fprintf(out,"%d ",sol[i]);

	//if( nsec  < 0 ){
	//	nsec = nsec * -1;
	//}
	//fprintf(out,"\nRestricciones insatisfechas : %d",failCon);
	//fprintf(out,"\nTiempo de ejecucion [s] : %d.%d",sec,nsec);

	//fclose(out);
	out = fopen("resultados-instancias.res","a+");
	fprintf(out,"%d\n",failCon);
	fclose(out);

}

bool checkFile(int argc, const char *argv[]){
	//if (argc != 6){
	if (argc != 5){
		cout << "Cantidad de parametros incorrecto:\n Ejecucion: ./csp archivo.txt" << endl;
		return false;
	}
	if (!strstr(argv[1],".txt")){
		cout << "NOMBRE: " <<argv[1] << endl;
		cout << "Nombre de archivo incorrecto:\n\tutilice extension .txt"<< endl;		
		return false;
	}
	return true;
}

void changeParam(const char *argv[]){

	clonationFactor = atof(argv[2]); //0.5 // Factor para calcular individuos clonados
	clonationRate = POP*atof(argv[3]); //POP*0.4 // Tasa para realizar la clonación
	replaceRate =  POP*atof(argv[4]); //POP*0.6  // Tasa para la cantidad de elementos reemplazados
}
