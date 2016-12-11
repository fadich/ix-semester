/* SeeObj.c              IBM                10.04.95
*/
#include <stdio.h>
#include "expert.h"

void SeeObj()
{
  extern struct OBJECT *obj_list;
         struct OBJECT *curr_obj;

  curr_obj = obj_list;
  printf("\nSeeObj: address of object list is %X",obj_list);
  puts("\nObjects list:");
  while(curr_obj != NULL)
     {
       printf("<%X><%s>\n",curr_obj,curr_obj->name);
       curr_obj = curr_obj->next;
   /*  getchar();   */
     }
  return;
}
/*SeeObj ----------------------------------------------------------------*/
