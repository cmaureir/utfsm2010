#ifndef ea_H
#define ea_H

#include "sa.cpp"

// Funcion encargada de la inicializacion de la poblacion
void initPopulation();

// Funcion encargada de evaluar la poblacion
void evaluation();

// Seleccion de un individuo mediante Ruleta
// En la FO se minimiza
void individualSelection();

// Funcion de Elitismo
// Pasamos siempre el mejor individuo de nuestra poblacion
//  a la siguiente.
void elitism();

// Funcion de Mutacion
// Simulated Annealing + Alguna Mejora
void mutation();

// Funcion encargada del cambio de una nueva poblacion
//  a la actual.
void changePop();

#endif
