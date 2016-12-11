/* Find_May.c                             07.09.98
   find and entry in the may have database
*/
#include <string.h>
#include "ml.h"
   find_may (n,v,o)
	char *n, *v, *o;
 {
 extern struct attr  may[];
         extern int  may_pos;
       register int  t;

        for (t=0; t<may_pos; t++)
            if (!strcmp(may[t].subject,n) &&
                !strcmp(may[t].verb,v) &&
                !strcmp(may[t].object,o) &&
                 may[t].active)
                           return t;
	return -1;
 }
