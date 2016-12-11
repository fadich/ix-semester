/* display.c                             07.09.98
   */
#include <stdio.h>
#include "ml.h"

    display( )
{
	extern FILE  *prtcl;
 extern struct attr  may[], must[];
	 extern int  may_pos, must_pos;
		int  t;

  printf ("\n\nDisplay of description:\n\n May have :");
  fputs  ("\n\nDisplay of description:\n", prtcl);
  fputs  ("-----------------------\n May have :", prtcl);
  for (t=0; t < may_pos; t++)
    {
      if (may[t].active)
       { printf ("\n %s %s %s", may[t].subject,
		     may[t].verb,may[t].object);
	     fprintf (prtcl, "\n %s %s %s",may[t].subject,
		      may[t].verb,may[t].object);
       }
    }
  printf("\n\n Must have :");
  fputs("\n\n Must have:", prtcl);
  for (t=0; t<must_pos; t++)
    {
      printf("\n %s %s %s", must[t].subject,must[t].verb,
             must[t].object);
      fprintf (prtcl, "\n %s %s %s", must[t].subject,
              must[t].verb, must[t].object);
    }
    return;
}

