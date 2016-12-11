/* restrict.c                         04.09.98
   restrict the description of an object-1. e.remove from
    may-have list and place in must-have list.
     */
#include <string.h>
#include "ml.h"

   void restrict (ms, mv, mo)
          char *ms, *mv, *mo;
{
       register int  t;
               char  temp[4];
         extern int  may_pos;
 extern struct attr  may[];
        
  for(t=0; t<3; t++)
      temp[t] = tolower(mv[t]);
  temp[3] = '\0';
  if(strcmp(temp,"not")) return;
  for (t=0; t<may_pos; t++)
    {
      if (!strcmp (&mv[4],may[t].verb) &&
          !strcmp (may[t].subject,ms) &&
          !strcmp (may[t].object,mo) && may[t].active)
       {
        assert_must (may[t].subject, may[t].verb, may[t].object);
        may[t].active = 0; /*remove from list*/
        return;
       }
    }
}
    
