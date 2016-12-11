/*AddPrem.c                      IBM                   20.10.97
 */
#include <stdio.h>
#include <string.h>
#include "expert.h"

void AddPrem(curr_rule, pr_obj, pr_val)
    struct RULE *curr_rule;
           char *pr_obj,
                *pr_val;
{
      extern FILE *debfile;
      extern char debug;
      struct PREM *prem_ptr, *curr_prem;
    struct OBJECT *c_obj;
     struct VALUE *c_val;

if (debug == 2) fprintf(debfile,
    "\nAddPrem: rule=(%d)%X, obj=%s, val=%s",
         curr_rule->numb, curr_rule, pr_obj, pr_val);
  prem_ptr = (struct PREM *) malloc (sizeof (struct PREM));
  if ( ! FindObj(pr_obj, &c_obj) ) AddObj(&c_obj, pr_obj);
  prem_ptr->obj = c_obj;
  c_val = (struct VALUE *) FindValue(c_obj, pr_val);
  if ( ! c_val)
         c_val = (struct VALUE *) AddValue (c_obj, pr_val);
  prem_ptr->value = c_val;
  AddInList(&c_val->prem, curr_rule);
  prem_ptr->next = NULL;
  if (curr_rule->prem == NULL)
        curr_rule->prem = prem_ptr;
     else
        {
          curr_prem = curr_rule->prem;
          while (curr_prem->next )
             curr_prem = curr_prem->next;
          curr_prem->next = prem_ptr;
        }
if (debug == 2) fprintf(debfile,
   "\nAddPrem: prem=%X, obj=(%s)%X, val=(%s)%X", prem_ptr,
     c_obj->name, c_obj, c_val->name,c_val);
    return;
}
/* AddPrem ----------------------------------------------------------- */
