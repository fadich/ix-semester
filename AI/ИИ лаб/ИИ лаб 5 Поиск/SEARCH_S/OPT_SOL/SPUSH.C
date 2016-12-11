/* solution stack                 23.11.98
*/
#include <string.h>
#include <stdio.h>
#include "search.h"

void spush (from, to, dist)
     char  *from, *to;
      int  dist;
{
 extern struct stack  solution[];
          extern int  stos;

  if (stos < MAX)  
    {
     strcpy (solution[stos].from,from);
     strcpy (solution[stos].to,to);
     solution[stos].dist=dist;
     stos++;
    }
  else printf("Shortest distance stack full.\n");
}
