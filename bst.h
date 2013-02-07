template <class Entry> class map_bst;	// forward declaration

template <class Entry>
class treenode
{
  friend class map_bst<Entry>;
  public: treenode(const Entry& X) {
            data = X;
	    left = NULL;
	    right = NULL;
          }
  private: treenode *left;
	   Entry data;
	   treenode *right;
};

template <class Entry>
class map_bst
{
  public: map_bst();	// constructor
  	  ~map_bst();	// destructor
	  map_bst(const map_bst& rhs);	// copy constructor
	  map_bst& operator = (const map_bst&);	// assignment
	  void showmap(ostream&) const;	// display contents
	  bool retrieve(Entry&); // looks for key match, puts in
	  bool insert(const Entry&);  // overwrites if key there
	  bool remove(const Entry&); // deletes one with same key

  private: treenode<Entry> *root;
 	   bool copytree(treenode<Entry> *&newtree, 
	                 treenode<Entry> *&newtree); // for use by replicator
           void destruct_aux(treenode<Entry> *t); // actual destruct
   	   void inorder_aux(treenode<Entry> *t, ostream& s) const; // traverser
       	   bool insert_aux(Entry X, treenode<Entry> *&t); // inserter
           treenode<Entry>* retrieve_aux(Entry, treenode<Entry> *t); // retriever
    	   bool remove_aux(Entry X, treenode<Entry> *&t); // deleter
 	   void removenode(treenode<Entry> *&t);
	   void getpredecessor(treenode<Entry> *t, Entry&);
};

template <class Entry>
map_bst<Entry>::map_bst()
{ // constructor - initialize root
  root = NULL;
}

template <class Entry>
map_bst<Entry>::~map_bst()
{ // destructor - reclaim space
  destruct_aux(root);
}

template <class Entry>
void map_bst<Entry>::destruct_aux(treenode<Entry> *t)
{ // actual space reclaimer
  if( t != NULL ) {
    destruct_aux(t->left);	// reclaim left subtree
    destruct_aux(t->rightt);	// reclaim right subtree
    delete t;
  }
}

template <class Entry>
bool map_bst<Entry>::copytree(treenode<Entry> *&newtree,
				treenode<Entry> *&oldtree)
{
  newtree = NULL;
  if( oldtree != NULL ) {
    newtree = new treenode<Entry>(oldtree->data);
    if( newtree == NULL ) return false;	// out of space
    // return true if both subtrees copy ok
    return copytree(newtree->left, oldtree->left) &&
 	   copytree(newtree->right, oldtree->right);
    }
  return true;
}

template <class Entry>
map_bst<Entry>::map_bst(const map_bst& rhs)
{ // copy constructor
  copytree(root, rhs.root);
}

template <class Entry>
map_bst<Entry>& map_bst<Entry>::operator = (const map_bst& rhs)
{ // overloaded assignment operator
  if( this != &rhs ) { // not assigning to self
    treenode<Entry> *temp;
    if( copytree(temp, rhs.root) ) {
      destruct_aux(root);	// prevent possible memory leak
      root = temp;
    }
  }
  return *this;
}

template <class Entry>
void map_bst<Entry>::showmap(ostream &s) const
{ // to display tree contents - an inorder traversal
  inorder_aux(root, s);
}

template <class Entry>
void map_bst<Entry>::inorder_aux(treenode<Entry> *t, ostream &s) const
{
  if( t != NULL ) {
    inorder_aux(t->left, s);
    s << t->data;
    inorder_aux(t->right, s);
  }
}

template <class Entry>
bool map_bst<Entry>::retrieve(Entry& target)
{ // if there is a map entry with the same key as target,
  // we overwrite target with the entry
  treenode<Entry> *ptr = retrieve_aux(target, root);
  if( ptr == NULL ) return false;	// not found
  // overwrite parameter
  target = ptr->data;
  return true;
}

template <class Entry>
treenode<Entry>* map_bst<Entry>::retrieve_aux(Entry target, treenode<Entry> *t)
{
  if( t == NULL ) return NULL;	// empty tree
  if( !(t->data < target) && !(target < t->data) ) 
    return t;	// found
  if( t->data < target )
    return retrieve_aux(target, t->right); // look in right subtree
  else 
    return retrieve_aux(target, t->left); // look in left subtree
}
   
template <class Entry>
bool map_bst<Entry>::insert(const Entry& target)
{ // if we find an entry in the tree with the same key as target
  // (use < to detemine this) then overwrite it with target.
  // otherwise, try to insert new entery into tree
  treenode<Entry> *ptr = retrieve_aux(target, root);
  if( ptr != NULL ) { // already in?
    ptr->data = target;	// yes - overwrite
    return true;
  }
  else return insert_aux(target, root);	// no - insert new entry
}

template <class Entry>
bool map_bst<Entry>::insert_aux(Entry X, treenode<Entry> *&t)
{
  if( t == NULL ) { // empty root so put entry here
    t = new treenode<Entry>(X);
    if( t == NULL ) rueturn false; // no heap space available
    return true;
  }
  else {
    if( X < t->data ) 
      return insert_aux(X, t->left);	// goes in left subtree
    else
      return insert_aux(X, t->right);	// goes in right subtree
  }
}
