/* Finding multiple solutions by Path-Removal
  Depth-first search                          05.12.98
*/
#include <conio.h>
#include <stdio.h>
#include "search.h"

void isflight (char *, char *);
int route (char *);
void setup (void);

struct FL flight[MAX]; /* array of db structures */
int f_pos=0;           /* number of entries in flight db */
int find_pos=0;        /* index for searching flight db */
int tos=0;             /* top of stack */
struct stack bt_stack[MAX]; /* backtracking stack */

void main()
{
   char from[20],to[20];
    int dist;

   setup();
   printf ("from? ");
   gets (from);
   printf("to? ");
   gets (to);
   do
    { isflight (from, to);
      dist = route (to);
      if (!dist) break;
      tos = 0; /* reset the backtrack stack */
    } while (getche() != 'q');
   getch();
   return;
}
