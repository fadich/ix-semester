/* get_exmp.c                      07.09.98
       input description
    */
#include <stdio.h>
#include <string.h>
#include "ml.h"

  get_example (n, v, o)
      char *n, *v, *o;
{
    extern struct attr  may[],must[];
            extern int  may_pos,must_pos;
           extern FILE  *prtcl;

    printf("\n subject: ");
    gets(n);
    if (!*n) strcpy(n, "<NL>");
    fprintf (prtcl, "\n subject: %s", n);
    if (n[0] == '<') return 0;
    printf("    verb: ");
    gets(v);
    printf ("  object: ");
    gets(o);
    fprintf (prtcl,"\n    verb: %s\n  object: %s", v, o);
    return 1;
 }




 
