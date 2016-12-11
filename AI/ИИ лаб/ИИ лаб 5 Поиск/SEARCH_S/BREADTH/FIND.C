/* given from, find anywhere          16.11.98
*/
#include <string.h>
#include "search.h"

int find (from, anywhere)
    char *from, *anywhere;
{
extern struct FL  flight[];
      extern int  find_pos, f_pos;

   find_pos=0;
   while (find_pos < f_pos)
     {
      if (!strcmp (flight[find_pos].from,from) &&
	  !flight[find_pos].skip)
        {
	  strcpy (anywhere, flight[find_pos].to);
	  flight[find_pos].skip = 1;  /* make active */
	  return  flight[find_pos].distance;
        }
      find_pos++;
   }
   return 0;
}
