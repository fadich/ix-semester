/*level2.c             IBM            19.03.1995
  H.Schioldt interpreter for student studing
  Addition or Subtraction for two terms
*/
void level2 (result)
     int *result;
{
       extern char  token[];
     register char  op;
	       int  hold;

     level3 (result);
     while ((op =* token) == '+' || op == '-')
     {
       get_token ();
       level3 (&hold);
       arith (op, result, &hold);
     }
}
/*level2.c___________________________________*/
