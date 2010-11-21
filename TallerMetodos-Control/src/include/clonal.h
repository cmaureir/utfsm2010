#ifndef clonal_H
#define clonal_H

#include "extra.cpp"

void averageFitness(bool option);
void saveBest(bool option);

// Funcion encargada de la inicializacion de la poblacion
void initPopulation();

// Funcion encargada de evaluar la poblacion
void evaluation(struct cell evalPop[POP+1]);

// Seleccion de los individuos mediante Ruleta
// En la FO se minimiza
void selection(int n, struct cell popToSel[POP+1]);

void sortPop(struct cell *p[POP+1]);

// Clonacion
void clonation(struct cell *clonePop[POP+1]);

// Funcion de Hypermutacion
void hypermutation();

// Seleccion de los mejores clones
void cloneSelection(struct cell popToSel[POP+1]);

// Inserción de clones
void cloneInsertion(int n);

// Creación de nuevos elementos e inserción en los peores lugares de la poblacion
void newGeneration(int counter);

void printPop(struct cell tmp[POP]);
void cleanPops();
#endif
