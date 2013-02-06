template <class Entry>
class queue
{
  public: queue();	// constructor
	  ~queue();	// destructor
	  bool enqueue(Entry);	// add item to queue
	  bool dequeue(Entry&);	// remove from queue into item
	  bool isempty();	// check if queue is empty
	  bool isfull();	// appropriate if queue is bounded
	  bool getfront(Entry&); // get front without removing it

  private: // implementation specific
          queue_node *first, *last;
};

template <class Entry>
bool queue<Entry>::enqueue(Entry item)
{
  if (isfull())
    return false;	// queue is full
  else {
    back = (back + 1) % queuesize; // may wrap around
    data_values[back] = item;	// store item
    count++;
    return true;
  }
}

template <class Entry>
bool queue<Entry>::dequeue(Entry& item)
{
  if (isempty())
    return false;	// queue is empty
  else {
    item = data_values[front];	// get item from queue
    front = (front + 1) % queuesize; // may wrap around
    count--;
    return true;
  }
}

template <class Entry>
bool queue<Entry>::enqueue(Entry item)
{ // add item to queue

  queue_node *temp = new queue_node;
  if (temp==NULL) return false;	// no space available 
  temp->data = item;
  temp->next = NULL;
  if (count==0)		// is this the first item?
     first = temp;	// yes
  else 
     last->next = temp;	// no, so append it
  last = temp;		// either way it is now the last
  count++;		// and the queue is one item longer
  return true;
}
