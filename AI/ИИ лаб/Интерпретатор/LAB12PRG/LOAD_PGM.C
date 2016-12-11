 /* load_pgm.c            IBM           13.03.1995
 H.Schildt interpreter for student studing
 */
#include <stdio.h>
#include "schildt.dfn"

 int load_pgm(p,fname)
     char *p,
          *fname;
 {
  FILE  *fp;
   int  i = 0;

  if (!(fp = fopen(fname,"rb")))  return 0;
  i = 0;
  do
    {
     *p = getc (fp);
     p++;i++;
    } while (!feof(fp) && i < PROG_SIZE);
  *(p-2) = '\0';
  fclose (fp);
  return 1;
 }
/*------------------------------------------------------------------*/
