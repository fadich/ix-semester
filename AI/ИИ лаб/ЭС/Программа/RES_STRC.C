/* Res_Strc.c                 IBM            17.10.97
CADSHELL complex
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expert.h"

char Res_Strc(fn)
   char *fn;
{
                 FILE *pf;
          extern FILE *prtcl;
          extern char debug, DEBG[], EMPT[];
   extern struct LIST *res;  /* T_Infer.c  */
          struct LIST *r, *curr_r;
                 char str[80], *n, s, i;

  printf("\nRes_Strc: (%s).",fn);
  strcpy(str,fn);
  strcat(str,".res");
  if (( pf = fopen(str,"r")) == NULL)
     {  printf("\nFile of the result structure list \"%s\" isn't open");
        getch();
        return 1;
     }
  printf("   Processing of \"%s\"", str);
  res = curr_r = NULL;
  while (1)
    {
      if (feof(pf)) break;
      for (i=0; i<80; )
        {
          s = fgetc(pf);
          if ((s>='A' && s<='Z') ||
              (s>='a' && s<='z') ||
              (s>='€' && s<='Ÿ') ||
              (s>=' ' && s<='ï') ||
              (s>='0' && s<='9') ||
               s == '_')
                {      str[i++] = s;
               /*  printf("\n --(%c) str[%d]=%c", s, i-1, str[i-1]);*/}
            else break;
        }
      if (!i) continue;
      str[i] = '\0';
      r = (struct LIST *) malloc (sizeof (struct LIST) );
      n = malloc (strlen(str) + 1);
      strcpy (n, str);
      r->elem =  (void *) n;
      r->next = NULL;
      if (res)   curr_r->next = r;
         else    res = r;
      curr_r = r;
    }
  r = res;
  printf("\nRes_Strc: stack of result, address is %X",res);
  if (debug) fprintf(prtcl,
         "\nRes_Strc: stack of result, address is %X",res);
  while (r)
    {
      if (debug) fprintf(prtcl,
             "\n   --< %X (%X) \"%s\" >", r, r->elem, r->elem);
      printf("\n   --< %X (%X) \"%s\" >", r, r->elem, r->elem);
      r = r->next;
     }
  fclose (pf);
  return 0;
}
/* Res_Strc.c ----------------------------------------------------------- */
