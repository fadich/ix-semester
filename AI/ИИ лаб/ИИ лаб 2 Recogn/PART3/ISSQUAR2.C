/* check for a square by key points       28.09.98
   Проверка квадрата по ключевой точке */

int issquare(x,y)
    int x,y;
{
   if (follow(x,y)==3)  return 1;

   return 0;
}
