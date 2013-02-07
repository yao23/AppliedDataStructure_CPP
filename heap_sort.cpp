reheap_elements(int T[], int A, int limit)
{
  if T [A] not a leaf
  {
    largechild = index of child with larger value
    if T[A] < elements[largechild]
    {
      swap( T[A], T[largechild] );
      reheap_elements(T, largechild, limit);
    }
  }
}
