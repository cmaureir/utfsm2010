#include <stdio.h>
#include <stdio.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define VARS 10
#define POP 12


int i,j,tmp = 0,m=0;
int carNumber = 10;
int optNumber = 5;
int typeNumber = 6;
int numMaxCarOptSeq[5] = {1,2,1,2,1};
int sizeMaxCarOptSeq[5] = {2,3,3,5,5};
int mal=0;

int sol[10]  = {0, 1, 5, 2, 4, 3, 3, 4, 2, 5};
int test[10] = {0, 1, 5, 3, 2, 3, 5, 4, 2, 4};
//int tArray[typeNumber][7];
int tArray[6][7];
void init(){
	tArray[0][0] = 0;tArray[0][1] = 1;/*Opciones*/tArray[0][2] = 1;tArray[0][3] = 0;tArray[0][4] = 1;tArray[0][5] = 1;tArray[0][6] = 0;
	tArray[1][0] = 1;tArray[1][1] = 1;/*Opciones*/tArray[1][2] = 0;tArray[1][3] = 0;tArray[1][4] = 0;tArray[1][5] = 1;tArray[1][6] = 0;
	tArray[2][0] = 2;tArray[2][1] = 2;/*Opciones*/tArray[2][2] = 0;tArray[2][3] = 1;tArray[2][4] = 0;tArray[2][5] = 0;tArray[2][6] = 1;
	tArray[3][0] = 3;tArray[3][1] = 2;/*Opciones*/tArray[3][2] = 0;tArray[3][3] = 1;tArray[3][4] = 0;tArray[3][5] = 1;tArray[3][6] = 0;
	tArray[4][0] = 4;tArray[4][1] = 2;/*Opciones*/tArray[4][2] = 1;tArray[4][3] = 0;tArray[4][4] = 1;tArray[4][5] = 0;tArray[4][6] = 0;
	tArray[5][0] = 5;tArray[5][1] = 2;/*Opciones*/tArray[5][2] = 1;tArray[5][3] = 1;tArray[5][4] = 0;tArray[5][5] = 0;tArray[5][6] = 0;
}


void eval(int array[10]){
	// Restriccion Dura, alcanzar la demanda de autos por cada type
	// Restriccion Blanda, que en cada subsecuencia X hayan Y autos.

	for(i = 0; i < optNumber; i++){
		cout << "Opcion: " << i << endl;
		while(m<carNumber){
			if(m+sizeMaxCarOptSeq[i] <= carNumber){
				cout<<"Comparacion: ";
				for (j = m; j < sizeMaxCarOptSeq[i]+m; j++) {
					cout << array[j] << " ";
					tmp += tArray[array[j]][i+2];
				}
				cout << endl;
				cout << "Suma: "<<tmp<< " Max: "<<numMaxCarOptSeq[i]<<endl;
				if(tmp > numMaxCarOptSeq[i]){
					//penalizo con una unidad por cada excedente o falta.
					mal += tmp-numMaxCarOptSeq[i];
					cout << "FAIL: " << tmp-numMaxCarOptSeq[i] << endl;
					
					tmp = 0;
				}
				else{
					cout<< "suma ok"<<endl;
					tmp = 0;
				}
			}
			m++;
		}
		m = 0;
		//getchar();
	}
}


int main(){
	init();
	//cout << "sol" << endl;
	//eval(sol);
	cout << "test" << endl;
	eval(test);
	cout << "Penalizacion: "<<mal<<endl;
	return 0;
}
