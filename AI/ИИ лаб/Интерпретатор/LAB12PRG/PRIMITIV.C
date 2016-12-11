/* primitive.c             IBM             13.03.1995
H.Schildt interpreter for student studing
*/
#include <stdlib.h>
#include "schildt.dfn"

void primitive (result)
   int * result;
{
  extern char  token[],
	       token_type;

  switch (token_type)
    {
      case VARIABLE:
	   *result = find_var(token);
	   get_token();
	   return;
      case NUMBER:
	   *result = atoi(token);
           get_token();
           return;
      default:
           serror(0,"primitive");
     }
}
/*primitive---------------------------------*/
