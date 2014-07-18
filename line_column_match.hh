#ifndef LINE_COLUMN_MATCH_HH
#define LINE_COLUMN_MATCH_HH
#include<ctype.h>
template<typename alphabet, typename pos_type, typename T>
inline bool line_column_match(const Basic_Sequence<alphabet, pos_type> &seq, T i, T k,
    T l, T m, T n, T j)
{
  int l_border = 0;
  int c_border= j;
	
  for(int x=l-2;x>0;--x) {
    if(!isdigit(seq[x])) {
      l_border = x+1;
      break;
    }
  }
  for(int x=m+1;x<j;++x) {
    if(!isdigit(seq[x])) {
      c_border = x-1;
      break;
    }
   }
   
  if ((l-1) - l_border != c_border - m) {
    goto stop;
  }
  
  for(int x=l_border, y=m;x<=l-1;++x,++y) {
    if(seq[x] != seq[y]) goto stop;
  }
  return true;
  
  stop:
  std::cerr << "Matrix dimensions don't match!" << std::endl;
  std::exit(1);
}

inline bool line_column_match_st(tuple a1,char a2,tuple a3) {
	if (a1.cols == a3.rows)
		return true;
	else
	{
		  std::cerr << "Matrix dimensions don't match!" << std::endl;
		  std::exit(1);
	} 
}
#endif