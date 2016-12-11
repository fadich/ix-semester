/* read the positions for the objects         28.09.98
   Ввод точек объектов */
#include <stdio.h>

void position()
{
   int x,y,a,b;

 gotoxy (0,0);
 do {
      printf("x y position of triangle:");
      scanf("%d%d", &x, &y);
    } while(outrange(x,y));

 do {
      printf("x y position of square:");
      scanf("%d%d", &a, &b);
    } while (outrange(x,y));
 cls();
 make_triangle (x,y);
 make_square (a,b);
}
