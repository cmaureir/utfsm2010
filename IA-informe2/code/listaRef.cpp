#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int> l1(6), a1(6), a2(6);
int i,j,n,m;
int l1_[6]={1,2,3,4,5,6};
int a1_[6]={6,1,4,3,2,5};
int a2_[6]={2,5,6,3,4,1};
int b[6];

void codification(int a[6]){
	// Asignacion	
	for(i = 0; i < l1.size(); i++)
		l1[i] = l1_[i];
	
	for(i = 0; i < l1.size(); i++)
		a1[i] = a[i];

	// loop
	n = 0;	m = 0;
	for(i=0;i<a1.size();i++){
		for(j=0;j<l1.size();j++){
			if( a1[i] == l1[j] ){
				cout << "borro: " << n << endl;
				l1.erase(l1.begin()+n);
				b[m] = n+1;
				n = 0;
			}
			n = n + 1;
		}
		n = 0;
		m = m + 1;
	}
}

void decodification(){

}

int main(int argc, const char *argv[])
{

	codification(a1_);
	decodification();
	// print
	for(i = 0; i < 6;i++)
		cout << b[i] << " ";
	cout << endl;
	return 0;
}
