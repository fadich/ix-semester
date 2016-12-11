/* determine if there is a route          19.11.98
   between from and to */

void isflight (from,to)
    char *from,*to;
{
       int  d,dist;
      char  anywhere[20];
extern int  tos;

  /* see if destination is reached */
  d= match(from,to);
  if (d)
   {
     push (from, to ,d);
     return;
   }
  /* try another connection */
  dist = find(from,anywhere);
  if (dist)
    {
     push (from,to,dist);
     isflight (anywhere,to);
    }
    else 
      if (tos > 0)
       { /*backtrack*/
         pop (from,to,&dist);
         isflight (from,to);
       }
  return;
}
