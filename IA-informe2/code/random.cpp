#include <iostream>
#include <cstdlib>   // for srand and rand
#include <ctime>     // for time
using namespace std;

# define N 20

int main() {
    int card[N];    // array of cards;
    int n;           // number of cards to deal
    srand(time(0));  // initialize seed "randomly"
     
    for (int i=0; i<N; i++) {
        card[i] = i;  // fill the array in order
    }
    n = N;
//    while (N > n) {    
        //--- Shuffle elements by randomly exchanging each with one other.
        for (int i=0; i<(N-1); i++) {
            int r = i + (rand() % (N-i)); // Random remaining position.
            int temp = card[i]; card[i] = card[r]; card[r] = temp;
        }
        
        //--- Print first n cards as ints.
        for (int c=0; c<n; c++) {
            cout << card[c] << " ";  // Just print number
        }
        cout << endl;
//    }
   
   return 0;
}

