#include <list>
#include <iostream>

using namespace std;

void showlist(list<int> L)
{
  cout << "[";
  for (list<int>::iterator i = L.begin(); i != L.end(); i++)
    cout << *i << " ";
  cout << "]"
       << endl;
}

int main()
{
  list<int> A, B, C;

  A.push_front(2); A.push_back(7); A.push_front(5);
  A.push_back(8); A.push_front(3);
  showlist(A); 				// should be 3 5 2 7 8

  // find 7 and replace by 5
  list<int>::iterator l = A.begin();
  while (*l != 7) l++;
  *l = 5;

  // make a copy of the list
  B = A;
  showlist(B); 				// should be 3 5 2 5 8

  // get rid of the 5s
  B.remove(5);
  showlist(B);				// should be 3 2 8

  // find the 2 and remove it
  l = B.begin();
  while (*l != 2) l++;
  B.erase(l);
  showlist(B);				// should be 3 8

  // add new numbers to the front
  B.push_front(12); B.push_front(9); B.push_front(20);

  // remove last element
  B.pop_back();
  showlist(B); 				// should be 20 9 12 3

  // sort, then output the list
  B.sort();
  showlist(B); 				// should be 3 9 12 20

  // create C then sort
  C.push_front(4); C.push_front(11); C.push_front(5); C.push_front(7);
  C.sort();

  B.merge(C);
  showlist(B);				// should be 3 4 5 7 9 11 12 20

  return 0;
}

