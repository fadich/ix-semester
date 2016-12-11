/* SeeRule.c                 IBM                10.04.95
CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

void SeeRule(rule_ptr)
   struct RULE *rule_ptr;
{
    struct OBJECT  *c_obj;
     struct VALUE  *c_val;
      struct PREM  *curr_prem;
       struct CON  *curr_con;

  while (rule_ptr )
    {
      curr_prem = rule_ptr->prem;
      curr_con = rule_ptr->con;
      cprintf("\n\rRULE (%d) factor=%d",
		rule_ptr->numb, rule_ptr->cert);
      cputs("\n\rIF");
      while (curr_prem )
         {
           c_obj = curr_prem->obj;
           c_val = curr_prem->value;
	   cprintf("  %s = %s", c_obj->name, c_val->name);
	   if (curr_prem->next != NULL)   cputs(" and");
		else                      cputs(", ");
	   curr_prem = curr_prem->next;    
	 }
      cputs("THEN");
      while (curr_con )
         {
           c_obj = curr_con->obj;
           c_val = curr_con->value;
	   cprintf("  %s = %s, cf=%d", c_obj->name,
		  c_val->name, curr_con->cert);
	   if (curr_con->next )  cputs(" and");
		else             cputs(". ");
	   curr_con = curr_con->next;
	 }
      rule_ptr = rule_ptr->next;
      cputs("Press \"Enter\" for continue.");
      if (getch() != 13) break;
    }
}   /* end of PGM   */
/* SeeRule --------------------------------------------------------------*/
