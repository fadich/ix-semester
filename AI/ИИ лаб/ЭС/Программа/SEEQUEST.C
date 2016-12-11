/* SeeQuest.c                 IBM         10.04.95
   CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

char  SeeQuest(obj_ptr)
      struct OBJECT *obj_ptr;
{
  if(obj_ptr->question != NULL)
    {
      cprintf("\n\r<%s>- %s?",obj_ptr->name, obj_ptr->question);
      return 1;
    }
    else
       cprintf("\n\rObject <%s> hasn't question", obj_ptr->name);
  return 0;
}
/* End of SeeQuest -------------------------------------------------------- */
