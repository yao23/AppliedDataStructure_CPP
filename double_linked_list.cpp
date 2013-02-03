template <class Type>
class dlistnode
{
  friend class dlinkedlist<Type>;

  private: Type data;
 	   dlistnode *next;
	   dlistnode *previous;
}

template <class Type>
bool dlinkedlist<Type>::insert(Type X, int i)
{
  if (i<0) return false;	// bad parameter

  dlistnode<Type> *location, *temp = new dlistnode<Type>;

  if (temp==NULL) return false;	// out of space

  temp->data = X;		// values in
  temp->previous = NULL; 	// the new
  temp->next = NULL;		// node

  if (i==0)	// new first element in the list?
  {			
    temp->next = root;		// LINK A
    if (root != NULL) root->previous = temp;	// LINK B
    root = temp;		// LINK C
    return true;
  }

  // more general insertion

  location = root;
  while (i>1 && location != NULL) {
    i--; location = location->next; }
  if (location == NULL) return false;	// list not long enough

  temp->previous = location;	// LINK D
  temp->next = location->next;	// LINK E
  if (temp->next != NULL) { temp->next->previous = temp; }	// LINK F
  location->next = temp;	// LINK G
  return true;
} 
