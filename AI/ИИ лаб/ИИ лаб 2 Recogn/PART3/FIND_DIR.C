/* find a new line to follow               28.09.98
   Поиск новой линии для слежения
   */

int find_direction (x,y,incx,incy)
    int  x,y,*incx,*incy;
{
   register int a,b;

   for (a=-1; a<2; a++)
     for (b=-1; b<2; b++)
       if (check_point (x+a,y+b) && !find (x+a,y+b))
         {
           *incx=a; *incy=b;
           return 1;
         }
   return 0;
}

