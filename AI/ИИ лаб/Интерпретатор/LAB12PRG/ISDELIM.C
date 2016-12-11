/* isdelim.c                        IBM-386         24.02.95
For H. Schildt interpreter
*/
char isdelim (c)
    char c;
{
  if (strchr(" ;,+-<>/*%=()", c) || c == 9 ||
         c == '\n' || c == '\r' || c == 0)
                              return 1;
                              return 0;
}
/* ------------------------------------------------------------------ */
