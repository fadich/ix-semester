/* assignment.c           IBM 386            19.03.95
H.Schildt interpreter for student studing
 Format: <name of variable>=<expression>
 */
#include <conio.h>
#include <ctype.h>

void assignment()
{
	int  var, value;
 extern int  variables[];
extern char  token[];

  get_token(); /*get variable name*/
  if (! isalpha (token[0]))
  {
   serror(4,"assignment"); /*this is not variable*/
   return;
  }
  var = toupper(*token) - 'A'; /*var is a index of variable */
  get_token(); /* reading of symbol '=' */
  if (*token != '=')
     {
      serror(3,"assignment");
      return;
     }
  get_exp (&value); /*getting of variable value */
  variables [var] = value; /*assignment */
 }
/* assignment------------------------------------------------*/
