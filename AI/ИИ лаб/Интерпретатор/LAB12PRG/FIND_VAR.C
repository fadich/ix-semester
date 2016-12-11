/* find_var.c              IBM           13.03.95
*/
#include <ctype.h>

int find_var (s)
     char  *s;
{
  extern int  variables[];
 extern char  token[];

   if (!isalpha (*s))
      {  serror (4,"find_var");  /* it's not variable  */
         return 0;
      }
   return (variables[toupper (token[0]) - 'A']);
}
/* -------------------------------------------------------*/           