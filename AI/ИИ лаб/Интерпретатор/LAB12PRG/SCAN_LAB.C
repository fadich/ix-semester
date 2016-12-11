/* scan_labels.c              IBM           19.03.95
H.Schildt interpreter for student studing
*/
#include "schildt.dfn"
#include "schildt.h2"
#include <string.h>

void scan_labels()
{
 extern struct label  label_table[];
	 extern char  *prog,  tok,
		      token[],
		      token_type;
	register int  loc;
		char  *temp;

   label_init();
   temp = prog;
   get_token();
   if (token_type == NUMBER)
     {
       strcpy (label_table[0].name, token);
       label_table[0].p = prog;
     }
   find_eol();
   do
     {
      get_token();
      if (token_type == NUMBER)
	{
	 loc = get_next_label(token);
	 if (loc == -1 || loc == -2)
	   {
	     (loc == -1) ? serror(5,"scan_labels") : serror(6,
                                    "scan_labels");
	   }
	 strcpy (label_table[loc].name, token);
	 label_table[loc].p = prog;
	}
      if (tok != EOL) find_eol();
     } while (tok != FINISHED);
   prog = temp;
}
/* scan_labels ---------------------------------------------- */
