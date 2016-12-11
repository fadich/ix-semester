/* get_token.c             IBM-386          19.03.95
  H.Schildt interpreter for student studing
 */
#include <ctype.h>
#include <process.h>
#include "schildt.dfn"

 get_token()
 {
     register char  *temp; /*pointer for work with token[] */
       extern char  token[],
                    *prog,
                    tok, token_type;

  token_type = 0;   tok = 0;
  while(1) {
  temp = token;  /* now temp points at the beginning of the token[]*/
  if (*prog == '\0') /*End of source program text is reached */
   {
     *token = 0;
     tok = FINISHED;
     token_type = DELIMITER;
     break;
   }
  while (iswhite (*prog))  ++prog;   /*blanks deletion */
  if ((*prog == '\n') || (*prog == '\r'))  /*line advance */
    {
      token[0] = *prog;
      token[1] = 0;
      ++prog;
      if ((*prog == '\r') || (*prog == '\n'))
         { token[1] = *prog;  ++prog;  token[2] = 0;
         }
      tok = EOL;
      token_type = DELIMITER;
      break;
    }
  if (strchr("+-*/%=;(),><", *prog))
    { /* current symbol is a delimiter of above enumerated sort,
         one of string's symbols */
      *temp = *prog;  /* the symbol is put down to the first position of
                       token[] */
      prog++;
      temp++;
      *temp = 0;
      token_type = DELIMITER;
      break;
    }
  if (*prog == '"') /* string constant   */
    {
      prog++;
      while (*prog != '"' && *prog != '\r' && *prog != '\n')
         *temp++ = *prog++; /*putting string down to the token() */
      if ((*prog == '\r') || (*prog == '\n'))  serror(1,"get_token");
      prog++;
      *temp = 0;
      token_type = QUOTE;
      break;
    }
  if (isdigit(*prog))
    {
      /* current symbol is digit therefore the token is number */
      while(!isdelim (*prog))
         *temp++ = *prog++; /*putting digit string down to the token[]*/
      *temp = '\0';
      token_type = NUMBER;
      break;
    }
  if (isalpha (*prog))
    {
  /*current symbol is letter therefore the token is variable or command*/
      while (!isdelim (*prog))
         *temp++ = *prog++;
      token_type = STRING;
    }
  *temp = '\0';
  if (token_type == STRING)
    {
      tok = look_up (token);
      if (!tok) token_type = VARIABLE;
          else  token_type = COMMAND;
    }
  break;
  } /* end of while  */
return;
}
/*-get_token()-----------------------------------------------------------*/
