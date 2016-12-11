/* FindObj.c               IBM             25.10.97
*/
#include <stdio.h>
#include "expert.h"

char FindObj (name_obj,obj_ptr)
           char *name_obj;
  struct OBJECT **obj_ptr;
{
 extern struct OBJECT  *obj_list;
          extern FILE  *debfile;
          extern char  debug;

 *obj_ptr = obj_list;
 while (*obj_ptr != NULL)
   {
     if (!strcmp (name_obj,(*obj_ptr)->name))
       {
	if (debug == 2) fprintf(debfile,
	   "\n FindObj: object \"%s\"(%X) is present in the list",
	    (*obj_ptr)->name, *obj_ptr);
        return 1; /* object is present and its address is returned */
       }
     if ((*obj_ptr)->next == NULL)
       {
        if (debug == 2) fprintf(debfile,
           "\n FindObj: object \"%s\" is absent in the list",
            *obj_ptr);
        return 0;  /* object is absent and it returns the address
                      of the last object in the list   */
      }
     *obj_ptr = (*obj_ptr)->next;
   }
  return 0; /* the object list is empty and it returns NULL-address */
}
/* FindObj.c ------------------------------------------------------------- */
