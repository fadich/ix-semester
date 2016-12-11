/* level5.c               IBM           19.03.1995
H.Schildt interpreter for studing studing
*/
#include "schildt.dfn"

void level5 (result)
   int *result;
{
 extern char  token[],
	      token_type;

   if (*token == '(' && (token_type == DELIMITER))
     {
      get_token();
      level2 (result);
      if (*token != ')') serror (1,"level5");
      get_token();
     }
    else
      primitive (result);
}
/* level5 -------------------------------------------------- */
