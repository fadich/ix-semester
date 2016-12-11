/* TextRule.c            IBM               20.10.97
  Reading of text-rule-file
  CADSHELL - complex
*/
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "expert.h"

char TextRule(fn)
   char *fn;
{
        FILE  *pf;
        char  filename[40], s,
              word[40],
              wordflag = 0,
              word_pos = 0;

 strcpy (filename, fn);
 strcat (filename, ".rul");
 if ((pf = fopen(filename,"r")) == NULL)
   {
     printf("\nFile \"%s\" isn't opened for reading",filename);
     getch();
     return 1;
   }
 cprintf("Reading of rule base from file: \"%s\"\n\r",
	   filename);
 while(1)  /* cycle of symbols reading from rule base file */
   {
     s = fgetc(pf);
     if (s == ' ' ||  s == '=' || s == '\0' || s == '\n' ||
         s == '(' ||  s == ')' || s == '.'  || s == ','  ||
         s == ';' ||  s == '\r' || s == '\t'|| s == EOF)
       { /* delimiter has read  */
         if ( s == EOF )
	    { WordProc (word, 1);
	      break;
	    }
	 if (wordflag)
	    { /* word has read     */
	      wordflag = 2;
	      word[word_pos] = '\0';
	    }
       }
      else
         {
           if (!wordflag) wordflag = 1;
           word[word_pos++] = s;
         }
     if (wordflag < 2) continue;
     wordflag = word_pos = 0;
     /* word processing  */
     s = (char) WordType(word);
     if (!(int) WordProc(word, (int) s) ) puts("Error");
   } /* end of while - cycle                     */
 fclose(pf);
 return 0;
}
/* TextRule ------------------------------------------------------------ */
