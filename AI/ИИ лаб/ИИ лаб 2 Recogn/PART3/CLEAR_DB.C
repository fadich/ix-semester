/*                                     28.09.98
*/
#include "recogn3.h"

void clear_db()
{
	    register int  t;
	      extern int  pos;
 extern struct oldpoints  oldp[];

   for (t=0; t<MAX; t++)   oldp[t].x = oldp[t].y= 0;
}

