/* FindRule.c                   IBM              15.10.97
  CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

struct RULE *  FindRule (obj)
       struct OBJECT  *obj;
{
    extern FILE  *prtcl;
    extern char  debug;
   struct VALUE  *v;
    struct LIST  *l;
    struct RULE  *r;

  v = obj->value;
  while (v)
    {
      l = v->con;
      while (l)
        {
          r = (struct RULE *) l->elem;
          if (r->used) l = l->next;
            else
	      { if (debug) fprintf(prtcl,"\n FindRule (%d)", r->numb);
                return (r); /* the rule is not used  */
              }
        }
      v = v->next;
    }
  if (debug) fprintf(prtcl,"\n FindRule (NULL)");
  return (NULL);
}
/* FindRule.c --------------------------------------------------- */
