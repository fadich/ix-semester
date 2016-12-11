#include <conio.h>
#include "recogn3.h"

/* Delta-D Recognizer                         28.09.98
*/
	     int  pos;   /* indexes into database */
struct oldpoints  oldp[MAX];

main()
  {
     cls();
     clear_db();
     position_2();
     recognize_3();
     getch();
     return;
  }
