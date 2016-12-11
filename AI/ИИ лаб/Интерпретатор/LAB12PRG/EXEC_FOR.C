/*  exec_for.c                 IBM           19.03.95
   H.Schildt interpreter for student studing
*/
#include <ctype.h>
#include "schildt.h2"
#include "schildt.dfn"

void exec_for()
{
	extern int  variables[];
       extern char  token[],
		    tok, *prog;
  struct for_stack  i;
	       int  value;

  get_token();
  if (!isalpha (token[0]))
      {
        serror (4,"exec_for");
        return;
      }
  i.var = toupper (token[0]) - 'A';
  get_token();
  if (token[0] != '=')
      {
        serror(3,"exec_for");
        return;
      }
  get_exp (&value);
  variables[i.var] = value;
  get_token();
  if (tok != TO ) serror(9,"exec_for");
  get_exp (&i.target);
  if (value >= variables[i.var])
      {
	i.loc = prog;
	if (fpush (i)) return;
      }
     else
        {
         while (tok != NEXT) get_token();
        }
  }
/*   exec_for----------------------------------------------------------*/
