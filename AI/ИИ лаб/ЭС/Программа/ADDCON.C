/*  AddCon.c                   IBM          20.10.97
  CADSHELL complex
*/
#include <stdio.h>
#include <stdlib.h>
#include "expert.h"

void AddCon (curr_rule, n_obj, n_val, c_cert)
     struct RULE *curr_rule;
            char *n_obj,
                 *n_val;
             int  c_cert;
{
       extern FILE *debfile;
       extern char debug;
        struct CON *con_ptr, *curr_con;
     struct OBJECT *p_obj;
      struct VALUE *p_val;

 if (debug == 2)
   fprintf(debfile,
    "\nAddCon: rule=(%d)%X, obj=%s, val=%s, cert=%d",
       curr_rule->numb, curr_rule, n_obj, n_val, c_cert);
con_ptr = (struct CON *) malloc (sizeof(struct CON) );
if ( ! FindObj(n_obj, &p_obj) ) AddObj(&p_obj, n_obj);
con_ptr->obj = p_obj;
p_val = (struct VALUE *) FindValue (p_obj, n_val);
if ( ! p_val)
       p_val = (struct VALUE *) AddValue (p_obj, n_val);
con_ptr->value = p_val;
AddInList(&p_val->con, curr_rule);
con_ptr->cert = c_cert;
con_ptr->next = NULL;
if (curr_rule->con == NULL)
      curr_rule->con = con_ptr;
   else
      {
        curr_con = curr_rule->con;
        while (curr_con->next )
            curr_con = curr_con->next;
        curr_con->next = con_ptr;
      }
if (debug == 2) fprintf(debfile,
   "\nAddCon: con=%X, obj=(%s)%X, val=(%s)%X", con_ptr,
      p_obj->name, p_obj, p_val->name, p_val);
  return;
}
/* AddCon ------------------------------------------------------------- */
