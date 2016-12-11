/* given from, find anywhere farthest away      19.11.98
Hill-Climbing Search
*/
#include <string.h>
#include "search.h"

int find (from, anywhere)
    char *from, *anywhere;
{
extern struct FL  flight[];
      extern int  find_pos, f_pos;
             int  pos, dist;

   pos = dist = 0;
   find_pos = 0;
   while (find_pos < f_pos)
     {
      if (!strcmp (flight[find_pos].from,from) &&
	  !flight[find_pos].skip)
        {
          if (flight[find_pos].distance > dist)
            { pos = find_pos;
              dist = flight[find_pos].distance;
            }
        } 
      find_pos++;
     } 
   if (pos)
     {
       strcpy (anywhere, flight[pos].to);
       flight[pos].skip = 1;  /* make active */
       return  flight[pos].distance;
     }
   return 0;
}
