/* level3.c             IBM             19.03.1995
  H.Schildt interpreter for student studing Multiplication or Division
   for two factors
*/
void level3 (result)
    int *result;
{
      extern char  token[];
    register char  op;
              int  hold;

    level4 (result);
    while ((op =* token) == '*' || op == '/' || op == '%')
     {
       get_token ();
       level4 (&hold);
       arith (op, result, &hold);
     }
}
/*level3.c-----------------------------------------------------------------*/
