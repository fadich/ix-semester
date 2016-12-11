/* place facts into flight db        19.11.98
*/
#include <stdio.h>
#include <string.h>
#include "search.h"

 void assert_flight (from, to, dist)
	       char  *from, *to;
		int  dist;
{
       extern int  f_pos;
 extern struct FL  flight[];

  if (f_pos < MAX)
  { 
     strcpy (flight[f_pos].from, from);
     strcpy (flight[f_pos].to, to);
     flight[f_pos].distance = dist;
     flight[f_pos].skip = 0;
     f_pos++;
  }
  else printf("Flight database full.\n");
  return;
}
