/* check to see if the point is an '*'      28.09.98
   by using BIOS int 10h,#8 */
/*Проверка является ли точка знаком '*'*/
#include <dos.h>

int check_point (a,b)
    int a,b;
{
  union REGS regs;

   gotoxy(a,b);
   regs.h.ah = 8;
   regs.h.bh = 0;
   int86 (16, &regs, &regs);
   if( regs.h.al=='*') return 1;
   return 0;
}
