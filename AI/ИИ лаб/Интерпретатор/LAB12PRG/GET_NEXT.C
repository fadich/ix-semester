/* get_next_label.c        IBM          13.03.1995
*/
#include <string.h>
#include "schildt.h2"

get_next_label (s)
  char *s;
{
	 register int  t;
  extern struct label  label_table[];

  for (t=0; t < NUM_LAB; ++t)
  {
    if ( ! label_table [t].name[0] ) return t;
    if (!strcmp (label_table[t].name, s)) return (-2);
  }
 return(-1);
}
 /*get_next_lable------------------------------------------------------*/
