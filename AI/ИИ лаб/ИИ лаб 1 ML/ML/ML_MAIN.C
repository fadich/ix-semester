  /* ML_main.c                                04.09.98
   Learning class descripthion by using the 
     "hit-and-near-miss" method
  */
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ml.h"

          FILE  *prtcl;     /* protocol file                 */
  struct attr may[MAX],     /* mdy-have database             */
              must [MAX];   /* must-have database            */
         int  may_pos=0,    /* index into may-have database  */
              must_pos=0;   /* index into must-have database */ 
         char str[20];
  main()
   {
     char s;

    mkwnd (1,1,80,25, YELLOW, BLUE);
    printf("\nEnter a name of your task, please\n");
    gets (str);
    strcat(str, ".ptc");
    if ((prtcl = fopen(str, "w+b")) == NULL)
       {
         printf("\nFile \"%s\" int't opened for writing", str);
         getch();
         exit(1);
       }
       else
         printf("\nFile \"%s\" is opened for protocol\n", str);
   for(;;)
     {
       printf("(L)earn, (D)isplay, or (Q)uit?  ");
       fputs("(L)earn, (D)isplay, or (Q)uit?",prtcl);
       s = getche();
       fprintf(prtcl," %c", s);
       switch (tolower (s))
        {
         case 'l': learn(); break;
         case 'd': display(); break;
         case 'q': fclose(prtcl);
                   cputs("\n\rThat is all!"); getch();
                   exit(1);
        }
         puts(" ");
         fputs("\n\n", prtcl);
     }     
}
 
