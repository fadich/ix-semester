 /* find_eol.c         IBM 386        24.02.95
 */
#include <string.h>

 void find_eol( )
 {
  extern char *prog;

  while (*prog != '\n' && *prog !='\0') ++prog;
  if (*prog) prog++;
 }
/*find_eol-------------------------------------------------------*/
