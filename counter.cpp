#include <iostream>
#include "counter.h"

using namespace std;

int main() {
  int N;
  counter<int> counterofodds; // for odd numbers
  counter<short> countermultiples; // for multiples of 3

  do
    {
     cout << "Enter number (-1 to finish):";
     cin >> N;
     
     if (N != -1) // not the terminator 
       {
        if (N%2 == 1) counterofodds.increment(); // odd number
        if (N%3 == 0) countermultiples.increment(); // multiple of 3
       }
   } while (N != -1);
 
   cout << "Number of odd numbers:" << counterofodds.getvalue() << endl
        << "Number of multiples of 3:" << countermultiples.getvalue() << endl;

  return 0;
}

