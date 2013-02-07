bool breadth_first_search(int i, int j, graph G)
{
  queue<int> Q;	// vertices to check 
  int n = G.numbervetices(); // number of vertices in graph
  bool visited[n]; // whether or not vertex has been visited

  for( int k = 0; k < n; k++) visited[k] = false; // mark all unvisited
  visited[i] = true;	// except starting point

  Q.enqueue(i); // start vertex

  while( !Q.empty() ) { // more vertices to check?
    int current = Q.dequeue(); // first vertex number in the queue

    for( int k = 0; k < n; k++ ) // look at its neighbors
      if( G.exists_edge(current, k) ) { // edge to k?
        if( k == j ) return true; // found end-point, path exists

   	if( !visited[k] ) { // haven't visited k yet
	  Q.enqueue(k);	// put it on the queue to visit
	  visited[k] = true; // and mark it
 	}
      }
  }
  return false;	// no more to check, search for path is unsuccessful
}

