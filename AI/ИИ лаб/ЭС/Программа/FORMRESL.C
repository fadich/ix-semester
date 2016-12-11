/* FormReslt.c                IBM                 27.03.95
CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expert.h"

void FormReslt()
{
   extern struct LIST *res;  /* T_Infer.c  */
          struct LIST *r;
                 char str[80], *n, s;

  res = NULL;
  while (1)
    {
      puts("\nEnter a name of a result member:");
      gets (str);
      r = (struct LIST *) malloc (sizeof (struct LIST) );
      n = malloc (strlen(str) + 1);
      strcpy(n, str);
      r->elem =  (void *) n;
      r->next = res;
      res = r;
      printf("\nFormRes: res=%X, <%s>  next=%X", res, res->elem,
                      res->next);
      puts("Press NL for continue");
      str[0] = getchar();
      if (str[0] != 10) break;
    }
  getch();
  r = res;
  printf("\nFormReslt: stack of resutl, address is %X",res);
  while (r)
    {
      printf(" <%X (%X) (%s) >", r, r->elem, r->elem);
      r = r->next;
     }
  return;
}
/* FormReslt.c ---------------------------------------------------------- */
