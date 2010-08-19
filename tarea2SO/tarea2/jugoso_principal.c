/*
 * Programa Principal
 * crea las colas de mensajes, ejecuta a jugoso_curso con cada argumento que se le entregue
 * para que haga los calculos correspondientes.
 * luego hace los ultimos calculos y elimina las colas de mensajes
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
#include <sys/wait.h>

struct mensaje {
	int tipo;
	float cantidad;
};
float m[200],d[200];//arreglo para las medias y las desviaciones
int i=0;

float calculaPromedio();
float calculaPromedioDesv();//necesario para poder calcular la desviacion de las desviaciones
float calculaDesviacion(float prom);

int main(int argc, char* argv[]){

	int pid,valor,medias,desv,longitud;
	struct mensaje datosMedias,datosDesv;
	int tipo=0;
	float promProm,desvDesv,promDesv;

	longitud = sizeof(struct mensaje) - sizeof(long int);//largo del mensaje
	//Creamos las colas de mensajes
	medias=msgget((key_t)1234,0666|IPC_CREAT);
	desv=msgget((key_t)1235,0666|IPC_CREAT);

	if(argc == 1){
		printf("No se pasaron parametros...saliendo\n");
		return 0;
		}
	else{
		for(i=1;i<argc;i++){
			pid = fork();//Por cada archivo se crea un nuevo proceso para que haga los calculos
			if(pid < 0){
				printf("Error\n");
			}
			else if(pid == 0){
				execlp("./jugoso_curso","./jugoso_curso",argv[i],NULL);//ejecutamos a jugoso_curso con 1 archivo
			}
			else{
				 while (wait(&valor) != pid);//el padre espera que el proceso hijo termine
			}
		}
	}
	for(i=1;i < argc;i++) {
		// Leemos los mensajes que estan en las colas
		msgrcv(medias,(void *)&datosMedias,longitud,tipo,0);
		msgrcv(desv,(void *)&datosDesv,longitud,tipo,0);
		//guardamos los mensajes en nuestros arreglos para medias y desviaciones
		m[i-1]=datosMedias.cantidad;
		d[i-1]=datosDesv.cantidad;
		}
	//Hacemos los calculos
	promProm=calculaPromedio();
	promDesv=calculaPromedioDesv();
	desvDesv=calculaDesviacion(promDesv);
	//Mostramos por pantalla los datos finales
	printf("prom:%f\nds:%f\n",promProm,desvDesv);
	//Eliminamos las colas de mensajes
	msgctl(medias,IPC_RMID,0);
	msgctl(desv,IPC_RMID,0);
	return 0;
}

float calculaPromedio(){
	int j=i-1;
	float prom=0,sum=0;
	while(j>0){
		sum = sum + m[j-1];
		j--;
	}
	prom=(float)sum/(float)(i-1);
	return prom;
}


float calculaPromedioDesv(){
	int j=i-1;
	float prom=0,sum=0;
	while(j>0){
		sum = sum + d[j-1];
		j--;
	}
	prom=(float)sum/(float)(i-1);
	return prom;
}

float calculaDesviacion(float prom){
	int j=i-1;
	float desv=0,a=2.0;
	if(i-2>0){
		while(j>0){
			desv=desv + pow((d[j-1]-prom),a);
			j--;
		}
		desv=sqrt(desv/(float)(i-1));
		return desv;
	}
	else return 0;
}
