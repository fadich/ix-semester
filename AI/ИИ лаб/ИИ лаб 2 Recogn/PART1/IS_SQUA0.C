/* check for a square            28.09.98
   */

int issquare(x,y)
    int x,y;
{
   if (check_point(x+1,y) && check_point(x,y+1))
      return 1;

   return 0;
}