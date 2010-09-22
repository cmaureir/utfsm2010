/* Programa para agregar mensajes a la cola */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* Estructura para mensajes */
struct mensaje {
int tipo;
float digitos;
};

int main(){

	struct mensaje datos;
	int msgid,longitud,contador=0;
	float bufer=1;
	longitud=sizeof(struct mensaje)-sizeof(int);
	/* Creando la cola de mensajes */
	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	
	/* Leer del teclado hasta "fin" */
	while((int)bufer != 0) {
		printf("%d\n\n",(int)bufer);
		printf("Escribe num ... ");
		scanf("%f",&bufer);
		datos.tipo=1;
		datos.digitos=bufer;
		/* Enviando el mensaje */
		msgsnd(msgid,(void*)&datos, longitud,0);
		}
return 0;
}
