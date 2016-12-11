/* astr.c                               04.09.98
     Learning class description by using the
	    "hit-and-near-miss" method
     place an entry into the may-have database
    */
#include <stdio.h>
#include <string.h>
#include "ml.h"

  assert_may (n,v,o)
       char *n, *v, *o;
 {
   extern struct attr  may[];
	   extern int  may_pos;

       if (may_pos < MAX)
          {
            strcpy (may [may_pos].subject, n);
            strcpy (may [may_pos].verb, v);
            strcpy (may [may_pos].object, o);
            may [may_pos].active = 1;
            may_pos++;
           }
        else
	    puts("Out of memory for may_have database");
   return;
  }
