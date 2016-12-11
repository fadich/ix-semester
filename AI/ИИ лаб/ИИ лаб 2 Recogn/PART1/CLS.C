/* clear the screen                28.09.98
   Очистка экрана */
#include <dos.h>

cls()
{
   union REGS regs;

   regs.h.ah=6;
   regs.h.al=0;
   regs.h.ch=0;
   regs.h.cl=0;
   regs.h.dh=24;
   regs.h.dl=79;
   regs.h.bh=7;
   int86 (16, &regs, &regs);
   return;
}
