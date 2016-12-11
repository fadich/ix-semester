/* reset the "skip" field i.e.,            19.11.98
   retractive all nodes */
#include "search.h"

void clearmarkers()
{
	     int  t;
extern struct FL  flight[];
      extern int  f_pos;

   for (t=0;t<f_pos;++t)
       flight[t].skip=0;
   return;
}