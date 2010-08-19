/*
 * Programa Jugoso Curso
 * ---------------------
 *  Este programa se dedica solo a leer los archivos que se le entregan como argumento, calcular
 *  su desviacion estandar y su media, luego añade los valores a las colas de mensajes para poder
 *  ser utilizados por el programa Jugoso Principal
 * 
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int i=0,n[200];
struct mensaje {
	int tipo;
	float cantidad;
};
float calculaPromedio();
float calculaDesviacion(float prom);

int main(int argc, char* argv[]){

	struct mensaje datosMedias,datosDesv;
	int medias,desv,longitud;
	float prom=0,ds=0;
	char res[20];
	FILE *notas, *resFile;
	//Accedemos a las colais de mensajes
	medias=msgget((key_t)1234,0666|IPC_CREAT);//cola de medias
	desv=msgget((key_t)1235,0666|IPC_CREAT);//cola de desviaciones
	strcpy(res,argv[1]);
	strcat(res,".res");
	notas=fopen(argv[1],"r");
	resFile=fopen(res,"w");

	longitud = sizeof(struct mensaje)-sizeof(int);//longitud del mensaje

	if(argc == 1){
		printf("No se paso ningun archivo\n");
		return 0;
		}
	else if(argc == 2){
		while(fscanf(notas,"%d",&n[i]) != EOF){
			i++;	
		}
	}
	else{
		printf("Se pasaron mas de un parametro\n");
		return 0;
		}
	//Hacemos los calculos
	prom=calculaPromedio();
	ds=calculaDesviacion(prom);
	//añadimos los valores a los mensajes
	datosMedias.tipo=1;
	datosMedias.cantidad=prom;
	datosDesv.tipo=1;
	datosDesv.cantidad=ds;

	//Enviamos los mensajes a la cola
	msgsnd(medias,(void*)&datosMedias,longitud,0);
	msgsnd(desv,(void*)&datosDesv,longitud,0);
	//escribimos el resultado en el archivo .res
	fprintf(resFile,"prom: %f\nds: %f\n",prom,ds);
	return 0;
}


float calculaPromedio(){
	int j=i,sum=0;
	float prom=0;
	while(j>0){
		sum = sum + n[j-1];
		j--;
	}

	prom=(float)sum/(float)i;
	return prom;
}

float calculaDesviacion(float prom){
	int j=i;
	float desv=0,a=2.0;
		while(j>0){
			desv=desv + pow(((float)n[j-1]-prom),a);
			j--;
		}
		desv=sqrt(desv/(float)i);
		return desv;
}
