#ifndef sa_H
#define sa_H

#include "extra.cpp"

int iteration = 0;			// Numero de iteraciones
int tmpSol[VARS];			// Solucion temporal
double temp = (double)TMAX; // Temperatura
double p;					// Probabilidad del SA (exp) 
double p_new;				// Random para comparar con p

// Funcion de Movimiento
// Consiste en un swap pero con una cantidad de veces equivalente
//  al 10% del numero de variables.
void saMovement();

// Funcion de Aceptacion
bool saAcceptance();

// Funcion encargada de reducir la temperatura despues de 3 iteraciones
void saTDecrease();

// Funcion que calcula el fitness de una solucion determinada
int getFitness(int individual[VARS]);

// Implementacion central del algoritmo SA + AM
void simulatedAnnealing();

#endif
