#include <limits.h>
#include <stdlib.h>
#include <bitset>
#include <iostream>

using namespace std;

int main()
{
  bitset<50> A, B, C, D;

  // set 20 random bits in A
  for (int i=0; i < 20; i++) A.set(rand()%50);

  cout << "number of bytes: " << sizeof(A) << endl;
  cout << "number of bits: " << A.size() << endl;
  cout << "number of 1s: " << A.count() << endl;
  cout << "A         " << A << endl;

  // set 20 random bits in B
  for (int i=0; i < 20; i++) B.set(rand()%50);
  cout << "B         " << B << endl;

  C = A & B; cout << "C=A&B    " << C << endl;
  D = C << 5; cout << "D=C<<5   " << D << endl;
  D.flip(4); cout << "D.flip(4) " << D << endl;

  return 0;
}
  
