/* AddQuest.c              IBM            27.03.95
   CADSHELL complex
*/
#include <stdio.h>
#include <stdlib.h>
#include "expert.h"

char AddQuest (curr_obj, quest)
     struct OBJECT *curr_obj;
              char *quest;
{
  curr_obj->question = malloc (strlen (quest) + 1);
  if (curr_obj->question == NULL)
     return 0;
  strcpy (curr_obj->question, quest);

  return 1;
}
/* AddQuest.c ------------------------------------------------------------ */
