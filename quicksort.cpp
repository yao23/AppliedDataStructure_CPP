int partition(int T[], int low, int high)
{ // partitions the array from T[low] to T[high] and
  // returns the index of the pivot element
  int middle = (low+high)/2, upper = low, lower = high, temp;
  // order the first, last, and middle elements
  if(T[low] > T[middle]) exchange(T[low], T[middle]);
  if(T[low] > T[high]) exchange(T[low], T[high]);
  if(T[middle] > T[high]) exchange(T[middle], T[high]);

  // move median of 3 to beginning
  exchange(T[low], T[middle]);
  temp = T[low]; // the pivot

  // now partition
  while( upper != lower ) {
    while( (upper < lower) && (temp <= T[lower]) ) lower--;
    if( upper != lower ) T[upper] = T[lower];
    while( (upper < lower) && (temp <= T[upper]) ) upper++;
    if( upper != lower ) T[lower] = T[upper];
  }
  T[upper] = temp; return upper;
}

void quicksort(int T[], int low, int high)
{
  if( (high-low) < 5 ) // arbitrary cut-off
    selectionsort(T, low, high); // or other nonrecursive sort
  else {
    int pivot = partition(T, low, high);
    quicksort(T, low, pivot-1);
    quicksort(T, pivot+1, high);
  }
}
 
