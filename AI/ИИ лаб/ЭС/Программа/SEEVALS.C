/* SeeVals.c                   IBM             10.04.95
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

void SeeVals(obj_ptr)
   struct OBJECT *obj_ptr;
{
   struct VALUE *c_val;

  c_val = obj_ptr->value;
  cprintf("\n\rSeeVals: for object \"%s\" value list is\n",
	  obj_ptr->name);
  while (c_val != NULL)
     {
       cprintf("  <%X> \"%s\"",c_val, c_val->name);
       c_val = c_val->next;
     }
  return;
}
/* ----------------------------------------------------------------------- */
