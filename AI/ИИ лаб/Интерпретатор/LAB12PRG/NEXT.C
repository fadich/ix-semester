/*  next.c                 IBM           19.03.95
   H.Schildt interpreter for student studing
*/
#include "schildt.h2"

 void next()
{
              extern char  *prog;
               extern int  variables[];
	 struct for_stack  i;

     fpop (&i);
    variables[i.var] ++;
    if (variables[i.var] > i.target) return;
    if (fpush (i)) return;
    prog = i.loc;
  }
/*---------------------------------------------------------------------*/
