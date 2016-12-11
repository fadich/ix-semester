/* draw a triangl at x,y               28.09.98
   Изображение треугольника в точке
  с координатами x,y */
#include <stdio.h>

make_triangle (x,y)
  int x,y;
{
   int t;

 for (t=0; t<5; t++) 
   {
     gotoxy(x-t,y+t);
     printf("*");
   }
 for (t=0; t<5; t++) 
   {
     gotoxy(x+t,y+t);
     printf("*");
   }

 gotoxy(x-5,y+5);
 printf("***********");
 return;
}
