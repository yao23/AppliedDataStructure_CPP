#include "counter.h"
template <class Type>
class general_counter : public counter<Type> // base on class counter
{
  public : general_counter(Type N=0) : counter(N){}
           void setcounter(Type N=0) { data = N; } // now can set value
                                                   // at any time
           void decrement(Type D=1) { data -= D; } // now can decrement too
};
