/* gener.c                        04.09.98
   generalize new examples
    */
#include <stdio.h>
#include <string.h>
#include "ml.h"

 extern struct attr  may[], must[];
	 extern int  may_pos, must_pos;
	extern FILE  *prtcl;
    
    generalize (n,v,o)
       char *n,*v,*o;
 {
	int  t,i;

   /* check may_have list*/
    for (t=0; t<may_pos; t++)
      {
         if (strcmp(may[t].subject,n)  &&  /*not same subject*/
             !strcmp(may[t].verb,v)  &&
             !strcmp(may[t].object,o) && may[t].active)
                {
                   strcat(may[t].subject," or ");
                   strcat(may[t].subject,n);
                }
      }
    for(t=0; t<may_pos; t++)
      {
         if (!strcmp(may[t].subject,n) &&
             !strcmp(may[t].verb,v) &&
              strcmp(may[t].object,o) /*not same object*/
            && may[t].active)
             {
               strcat(may[t].object," or ");
               strcat(may[t].object,o);
             }
      }
    /*check must_have list */
    for (t=0;t<must_pos;t++)
      {
        if(strcmp(must[t].subject,n)  &&  /*not same subject*/
           !strcmp(must[t].verb,v) && !strcmp(must[t].object,o))
            {
               strcat(must[t].subject," or ");
               strcat(must[t].subject,n);
               i = find_may(n,v,o);
               may[i].active=0; /*remove from may_have list*/
            }
      }
    for(t=0;t<must_pos;t++)
      {
        if (!strcmp(must[t].subject,n) &&
	    !strcmp(must[t].verb,v) &&
	     strcmp(must[t].object,o)) /*not same object*/
           {
              strcat(must[t].object," or ");
              strcat(must[t].object,o);
              i=find_may(n,v,o);
              may[i].active=0;   /*remove from may_have list*/
           }
      }
  return;
}
/* gener.c ---------------------------------------------------*/
