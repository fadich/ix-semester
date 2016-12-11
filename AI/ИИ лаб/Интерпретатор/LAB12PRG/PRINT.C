/* print.c              IBM             19.03.1995
H.Schildt interpreter for student studing
Format: PRINT  <list_of_arguments>
*/
#include <conio.h>
#include <string.h>
#include "schildt.dfn"

void print()
{
  extern char  token[],
	       token_type,
	       tok;
	  int  answer,
	       len , spaces;
	 char  last_delim;
   
 len = 0;
 do
   {
     get_token(); /* get next list element */
     if (tok == EOL || tok == FINISHED) break;
     if (token_type == QUOTE)
	{ /* this is a string constant */
	  cprintf ("%s", token);
	  len += strlen(token);
	  get_token();
        }
       else
        { /* this is an expression */
          putback();
	  get_exp (&answer);
	  get_token();
	  cprintf("%d",answer);
	}
      last_delim = *token;
      if (*token == ';')
	{ /*calculating of number of blanks for tabulation */
	  spaces = 8 - (len %8);
	  len += spaces; /* drifting for one tabulation */
	  while (spaces)
            {
	      cprintf(" ");
	      spaces--;
            }
       }
       else
          if (*token == ','); /* nothing do */
             else
	       if (tok != EOL && tok != FINISHED) serror(0,"print");
    } while (*token == ';' || *token == ',');
 if (tok == EOL || tok == FINISHED)
    {
      if (last_delim != ';' && last_delim != ',') cprintf ("\n\r");
    }
    else
      { cprintf("\nprint:"); serror (0,"print"); /* delimiter is absent */
      }
}
