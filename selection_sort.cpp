void selection_sort(int T[], int low, int high)
{
  int temp;
  for( int i = low; i <= high; i++ ) { // find smallest among T[i]...T[high]    
    int min = T[i]; // smallest so far
    int minind = i; // index of smallest so far

    for( int j = i+1; j <= high; j++ )
      if( T[j] < min ) { min = T[j]; minind = j; }

    // now exchange it with T[i] if not already there
    if( i != minind ) {
      temp = T[i];
      T[i] = min;
      T[minind] = temp;
    }
  }
}



