/*   find_label.c          IBM        19.03.1995
*/
#include <string.h>
#include "schildt.dfn"
#include "schildt.h2"

  char * find_label (s)
    char *s;
  {
  extern struct label  label_table[];
	     register  int t;

    for (t=0; t < NUM_LAB; ++t)
      if ( ! strcmp (label_table [t].name, s))
		   return label_table [t].p;
    return '\0';
  }
 /*find_label----------------------------------------------------------------*/
