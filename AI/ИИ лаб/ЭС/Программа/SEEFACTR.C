/* SeeFactRule.c            IBM             10.04.95
CADSHELL complex
*/
#include "expert.h"

void SeeFactRule()
{
  extern struct OBJECT *obj_list;
         struct OBJECT *curr_obj;
          struct VALUE *v;
           struct LIST *l;
           struct RULE *r;

  curr_obj = obj_list;
  puts("\nFacts list:");
  while(curr_obj )
     {
       v = curr_obj->value;
       while (v)
         {
           printf("\nfact:<%s>=<%s>",curr_obj->name, v->name);
           l = v->prem;
           if (l)
              {
                puts("\n    is included in the prem-part of the rules:");
                while (l)
                  {
                    r = (struct RULE *) l->elem;
                    printf("   <%d>", r->numb);
                    l = l->next;
                  }
              }
           l = v->con;
           if (l)
              {
                puts("\n    is included in the con-part of the rules:");
                while (l)
                  {
                    r = (struct RULE *) l->elem;
                    printf("   <%d>", r->numb);
                    l = l->next;
                  }
              }
           if ((!v->prem) && (!v->con))
              puts(" is not included in any rule.");
           v = v->next;
         }
       curr_obj = curr_obj->next;
     }
  return;
}
/*SeeFactRule -----------------------------------------------------------*/
