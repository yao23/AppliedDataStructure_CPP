template <class Entry>
class listnode
{
  private: Entry data;
  	   listnode *next;
};

template <class Entry>
class linkedlist
{
  public: linkedlist();	// constructor - initialize root
	  ~linkedlist(); // destructor - reclaim memory
	  int Getlength();
	  int Finditem(Entry X); // return position or -1
	  bool Finditem(int i, Entry& X); // get ith item. False if none
	  bool remove (int i);	// remove ith list element
	  bool insert (Entry X, int i);	// insert new item

  private: listnode<Entry> *root;
};
