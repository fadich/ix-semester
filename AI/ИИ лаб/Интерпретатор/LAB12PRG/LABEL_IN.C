/* label_init.c              IBM           13.03.95
H.Schildt interpreter for student studing
*/
#include "schildt.dfn"
#include "schildt.h2"

void label_init()
{
  extern struct label  label_table[];
   register int t;
   
   for (t=0; t<NUM_LAB; ++t)
       label_table[t].name[0] = '\0';
}
/* label_init ----------------------------------------------- */
