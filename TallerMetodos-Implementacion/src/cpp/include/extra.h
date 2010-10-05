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
#define VARS 10    // Numero de autos


// Variables Problema
#define POP  10    // Tamaño poblacion
#define GENS 20  // Numero maximo de generaciones
#define N 128	   // Variable para crear arreglos determinados


struct genotype {  		// Individuo de la poblacion
    int gene[VARS];     // Automoviles
	int fitness;		// Valor evaluacion de la FO
	int fail;			// Cantidad de restricciones insatisfechas
	double rfitness;    // Fitness relativo
	double cfitness;    // Fitness acumulado
} population[POP+1],    // Poblacion Actual
  clonePop[POP+1],		// Nueva población con los primeros seleccionados y luego los clones
  mutPop[POP+1],		// Población con los clones mutados
  tmpPop[POP+1];		// Poblacion Temporal con seleccionados de clones


// Variables Generales del problema
int carNumber;				// Numero de autos
int optNumber;			 	// Numero de opciones
int typeNumber;				// Numero de tipos de autos
int numMaxCarOptSeq[N];		// Numero maximo de autos con la opcion i en una subsecuencia
int sizeMaxCarOptSeq[N];	// Tamaño de la subsecuencia donde debe haber un numMaxCarOptSeq
int types[N][N];			// Arreglo bidimensional que posee [tipoDeAuto(indice)][N]
							//  donde N es tipoDeAuto(indice), demandaDeAuto (int), tieneOpcion_i (1 o 0)

int generation; 	    // Numero de generaciones
int itePop=0; 			// Contador de poblacion
int worst_mem;		    // Indice del peor individuo de la poblacion
int best_mem;			// Indice del mejor individuo de la poblacion

// Funcion encargada de la interpretacion del archivo de entreda
void inputReading(const char name[50]);

// Funcion que permite desplegar por pantalla el contenido del archivo
void showFile(); 

// Funcion encargada de escribir el archivo de salida del programa
void printFile(const char c_name[50], int sol[512], int failCon, int sec, int nsec);

// Funcion encargada de verificar si el archivo de entrada es correcto
bool checkFile(int argc, const char *argv[]);

#endif
