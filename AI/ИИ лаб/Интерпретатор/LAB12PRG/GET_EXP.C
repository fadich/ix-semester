/*get_exp.c            IBM 386         19.03.95
  H.Schildt interpreter for student studing
  Entrance into analyzer
*/
void get_exp (result)
    int *result;
{
  extern char token[];

    get_token();
    if (! *token)
      {
       serror (2,"get_exp");
      }
    level2 (result);
    putback();
}
/*get_exp.c_______________________________*/
