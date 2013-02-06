template <class Entry>
class set
{
  public: set();		// constructor - empty set
	  ~set();		// destructor - reclaim space
	  set(const set& x);	// copy constructor
	  set& operator = (const set&);	// assignment operator
	  bool is_member(Entry E);	// check for membership
	  bool insert(Entry E);		// add new member
	  bool remove(Entry E);		// remove member
	  bool empty();		// is set empty?
	  int size();		// current set size
	  void show(ostream&, char[]="");	// contents to output stream
	  bool extract(Entry& E);	// take out arbitrary member

  private: // implementation specific
}
