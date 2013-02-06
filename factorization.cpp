#include <set>
#include <algorithm>	// for intersection
#include <iostream>

using namespace std;

multiset<int> factorize(int N)
{
  // return a multiset containing the prime factors of N
  multiset<int> factors;
  int f=2; // current factor
  while (N >= f)
  {
    while (N%f==0) { factors.insert(f); N/=f; } // all instances of f
    f++;
  }
  return factors;
}

int main()
{
  multiset<int> FA, FB, FHCF;	// for factors
  int A, B, HCF = 1;

  cout << "Numbers please : "; cin >> A >> B;

  FA = factorize(A);
  FB = factorize(B);

  // FHCF = intersection FA, FB using STL method

  set_intersection(FA.begin(), FA.end(), 
                   FB.begin(), FB.end(),
                   inserter(FHCF, FHCF.begin())
                  );

  // multiply HCF by each member of FHCF using iterator a
  
  for (multiset<int>::iterator a = FHCF.begin();
       a != FHCF.end();
       a++
      ) HCF *= *a;

  cout << "hcf of " << A << " and " << B << " is " << HCF << endl;

  return 0;
}
