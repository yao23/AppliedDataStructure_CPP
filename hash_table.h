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

