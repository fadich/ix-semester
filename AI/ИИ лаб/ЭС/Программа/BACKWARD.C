/* BackWard.c                     IBM             15.10.97
CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

void BackWard()
{
    extern FILE  *prtcl;
    extern char  step, protocol, debug,
                 SYST[], USER[];
  struct OBJECT  *goal;
   struct VALUE  *val_ptr;
    struct RULE  *curr_rule;
           char  goal_name[40], s;
            int  cf, val_cf, rul_cf;

  cputs("\n\rEnter a goal, please:");
  gets (goal_name);
  if (protocol)
     fprintf(prtcl, "\n%s Enter a goal, please.\n%s %s",
         SYST, USER, goal_name);
  if ( !FindObj (goal_name, &goal) )
	AddObj(&goal, goal_name);
  cprintf("\n\rThe goal is \"%s\" <%X>", goal->name, goal);
  if (!goal) return;
  InStack (goal);
  while (goal)
    {
      if (step) { SeeStack();  s = getch();
		   if (s == 27) { getch(); return; } }
      val_ptr = goal->value;
      val_cf = 0;
      while (val_ptr)
        {
          if (val_ptr->cert > val_cf)
              val_cf = val_ptr->cert;
          val_ptr = val_ptr->next;
        }
      if ( val_cf < 100)
        {
	  curr_rule = (struct RULE *) FindRule (goal);
	  if (curr_rule)
	    {
	      rul_cf = TestRule (curr_rule, &goal);
          if (debug)
             fprintf(prtcl,"\n TestRule: rul_cf=%d", rul_cf);
	      if (rul_cf<0) continue;
	      if (rul_cf) Conclude (curr_rule, rul_cf);
		 else     InStack(goal);
	    }
	    else
	     { if ( ! val_cf )
		   Ask (goal);
	       goal = (struct OBJECT *) OutStack();
	     }
	}
	else
	    goal = (struct OBJECT *) OutStack();
    }     /*  end of while(goal)  */
}
/* BackWard -----------------------------------------------------------*/
