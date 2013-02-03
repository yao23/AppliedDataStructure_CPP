#include "general_list.h"
#include  <iostream>

using namespace std;

int main()
{
  glinkedlist<char> final, temp1, temp2, temp3, temp4, temp5;
  glistnode<char> *temp;
  int i;

  final.insert('p', 1);
  final.insert('b', 2);
  final.insert('v', 3);

  temp1.insert('q', 1); temp1.insert('r', 2);
  final.insert(temp1, 2);

  temp2.insert('a', 1); temp2.insert('t', 2); temp2.insert('g', 3);
  temp3.insert('m', 1); temp3.insert('n', 2);
  temp2.insert(temp3, 3);
  final.insert(temp2, 4);

  temp4.insert('x', 1);
  temp5.insert(temp4, 1);
  final.insert(temp5, 6);

  final.showlist();
  cout << endl;
}
