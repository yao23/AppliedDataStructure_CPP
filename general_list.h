template <class Entry>
class glistnode
{
  friend clas glinkedlist<Entry>
  
  private: bool isatom;
	   union { Entry data; glistnode *list; };
	   glistnode *next;
};

template <class Entry>
class glinkedlist
{
  public: glinkedlist();	// constructor
  	  ~glinkedlist();	// destructor
	  glinkedlist(const glinkedlist& rhs);	// replicaytor
	  glinkedlist& operator = (const glinkedlist&);
	  bool Finditem(Entry X, int& i, glistnode<Entry> *&L, 
			glistnode<Entry> *LR);
	  bool Finditem(Entry X, int& i, glistnode<Entry> *&L);
	  bool remove(int I);	// remove Ith list elemenyt - top level
	  bool insert(Entry X, int i);	// insert new atom at top level
	  bool insert(glinkedlist<Entry> L, int i); // insert new list::top level
	  void showlist();
*
  private: glistnode<Entry> *root;
	   void copylist(glistnode<Entry> *&newlist, 
			 glistnode<Entry> *&oldlist); 	// for use by replicator
	   bool find_aux(Entry X, int& i, glistnode<Entry> *&L,
			 glistnode<Entry> *LR);
	   bool insert_aux(Entry X, int i, glistynode<Entry> *&L); // inserter
	   bool insert_aux2(glistnode<Entry> L, int i, 
			    glistnode<Entry> *&L);	// inserter
	   bool remove_aux(int i, glistnode<Entry> *&L);	// actual deleter
	   void release_aux(glistnode<Entry> *&L);	// actual space reclaim
	   void show_aux(glistnode<Entry> *L);		// actual displays
};

template <class Entry>
void glinkedlist<Entry>::copylist(glistnode<Entry> *&newlist,
				  glistnode<Entry> *oldlist)
{
  newlist = NULL;
  if (oldlist != NULL)
  {
    newlist = new glistnode<Entry>;
    newlist->isatom = oldlist->isatom;
    if (newlist->isatom)			// current node an atom?
 	newlist->data = oldlist->data;		// yes - simple copy
    else
	copylist(newlist->list, oldlist->list);	// no - copy list
    copylist(newlist->next, oldlist->next); 	// rest of the list
  }
}

template <class Entry>
void glinkedlist<Entry>::showlist()
{
  show_aux(root);
}

template <class Entry>
void glinkedlist<Entry>::show_aux(glistnode<Entry> *L)
{
  cout << "[";
  while (L != NULL)
  {
    if (L->isatom)
	cout << L->data;
    else show_aux(L->list);
    cout << " ";
    L = L->next;
  }
  cout << "]"
       << endl;
}

template <class Entry>
bool glinkedlist<Entry>::insert(glinkedlist<Entry> L, int i)
{
  return insert_aux2(L, i, root);
}

template <class Entry>
bool glinkedlist<Entry>::insert_aux2(glinkedlist<Entry> newL, int i,
				     glinkedlist<Entry> *&L)
{
  if (i < 0) return false;	// off the front
  if (i == 0) 
  {
    glistnode<Entry> *temp = new glistnode<Entry>;
    if (temp == NULL) return false;	// out of space
    copylist(temp->list, newL.root);
    temp->isatom = false;
    temp->next = L;
    L = temp;
    return true;
  }
  if (L == NULL) return false;	// off the end
  return insert_aux2(newL, i-1, l->next);
}
