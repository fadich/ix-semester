/* ObjFree.c                 IBM               27.03.95
     CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

void ObjFree()
{
  extern struct OBJECT *obj_list;
         struct OBJECT *curr_obj;
          struct VALUE *curr_val;
           struct LIST *l;

  printf("\nObjFree: address of objects list is %X", obj_list);
  while(obj_list != NULL)
   {
     curr_obj = obj_list;
     if (curr_obj->name != NULL) free(curr_obj->name);
     if (curr_obj->question != NULL)
         free(curr_obj->question);
     while (curr_obj->value != NULL)
       {
         curr_val = curr_obj->value;
         curr_obj->value = curr_val->next;
         if (curr_val->name) free(curr_val->name);
         l = curr_val->prem;
         while (l)
            {
              curr_val->prem = l->next;
              free (l);
              l = curr_val->prem;
            }
         l = curr_val->con;
         while (l)
            {
              curr_val->con = l->next;
              free (l);
              l = curr_val->con;
            }
         free(curr_val);
       }
     obj_list = curr_obj->next;
     free(curr_obj);
   }
}
/* ObjFree.c -------------------------------------------------------------*/
