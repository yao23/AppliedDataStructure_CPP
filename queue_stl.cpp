#include <queue>
#include <stack>
#include <list>
#include <iostream>

using namespace std;

int main()
{
  stack<char> Three;
  queue<char, list<char> > Four;
  char a, b, c;
  bool palindrome;
  
  Four.push('x'); Four.push('a'); Four.push('b'); 
  Four.push('c'); Four.push('b'); Four.push('a');

  // see what's in the queue
  for (int i = 0; i < Four.size(); i++)
  {
    c = Four.front(); cout << c;
    Four.pop();
    Four.push(c);
  }
  cout << endl;

  // the two end items
  cout << Four.front() << Four.back() << endl;

  // pop one item and check size
  Four.pop();
  cout << "Number of elements in queue is now: " << Four.size() << endl;

  // palindrome testing of the queue (non-destructive)
  for (int i = 0; i < Four.size(); i++)
  {
    c = Four.front();
    Four.pop();
    Three.push(c); 	// char to stack
    Four.push(c);	// and back in queue
  }

  palindrome = true;
  while (!Three.empty() & palindrome)
  {
    a = Three.top(); Three.pop();
    b = Four.front(); Four.pop(); Four.push(b);
    if ( a != b) palindrome = false;
  }

  if ( palindrome ) cout << "palindrome\n";
  else cout << "not palindrome\n";

  return 0;
}
   
