/* remove an entry                   19.11.98
   from the database */
#include <string.h>
#include "search.h"

void retract(from,to)
    char *from, *to;
{
	     int  t;
extern struct FL  flight[];
      extern int  f_pos;

  for(t=0;t<f_pos;t++)
    if(!strcmp(flight[t].from,from) &&
       !strcmp(flight[t].to,to))  {
	  strcpy(flight[t].from,"");
	  return;
    }
  return;
}