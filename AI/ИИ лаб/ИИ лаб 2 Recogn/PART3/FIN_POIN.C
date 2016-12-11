/* returns the cursor loc of an '*' with the    28.09.98
   search beginning with startx and starty */
/* Возврат курсора.........
   поиск точки начала */

int find_point (startx, starty, x, y)
    int startx, starty, *x, *y;
{
   int a,b;

   a=startx; b=starty;
   do 
     {
      do 
        {
         if (check_point(a,b)) 
           {
             *x=a;  *y=b;
             return 1;
           }
         a++;
        } while (a<79);
      a=0; b++;
     } while (b<24);
   return 0;
}
