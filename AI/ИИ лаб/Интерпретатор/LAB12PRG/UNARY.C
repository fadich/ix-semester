/* unary.c              IBM          24.02.95
 H.Schildt interpreter for student studing
 sign changing
*/
  void unary (o,r)
    char o;
     int *r;
 {
  if (o == '-') *r =- (*r);
 }
/*unary.c----------------------------------------------------*/
