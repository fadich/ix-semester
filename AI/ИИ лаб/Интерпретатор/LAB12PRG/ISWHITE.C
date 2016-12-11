/* iswhite.c                      IBM-386          24.02.94
For H. Schildt interpreter
*/
char  iswhite (c)
     char c;
{
   if (c == ' ' || c == '\t') return 1;
                              return 0;
}
/* -------------------------------------------------------------------- */
