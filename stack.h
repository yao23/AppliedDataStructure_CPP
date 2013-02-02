template <class Entry>
class stack
{
  public: stack();   		// constructor
 	  bool push(Entry); 	// push item onto stack
	  bool pop(Entry&); 	// pop from stack into item
	  bool isempty();	// check if stack is empty
	  bool gettop(Entry&); 	// get top without popping it

  private: int count; 		// count of items in stack
	   Entry data[100]; 	// to hold the items. Top is data[count-1]
};

template <class Entry>
stack<Entry>::stack():count(0) {}

template <class Entry>
bool stack<Entry>::push(Entry item)
  {
    if (count==100)
         return false;		// stack full
    else
       {
	 data[count] = item; 	// inset item
	 count++;
	 return true;
       }
  }

template <class Entry>
bool stack<Entry>::pop(Entry& item)
  {
    if (isempty())
	return false;		// stack empty
    else
	{
	  count--;
	  item = data[count];	// get item
	  return true;
	}
  }

template <class Entry>
bool stack<Entry>::isempty() {return count==0;}

template <class Entry>
bool stack<Entry>::gettop(Entry& item)
{
  if (isempty())
	return false;
  else
	{
	  item = data[count-1];
	  return true;
	}
}
