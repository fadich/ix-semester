/* Optimal solution using 
   least-cost with Path-Removal
  Depth-first search                          23.11.98
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
int stos=0;    /* top of solution stack */    
struct stack bt_stack[MAX]; /* backtracking stack */
struct stack solution[MAX]; /* hold temporary solution */

void main()
{
   char  from[20],to[20];
    int  t,d;

   setup();
   printf ("from? ");
   gets (from);
   printf("to? ");
   gets (to);
   do
    { isflight (from, to);
      d = route (to);
      tos = 0; /* reset the backtrack stack */
    } while (d != 0); /* while still finding solusions */
   t = 0;
   printf ("\nOptimal solution is:\n");
   while (t < stos)
     { printf ("%s to ", solution[t].from);
       d += solution[t].dist;
       t++;
     }
   printf("%s\n", to);
   printf("distance is %d\n", d);
   getch();
   return;
}
