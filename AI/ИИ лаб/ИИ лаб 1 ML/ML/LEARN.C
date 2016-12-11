/* Learn.c                             04.09.98
     Learn a class description for an object
  */
#include <stdio.h>
#include "ml.h"

  void learn()
  {
       char  sub[80], verb[80], obj[80],
	     msub[80], mverb[80], mobj[80];
extern FILE  *prtcl;

  for ( ; ; )
    {
      printf("\nEnter an exampl.");
      fputs("\n\nEnter an exampl.", prtcl);
      if (! get_example (sub,verb,obj)) return;
      if (find_may (sub,verb,obj) == -1)
         {
           assert_may (sub,verb,obj);
           generalize (sub,verb,obj);
         }
      printf("Enter a near-miss (NL to skip).");
      fputs("\n\nEnter a near-miss (NL to skip).", prtcl);
      get_example (msub,mverb,mobj);
      restrict (msub,mverb,mobj);
    }
  return;
 }
         
