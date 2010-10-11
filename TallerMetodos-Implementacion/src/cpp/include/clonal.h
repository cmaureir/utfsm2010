#ifndef clonal_H
#define clonal_H

#include "extra.cpp"

// Funcion encargada de la inicializacion de la poblacion
void initPopulation(bool type);

// Funcion encargada de evaluar la poblacion
void evaluation(bool type);

// Seleccion de los individuos mediante Ruleta
// En la FO se minimiza
void selection(int n, struct genotype popToSel[POP+1]);

void sortPop(struct genotype *p[POP+1]);

// Clonacion
void clonation(struct genotype *clonePop[POP+1]);

// Funcion de Hypermutacion
void hypermutation();

// Seleccion de los mejores clones
void cloneSelection(int n, struct genotype popToSel[POP+1], bool clonalSelType);

// Inserción de clones
void cloneInsertion(int n);

// Creación de nuevos elementos e inserción en los peores lugares de la poblacion
void newGeneration(int counter, bool replaceType);

void printPop(struct genotype tmp[POP]);
void cleanPops();
#endif
