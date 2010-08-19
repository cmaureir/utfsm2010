/* Programa para retirar mensajes de la cola */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* Estructura para los mensajes */
struct mensaje {
int tipo;
float digitos;
};

int main(){
	struct mensaje datos;
	int msgid,longitud,pid,valor;
	int tipo=0;
	msgid=msgget((key_t)1234,0666|IPC_CREAT);

	pid=fork();

	longitud=sizeof(struct mensaje)-sizeof(int);
	/* Creando o accesando la cola de mensajes */

	if(pid==0){

	printf("voy a ejecutar!\n");
	execlp("./agregar",0);
	printf("sali\n");
	}
	else{
			 while (wait(&valor) != pid); 
			printf("Padre\n");

		}


	/* Leer de la cola hasta "fin" */
	printf("%f\n\n",datos.digitos);
	while(datos.digitos != 0) {
		/* Leyendo el mensaje de la cola */
		msgrcv(msgid,(void *)&datos,longitud,tipo,0);
		printf("Escribiste: %f\n", datos.digitos);
	}

	/* Eliminando la cola de mensajes */
	msgctl(msgid,IPC_RMID,0);
exit(0);
}
