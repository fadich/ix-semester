/* follow a shape and return number of turns     28.09.98
*/

int follow(x,y)
    int x,y;
{
   int  incx, incy,
        startx, starty, count;

   startx=x;  starty=y;
   count=0;
   assert_oldp (x,y);
   if (!find_direction (x, y, &incx, &incy)) return 0;
   do
     {
       while (check_point (x+incx, y+incy))
         {
           x = incx + x;
           y = incy + y;
           assert_oldp (x,y);
         }
       if (x == startx && y == starty) return count;
       count++;
       if (!find_direction (x, y, &incx, &incy))  return 0;
     } while(1);
}

