void merge(int T[], int low, int middle, int high)
{ // pre: sorted are T[low..middle) and T[middle+1..high]
  // post: sorted are T[low..high]

  int i, left = low, right = middle+1;
  int *temp = new int[high+1]; // temporary storage

  for( i = low; i <= high; i++) 
    if( left > middle ) { temp[i] = T[right]; right++; }
  else if( right > high ) { temp[i] = T[left]; left++; }
  else if(T[left] < T[right]) { temp[i] = T[left]; left++; }
    else { temp[i] = T[right]; right++; }

  for( i = low; i <= high; i++ ) T[i] = temp[i];

  delete[] temp; // finished with temporary storage
}

void mergesort(int T[], int low, int high)
{
  if( (high-low) < 5 )
    selectionsort(T, low, high); // or another nonrecursive sort
  else {
    int middle = (low+high)/2;
    mergesort(T, low, middle);
    mergesort(T, middle+1, high);
    merge(T, low, middle, high);
  }
}
