/* T_Infer.c            IBM              20.10.97
CADSHELL complex: test for inference engine
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expert.h"

         FILE  *prtcl, *debfile;
struct OBJECT  *obj_list = NULL;
  struct RULE  *rule_list = NULL;
  struct LIST  *res = NULL;
 struct STACK  *stack_ptr = NULL;
         char  g[40],
               i,
               USER[] = "USER:",
               SYST[] = "SYST:",
               EXPL[] = "EXPL:",
               EMPT[] = "     ",
               DEBG[] = "DEBG:",
               protocol=0, /* 1 - protocol is needed, 0 - work without it */
               explan = 0, /* 1 - explanation is needed, otherwise 0 */
               step = 0,   /* 1 - step by step moving, 0 - without stops */
               debug = 0;  /* 1 - make debuggin protocol */

void main (argc, argv)
     int argc;
    char *argv[];
{
    char var[4];

  mkwnd (1, 1, 80, 25, YELLOW, BLUE);
  if (argc < 2)
     { cprintf("Use format: pgn ES_name [optins: -prot -expl -step -deb]");
       exit(1);
     }
  cprintf("\n\r");
  for (i=2; i<=argc; i++)
    {
      if (!strcmp(argv[i], "-prot")) protocol = 1;
      if (!strcmp(argv[i], "-expl")) explan = 1;
      if (!strcmp(argv[i], "-step")) step = 1;
      if (!strcmp(argv[i], "-dall")) { debug = 2; explan = 1;
                                         step = 1; protocol = 1; }
      if (!strcmp(argv[i], "-deb")) { debug = 1; explan = 1;
                                      step = 1; protocol =1; }
    }
  if (debug == 2)
     { g[0] = '\0';  strcpy (g, argv[1]);
       strcat (g, ".deb");
       if ((debfile = fopen (g, "w+b")) == NULL)
         { printf("\nFile \"%s\" isn't opened for writing",g);
           getch(); exit(1);
	 }
     }
  if (TextFact(argv[1])) goto label_fact;
  if (TextRule(argv[1])) goto label_rule;
  if (debug == 2) free (debfile);
  cprintf("\n\rFacts and Rules are read");
do{
  if (protocol)
    {
      cprintf("\n\rEnter of your number,please.");
      g[0] = var[0] = '\0';
      gets (var);
      strcpy (g, argv[1]);
      strcat (g, var);
      strcat (g, ".ptc");
      if ((prtcl = fopen (g, "w+b")) == NULL)
         {
	   cprintf("\n\rFile \"%s\" isn't opened for writing", g);
	   getch();  exit(1);
	 }
     else { cprintf("\n\rFile \"%s\" is opened  for protocol", g);
            if (debug) fprintf(prtcl,
              "\nFile \"%s\" is opened for protocol", g);
          }
    }
  if (debug)
     { cprintf("\n\rWill you get addresses? (y/n)");
       if (getch() == 'y')
          { AddrFact();
            AddrRule();
          }
     }
  if (!Res_Strc(argv[1]))
      { BackWard();
        Result();
      }
  Clearing();
  fclose(prtcl);
  cprintf("\n\rWill you try again? (y/n)");
  }while (getche() == 'y');
  RuleFree();
label_rule:
  ObjFree();
label_fact:
   getch();
  return;
}
