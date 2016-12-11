/* serror.c             IBM           13.03.95
H.Schildt interpreter for student studing
*/
#include <alloc.h>
#include <conio.h>
#include<process.h>

void serror (error, pgm)
    int error;
   char *pgm;
{
	  char *buff;
	   int x, y;
   static char *e[]=
     {
      "Syntax error",
      "Expecting ')'",
      "It isn't expression",
      "Expecting '='",
      "It isn't variable",
      "Table of labels is overfull",
      "Double of label",
      "Undefined label",
      "Needed THEN",
      "Needed TO",
      "Too many levels of FOR cycle",
      "NEXT doesn't correspond to the FOR",
      "Too many levels of GOSUB",
      "RETURN doesn't correspond to the GOSUB"
     };

     if ((buff = malloc (161)) == NULL)
	{  mkwnd (25, 5, 35, 5, YELLOW, RED);
	   cprintf ("  Œ «® Ž‡“");
	   getch ();
	   return;
	}
     x = wherex();
     y = wherey();
     gettext (1, 1, 80, 1, buff);
     mkwnd (1, 1, 80, 1, YELLOW, RED);
     printf ("%s: %s",pgm, e[error]);
     if (getch () == 27) exit(1);
     puttext (1, 1, 80, 1, buff);
     free (buff);
     window (1, 2, 80, 25);
     textcolor (YELLOW);
     textbackground (BLUE);
     gotoxy (x, y);
}
/*serror-------------------------------------------------------*/
