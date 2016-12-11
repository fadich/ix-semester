/* AddRule.c                IBM                   20.10.97
   Rule addition for CADSHELL complex
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expert.h"

struct RULE *
      AddRule(nmb,r_cert)
 int nmb,
     r_cert;
 {
  extern struct RULE *rule_list;
         struct RULE *rule_ptr,
                     *curr_rule;
  extern struct PREM *prem_ptr;
  extern struct CON  *con_ptr;
                int  numb,
                     cert;

  rule_ptr = (struct RULE*) malloc (sizeof (struct RULE) );
  curr_rule = rule_list;
  if(rule_list == NULL)
       rule_list = rule_ptr;
    else
       while (1)
         {
           if (curr_rule->next == NULL)
              {
                curr_rule->next = rule_ptr;
                break;
              }
           curr_rule = curr_rule->next;
         }
  rule_ptr->numb = nmb;
  rule_ptr->cert = r_cert;
  rule_ptr->used = 0 ;
  rule_ptr->prem = NULL;
  rule_ptr->con  = NULL;
  rule_ptr->next = NULL;

  return rule_ptr;
 }
 /*End of AddRule  */
/* --------------------------------------------------------------------- */
