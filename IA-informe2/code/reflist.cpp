#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int i,j,k,n,m;
int l[6]={1,2,3,4,5,6};
int a1[6]={2,5,6,3,4,1};
//int a2[6]={2,5,6,3,4,1};
int a2[6]={2,4,4,2,2,1};
int b1[6],b[6], l1[6];

void codification(int a[6]){
	for (i = 0; i < 6; i++) {
		l1[i] = l[i];
	}
	n = 0;
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			if(a[i] == l1[j]){
				b[i] = n+1;
				l1[j] = -1;
				
			}
			if(l1[j] != -1){
				n++;
			}
		}
	n=0;
	}
}

void decodification(int a[6]){
	for (i = 0; i < 6; i++) {
		l1[i] = l[i];
	}
	n = 0;
	bool ok = 1;
	for(i=0;i<6;i++){
		for(j=0;j<6 && ok;j++){
			if(a[i] == n+1  && l1[j] != -1){
				b[i] = l1[j];
				l1[j] = -1;
				ok = 0;
				
			}
			if(l1[j] != -1){
				n++;
			}
		}
	ok = 1;
	n=0;
	}
}

int main(int argc, const char *argv[])
{

	codification(a1);
	// print
	for(i = 0; i < 6;i++)
		cout << b[i] << " ";
	cout << endl;
	//

	decodification(a2);
	//
	for(i = 0; i < 6;i++)
		cout << b[i] << " ";
	cout << endl;
	//
	
	return 0;
}
