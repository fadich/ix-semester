/* input.c               IBM            19.03.1995
H.Schildt interpreter for student studind
Format : INPUT <name_of_variable>  or
         INPUT "<string constant>" <name_of_variable>
*/
#include <conio.h>
#include "schildt.dfn"
#include <ctype.h>

void input()
{
 extern char  token_type,
	      token[];
  extern int  variables[];
	char  str[80], var;
	 int  i;

   get_token(); /* checking for string constant */
   if (token_type == QUOTE)
     {
       cprintf("\n\r%s ",token);
       get_token();
       if (*token != ',') serror (1,"input");
       get_token();
     }
     else
       cprintf("\n\r? ");
   var = toupper(*token)-'A'; /* calculating of var.name index */
   cscanf("%d",&i); getch();/* input reading */
   cprintf("\n\r");
   variables[var] = i; /* variable value saving */
}
/* input.c ------------------------------------------------------------ */
