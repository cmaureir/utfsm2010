/*
Tarea 1 SO
Cristian Maureira Fredes
2673030-9 
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

DIR *dir;
struct dirent *di;
struct stat filestat;
unsigned int Stat;
char ruta[200];
char directorio[200];
char permisos[11];

void setPermisos(char directory[200]){
	while ((di = readdir(dir)) != NULL){
		strcpy(ruta, directory);//copiamos el directorio a ruta
		strcat(ruta, "/");//añadimos un "/" al directorio actual
		strcat(ruta, di->d_name);//añadimos el nombre del fichero que estamos leyendo a ruta
		lstat(ruta,&filestat);//obtenemos el status de nuestro link simbolico al archivo
		Stat = filestat.st_mode;//obtenemos el modo del archivo(directorio, link simbolico,...)
		if(S_ISDIR(Stat))      permisos[0]='d';//directorio
		else if(S_ISCHR(Stat)) permisos[0]='c';//archivo de caracter especial
		else if(S_ISBLK(Stat)) permisos[0]='b';//archivo de bloque especial
		else if(S_ISFIFO(Stat))permisos[0]='p';//pipe o archivo de fifo especial
		else if(S_ISLNK(Stat)) permisos[0]='l';//link simbolico
		else if(S_ISSOCK(Stat))permisos[0]='s';//socket
		else if(S_ISREG(Stat)) permisos[0]='-';//archivo regular
		//Permisos del Owner
		if(Stat & S_IRUSR) permisos[1]='r';//lectura
		else  permisos[1]='-';
		if(Stat & S_IWUSR) permisos[2]='w';//escritura
  		else permisos[2]='-';
 		if(Stat & S_IXUSR) permisos[3]='x';//ejecucion
		else permisos[3]='-';
		//Permisos de Grupos
		if(Stat & S_IRGRP) permisos[4]='r';//lectura
		else permisos[4]='-';
		if(Stat & S_IWGRP) permisos[5]='w';//escritura
	        else permisos[5]='-';
		if(Stat & S_IXGRP) permisos[6]='x';//ejecucion
		else permisos[6]='-';
		//Permisos para Otros
		if(Stat & S_IROTH) permisos[7]='r';//lectura
		else permisos[7]='-';
		if(Stat & S_IWOTH) permisos[8]='w';//escritura
		else permisos[8]='-';
		if(Stat & S_IXOTH) permisos[9]='x';//ejecucion
		else permisos[9]='-';
	
		permisos[10]='\0';//fin de string
		printf("%s %s\n",permisos,di->d_name);//imprimimos los permisos y el fichero
	}
}

int main(int argc, char* argv[]){
	int i=0;
	//Directorio Actual
	if(argc == 1){
		strcpy(directorio,".");
	       	dir=opendir(directorio);
		setPermisos(directorio);
		closedir(dir);
	}
	//Directorios por argumento
	for(i=1;i<argc;i++){
		strcpy(directorio,argv[i]);
		printf("%s:\n",directorio);
	       	dir=opendir(directorio);
		setPermisos(directorio);
		closedir(dir);
		if(i+1 < argc) printf("\n");
	}
	return 0;
}
