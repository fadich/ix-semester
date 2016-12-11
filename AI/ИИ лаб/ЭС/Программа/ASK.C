/* Ask.c                IBM              17.10.97
  CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

void Ask (ob)
    struct OBJECT  *ob;
{
   extern FILE *prtcl;
   extern char  SYST[], USER[], EMPT[], debug, protocol, explan;
   struct VALUE *v;
	   char strng[40], s[240];
	    int  numb, i;

  s[0] = '\0';
/*cprintf("\n\rAsk: ob=%X  %s, ptc=%d\n", ob,SYST,protocol);
*/if (ob->question)
       { cprintf("\n\r%s?", ob->question);
     if (protocol) fprintf(prtcl,"\n%s %s?", SYST, ob->question);
       }
     else
       { cprintf("\n\rWhat is the value of \"%s\"?", ob->name);
	 if (protocol)  fprintf(prtcl,
        "\n%s What is the value of \"%s\"?", SYST, ob->name);
       }
  v = ob->value; i = 0;
  if (!v)
    { cputs(" Enter a name:");
      if (protocol) fprintf(prtcl, "\n%s Enter a name:", SYST);
      gets (strng);
      if (protocol) fprintf(prtcl, "\n%s %s", USER, strng);
      v = (struct VALUE *) AddValue(ob, strng);
      v->cert = 100;
      goto label;
    }
  while (v)
    {
      if (protocol) fprintf(prtcl, "\n%s%d) %s", EMPT, i, v->name);
      cprintf("\n\r%d) %s", i++, v->name);
      v = v->next;
    }
  cputs("\n\rPlease enter a corresponding number");
  if (protocol) fprintf(prtcl,
     "\n%sPlease enter a corresponding number", EMPT);
  cscanf("%d", &numb);
  if (protocol) fprintf(prtcl, "\n%s  %d", USER, numb);
  v = ob->value;
  for (i=0; v; i++)
    {
      if ( i == numb )
        {
          v->cert = 100;
          break;
        }
      v = v->next;
    }
  label:
  if (debug) fprintf(prtcl, "\n Ask: %s = %s (%d)", ob->name,
                            v->name, v->cert);
  if (explan) ExplainWhy (ob);
  return;
}
/* Ask.c -------------------------------------------------------- */

