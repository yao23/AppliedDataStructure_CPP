// operator == is defined on actual objects in list
// assume items in list are numbered 0 upwards

template <class Entry> class linkedlist;	// forward declaration

template <class Entry> 
class listnode
{
  friend class linkedlist<Entry>;
  
  private: Entry data;
 	   listnode *node;
};

template <class Entry>
class linkedlist
{
  public: linkedlist();	// constructor - initialize root
	  ~linkedlist(); // destructor - reclaim memory
	  linkedlist(const linkedlist& rhs);	// replicator
	  linkedlist& operator = (const linkedlist&); // assignment
	  void clear(); // clear the list
	  int Getlength();
	  int Finditem(Entry X); // return position or -1
	  bool Finditem(int i, Entry& X); // get ith item. False if none
	  bool remove (int I); 	// remove Ith list element
	  bool insert (Entry X, int i);	// insert new item

  private: listnode<Entry> *root;
	   void copylist (listnode<Entry> *&newlist,	// for use by
	   		  listnode<Entry> *oldlist);	// replicator
	   int llength(listnode<Entry> *L);		// actual counter
	   int find_aux(int N, Entry X, listnode<Entry> *L);
	   bool find_aux2(int N, Entry& X, listnode<Entry> *L);	
	   bool insert_aux(Entry X, int i, listnode<Entry> *&L); // inserter
	   bool remove_aux(int i, listnode<Entry> *&L);	// actual deleter
	   void release_aux(listnode<Entry> *&L);	// actual space reclaim
};

template <class Entry>
&linkedlist<Entry>::linkedlist()
{
  root = NULL;
}

template <class Entry>
linkedlist<Entry>::~linkedlist()
{
  release_aux(root);
}

template <class Entry>
void linkedlist<Entry>::clear()
{
  release_aux(root);
  root = NULL;
}

template <class Entry>
void linkedlist<Entry>::release_aux(listnode<Entry> *&L)
{
  if (L!=NULL)
  {
    release_aux(L->next);
    delete L;
  }
}

template <class Entry>
int linkedlist<Entry>::Getlength()
{
  return llength(root);
}

template <class Entry>
int linkedlist<Entry>::llength(listnode<Entry> *L)
{
  if (L==NULL) return 0;
	  else return 1+llength(L->next);
}

template <class Entry>
void linkedlist<Entry>::copylist(listnode<Entry> *&newlist,
                      listnode<Entry> *oldlist)
{
  newlist = NULL;
  if (oldlist != NULL)
    { newlist = new listnode<Entry>;
      newlist->data = oldlist->data;
      copylist(newlist->next, oldlist->next);
    }
}

template <class Entry>
linkedlist<Entry>::linkedlist(const linkedlist &rhs)
{
  copylist(root, rhs.root);
}

template <class Entry>
linkedlist<Entry>& linkedlist<Entry>::operator = (const linkedlist& rhs)
{
  // overloaded assignment operator
  if (this != &rhs) // not assinging to self
        {
	  release_aux(root); // to stop memory leak
	  copylist(root, rhs.root);
	}
  return *this;
}

template <class Entry>
int linkedlist<Entry>::Finditem(Entry X)
{  // looking for an item by its contents
	return find_aux(0, x, root);
}

template <class Entry>
int linkedlist<Entry>::find_aux(int i, Entry X, listnode<Entry> *L)
{
	if (L==NULL)	return -1;	// list empty
	if (X==L->data) return i;	// found the item
	return find_aux(i+1, X, L->next); // look in the rest of the list
}

template <class Entry>
bool linkedlist<Entry>::Finditem(int i, Entry& X)
{ //looking for an item by its position
  if (i<0) return false;	// bad parameter
  return find_aux2(i, X, root);
}

template <class Entry>
bool linkedlist<Entry>::find_aux2(int i, Entry& X, listnode<Entry> *L)
{ // put into X the ith item in L
  if (L==NULL) return false;	// empty list
  if (i==0)	// return first item
  {
    X = L->data;
    return true;
  }
  return find_aux2(i-1, X, L->next);
}

template <class Entry>
bool linkedlist<Entry>::remove(int i)
{ // remove the ith item
  if (i<0) return false; // bad parameter
  return remove_aux(i, root); //does the removal
}

template <class Entry>
bool linkedlist<Entry>::remove_aux(int i, listnode<Entry> *&L)
{ // remove ith item from list L
  if (L==NULL) return false;	// list is empty
  if (i==0)	// remove front item
  {
    listnode<Entry> *temp = L;
    L = temp->next;
    delete temp;
    return true;
  }
  return remove_aux(i-1, L->next);
}

template <class Entry>
bool linkedlist<Entry>::insert(Entry X, int i)
{ // insert X at ith position
  return insert_aux(X, i, root);
}

template <class Entry>
bool linkedlist<Entry>::insert_aux(Entry X, int i, listnode<Entry> *&L)
{
  if (i<0) return false; // off the front
  if (i==0)
  {
    listnode<Entry> *temp = new listnode<Entry>;
    if (temp==NULL) return false; // out of space
      temp->data = X;
    temp->next = L;
    L = temp;
    return true;
  }
  if (L==NULL) return false; // off the end;
  return insert_aux(X, i-1, L->next);
}


 
  

