/*  found shortest distance             19.11.98
*/
#include <stdio.h>
#include "search.h"

int route (to)
    char *to;
{
                int  dist,t;
         static int  old_dist = 32000;
extern struct stack  bt_stack[];
	 extern int  tos, stos;

  if (!tos) return 0; /* all done  */
  t=0;
  dist=0;
  while (t<tos)  
    {
      printf("%s to ", bt_stack[t].from);
      dist += bt_stack[t].dist;
      t++;
    }
  printf("%s\n", to);
  printf("distance is %d\n", dist);
/* if shorter, then make new solution */
  if (dist < old_dist && dist)
    { t=0;
      old_dist = dist;
      stos = 0;  /* clear old route from solution stack */
      while (t < tos)
        { spush (bt_stack[t].from, bt_stack[t].to,
                 bt_stack[t].dist);
          t++;
        }
     }
  return dist;
}
