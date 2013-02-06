#include <limits.h>	// for CHAR_BIT : number of bits in a char

template <class Entry>
class set_bitmap
{
  // requires that Entry can be cast to int

  friend set_bitmap<Entry> operator +<> (set_bitmap<Entry>, set_bitmap<Entry>);
  friend set_bitmap<Entry> operator *<> (set_bitmap<Entry>, set_bitmap<Entry>);
  friend set_bitmap<Entry> operator -<> (set_bitmap<Entry>, set_bitmap<Entry>);

  public: set_bitmap(int N=1024); 	// allocate space - default 1K bits
	  ~set_bitmap();		// destructor - reclaim space
	  set_bitmap(const set_bitmap& x);	// copy constructor
	  set_bitmap& operator  = (const set_bitmap&);	// assignment operator
  	  bool is_member(Entry);	// check for membership
	  bool insert(Entry);	// add new member
	  bool remove(Entry);	// remove member
	  int setsize();	// current set size
	  void show(ostream&);	// output locations of the 1 bits

  private: unsigned char *bits;
	   int elements;	// number of array elements in bitlist
	   int size;	// number of potential elements in set
};

// constructor
template <class Entry>
set_bitmap<Entry>::set_bitmap(int N=1024)
{
  size = N;
  // figure how many bytes needed
  if (N%CHAR_BIT==0)
      elements = N/CHAR_BIT;
  else elements = N/CHAR_BIT + 1;
  bits = new unsigned char [elements];	// allocate from heap
  for (int i=0; i < elements; i++) bits[i] = 0;	// and set to 0
}

// destructor
template <class Entry>
set_bitmap<Entry>::~set_bitmap()
{
  delete[] bits;
}

template <class Entry>
set_bitmap<Entry>& set_bitmap<Entry>::operator = (const set_bitmap<Entry>& x)
{
  if (this != &x)
  { 
    elements = x.elements;
    size = x.size;
    delete[] bits;	// to avoid memory leak
    bits = new unsigned char[elements];
    for (int i=0; i<element; i++) bits[i] = x.bits[i];
  }
  return *this;
}

template <class Entry>
set_bitmap<Entry>::set_bitmap<Entry>(const set_bitmap<Entry> &x)
{
  // copy constructor
  elements = x.elements;
  size = x.size;
  bits = new unsigned char[elements];
  for (int i = 0; i < elements; i++) bits[i] = x.bits[i];
}

template <class Entry>
bool set_bitmap<Entry>::is_member(Entry E)
{
  int i = (int)E;
  if (i < 0 || i > size-1) return false; // index out of range
  if ( (bits[i/CHAR_BIT] & (1 << ((CHAR_BIT-1)-i%CHAR_BIT))) != 0)
       return true;
  else return false;
}

template <class Entry>
bool set_bitmap<Entry>::insert(Entry E)
{
  int i = (int)E;
  if (i < 0 || i > size-1) return false; // index out of range
  bits[i/CHAR_BIT] |= (1 << ((CHAR_BIT-1)-i%CHAR_BIT));
  return true;
}

template <class Entry>
bool set_bitmap<Entry>::remove(Entry E)
{
  int i = (int)E;
  if (i < 0 || i > size-1) return false; // index out of range
  if (!is_member(E)) return false;	// not in set
  bits[i/CHAR_BIT] &= ~(1 << ((CHAR_BIT-1)-i%CHAR_BIT));
  return true;
}

   
	
