#ifndef extra_H
#define extra_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <iostream>
using namespace std;

// IMPORTANTE:
// Variables establecidas a mano
// cambiar antes de ejecutar cada test
#define VARS 400    // Numero de autos


// Variables Problema
#define POP  20    // Tamaño poblacion
#define GENS 500  // Numero maximo de generaciones
#define N 128	   // Variable para crear arreglos determinados
#define clonationRate POP*0.4
#define selRate POP*0.4
#define replaceRate POP*0.6
#define swap VARS*0.4
#define clonationFactor 0.5

struct genotype {  		// Individuo de la poblacion
    int gene[VARS];     // Automoviles
	int fitness;		// Valor evaluacion de la FO
	double rfitness;    // Fitness relativo
	double cfitness;    // Fitness acumulado
} population[POP+1],    // Poblacion Actual
  clonePop[POP+1],		// Nueva población con los primeros seleccionados y luego los clones
  tmpPop[2*(POP+1)];		// Poblacion Temporal con seleccionados de clones


// Variables Generales del problema
int carNumber;				// Numero de autos
int optNumber;			 	// Numero de opciones
int typeNumber;				// Numero de tipos de autos
int numMaxCarOptSeq[N];		// Numero maximo de autos con la opcion i en una subsecuencia
int sizeMaxCarOptSeq[N];	// Tamaño de la subsecuencia donde debe haber un numMaxCarOptSeq
int types[N][N];			// Arreglo bidimensional que posee [tipoDeAuto(indice)][N]
							//  donde N es tipoDeAuto(indice), demandaDeAuto (int), tieneOpcion_i (1 o 0)

int generation; 	    // Numero de generaciones

// Funcion encargada de la interpretacion del archivo de entreda
void inputReading(const char name[50]);

// Funcion que permite desplegar por pantalla el contenido del archivo
void showFile(); 

// Funcion encargada de escribir el archivo de salida del programa
void printFile(const char c_name[50], int sol[512], int failCon, int sec, int nsec);

// Funcion encargada de verificar si el archivo de entrada es correcto
bool checkFile(int argc, const char *argv[]);

#endif
