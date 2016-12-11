/* Result.c                 IBM             17.10.97
  CADSHELL complex
*/
#include <stdio.h>
#include "expert.h"

void  Result ()
{
         extern FILE *prtcl;
         extern char protocol, debug, EMPT[];
  extern struct LIST *res;
         struct LIST *r;
       struct OBJECT *ob;
        struct VALUE *v;
                char main_val[80], vcf;

  printf("\nRESULT:");
  if (protocol) fprintf(prtcl, "\nRESULT:");
  r = res;
  while ( r )
    {
      if (FindObj ( r->elem, &ob))
        {
          if (debug) fprintf(prtcl, "\nOBJECT: %s ", ob->name);
          v = ob->value;  vcf = 0;  main_val[0] = '\0';
          while (v)
            {
              if (debug) fprintf(prtcl,"\n%s VAL: %s, cf=%d",
                         EMPT, v->name, v->cert);
              if (v->cert > vcf)
                 {  vcf = v->cert;
                    strcpy(main_val, v->name);
                 }
              v = v->next;
            }
          if (vcf > 10)
            { printf("\n%s = %s, cf = %d", ob->name, main_val, vcf);
              if (protocol) fprintf(prtcl, "\n%s %s = %s, cf = %d",
                    EMPT, ob->name, main_val, vcf);
            }
            else
              { printf("\n%s = undefined;", ob->name);
                if (protocol) fprintf(prtcl, "\n%s %s = undefined",
                              EMPT, ob->name);
              }
        }
      r = r->next;
    }
  return;
}
/* Result.c ------------------------------------------------------ */
