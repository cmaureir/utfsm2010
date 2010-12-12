#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
using std::ifstream;
using namespace std;


float A[1600][1600],B[1600][1600];

void Mul(int hA, int wA, int wB,float* C){

    int i,k,j,m=0;

	for (i = 0; i < hA; i++) {
		for (k = 0; k< wA; k++) {
			double s = 0;
			for (j = 0; j < wB; j++) {
				s += A[i][j] * B[j][k];
			}
			C[m] = s;
			m++;
		}
	}
}

void readFile(){

    int i=0,j=0,tmp=0;
	ifstream f;
	int num;
	bool t = true;
	f.open("1");
	f >> num;
	tmp += 1;

	while(!f.eof())
     {
		if(j == 1600){
			j=0;
			i++;
			//cout << endl;
			//getchar();
		}
		if(i == 1600){
			t = false;
			i = 0;
			j = 0;
		}
		if(t){
			A[i][j] = num;
		}
		else{
			B[i][j] = num;
		}
		f >> num;
		j++;
     }
	f.close();
}

int main(int argc, const char *argv[])
{
    int i=0;
    float *C;
    C = (float*)malloc(sizeof(float) * 1600 * 1600);
	

	readFile();
    Mul(1600,1600,1600,C);


    for(i=0;i<1600;i++){
    	//for(j=0;j<1600;j++){
		//	cout << A[i][j] << " ";
			cout << A[0][i] << " ";
		//}
		//cout << endl;
	}
		cout << endl;

	cout << "====================" << endl;

    for(i=0;i<1600;i++){
            cout << C[i] << " ";
    }
	cout << endl;
	return 0;
}
