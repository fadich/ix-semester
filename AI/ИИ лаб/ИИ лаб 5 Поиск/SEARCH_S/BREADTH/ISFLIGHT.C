/* determine if there is a route          19.11.98
   between from and to       "breadth-first mth"    */

void isflight (from,to)
    char *from,*to;
{
       int  d,dist;
      char  anywhere[20];
extern int  tos;

while (dist = find (from, anywhere))
  {
    d = match (anywhere,to);
    if (d)
      {
	push (from, to ,dist);
	push (anywhere,to,d);
	return;
      }
  }
  /* try any connection */
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
