template<class Type>
class counter
{
  public : counter(Type N=0) { data = N; }
           void increment(Type D=1) { data += D; }
           Type getvalue() { return data; }

  private: Type data;
};
