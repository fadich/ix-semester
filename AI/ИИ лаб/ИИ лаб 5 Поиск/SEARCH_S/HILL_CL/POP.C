/*                                   19.11.98
*/
#include <stdio.h>
#include <string.h>
#include "search.h"

void pop (from,to,dist)
    char  *from, *to;
     int  *dist;
{
	 extern int  tos;
extern struct stack  bt_stack[];

  if(tos > 0)
    {
      tos--;
      strcpy(from,bt_stack[tos].from);
      strcpy(to,bt_stack[tos].to);
      *dist=bt_stack[tos].dist;
    }
   else printf("Stack underflow.\n");
}
