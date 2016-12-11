/* Conclude.c                 IBM            14.09.98
  CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

void Conclude(r, rcf)
   struct RULE *r;
          int  rcf;
{
    extern char  explan, debug;
    extern FILE  *prtcl;
     struct CON  *con;
   struct VALUE  *v;
  struct OBJECT  *obj;
            int  cf;

  con = r->con;
  while( con )
    {  /*  Facts  addition  */
      v = con->value;
      obj = con->obj;
      cf = v->cert;
      if (cf<100)
        cf = cf + rcf * con->cert / 100 * (100 - cf) / 100;
      v->cert = cf;
      if (debug) fprintf(prtcl, "\n Conclude: <%s = %s> cf=%d",
         obj->name, v->name, cf);
      con = con->next;
    }
  if (explan) ExplainHow(r);
  return;
}
/* Conclude.c ----------------------------------------------------- */
