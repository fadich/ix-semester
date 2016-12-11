/* check for a right triangle by key points    28.09.98
    Проверка ..... */

int isright (x,y)
     int x,y;
{
   if (check_point (x+9,y) && check_point (x,y+9))
      return 1;

   return 0;
}
