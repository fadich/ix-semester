 /*look_up.c           IBM         13.03.1995
 H.Schildt interpreter for student studing
 */
#include <string.h>
#include <ctype.h>
#include "schildt.h2"

  look_up(s)
     char *s;
 {
    extern struct commands   table[];
	      register int   i,j;
		      char   *p;
  p = s;
  while (*p)
   {
    *p = tolower (*p);
     p++;
   }
  for (i=0; *table[i].command; i++)
      if(! strcmp(table[i].command, s))
           return table[i].tok;
  return 0;
 }
/*------------------------------------------------------------*/
