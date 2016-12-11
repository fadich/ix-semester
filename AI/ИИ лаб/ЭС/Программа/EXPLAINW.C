/* ExplainWhy.c                 IBM              27.03.95
*/
#include <stdio.h>
#include "expert.h"

void ExplainWhy (ob)
     struct OBJECT  *ob;
{
   extern FILE  *prtcl;
   extern char  EXPL[], EMPT[],
                protocol;

  printf("\n%s There is not a rule for getting value of \"%s\"",
           EXPL, ob->name);
  printf("\n%s that is why it needs to be asked.", EMPT);
  if (protocol)
     {
       fprintf(prtcl,
         "\n%s There is not a rule for getting value of \"%s\"",
            EXPL, ob->name);
       fprintf(prtcl,
         "\n%s that is why it needs to be asked.", EMPT);
     }
}
/*ExplainWhy.c ---------------------------------------------------------*/
