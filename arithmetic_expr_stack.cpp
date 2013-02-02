// fragile evaluator of well-formed infix expressions
// assume tokens are separated by white space
#include <iostream> 	
#include <stdlib.h>	// for the atoi function
#include "stack.h"
#include <string.h>

using namespace std;

stack<char> operatorstack;
stack<int> operandstack;

enum symtype {oprand, openparen, closeparen, oprator};	// the 4 token types

symtype classify(char sym[])
{
  // determine which type of symbol we have
  if (strcmp(sym, "(")==0) return openparen;
  if (strcmp(sym, ")")==0) return closeparen;
  if ( strcmp(sym, "+")==0 || strcmp(sym, "-")==0 ||
       strcmp(sym, "*")==0 || strcmp(sym, "/")==0) return oprator;
  return oprand;
}

void apply (char op)
{
  // apply the operator to the top two stack items and replace them
  // by the result of the operation
  int one, two;
  operandstack.pop(two);
  operandstack.pop(one);
       if (op=='+') operandstack.push(one+two);
  else if (op=='-') operandstack.push(one-two);
  else if (op=='*') operandstack.push(one*two);
  else if (op=='/') operandstack.push(one/two);
}

int priority (char op)
{
  // determine the priority of the operator
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

int main()
{
  int result;						// for result of expression
  char OP;						// temporary for operator symbol
  char symbol[100];					// to store expression symbols  

  while (cin >> symbol)
    {
      int symboltype = classify(symbol);
      switch (symboltype)
        {
          case oprand: operandstack.push(atoi(symbol));	// oprand is pushed
	  	       break;				// on operand stack

	  case openparen: operatorstack.push('(');	// open paren is pushed 
		          break; 			// on operator stack

	  case closeparen: while(true)			// pop and apply operators
			   { operatorstack.pop(OP);	// until open paren is 
			     if (OP=='(') break; 	// found. Pop it
				     else apply(OP);
			   }
			   break;

	  case oprator: while(true)
			  {						// pop and apply
			    if (operatorstack.isempty()) break;		// operators
			    operatorstack.gettop(OP); 			// until stack is 
			    if (priority(OP) < priority(symbol[0]))	// empty or top 
				break;					// has lower
			    operatorstack.pop(OP);			// priority than 
			    apply(OP); 					// operator just 
			  }						// read
			operatorstack.push(symbol[0]);
	  }
	}

  while (operatorstack.pop(OP)) apply(OP); 		// pop and apply any operators
  operandstack.pop(result);				// top operand is result
  cout << result << endl;

  return 0;
}
		
