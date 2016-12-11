/* Must.c                                04.09.98
  place an entry into the must have database */
#include <string.h>
#include "ml.h"

   assert_must (n,v,o)
      char *n, *v, *o;
{
 extern struct attr  must[];
         extern int  must_pos;

   if (must_pos < MAX)
     {
       strcpy(must[must_pos].subject,n);
       strcpy(must[must_pos].verb,v);
       strcpy(must[must_pos].object,o);
       must_pos ++;
     }
    else
       puts("Out of memory for must have database\n");
 return;
 }

  
