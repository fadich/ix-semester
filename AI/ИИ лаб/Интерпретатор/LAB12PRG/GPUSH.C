/*gpush.c             IBM            19.03.1995
H.Schildt interpreter for student studing
*/
#include "schildt.dfn"

void gpush(s)
     char *s;
{
    extern int  gtos;
   extern char  *gstack[];

   gtos++;
   if (gtos == SUB_NEST)
     {
       serror(12,"gpush");
       return;
     }
   gstack[gtos] = s;
}
/*-------------------------------------------------------*/
