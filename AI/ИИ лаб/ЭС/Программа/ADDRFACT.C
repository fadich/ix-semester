/* AddrFact.c                IBM             20.10.97
     CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "expert.h"

void AddrFact()
{
           extern FILE *prtcl;
  extern struct OBJECT *obj_list;
         struct OBJECT *ob;
          struct VALUE *val;
           struct LIST *lst;
           struct RULE *r;
                  char str[80], i;

  fprintf(prtcl,"\nAddrFact: address of objects list is %X",
                obj_list);
  ob = obj_list;
  while( ob )
   {
     if (ob->question) strcpy (str, ob->question);
                 else  str[0] = '\0';
     fprintf(prtcl,"\nObj:<%s>, addr:%X",ob->name, ob);
     fprintf(prtcl,"\n    Q:(<%s>,%X)", str, ob->question);
     fprintf(prtcl," val=<%X>, next:<%X>", ob->value, ob->next);
     val = ob->value;
     while ( val )
       {
     fprintf(prtcl,"\n     value:(<%s>, %X)", val->name, val);
     fprintf(prtcl,"  prem:<%X>, con:<%X>, next:<%X>\n",
            val->prem, val->con, val->next);
	 lst = val->prem;  i=0;
	 while (lst)
	   {
	     r = ( struct RULE *) lst->elem;  i++;
         fprintf(prtcl," <rule_prem(%d)>", r->numb);
         if (i>2) { fprintf(prtcl,"\n   ");  i=0;}
	     lst = lst->next;
	    }
     lst = val->con;  i=0;  fprintf(prtcl,"\n    ");
	 while (lst)
	   {
	     r = ( struct RULE *) lst->elem;    i++;
         fprintf(prtcl," <rule_con(%d)>", r->numb);
	 if (i>2) { fprintf(prtcl,"\n   "); i=0;}
	     lst = lst->next;
           }
         val = val->next;
       }
     ob = ob->next;
   }
} /* end of AddrObj.c
----------------------------------------------------------------------
*/
