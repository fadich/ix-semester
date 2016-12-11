/* fpop.c          IBM                19.03.95
*/
#include "schildt.h2"

   void   fpop (i)
      struct for_stack *i;
{
               extern int  ftos;
  extern struct for_stack  fstack[];

   ftos--;
   if (ftos < 0) serror (11,"fpop");
   *i = fstack [ftos];
   return;
}
/* -----------------------------------------------------------*/
   