/* level4.c             IBM            19.03.1995
   H.Schildt interpriter for student studing
*/
#include "schildt.dfn"

 void level4 (result)
      int *result;
 {
      extern char  token[],
		   token_type;
    register char  op;

    op = 0;
    if (( token_type == DELIMITER) &&
	    *token == '+' || *token == '-')
        {
          op = *token;
          get_token();
        }
     level5 (result);
     if (op)
	unary (op, result);
 }
/*level4.c--------------------------------------------------------------*/
