/* read the positions for the objects         28.09.98
   Ввод точек объектов */
#include <stdio.h>

void position_2()
{
   int x,y,a,b,i,j;

 gotoxy (0,0);
 do {
      printf("x y position of triangle:");
      scanf("%d%d", &x, &y);
    } while(outrange(x,y));
 do
   {
      printf ("x y position of right triangle: ");
      scanf ("%d%d", &i, &j);
   }  while (outrange(i,j));
 do {
      printf("x y position of square:");
      scanf("%d%d", &a, &b);
    } while (outrange(x,y));
 cls();
 make_triangle (x,y);
 make_square (a,b);
 make_right_triangle (i,j);
}
