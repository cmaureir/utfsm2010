#include<iostream>
#include<list>
using namespace std;

main(){
	list<int> L;
	L.push_back(0);
	L.push_front(0);
	L.insert(++L.begin(),2);

	L.push_back(5);
	L.push_back(6);

	list<int>::iterator i;

	for(i=L.begin(); i != L.end(); ++i) cout << *i << " ";
	cout << endl;
	return 0;
}
