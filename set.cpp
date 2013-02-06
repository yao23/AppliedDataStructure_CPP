#include <stdlib.h>	// for rand - see extract function

template <class Entry> class set_llist;	// forward declaration

template <class Entry> 
class set_llist_element	// class definition for linked list element
{
  friend class set_llist<Entry>;
  
  public: set_llist_element() { next = NULL; }

  private: Entry data;
	  set_llist_element<Entry> *next;
};

template <class Entry>
class set_llist
{
  // set as ordered linked list
  // assume that operator < is definded on set element

  public: set_llist();                // constructor - empty set
          ~set_llist();               // destructor - reclaim space
          set_llist(const set_llist& x);    // copy constructor
          set_llist& operator = (const set_llist&); // assignment operator
          bool is_member(Entry E);      // check for membership
          bool insert(Entry E);         // add new member
          bool remove(Entry E);         // remove member
          bool empty();         // is set empty?
          int size();           // current set size
          void show(ostream&, char[]="");       // contents to output stream
          bool extract(Entry& E);       // take out arbitrary member
 
   private: int count;
            // for copy constructor 
	    void copylist(set_llist_element<Entry> *&, 
		 set_llist_element<Entry>*);
	    void cleanup(set_llist_element<Entry> *&L);	// actual space reclaim
	    set_llist_element<Entry> *root;	// pointer to members in asc. order
};

template <class Entry>	// constructor
set_llist<Entry>::set_llist()
{
  count = 0;
  root = NULL;
}

template <class Entry>
void set_llist<Entry>::cleanup(set_llist_element<Entry> *&L)
{  if (L != NULL)
  {
    cleanup(L->next);
    delete L;
  }
}

template <class Entry>	// destructor
set_llist<Entry>::~set_llist()
{
  cleanup(root);
}

template <class Entry>
void set_llist<Entry>::copylist (set_llist_element<Entry> *&newlist,
				 set_llist_element<Entry> *&oldlist)

  //
  newlist = NULL;y
  // the first element
  if (oldlist != NULL)
  {
    newlist = new set_llist_element<Entry>;
    newlist->data = oldlist->data;
    newlist->next = NULL;
    oldlist = oldlist->next;
  }
  // remaining items
  set_llist_element<Entry> *endlist = newlist;
  while (oldlist != NULL)
  {
    endlist->next = new set_llist_element<Entry>;
    endlist->next->data = oldlist->data;
    endlist->next->next = NULL;
    endlist = endlist->next;
    oldlist = oldlist->next;
  }
}

template <class Entry>
set_llist<Entry>& set_llist<Entry>::operator = (const set_llist<Entry>& x)
{
  if (this != &x) // not assigning to self
  {
    count = x.count;
    cleanup(root);	// avoid memory leak
    copylist(root, x.root);
  }
  return *this;
}

template <class Entry>
set_llist<Entry>::set_llist<Entry>(const set_llist<Entry> &x)
{
  // copy constructor
  count = x.count;
  copylist(root, x.root);
}

template <class Entry>
bool set_llist<Entry>::is_member(Entry E)
{
  // returns true if E is in the list, false otherwise
  set_llist_element<Entry> *L=root;
  while(L != NULL)
  {
    if ( !(L->data < E) && !(E < L->data) ) return true;
    L = L->next;
  }
  return false;
}

template <class Entry>
bool set_llist<Entry>::insert(Entry E)
{
  // attempt to insert E in the correct place in the ordered list

  if (is_member(E)) return true; // alread in, no duplication is permitted

  set_llist_element<Entry> *t = new set_llist_element<Entry>;
  if (t == NULL) return false;	// out of space for new items

  t->data = E;
  if (root == NULL || E < root->data)	// new first element
  {
    t->next = root;
    root = t;
    count++;	// number of items in set
    return true;
  }
  // find insert place
  set_llist_element<Entry> *L = root;
  while (L->next != NULL && (L->next)->data < E) L=L->next;

  // update the list
  t->next = L->next;
  L->next = t;
  count++;	// number of items in set
  return true;
}

template <class Entry>
bool set_llist<Entry>::remove(Entry E)
{
  // attempt to remove E from the ordered list

  set_llist_element<Entry> *L = root;
  if (L == NULL) return false;	// list is empty
  if ( !(L->data < E) && !(E < L->data) ) // first item is the one to remove
  {
    root = L->next;
    delete L;
    count--;	// number of items in set
    return true;
  }
  // search for item with L pointer to item before it in the lsit
  while ( (L->next != NULL) && (L->next->data < E) ) L=L->next;

  if (L->next == NULL) return false;	// E is not in the list
  if ( !(E < L->next->data) )	// found it
  {
    set_llist_element<Entry> *temp = L->next;
    L->next = temp->next;
    delete temp;	// reclaim space
    count--;	// number of items in set
    return true;
  }
  return false;	// E not found
}

template <class Entry> bool set_llist<Entry>::empty() { return count==0; }

template <class Entry> int set_llist<Entry>::size() { return count; }

template <class Entry> 
void set_llist<Entry>::show(ostream &s, char message[])
{  // output set members with message and count

   set_llist_element<Entry> *L=root;
   s << message << count << " elements: ";
  
   while(L!=NULL)
   {
     s << L->data << " ";
     L = L->next;
   }
   s << endl;
}

template <class Entry>
bool set_llist<Entry>::extract(Entry& R)
{
  // remove a random element from the set and put in R

  if (count == 0) return false;	// set is empty

  int location = rand()%count;	// get random index 0..count-1
  set_llist_element<Entry> *L=root;

  if (location==0) // we are removing the first item
  {
    R = L->data;
    root = L->next;
    delete L;
    count--;	// number of items in set
    return true;
  }
  // move down list to deletion point
  while (location > 1) { location--; L=L->next; }
  // extract
  set_llist_element<Entry> *temp = L->next;
  R = temp->data;
  L->next = temp->next;
  delete temp;	// reclaim space
  count--;
  return true;
}

template <class Entry>
set_llist<Entry> operator + (set_llist<Entry> A, set_llist<Entry> B)
{
  // union: implementation independent, uses extract and insert
  set_llist<Entry> result; Entry temp;
  while (A.extract(temp)) result.insert(temp);
  while (B.extract(temp)) result.insert(temp);
  return result;
}

template <class Entry>
set_llist<Entry> operator - (set_llist<Entry> A, set_llist<Entry> B)
{
  // difference A minus B: implementation independent, uses extract, 
  // is_member and insert
  
  set_llist<Entry> result; Entry temp;
  while (A.extract(temp))
       if (!B.is_member(temp)) result.insert(temp);
  return result;
}

template <class Entry>
set_llist<Entry> operator * (set_llist<Entry> A, set_llist<Entry> B)
{
  // intersection: implementation independnet, uses extract, 
  // is_member and insert

  set_llist<Entry> result; Entry temp;
  while (A.extract(temp))
       if (B.is_member(temp)) result.insert(temp);
  return result;
}
