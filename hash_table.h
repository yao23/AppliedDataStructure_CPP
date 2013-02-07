template <class Entry>
class map_hash_bounded
{
  public:
          map_hash_bounded(int N=10);	// constructor - allocate memory
	  ~map_hash_bounded();		// destructor - clean up memory
	  map_hash_bounded(const map_hash_bounded &rhs);	// replicator
	  map_hash_bounded& operator = (const map_hash_bounded&); // assignment
	  void showmap(ostream&) const;	// display contents
	  bool retrieve(Entry&);	// looks for key match, puts in
	  bool insert(Entry);	// overwrites if key there
	  bool remove(Entry);	// delete one with same key

  private:
   	   enum hashtag(empty, full, deleted);
	   void copytags(hashtag *&newtable, hashtag *oldtable, int N);	// used by rep.
	   void copyentries(Entry *&newtable, Entry *oldtable, int N); 	// used by rep.
	   int size;	// number of slots in table
	   hashtag *tag;	// for tags
	   Entry *entries;	// for the table entries
	   int find(Entry);	// find entry with same key
	   int findfree(Entry);	// find appropriate space for new key
};


template <class Entry>
map_hash_bounded<Entry>::map_hash_bounded(int N=10)
{ // constructor: remember size of table, allocate space for array of tags
  // and array of entries. Initialize the array of tags
  size = N;
  tags = new hashtag[N];
  entries = new Entry[N];
  for (int i = 0; i < N; i++) tags[i] = empty;
}

template <class Entry>
map_hash_bounded<Entry>::~map_hash_bounded()
{ // destructor: reclaim space for array of tags and array of entries
  delete[] tags;
  delete[] entries;
}

template <class Entry>
void map_hash_bounded<Entry>::copytags(hashtag *&newtable,
				       hashtag *&oldtable, int size)
{ // make a copy of the array of tags
  newtable = new hashtag[size];
  for (int i = 0; i < size; i++) newtable[i] = oldtable[i];
}

template <class Entry>
void map_hash_bounded<Entry>::copyentries(Entry *&newtable, Entry *&oldtable, int size)
{ // make a copy of the array of entries
  newtable = new Entry[size];
  for (int i = 0; i < size; i++) newtable[i] = oldtable[i];
}

template <class Entry>
map_hash_bounded<Entry>::map_hash_bounded(const map_hash_bounded &rhs)
{ // copy constructor
  size = rhs.size;
  copytags(tags, rhs.tags, size);
  copyentries(entries, rhs.entries, size);
}

template <class Entry>
map_hash_bounded<Entry>& map_hash_bounded<Entry>::operator = (const map_hash_bounded &rhs)
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
void map_hash_bounded<Entry>::showmap(ostream &s) const
{ // to display the table in a simple way
  // requiers << to be defined for objects being stored
  for (int i = 0; i < size; i++)
  {
    s << i << " ";
    if ( tags[i] == full) s << entries[i];
    s << endl;
  }
}

template <class Entry>
int map_hash_bounded<Entry>::find(Entry target)
{ // reutrn index in the table of undeleted target.
  // return -1 if not present or present but deleted
  int home = target.H(size);	// hash function gives home address
  int pos = home;	// starting point for search

  while( tags[pos] != empty && !(entries[pos] == target)) {
    pos = (pos + 1) % size;	// next location - circular
    if (pos == home) return -1;	// back at starting point - not found
  }
  
  if( tags[pos] == full ) return pos;	// stopped on target
  return -1;	// found target but it was deleted
}

template <class Entry>
bool map_hash_bounded<Entry>::retrieve(Entry& target)
{
  int row = find(target);	// look for key match
  if( row == -1) return false;	// not found
  target = entries[row];	// found: overwrite parameter
  return true;
}

template <class Entry>
bool map_hash_bounded<Entry>::insert(Entry E)
{
  int row = find(E);	// look for key match
  if( row >= 0) { // already in - overwrite attributes
    entries[row] = E;
    return true;
  } else { row = findfree(E); // not in, look for free space
        if( row >= 0) { // free space found
          entries[row] = E;
          tags[row] = full;
          return true;
        } else return false; // table full
  }
}

template <class Entry>
bool map_hash_bounded<Entry>::remove(Entry target)
{
  int row = find(target); // look for key match
  if(row == 1) return false; // not in the table 
  tags[row] = deleted; // found. mark deleted
  return true;
}

template <class Entry>
int map_hash_bounded<Entry>::findfree(Entry target)
{ // return index of free space or -1 if none
  int home = target.H(size); // H give home address
  int pos = home; // start search there
  while( tags[pos] == full) {
    pos = (pos + 1) % size; // treat table as circular
    if( pos == home) return -1; // back at beginning - no free space
  }
  return pos;
} 


           

    
  
  
  
  
  
