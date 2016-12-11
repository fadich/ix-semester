/* AddInList.c                 IBM              27.03.95
 CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

void  AddInList (l, r)
      struct LIST  **l;
      struct RULE  *r;
{
   struct LIST  *curr, *el;

  el = (struct LIST *) malloc (sizeof(struct LIST) );
  el->elem = (void *) r;
  el->next = NULL;
  if (*l)   /* List isn't empty  */
     {
       curr = *l;
       while (1)
         if ( ! curr->next)
            {
               curr->next = el;
               return;
            }
            else
                curr = curr->next;
     }
    else
        *l = el;
  return;
}
/* AddInList.c -----------------------------------------------------*/
