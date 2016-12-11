/* AddValue.c             IBM              27.03.95
*/
#include <stdlib.h>
#include "expert.h"

struct VALUE *
   AddValue (curr_obj, v_name)
     struct OBJECT *curr_obj;
              char *v_name;
{
     struct VALUE *v_ptr, *v;

  v_ptr = (struct VALUE *) malloc (sizeof (struct VALUE) );
  v_ptr->name = malloc (strlen (v_name) + 1);
  v_ptr->cert = 0;
  v_ptr->prem = NULL;
  v_ptr->con = NULL;
  strcpy (v_ptr->name, v_name);
  v_ptr->next = NULL;
  if (curr_obj->value == NULL)
        curr_obj->value = v_ptr;
     else
        {
          v = curr_obj->value;
          while (v->next)
              v = v->next;
          v->next = v_ptr;
        }
  return (v_ptr);
}
/* AddValue.c -----------------------------------------------------------*/
