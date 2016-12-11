/*arith.c              IBM_386          13.03.95
H.Schildt interpreter for student studing
*/
void arith (o,r,h)
   char o;
    int *r,*h;
{
    register int t,ex;
   switch (o)
     {
      case '-': *r=*r-*h;
                break;
      case '+': *r=*r+*h;
                break;
      case '*': *r=*r**h;
                break;
      case '/': *r=(*r)/(*h);
                break;
      case '%': t=(*r)/(*h);
                *r=*r-(t*(*h));
                break;
     }
 }
 /*arith.c------------------------------------------------------*/
