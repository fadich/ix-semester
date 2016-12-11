/* RuleFalse.c                    IBM            27.03.95
*/
#include <stdio.h>
#include "expert.h"

void RuleFalse (r, ob, v100)
     struct RULE  *r;
   struct OBJECT  *ob;
    struct VALUE  *v100;
{
     extern FILE  *prtcl;
     extern char  protocol, EXPL[], EMPT[];
    struct VALUE  *v;
     struct PREM  *p;

  printf("\n%s RULE (%d) = FALSE, because the object \"%s\"",
            EXPL, r->numb, ob->name);
  printf("\n%s has value \"%s\" with cf = %d", EMPT,
         v100->name, v100->cert);
  if (protocol)
    {
      fprintf(prtcl,"\n%s RULE (%d) = FALSE, because the object \"%s\"",
              EXPL, r->numb, ob->name);
      fprintf(prtcl,"\n%s has value \"%s\" with cf = %d", EMPT,
              v100->name, v100->cert);
    }
  p = r->prem;
  while (p)
    {
      if ( p->obj == ob)
         {
           v = p->value;
           printf("\n%s and IF-part of this rule include the fact:\
                   \n%s\"%s = %s\".", EMPT, EMPT, ob->name, v->name);
           if (protocol) fprintf(prtcl,
                 "\n%s and IF-part of this rule include the fact:\
                  \n%s \"%s = %s\".", EMPT, EMPT, ob->name, v->name);
           return;
         }
      p = p->next;
    }
  printf("\nRuleFalse: error");
}
/* RuleFalse.c ----------------------------------------------------------*/
