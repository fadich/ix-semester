/*                                         28.09.98
*/
#include "recogn3.h"

void assert_oldp (x,y)
      int  x,y;
{
	       extern int  pos;
  extern struct oldpoints  oldp[];

  if (pos==MAX)
    {
      printf("point database full\n");
      return ;
    }
  if (find(x,y)) return; /* already in db */
  oldp[pos].x=x;
  oldp[pos].y=y;
  pos++;
}

