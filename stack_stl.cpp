#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
  stack<int> One;
  stack< int, vector<int> > Two;

  One.push(60); One.push(20); One.push(50); One.push(10);
  cout << "Number of elements in One is: " << One.size() << endl;

  cout << "Top item is: " << One.top() << endl;
  One.pop();
  cout << "Top item is: " << One.top() << endl;

  // pour items from One to Two
  while (!One.empty()) { Two.push(One.top()); One.pop(); }

  cout << "Number of elements in Two is: " << Two.size() << endl;

  cout << "Contents of Two: ";
  while (!Two.empty()) { cout << Two.top() << " "; Two.pop(); }
  cout << endl;

  return 0;
}
