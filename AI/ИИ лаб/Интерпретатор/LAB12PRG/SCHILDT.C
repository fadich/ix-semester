/* schildt.c            IBM 386           19.03.95
H.Schild interpreter for student studing
*/
#include <conio.h>
#include <alloc.h>
#include <process.h>
#include <stdio.h>
#include "schildt.h"

main (argc, argv)
   int argc;
   char *argv[];
{
   char fn[20],
	*p_buf,
	*t;
   int answer;

if (argc != 2)
   {
    mkwnd (26, 7, 54, 7, YELLOW, RED);
    cprintf (" Use format: run <filename> ");
    getch();
    exit (1);
   } 
p_buf = (char *) malloc (PROG_SIZE);
if (!p_buf)
   {
    mkwnd (30, 7, 50, 7, YELLOW, RED);
    cprintf (" Malloc doesn't run ");
    getch();
    exit (1);
   }
if (!load_pgm (p_buf,argv[1])) exit (1);
prog = p_buf;
mkwnd (1, 1, 80, 1, BLACK, LIGHTGRAY);
gotoxy (7, 1);
cprintf("%c Интерпретатор простейшего языка программирования:", 4);
cprintf(" ЛО САПР %c", 4);
mkwnd (1, 2, 80, 25, YELLOW, BLUE);
cprintf(
"==================  И С Х О Д Н Ы Й   Т Е К С Т  ==================");
cprintf("\n\r%s\n\r", p_buf);
cprintf(
"================  Р Е З У Л Ь Т А Т   Р А Б О Т Ы  ================\n\r");
getch();
scan_labels();
ftos = gtos = 0;
do
   {
    get_token();
    if (token_type == VARIABLE)
      {
       putback();
       assignment();
      }
    else
       switch(tok)
          {
           case PRINT : print(); break;
	   case GOTO  : exec_goto(); break;
           case IF    : exec_if(); break;
           case FOR   : exec_for(); break;
	   case NEXT  : next(); break;
           case INPUT : input(); break;
           case GOSUB : gosub(); break;
           case RETURN: greturn(); break;
	   case END   : goto label;
          }
   } while (tok != FINISHED);
 label:
 cprintf("============ Это и все. Нажмите Enter ================");
 getch();
}
/* --------------------------------------------------------------*/
