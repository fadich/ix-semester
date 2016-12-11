/* schildt.h             IBM 386        24.02.95
*/
#include <stdio.h>
#include <stdlib.h>
#include "schildt.dfn"

int variables[26]=
  {
   0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0
  };

char *prog,
      token[80],
      token_type,
      tok,
      *gstack[SUB_NEST];

struct commands
 {
  char command[20],
        tok;
 }table[]=
   { "print",PRINT,
     "input",INPUT,
     "if",IF,
     "then",THEN,
     "goto",GOTO,
     "for",FOR,
     "next",NEXT,
     "to",TO,
     "gosub",GOSUB,
     "return",RETURN,
     "end",END,
     "",END
   };

struct label
 {
  char name[LAB_LEN],
       *p;
 } label_table[NUM_LAB];

struct for_stack
 {
  int var,
      target;
  char *loc;
 } fstack [FOR_NEST];   /*stack for cycle FOR/NEXT */

int ftos, /*index of stack FOR beginning */
    gtos; /*index of stack GOSUB beginning */
