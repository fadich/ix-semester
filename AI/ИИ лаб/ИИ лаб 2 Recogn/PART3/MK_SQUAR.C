/* draw a square at x,y         28.09.98
   Изображение квадрата */
#include <stdio.h>

make_square (x,y)
    int x,y;
{
   int t;

   for (t=0; t<5; t++) 
     {
       gotoxy (x, y+t);
       printf("*");
     }
   for (t=0; t<5; t++)
     {
       gotoxy (x+10, y+t);
       printf ("*");
     }
   gotoxy(x,y);
   printf("***********");
   gotoxy(x,y+5);
   printf("***********");
   return;
}
