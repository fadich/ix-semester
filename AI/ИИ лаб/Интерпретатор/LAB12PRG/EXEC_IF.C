/*exec_if.c             IBM 386        13.03.95
 H.Schildt interpreter for student studing
*/
#include <string.h>
#include "schildt.dfn"

void exec_if()
{
	int  x, y, cond;
       char  op;
extern char  token[], tok;

 get_exp(&x);   /*left expression*/
 get_token();   /*operater*/
 if (!strchr("=<>", token[0]))
   {
     serror(0,"exec_if");
     return;
   }
  op = token[0];
  get_exp(&y); /*right expression*/
  cond = 0;
  switch (op)
   {
     case '=':if(x == y) cond = 1;
              break;
     case '<':if(x < y) cond = 1;
              break;
     case '>':if(x > y) cond = 1;
              break;
    }
  if(cond)
    {
     get_token();
     if (tok != THEN)
       {
         serror(8,"exec_if");
         return;
       }
     }
   else
      find_eol();
 }
 /* exet_if--------------------------------------------------*/
