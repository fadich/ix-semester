/*Stack.c               IBM                  15.10.97
 CADSHELL complex
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "expert.h"

void InStack (g)
     struct OBJECT  *g;
{
 extern struct STACK  *stack_ptr;
        struct STACK  *s;
       struct OBJECT  *o;
         extern char  debug, DEBG[], EMPT[];
         extern FILE  *prtcl;

 if (debug) fprintf(prtcl,"\n--< InStack >--ptr=%X", stack_ptr);
  s = stack_ptr;
  while (s)
    {
      o = s->goal;
      if (o == g)
     { cprintf("\n\rGoal: \"%s\" is present in the stack.", g->name);
           if (debug)  fprintf(prtcl,
                   "\nGoal: \"%s\" is present in the stack.", g->name);
	   return;
	 }
      s = s->next;
    }
  s = (struct STACK *) malloc (sizeof (struct STACK) );
  s->goal = g;
  s->next = stack_ptr;
  stack_ptr = s;
  if (debug) fprintf(prtcl,
           " --stack: %X, next=%X", stack_ptr, s->next);
 return;
}
/* ---------------------------------------------------------------*/
struct OBJECT *
    OutStack()
{
  extern struct STACK  *stack_ptr;
         struct STACK  *s;
        struct OBJECT  *o;
          extern FILE  *prtcl;
          extern char  debug, DEBG[], EMPT[];

  s = stack_ptr;
  if (debug)
    { o = s->goal;
      fprintf(prtcl,"\n--< OutStack >-- s=%X<%s>, s->next=%X",
		 s, o->name, s->next);
    }
  if (s)
     {   stack_ptr = s->next;
         free (s);
     }
  if (stack_ptr)  return (stack_ptr->goal);
                  return (NULL);
}
/* ------------------------------------------------------------ */
void SeeStack()
{
          extern FILE  *prtcl;
          extern char  debug, DEBG[], EMPT[];
  extern struct STACK  *stack_ptr;
         struct STACK  *s;
        struct OBJECT  *o;
                  int  i;

  s = stack_ptr;
  i = 0;
  printf("\nSeeStack:  Stack is ");
  if (debug) fprintf (prtcl, "\nSeeStack: Stack is ");
  if (! s) { puts("empty");
             if (debug) fprintf (prtcl, "empty");
           }
     else
        while (s)
          {
            o = s->goal;
            printf("\n\r   i=%2d<%s>", i++, o->name);
            if (debug) fprintf(prtcl,"\n    i=%2d<%s>", i, o->name);
            s = s->next;
          }
  return;
}
/* Stack.c --------------------------------------------------- */
