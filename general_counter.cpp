#include <iostream>
#include "counter.h"
#include "general_counter.h"

using namespace std;
/*
template <class Type>
class general_counter : public counter<Type> // base on class counter
{
  public : general_counter(Type N=0) : counter(N){}
           void setcounter(Type N=0) { data = N; } // now can set value
                                                   // at any time
           void decrement(Type D=1) { data -= D; } // now can decrement too
};
*/
int main()
{
  general_counter<int> difference;
  int N;

  do 
    {
      cout << "Enter a number  (0 to finish): ";
      cin >> N;

      if (N != 0) // not the terminator
        {
          if (N<0)
                difference.decrement(); // negative number read
          else difference.increment();  // positive number read
        }
     }  while (N != 0);

  cout << "Number of positive entered minus number of negative: "
       << difference.getvalue() << endl;

  return 0;
}

