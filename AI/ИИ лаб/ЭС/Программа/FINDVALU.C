/*  FindValue.c                  IBM             27.03.95
    CADSHELL complex
*/
#include "expert.h"

struct VALUE *
     FindValue (obj_ptr, v_name)
     struct OBJECT *obj_ptr;
              char *v_name;
{
     struct VALUE *val_ptr;

  val_ptr = obj_ptr->value;
  while (val_ptr )
    if (!strcmp(v_name, val_ptr->name))
          break;  /* The value is present, it returns value address */
      else
          val_ptr = val_ptr->next;
              /* If the value is absent, then it returns NULL-address */
  return (val_ptr);
}
/* FindValue.c ------------------------------------------------------------ */
