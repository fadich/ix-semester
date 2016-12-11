/* check for an isosceles triangle by key points  28.09.98
   Проверка .... */

int istriangle (x,y)
    int x,y;
{
   if (follow (x,y)==2) return 1;

   return 0;
}
