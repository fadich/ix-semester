/* draw a right triangl at x,y               28.09.98
   Изображение ... треугольника в точке
  с координатами x,y */
#include <stdio.h>

void make_right_triangle(x,y)
     int x,y;
{
   int t;

   for (t=0; t<10; t++) 
      {
        gotoxy (x, y+t);
        printf ("*");
      }
   for (t=0; t<9; t++) 
      {
        gotoxy (x-t+9, y+t);
        printf("*");
      }
   gotoxy (x,y);
   printf("**********");
}
