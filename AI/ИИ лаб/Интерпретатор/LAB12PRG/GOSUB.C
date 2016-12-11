/*gosub.c           IBM           19.03.1995
H.Schildt interpreter for student studing
*/
#include "schildt.h2"

void gosub()
{
	char  *loc;
 extern char  *prog,
	      token[];

   get_token();
   loc = find_label (token);
   if (loc == '\0')
      serror (7,"gosub");
     else
      {
       gpush (prog);
       prog = loc;
      }
}
/*-------------------------------------------------------*/
