/* AddrRule.c             IBM            20.10.97
CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

void AddrRule()
{
         extern FILE  *prtcl;
       struct OBJECT  *ob;
        struct VALUE  *val;
  extern struct RULE  *rule_list;
         struct RULE  *rul;
         struct PREM  *prem;
          struct CON  *con;

  rul = rule_list;
  while ( rul )    /* rule cycle   */
    {
      fprintf(prtcl,"\nRule: (%d), addr=%X", rul->numb, &rul);
      fprintf(prtcl," prem:<%X>, con:<%X>, next:<%X>", rul->prem,
	       rul->con, rul->next);
      prem = rul->prem;
      while ( prem )        /* prem cycle   */
        {
          ob = prem->obj;
          val = prem->value;
      fprintf(prtcl,"\n    Prem:<%X>, %s = %s", prem,
                     ob->name, val->name);
      fprintf(prtcl,"  next:<%X>", prem->next);
	  prem = prem->next;
	}
      con = rul->con;
      while ( con )           /* con cycle */
        {
          ob = con->obj;
          val = con->value;
      fprintf(prtcl,"\n    Con:<%X>, %s = %s", con,
                     ob->name, val->name);
      fprintf(prtcl,"  next:<%X>", con->next);
	  con = con->next;
	}
      rul = rul->next;
    }
} /* end of PGM  */
/* AddrRule ---------------------------------------------------------------*/
