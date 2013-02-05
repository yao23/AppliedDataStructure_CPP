int find(char Pattern[], int M, char Text[], int N)
{
  int index = 0, text_index, pattern_index;
  while ( index < N-M+1 ) // more alignment to try
  {
    index++;
    text_index = index;
    pattern_index = 1;
  
    while (Pattern[pattern_index] ==  Text[text_index])
    {
      if ( pattern_index == M )
         return index;	// matched all of Pattern

      text_index++;	// move to next pair of
      pattern_index++;	// characters to compare
    }
  }

  return -1; 	// no match found
}
