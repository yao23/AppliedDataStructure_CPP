#include <list>
#include <iostream>	// for cout

template <class Entry>
class map_hash_unbounded
{
  public:
          map_hash_unbounded(int N=10);	// constructor - allocate memory
	  ~map_hash_unbounded();		// destructor - clean up memory
	  map_hash_unbounded(const map_hash_unbounded &rhs);	// replicator
	  map_hash_unbounded& operator = (const map_hash_unbounded&); // assignment
	  void showmap(ostream&) const;	// display contents
	  bool retrieve(Entry&);	// looks for key match, puts in
	  bool insert(Entry);	// overwrites if key there
	  bool remove(Entry);	// delete one with same key

  private:
   	   enum hashtag(empty, full);
	   typedef list<Entry> overflow;
	   void copytags(hashtag *&newtable, hashtag *oldtable, int N);	// used by rep.
	   void copyentries(Entry *&newtable, Entry *oldtable, int N); 	// used by rep.
	   void copyoverflows(overflow *&newtable, overflow *oldtable, int N); 	// used by rep.
	   int size;	// number of slots in table
	   hashtag *tag;	// for tags
	   Entry *entries;	// for the table entries
	   overflow *overflows;	// for the overflow lists
};


template <class Entry>
map_hash_unbounded<Entry>::map_hash_unbounded(int N=10)
{ // constructor: remember size of table, allocate space for array of tags
  // and array of entries and array of overflow lists. Initialize the array of tags
  size = N;
  tags = new hashtag[N];
  entries = new Entry[N];
  overflows = new overflow[N];
  for (int i = 0; i < N; i++) tags[i] = empty;
}

template <class Entry>
map_hash_bounded<Entry>::~map_hash_bounded()
{ // destructor: reclaim space allocated for the three arrays
  delete[] tags;
  delete[] entries;
  delete[] overflows;
}

template <class Entry>
void map_hash_unbounded<Entry>::copytags(hashtag *&newtable,
				       hashtag *&oldtable, int size)
{ // make a copy of the array of tags
  newtable = new hashtag[size];
  for (int i = 0; i < size; i++) newtable[i] = oldtable[i];
}

template <class Entry>
void map_hash_unbounded<Entry>::copyentries(Entry *&newtable, Entry *&oldtable, int size)
{ // make a copy of the array of entries
  newtable = new Entry[size];
  for (int i = 0; i < size; i++) newtable[i] = oldtable[i];
}

template <class Entry>
void map_hash_unbounded<Entry>::copyoverflows(overflow *&newtable, overflow *&oldtable, int size)
{ // make a copy of the array of overflow lists
  newtable = new overflow[size];
  for (int i = 0; i < size; i++) newtable[i] = oldtable[i];
}

template <class Entry>
map_hash_unbounded<Entry>::map_hash_unbounded(const map_hash_unbounded &rhs)
{ // copy constructor
  size = rhs.size;
  copytags(tags, rhs.tags, size);
  copyentries(entries, rhs.entries, size);
  copyoverflows(overflows, rhs.overflows, size);
}

template <class Entry>
map_hash_unbounded<Entry>& map_hash_unbounded<Entry>::operator = (const map_hash_unbounded &rhs)
{ // overloaded assignment operator
  if (this != &rhs)	// not trying to assign to self
  {
    size = rhs.size;
    copytags(tags, rhs.tags, size);
    copyentries(entries, rhs.entries, size);
    return *this;
  }
}

template <class Entry>
void map_hash_unbounded<Entry>::showmap(ostream &s) const
{ // to display the table on stream s
  for (int i = 0; i < size; i++) {
    s << i << " ";
    if ( tags[i] == full) {
      s << entries[i]; // here is the entry
      if( !overflows[i].empty() ) { // print the overflow list
        overflow::iterator t = overflow[i].begin();
        while( t != overflows[i].end()) {
          s << " " << *t;
          t++;
        }
      }
    } 
    s << endl;
  }
}

template <class Entry>
bool map_hash_bounded<Entry>::retrieve(Entry& target)
{
  int row = target.H(size);	// the row of interest
  if( tags[row] == empty ) return false; // nothing there
  if( entries[row] == target ) { // found in the table
    target = entries[row];	// overwrite parameter with table entry
    return true;
  }
  if( overflows[row].empty() ) return false;	// no overflows to search
  // look in overflow list
  overflow::iterator i = overflows[row].begin();
  while( i != overflows[row].end() && !(target == *i) ) i++;
  if( i == overflows[row].end() ) return false;	// not match in overflow list
    return true;
}

template <class Entry>
bool map_hash_unbounded<Entry>::insert(Entry E)
{
  int row = E.H(size);	// the row of interest
  if( tags[row] == empty ) { // entry is currently empty
    entries[row] = E;
    tags[row] = full;
    return true;
  }
  if( entries[row] == E) { // entry found with same key
    entries[row] = E; // overwrite with the new object
    return true;
  }
  // see if in overflow list
  overflow::iterator i = overflows[row].begin();
  while( i != overflows[row].end() && !(E == *i)) i++;
  if( i != overflows[row].end())
    *i = E; // found so overwrite with new object
  else overflows[row].push_front(E); // not found, push at front of list
  return true;   
}

template <class Entry>
bool map_hash_unbounded<Entry>::remove(Entry target)
{
  int row = target.H(size); // the row of interest
  if( tags[row] == empty ) return false; // is empty so not in table
  if( entries[row] == target ) { // is it the table entry
    if( overflows[row].empty() ) // yes. any overflows?
      tags[row] = empty;	// no so this row is now empty
    else { // yes so move first overflow to table
      overflow::iterator i = overflows[row].begin();
      entries[row] = *i; 
      overflows[row].pop_front();
    }
    return true;
  }
  else { // see if object to be removed is in overflow list
    overflow::iterator i = overflows[row].begin();
    while( i != overflows[row].end() && !(E == *i)) i++;
    if( i != overflows[row].end())
      return false; // no so remove fails
    overflows[row].erase(i); // yes get rid of it
    return true;
  }
}


           

    
  
  
  
  
  
