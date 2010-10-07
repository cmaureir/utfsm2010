#ifndef clonal_H
#define clonal_H

#include "extra.cpp"

// Funcion encargada de la inicializacion de la poblacion
void initPopulation(bool type);

// Funcion encargada de evaluar la poblacion
void evaluation(bool type);

// Seleccion de los individuos mediante Ruleta
// En la FO se minimiza
void selection(int n);

// Clonacion
void clonation();

// Funcion de Hypermutacion
void hypermutation();

// Seleccion de los mejores clones
void cloneSelection();

// Inserción de clones
void cloneInsertion(int n);

// Creación de nueva generación
void newGeneration();

// Reemplazo de la nueva generación dentro de la poblacion inicial
void replace();

#endif
