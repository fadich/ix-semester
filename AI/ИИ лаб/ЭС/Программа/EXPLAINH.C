/* ExplainHow.c                 IBM             27.03.95
*/
#include <stdio.h>
#include "expert.h"

void ExplainHow (r)
    struct RULE  *r;
{
    extern FILE  *prtcl;
    extern char  EXPL[], EMPT[], protocol;
  struct OBJECT  *o;
   struct VALUE  *v;
    struct PREM  *p;
     struct CON  *c;

  printf("\n%s On the basis of a RULE (%d) with cf = %d",
         EXPL, r->numb, r->cert);
  printf("\n%s the conclusion is:",EMPT);
  if (protocol)
    { fprintf(prtcl, "\n%s On the basis of a RULE (%d) with cf = %d",
          EXPL, r->numb, r->cert);
      fprintf(prtcl, "\n%s the conclusion is:", EMPT);
    }
  c = r->con;
  while (c)
    {
      o = c->obj;
      v = c->value;
      printf("\n%s %s = %s with cf = %d",EMPT,o->name,v->name,v->cert);
      if (c->next)  printf(" and");
             else   printf(", ");
      if (protocol)
        { fprintf(prtcl, "\n%s %s = %s with cf = %d",
               EMPT, o->name, v->name, v->cert);
          if (c->next)  fprintf(prtcl, " and");
                 else   fprintf(prtcl, ", ");
        }
      c = c->next;
    }
  printf("\n%s because", EMPT);
  if (protocol) fprintf(prtcl, "\n%s because", EMPT);
  p = r->prem;
  while (p)
    {
      o = p->obj;
      v = p->value;
      printf("\n%s %s = %s with cf = %d", EMPT,o->name,v->name,v->cert);
      if (p->next) printf(" and");
             else  printf(". ");
      if (protocol)
        { fprintf(prtcl, "\n%s %s = %s with cf = %d", EMPT,
                o->name, v->name, v->cert);
          if (p->next) fprintf (prtcl, " and");
                 else  fprintf (prtcl, ". ");
        }
      p = p->next;
    }
}
/* ExplainHow.c ----------------------------------------------------------*/
