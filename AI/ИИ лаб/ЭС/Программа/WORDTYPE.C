/* WordType.c                C-UNIX                       26.03.93
   CADSHELL - complex
*/
#include <stdio.h>
#include <string.h>
#include "expert.h"

int WordType (wd)
   char *wd;
{
  switch (wd[0])
   {
     case 'R': if (!strcmp (wd, "RULE")) return 1;
               break;
     case 'П': if (!strncmp (wd, "ПРАВИЛО", 7) ||
                   !strncmp (wd, "Правило", 7))
                       return 1;
               break;
     case 'I': if (!strcmp (wd, "IF")) return 2;
               break;
     case 'Е': if (!strncmp (wd, "ЕСЛИ", 4) ||
                   !strncmp (wd, "Если", 4))
                       return 2;
               break;
     case 'c': if (!strcmp (wd, "cf")) return 3;
               break;
     case 'К':
     case 'к': if (!strncmp (wd, "КУ", 2) ||
                   !strncmp (wd, "ку", 2))
                       return 3;
     case 'T': if (!strcmp (wd, "THEN")) return 4;
     case 'Т': if (!strncmp (wd, "ТО", 2) ||
                   !strncmp (wd, "То", 2))
                       return 4;
               break;
     case 'a': if (!strcmp (wd, "and")) return 5;
               break;
     case 'и': if (strlen (wd) == 1)  return 5;
    }
  return 6;
}
/* WordType ----------------------------------------------------------- */
