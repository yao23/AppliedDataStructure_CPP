template <class vertex>
class graph
{
  public: graph();	// constructor - initialize graph
	  ~graph();	// destructor - tidy up any storage allocation
	  bool isempty();	// true if no vertices
  	  int numvertices();	// return the number of vertices
  	  bool insertvertex(vertex v);
	  bool deletevertex(vertex v);
 	  bool insertedge(vertex v1, vertex v2);
	  bool deleteedge(vertex v1, vertex v2);
	  list<vertex> adjacent(vertex v);

  private:
           // see implementation possibilities below
}; 
