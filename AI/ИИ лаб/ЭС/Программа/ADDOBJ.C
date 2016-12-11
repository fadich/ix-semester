/* AddObj.c                   IBM                  14.09.98
   Object addition for CADSHELL project
*/
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expert.h"

char AddObj(c_obj, obj_name)
     struct OBJECT **c_obj;  /* address of the last object in the list  */
              char *obj_name;
{
          struct OBJECT *obj_ptr;
   extern struct OBJECT *obj_list;
            extern FILE *debfile;
	    extern char debug;

  obj_ptr = (struct OBJECT *) malloc(sizeof(struct OBJECT));
  if (obj_ptr == NULL)
    { puts("\nAddObj: No room for new object list member");
      getch();
      return 0;
    }
  if (*c_obj == NULL)   /* list is empty  */
       obj_list = obj_ptr;
     else
       (*c_obj)->next = obj_ptr;
  *c_obj = obj_ptr;  /* new object is current now  */
  /*            */
  if ((obj_ptr->name = malloc(strlen(obj_name)+1)) == NULL)
      { puts("\nAddObj: No room for name of a new object");
	getch();
        return NULL;
      }
  strcpy(obj_ptr->name, obj_name);
  if (debug == 2) fprintf(debfile,
    "\n AddObj: object \"%s\"(%X) is added in the list",
    obj_ptr->name, obj_ptr);
  obj_ptr->question = NULL;
  obj_ptr->value = NULL;
  obj_ptr->next = NULL;

  return 1;
} /* end of PGM  */
/* AddObj.c -----------------------------------------------------------*/
