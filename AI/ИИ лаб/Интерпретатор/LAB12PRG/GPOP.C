/*gpop.c             IBM          19.03.1995
H.Schildt interpreter for student studing
*/
char * gpop()
{
  extern char  *gstack[];
   extern int  gtos;

   if (!gtos)
      {
	serror (13,"gpop");
	return ("");
      }
   return (gstack[gtos--]);
}
/*-------------------------------------------------------*/
