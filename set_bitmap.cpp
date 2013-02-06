#include "set_bitmap.h"
#include <iostream>

using namespace std;

int main()
{
  set_bitmap<char> A, B, C;
  set_bitmap<char> X, Y, Z, S, T, U;

  A.insert('x'); cout << A.setsize(); A.show(cout);
  A.insert('P'); cout << A.setsize(); A.show(cout);


  B.insert('Q'); cout << B.setsize(); B.show(cout);
  B.insert('R'); cout << B.setsize(); B.show(cout);
  B.insert('P'); cout << B.setsize(); B.show(cout);
  B.insert('V'); cout << B.setsize(); B.show(cout);
  B.insert('H'); cout << B.setsize(); B.show(cout);
 
  if (B.is_member('P')) cout << "OK"; else cout << "bad"; cout << endl;
  if (!B.is_member('M')) cout << "OK"; else cout << "bad"; cout << endl;
  if (!B.is_member('W')) cout << "OK"; else cout << "bad"; cout << endl;
  if (B.is_member('H')) cout << "OK"; else cout << "bad"; cout << endl;

  C = B;
  C.show(cout);
  cout << C.setsize(); C.show(cout);
  C = C;
  cout << C.setsize(); C.show(cout);

  if (C.remove('V')) C.show(cout); else cout << "bad remove\n";
  if (C.remove('D')) C.show(cout); else cout << "bad remove\n";
  if (C.remove('H')) C.show(cout); else cout << "bad remove\n";

  X.insert('g'); X.insert('f'); X.insert('e'); 
  X.insert('d'); X.insert('c'); X.insert('a');
 
  Y.insert('c'); Y.insert('f'); Y.insert('r'); Y.insert('t');

  Z.insert('a'); Z.insert('c'); Z.insert('d'); 

  S = X * Y; cout << S.setsize(); S.show(cout);
  T = Y + Z; cout << T.setsize(); T.show(cout);
  U = X - Y; cout << U.setsize(); U.show(cout);

  return 0;
}
