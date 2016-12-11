/* putback.c          IBM           24.02.95
   H.Schildt interpreter for student studing
   Token returning into input.
*/
void putback()
{
  extern char  token[],
	       *prog;
	 char  *t ;

  t = token ;
  for ( ; *t; t++) prog--;
}
/*putback.c___________________________________________________*/
