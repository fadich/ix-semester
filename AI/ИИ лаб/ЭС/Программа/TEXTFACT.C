/* TextFact.c               IBM                    10.04.95
   Reading of text-fact-file      CADSHELL - complex
   Format of the text-fact-file is:
 object (question_to_object) = value, value, ... , value;(.)
*/
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "expert.h"

char TextFact(fn)
    char *fn;
{
    FILE  *pf;
    char  word[80], s,
          flag, p_flag, pos;
    struct OBJECT *curr_obj;

  curr_obj = NULL;
  flag = p_flag = pos = 0;
  strcpy (word,fn);
  strcat (word, ".fct");
  if ((pf = fopen(word, "r")) == NULL)
    { cprintf("\n\rFile \"%s\" isn't opened for reading", word);
      getch();
      return 1;
    }
  cprintf("\n\rReading of the file \"%s\"\n\r", word);
  while(1)    /* cycle of symbols reading from text-fact-file */
   {
     s = fgetc(pf);
     if (feof(pf)) break;
     switch(s)
      {
        case ' ': break;
        case ',':
        case '=': flag = 1;  break;
        case ';': flag = 0;  break;
        case '(': flag = 2;  break;
        case ')': break;
        case '.': flag = 0;  break;
        case '\0': break;
	case '\n': break;
	case '\r':
        case '\t': break;
        default  : if (flag < 3)   /* symbol of name has been read */
                      { p_flag = flag; flag = 3;
                      }
                   word[pos++] = s; /*current symbol has been written
                                      into work word   */
      }  /* end of switch(s)  */
     if ((flag < 3) && pos)  /* symbol of name has been read  */
           word[pos] = '\0';
        else
          continue;
     switch (p_flag)
       {
	 case 1: AddValue (curr_obj, word);  break;
	 case 2: AddQuest (curr_obj, word, 100);  break;
	 case 0: AddObj (&curr_obj, word);
       }
     pos = 0;
   } /* end of while   */
  cputs("  ");
  fclose(pf);
  return 0;
} /* end of TextFact.c ------------------------------------------------- */
