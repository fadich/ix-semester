/*                                        20.09.98
*/
#include "recogn3.h"

int find(x,y)
    int x,y;
{
	   register int  t;
	     extern int  pos;
extern struct oldpoints  oldp[];

   for (t=0; t<pos; t++)
      if( oldp[t].x==x && oldp[t].y==y) return 1;

   return 0;
}
