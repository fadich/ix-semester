/* WordProc.c                  IBM                    20.10.97
   CADSHELL - complex
*/
#include <conio.h>
#include <stdio.h>
#include "expert.h"

char WordProc (str, status)     /*  1 - Ok, 0 - error is present */
     char *str;
      int status;
{
           extern FILE  *debfile;
           extern char  debug;
            static int  stage = 0,
                        num, cf;
           static char  pre_str[40], v_str[40];
    static struct RULE  *c_rule;

   if (debug == 2)
     fprintf(debfile,"WP: <%s> = %d, stage = %d",
                       str, status, stage);
  switch (status)
    {
      case 1: if (stage > 10 ) AddCon (c_rule, pre_str, v_str, cf);
              stage = 1; /*  word "RULE" has been read      */
              break;
      case 2: if (stage == 1) /* word "IF" has been read    */
                 {
                   puts("Number of rule is absent");
                   return 0;
                 }
              if (stage == 2) cf = 100;
              stage = 5;
              c_rule = (struct RULE *) AddRule(num, cf);
              break;
      case 3: if (stage == 11)   stage = 12;  /* word "CF" has been read  */
                  /* next word must be certainty factor */
                else
                    if (stage == 2) stage = 3;
                       else
                         if (stage == 1)
                           {
                             puts("Number of rule is absent");
                             return 0;
                           };
              break;
      case 4: stage = 9; break;          /* THEN */
      case 5: if (stage == 7)  stage = 5;   /*  and  */
                 else
                     {  stage = 9;
                        AddCon(c_rule, pre_str, v_str, cf);
                     }
              break;
      case 6: switch (stage)
               {
                 case  1: num = atoi (str);
                          stage = 2; break;
                 case  3: cf = atoi (str);
                          stage = 4;  break;
                 case  5: strcpy (pre_str, str);  /*  obj */
                          stage = 6;  break;
                 case  6: AddPrem (c_rule, pre_str, str);
                          stage = 7;  break;
                 case  9: strcpy (pre_str, str);    /*  obj */
                          stage = 10;   break;
                 case 10: strcpy (v_str, str);
                          cf = 100;
                          stage = 11;  break;
                 case 12: cf = atoi (str);
                          stage = 13; break;
               } /* end of switch (stage)   */
    } /* end of switch (status)    */
    if (debug == 2) fprintf(debfile," new_stage = %d\n", stage);
  return 1;
}
/*WordProc.c--------------------------------------------------------------*/
