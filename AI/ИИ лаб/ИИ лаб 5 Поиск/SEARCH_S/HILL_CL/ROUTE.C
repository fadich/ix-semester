/*  found the route and distance             19.11.98
*/
#include <stdio.h>
#include "search.h"

void route (to)
    char *to;
{
                int  dist,t;
extern struct stack  bt_stack[];
         extern int  tos;

  t=0;
  dist=0;
  while (t<tos)  
    {
      printf("%s to ", bt_stack[t].from);
      dist += bt_stack[t].dist;
      t++;
    }
  printf("%s\n",to);
  printf("distance is %d\n",dist);
  return;
}
