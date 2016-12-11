/* Clearing.c
CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

void Clearing()
{
   extern struct OBJECT  *obj_list;
     extern struct RULE  *rule_list;
     extern struct LIST  *res;
          struct OBJECT  *ob;
           struct VALUE  *v;
            struct RULE  *ru;
            struct LIST  *re;

  ru = rule_list;
  while (ru)
    {
      ru->used = 0;
      ru = ru->next;
    }
  ob = obj_list;
  while ( ob )
    {
      v = ob->value;
      while ( v )
        {
          v->cert = 0;
          v = v->next;
        }
      ob = ob->next;
    }
  while (res)
    {
      re = res;
      res = re->next;
      free(re->elem);
      free(re);
    }
  res = NULL;
  return;
}
/* Clearing.c ---------------------------------------------------- */
