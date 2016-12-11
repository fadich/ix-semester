/*fpush.c             IBM 386        19.03.95
 H.Schildt interpreter for student studing
*/
#include "schildt.h2"

  void fpush (i)
   struct for_stack  i;
 {
 extern struct for_stack  fstack[];
	      extern int  ftos;

   if (ftos > FOR_NEST)
      serror(10,"fpush");
   fstack [ftos].var = i.var;
   fstack [ftos].target = i.target;
   fstack [ftos].loc = i.loc;
   ftos++;
 }
/*-----------------------------------------------------------*/
